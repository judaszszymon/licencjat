#include "Runner.h"
#include <vector>
#include <utility>
#include "SubsetSumSolver.h"
#include <iostream>
#include <fstream>
#include <tuple>
#include <cassert>
#include <chrono>

std::vector<std::tuple<std::vector<int>, int, char*>> TestLoader::loadTests(){
	std::vector<std::tuple<std::vector<int>, int, char*>> result;
	std::vector<char*> filenamesVect;

//	filenamesVect.push_back((char*)"tests/yes_5_5.txt");
	filenamesVect.push_back((char*)"tests/yes_25_5.txt");
	filenamesVect.push_back((char*)"tests/yes_25_20.txt");
	filenamesVect.push_back((char*)"tests/yes_50_10.txt");
	filenamesVect.push_back((char*)"tests/yes_50_40.txt");
	filenamesVect.push_back((char*)"tests/yes_75_15.txt");
	filenamesVect.push_back((char*)"tests/yes_75_60.txt");

	filenamesVect.push_back((char*)"tests/yes_100_20.txt");
	filenamesVect.push_back((char*)"tests/yes_100_80.txt");
	filenamesVect.push_back((char*)"tests/yes_125_25.txt");
	filenamesVect.push_back((char*)"tests/yes_125_100.txt");
	filenamesVect.push_back((char*)"tests/yes_150_30.txt");
	filenamesVect.push_back((char*)"tests/yes_150_120.txt");
	filenamesVect.push_back((char*)"tests/yes_175_35.txt");
	filenamesVect.push_back((char*)"tests/yes_175_140.txt");

	filenamesVect.push_back((char*)"tests/yes_200_40.txt");
	filenamesVect.push_back((char*)"tests/yes_200_160.txt");
	filenamesVect.push_back((char*)"tests/yes_250_50.txt");
	filenamesVect.push_back((char*)"tests/yes_250_200.txt");

	filenamesVect.push_back((char*)"tests/yes_300_60.txt");
	filenamesVect.push_back((char*)"tests/yes_300_240.txt");
	filenamesVect.push_back((char*)"tests/yes_350_70.txt");
	filenamesVect.push_back((char*)"tests/yes_350_280.txt");

	filenamesVect.push_back((char*)"tests/yes_400_80.txt");
	filenamesVect.push_back((char*)"tests/yes_400_320.txt");
	filenamesVect.push_back((char*)"tests/yes_450_90.txt");
	filenamesVect.push_back((char*)"tests/yes_450_360.txt");

	filenamesVect.push_back((char*)"tests/yes_500_100.txt");
	filenamesVect.push_back((char*)"tests/yes_500_400.txt");
	filenamesVect.push_back((char*)"tests/yes_550_110.txt");
	filenamesVect.push_back((char*)"tests/yes_550_440.txt");

	filenamesVect.push_back((char*)"tests/yes_600_120.txt");
	filenamesVect.push_back((char*)"tests/yes_600_480.txt");
	filenamesVect.push_back((char*)"tests/yes_650_130.txt");
	filenamesVect.push_back((char*)"tests/yes_650_520.txt");

	filenamesVect.push_back((char*)"tests/yes_700_140.txt");
	filenamesVect.push_back((char*)"tests/yes_700_560.txt");
	filenamesVect.push_back((char*)"tests/yes_750_150.txt");
	filenamesVect.push_back((char*)"tests/yes_750_600.txt");

	filenamesVect.push_back((char*)"tests/yes_800_160.txt");
	filenamesVect.push_back((char*)"tests/yes_800_640.txt");
	filenamesVect.push_back((char*)"tests/yes_850_170.txt");
	filenamesVect.push_back((char*)"tests/yes_850_680.txt");

	filenamesVect.push_back((char*)"tests/yes_900_180.txt");
	filenamesVect.push_back((char*)"tests/yes_900_720.txt");
	filenamesVect.push_back((char*)"tests/yes_950_190.txt");
	filenamesVect.push_back((char*)"tests/yes_950_760.txt");

	for(int i = 0; i < filenamesVect.size(); i++){
		result.push_back(loadTestFromFile(filenamesVect[i]));
	}
	return result;
}

/*
 * Data format
 * First line consists of n and s:
 * n - amount of numbers, s - desired sum
 * Second line consists of n positive intigers separated by spaces
 */
std::tuple<std::vector<int>, int, char*> TestLoader::loadTestFromFile(char* filename){
	std::ifstream fileStream;
	fileStream.open(filename, std::ios::in);
	int n, s;
	fileStream >> n >> s;
	std::vector<int> result;

	for (int i = 0; i < n; i++){
		int x;
		fileStream >> x;
		result.push_back(x);
	}
	fileStream.close();
	return std::tuple<std::vector<int>, int, char*>(result, s, filename);
}

std::pair<std::vector<SubsetSumSolver*>, std::vector<char*>> TestRunner::prepareSolvers(){
	std::vector<SubsetSumSolver*> solversInstances;
	std::vector<char*> solverNames;

	solversInstances.push_back(new DpSolver());
	solverNames.push_back((char*) "dynamic programming solver");

//	solversInstances.push_back(new DpSolverPlus());
//	solverNames.push_back((char*) "dynamic programming solver plus");

//	solversInstances.push_back(new TwoListSolver());
//	solverNames.push_back((char*) "two list solver");

	solversInstances.push_back(new KoiliarisXuSolver());
	solverNames.push_back((char*) "Koiliaris Xu Solver");


//	solversInstances.push_back(new BringmannSolver());
//	solverNames.push_back((char*) "Bringmann Solver");

	assert(solverNames.size() == solversInstances.size());

	return std::pair<std::vector<SubsetSumSolver*>, std::vector<char*>>(solversInstances, solverNames);
}


void TestRunner::compareSolversOnOneTest(std::tuple<std::vector<int>, int, char*> testInstance){
	std::cout << "Running on test: " << std::get<2>(testInstance) << std::endl;



	std::pair<std::vector<SubsetSumSolver*>, std::vector<char*>> solversTuple = prepareSolvers();
	std::vector<SubsetSumSolver*> solvers = std::get<0>(solversTuple);
	std::vector<char*> solversNames = std::get<1>(solversTuple);
	std::vector<SubsetSumSolver*>::iterator solverIt = solvers.begin();
	std::vector<char*>::iterator solverNameIt = solversNames.begin();
	for(; solverIt != solvers.end() && solverNameIt != solversNames.end(); solverIt++, solverNameIt++){
		std::cout << "Testing solver: " << *solverNameIt << std::endl;
		std::vector<int> tab = std::get<0>(testInstance);
		int s = std::get<1>(testInstance);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		bool ok = (*solverIt)->solve(tab, s);
		std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
		std::cout << "Took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
				<<" ms" << "ans: " << ok << std::endl;
	}

}

void TestRunner::compare(){
	std::vector<std::tuple<std::vector<int>, int, char*>> tests = TestLoader().loadTests();
	for(std::tuple<std::vector<int>, int, char*> test : tests){
		compareSolversOnOneTest(test);
	}
}


