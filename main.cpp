#include "SubsetSumSolver.h"
#include <iostream>

int main(){
	Helpers helper;

	std::vector<int> tabA(4);
	tabA[0] = 0;
	tabA[1] = 1;
	tabA[2] = 2;
	tabA[3] = 3;

	std::vector<int> tabB(4);
	tabB[0] = 0;
	tabB[1] = 10;
	tabB[2] = 20;
	tabB[3] = 30;

	auto result = helper.fftSumset(tabA, tabB);
	for(int i : result){
		std::cout << i << " ";
	}
	return 0;
}
