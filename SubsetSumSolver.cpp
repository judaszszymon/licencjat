#include "SubsetSumSolver.h"
#include <algorithm>
#include "cstring"
#include <functional>
#include <vector>
#include <queue>
#include <cassert>
#include <fftw3.h>
#include <set>
#include <cmath>
#include <iostream>
#include <random>

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

//bool SubsetSumSolver::solve(std::vector<int>& tab, int s){return 0;}

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


std::vector<int> Helpers::merge(std::vector<int>& tab_a, std::vector<int>& tab_b, bool (*comp)(int, int)){

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

std::vector<int> Helpers::generate(std::vector<int>& tab, int s, bool (*comp)(int, int)){
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
	std::vector<int>** t = new std::vector<int>*[2];
	t[0] = &a;
	t[1] = &b;
	for (int i = 0; i < tab.size(); i++){
		t[i%2]->push_back(tab[i]);
	}
	std::vector<int> incTab = helper.generate(a, s, increasingComparator);
	std::vector<int> decTab = helper.generate(b, s, decreasingComparator);

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

std::vector<int> Helpers::reduce(std::vector<int>& tab, int s){
	std::priority_queue<int, std::vector<int>, std::greater<int>> priorityQueue;
	std::vector<int> result;
	for (int number : tab){
		priorityQueue.push(number);
	}

	while (!priorityQueue.empty() && priorityQueue.top() <= s){
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

std::vector<std::vector<double>> tabToCharPoly(std::vector<std::pair<int, int>>& tab){
	std::vector<std::vector<double>> result;
	for(std::pair<int, int> point : tab){
		if(point.first >= result.size()){
			result.resize(point.first+1, std::vector<double>());
		}
		if(point.second >= result[point.first].size()){
			result[point.first].resize(point.second+1, 0);
		}
		result[point.first][point.second] = 1;
	}
	return result;
}

void normalize2dTab(std::vector<std::vector<double>>& tabA, std::vector<std::vector<double>>& tabB){
	int firstDim = std::max(tabA.size(), tabB.size());
	int secondDim = 0;
	for(std::vector<double>& t : tabA){
		secondDim = std::max<int>(secondDim, t.size());
	}
	for(std::vector<double>& t : tabB){
		secondDim = std::max<int>(secondDim, t.size());
	}

	tabA.resize(2*firstDim);
	tabB.resize(2*firstDim);

	for(std::vector<double>& t : tabA){
		t.resize(2*secondDim);
	}
	for(std::vector<double>& t : tabB){
		t.resize(2*secondDim);
	}

}

std::vector<int> charPolyToTab(std::vector<double>& tab, int u){
	std::vector<int> result;
	int end = std::min<int>(tab.size(), u);
	for(int i = 0; i < end; i++){
		if(tab[i] > 0.5 * tab.size()){
			result.push_back(i);
		}
	}
	return result;
}

std::vector<std::pair<int, int>> charPolyToTab(std::vector<std::vector<double>>& tab, int scale){
	std::vector<std::pair<int, int>> result;
	for(int i = 0; i < tab.size(); i++){
		for(int j = 0; j < tab[i].size(); j++){
			if(tab[i][j] > 0.5 * scale){
				result.push_back(std::pair<int, int>(i,j));
			}
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

void putToComplex(std::vector<std::vector<double>>& input, fftw_complex* output){
	int i = 0;
	for(std::vector<double>& vect : input){
		for(double number : vect){
			output[i][0] = number;
			output[i++][1] = 0;
		}
	}
}

void getFromComplex(fftw_complex* input, std::vector<double>& output){
	for (int i = 0; i < output.size(); i++){
		output[i] = input[i][0];
	}
}
void getFromComplex(fftw_complex* input, std::vector<std::vector<double>>& output){
	int i = 0;
	int p = 0;
	for(std::vector<double>& vect : output){
		for(i = 0; i < vect.size(); i++){
			vect[i] = input[p++][0];
		}
	}
}

void addVect(fftw_complex* u, fftw_complex* w, fftw_complex* v, int n){
	for (int i = 0; i < n; i++){
		double a = u[i][0], b = u[i][1], c = w[i][0], d = w[i][1];
		v[i][0] = a*c - b*d;
		v[i][1] = a*d + b*c;

	}
}

std::vector<int> Helpers::fftSumset(std::vector<int>& tabA, std::vector<int>& tabB, int u){
	std::vector<double> polyCharA = tabToCharPoly(tabA);
	std::vector<double> polyCharB = tabToCharPoly(tabB);
	std::vector<double> polyCharC;
	int degree = std::max(polyCharA.size(), polyCharB.size()) * 2;

	int i = 1;
	while(i < degree){
		i += i;
	}
	degree = i;

	polyCharA.resize(degree, 0);
	polyCharB.resize(degree, 0);
	polyCharC.resize(degree, 0);

	fftw_complex *inA, *inB, *outA, *outB;
	fftw_plan planA, planB, planC;
	inA = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * degree);
	inB = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * degree);
	outA = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * degree);
	outB = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * degree);

	fftw_import_wisdom_from_filename("wisdom.wis");
	planA = fftw_plan_dft_1d(degree, inA, outA, FFTW_FORWARD, FFTW_MEASURE);
	planB = fftw_plan_dft_1d(degree, inB, outB, FFTW_FORWARD, FFTW_MEASURE);
	planC = fftw_plan_dft_1d(degree, inA, outA, FFTW_BACKWARD, FFTW_MEASURE);
	fftw_export_wisdom_to_filename("wisdom.wis");

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
	return charPolyToTab(polyCharC, u);
}

std::vector<std::pair<int, int>> Helpers::fftSumset2d(std::vector<std::pair<int, int>>& tabA,
		std::vector<std::pair<int, int>>& tabB, int u, int v){


	std::vector<std::vector<double>> polyCharA = tabToCharPoly(tabA);
	std::vector<std::vector<double>> polyCharB = tabToCharPoly(tabB);
	std::vector<std::vector<double>> polyCharC;
	normalize2dTab(polyCharA, polyCharB);
	int degreeX = polyCharA.size();
	int degreeY = polyCharA[0].size();

	polyCharC.resize(degreeX, std::vector<double>(degreeY, 0));

	fftw_complex *inA, *inB, *outA, *outB;
	fftw_plan planA, planB, planC;
	inA = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * degreeX * degreeY);
	inB = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * degreeX * degreeY);
	outA = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * degreeX * degreeY);
	outB = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * degreeX * degreeY);

	planA = fftw_plan_dft_2d(degreeX, degreeY, inA, outA, FFTW_FORWARD, FFTW_ESTIMATE);
	planB = fftw_plan_dft_2d(degreeX, degreeY, inB, outB, FFTW_FORWARD, FFTW_ESTIMATE);
	planC = fftw_plan_dft_2d(degreeX, degreeY, inA, outA, FFTW_BACKWARD, FFTW_ESTIMATE);

	putToComplex(polyCharA, inA);
	putToComplex(polyCharB, inB);

	fftw_execute(planA);
	fftw_execute(planB);

	addVect(outA, outB, inA, degreeX*degreeY);

	fftw_execute(planC);
	fftw_destroy_plan(planA);
	fftw_destroy_plan(planB);
	fftw_destroy_plan(planC);


	getFromComplex(outA, polyCharC);
	fftw_free(inA);
	fftw_free(inB);
	fftw_free(outA);
	fftw_free(outB);
	return charPolyToTab(polyCharC, degreeX*degreeY);



}


