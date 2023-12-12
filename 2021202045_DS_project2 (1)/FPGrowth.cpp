#include "FPGrowth.h"


FPGrowth::~FPGrowth() { //destructor
	frequenctPatterns.clear();
	delete table;
	delete fpTree;
}

void FPGrowth::createFPtree(FPNode* root, HeaderTable* table, set<string> item_array, int frequency) { //create FP-tree
	multimap<int, string, greater<int>> m; //sorting transaction according to each frequency of indexTable(greater)

	for (auto it = item_array.begin(); it != item_array.end(); it++) { //traverse of list item_array->a transaction
		int freq = table->find_frequency(*it); //find item's frequency
		m.insert(pair<int, string>(freq, *it)); //insert in multimap ->sort automatically 
	}
	int count = 0; //value of how many same frequency

	vector<pair<int, string>> v(m.begin(), m.end()); //pair to vector because need to sort string(value) when key(int) is same

	for (auto iter = v.begin(); iter != v.end(); ) //traverse vector v
	{

		if ((iter + 1) != v.end())  
		{

			if (iter->first == (iter + 1)->first)  //if adjacent frequency is same
			{
				count += 1;       //increase
			}
			iter++;

		}
		else
		{
			iter++;
		}
	}

	for (int i = 0; i < count; i++)   
	{
		for (auto iter = v.begin(); iter != v.end(); )
		{
			if ((iter + 1) != v.end())
			{
				if (iter->first == (iter + 1)->first)
				{
					if (iter->second < (iter + 1)->second)         //compare string -> swap
					{
						string temp;
						temp = (iter + 1)->second;
						(iter + 1)->second = iter->second;
						iter->second = temp;
					}
					else
					{
						iter++;
					}
				}
				else
				{
					iter++;
				}
			}
			else
			{
				iter++;
			}
		}
	}


	FPNode* cur = root;
	FPNode* pp = cur;           //pp= cur->parent
	vector<pair<int, string>>::iterator itr;

	for (itr = v.begin(); itr != v.end(); itr++) {
		pp = cur;                          //update pp
		if (check == 0) {                //value of first in -> can know fptree is empty or not
			if (cur->getChildrenNode(itr->second) == NULL) {
				FPNode* add = new FPNode;
				add->setParent(pp);
				add->updateFrequency(frequency);
				add->setFpitem(itr->second);
				cur->pushchildren(itr->second, add);
				connectNode(table, itr->second, add);
				check++;
			}
			else {

				cur->getChildrenNode(itr->second)->updateFrequency(frequency);
				check++;
			}
		}
		else {
			if (cur->getChildrenNode(itr->second) == NULL) {     //if item is not in childrenNode
				FPNode* add = new FPNode;                //allocate FPNode add
				add->setParent(pp);                      //set parent
				add->updateFrequency(frequency);        //insert frequency
				add->setFpitem(itr->second);              //insert item
				cur->pushchildren(itr->second, add);      //push cilderen
				connectNode(table, itr->second, add);    //connect same items
				check++;
			}  
			else {              //if item is already in childrenNOde

				cur->getChildrenNode(itr->second)->updateFrequency(frequency); //just update frequency
				check++;
			}
		}
		cur = cur->getChildrenNode(itr->second);  //move cur
	}

}

bool FPGrowth::isexist() {  //fp tree is exist
	if (check != 0) {  //check is not 0 -> is exist
		return 1;
	}
	else
		return 0;
}

void FPGrowth::connectNode(HeaderTable* table, string item, FPNode* node) {   //connect node table and fp tree nodes
	
	FPNode* cur;

	cur = table->getNode(item);   //find item FPNode* in dataTable

	if (cur->getNext() == NULL) {       //connect table and fpnode
		cur->setNext(node);
	}
	else {                                  //connect fpnode and fpnode
		while (cur->getNext() != NULL) {
			cur = cur->getNext();       
		}
		cur->setNext(node);
	}

}


