#include "Manager.h"
#include <sstream>
//#define _CRT_SECURE_NO_WARNINGS
void Manager::run(const char* command) 
{
	string order;
	int min_freq;
	int max_freq;
	double min_conf;
	string item;
	fin.open(command); //call command.txt
	flog.open("log.txt", ios::app); 
	result.open("result.txt", ios::app);
	if (!fin) //if not open command.txt
	{
		cout << "File Open Error" << endl;
		return;
	}
	while (!fin.eof()) //while(command is not end)
	{	
		getline(fin, order);
		stringstream com(order);
		com >> cmd;
		if (cmd == "LOAD") { //command is "LOAD"
			if (LOAD()) {
				flog << "========LOAD=========" << endl;
				printSuccessCode();
			}

			else {
				flog << "========LOAD=========" << endl;
				printErrorCode(100);
			}
		}
		else if (cmd == "PRINT_ITEMLIST") //command is "PRINT_ITEMLIST"
		{
			if (PRINT_ITEMLIST())
			{
				flog << "=====================" << endl;
			}
		}
		else if (cmd == "PRINT_FPTREE") //command is "PRINT_FPTREE"
		{
			if (PRINT_FPTREE())
			{
				flog << "====================" << endl;
			}
		} 
		else if (cmd == "BTLOAD") { //command is "BTLOAD"
			if (BTLOAD()) {
				flog << "========BTLOAD=========" << endl;
				printSuccessCode();
			}
			else {
				flog << "========BTLOAD=========" << endl;
				printErrorCode(200);
			}
		}
		else if (cmd == "PRINT_BPTREE") { //command is "PRINT_BPTREE"
			string para;
			getline(com, para);
			char c_item[10000];
			strcpy(c_item, para.c_str());
			char* ptr = strtok(c_item, "\t");
			item = ptr;
			ptr = strtok(NULL, "\t");
			min_freq = stoi(ptr);
			string s_min_freq = to_string(min_freq); //int to string to find no parameter
			if (item.size() < 1 || s_min_freq.size() < 1) { //have no parameter
				flog << "========PRINT_BPTREE=========" << endl;
				printErrorCode(500);
				return;
			}
			if (PRINT_BPTREE(item, min_freq)) {
				flog << "=======================" << endl;
			}
		}
		else if (cmd == "PRINT_RANGE") { //command is "PRINT_RANGE"
			string para;
			getline(com, para);
			char c_item[10000];
			strcpy(c_item, para.c_str());
			char* ptr = strtok(c_item, "\t");
			item = ptr;
			ptr = strtok(NULL, "\t");
			min_freq = stoi(ptr);
			ptr = strtok(NULL, "\t");
			max_freq = stoi(ptr);
			string s_min_freq = to_string(min_freq); //int to string to find no parameter
			string s_max_freq = to_string(max_freq); //int to string to find no parameter
			if (item.size() < 1 || s_min_freq.size() < 1 || s_max_freq.size()<1) { //have no parameter
				flog << "========PRINT_RANGE=========" << endl;
				printErrorCode(700);
				return;
			}
			if (PRINT_RANGE(item, min_freq,max_freq)) {
				flog << "======================== " << endl;
			}
		}
		else if (cmd == "PRINT_CONFIDENCE") { //command is "PRINT_CONFIDENCE"
			string para;
			getline(com, para);
			char c_item[10000];
			strcpy(c_item, para.c_str());
			char* ptr = strtok(c_item, "\t");
			item = ptr;
			ptr = strtok(NULL, "\t");
			min_conf = stod(ptr);
			
			string s_min_conf = to_string(min_conf); //int to string to find no parameter
			if (item.size() < 1 || s_min_conf.size() < 1) { //have no parameter
				flog << "========PRINT_CONFIDENCE=========" << endl;
				printErrorCode(600);
				return;
			}
			if (PRINT_CONFIDENCE(item, min_conf)) {
				flog << "======================= " << endl;
			}
		}
		else if (cmd == "SAVE") { //command is "SAVE"
			fpgrowth->frequenctPatternSetting();
			if (fpgrowth->get_check_pattern() == 0) {	//have no frequent pattern
				printErrorCode(800);
				return;
			}
			else {
				printSuccessCode();
			}
		}
		else if (cmd == "EXIT") { //command is "EXIT"
			flog << "========EXIT==========" << endl;
			printSuccessCode();
			break;
		}

	}
	fin.close();
	return;
}

	bool Manager::LOAD()

	{
		string item;
		ifstream market;
		//int count = 0;

		market.open("market.txt", ios::in);
		if (!market.is_open() && fpgrowth->isexist()) {                    //if no file->error and already fp-tree is exist
			printErrorCode(100);
			return 0;
		}
		else {
			list<pair<int, string>> idx = fpgrowth->getHeaderTable()->getindexTable(); //idx is indexTable
			
			while (!market.eof()) {
				getline(market, item);
				if (!item.compare(""))           //don't read last space sentence
					break;
				char c_item[10000];
				strcpy(c_item, item.c_str());
				char* ptr = strtok(c_item, "\t");   //cut items according to '\t'
				while (ptr != NULL) {
					fpgrowth->createTable(ptr, 1); //frequency is 1(update value) and create table
					ptr = strtok(NULL, "\t");
				}
			}
			
			market.close();
			market.open("market.txt", ios::in);
			HeaderTable* head = fpgrowth->getHeaderTable(); //call fpgrowth's headertable
			FPNode* root = fpgrowth->getTree();
			while (!market.eof()) {
				getline(market, item);
				if (!item.compare(""))           //don't read last space sentence
					break;
				set<string> trans_list;
				char c_item[10000];
				strcpy(c_item, item.c_str()); //string to char for strtok
				char* ptr = strtok(c_item, "\t");
				while (ptr != NULL) {
					trans_list.insert(ptr); //read a transaction and list.push back(item)
					ptr = strtok(NULL, "\t");
				}
		
			fpgrowth->createFPtree(root,head,trans_list,1); //createFptree line by line of command.txt(each transaction)
			}
			market.close();
		}
		return true;
	}
	bool Manager::PRINT_ITEMLIST() {
		if (fpgrowth->getHeaderTable()->get_count() == 0) { //if no headertable
			flog << "========PRINT_ITEMLIST=========" << endl;
			printErrorCode(300);
			return 0;
		}
		else {
			flog << "==========PRINT_ITEMLIST============" << endl;
			flog << "Item     Frequency" << endl;
			fpgrowth->getHeaderTable()->descendingIndexTable(); //indextable sorting
			fpgrowth->printList(); 
			return true;
		}
	}

	bool Manager::PRINT_FPTREE()
	{
		if (!fpgrowth->isexist()) {         //if fpgrowth is not exist -> can't print
			flog << "========PRINT_FPTREE=========" << endl;
			printErrorCode(400);
			return 0;
		}
		else {
			return fpgrowth->printTree();
		}
	}

	bool Manager::BTLOAD()
	{
		string bp_item;
		ifstream result;
		int freq = 0;

		result.open("result.txt", ios::in);
		if (!result.is_open() && bptree->getRoot() != NULL) {                    //if no file->error  
			printErrorCode(200);
			return 0;
		}
		else {
			while (!result.eof()) {
				getline(result, bp_item); //read result.txt line by line
				set<string> word;
				if (!bp_item.compare(""))           //don't read last space sentence
					break;
				char c_bp_item[10000];
				strcpy(c_bp_item, bp_item.c_str()); //string to char for strtok
				char* bp_ptr = strtok(c_bp_item, "\t");
				freq = atoi(bp_ptr); //first component is frequency so store int type
				bp_ptr = strtok(NULL, "\t");
				while (bp_ptr != NULL) {
					word.insert(bp_ptr); 
					bp_ptr = strtok(NULL, "\t");
				}
				bptree->Insert(freq, word); //bptree insert
			}
			result.close();
		
		}

		return true;
	}
	bool Manager::PRINT_BPTREE(string item, int min_frequency) {
		if (bptree->getRoot() == NULL) {                  //bptree is empty
			flog << "========PRINT_BPTREE=========" << endl;
			printErrorCode(500);
			return 0;
		}
		else {

			if (bptree->printFrequency(item, min_frequency) == 0) { //nothing to print
				flog << "========PRINT_BPTREE=========" << endl;
				printErrorCode(500);
				return false;
			}
			else
			{
				return true;
			}
		}
	}
	bool Manager::PRINT_CONFIDENCE(string item, double rate) {
		if (bptree->getRoot() == NULL) {                             //bptree is empty
			flog << "========PRINT_CONFIDENCE=========" << endl;
			printErrorCode(600);
			return 0;
		}
		else {
			double freq;
			freq = fpgrowth->getHeaderTable()->find_frequency(item); //find frequency of item -> denominator of confidence calculation

			if (bptree->printConfidence(item, freq, rate) == 0) { //caculate confidence 
				flog << "========PRINT_CONFIDENCE=========" << endl;
				printErrorCode(600);
				return false;
			}
			else {
				return true;
			}
		}
	}
	bool Manager::PRINT_RANGE(string item, int start, int end) {
		if (bptree->getRoot() == NULL) {                    //bptree is empty
			flog << "========PRINT_RANGE=========" << endl;
			printErrorCode(700);
			return 0;
		}
		else {
			if (bptree->printRange(item, start, end) == 0) {  //nothing to print
				flog << "========PRINT_RANGE=========" << endl;
				printErrorCode(600);
				return false;
			}
			else {
				return true;
			}
		}
	}

	void Manager::printErrorCode(int n) {				//ERROR CODE PRINT
		flog << "ERROR" << n << endl;
		flog << "========================" << endl << endl;
	}

	void Manager::printSuccessCode() {//SUCCESS CODE PRINT 
		flog << "Success" << endl;
		flog << "=========================" << endl << endl;
	}
