#ifndef _BpTree_H_
#define _BpTree_H_

#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include <fstream>
#include <iostream>

class BpTree {
private:
	BpTreeNode* root;
	int			order;		// m children
	ofstream* fout;
public:
	BpTree(ofstream* fout, int order = 3) { //contructor
		root = NULL;
		this->order = order;
		this->fout = fout;
	}
	~BpTree() {

	};
	bool		Insert(int key, set<string> set); //create BPtree
	bool		excessDataNode(BpTreeNode* pDataNode);  //if excess components in DataNode
	bool		excessIndexNode(BpTreeNode* pIndexNode);  //if excess components in IndexNode
	void		splitDataNode(BpTreeNode* pDataNode);       //split data node
	void		splitIndexNode(BpTreeNode* pIndexNode);    //split index node
	BpTreeNode* getRoot() { return root; }  //get root
	BpTreeNode* searchDataNode(int n);      //if frequency data node is already in ->search

	/*print bp tree functions*/
	void	printFrequentPatterns(set<string> pFrequentPattern, string item);
	bool	printFrequency(string item, int min_frequency);
	bool	printConfidence(string item, double item_frequency, double min_confidence);
	bool 	printRange(string item, int min, int max);

};

#endif