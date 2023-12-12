#pragma once
#include "FPNode.h"
#include <list>

class HeaderTable
{
private:
	list<pair<int, string> > indexTable;
	map<string, FPNode*> dataTable;
	int count; //value of table is empty or not
	FPNode* fpnode;
public:
	HeaderTable() { count = 0; } //constructor
	~HeaderTable();
	void insertTable(char* item, int frequency);  //create index and data Table
	list<pair<int, string>> getindexTable() { return indexTable; }
	void show_data();                                        //print dataTable
	map<string, FPNode*> getdataTable() { return dataTable; }
	FPNode* getNode(string item) { return dataTable.find(item)->second; }
	void descendingIndexTable() { indexTable.sort(greater<pair<int, string>>()); } //sort get smaller
	void ascendingIndexTable() { indexTable.sort(); } //sort get bigger
	int find_frequency(string item); 
	int get_count() { return count; } //if 0-> headerTable is empty
};

