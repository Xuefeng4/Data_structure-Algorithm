#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>

/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::numVertices() const {
  // TODO: Part 2
  return vertexMap.size();
}


/**
* The degree of the vertex. For directed: Sum of in-degree and out-degree
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  // TODO: Part 2
  //if(adjList.find(v.key()) == adjList.end()) return -1;
  return adjList.at(v.key()).size();
}


/**
* Inserts a Vertex into the Graph.
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  // TODO: Part 2
  //if(vertexMap.find(key) != vertexMap.end()) return vertexMap.at(key);
  V & v = *(new V(key));
  vertexMap.insert({key,v});
  std::list<edgeListIter> a;
  adjList.insert({key,a});
  return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  // TODO: Part 2
  //if(vertexMap.find(key) == vertexMap.end()) return;
  std::list<edgeListIter> abandon;
  for(auto it = edgeList.begin(); it!= edgeList.end(); it++){
    if((*it).get().source().key()==key||(*it).get().dest().key()==key){
      abandon.push_back(it);
    }
  }
  for(auto i: abandon){
    removeEdge(i);
  }
  vertexMap.erase(key);
}


/**
* Inserts an Edge into the Graph.
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  E & e = *(new E(v1, v2));
  //lack of check if exists?
  edgeList.push_front(e);
  adjList.at(v1.key()).push_front(edgeList.begin());
  adjList.at(v2.key()).push_front(edgeList.begin());
  return e;
}


/**
* Removes an Edge from the Graph. Consider both the undirected and directed cases.
* min(degree(key1), degree(key2))
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {
  // TODO: Part 2
  for(auto it = edgeList.begin(); it!=edgeList.end(); it++){
    E & target = (*it).get();
    if(target.directed()){
      if(target.source().key() == key1 && target.dest().key() == key2){
        adjList.at(key1).remove(it);
        adjList.at(key2).remove(it);
        edgeList.erase(it);
        break;
      }
    }else{
      if(target.source().key() == key1 && target.dest().key() == key2){
        adjList.at(key1).remove(it);
        adjList.at(key2).remove(it);
        edgeList.erase(it);
        break;
      }
      else if(target.source().key() == key2 && target.dest().key() == key1){
        adjList.at(key1).remove(it);
        adjList.at(key2).remove(it);
        edgeList.erase(it);
        break;
      }
    }
  }
}



/**
* Removes an Edge from the Graph given by the location of the given iterator into the edge list.
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // TODO: Part 2
  adjList.at((*it).get().source().key()).remove(it);
  adjList.at((*it).get().dest().key()).remove(it);
  edgeList.erase(it);
}


/**
* Return the list of incident edges from a given vertex.
* For the directed case, consider all edges that has the vertex as either a source or destination.
* @param key The key of the given vertex
* @return The list edges (by reference) that are adjacent to the given vertex
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
  std::list<std::reference_wrapper<E>> edges;
  for(auto it = adjList.at(key).begin(); it !=adjList.at(key).end(); it++){
    edges.push_back(*(*it));
  }
  return edges;
}


/**
* Return whether the two vertices are adjacent to one another. Consider both the undirected and directed cases.
* When the graph is directed, v1 and v2 are only adjacent if there is an edge from v1 to v2.
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  // TODO: Part 2
  for(auto it : adjList.at(key1)){
    E & target = (*it).get();
    if(target.directed()){
      if(target.source().key() == key1 && target.dest().key() == key2)
        return true;
    }else{
      if(target.source().key() == key1 && target.dest().key() == key2)
        return true;
      if(target.source().key() == key2 && target.dest().key() == key1)
        return true;
    }
  }
  return false;
}
