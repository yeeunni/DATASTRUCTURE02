#pragma once
#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Graph.h"

class MatrixGraph : public Graph {
private:
	int** m_Mat;  // int array m_Mat of 2 degree
public:
	MatrixGraph(bool type, int size);
	~MatrixGraph();
	bool ifVertexin(int vertex); //if vertex in graph
	void getAdjacentEdges(int vertex, map<int, int>* m); //get adjacent edge of directed graph
	void getAdjacentEdges_UD(int vertex, map<int, int>* m); //get adjacent edge of undirected graph
	void insertEdge(int from, int to, int weight); //insert edge in Matrix
	bool printGraph(); //print graph
};

#endif