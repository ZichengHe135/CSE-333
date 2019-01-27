/*
 * Copyright ©2018 Hal Perkins.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Summer Quarter 2018 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include <iostream>
#include <algorithm>
#include <unordered_set>

#include "./QueryProcessor.h"

extern "C" {
  #include "./libhw1/CSE333.h"
}

using namespace std;

namespace hw3 {

QueryProcessor::QueryProcessor(list<string> indexlist, bool validate) {
  // Stash away a copy of the index list.
  indexlist_ = indexlist;
  arraylen_ = indexlist_.size();
  Verify333(arraylen_ > 0);

  // Create the arrays of DocTableReader*'s. and IndexTableReader*'s.
  dtr_array_ = new DocTableReader *[arraylen_];
  itr_array_ = new IndexTableReader *[arraylen_];

  // Populate the arrays with heap-allocated DocTableReader and
  // IndexTableReader object instances.
  list<string>::iterator idx_iterator = indexlist_.begin();
  for (HWSize_t i = 0; i < arraylen_; i++) {
    FileIndexReader fir(*idx_iterator, validate);
    dtr_array_[i] = new DocTableReader(fir.GetDocTableReader());
    itr_array_[i] = new IndexTableReader(fir.GetIndexTableReader());
    idx_iterator++;
  }
}

QueryProcessor::~QueryProcessor() {
  // Delete the heap-allocated DocTableReader and IndexTableReader
  // object instances.
  Verify333(dtr_array_ != nullptr);
  Verify333(itr_array_ != nullptr);
  for (HWSize_t i = 0; i < arraylen_; i++) {
    delete dtr_array_[i];
    delete itr_array_[i];
  }

  // Delete the arrays of DocTableReader*'s and IndexTableReader*'s.
  delete[] dtr_array_;
  delete[] itr_array_;
  dtr_array_ = nullptr;
  itr_array_ = nullptr;
}

list<docid_element_header> intersection(const list<docid_element_header>& a,
                                        const list<docid_element_header>& b) {
    list<docid_element_header> rtn;
    list<docid_element_header>::const_iterator it1;
    list<docid_element_header>::const_iterator it2;
    for (it1 = a.begin(); it1 != a.end(); it1++) {  // iterator 1
    for (it2 = b.begin(); it2 != b.end(); it2++) {  // iterator 2
      if (it1->docid == it2->docid) {  // encounter intersection
        docid_element_header new_deh;
        new_deh.num_positions = it1->num_positions + it2->num_positions;
        new_deh.docid = it1->docid;
        rtn.push_back(new_deh);
        break;
      }
    }
  }
    return rtn;
}

list<docid_element_header> ProcessOne(IndexTableReader* itr,
                                      const list<docid_element_header> &result,
                                      const vector<string> &query,
                                      HWSize_t pos,
                                      HWSize_t size) {
  if (pos >= size) {  // finished all queries
    return result;
  }
  list<docid_element_header> merged_result;
  DocIDTableReader* ditr = itr->LookupWord(query[pos]);
  if (ditr == NULL) {  // can't find the word
    return merged_result;
  } else {  // found the word
    list<docid_element_header> new_result = ditr->GetDocIDList();
    delete ditr;
    if (result.size() != 0) {  // normal case
      merged_result = intersection(result, new_result);
    } else {  // edge case, the first query
      merged_result = new_result;
    }
    if (merged_result.size() == 0) {  // no intersection
      return merged_result;
    } else {  // there are results, continue recursion
      return ProcessOne(itr, merged_result, query, pos + 1, size);
    }
  }
}

vector<QueryProcessor::QueryResult>
QueryProcessor::ProcessQuery(const vector<string> &query) {
  Verify333(query.size() > 0);
  vector<QueryProcessor::QueryResult> finalresult;

  // MISSING:
  HWSize_t qs = query.size();
  // first, use for loop for each index file
  for (HWSize_t i = 0; i < arraylen_; i++) {
    DocTableReader* dtr = dtr_array_[i];
    IndexTableReader* itr = itr_array_[i];

    list<docid_element_header> docid_list;
    // get the docid_list for docs with all the query words by recursion
    docid_list = ProcessOne(itr, docid_list, query, 0, qs);
    if (docid_list.size() == 0) {
      continue;
    }
    for (auto k : docid_list) {
      // get all the files and their rank, push into final result
      string filename;
      Verify333(dtr->LookupDocID(k.docid, &filename));
      QueryResult qr;
      qr.document_name = filename;
      qr.rank = k.num_positions;
      finalresult.push_back(qr);
    }
  }

  // Sort the final results.
  std::sort(finalresult.begin(), finalresult.end());
  return finalresult;
}

}  // namespace hw3





