#include "Runner.h"
#include <vector>
#include <utility>
#include "SubsetSumSolver.h"
#include <iostream>
#include <fstream>
#include <tuple>

std::vector<std::tuple<std::vector<int>, int, char*>> TestLoader::loadTests(){
	std::vector<std::tuple<std::vector<int>, int, char*>> result;
	std::vector<char*> filenamesVect;

	filenamesVect.push_back((char*)"test0");

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

std::pair<std::vector<SubsetSumSolver>, std::vector<char*>> TestRunner::prepareSolvers(){
//	std::vector<std::pair<SubsetSumSolver, char*>> result;
	std::vector<SubsetSumSolver> solversInstances;
	std::vector<char*> solverNames;

	solversInstances.push_back(DpSolver());
	solverNames.push_back((char*) "dynamic programming solver");

	solversInstances.push_back(DpSolverPlus());
	solverNames.push_back((char*) "dynamic programming solver plus");

	solversInstances.push_back(TwoListSolver());
	solverNames.push_back((char*) "two list solver");
	return std::pair<std::vector<SubsetSumSolver>, std::vector<char*>>(solversInstances, solverNames);
}


void TestRunner::compareSolversOnOneTest(std::tuple<std::vector<int>, int, char*> testInstance){



}
