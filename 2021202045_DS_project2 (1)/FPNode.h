#pragma once
#include <cstring>
#include <string>
#include <map>
#include <cmath>
#include <iostream>
using namespace std;
class FPNode
{
private:
	string fp_item;
	int frequency;
	FPNode* parent;
	FPNode* next;
	map<string, FPNode*> children;
public:
	FPNode();
	~FPNode();
	void setParent(FPNode* node) { this->parent = node; } //setParent
	void setNext(FPNode* node) { next = node; } //setNext-> same item connection
	void pushchildren(string item, FPNode* node) { children.insert(map<string, FPNode*>::value_type(item, node)); } //connect same transaction
	void updateFrequency(int frequency) { this->frequency += frequency; } //update frequency
	void setFpitem(string item) { fp_item = item; }
	/*get value or address*/
	int getFrequency() { return frequency; }
	FPNode* getParent() { return parent; }
	FPNode* getNext() { return next; }
	FPNode* getChildrenNode(string item);
	string getFpitem() { return fp_item; }
	map<string, FPNode*> getChildren() { return children; }


};

