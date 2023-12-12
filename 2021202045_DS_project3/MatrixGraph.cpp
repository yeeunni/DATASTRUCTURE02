#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(bool type, int size) : Graph(type, size) //constructor of MatrixGraph
{
	
	m_Mat = new int* [size]; //m_Mat is int array of 2 degree
	for (int i = 0; i < size; i++)
	{
		m_Mat[i] = new int[size];
		memset(m_Mat[i], 0, sizeof(int) * size); //initialize all componenet -> 0
	}
}

MatrixGraph::~MatrixGraph() //destructor of MatrixGraph
{
	//cout << "delete_M" << endl;
	//delete m_Mat
	for (int i = 0; i < getSize(); i++)
	{
		delete[] m_Mat[i]; 
	}
	delete[] m_Mat;
}

void MatrixGraph::getAdjacentEdges(int vertex, map<int, int>* m) //get adjacent edge of directed graph
{
	for (int i = 0; i < m_Size; i++)  //find location
	{
		if (i == vertex) {

			for (int j = 0; j < m_Size; j++)
			{
				if (m_Mat[i][j] != 0) { //if weight is not 0
					m->insert(pair<int, int>(j, m_Mat[i][j]));
				}
			}
		}
	}
	
}
bool MatrixGraph::ifVertexin(int vertex) //if vertex is in graph
{
	if (vertex > m_Size) { //if vertex > m_Size
		return 0;
	}
	return 1;
}
void MatrixGraph::getAdjacentEdges_UD(int vertex, map<int, int>* m) //get adjacent edge of undirected graph
{

	for (int i = 0; i < m_Size; i++)  //find location
	{
		if (i == vertex) {

			for (int j = 0; j < m_Size; j++)
			{
				if (m_Mat[i][j] != 0) {        // if not 0
					if(m_Mat[j][i] != 0) {     //if from->to && to->from
						int final_w = min(m_Mat[i][j], m_Mat[j][i]); //compare weight
						m->insert(pair<int, int>(j, final_w)); //insert smaller weight
					}
					else {
						m->insert(pair<int, int>(j, m_Mat[i][j]));  //else
					}
				}
			}
		}
	}
	for (int i = 0; i < m_Size; i++)  //find location
	{
		for (int j = 0; j < m_Size; j++)
		{
			if (j == vertex) {
				if (m_Mat[i][j] != 0) {  // if not 0
					if (m_Mat[j][i] != 0) {  //if from->to && to->from
						int final_w = min(m_Mat[i][j], m_Mat[j][i]);
						m->insert(pair<int, int>(i, final_w));  //insert smaller weight
					}
					else {
						m->insert(pair<int, int>(i, m_Mat[i][j]));
					}
				}
			}
		}

	}


}

void MatrixGraph::insertEdge(int from, int to, int weight) //insert edge in matrix
{
	int i = from;
	int j = to;
	m_Mat[i][j] = weight; //insert

}

bool MatrixGraph::printGraph()
{
	
	if (m_Size < 0) //if there is not graph
		return 0;

	flog2 << "===========PRINT==========" << endl;

	flog2 << '\t';
	for (int i = 0; i < m_Size; i++) //print row
	{
		flog2 << "[" << i << "]" << '\t';
	}
	flog2 << endl;

	for (int i = 0; i < m_Size; i++)  //print column
	{
		flog2 << "[" << i << "]";
		for (int j = 0; j < m_Size && flog2 << '\t'; j++)
		{
			flog2 << m_Mat[i][j];   //print matrix 
		}
		flog2 << endl;
	}
	return 1;
}