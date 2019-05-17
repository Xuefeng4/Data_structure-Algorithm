#include <queue>
#include <algorithm>
#include <string>
#include <list>
#include <queue>
#include <vector>
/**
 * Returns an std::list of vertex keys that creates any shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * You should use undirected edges. Hint: There are no edge weights in the Graph.
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  // TODO: Part 3
  std::list<std::string> path;
  std::unordered_map<std::string, std::string> pathMap;
  std::queue<string> q;
  std::unordered_map<std::string, bool> visited;
  for(auto i:vertexMap){
    visited[i.first] = true;
  }

  q.push(start);
  visited[start] = false;
  pathMap[start] = " ";
  string tmp;
  while(!q.empty()){
    std::cout << q.front()<<std::endl;
    tmp = q.front();
    q.pop();
    std::list<std::reference_wrapper<E>> neg = incidentEdges(tmp);
    for(auto i : neg){
      Vertex target1 = i.get().source();
      Vertex target2 = i.get().dest();
      if(target1.key() != tmp && visited[target1.key()]){
        q.push(target1.key());
        pathMap[target1.key()] = tmp;
        visited[target1.key()] = false;
      }
      if(target2.key() != tmp && visited[target2.key()]){
        q.push(target2.key());
        pathMap[target2.key()] = tmp;
        visited[target2.key()] = false;
      }
    }
    if(tmp == end) break;
  }
  string back = end;

  while(back != start){
    path.push_front(back);
    back = pathMap[back];
  }
  path.push_front(start);
  return path;
}










//   std::list<std::string> path;
//   std::queue<string> q;
//   std::unordered_map<string,string> pathMap;
//   std::unordered_map<string,bool> visited;
//   for(auto it : vertexMap){
//     visited[it.first] = true;
//   }
//
//   q.push(start);
//   visited[start] = false;;
//   string tmp;
//   while(q.front() != end){
//     tmp = q.front();
//     //std::cout<<"tmp: "<<tmp<<std::endl;
//     q.pop();
//     std::list<std::reference_wrapper<E>> incident = incidentEdges(tmp);
//     for(auto it: incident){
//       string target1 = it.get().source().key();
//       string target2 = it.get().dest().key();
//       if(target1 != tmp && visited[target1]){
//         q.push(target1);
//         visited[target1] = false;
//         pathMap[target1] = tmp;
//         //std::cout<<"insert1: "<<target1<<std::endl;
//       }
//       if(target2 != tmp && visited[target2]){
//         q.push(target2);
//         visited[target2] = false;
//         pathMap[target2] = tmp;
//         //std::cout<<"insert2: "<<target2<<std::endl;
//       }
//     }
//   }
//
//   string back = q.front();
//   path.push_front(back);
//   while(pathMap.find(back) != pathMap.end()){
//     back = pathMap[back];
//     path.push_front(back);
//     //std::cout<<"path: "<<back<<std::endl;
//   }
//   return path;
// }
