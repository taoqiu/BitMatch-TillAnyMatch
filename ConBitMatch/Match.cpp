#pragma once
#include "Match.h"
#include <bitset>
using namespace std;

size_t match::eql2Match(size_t X, size_t mask1)
{
	size_t Rx = 0;
	Rx = mask1 & X;
	return Rx;
}


size_t match::eql3Match(size_t Rx, size_t Y, size_t T_tw, size_t& out_T2) {
	size_t T0 = Rx | Y;
	T0 |= 0x8000000000000000;
	size_t T1 = (Y ^ (Rx & Y)) << 1;

	size_t T2 = ((T0 - T1) ^ T0) >> 1;
	out_T2 = T2;
	size_t T3 = T2 & T_tw;

	return T3 ^ T_tw;
}


size_t match::eql4Match(size_t Z, size_t Y, size_t T_tw, size_t& out_T2) {
	size_t Tz = Z & T_tw;

	size_t T0 = Tz | Y;

	size_t T1 = (Y ^ (Tz & Y)) << 1;

	size_t T2 = ((T0 - T1) ^ T0) >> 1;
	out_T2 = T2;

	return T2 & T_tw;
}

size_t match::eql5Match(size_t T_tw) {
	return (T_tw | (T_tw << 1)) ^ (T_tw << 1);
}

int count_leading_zeros_msvc_64(uint64_t x) {
	unsigned long index;
	if (_BitScanReverse64(&index, x)) {
		return 63 - index; 
	}
	return 64; 
}

size_t match::multiWordMatch(unordered_map<string, int> eventmap, vector<vector<size_t>> & bitSequence, query a, int i, int j, int twsize)
{ 
	

	int arryflag1 = eventmap[a.pt.evtype[a.pt.evtype.size() - 1]] - 1;
	int tw1 = count_leading_zeros_msvc_64(bitSequence[arryflag1][j]);
	int tw2 = twsize - tw1;
	size_t Tw = pow(2, tw2 + 1) - 1;
	size_t Rx = 0;
	for (; i >= 0; i--)
	{
		int arryflag2 = eventmap[a.pt.evtype[i]] - 1;
		size_t T_2 = 0;
		size_t Ty = eql5Match(Tw);
		if (a.pt.sttype[i] == "negation")
		{
			Tw = eql4Match(bitSequence[arryflag2][j], Ty, Tw, T_2);
			i--;
			arryflag2 = eventmap[a.pt.evtype[i]] - 1;
			Ty = eql5Match(Tw);
		}
		Rx = eql2Match(bitSequence[arryflag2][j], Tw);
		if (Rx == 0)
			break;
		Tw = eql3Match(Rx, Ty, Tw, T_2);
	}
	return Rx;
}


size_t match::overlap_Tw(size_t Y,int twsize) {
	size_t finamask = Y;
	size_t curmask = Y;
	for (int j = 1; j < twsize; j++)
	{
		curmask = curmask << 1;

		finamask |= curmask;

	}
	finamask &= 0x7fffffffffffffff;
	return finamask;

}

size_t match::overlapMatch(global& g, query a, vector<vector<size_t>> bitSequence, unordered_map<string, int> eventmap, int twsize, int j, size_t T_lmask, vector<size_t>& multilyResult)
{
	int arryflag1 = eventmap[a.pt.evtype[a.pt.evtype.size() - 1]] - 1;
	size_t result = 0;
	for (const auto& layer : g.bwArray[j].bitWord.layers) {
		size_t Tw = overlap_Tw(layer.binary_val,twsize);
		size_t T_2 = 0;
		size_t Rx = 0;
		bool multiflag = false;
			for (int i = (a.pt.evtype.size() - 2); i >= 0; i--) {
				int arryflag2 = eventmap[a.pt.evtype[i]] - 1;
				size_t Ty = eql5Match(Tw);
				if (a.pt.sttype[i] == "negation")
				{
					Tw = eql4Match(bitSequence[arryflag2][j], Ty, Tw, T_2);
					i--;
					arryflag2 = eventmap[a.pt.evtype[i]] - 1;
					Ty = eql5Match(Tw);
				}
				Rx = eql2Match(bitSequence[arryflag2][j], Tw);
				if (Rx == 0)
					break;
				Tw = eql3Match(Rx, Ty, Tw, T_2);
				if ((T_2 & 0x4000000000000000) && (count_leading_zeros_msvc_64(bitSequence[arryflag1][j]) <= twsize) && (j != 0) && !multiflag)
				{
					multilyResult[j - 1] |= multiWordMatch(eventmap, bitSequence, a, i, j, twsize);
					multiflag = true;
				}
			}
			result |= Rx;
	}
	return result;
}

vector<size_t> match::newbitMatch(global& g,query a, vector<vector<size_t>> bitSequence, unordered_map<string, int> eventmap, int timeContainer)
{
	long t1 = GetTickCount64();
	int twsize = a.timeWindow / timeContainer;
	int eventnum = eventmap[a.pt.evtype[a.pt.evtype.size() - 1]] - 1;
	vector<size_t> mask1;
	vector<size_t> overmask1;
	

	for (int i = 0; i < bitSequence[eventnum].size(); i++)
	{

		int overflag = 0;
		size_t overmask = 0;
		size_t finamask = bitSequence[eventnum][i];
		size_t curmask = bitSequence[eventnum][i];
		for (int j = 1; j < twsize; j++)
		{
			curmask = curmask<<1;

			finamask |= curmask;

			if (overflag==0 &&  finamask >= 9223372036854775808)
			{
				overmask += pow(2, twsize - j+1)-2;
				overflag = 1;
			}
		}
		finamask &= 0x7fffffffffffffff;
		mask1.push_back(finamask);
		overmask1.push_back(overmask);
		if (overmask != 0&&mask1.size()>1)
		{
			mask1[i - 1] |= overmask;
		}

	}

	vector<size_t> multilyResult;

	int j = 0;
	int arryflag1 = eventmap[a.pt.evtype[a.pt.evtype.size() - 1]] - 1;
	size_t T_lmask = 0x8000000000000000;
	size_t T_mask = 0x8000000000000000;

	while (j < bitSequence[0].size())
	{

		size_t Tw = mask1[j];
		size_t Rx = 0;
		size_t T_2 = 0;
		bool multiflag = false;
		if (g.bwArray[j].bitWord.flag) 
		{
			multilyResult.push_back(overlapMatch(g,a,bitSequence,eventmap,twsize,j,T_lmask,multilyResult));
		}
		else {
			for (int i = (a.pt.evtype.size() - 2); i >= 0; i--) {
				int arryflag2 = eventmap[a.pt.evtype[i]] - 1;
				size_t Ty = eql5Match(Tw);
				if (a.pt.sttype[i] == "negation")
				{
					Tw = eql4Match(bitSequence[arryflag2][j], Ty, Tw, T_2);
					i--;
					arryflag2 = eventmap[a.pt.evtype[i]] - 1;
					Ty = eql5Match(Tw);
				}
				Rx = eql2Match(bitSequence[arryflag2][j], Tw);
				if (Rx == 0)
					break;
				Tw = eql3Match(Rx, Ty, Tw, T_2);
				if ((T_2 & 0x4000000000000000) && (count_leading_zeros_msvc_64(bitSequence[arryflag1][j]) <= twsize) && (j != 0) && !multiflag)
				{
					multilyResult[j - 1] |= multiWordMatch(eventmap, bitSequence, a, i, j, twsize);
					multiflag = true;
				}
			}
			multilyResult.push_back(Rx);
		}
		j++;
	}

	return multilyResult;
}