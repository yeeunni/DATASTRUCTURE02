#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "GraphMethod.h"

class Manager {
private:
	Graph* graph;
	ofstream fout;
	int load;

public:
	Manager();
	~Manager();
	//read command.txt
	void run(const char* command_txt);
	//read txt->graph load
	bool LOAD(string filename);
	bool PRINT(); //print the graph

	/*operation of graph calculation*/
	bool mBFS(int vertex);
	bool mDFS_R(int vertex);
	bool mDFS(int vertex);
	bool mDIJKSTRA(int vertex);
	bool mKRUSKAL();
	bool mBELLMANFORD(int s_vertex, int e_vertex);
	bool mFLOYD();
	
	//print error code according to type
	void printErrorCode(int n);
};

#endif