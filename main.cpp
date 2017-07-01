#include "SubsetSumSolver.h"

int main(){
	DpSolver solver;
	int tab[] = {1, 2, 3};
	int n = 3;
	int s = 4;
	if(solver.solve(tab, n, s)){
		return 0;
	}
	return 1;
}
