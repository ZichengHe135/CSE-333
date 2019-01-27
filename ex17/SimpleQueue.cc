// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.

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

#include "SimpleQueue.h"

// thread safe lock
static pthread_mutex_t queue_lock;

// initiate a lock
SimpleQueue::SimpleQueue() {
  size = 0;
  front = nullptr;
  end = nullptr;
  pthread_mutex_init(&queue_lock, NULL);
}

SimpleQueue::~SimpleQueue() {
  while (front != nullptr) {
    node *next = front->next;
    delete front;
    front = next;
  }
  // destroy the lock
  pthread_mutex_destroy(&queue_lock);
}

// lock before editing the queue, unlock after
void SimpleQueue::Enqueue(string item) {
  pthread_mutex_lock(&queue_lock);
  node *new_node = new node();
  new_node->next = nullptr;
  new_node->item = item;
  if (end != nullptr) {
    end->next = new_node;
  } else  {
    front = new_node;
  }
  end = new_node;
  size++;
  pthread_mutex_unlock(&queue_lock);
}

// lock before editing the queue, unlock after
bool SimpleQueue::Dequeue(string *result) {
  if (size == 0) {
    return false;
  }
  pthread_mutex_lock(&queue_lock);
  *result = front->item;
  node *next = front->next;
  delete front;
  if (end == front) {
    end = front = next;
  } else {
    front = next;
  }
  size--;
  pthread_mutex_unlock(&queue_lock);
  return true;
}

int SimpleQueue::Size() const {
  return size;
}

bool SimpleQueue::IsEmpty() const {
  return size == 0;
}
