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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "CSE333.h"
#include "HashTable.h"
#include "HashTable_priv.h"

// A private utility function to grow the hashtable (increase
// the number of buckets) if its load factor has become too high.
static void ResizeHashtable(HashTable ht);

// a free function that does nothing
static void LLNullFree(LLPayload_t freeme) { }
static void HTNullFree(HTValue_t freeme) { }

HashTable AllocateHashTable(HWSize_t num_buckets) {
  HashTable ht;
  HWSize_t  i;

  // defensive programming
  if (num_buckets == 0) {
    return NULL;
  }

  // allocate the hash table record
  ht = (HashTable) malloc(sizeof(HashTableRecord));
  if (ht == NULL) {
    return NULL;
  }

  // initialize the record
  ht->num_buckets = num_buckets;
  ht->num_elements = 0;
  ht->buckets =
    (LinkedList *) malloc(num_buckets * sizeof(LinkedList));
  if (ht->buckets == NULL) {
    // make sure we don't leak!
    free(ht);
    return NULL;
  }
  for (i = 0; i < num_buckets; i++) {
    ht->buckets[i] = AllocateLinkedList();
    if (ht->buckets[i] == NULL) {
      // allocating one of our bucket chain lists failed,
      // so we need to free everything we allocated so far
      // before returning NULL to indicate failure.  Since
      // we know the chains are empty, we'll pass in a
      // free function pointer that does nothing; it should
      // never be called.
      HWSize_t j;
      for (j = 0; j < i; j++) {
        FreeLinkedList(ht->buckets[j], LLNullFree);
      }
      free(ht->buckets);
      free(ht);
      return NULL;
    }
  }

  return (HashTable) ht;
}

void FreeHashTable(HashTable table,
                   ValueFreeFnPtr value_free_function) {
  HWSize_t i;

  Verify333(table != NULL);  // be defensive

  // loop through and free the chains on each bucket
  for (i = 0; i < table->num_buckets; i++) {
    LinkedList  bl = table->buckets[i];
    HTKeyValue *nextKV;

    // pop elements off the the chain list, then free the list
    while (NumElementsInLinkedList(bl) > 0) {
      Verify333(PopLinkedList(bl, (LLPayload_t*)&nextKV));
      value_free_function(nextKV->value);
      free(nextKV);
    }
    // the chain list is empty, so we can pass in the
    // null free function to FreeLinkedList.
    FreeLinkedList(bl, LLNullFree);
  }

  // free the bucket array within the table record,
  // then free the table record itself.
  free(table->buckets);
  free(table);
}

HWSize_t NumElementsInHashTable(HashTable table) {
  Verify333(table != NULL);
  return table->num_elements;
}

HTKey_t FNVHash64(unsigned char *buffer, HWSize_t len) {
  // This code is adapted from code by Landon Curt Noll
  // and Bonelli Nicola:
  //
  // http://code.google.com/p/nicola-bonelli-repo/
  static const uint64_t FNV1_64_INIT = 0xcbf29ce484222325ULL;
  static const uint64_t FNV_64_PRIME = 0x100000001b3ULL;
  unsigned char *bp = (unsigned char *) buffer;
  unsigned char *be = bp + len;
  uint64_t hval = FNV1_64_INIT;

  /*
   * FNV-1a hash each octet of the buffer
   */
  while (bp < be) {
    /* xor the bottom with the current octet */
    hval ^= (uint64_t) * bp++;
    /* multiply by the 64 bit FNV magic prime mod 2^64 */
    hval *= FNV_64_PRIME;
  }
  /* return our new hash value */
  return hval;
}

HTKey_t FNVHashInt64(HTValue_t hashval) {
  unsigned char buf[8];
  int i;
  uint64_t hashme = (uint64_t)hashval;

  for (i = 0; i < 8; i++) {
    buf[i] = (unsigned char) (hashme & 0x00000000000000FFULL);
    hashme >>= 8;
  }
  return FNVHash64(buf, 8);
}

HWSize_t HashKeyToBucketNum(HashTable ht, HTKey_t key) {
  return key % ht->num_buckets;
}

// helper function: take in a key, a iterator of a KVPair list, a pointer
// to store the pair if the key is found. It starts to look up the key
// from where the iterator is at right now
// parameter: key: the target key
//            iter: the iterator
//            result: the pointer to store the result
static int findKVPair(HTKey_t key, LLIter iter, HTKeyValue** result) {
  // check for null iterator
  if (iter == NULL) {
    return 0;
  }

  // loop through the list
  while (LLIteratorHasNext(iter)) {
    LLIteratorGetPayload(iter, (void**) result);
    if ((*result)->key == key) {
      return 1;
    }
    LLIteratorNext(iter);
  }

  // The last element is an edge case, check for it individually
  LLIteratorGetPayload(iter, (void**) result);
  if ((*result)->key == key) {
    return 1;
  }

  // not found
  return 0;
}

