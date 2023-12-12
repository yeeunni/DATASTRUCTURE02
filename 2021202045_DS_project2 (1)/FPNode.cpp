#include "FPNode.h"

FPNode::FPNode()	//constructor
{
	parent = NULL;
	next = NULL;
	frequency = 0;
}


FPNode::~FPNode()//destructor
{
	children.clear();
}

FPNode* FPNode::getChildrenNode(string item) {
	map<string, FPNode*>::iterator it = children.find(item); //traverse childeren's node's item
	if (it == children.end()) return NULL; //can't find
	FPNode* findNode = it->second; //if find
	return findNode; //return children node
}

