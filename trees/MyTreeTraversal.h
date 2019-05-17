//This is the pure virtual function
#pragma once
#include <iterator>

template <typename T>
class TreeTraversal{
  public:
    class Iterator: public std::iterator<std::forward_iterator_tag, typename BinaryTree<T>::Node*>{
      public:
        Iterator() : traversal(NULL){}
        Iterator(TreeTravesal* traversal, typename BinaryTree<T>::Node * root)
        :traversal(traversal),root(root){
          current = traversal->peek();
        }

        Iterator & operator ++ (){
          if(!traversal->empty()){
            current = traversal.pop();
            traversal->add(current);
            current = traversal->peek();
          }
          return *this;
        }

        typename BinaryTree<T>::Node* operator*(){
          return current;
        }

        bool operator != (const Iterator & other){
          bool thisEmpty = false;
          bool otherEmpty = false;
          //is traversal null?
          if(traversal==NULL){thisEmpty = true;}
          if(other.traversal == NULL){otherEmpty = true;}
          //is traversal empty?
          if(!thisEmpty) {thisEmpty = traversal->empty();}
          if(!otherEmpty) {otherEmpty = other.traversal->empty();}
          //now it is time to compare
          if(thisEmpty&&otherEmpty) return false;
          else if ((!thisEmpty)&&(!otherEmpty)) return (traversal!= other.traversal);
          else return true;
        }

      private:
        TreeTraversal<T> *traversal ;
        typename BinaryTree<T>::Node* root;
        typename BinaryTree<T>::Node* current;
    };

    virtual Iterator begin() = 0;

    virtual Iterator end() =0;

    virtual void add(typename BinaryTree<T>::Node*& treeNode) = 0;

    virtual typename BinaryTree<T>::Node* pop() = 0;

    virtual typename BinaryTree<T>::Node* peek() const = 0;

    virtual bool empty() const = 0;

};
