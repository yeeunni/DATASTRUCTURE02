#ifndef _GRAPHMETHOD_H_
#define _GRAPHMETHOD_H_

#include "ListGraph.h"
#include "MatrixGraph.h"

/*functions of each type of graph search*/
bool BFS(Graph* graph, int vertex);
bool DFS(Graph* graph, int vertex);
bool DFS_R(Graph* graph, bool* visit, int vertex,int count,queue<int>* stk);
bool Kruskal(Graph* graph);
bool Dijkstra(Graph* graph, int vertex);
bool Bellmanford(Graph* graph, int s_vertex, int e_vertex);
bool FLOYD(Graph* graph);

/*function about sorting and union, find*/
int Find(int parent[],int vertex);
void Union(int parent[],int vertex1, int vertex2);
void insertionSort(int* a, const int n1, const int n2);
void insert(int* a, const int& e, int i);
void quickSort(int* arr, int left, int right);
#endif
