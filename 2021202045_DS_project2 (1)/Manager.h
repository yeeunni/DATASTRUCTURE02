#pragma once
#include "FPGrowth.h"
#include "BpTree.h"
using namespace std;

class Manager
{
private:
	string cmd; //get command from command.txt
	FPGrowth* fpgrowth;
	BpTree* bptree;
	
public:
	Manager(int threshold, int bpOrder)	//constructor of Manager
	{
		fpgrowth = new FPGrowth(&flog,&result, threshold); //constructor of FPGrowth
		bptree = new BpTree(&flog, bpOrder); //constructor of BpTree
	}


	~Manager()//destructor
	{
		delete fpgrowth;
	}

	ifstream fin; //read market.txt
	ofstream flog; //write log.txt
	ofstream result; //write result.txt
	

	void run(const char* command); //run according to command.txt
	/*function of each command*/
	bool LOAD(); 
	bool BTLOAD();

	bool PRINT_ITEMLIST();
	bool PRINT_FPTREE();

	bool PRINT_RANGE(string item, int start, int end);
	bool PRINT_CONFIDENCE(string item, double rate);
	bool PRINT_BPTREE(string item, int min_frequency);

	void printErrorCode(int n); //print Error code
	void printSuccessCode(); //print Success code


};
