#include "BpTree.h"
#include <iomanip>
bool BpTree::Insert(int key, set<string> set) {
	
	if (root == NULL) {      //if root is null-> insert at first
		BpTreeNode* data_add = new BpTreeDataNode; //allocate new BpTreeDataNode
		FrequentPatternNode* fp_add = new FrequentPatternNode; //allocate new FrequentPatternNode
		fp_add->setFrequency(key); //set frequency in FrequentPatternNode
		data_add->insertDataMap(key, fp_add); //complete data_add
		root = data_add; //generate root
	}
	else {
		if (searchDataNode(key)!=NULL) {  //if same frequency is already in BpTreeDataNode
			FrequentPatternNode* pattern_add = new FrequentPatternNode;  //allocate new FrequentPatternNode
			BpTreeNode* cur = searchDataNode(key);      //cur is point to BpTreeDataNode that has same frequency 
			map<int, FrequentPatternNode*>* data_map = cur->getDataMap();
			map<int, FrequentPatternNode*>::iterator it;
			for (it = data_map->begin(); it != data_map->end(); it++) {
				if (key == it->first) {
					it->second->InsertList(set);   //update FrequentPatternNode
				}
			}
		}
		else {
			int count = 1;
			FrequentPatternNode* fp_add = new FrequentPatternNode; //allocate new FrequentPatternNode
			fp_add->InsertList(set);
			BpTreeNode* pCur = root;                               //pCur = root
			map<int, BpTreeNode*>* index_map = pCur->getIndexMap();
			while (index_map != NULL) {
				map<int, BpTreeNode*>::iterator it;
				count = 1;
			
				for (it = index_map->begin(); it != index_map->end(); it++) { //traverse of BpTreeIndexNode
					if (key < it->first && count == 1) {   //case 1
						pCur = pCur->getMostLeftChild();
						break;
					}
					else if (key < it->first && count != 1) {  //case 2
						it--;
						pCur = it->second;
						break;
					}
					else if (key == it->first) { //case3
						pCur = it->second;
						break;
					}
					else if ((count) == index_map->size() && key > it->first) { //case4
						pCur = it->second;
						break;
					}
					count++;
				}
				index_map = pCur->getIndexMap(); //move pCur
				
			}
			
			pCur->insertDataMap(key, fp_add); //find DataMap's location to input and insert
			
			if (excessDataNode(pCur)) {   //if excess DataNode
				splitDataNode(pCur);
				
			}
			if (root->getParent() != NULL) {  //if root have parent
				while(root->getParent()!=NULL){
				root = root->getParent();  //root change
				}
			}
		}
	}

	return true;
}

BpTreeNode* BpTree::searchDataNode(int n) {
	BpTreeNode* pCur = root;

	while (pCur->getMostLeftChild() != NULL) { //move to BpTreeDataNode at first
		pCur = pCur->getMostLeftChild();
	}
	while (pCur != NULL) {
		map<int, FrequentPatternNode*>* data_map = pCur->getDataMap();
		map<int, FrequentPatternNode*>::iterator it;
		for (it = data_map->begin(); it != data_map->end(); it++) { //traverse all BpTreeDataNode
			if (n == it->first) {  //if same frequency is already in BpTreeDataNode
				return pCur;
			}
		}
		pCur = pCur->getNext(); //move pCur
	}
	return NULL;
}

