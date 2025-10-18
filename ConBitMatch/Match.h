#pragma once
#include "bitSequence.h"

using namespace std;

class match
{
public:
	size_t overlap_Tw(size_t Y, int twsize);
	size_t eql2Match(size_t X, size_t mask1);

	size_t eql3Match(size_t Rx, size_t Y, size_t T_tw, size_t& out_T2);

	size_t eql4Match(size_t Z, size_t Y, size_t T_tw, size_t& out_T2);

	size_t eql5Match(size_t T_tw);
	size_t overlapMatch(global& g, query a, vector<vector<size_t>> bitSequence, unordered_map<string, int> eventmap, int twsize, int j, size_t T_lmask, vector<size_t>& multilyResult);
	size_t multiWordMatch(unordered_map<string, int> eventmap, vector<vector<size_t>>& bitSequence, query a, int i, int j, int twsize);
	vector<size_t> newbitMatch(global& g,query a, vector<vector<size_t>> bitSequence, unordered_map<string, int> eventmap, int timeContainer);
};

