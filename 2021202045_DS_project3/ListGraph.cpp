#include "ListGraph.h"

ListGraph::ListGraph(bool type, int size) : Graph(type, size) //constructor of ListGraph
{
	m_Type = type;
	m_List = new map<int, int>[size];
	
}

ListGraph::~ListGraph()  //destructor of ListGraph
{
	//cout << "delete_L" << endl;
	delete[] m_List;   //delete allocated memory
}

void ListGraph::getAdjacentEdges_UD(int vertex, map<int, int>* m)   //get adjacent edge of undirected graph
{
	
	for (int i = 0; i < m_Size; i++)
	{
		if (i == vertex) {   //vertex(i) -> another vertex is exit
			for (auto it_ = m_List[i].begin(); it_ != m_List[i].end(); it_++)
			{
				auto iter = m_List[it_->first].find(i);
				if (iter != m_List[it_->first].end())
				{
					if (it_->second < iter->second)
					{
						m->insert(pair<int, int>(it_->first, it_->second ));
					}
				}
				else
				{
					m->insert(pair<int, int>(it_->first, it_->second));
				}

			}
		}
	}

	for (int i = 0; i < m_Size; i++)
	{
		for (auto it_ = m_List[i].begin(); it_ != m_List[i].end(); it_++)
		{
			if (it_->first == vertex) {  //vertex(i) <- another vertex is exit
				auto iter = m_List[it_->first].find(i);
				if (iter != m_List[it_->first].end())
				{
					if (it_->second < iter->second)
					{
						m->insert(pair<int, int>(i, it_->second));
					}
				}
				else
				{
					m->insert(pair<int, int>(i, it_->second));
				}

			}
		}
	}

}
void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m)  //get adjacent edge of directed graph
{

	for (int i = 0; i < m_Size; i++)
	{
		if (i == vertex) {                                    //vertex(i) -> another vertex is exit
			for (auto it_ = m_List[i].begin(); it_ != m_List[i].end(); it_++)
			{
				m->insert(pair<int, int>(it_->first, it_->second));
			}
		}
	}

}

void ListGraph::insertEdge(int from, int to, int weight)   //insert edge in list
{
	
	for (int i = 0; i < m_Size; i++)
	{
		if (i == from) {
			m_List[i].insert(pair<int,int>(to, weight));      //m_List insert
		}

	}
}
bool ListGraph::ifVertexin(int vertex)   //if vertex is in graph
{

	if (vertex > m_Size) { //if vertex > m_Size
		return 0;
	}
	return 1;   //vertex is not in
}

bool ListGraph::printGraph()   //print graph
{

	flog2 << "===========PRINT==========" << endl;

	for (int i = 0; i < m_Size; i++)   //traversal of all rows of list
	{
		flog2 << "[" << i << "]";

		for (auto it_ = m_List[i].begin(); it_ != m_List[i].end() && flog2 << " -> "; it_++) //traversal a line of list
		{
			flog2 << "(" << it_->first << "," << it_->second << ")";
		}
		flog2 << endl;
	}
	flog2 << endl;
	return 1;
}