/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
#include <iostream>
#include<cstddef>

template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  ListNode* position = head_;
  return List<T>::ListIterator(position);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  if(tail_ != NULL){
  ListNode* position = tail_;
  return List<T>::ListIterator(position->next);
} else{
   return List<T>::ListIterator(NULL);
}

}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode * thru = head_;
  while(thru != NULL){
    ListNode * tmp = thru->next;
    delete thru;
    thru = tmp;
  }
  head_ = NULL;
  tail_ = NULL;
}
/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1

  ListNode * newNode = new ListNode(ndata);

  newNode -> next = head_;
  newNode -> prev = NULL;

  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }

  head_ = newNode;
  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode *newNode = new ListNode(ndata);
  newNode->prev = tail_;
  newNode->next = NULL;

  if(head_ == NULL){
    head_ = newNode;
  }

  if(tail_ != NULL){
    tail_->next = newNode;
  }

  tail_ = newNode;

  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;
  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }
  if (curr != NULL && curr->prev!= NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }
  return curr;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  ListNode * curr = head_;

  while(curr->next!= tail_ && curr->next != NULL){
    curr = curr->next;
    ListNode * tmp = curr->next;
    //remove
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    //insert back
    curr->prev = tail_;
    curr->next = NULL;
    tail_-> next = curr;
    tail_ = curr;
    // next round
    curr = tmp;
  }
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  if (this->size() <= 1 ) return;
  // ListNode* st = startPoint, ed = endPoint;
  ListNode* s_prev = startPoint->prev;
  ListNode* e_next = endPoint->next;

  startPoint->prev = startPoint->next;
  startPoint->next = e_next;
  endPoint ->next = endPoint->prev;
  endPoint->prev = s_prev;

  ListNode * thru = startPoint->prev;
  while (thru != endPoint){
    ListNode * tmp = thru->prev;
    thru->prev = thru->next;
    thru->next = tmp;
    thru = thru->prev;
  }
  ListNode* tmp2 = startPoint;
  startPoint = endPoint;
  endPoint = tmp2;
  if (s_prev != NULL) s_prev->next = startPoint;
  else head_ = startPoint;
  if (e_next != NULL) e_next->prev = endPoint;
  else tail_ = endPoint;

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  int remain = this->size();
  int total_size = this->size();
  int num = 0;
  if(total_size%n !=0){
    num = total_size/n +1;
  }
  else num = total_size/n;

  ListNode * startPoint = head_;
  ListNode * endPoint = startPoint;

  for(int x=0; x< num; x++){

    if(remain < n ) n = remain;
    for(int i = 0; i < n-1; i++){
      endPoint = endPoint->next;
    }

    reverse(startPoint,endPoint);
    startPoint = endPoint->next;
    endPoint = startPoint;
    remain = remain - n;

}
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL){
            tail_ = tail_->next;
          }
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2

    ListNode* head = first;
    while (second != NULL && first != NULL) {
      if(first ->data < second->data){
        ListNode* tmp = first ->next;
          if(first->next == NULL){
            second->prev = first;
            first->next = second;
          }
          first = tmp;
      } else {
        ListNode* tmp = second;
        second = second->next;
        if(second != NULL)
          second->prev = NULL;
        tmp ->next = NULL;
          //insert second
        tmp->next = first;
        tmp->prev = first->prev;
         // push back first
        if(first->prev == NULL){
            head = tmp;
        } else {
            first->prev->next = tmp;
        }
        first->prev = tmp;
      }
    }
    return head;
}



/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if(start == NULL||start->next == NULL) return start;
  int length  = chainLength;
  int mid = (length)/2;
  ListNode * start2 = start;
  for(int i =0; i < mid; i++){
    //start = start2;
    start2 = start2->next;
  }
  if(start2 != NULL){
    start2->prev->next =NULL;
    start2->prev =NULL;
  }

  ListNode* head1 = mergesort(start, mid);
  ListNode* head2 = mergesort(start2, length - mid);
  return merge(head1,head2);
}