void BpTree::splitDataNode(BpTreeNode* pDataNode) {
	BpTreeNode* data_add = new BpTreeDataNode;     //allocate BpTreeDataNode to be moved
	double del = ceil((order - 1) / 2.0) + 1;   //del = split key
	int count = 0;
	int split_key=0;
	map<int, FrequentPatternNode*>* data_map = pDataNode->getDataMap();
	map<int, FrequentPatternNode*>::iterator it = data_map->begin();
	while (it != data_map->end()) {
		count++;
		if (count >= del) {  //if count is over split_key
			if (count == del) {
				split_key = it->first;  //store split_key
			}
			data_add->insertDataMap(it->first,it->second); //move datanode to data_add
			pDataNode->deleteMap(it++->first);  //delete components after move
		}
		else {
			it++;
		}
	}
	/*reconnect BpTreeDataNode(linked list)*/
	if (pDataNode->getNext() != NULL) {
		pDataNode->getNext()->setPrev(data_add);
	}
	data_add->setNext(pDataNode->getNext());
	pDataNode->setNext(data_add);
	data_add->setPrev(pDataNode);

	/*reset parent of BpTreeDataNode*/
	BpTreeNode* pp = pDataNode->getParent();

	if (pp != NULL) { //pp is not null-> insert to original parent node
		pp->insertIndexMap(split_key,data_add);
	}
	else {  //have no parent -> make parnet node and connect
		pp = new BpTreeIndexNode;
		pp->insertIndexMap(split_key, data_add);
		pp->setMostLeftChild(pDataNode);
	}
	/*reconnect parent of BpTreeDataNode*/
	pDataNode->setParent(pp);
	data_add->setParent(pp);

	if (excessIndexNode(pp)) { //if excess indexNode
		splitIndexNode(pp);
	}
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {
	BpTreeNode* index_add = new BpTreeIndexNode;  //allocate  new BpTreeIndexNode to be moved
	double del = ceil((order - 1) / 2.0) + 1;  //del = split key
	int count = 0;
	int split_key = 0;
	map<int, BpTreeNode*>* index_map = pIndexNode->getIndexMap();
	map<int, BpTreeNode*>::iterator it = index_map->begin();
	while (it != index_map->end()) {
		count++;
		if (count == del) {
			split_key = it->first;                      //store split_key
			index_add->setMostLeftChild(it->second);  //set most left child of index_add
			it->second->setParent(index_add);       //set parent of it->second
			pIndexNode->deleteMap(it++->first);    //delete from original index node
		}
		else if (count > del) {    

			it->second->setParent(index_add); //set parent of it->second
			index_add->insertIndexMap(it->first, it->second);  //move from original index node to index_add
			pIndexNode->deleteMap(it++->first);  //delete from original index node
		}
		else {
			it++;
		}
	}
	/*reset parent of BpTreeDataNode*/
	BpTreeNode* pp = pIndexNode->getParent();
	if (pp != NULL) {
		pp->insertIndexMap(split_key, index_add);
	}
	else {
		pp = new BpTreeIndexNode;
		pp->insertIndexMap(split_key, index_add);
		pp->setMostLeftChild(pIndexNode);
	}
	/*reconnect parent of BpTreeDataNode*/
	pIndexNode->setParent(pp);
	index_add->setParent(pp); 
	if (excessIndexNode(pp)) {  //if pp(index node) also excess-> split again
		splitIndexNode(pp);
	}
}
bool BpTree::excessDataNode(BpTreeNode* pDataNode) { //if excess components in datanode
	if (pDataNode->getDataMap()->size() > order - 1) return true;//order is equal to the number of elements 
	else return false;
}

bool BpTree::excessIndexNode(BpTreeNode* pIndexNode) { //if excess components in indexnode
	if (pIndexNode->getIndexMap()->size() > order - 1)return true;//order is equal to the number of elements 
	else return false;
}


bool BpTree::printConfidence(string item, double item_frequency, double min_confidence) //same algorithm to printFrequency -> skip comments
{
	int count = 0;
	BpTreeNode* pCur = root;
	while (pCur->getMostLeftChild() != NULL) {
		pCur = pCur->getMostLeftChild();
	}
	while (pCur != NULL) {
		map<int, FrequentPatternNode*>* data_map = pCur->getDataMap();
		map<int, FrequentPatternNode*>::iterator it;
		for (it = data_map->begin(); it != data_map->end(); it++) {
				multimap<int, set<string> >  frequent_node = it->second->getList();
				multimap<int, set<string> >::iterator m_it;
				set<string>::iterator s_it;
				for (m_it = frequent_node.begin(); m_it != frequent_node.end(); m_it++) {
					set<string> str = m_it->second;
					for (s_it = str.begin(); s_it != str.end(); s_it++) {
						string tmp;
						tmp = *s_it;
						if (tmp == item) {
							double rate = it->first / item_frequency;  //save confidence
							if (rate >= min_confidence) {  //if rate >= confidence
								count++;
								if (count == 1) {    //print at first
									*fout << "==========PRINT_CONFIDENCE============ " << endl;
									*fout << "FrequentPattern      Frequency   Confidence " << endl;
								}
								printFrequentPatterns(str, item);  //print
								*fout << "         " << it->first << "  ";
								*fout << setprecision(2)<<fixed;                 //print rate unitl .xx
								*fout << rate << endl;
							}
						}
					}
				}

		}
		pCur = pCur->getNext();
	}
	if (count != 0) {
		return 1;
	}
	else {
		return 0;
	}
}
bool BpTree::printFrequency(string item, int min_frequency)//print winratio in ascending order
{
	int count = 0;
	BpTreeNode* pCur = root;
	while (pCur->getMostLeftChild() != NULL) {   //move to BpTreeDataNode at first
		pCur = pCur->getMostLeftChild();
	}
	while (pCur != NULL) {
		map<int, FrequentPatternNode*>* data_map = pCur->getDataMap(); //getDataMap
		map<int, FrequentPatternNode*>::iterator it;
		for (it = data_map->begin(); it != data_map->end(); it++) { //traverse all components of data_amp
		
			if (it->first >= min_frequency) {  // BpTreeDataNode's frequency is over min_frequency
				multimap<int, set<string> >  frequent_node = it->second->getList(); //get each BpTreeDataNode's frequentpatterns
				multimap<int, set<string> >::iterator m_it;
				set<string>::iterator s_it;
				for (m_it = frequent_node.begin(); m_it != frequent_node.end(); m_it++) { //traverse all components of each BpTreeDataNode's frequentpatterns
					set<string> str = m_it->second;
					for (s_it = str.begin(); s_it != str.end(); s_it++){
						string tmp;
						tmp = *s_it;
						if (tmp == item) {
							count++;
							if (count == 1) {       //print at first
								*fout << "==========PRINT_BPTREE============ " << endl;
								*fout << "FrequentPattern           Frequency " << endl;
							}
							printFrequentPatterns(str, item);  //print frequentpatterns
							*fout << "         " << it->first << endl;
						}
					}
				}
			}

		}
		pCur = pCur->getNext();  //move pCur
		
	}
	
	if (count != 0) { 
		return true;
	}
	else { //if nothing to print
		return false;
	}
}
bool BpTree::printRange(string item, int min, int max) { //same algorithm to printFrequency -> skip comments
	int count = 0;
	BpTreeNode* pCur = root;
	while (pCur->getMostLeftChild() != NULL) {
		pCur = pCur->getMostLeftChild();
	}
	while (pCur != NULL) {
		map<int, FrequentPatternNode*>* data_map = pCur->getDataMap();
		map<int, FrequentPatternNode*>::iterator it;
		for (it = data_map->begin(); it != data_map->end(); it++) {
			if (it->first >= min && it->first <= max) {                      //if frequency is over min and smaller than max parameter
				multimap<int, set<string> >  frequent_node = it->second->getList();
				multimap<int, set<string> >::iterator m_it;
				set<string>::iterator s_it;
				for (m_it = frequent_node.begin(); m_it != frequent_node.end(); m_it++) {
					set<string> str = m_it->second;
					for (s_it = str.begin(); s_it != str.end(); s_it++) {
						string tmp;
						tmp = *s_it;
						if (tmp == item) {
							count++;
							if (count == 1) {
								*fout << "==========PRINT_RANGE============ " << endl;
								*fout << "FrequentPattern           Frequency " << endl;
							}
							printFrequentPatterns(str, item);
							*fout << "         " << it->first << endl;
						}
					}
				}
			}

		}
		pCur = pCur->getNext();
	}

	if (count != 0) {
		return true;
	}
	else {
		return false;
	}
}
void BpTree::printFrequentPatterns(set<string> pFrequentPattern, string item) { //print frequent patterns template
	*fout << "{";
	set<string> curPattern = pFrequentPattern;
	for (set<string>::iterator it = curPattern.begin(); it != curPattern.end();) { //traverse using iterator
		string temp = *it++;
		if (temp != item) *fout << temp<< ", ";
		if (it == curPattern.end()) {
			*fout << item;                             //print item at last
			*fout << "} ";
			break;
		}
	}
}