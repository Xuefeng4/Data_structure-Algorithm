/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subR  // Base case - null nodeoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    mirror(root);
}

template<typename T>
void BinaryTree<T>::mirror(Node * subRoot){
  if (subRoot == NULL) return;
  mirror(subRoot->left);
  mirror(subRoot->right);

  Node* tmp = subRoot->left;
  subRoot->left = subRoot->right;
  subRoot->right = tmp;
}

/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    bool rtu = false;

    InorderTraversal<T> iot(root);

    typename TreeTraversal<T>::Iterator it = iot.begin();
    T tmp = (*it)->elem;
    ++it;
    for (;it != iot.end(); ++it) {
      if ((*it)->elem  < tmp){ return false;  }
      tmp = (*it)->elem;
    }
  return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
  InorderTraversal<int> iot(root);
  //TreeTraversal<int>::Iterator i = iot.begin();
  //T min = (*i)->elem, max = (*i)->elem; //?????
  for (TreeTraversal<int>::Iterator it = iot.begin(); it != iot.end(); ++it) {
    if(min > (*it)->elem){
      min = (*it)->elem;
    }
    if(max < (*it)->elem){
      max = (*it)->elem;
    }
  }
  return isOrderedRecursiveHelper(root,min,max);
}

template <typename T>
bool BinaryTree<T>::isOrderedRecursiveHelper(Node* node, T low, T high) const{
    if(node -> elem  < low || node -> elem > high){

      return false;
    }

    bool left = true, right = true;
    if(node -> left != NULL)
      left = isOrderedRecursiveHelper(node->left, low, node->elem);
    if(node -> right!= NULL)
      right = isOrderedRecursiveHelper(node->right, node->elem,high);

  return left && right;

}


/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::getPaths(std::vector<std::vector<T>>& paths) const
{
  if(!root) return;
  std::vector<T> cur;
  cur.push_back(root->elem);
  binaryTreePaths(paths, root, cur);

}
template <typename T>
void BinaryTree<T>::binaryTreePaths(std::vector<std::vector<T>>& paths, Node* root, std::vector<T> cur)const {
    if(!root->left && !root->right)
        paths.push_back(cur);
        return;
    }

    if(root->left) {
      cur.push_back(root->left->elem);
      binaryTreePaths(paths, root->left, cur);
      cur.pop_back();
    }
    if(root->right) {
      cur.push_back(root->right->elem);
      binaryTreePaths(paths, root->right, cur);
      cur.pop_back();
  }
}


/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    int ret =  binaryTreePathsSum(root, 0);
    return ret;
}
<<<<<<< HEAD
=======
template <typename T>
int  BinaryTree<T>::binaryTreePathsSum(Node* root, int len)const {
    if(!root->left && !root->right) {
        return len;
    }

    int left = 0, right = 0;
    if(root->left) {
      left = binaryTreePathsSum(root->left, len+1);
    }
    if(root->right) {
      right = binaryTreePathsSum(root->right, len +1);
    }

    return left + right + len;
  }
>>>>>>> 19a95b4f1e31cc612973e32b2276d62ecd9faae0
