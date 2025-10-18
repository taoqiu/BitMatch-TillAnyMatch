#include "fileio.h"
using namespace std;


void loadInfo(fileio& fio)
{
	fio.loadConfig();
}
void parseInput(vector<query>& a, parseData& procData, fileio fio)
{
	global pg;
	pg.parseFiletxt(a, fio.inputQuery);
	procData.parseStream(fio.inputData);
}
void construct(global& g, query a, parseData procData, vector<vector<size_t>>& bitvector, unordered_map<string, int>& eventmap, int timeSlice)
{
	sequence s;
	s.newbitVector(g, a, procData, bitvector, eventmap, timeSlice);
}
void matching(global& g,vector<size_t>& matchResult, query a, vector<vector<size_t>> bitvector, unordered_map<string, int> eventmap, int timeSlice)
{ 
	match m;
	matchResult = m.newbitMatch(g,a, bitvector, eventmap, timeSlice);
}
void resultParse(global& g,vector<size_t> matchResult)
{
	result r;
	r.finalResult(g, matchResult);
}
void runBitparell(global& g, fileio fio)
{

	double constructTime = 0;
	double matchTime = 0;
	double parseTime = 0;
	for (int i = 0; i < fio.forNum; i++)
	{
		double totalTime = 0;
		int totalResultNum = 0;
		int totalOperationsNum = 0;
		double totalMRTime = 0;

	

		vector<query> a;
		parseData procData;
		parseInput(a, procData, fio);

		for (int j = 0; j < a.size(); j++)
		{


			vector<vector<size_t>> bitvector;
			unordered_map<string, int> eventmap;
			vector<size_t> matchResult;
			g.operations_num = 0;

			cout << "--------------------------------------------------------------------" << endl;
			cout << "The following is the matching result of Query " << j + 1 << " : " << endl << endl;
			auto start = std::chrono::high_resolution_clock::now();
			auto construct_start = std::chrono::high_resolution_clock::now();
			construct(g, a[j], procData, bitvector, eventmap, fio.timeSlice);
			auto construct_end = std::chrono::high_resolution_clock::now();
			auto construct_duration = std::chrono::duration_cast<std::chrono::milliseconds>(construct_end - construct_start).count();
			std::cout << "Construct Operation took " << construct_duration << " milliseconds." << std::endl;

			constructTime += construct_duration;

			auto out_start = std::chrono::high_resolution_clock::now();
			matching(g,matchResult, a[j], bitvector, eventmap, fio.timeSlice);
			auto out_end = std::chrono::high_resolution_clock::now();
			auto out_duration = std::chrono::duration_cast<std::chrono::microseconds>(out_end - out_start).count();
			std::cout << "Matching Operation took " << out_duration << " microseconds." << std::endl;
			std::cout << "Matching Operation numbers " << g.operations_num << std::endl;

			matchTime += out_duration;

			auto resultParse_start = std::chrono::high_resolution_clock::now();
			resultParse(g, matchResult);
			auto resultParse_end = std::chrono::high_resolution_clock::now();
			auto resultParse_duration = std::chrono::duration_cast<std::chrono::microseconds>(resultParse_end - resultParse_start).count();
			std::cout << "ResultParse Operation took " << resultParse_duration << " microseconds." << std::endl;

			parseTime += resultParse_duration;

			auto end = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
			double queryTime = (double(duration) / 1000000);

			totalTime += queryTime;
			totalResultNum += g.numresult.size();			
			totalMRTime += out_duration;


			cout << "The number of match result: " << g.numresult.size() << endl;
			cout << "The total running time of Query " << j + 1 << " : " << queryTime << endl;
			cout << "--------------------------------------------------------------------" << endl << endl;
			totalOperationsNum += g.operations_num;
			vector <int>().swap(g.numresult);

		}
		cout << "*********************************" << endl;

		cout << "The total running time for all queries: " << totalTime << endl;
		cout << "The total Match Operation time for all queries: " << totalMRTime << " microseconds." << endl;
		cout << "The total matching result number for all queries: " << totalResultNum << endl;

	}
	cout << "-----------------------------------------------£¨Contstruct Time£©" << constructTime << endl;
	cout << "===============================================£¨Matching   Time£©" << matchTime / 1000 << endl;
	cout << "===============================================£¨Parse      Time£©" << parseTime / 1000 << endl;
}
void printResult(global g, fileio fio)
{
	fio.output(g, fio);
	cin.get();
}
void start()
{
	cout << "*****************ConBitMatch*****************" << endl;
	fileio fio;
	global g;
	loadInfo(fio);
	runBitparell(g, fio);
	printResult(g, fio);
}

int main()
{
	start();
}