std::pair<std::vector<int>, std::vector<int>> KoiliarisXuSolver::parseMultiset(std::vector<int>& tab){
	std::sort(tab.begin(), tab.end());
	std::vector<int> results[2];
	for(int i = 0; i < tab.size(); i++){
		results[i%2].push_back(tab[i]);
	}
	return std::pair<std::vector<int>, std::vector<int>>(results[0], results[1]);
}


std::vector<int> KoiliarisXuSolver::recursiveSolveSet(std::vector<int>& tab, int u){
	if(tab.size() == 0){
		return tab;
	}
	if(tab.size() == 1){
		std::vector<int> res;
		res.push_back(0);
		res.push_back(tab[0]);
		return res;
	}

	if (tab.size() < 20){
		return helper.generate(tab, u, increasingComparator);
	}
	std::vector<int> parts[2];
	for(int i = 0; i < tab.size(); i++){
		parts[i%2].push_back(tab[i]);
	}

	std::vector<int> sumsets[2];
	for(int i = 0; i < 2; i++){
		sumsets[i] = recursiveSolveSet(parts[i], u);
	}
	return helper.fftSumset(sumsets[0], sumsets[1], u);
}

std::vector<std::vector<int>> KoiliarisXuSolver::logPartition(std::vector<int>& tab, int r0){
	assert(r0 > 0);
	std::vector<std::vector<int>> result;
	result.push_back(std::vector<int>());
	std::sort(tab.begin(), tab.end());
	auto it = tab.begin();
	while(it != tab.end()){
		int curValue = *it;
		if (curValue > r0){
			r0 *= 2;
			result.push_back(std::vector<int>());
			continue;
		}
		result.back().push_back(curValue);
		it++;
	}
	return result;
}

