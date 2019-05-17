/* Your code here! */
#include "dsets.h"

void DisjointSets::addelements(int num){
  for(int i = 0; i<num; i++){
    collection.push_back(-1);
  }
}

int DisjointSets::find(int elem){
  if(collection[elem]<0) return elem;
  else{
    int root = find(collection[elem]);
    collection[elem] = root;
    return root;
  }
}

void DisjointSets::setunion(int a, int b){
  int root1 = find(a);
  int root2 = find(b);
  //connect root2 to  root1's child;
  int newSize = collection[root1]+ collection[root2];
  if(collection[root1] <= collection[root2]){
    collection[root2] = root1;
    collection[root1] = newSize;
  }
  else{
    collection[root1] = root2;
    collection[root2] = newSize;
  }

}

int DisjointSets::size(int elem){
  int root = find(elem);
  return -(collection[root]);
}