map<set<string>, int> FPGrowth::getFrequentPatterns(HeaderTable* pTable, FPNode* pTree) {  //get frequent patterns and print to result.txt function
	
	FPNode* cur_next; //connect same item node
	FPNode* cur_list; //connect a transaction
	string item_1;  
	string item_2;   
	int num;
	int count = 0;
	list<pair<int, string>> idxTable = pTable->getindexTable();  //to find all items' frequent patterns ->call indexTable


	for (auto iter = idxTable.begin(); iter != idxTable.end(); iter++)  //traverse all componenets of idxTable
	{
		
		cur_next = pTable->getNode(iter->second);  
		item_1 = iter->second;                       //conditional FP-tree for "item_1"
		multimap<int, set<string>, greater<int>> mm;  //sotre conditional FP-tree for "item_1"

		while (cur_next->getNext() != NULL)
		{
			count = 0;
			cur_next = cur_next->getNext();
			cur_list = cur_next;
			set<string> set_item; //store items of a transaction
			while (cur_list->getParent() != NULL)
			{
				item_2 = cur_list->getFpitem();     //read a transaction
				if (count == 0) {                   //set frequency only at first
					num = cur_list->getFrequency();  
				}
				set_item.insert(item_2);           //insert to set_item
				cur_list = cur_list->getParent();  //move cur_list
				count++;
			}
			mm.insert(pair<int, set<string>>(num, set_item));  //insert to mm(conditional FP-tree)
		}

		int freq;
		multimap<int, set<string>, greater<int>>::iterator it; 
		set<string>::iterator s_it;
		map<string, int>  m_isover;  //sotre all frequnces of each item in mm
		string temp;
		for (it = mm.begin(); it != mm.end(); it++) {  //traverse all mm components
			freq = it->first;
			for (s_it = it->second.begin(); s_it != it->second.end(); s_it++)
			{
				temp = *s_it;
				
				if (m_isover.find(temp) != m_isover.end()) { //if item is already in m_isover
					m_isover[temp] = m_isover[temp]+freq;   //update freq using key-value
					
				}
				else {                                      //not found
					m_isover.insert(pair<string, int>(temp, freq));   //insert item and frequency newly
				}
			}
		}
		/*cout << "m_isover==========" << endl;
		for (auto iter = m_isover.begin(); iter != m_isover.end(); iter++)
		{
			cout << iter->first << " " << iter->second << endl;
		}*/
		map<string, int>  m_isover2;                                              //sotre item in m_isover that is only over threshold 
		for (auto itt = m_isover.begin(); itt != m_isover.end(); itt++) {         //traverse all componens in m_isover
			if (itt->second >= threshold) {            //if is over threshold
				m_isover2.insert(pair<string, int>(itt->first, itt->second));      //insert to m_isover2
			}
		}
		/*cout << "m_isover2==========" << endl;
		for (auto iter = m_isover2.begin(); iter != m_isover2.end(); iter++)
		{
			cout << iter->first << " " << iter->second << endl;
		}*/
		map<set<string>,int> m_fp;
		multimap<int, set<string>, greater<int>>::iterator mm_it;

		for (mm_it = mm.begin(); mm_it != mm.end(); mm_it++) 
		{
			set<string> fp;
			for (auto fp_it = m_isover2.begin(); fp_it != m_isover2.end(); fp_it++)
			{
				temp = fp_it->first; //frequent pattern
	

				if (mm_it->second.find(temp) != mm_it->second.end()) //if temp is in mm
				{
					fp.insert(temp);            //insert to fp
				}
				else
				{
					continue;
				}

			}
				if (m_fp.find(fp) != m_fp.end())  //if frequent pattern is in already in m_fp
				{
					m_fp[fp] = m_fp[fp] + mm_it->first; //just update frequent
					
				}
				else
				{
					m_fp.insert(pair<set<string>, int>(fp, mm_it->first)); //insert to m_fp
					
				}
			
		}
		
		
		for (auto fp_itt = m_fp.begin(); fp_itt != m_fp.end(); fp_itt++) { //traverse of all componenets of m_fp
			int size = fp_itt->first.size();   //set<string>.size
			int* arr = new int[size];          //allocate int array
			vector<string> v_data(fp_itt->first.begin(), fp_itt->first.end()); //set to vector -> to input poserSet parameter
			powerSet(&frequenctPatterns, v_data, iter->second, fp_itt->second, arr, 0); //to find partial set function
			delete[] arr; //delete int array
		}
		
	}

	for (auto poweriter = frequenctPatterns.begin(); poweriter != frequenctPatterns.end(); poweriter++) {
		if ((poweriter->second )/2>= 2) {
			if (check_pattern == 0) {         //at first
			*fout << "==========SAVE=============\n";
		}
		*result1 << (poweriter->second) / 2 << "\t";
		for (auto set_it = poweriter->first.begin(); set_it != poweriter->first.end(); set_it++) {
			*result1 << *set_it << "\t";
			check_pattern++;
			}
		}
		else { continue; }
		*result1 << endl;
	}
	return{};
	}