std::vector<std::pair<int, int>> KoiliarisXuSolver::lemma_2_8(std::vector<int>& tab, int alpha){
	if(tab.size() == 0){
		return std::vector<std::pair<int, int>>(1, std::pair<int, int>(0, 0));
	}

	if(tab.size() == 1){
		std::vector<std::pair<int, int>> result;
		result.push_back(std::pair<int, int>(0, 0));
		result.push_back(std::pair<int, int>(tab[0], 1));
		return result;
	}

	assert(std::is_sorted(tab.begin(), tab.end()));
	std::vector<int> lower, upper;

	int i = 0;
	int x = tab.front();
	int l = tab.back() - x;

	for (i = 0; i < tab.size()/2; i++){
		lower.push_back(tab[i]);
	}
	for(; i < tab.size(); i++){
		upper.push_back(tab[i]);
	}

	auto L = lemma_2_8(lower, alpha);
	auto R = lemma_2_8(upper, alpha);

	return lemma_2_7(L, R, x, l, alpha);
}

std::pair<int, int> fScale(std::pair<int, int>& ij, int x){
	return std::pair<int, int>(ij.first - x * ij.second, ij.second);
}

std::pair<int, int> fScaleInv(std::pair<int, int>& ij, int x){
	return std::pair<int, int>(ij.first + x * ij.second, ij.second);
}

std::vector<std::pair<int, int>> KoiliarisXuSolver::lemma_2_7(std::vector<std::pair<int, int>>& tabA,
		std::vector<std::pair<int, int>>& tabB, int x, int l, int alpha){
	std::vector<std::pair<int, int>> X, Y;
	for(auto& p : tabA){
		X.push_back(fScale(p, x));
	}
	for(auto& p : tabB){
		Y.push_back(fScale(p, x));
	}

	auto XY = helper.fftSumset2d(X, Y, l*alpha, alpha);
	std::vector<std::pair<int, int>> Z;
	for(auto& p: XY){
		if(p.first <= l * alpha && p.second <= alpha){
			Z.push_back(fScaleInv(p, x));
		}
	}
	return Z;
}

std::vector<int> KoiliarisXuSolver::lemma_2_9(std::vector<int> tab, int x, int l, int u){
	auto S = lemma_2_8(tab, u/x);
	std::vector<int> result;
	std::set<int> gotNumbers;
	for(auto& p : S){
		if(p.first <= u && !gotNumbers.count(p.first)){
			result.push_back(p.first);
			gotNumbers.insert(p.first);
		}
	}

	return result;
}


std::vector<std::vector<int>> KoiliarisXuSolver::lemma_2_11(std::vector<int> tab, int r0, int u){
	auto partition = logPartition(tab, r0);
	std::vector<std::vector<int>> result;
	int l = r0+1;
	int r = 2*r0;

	result.push_back(recursiveSolveSet(partition[0], u));
	for(int i = 1; i < partition.size(); i++){ // not for l == 0
		std::vector<int> sumset = lemma_2_9(partition[i], l, r, u);
		l = r+1;
		r *= 2;
		result.push_back(sumset);
	}
	return result;
}

int getR0(int u, int n, double c = 1){
	double sqrt_n = sqrt(n);
	double crt_u = pow(u, 1.0 / 3.0);
	if(crt_u < c*sqrt_n){
		return (int) pow(u, 2.0 / 3.0) + 1;
	} else {
		return (int) (u / sqrt_n) + 1;
	}
}

std::vector<int> KoiliarisXuSolver::theorem_2_2(std::vector<int> tab, int u){
	int r0 = getR0(u, tab.size());
	auto sumParts = lemma_2_11(tab, r0, u);

	auto P = sumParts[0];
	for(int i = 1; i < sumParts.size(); i++){
		P = helper.fftSumset(P, sumParts[i], u);
	}
	return P;
}

