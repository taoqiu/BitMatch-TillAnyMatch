#pragma once
#include "parseData.h"
using namespace std;

class sequence
{
public:
	void newbitVector(global& g,query a, parseData procData, vector<vector<size_t>>& bitvector, unordered_map<string, int>& eventmap, int timeContainer);
	struct attcons
	{
		vector<string> eventName;
		vector<string> attName;
		vector<string> opNum;
		vector<float>  value;
	};

};