#ifndef _BpTreeDataNode_H_
#define _BpTreeDataNode_H_

#include "BpTreeNode.h"
class BpTreeDataNode : public BpTreeNode  //class of BpTreeNode
{
private:
	map <int, FrequentPatternNode*> mapData;  //datamap
	BpTreeNode* pNext;
	BpTreeNode* pPrev;
public:
	BpTreeDataNode() { //constructor
		pNext = NULL;
		pPrev = NULL;
	}

	void setNext(BpTreeNode* pN) { pNext = pN; }  //set next of datanode 
	void setPrev(BpTreeNode* pN) { pPrev = pN; }  //set prev of datanode
	BpTreeNode* getNext() { return pNext; } //get next of datanode 
	BpTreeNode* getPrev() { return pPrev; } //get prev of datanode

	void insertDataMap(int n, FrequentPatternNode* pN) {                    //insert datanode to datamap
		mapData.insert(map<int, FrequentPatternNode*>::value_type(n, pN));
	}

	void deleteMap(int n) {          //delete when split
		mapData.erase(n);
	}
	map<int, FrequentPatternNode*>* getDataMap() { return &mapData; }

};

#endif
