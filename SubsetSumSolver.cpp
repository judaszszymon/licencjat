#include "SubsetSumSolver.h"
#include <algorithm>
#include "cstring"
SubsetSumSolver::~SubsetSumSolver(){}
bool SubsetSumSolver::solve(int* tab, int n, int s){return 0;}

bool DpSolver::solve(int* tab, int n, int s){
	int* currentTab = new int[s+1];
	int* prevTab = new int[s+1];
	int* tmp;
	std::memset(currentTab, 0, sizeof(int) * (s+1));
	std::memset(prevTab, 0, sizeof(int) * (s+1));
	prevTab[0] = 1;

	for(int i = 0; i < n; i++){
		int number = tab[i];
		for(int p = 0; p < s; p++){
			if(prevTab[p]){
				currentTab[p] = 1;
				if(number + p <= s){
					currentTab[number + p] = 1;
				}
			}
		}
		if(currentTab[s]){
			delete [] currentTab;
			delete [] prevTab;
			return 1;
		}
		std::swap(currentTab, prevTab);
	}
	delete [] currentTab;
	delete [] prevTab;
	return 0;
}

bool DpSolverPlus::solve(int* tab, int n, int s){
	int* currentTab = new int[s+1];
	int* prevTab = new int[s+1];
	int* tmp;
	std::sort(tab, tab+n);
	std::memset(currentTab, 0, sizeof(int) * (s+1));
	std::memset(prevTab, 0, sizeof(int) * (s+1));
	prevTab[0] = 1;

	for(int i = 0; i < n; i++){
		int number = tab[i];
		for(int p = 0; p < s; p++){
			if(number + p > s){
				break;
			}
			if(prevTab[p]){
				currentTab[number + p] = 1;
			}
		}
		if(currentTab[s]){
			delete [] currentTab;
			delete [] prevTab;
			return 1;
		}
		memcpy(prevTab, currentTab, sizeof(int) * (s+1));
	}

	delete [] currentTab;
	delete [] prevTab;
	return 0;
}
