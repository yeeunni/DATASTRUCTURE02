#include "Manager.h"
#include<sstream>
#include <iostream>
Manager::Manager()    //constructor of Mangaer
{
	graph = NULL;
	fout.open("log.txt", ios::app);
	load = 0;
}

Manager::~Manager()  //destructor of Manager
{
	if (load)
		delete graph;    //delete
	fout.close();
}

void Manager::run(const char* command_txt) {
	ifstream fin;
	fin.open(command_txt);
	string order;
	string cmd;
	if (!fin)     //if command_txt is not exit
	{
		fout << "[ERROR] command file open error!" << endl;
		return;
	}

	char* str = NULL;
	char* str2 = NULL;
	char buf[129] = { 0 };
	while (!fin.eof())
	{
		getline(fin, order);
		if (!order.compare(""))    //if read " "
			break;
		stringstream com(order);
		com >> cmd;
		if (cmd == "LOAD") {     //cmd =="LOAD"
			string txt;    //read txt
			com >> txt;
			if (LOAD(txt)) {
				load = 1;
				fout << "========LOAD========" << endl;
				fout << "Success" << endl;
				fout << "====================" << endl;
			}
			else {
				printErrorCode(100);              //error code
			}
		}
		else if (cmd == "PRINT") {   //cmd == "PRINT"
			if (PRINT()) {
				fout << "=============" << endl;
			}
		}
		else if (cmd == "BFS") { //cmd == "BFS"
			int start_vertex=-1;
			com >> start_vertex;
			
			if (start_vertex== -1 || load==0) { //if no parameter and can't start operation
				printErrorCode(300);
			}
			else {
				if (mBFS(start_vertex)) {
					fout << "=============" << endl;
				}
				else {
					printErrorCode(300);
				}
			}
		}
		else if (cmd == "DFS") { //cmd == "DFS"
			int start_vertex = -1;
			com >> start_vertex;
			if (start_vertex == -1 || load == 0) { //if no parameter and can't start operation
				printErrorCode(400);
			}
			else {
				
				if (mDFS(start_vertex)) {
					fout << "=============" << endl;
				}
				else {
					printErrorCode(400);
				}
			}
		}
		else if (cmd == "DFS_R") {  //cmd == "DFS_R"
			int start_vertex = -1;
			com >> start_vertex;
			if (start_vertex == -1 || load == 0) {  //if no parameter and can't start operation
				printErrorCode(500);
			}
			else {
				
				if (mDFS_R(start_vertex)) {
					fout << endl;
					fout << "=============" << endl;
				}
				else {
					printErrorCode(500);
				}
			}
		}
		else if (cmd == "KRUSKAL") {    //cmd == "KRUSKAL"

			if (mKRUSKAL()) {
				fout << "===============" << endl;
			}
			else {
				printErrorCode(600);
			}
		}
		else if (cmd == "DIJKSTRA") {   //cmd == "DIJKSTRA"
			int start_vertex = -1;
			com >> start_vertex;
			if (start_vertex == -1 || load == 0) { //if no parameter and can't start operation
				printErrorCode(700);
			}
			else {
				
				if (mDIJKSTRA(start_vertex)) {
					fout << "=================" << endl;
				}
				else {
					printErrorCode(700);

				}
			}
		}
		else if (cmd == "BELLMANFORD") {   //cmd == "BELLMANFORD"
			int start_vertex=-1;
			int end_vertex=-1;
			com >> start_vertex;
			com >> end_vertex;
			if (start_vertex == -1 || end_vertex == -1|| load==0) { //if no parameter and can't start operation
				printErrorCode(800);
			}
			else {
				if (mBELLMANFORD(start_vertex, end_vertex)) {
					fout << "=====================" << endl;
				}
				else {
					printErrorCode(800);
				}
			}
		}
		else if (cmd == "FLOYD") {    //cmd == "FLOYD"

			if (mFLOYD()) {
				fout << "=================" << endl;
			}
			else {
				printErrorCode(900);   //error code
			}
		}
		else if (cmd == "EXIT") {

			break;
		}
	}
	fin.close();
}

