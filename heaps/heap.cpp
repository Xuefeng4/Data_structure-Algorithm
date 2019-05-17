#include <cmath>
#include <vector>
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */


template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return 2*currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return 2*currentIdx+1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return floor(currentIdx/2);
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child

    return currentIdx * 2 <= _elems.size()-1;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()

    size_t left = leftChild(currentIdx);
    size_t right = rightChild(currentIdx);
    if (right >= _elems.size()) return left;
    if(higherPriority(_elems[left], _elems[right]))
      return left;
    else return right;

}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
  //   if(currentIdx >= _elems.size()) return;
  //   int leftChild = currentIdx*2;
  //   int rightChild = currentIdx*2 + 1;
  //   int child;
  //   if(_elem[leftChild] <= _elems[rightChild])
  //     child = leftChild;
  //   else
  //     child = rightChild;
  //   if(_elem[currentIdx] > _elems[child]){
  //     std::swap(_elem[currentIdx],_elems[child]);
  //     heapifyDown(child);
  //   }
  // }
    //@TODO Implement the heapifyDown algorithm.
    if(!hasAChild(currentIdx)) return;
    size_t childIdx = maxPriorityChild(currentIdx);
    if(higherPriority(_elems[childIdx],_elems[currentIdx])){
      std::swap(_elems[currentIdx],_elems[childIdx]);
      heapifyDown(childIdx);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    // if(currentIdx < 2) return;
    //
    // int parent = currentIdx/2;
    //
    // if(_elems[currentIdx]<_elems[parent]){
    //   std::swap(_elems[currentIdx],)_elems[parent])
    //   heapifyUp(parent);
    // }
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    //@TODO Construct a heap using the buildHeap algorithm
    _elems.push_back(T());
    for(auto it = elems.begin();it != elems.end();it++){
      _elems.push_back(*it);
    }
    //int intNode = ceil((_elems.size()-1)/2);
    for(int i = parent(_elems.size()-1); i > 0; i--){
      heapifyDown(i);
    }//_elems.size()-1-intNode
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    //@TODO Remove, and return, the element with highest priority
    if(empty()) return T();
    T rtu = _elems[1];
    _elems[1] = _elems[_elems.size() - 1];
    _elems.pop_back();
    heapifyDown(1);
    return rtu;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return _elems[root()];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size()-1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    _elems[idx]= elem;
    if(!higherPriority(elem,_elems[maxPriorityChild(idx)]))
    heapifyDown(idx);
    if(higherPriority(elem,_elems[parent(idx)]))
    heapifyUp(idx);
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    return _elems.size()<=1;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
