#include "SubsetSumSolver.h"
#include <iostream>
#include <vector>
#include <utility>


int main(){
	Helpers helper;

	std::vector<std::pair<int, int>> tabA(4);
	tabA[0] = std::pair<int, int>(0, 0);
	tabA[1] = std::pair<int, int>(1, 0);
	tabA[2] = std::pair<int, int>(2, 0);
	tabA[3] = std::pair<int, int>(3, 0);

	std::vector<std::pair<int, int>> tabB(4);
	tabB[0] = std::pair<int, int>(0, 0);
	tabB[1] = std::pair<int, int>(0, 1);
	tabB[2] = std::pair<int, int>(0, 2);
	tabB[3] = std::pair<int, int>(0, 3);

	auto result = helper.fftSumset2d(tabA, tabB, 4, 4);
	for(std::pair<int, int> i : result){
		std::cout << i.first << " " << i.second << " " <<std::endl;
	}
	return 0;
}
