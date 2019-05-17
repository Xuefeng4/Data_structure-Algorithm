/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>
using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */

     if(first[curDim]<second[curDim])
     return true;
     if(first[curDim]>second[curDim])
     return false;
     if(first<second) return true;
     else return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */

    double currDist = distance(target, currentBest);
    double potenDist = distance(target, potential);
    if(currDist<potenDist) return false;
    else if(currDist>potenDist) return true;
    else{
      if(potential < currentBest) return true;
      else return false;
    }
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     if(newPoints.empty()){
       root = NULL;
     }
     else{
       for(unsigned i = 0; i<newPoints.size();i++){
         nodeList.push_back(newPoints[i]);
         //std::cout<<newPoints[i]<<std::endl;
       }
       int left = 0;
       int right = newPoints.size()-1;
       root = sortDim(0, left, right);
     }
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::sortDim(int curDim, int left, int right)
{    //std::cout<<"qS0"<<left <<" "<< right<<std::endl;
    if(left > right) return NULL;
       // std::cout<<"nodeList[index]"<<left <<
       // " "<< right<<std::endl;
    int key = (left+right)/2;
    int index = quickSelect(curDim,left,right,key);
    //std::cout<<nodeList[index]<<std::endl;
    KDTreeNode * node = new KDTreeNode(nodeList[index]);

    node->left = sortDim((curDim+1)%Dim, left, index-1);
    node->right = sortDim((curDim+1)%Dim, index+1, right);

    return node;
}

template <int Dim>
int KDTree<Dim>::quickSelect(int curDim,int left, int right, int key)
{   // std::cout<<"qS"<<left <<" "<< right<<" "<<key<<std::endl;
    int median = _partition(curDim,left,right);
    if(median < key)
      return quickSelect(curDim,median+1,right,key);
    else if(median > key)
      return quickSelect(curDim,left,median-1,key);
    else return median;
}

template <int Dim>
int KDTree<Dim>::_partition(int curDim, int left, int right)
{
    Point<Dim> pivot = nodeList[right];
  int j = left;
  for(int i = left; i < right; i++){
    if(smallerDimVal(nodeList[i],pivot,curDim)){
      swap(nodeList[i],nodeList[j]);
      j++;
    }
  }
  swap(nodeList[j],nodeList[right]);
  return j;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::_copy(const KDTreeNode * otherNode){
  if(otherNode == NULL) return NULL;
  KDTreeNode * thisNode = new KDTreeNode(otherNode->point);
  thisNode->left = _copy(otherNode->left);
  thisNode->right = _copy(otherNode->right);
  return thisNode;
}

template <int Dim>
void KDTree<Dim>::_destory(const KDTreeNode * node){
  if(node == NULL) return;
  _destory(node->left);
  _destory(node->right);
  delete node;
}


template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
   this->root = _copy(other.root);
}


template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
   if(this != &rhs){
     _destory(root);
     root = _copy(rhs.root);
   }
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   _destory(root);
   root = NULL;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    Point<Dim>* curBest = NULL;
    findTarget(query,root,0,curBest);

    return *curBest;
}




template <int Dim>
void KDTree<Dim>::findTarget(const Point<Dim>& query, KDTreeNode * node, int curDim, Point<Dim> *& curBest) const
{
  //std::cout<<"enter:"<<node->point<<std::endl;
  if(node->left==NULL && node->right == NULL){
    if(curBest == NULL){
      curBest = &(node->point);
    }else {
      if(shouldReplace(query,*curBest,node->point))
        curBest = &(node->point);
    }
    return;
  }
  //std::cout<<"enter0:"<<node->point<<std::endl;
  if(smallerDimVal(query,node->point,curDim)){
      //std::cout<<"enter1:"<<node->point<<std::endl;
    if(node->left  == NULL){
      if(curBest == NULL){
        curBest = &(node->point);
      } else{
        if(shouldReplace(query,*curBest,node->point))
          curBest = &(node->point);
      }
      findTarget(query,node->right,(curDim+1)%Dim,curBest);
      return;
    } else {
      //std::cout<<"enter4:"<<node->left<<std::endl;
        findTarget(query,node->left,(curDim+1)%Dim,curBest);
    }
    //std::cout<<"back1:"<<node->point<<std::endl;
    //traversal back;
    if(shouldReplace(query,*curBest,node->point)){
      curBest = &node->point;
    }

    double radiusSquared = distance((*curBest), query);
    double planeDistanceSquared = pow((query[curDim] - node->point[curDim]),2);

    if(planeDistanceSquared <= radiusSquared){
      if (node -> right != NULL)
        findTarget(query,node->right,(curDim+1)%Dim,curBest);
      }
    //std::cout<<"end"<<std::endl;
  } else{
      //std::cout<<"enter2:"<<node->point<<std::endl;
      if(node->right  == NULL){
        if(curBest == NULL){
          curBest = &(node->point);
        }else{
          if(shouldReplace(query,*curBest,node->point))
            curBest = &(node->point);
        }
        findTarget(query,node->left,(curDim+1)%Dim,curBest);
        return;
      } else {
        //std::cout<<"enter4:"<<node->left<<std::endl;
        findTarget(query,node->right,(curDim+1)%Dim,curBest);
      }
    //std::cout<<"back2:"<<node-> point<<std::endl;
    if(shouldReplace(query,*curBest,node->point)){
      curBest = &(node->point);
    }

    double radiusSquared = distance((*curBest), query);
    double planeDistanceSquared = pow((query[curDim] - node->point[curDim]),2);
    //std::cout<<"go?"<<std::endl;
    if(planeDistanceSquared <= radiusSquared){
      if (node -> left != NULL){
        //std::cout<<node->point << node->left->point<<std::endl;
        findTarget(query,node->left,(curDim+1)%Dim,curBest);
      }
    }
  }
}

template <int Dim>
double KDTree<Dim>::distance(const Point<Dim>& first, const Point<Dim>& second) const
{
    double dis = 0;
    for (int i = 0; i < Dim; i++) {
        dis += pow((first[i] - second[i]),2);
    }
    return dis;
}