void FPGrowth::powerSet(map<set<string>, int>* FrequentPattern, vector<string> data, string item, int frequency, int* ptr, int depth) { //to find partial set function
	if (data.size() == depth) {
		
		set<string> set; 
		set.insert(item);
		for (int i = 0; i < data.size(); i++) { 
			if (ptr[i] == 1) set.insert(data[i]);
		}
		if (set.size() <= 1) {    //remove set's component is one or zero
			return;
		}
		else if (FrequentPattern->find(set) != FrequentPattern->end()) { //frequent pattern is duplicated
			FrequentPattern->find(set)->second = FrequentPattern->find(set)->second + frequency; //just update frequency
			return;
		}
		else {
			FrequentPattern->insert(make_pair(set, frequency)); 
			return;
		}
	}
	ptr[depth] = 1;
	
	powerSet(FrequentPattern, data, item, frequency, ptr, depth + 1); //recursive function
	
	ptr[depth] = 0;
	
	powerSet(FrequentPattern, data, item, frequency, ptr, depth + 1); //recursive functions
	

}

bool FPGrowth::printList() { //print itemlist
	list<pair<int, string>> idx_table = table->getindexTable(); //get indexTable
	for (auto it = idx_table.begin(); it != idx_table.end(); it++) { //from begin to end
		*fout << it->second << "   " << it->first << endl;
	}
	return true;
}
bool FPGrowth::printTree() {        //print FPTREE

	table->ascendingIndexTable();  //sorting
	FPNode* cur_next;        //connect same item node
	FPNode* cur_list;            //connect a transaction
	string item_2;
	list<pair<int, string>> idxTable = table->getindexTable();

	*fout << "==========PRINT_FPTREE==============="<<endl;
	*fout << "{StandardItem.Frequency}    (Path_Item.Frequency)" << endl;


	for (auto iter = idxTable.begin(); iter != idxTable.end(); iter++)
	{
		cur_next = table->getNode(iter->second); //table -> getNode

		string item_1;
		item_1 = iter->second;
		*fout << "{" << item_1 << ", " << iter->first << "}" << endl;

		while (cur_next->getNext() != NULL)
		{
			cur_next = cur_next->getNext(); //cur_next move
			cur_list = cur_next;   //cur_list move

			while (cur_list->getParent() != NULL)  //move to root
			{
				item_2 = cur_list->getFpitem();   
				int num = cur_list->getFrequency();
				*fout << "(" << item_2 << ", " << cur_list->getFrequency() << ") ";
				cur_list = cur_list->getParent(); //cur_list move
			}
			*fout << endl;
		}

	}
	return true;
}