#include "parseData.h"
using namespace std;
global gd;
bool parseData::AllisNum(string str)
{
	for (int i = 0; i < str.size(); i++)
	{
		int tmp = (int)str[i];
		if ((tmp >= 48 && tmp <= 57) || (tmp == (int)'.'))
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}
void parseData::parseStream(string file)
{
	vector<string> fileTxt;
	int fileLineNum = 0;
	long t3 = GetTickCount64();
	gd.read1(file, fileTxt, fileLineNum);
	long t4 = GetTickCount64();

	vector<vector<string>> tokFileTxt;
	vector<string> dataName;
	for (int num = 0; num < fileLineNum; num++)    
	{
		string oneFileLine = fileTxt[num];
		vector<string> oneFileLineTxt;
		gd.Tokenize(oneFileLine, oneFileLineTxt, ",");
		if (num == 0)
		{
			for (int i = 0; i < oneFileLineTxt.size(); i++)
			{
				dataName.push_back(oneFileLineTxt[i]);
			}
			oneFileLineTxt.shrink_to_fit();
		}
		else if (num == 1)
		{
			oneFileLineTxt.shrink_to_fit();
			for (int i = 0; i < oneFileLineTxt.size(); i++)
			{
				vector<string> curtex;
				oneFileLineTxt[i].shrink_to_fit();
				curtex.push_back(oneFileLineTxt[i]);
				tokFileTxt.push_back(curtex);
			}
		}
		else
		{
			oneFileLineTxt.shrink_to_fit();
			for (int i = 0; i < oneFileLineTxt.size(); i++)
			{
				oneFileLineTxt[i].shrink_to_fit();
				tokFileTxt[i].push_back(oneFileLineTxt[i]);
			}
		}
		oneFileLineTxt.clear();
		oneFileLineTxt.shrink_to_fit();
	}
	vector <string>().swap(fileTxt);

	tag = dataName;
	int numflag = 0, txtflag = 0;
	int isnum[20] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	for (int i = 0; i < dataName.size(); i++)
	{
		if (AllisNum(tokFileTxt[i][0]))
		{
			isnum[i] = 1;
			numcor.insert(pair<int, int>(i, numflag));
			vector<double> curnn;
			numdata.push_back(curnn);
			numflag++;
		}
		else
		{
			txtcor.insert(pair<int, int>(i, txtflag));
			vector<string> curnn;
			txtdata.push_back(curnn);
			txtflag++;
		}
	}
	for (int k = 0; k < tokFileTxt.size(); k++)
	{
		if (isnum[k] == 1)
		{
			for (int i = 0; i < tokFileTxt[0].size(); i++)
			{
				numdata[numcor[k]].push_back(stod(tokFileTxt[k][i]));
			}

		}
		else
		{
			for (int i = 0; i < tokFileTxt[0].size(); i++)
			{
				txtdata[txtcor[k]].push_back(tokFileTxt[k][i]);
			}
		}
	}
	for (int i = 0; i < dataName.size(); i++)
	{
		if (dataName[i] == "eventType")
		{
			eventNum = i;
			break;
		}
	}
	vector<vector<string>>().swap(tokFileTxt);
}
