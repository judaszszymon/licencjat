#ifndef SUBSETSUMSOLVER_H_
#define SUBSETSUMSOLVER_H_

#include <vector>
#include <climits>

class Helpers{
public:
	std::vector<int> reduce(std::vector<int>& tab, int s);
	std::vector<int> fftSumset(std::vector<int>& tabA, std::vector<int>& tabB, int u);
	std::vector<std::pair<int, int>> fftSumset2d(std::vector<std::pair<int, int>>& tabA, std::vector<std::pair<int, int>>& tabB, int u, int v);

	// from two list
	std::vector<int> generate(std::vector<int>& tab, int s, bool (*comp)(int, int));
	std::vector<int> merge(std::vector<int>& tab_a, std::vector<int>& tab_b, bool (*comp)(int, int));

};

class SubsetSumSolver{
public:
	virtual bool solve(std::vector<int>& tab, int s) = 0;
	virtual ~SubsetSumSolver();
	Helpers helper;
};


class DpSolver : public SubsetSumSolver{
public:
	virtual bool solve(std::vector<int>& tab, int s);
};
class DpSolverPlus : public SubsetSumSolver{
public:
	virtual bool solve(std::vector<int>& tab, int s);
};
class TwoListSolver: public SubsetSumSolver{
public:
	virtual bool solve(std::vector<int>& tab, int s);
private:

};


class KoiliarisXuSolver : public SubsetSumSolver{
public:
	virtual bool solve(std::vector<int>& tab, int s);
private:
	std::pair<std::vector<int>, std::vector<int>> parseMultiset(std::vector<int>& tab);
	std::vector<int> recursiveSolveSet(std::vector<int>& tab, int u);
	std::vector<int> generateViaTheorem_2_2(std::vector<int>& tab, int u);
	std::vector<std::vector<int>> logPartition(std::vector<int>& tab, int r0);
	std::vector<std::pair<int, int>> lemma_2_8(std::vector<int>& tab, int alpha);
	std::vector<std::pair<int, int>> lemma_2_7(std::vector<std::pair<int, int>>& tabA, std::vector<std::pair<int, int>>& tabB, int x, int l, int alpha);
	std::vector<int> lemma_2_9(std::vector<int> tab, int x, int l, int u);
	std::vector<std::vector<int>> lemma_2_11(std::vector<int> tab, int r0, int u);
	std::vector<int> theorem_2_2(std::vector<int> tab, int u);
};


class BringmannSolver : public SubsetSumSolver{
public:
	virtual bool solve(std::vector<int>& tab, int s);
	bool solve (std::vector<int>& tab, int s, double delta);
private:
	std::vector<int> colorCoding(std::vector<int> Z, int t, int k, double delta);
	std::vector<int> colorCodingLayer(std::vector<int> Z, int t, int l, double delta);
	std::vector<int> fasterSubsetSum(std::vector<int> Z, int t, double delta);
	std::vector<std::vector<int>> randomPartition(std::vector<int> Z, int numberOfBuckets);
	std::vector<int> mergeTo(std::vector<int>& left, std::vector<int>& right);
};

#endif /* SUBSETSUMSOLVER_H_ */
