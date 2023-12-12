#pragma once

#include <set>
#include <map>
#ifndef _string
#define _string
#include<string>
#endif
using namespace std;

class FrequentPatternNode
{
private:
	int frequency;		// FrequentPattern frequency
	multimap<int, set<string> > FrequentPatternList;	//first is FrequentPattern size, second is FrequentPattern data

public:
	FrequentPatternNode() { frequency = 0; }
	~FrequentPatternNode() { FrequentPatternList.clear(); } 
	void setFrequency(int frequency) { this->frequency = frequency; } //setFrequency
	void InsertList(set<string> item) { FrequentPatternList.insert(multimap<int, set<string>>::value_type(item.size(), item)); } //insert string item and its size
	int getFrequency() { return frequency; } //get freuquency
	multimap<int, set<string> > getList() { return FrequentPatternList; }
};