int InsertHashTable(HashTable table,
                    HTKeyValue newkeyvalue,
                    HTKeyValue *oldkeyvalue) {
  HWSize_t insertbucket;
  LinkedList insertchain;

  Verify333(table != NULL);
  ResizeHashtable(table);

  // calculate which bucket we're inserting into,
  // grab its linked list chain
  insertbucket = HashKeyToBucketNum(table, newkeyvalue.key);
  insertchain = table->buckets[insertbucket];

  // Step 1 -- finish the implementation of InsertHashTable.
  // This is a fairly complex task, so you might decide you want
  // to define/implement a helper function that helps you find
  // and optionally remove a key within a chain, rather than putting
  // all that logic inside here.  You might also find that your helper
  // can be reused in steps 2 and 3.
  HTKeyValue* newKV= (HTKeyValue*) malloc(sizeof(HTKeyValue));
  // check if malloc failed
  if (newKV == NULL) {
    return 0;
  }
  newKV->key = newkeyvalue.key;
  newKV->value = newkeyvalue.value;

  // empty case, no need to search
  if (NumElementsInLinkedList(insertchain) == 0) {
    int success = PushLinkedList(insertchain, (LLPayload_t) newKV);
    // check if push node failed
    if (!success) {
      free(newKV);
      return 0;
    }
    table->num_elements++;
    return 1;
  }

  // non-empty case, need to loop though the list
  LLIter iter = LLMakeIterator(insertchain, 0);
  // check if make iterator failed
  if (iter == NULL) {
    free(newKV);
    return 0;
  }

  HTKeyValue* oldKV;
  int success2 = findKVPair(newKV->key, iter, &oldKV);
  if (success2) {  // found the key
    int success3 = PushLinkedList(insertchain, (LLPayload_t) newKV);
    if (!success3) {  // not freeing oldKV when failed, not changing list
      LLIteratorFree(iter);
      free(newKV);
      return 0;
    }
    oldkeyvalue->key = oldKV->key;
    oldkeyvalue->value = oldKV->value;
    LLIteratorDelete(iter, LLNullFree);
    free(oldKV);
    LLIteratorFree(iter);
    return 2;

  } else {  // not found
    int success3 = PushLinkedList(insertchain, (LLPayload_t) newKV);
    LLIteratorFree(iter);
    if (!success3) {  // not changing list
      free(newKV);
      return 0;
    }
    table->num_elements++;
    return 1;
  }

  return 0;
}

int LookupHashTable(HashTable table,
                    HTKey_t key,
                    HTKeyValue *keyvalue) {
  Verify333(table != NULL);

  // Step 2 -- implement LookupHashTable.
  uint32_t hashValue = HashKeyToBucketNum(table, key);
  LinkedList chain = table->buckets[hashValue];
  // check if the list is empty
  if (NumElementsInLinkedList(chain) == 0) {
    return 0;
  }

  LLIter iter = LLMakeIterator(chain, 0);
  // check if make iterator failed
  if (iter == NULL) {
    return -1;
  }

  HTKeyValue* resultKV;
  int success = findKVPair(key, iter, &resultKV);
  if (!success) {  // not found
    LLIteratorFree(iter);
    return 0;
  } else {  // found the key
    keyvalue->key = resultKV->key;
    keyvalue->value = resultKV->value;
    LLIteratorFree(iter);
    return 1;
  }
}

int RemoveFromHashTable(HashTable table,
                        HTKey_t key,
                        HTKeyValue *keyvalue) {
  Verify333(table != NULL);

  // Step 3 -- implement RemoveFromHashTable.
  uint32_t hashValue = HashKeyToBucketNum(table, key);
  LinkedList chain = table->buckets[hashValue];
  // check if the list is empty
  if (NumElementsInLinkedList(chain) == 0) {
    return 0;
  }

  // check if make iterator failed
  LLIter iter = LLMakeIterator(chain, 0);
  if (iter == NULL) {
    return -1;
  }

  HTKeyValue* resultKV;
  int success = findKVPair(key, iter, &resultKV);
  if (!success) {  // not found
    LLIteratorFree(iter);
    return 0;
  } else {  // found the key
    keyvalue->key = resultKV->key;
    keyvalue->value = resultKV->value;
    LLIteratorDelete(iter, LLNullFree);
    free(resultKV);
    table->num_elements--;
    LLIteratorFree(iter);
    return 1;
  }

  return 0;  // you may need to change this return value.
}

