#include "SubsetSumSolver.h"
#include <algorithm>
#include "cstring"
#include <functional>
#include <vector>
#include <queue>
#include <fftw3.h>

SubsetSumSolver::~SubsetSumSolver(){}

void vector_many(std::vector<int>& vect, int element, int count){
	while(count-- > 0){
		vect.push_back(element);
	}
}

void vector_many(std::priority_queue<int, std::vector<int>, std::greater<int>>& vect, int element, int count){
	while(count-- > 0){
		vect.push(element);
	}
}

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

std::vector<int> Helpers::reduce(std::vector<int>& tab){
	std::priority_queue<int, std::vector<int>, std::greater<int>> priorityQueue;
	std::vector<int> result;
	for (int number : tab){
		priorityQueue.push(number);
	}

	while (!priorityQueue.empty()){
		int topElement = priorityQueue.top();
		int topElementCount = 0;
		while(!priorityQueue.empty() && priorityQueue.top() == topElement) {
			topElementCount++;
			priorityQueue.pop();
		}
		if (topElementCount <= 2){
			vector_many(result, topElement, topElementCount);
		} else{
			if(topElementCount % 2 == 0){
				vector_many(result, topElement, 2);
				vector_many(priorityQueue, 2*topElement, (topElementCount / 2) - 1);
			} else{
				vector_many(result, topElement, 1);
				vector_many(priorityQueue, 2*topElement, (topElementCount / 2));
			}
		}
	}
	return result;
}

std::vector<double> tabToCharPoly(std::vector<int>& tab){
	std::vector<double> result;
	for(int i : tab){
		if(i >= result.size()){
			result.resize(i+1, 0);
		}
		result[i] = 1;
	}
	return result;
}

std::vector<int> charPolyToTab(std::vector<double>& tab){
	std::vector<int> result;
	for(int i = 0; i < tab.size(); i++){
		if(tab[i] > 0.5 * tab.size()){
			result.push_back(i);
		}
	}
	return result;
}

void putToComplex(std::vector<double>& input, fftw_complex* output){
	int i = 0;
	for(; i < input.size(); i++){
		output[i][0] = input[i];
		output[i][1] = 0;
	}
}

void getFromComplex(fftw_complex* input, std::vector<double>& output){
	for (int i = 0; i < output.size(); i++){
		output[i] = input[i][0];
	}
}

void addVect(fftw_complex* u, fftw_complex* w, fftw_complex* v, int n){
	for (int i = 0; i < n; i++){
		double a = u[i][0], b = u[i][1], c = w[i][0], d = w[i][1];
		v[i][0] = a*c - b*d;
		v[i][1] = a*d + b*c;

	}
}

std::vector<int> Helpers::fftSumset(std::vector<int>& tabA, std::vector<int>& tabB){
	std::vector<double> polyCharA = tabToCharPoly(tabA);
	std::vector<double> polyCharB = tabToCharPoly(tabB);
	std::vector<double> polyCharC;
	int degree = std::max(polyCharA.size(), polyCharB.size()) * 2;
	polyCharA.resize(degree, 0);
	polyCharB.resize(degree, 0);
	polyCharC.resize(degree, 0);

	fftw_complex *inA, *inB, *outA, *outB;
	fftw_plan planA, planB, planC;
	inA = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * degree);
	inB = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * degree);
	outA = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * degree);
	outB = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * degree);

	planA = fftw_plan_dft_1d(degree, inA, outA, FFTW_FORWARD, FFTW_ESTIMATE);
	planB = fftw_plan_dft_1d(degree, inB, outB, FFTW_FORWARD, FFTW_ESTIMATE);
	planC = fftw_plan_dft_1d(degree, inA, outA, FFTW_BACKWARD, FFTW_ESTIMATE);

	putToComplex(polyCharA, inA);
	putToComplex(polyCharB, inB);

	fftw_execute(planA);
	fftw_execute(planB);

	addVect(outA, outB, inA, degree);

	fftw_execute(planC);
	fftw_destroy_plan(planA);
	fftw_destroy_plan(planB);
	fftw_destroy_plan(planC);


	getFromComplex(outA, polyCharC);
	fftw_free(inA);
	fftw_free(inB);
	fftw_free(outA);
	fftw_free(outB);
	return charPolyToTab(polyCharC);
}

std::pair<std::vector<int>, std::vector<int>> KoiliarisXuSolver::parseMultiset(std::vector<int> tab){
	std::sort(tab.begin(), tab.end());
	std::vector<int> results[2];
	for(int i = 0; i < tab.size(); i++){
		results[i%2].push_back(tab[i]);
	}
	return std::pair<std::vector<int>, std::vector<int>>(results[0], results[1]);
}


std::vector<int> KoiliarisXuSolver::recursiveSolveSet(std::vector<int> tab){
	if(tab.size() == 0){
		return tab;
	}
	std::vector<int> parts[2];
	for(int i = 0; i < tab.size(); i++){
		parts[i%2].push_back(tab[i]);
	}

	std::vector<int> sumsets[2];
	for(int i = 0; i < 2; i++){
		sumsets[i] = recursiveSolveSet(parts[i]);
	}
	return helper.fftSumset(sumsets[0], sumsets[1]);
}

std::vector<std::vector<int>> KoiliarisXuSolver::logPartition(std::vector<int> tab, int r0){
	std::vector<std::vector<int>> result;
	std::sort(tab.begin(), tab.end());
	while(true){
		//TODO
		break;
	}

	return result;
}

