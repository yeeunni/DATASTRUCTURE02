#pragma once
#include "FrequentPatternNode.h"
#include "FPNode.h"
class BpTreeNode     //parent class of BpTreeDataNode and BpTreeIndexNode
{
private:
	BpTreeNode* pParent;   //pointer to parent
	BpTreeNode* pMostLeftChild;  //point to most left child

public:
	BpTreeNode() {       //constructor
		pParent = NULL;
		pMostLeftChild = NULL;
	}
	~BpTreeNode() {

	}

	void setMostLeftChild(BpTreeNode* pN) { pMostLeftChild = pN; } //set most left child
	void setParent(BpTreeNode* pN) { pParent = pN; }  //set parent node

	BpTreeNode* getParent() { return pParent; }
	BpTreeNode* getMostLeftChild() { return pMostLeftChild; }

	/*embody in each derived class-> virtual function*/
	virtual void setNext(BpTreeNode* pN) {}
	virtual void setPrev(BpTreeNode* pN) {}
	virtual BpTreeNode* getNext() { return NULL; }
	virtual BpTreeNode* getPrev() { return NULL; }

	virtual void insertDataMap(int n, FrequentPatternNode* pN) {}
	virtual void insertIndexMap(int n, BpTreeNode* pN) {}
	virtual void deleteMap(int n) {}

	virtual map<int, BpTreeNode*>* getIndexMap() { return {}; }
	virtual map<int, FrequentPatternNode*>* getDataMap() { return {}; }

};