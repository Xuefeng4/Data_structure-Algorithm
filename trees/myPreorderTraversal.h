#pragma once

#include "MyTreeTraversal.h"
#include "../BinaryTree.h "
#include <iterator>
#include <stack>

class PreorderTraversal: public TreeTravesal<T>{
  public:
  PreorderTraversal(typename BinaryTree<T>::Node * treeNode)
  :current(treeNode){
    path.push(current);
    }

  void add(typename BinaryTree<T>::Node * treenode){
    if(!treenode->right){
      path.push(treenode->right);
    }
    if(!treenode->left){
      path.push(treenode->left);
    }
  }

  typename BinaryTree<T>::Node * pop(){
    typename BinaryTree<T>::Node * tmp = path.top();
    path.pop();
    return tmp;
  }

  typename BinaryTree<T>::Node * peek const(){
    return empty()? NULL:path.top();
  }

  bool empty() const{
    return path.empty();
  }



  }
  }

  private:
    std::stack<typename BinaryTree<T>::Node *> path;
    typename BinaryTree<T>::Node * current;


}
