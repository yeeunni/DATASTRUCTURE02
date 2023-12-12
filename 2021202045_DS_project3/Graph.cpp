#include "Graph.h"

Graph::Graph(bool type, int size)         //constructor of Graph
{
	m_Type = type;    //initialize type
	m_Size = size;      //initialize size
	flog2.open("log.txt", ios::app);   //define ofstream
}

Graph::~Graph()   //destructor of Graph
{
}

//functions of getting values
bool Graph::getType() { return m_Type; }
int Graph::getSize() { return m_Size; }