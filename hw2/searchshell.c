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

// Feature test macro for strtok_r (c.f., Linux Programming Interface p. 63)
#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "libhw1/CSE333.h"
#include "memindex.h"
#include "filecrawler.h"

static void Usage(void);

int main(int argc, char **argv) {
  if (argc != 2)
    Usage();

  // Implement searchshell!  We're giving you very few hints
  // on how to do it, so you'll need to figure out an appropriate
  // decomposition into functions as well as implementing the
  // functions.  There are several major tasks you need to build:
  //
  //  - crawl from a directory provided by argv[1] to produce and index
  //  - prompt the user for a query and read the query from stdin, in a loop
  //  - split a query into words (check out strtok_r)
  //  - process a query against the index and print out the results
  //
  // When searchshell detects end-of-file on stdin (cntrl-D from the
  // keyboard), searchshell should free all dynamically allocated
  // memory and any other allocated resources and then exit.
  int res;
  char* dirname = argv[1];
  DocTable doctable;
  MemIndex index;
  printf("Indexing \'%s\'\n", argv[1]);

  // crawl
  res = CrawlFileTree(dirname, &doctable, &index);
  Verify333(res != 0);

  // query
  while (1) {
    // get query
    printf("enter query:\n");
    char line[500];
    if (fgets(line, sizeof(line), stdin) != NULL) {
      for (int i = 0; i < strlen(line); i++) {
        line[i] = tolower(line[i]);
      }
      char** query = (char**)malloc(100 * sizeof(char*));
      Verify333(query != NULL);

      // split
      int i = 1;
      char* token = strtok(line, " ");
      query[0] = token;
      while (i < 100) {  // don't go over query array size
        token = strtok(NULL, " ");
        if (token == NULL) {  // finished
          break;
        }
        query[i] = token;
        i++;
      }
      char *eof = strchr(query[i - 1], '\n');
      if (eof) {
        *eof = '\0';
      }

      // search
      LinkedList result = MIProcessQuery(index, query, i);
      if (result != NULL) {  // user typed words in
        if (NumElementsInLinkedList(result) != 0) {  // found result
          LLIter iter = LLMakeIterator(result, 0);
          do {  // loop though result files and print out names and ranks
            SearchResult* sr;
            LLIteratorGetPayload(iter, (LLPayload_t *)&sr);
            char* filename = DTLookupDocID(doctable, sr->docid);
            printf("  %s (%u)\n", filename, sr->rank);
         } while (LLIteratorNext(iter));
          LLIteratorFree(iter);
          FreeLinkedList(result, &free);
        } else {  // did not found any result
          FreeLinkedList(result, &free);
          continue;
        }
      }
      free(query);
    } else {  // exit the program if user push ctrl+D
      break;
    }
  }
  FreeMemIndex(index);
  FreeDocTable(doctable);
  return EXIT_SUCCESS;
}

static void Usage(void) {
  fprintf(stderr, "Usage: ./searchshell <docroot>\n");
  fprintf(stderr,
          "where <docroot> is an absolute or relative " \
          "path to a directory to build an index under.\n");
  exit(EXIT_FAILURE);
}

