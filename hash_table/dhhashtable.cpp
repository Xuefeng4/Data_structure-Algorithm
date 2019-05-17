/**
 * @file dhhashtable.cpp
 * Implementation of the DHHashTable class.
 */

#include "dhhashtable.h"

template <class K, class V>
DHHashTable<K, V>::DHHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new std::pair<K, V>*[size];
    should_probe = new bool[size];
    for (size_t i = 0; i < size; i++) {
        table[i] = NULL;
        should_probe[i] = false;
    }
    elems = 0;
}

template <class K, class V>
DHHashTable<K, V>::~DHHashTable()
{
    destroy();
}

template <class K, class V>
DHHashTable<K, V> const& DHHashTable<K, V>::operator=(DHHashTable const& rhs)
{
    if (this != &rhs) {
        destroy();

        copy(rhs);
    }
    return *this;
}

template <class K, class V>
DHHashTable<K, V>::DHHashTable(DHHashTable<K, V> const& other)
{
    copy(other);
}


template <class K, class V>
void DHHashTable<K, V>::destroy()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table; table = nullptr;
    delete[] should_probe; should_probe = nullptr;
}

template <class K, class V>
void DHHashTable<K, V>::copy(const DHHashTable<K, V>& other)
{
    table = new std::pair<K, V>*[other.size];
    should_probe = new bool[other.size];
    for (size_t i = 0; i < other.size; i++) {
        should_probe[i] = other.should_probe[i];
        if (other.table[i] == NULL)
            table[i] = NULL;
        else
            table[i] = new std::pair<K, V>(*(other.table[i]));
    }
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void DHHashTable<K, V>::insert(K const& key, V const& value)
{

    /**
     * @todo Implement this function.
     *
     * @note Remember to resize the table when necessary (load factor >=
     *  0.7). **Do this check *after* increasing elems!!** Also, don't
     *  forget to mark the cell for probing with should_probe!
     */

    //(void) key;   // prevent warnings... When you implement this function, remove this line.
    //(void) value; // prevent warnings... When you implement this function, remove this line.
    elems++;
    if(shouldResize()) resizeTable();
    size_t index = hashes::hash(key,size);
    bool flag = false;
    int cot = 0;
    while(!flag){
      if(should_probe[index]==false){
        std::pair<K,V> * insertion  = new std::pair<K,V>(key,value);
        table[index]= insertion;
        should_probe[index] = true;
        flag = true;
      }
      else{
        cot++;
        index = (index + cot*hashes::secondary_hash(key,size))%size;
      }
    }
}

template <class K, class V>
void DHHashTable<K, V>::remove(K const& key)
{
    /**
     * @todo Implement this function
     */
     int index = findIndex(key);
     if(index != -1){
       delete table[index];
       table[index] = NULL;
       should_probe[index] = false;
       elems--;
     }
}

template <class K, class V>
int DHHashTable<K, V>::findIndex(const K& key) const
{
  int odx = hashes::hash(key,size);
  int idx = hashes::hash(key,size);

  // if(table[idx]!= NULL && table[idx]->first == key)
  // return odx;
  int count = 0;
  while(true){
    if(table[idx]!= NULL && table[idx]->first == key){
      return idx;
    }
    else{
      count++;
      idx = (odx + count*hashes::secondary_hash(key,size))%size;
      if(idx == odx) break;
    }
  }
  return -1;
    /**
     * @todo Implement this function
     */
    //  size_t org_index = hashes::hash(key,size);
    //  size_t index = org_index;
    //
    //  if(table[org_index] != NULL && table[org_index]->first == key)
    //   return org_index;
    //  else index = (index + hashes::secondary_hash(key,size))%size;
    //
    //  int cot = 1;
    //  while(true){
    //    if(table[index] != NULL && table[index]->first == key){
    //      return index;
    //    }
    //    else{
    //       cot++;
    //       index = (index + cot*hashes::secondary_hash(key,size))%size;
    //       if(index == org_index) break;
    //    }
    //  }
    // return -1;
}

template <class K, class V>
V DHHashTable<K, V>::find(K const& key) const
{
    int idx = findIndex(key);
    if (idx != -1)
        return table[idx]->second;
    return V();
}

template <class K, class V>
V& DHHashTable<K, V>::operator[](K const& key)
{
    // First, attempt to find the key and return its value by reference
    int idx = findIndex(key);
    if (idx == -1) {
        // otherwise, insert the default value and return it
        insert(key, V());
        idx = findIndex(key);
    }
    return table[idx]->second;
}

template <class K, class V>
bool DHHashTable<K, V>::keyExists(K const& key) const
{
    return findIndex(key) != -1;
}

template <class K, class V>
void DHHashTable<K, V>::clear()
{
    destroy();

    table = new std::pair<K, V>*[17];
    should_probe = new bool[17];
    for (size_t i = 0; i < 17; i++)
        should_probe[i] = false;
    size = 17;
    elems = 0;
}

template <class K, class V>
void DHHashTable<K, V>::resizeTable()
{
    size_t newSize = findPrime(size * 2);
    std::pair<K, V>** temp = new std::pair<K, V>*[newSize];
    delete[] should_probe;
    should_probe = new bool[newSize];
    for (size_t i = 0; i < newSize; i++) {
        temp[i] = NULL;
        should_probe[i] = false;
    }

    for (size_t slot = 0; slot < size; slot++) {
        if (table[slot] != NULL) {
            size_t h = hashes::hash(table[slot]->first, newSize);
            size_t jump = hashes::secondary_hash(table[slot]->first, newSize);
            size_t i = 0;
            size_t idx = h;
            while (temp[idx] != NULL)
            {
                ++i;
                idx = (h + jump*i) % newSize;
            }
            temp[idx] = table[slot];
            should_probe[idx] = true;
        }
    }

    delete[] table;
    // don't delete elements since we just moved their pointers around
    table = temp;
    size = newSize;
}
