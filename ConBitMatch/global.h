#include "includefile.h"
#include "parseQuery.h"
#include "event.h"
using namespace std; 

struct Layer {
	int   value;
	size_t   binary_val;
	Layer(int v, uint64_t b) : value(v), binary_val(b) {}
};

struct BitWord {
	bool                flag;
	std::vector<Layer>  layers;
};

struct BitWordWithID {
	int       id;
	BitWord   bitWord;
};

class global
{
public:
	vector<event> candis;
	vector<int> numresult;
	unordered_map<int, event> hmap;
	long long operations_num;
	
	vector<BitWordWithID> bwArray;
public:
	bool read1(string a, vector<string>& b, int& c);
	void Tokenize(const string& str, vector<string>& tokens, const string& delimiters);
	void test(query& a, vector<vector<size_t>> b);
	void parseFiletxt(vector<query>& a, string b);
	void printAsBit(size_t val);
};

