#include "SubsetSumSolver.h"
#include <iostream>

int main(){
	DpSolver solver;
	std::vector<int> tab;
	tab.push_back(1);
	tab.push_back(2);
	tab.push_back(3);
	int s = 4;
	if(solver.solve(tab, s)){
		std::cout << "yes!";
	}
	std::cout << "no!";
	return 0;
}
