#pragma once
#include "HeaderTable.h"
#include <fstream>
#ifndef _ios
#define _ios
#include <iostream>
#endif
#include <vector>
#include <set>

class FPGrowth
{
private:
	int threshold;     //threshold value
	int check;       //value whether fptree is eixst
	int check_pattern; //value pattern is exist
	FPNode* fpTree;
	HeaderTable* table;
	map<set<string>, int> frequenctPatterns; //store all frequentpatterns of powerSet
	ofstream* fout;
	ofstream flog;
	ofstream result;
	ofstream* result1;
public:
	FPGrowth(ofstream* fout, ofstream* result1,int threshold = 3) { //contructor
		this->threshold = threshold;       //set threshold
		result.open("result.txt", ios::app); //ofstream result.open
		result.setf(ios::fixed);
		fpTree = new FPNode;  //allocate
		table = new HeaderTable; //allocate
		this->fout = fout;  //set fout
		this->result1 = result1;
		check = 0;  //initialize
		check_pattern = 0; //initialize
	}
	~FPGrowth();
	void createTable(char* item, int frequency) { table->insertTable(item, frequency); } //createTable
	void createFPtree(FPNode* root, HeaderTable* table, set<string> item_array, int frequency); //createFPtree
	void connectNode(HeaderTable* table, string item, FPNode* node); //connect table and fpnodes/ fpnodes and fpnodes
	bool isexist(); //if fptree is exist
	int get_check_pattern(){ return check_pattern; } //get check_pattern

	void frequenctPatternSetting() { //save frequentpatterns and print to result.txt
		table->ascendingIndexTable();  //table sorting to frequenctPatterns function's parameter
		frequenctPatterns = getFrequentPatterns(table, fpTree);
	}

	map<set<string>, int> getFrequentPatterns(HeaderTable* pTable, FPNode* pTree); //save frequentpatterns and print to result.txt
	void powerSet(map<set<string>, int>* FrequentPattern, vector<string> data, string item, int frequency, int* flag, int depth); //find partial set of powerSet
	
	int item_frequency(string item) { return table->find_frequency(item); } //find item's frequency
	FPNode* getTree() { return fpTree; }
	HeaderTable* getHeaderTable() { return table; }

	bool printList(); //print indextable list
	bool printTree(); //print fptree


};