std::vector<int> KoiliarisXuSolver::generateViaTheorem_2_2(std::vector<int>& tab, int u){
	std::vector<int> partition[2];
	int i = 0;
	for(i = 0; i < tab.size(); i++){
		partition[i%2].push_back(tab[i]);
	}
	auto sumA = theorem_2_2(partition[0], u);
	auto sumB = theorem_2_2(partition[1], u);

	return helper.fftSumset(sumA, sumB, u);
}

bool shouldRecursive(std::vector<int>& tab, int s){
	return false;
	//TODO provide implementation
}

bool KoiliarisXuSolver::solve(std::vector<int>& tab, int s){
	tab = helper.reduce(tab, s);
	std::vector<int> sumsets;
	if(shouldRecursive(tab, s)){
		sumsets = recursiveSolveSet(tab, s);

	} else{
		sumsets = generateViaTheorem_2_2(tab, s);
	}
	for(int i : sumsets){
		if(i==s){
			return true;
		}
	}
	return false;
}

std::vector<std::vector<int>> BringmannSolver::randomPartition(std::vector<int> Z, int numberOfBuckets){
	std::vector<std::vector<int>> result(numberOfBuckets);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, numberOfBuckets-1);

	for(int number : Z){
		int bucketNumber = dis(gen);
		result[bucketNumber].push_back(number);
	}
	return result;
}

std::vector<int> BringmannSolver::mergeTo(std::vector<int>& left, std::vector<int>& right){
	assert(std::is_sorted(left.begin(), left.end()));
	assert(std::is_sorted(right.begin(), right.end()));
	std::vector<int> result;

	int l = 0, r = 0;
	while (l < left.size() && r < right.size()){
		if(left[l] < right[r]){
			result.push_back(left[l++]);
		} else{
			result.push_back(right[r++]);
		}
	}
	while (l < left.size() ){
		result.push_back(left[l++]);
	}
	while (r < right.size() ){
		result.push_back(right[r++]);
	}
	return result;
}



std::vector<int> BringmannSolver::colorCoding(std::vector<int> Z, int t, int k, double delta){
	int end = std::log(1.0 / delta) / std::log(4.0 / 3.0);
	end++;
	std::vector<int> result;
	for(int i = 0; i < end; i++){
		auto partition = randomPartition(Z, k*k);
		std::vector<int> Sj;
		for (std::vector<int>& bucket : partition){
			Sj = helper.fftSumset(Sj, bucket, t);
		}
		result = mergeTo(result, Sj);
	}
	return result;
}

std::vector<int> BringmannSolver::colorCodingLayer(std::vector<int> Z, int t, int l, double delta){
	if(l < std::log(l/delta) / std::log(2)){
		return colorCoding(Z, t, l, delta);
	}
	double m = l / std::log(l/delta);
	int mSquare = 1;
	while (mSquare <= m){
		mSquare *= 2;
	}

	auto Zpartition = randomPartition(Z, m);
	double gamma = 6 * std::log(l/delta) / std::log(2.0);
	std::vector<std::vector<int>> S;
	for(int j = 0; j < m; j++){
		S[j] = colorCoding(Zpartition[j], 2*gamma*t/l, gamma, delta/l);
	}

	for(int h = 1; h < m; h*=2){
		for(int j = 0; j + h < m; j += 2*h){
			S[j] = helper.fftSumset(S[j], S[j+h], h*2*gamma*t/l);
		}
	}

	return S[0];
}

std::vector<std::vector<int>> BringmannSolver::logSplit(std::vector<int>& tab, int t){
	std::vector<std::vector<int>> result;

	for(int el : tab){
		if(el > t){
			continue;
		}

		int index = std::floor(std::log(static_cast<double>(t)/el));
		if(result.size() <= index){
			result.resize(index);
		}
		result[index].push_back(el);
	}

	return result;
}

std::vector<int> BringmannSolver::fasterSubsetSum(std::vector<int> Z, int t, double delta){
	std::vector<int> result;
	int n = Z.size();

	std::vector<std::vector<int>> Zsplit = logSplit(Z, t);
	double deltaLogn = delta / std::ceil((std::log(n) / std::log(2)));
	for(int i = 0 ; i < Zsplit.size(); i++){
		auto ts = colorCodingLayer(Zsplit[i], t, 1 << i, delta);
		result = helper.fftSumset(result, ts, t);
	}
	return result;
}



