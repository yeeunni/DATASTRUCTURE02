#include "HeaderTable.h"

HeaderTable::~HeaderTable() {
	dataTable.clear();
}


void HeaderTable::insertTable(char* item, int frequency) {
	string s_item(item); //char* to string
	fpnode = new FPNode; //allocate FPNode to connect table and fptree
	if (count == 0) { //if first insert
		indexTable.push_back(pair<int, string>(frequency, s_item)); //push_back to indexTable
		count++;
		dataTable.insert(map<string, FPNode*>::value_type(s_item, fpnode)); //insert to dataTable
		return; 
	}
	for (auto it = indexTable.begin(); it != indexTable.end(); it++) {
		if (it->second == s_item) { //if item is already in indexTable
			it->first = it->first + 1; //just update frequency
			return;
		}
	}
	indexTable.push_back(pair<int, string>(frequency, s_item)); //if item is not in indexTable->push_back
	dataTable.insert(map<string, FPNode*>::value_type(s_item, fpnode)); //if item is not in datatTable->insert
}

void HeaderTable::show_data() {          //print datatable
	map<string, FPNode*>::iterator it;
	for (it = dataTable.begin(); it != dataTable.end(); it++) {
		cout << it->first << "   "<<it->second << endl;      //print item and each fpnode's address
	}
}
int HeaderTable::find_frequency(string item) { //find item's frequency
	int frequency = 0; //initialization
	for (auto it = indexTable.begin(); it != indexTable.end(); it++) { //traversal using iterator
		if (it->second == item) {   //if find item
			frequency = it->first;
			break;
		}
	}
	return frequency;
}