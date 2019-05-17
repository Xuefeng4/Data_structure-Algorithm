#include <iostream>
#include <string>

#include "adjacency_matrix.h"

using namespace std;

/*
 Implement the functions below
 */

bool containsEdge(Graph const * const g, int src, int dest) {
    return g->adjMatrix[src][dest];
}

void addEdge(Graph* g, int src, int dest) {
  g->adjMatrix[src][dest]=true;
}

int numOutgoingEdges(Graph const * const g, int v) {
  int j=0;
  for (unsigned i=0; i<g->n; i++)
  {
    if (g->adjMatrix[v][i]) j++;
  }
  return j;
}


int numIncomingEdges(Graph const * const g, int v) {
  int j=0;
  for (unsigned i=0; i<g->n; i++)
  {
    if (g->adjMatrix[i][v]) j++;
  }
  return j;
}

void printGraph(Graph const * const g) {
        cout << "Adjacency Matrix: " << endl;
        for (int i = 0; i < g->n; i += 1) {
                for (int j = 0; j < g->n; j += 1) {
                        bool neighbor = g->adjMatrix[i][j];
                        cout << neighbor << " ";
                }
                cout << "\n\n";
        }
}

Graph* createVertices(int numV) {
    // No need to modify this function
    Graph* g = new Graph();
    g->n = numV;
    g->adjMatrix = new bool*[numV];
    for (int i = 0; i < numV; i += 1) {
        g->adjMatrix[i] = new bool[numV];
        for (int j = 0; j < numV; j += 1) {
            g->adjMatrix[i][j] = 0;
        }
    }
    return g;
}
