#pragma once
#include "../binarytree.h"
#include "TreeTravesal.h"
#include <iterator>
#include <stack>

template<typename T>
class InorderTraversal: public TreeTraversal<T>{
  public:
    InorderTraversal(BinaryTree<T>::Node* root)
    :current(root){
      while(!current){
        path.push(current);
        current = current->left;
      }
    }

  typename TreeTravesal<T>::Iterator begin(){
    return typename TreeTravesal<T>::Iterator(this,root);
  }

  void add(typename BinaryTree<T>::Node *& treeNode){
    treeNode = treeNode->right;
    while(!treeNode){
      path.push_back(treeNode);
      treeNode = treeNode->left;
    }
  }

  typename BinaryTree<T>::Node *pop(){
    typename BinaryTree<T>::Node * rtu = path.top();
    path.pop();
    return rtu;
  }

  typename BinaryTree<T>::Node *peek() const{
    return empty()? NULL:path.top();
  }

  bool empty() const{
    return path.empty();
  }

  private:
    std::stack<typename BinaryTree<T>::Node * > path;
    BinaryTree<T>::Node* current;
};
