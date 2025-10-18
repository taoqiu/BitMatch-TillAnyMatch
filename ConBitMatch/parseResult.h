#pragma once
#include "Match.h"
using namespace std;
class result
{
public:
	void FindPosition(global& g,const unsigned& k, size_t num);
	void finalResult(global& g, vector<size_t> result);
};