bool Manager::LOAD(string filename)
{
	if (load == 1) {                      //if graph is already in 
		delete graph;
	}
	ifstream g_txt;
	string g_type;
	int size;
	int count = 0;
	string line;
	int start_vertex=0;
	int to_vertex;
	int vertex;
	int weight;
	g_txt.open(filename, ios::in);
	if (!g_txt.is_open()) {  //can't open file
		printErrorCode(100);
		return 0;
	}
	else {
		int check = 0;
		while (!g_txt.eof()) {
			getline(g_txt,line);
			if (!line.compare("")) {

				if (check == 0)     //graph is empty
				{
					return false;
				}
				break;
			}
			check = 1;
			if (count == 0) {
				g_type = line;    //update g_type
				count++;
			}
			else if (count == 1) {
				size = stoi(line);   //updatae size
				count ++;
				if (g_type == "L") {   //if g_type is L
					graph = new ListGraph(0, size);
				}
				else if (g_type == "M") { //if g_type is M
					graph = new MatrixGraph(1, size);
				}
			}
			
			else {
				if (g_type == "L") {
					char c_line[10000];
					strcpy(c_line, line.c_str());
					int num_para = 0;
					char* line_ptr = strtok(c_line, " ");
					while (line_ptr != NULL) {
						num_para++;

						if (num_para == 1) {           //if vertex is alone
							vertex = atoi(line_ptr);    //it is start vertex
						}
						else {                                //if num_para is not 1
							weight = atoi(line_ptr);       //it is weight
						}
						line_ptr = strtok(NULL, " ");
					}
					if (num_para == 1) {
						start_vertex = vertex;   //update start_vertex
					}
					else {
						to_vertex = vertex;  //update to_vertex
						
						graph->insertEdge(start_vertex, to_vertex, weight); //insert
					}
				}
				else if (g_type == "M") {
					to_vertex = 0;
					char c_line[10000];
					strcpy(c_line, line.c_str());
					char* line_ptr = strtok(c_line, " ");
					while (line_ptr != NULL) {
						weight = atoi(line_ptr);
						graph->insertEdge(start_vertex,to_vertex,weight); //insert
						to_vertex++;
						line_ptr = strtok(NULL, " ");
					}
					start_vertex++;
				}
		  }
		}
	}
}

bool Manager::PRINT()
{
	if (load == 0) { //if there is not graph
		printErrorCode(200);
	}
	else {
		if (graph->printGraph()) {
		return true;
	     }
	}
	return false;
}

bool Manager::mBFS(int vertex)
{
	if (graph->ifVertexin(vertex)) {  //if vertex is in graph
		if (BFS(graph, vertex)) {
			return true;
		}
	}
	return false;
}

bool Manager::mDFS(int vertex)
{
	if (graph->ifVertexin(vertex)) {  //if vertex is in graph
		if (DFS(graph, vertex)) {
			return true;
		}
	}
	return false;
}


bool Manager::mDFS_R(int vertex)
{
	int count=0;
	queue<int>stk;
	int size = graph->getSize();
	bool* visit = new bool[size];  
	fill(visit,visit+size,false);   //initailize
	if (graph->ifVertexin(vertex)) { //if vertex is in graph
		fout << "======DFS_R=======" << "\n";
		fout << "startvertex : " << vertex << endl;
		if (DFS_R(graph, visit, vertex, count, &stk)) {  //call recursive function
			delete[]visit;   //delete visit
			return true;
		}
	}
	delete[]visit;   //delete visit
	return false;
}

bool Manager::mDIJKSTRA(int vertex)
{
	if (graph->ifVertexin(vertex)){ //if vertex is in graph
		
		if (Dijkstra(graph, vertex))
		return true;
		else {
			return false;
		}
	}
	
	return false;
}

bool Manager::mKRUSKAL()
{
	if (load != 0) {  //if can do operation
		if (Kruskal(graph))
			return true;
	}
	return false;
}

bool Manager::mBELLMANFORD(int s_vertex, int e_vertex)
{
	if (load != 0) { //if can do operation
		if (graph->ifVertexin(s_vertex) && graph->ifVertexin(e_vertex)) {  //vertex is in graph

			if (Bellmanford(graph, s_vertex, e_vertex))
				return true;
			else {
				return false;
			}
		}
	}
	
	return false;
}

bool Manager::mFLOYD()
{

	if (load == 0) {  //can't do operation
		return false;
	}
	else {
		if (FLOYD(graph)) {
			return true;
		}
	}
	return false;
}

void Manager::printErrorCode(int n)  //error code
{
	fout << "======== ERROR ========" << endl;
	fout << n << endl;
	fout << "=======================" << endl;
}