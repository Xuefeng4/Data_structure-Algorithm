/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node * tmp = t->right;
    t->right = tmp->left;
    tmp->left = t;
    t = tmp;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * tmp = t->left;
    t->left = tmp->right;
    tmp->right = t;
    t = tmp;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    int b = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    if(b==2){
      int sub = heightOrNeg1(subtree->right->right)- heightOrNeg1(subtree->right->left);
      if(sub==1) {
        rotateLeft(subtree);
      }
      else{
        rotateRightLeft(subtree);
      }
    }
    else if (b==-2){
      int sub  = heightOrNeg1(subtree->left->right)- heightOrNeg1(subtree->left->left);
      if(sub==-1){
        rotateRight(subtree);
      }
      else{
        rotateLeftRight(subtree);
      }
    }
    updateHeight(subtree);
}

template <class K, class V>
void AVLTree<K, V>::updateHeight(Node*& subtree){
  // if (subtree == NULL) return -1;
  // subtree->height = 1 + std::max(subtree->left->,updateHeight(subtree)->right);
  // return subtree->height;
  if (subtree==NULL) return;
  updateHeight(subtree->left);
  updateHeight(subtree->right);
  subtree->height = 1 + std::max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right));
}


template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL){
      subtree = new Node(key,value);
    }
    else if (key<subtree->key) insert(subtree->left,key,value);
    else if (key>subtree->key) insert(subtree->right,key,value);
    rebalance(subtree);
    //std::cout<<"a"<<std::endl;

}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);

    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;

        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node *tmp = subtree->left;
            while (tmp->right!=NULL){
              tmp = tmp->right;
            }
            swap(subtree, tmp);
            // delete tmp;
            // tmp = NULL;
            remove(subtree->left, key);

        } else {
            /* one-child remove */
            // your code here
            if(subtree->left!= NULL){
              Node * tmp = subtree->left;
              //subtree = subtree->left;
              delete subtree;
              subtree = tmp;
            }
            else{
              Node * tmp = subtree->right;
              //subtree = subtree->right;
              delete subtree;
              subtree = tmp;
            }
        }
        // your code here
    }
    if(subtree)
    rebalance(subtree);
}
