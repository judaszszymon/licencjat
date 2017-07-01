#include "SubsetSumSolver.h"
#include <algorithm>
#include "cstring"
#include <functional>
#include <vector>
SubsetSumSolver::~SubsetSumSolver(){}
bool SubsetSumSolver::solve(std::vector<int>& tab, int s){return 0;}

bool DpSolver::solve(std::vector<int>& tab, int s){
	std::vector<int> currentTab;
	std::vector<int> prevTab;
	std::vector<int> tmp;

	std::sort(tab.begin(), tab.end());
	currentTab.resize(s+1, 0);
	prevTab.resize(s+1, 0);
	prevTab[0] = 1;

	for(int i = 0; i < tab.size(); i++){
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
			return 1;
		}
		std::swap(currentTab, prevTab);
	}
	return 0;
}

bool DpSolverPlus::solve(std::vector<int>& tab, int s){
	std::vector<int> currentTab;
	std::vector<int> prevTab;
	std::vector<int> tmp;

	std::sort(tab.begin(), tab.end());
	currentTab.resize(s+1, 0);
	prevTab.resize(s+1, 0);
	prevTab[0] = 1;

	for(int i = 0; i < tab.size(); i++){
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
			return 1;
		}
		prevTab = currentTab;
	}

	return 0;
}


std::vector<int> TwoListSolver::merge(std::vector<int>& tab_a, std::vector<int>& tab_b, bool (*comp)(int, int)){

	std::vector<int> result;
	int pa, pb;
	pa = pb = 0;
	while(pa < tab_a.size() && pb < tab_b.size()){
		if(comp(tab_a[pa], tab_b[pb])){
			result.push_back(tab_a[pa++]);
		} else{
			result.push_back(tab_b[pb++]);
		}
	}
	while(pa < tab_a.size()){
		result.push_back(tab_a[pa++]);
	}
	while(pb < tab_b.size()){
		result.push_back(tab_b[pb++]);
	}
	return result;
}

std::vector<int> TwoListSolver::generate(std::vector<int>& tab, int s, bool (*comp)(int, int)){
	std::vector<int> newPart;
	std::vector<int> result, merged;
	result.push_back(0);

	for(int i = 0; i < tab.size(); i++){
		int newNumber = tab.at(i);
		for(int j = 0; j < result.size(); j++){
			newPart.push_back(result.at(j) + newNumber);
		}
		merged = merge(result, newPart, comp);
		std::swap(result, merged);
		newPart.clear();
	}

	return result;
}

bool increasingComparator(int a, int b){ return a < b;}
bool decreasingComparator(int a, int b){ return b < a;}

bool TwoListSolver::solve(std::vector<int>& tab, int s){
	std::vector<int> a, b;
	std::vector<int>* t = new std::vector<int>[2];
	t[0] = a;
	t[1] = b;
	for (int i = 0; i < tab.size(); i++){
		t[i%2].push_back(tab[i]);
	}
	std::vector<int> incTab = generate(a, s, increasingComparator);
	std::vector<int> decTab = generate(b, s, decreasingComparator);

	std::vector<int>::iterator incIt = incTab.begin();
	std::vector<int>::iterator decIt = decTab.begin();

	while(incIt != incTab.end() && decIt != decTab.end()){
		int trackedValue = *incIt + *decIt;
		if(trackedValue == s){
			return true;
		}
		if(trackedValue < s){
			incIt++;
		} else{
			decIt++;
		}
	}
	return false;

}