HTIter HashTableMakeIterator(HashTable table) {
  HTIterRecord *iter;
  HWSize_t      i;

  Verify333(table != NULL);  // be defensive

  // malloc the iterator
  iter = (HTIterRecord *) malloc(sizeof(HTIterRecord));
  if (iter == NULL) {
    return NULL;
  }

  // if the hash table is empty, the iterator is immediately invalid,
  // since it can't point to anything.
  if (table->num_elements == 0) {
    iter->is_valid = false;
    iter->ht = table;
    iter->bucket_it = NULL;
    return iter;
  }

  // initialize the iterator.  there is at least one element in the
  // table, so find the first element and point the iterator at it.
  iter->is_valid = true;
  iter->ht = table;
  for (i = 0; i < table->num_buckets; i++) {
    if (NumElementsInLinkedList(table->buckets[i]) > 0) {
      iter->bucket_num = i;
      break;
    }
  }
  Verify333(i < table->num_buckets);  // make sure we found it.
  iter->bucket_it = LLMakeIterator(table->buckets[iter->bucket_num], 0UL);
  if (iter->bucket_it == NULL) {
    // out of memory!
    free(iter);
    return NULL;
  }
  return iter;
}

void HTIteratorFree(HTIter iter) {
  Verify333(iter != NULL);
  if (iter->bucket_it != NULL) {
    LLIteratorFree(iter->bucket_it);
    iter->bucket_it = NULL;
  }
  iter->is_valid = false;
  free(iter);
}

int HTIteratorNext(HTIter iter) {
  Verify333(iter != NULL);

  // Step 4 -- implement HTIteratorNext.
  // check for iter validity
  if (iter->is_valid) {
    // check if the bucket iter still has elements
    if (LLIteratorNext(iter->bucket_it)) {  // still in current bucket
      return 1;
    } else {  // go to next bucket, or end
      if (iter->bucket_num < (iter->ht->num_buckets - 1)) {
        // try to find the the next one
        for (int i = iter->bucket_num + 1; i < iter->ht->num_buckets; i++) {
          if (NumElementsInLinkedList(iter->ht->buckets[i]) > 0) {
            // found the next non-empty bucket, go to it
            iter->bucket_num = i;
            LLIteratorFree(iter->bucket_it);
            iter->bucket_it = LLMakeIterator(iter->ht->buckets[i], 0);
            return 1;
          }
        }
        // if after the for loop we did not find one valid bucket,
        // we shall end the iter
        iter->is_valid = false;
        return 0;
      } else {  // at the final bucket already, in this case end the iter
        iter->is_valid = false;
        return 0;
      }
    }
  }

  return 0;
}

int HTIteratorPastEnd(HTIter iter) {
  Verify333(iter != NULL);

  // Step 5 -- implement HTIteratorPastEnd.
  if (iter->is_valid) {
    return 0;
  }

  return 1;  // you might need to change this return value.
}

int HTIteratorGet(HTIter iter, HTKeyValue *keyvalue) {
  Verify333(iter != NULL);

  // Step 6 -- implement HTIteratorGet.
  if (iter->is_valid) {
    HTKeyValue* payload;
    LLIteratorGetPayload(iter->bucket_it, (void**) &payload);
    keyvalue->key = payload->key;
    keyvalue->value = payload->value;
    return 1;
  }

  return 0;  // you might need to change this return value.
}

int HTIteratorDelete(HTIter iter, HTKeyValue *keyvalue) {
  HTKeyValue kv;
  int res, retval;

  Verify333(iter != NULL);

  // Try to get what the iterator is pointing to.
  res = HTIteratorGet(iter, &kv);
  if (res == 0)
    return 0;

  // Advance the iterator.
  res = HTIteratorNext(iter);
  if (res == 0) {
    retval = 2;
  } else {
    retval = 1;
  }
  res = RemoveFromHashTable(iter->ht, kv.key, keyvalue);
  Verify333(res == 1);
  Verify333(kv.key == keyvalue->key);
  Verify333(kv.value == keyvalue->value);

  return retval;
}

static void ResizeHashtable(HashTable ht) {
  // Resize if the load factor is > 3.
  if (ht->num_elements < 3 * ht->num_buckets)
    return;

  // This is the resize case.  Allocate a new hashtable,
  // iterate over the old hashtable, do the surgery on
  // the old hashtable record and free up the new hashtable
  // record.
  HashTable newht = AllocateHashTable(ht->num_buckets * 9);

  // Give up if out of memory.
  if (newht == NULL)
    return;

  // Loop through the old ht with an iterator,
  // inserting into the new HT.
  HTIter it = HashTableMakeIterator(ht);
  if (it == NULL) {
    // Give up if out of memory.
    FreeHashTable(newht, &HTNullFree);
    return;
  }

  while (!HTIteratorPastEnd(it)) {
    HTKeyValue item, dummy;

    Verify333(HTIteratorGet(it, &item) == 1);
    if (InsertHashTable(newht, item, &dummy) != 1) {
      // failure, free up everything, return.
      HTIteratorFree(it);
      FreeHashTable(newht, &HTNullFree);
      return;
    }
    HTIteratorNext(it);
  }

  // Worked!  Free the iterator.
  HTIteratorFree(it);

  // Sneaky: swap the structures, then free the new table,
  // and we're done.
  {
    HashTableRecord tmp;

    tmp = *ht;
    *ht = *newht;
    *newht = tmp;
    FreeHashTable(newht, &HTNullFree);
  }

  return;
}
