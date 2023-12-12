#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <cstring>
#include <string.h>
#include <fstream>
#include <map>
#include <set>
#include <math.h>
#include <vector>
#include <algorithm>
#include <deque>
#include <queue>
#include <stack>

using namespace std;

#define MAX 999999     

class Graph {
protected:
	bool m_Type;//0:List 1:Matrix
	int m_Size =0;  //initialize size
	ofstream flog2;  //ofstream
	
public:
	Graph(bool type, int size); 
	virtual ~Graph();

	bool getType();
	int getSize();
	/*virtual functions*/
	virtual void getAdjacentEdges_UD(int vertex, map<int, int>* m) = 0;
	virtual void getAdjacentEdges(int vertex, map<int, int>* m) = 0;
	virtual void insertEdge(int from, int to, int weight) = 0;
	virtual bool ifVertexin(int vertex)=0;
	virtual	bool printGraph() = 0;
};

#endif