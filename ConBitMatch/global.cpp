
#include "bitSequence.h"
using namespace std;

bool global::read1(string a, vector<string>& b, int& c)
{
	ifstream file;
	file.open(a, ios_base::in);
	if (!file.is_open())
	{
		std::cout << "打开文件失败";
	}
	string s;
	int f = 0;
	while (getline(file, s))
	{
		b.push_back(s);
	}
	c = b.size();
	file.close();
	return true;
}
void global::Tokenize(const string& str, vector<string>& tokens, const string& delimiters)
{

	string::size_type lastPos = str.find_first_not_of(delimiters, 0);

	string::size_type pos = str.find_first_of(delimiters, lastPos);
	while (string::npos != pos || string::npos != lastPos)
	{

		tokens.push_back(str.substr(lastPos, pos - lastPos));

		lastPos = str.find_first_not_of(delimiters, pos);

		pos = str.find_first_of(delimiters, lastPos);
	}
}
void global::test(query& a, vector<vector<size_t>> b)
{

	for (int i = 0; i < a.pt.evtype.size(); i++)
	{
		std::cout << a.pt.evtype[i] << endl << a.pt.sttype[i] << endl;
	}
	for (int i = 0; i < a.PartitionAttribute.size(); i++)
	{
		std::cout << a.PartitionAttribute[i] << endl;
	}
	for (int i = 0; i < a.morePartitionAttribute.size(); i++)
	{
		std::cout << a.morePartitionAttribute[i] << endl;
	}

	for (int i = 0; i < a.addPredicate.size(); i++)
	{
		for (int j = 0; j < a.addPredicate[i].size(); j++)
		{
			std::cout << a.addPredicate[i][j] << endl;
		}
	}

}
void global::parseFiletxt(vector<query>& a, string b)
{
	vector<string> fileString;
	int fileStrNum;
	read1(b, fileString, fileStrNum);
	query c;
	for (int i = 0; i < fileStrNum; i++)
	{
		int num = c.parseFastQueryLine(c, fileString[i]);
		if (num == 2)
		{
			a.push_back(c);
			vector<string> tmp;
			c.pt.evtype.swap(tmp);
			c.pt.evtype.clear();
			vector<string> tmp1;
			c.pt.streal.swap(tmp1);
			c.pt.streal.clear();
			vector<string> tmp2;
			c.pt.sttype.swap(tmp2);
			c.pt.sttype.clear();
			vector<vector<string>> tmp3;
			c.addPredicate.swap(tmp3);
			c.addPredicate.clear();
		}
	}
}
void global::printAsBit(size_t val)
{
	std::cout << bitset<sizeof(size_t) * 8>(val) << endl;
}