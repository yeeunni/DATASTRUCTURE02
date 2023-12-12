#ifndef _LIST_H_
#define _LIST_H_

#include "Graph.h"

class ListGraph : public Graph {
private:
	map < int, int >* m_List;  //memory that stores graph in list
	

public:
	ListGraph(bool type, int size);
	~ListGraph();
	void getAdjacentEdges(int vertex, map<int, int>* m); //get adjacent edge of directed graph
	bool ifVertexin(int vertex);  //if vertex is in graph
	void getAdjacentEdges_UD(int vertex, map<int, int>* m); //get adjacent edge of undirected graph
	void insertEdge(int from, int to, int weight);   //insert edge in list
	bool printGraph(); //print
	map<int, int>* getGraph() { return m_List; } //get graph
};

#endif