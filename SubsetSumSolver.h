#ifndef SUBSETSUMSOLVER_H_
#define SUBSETSUMSOLVER_H_

#include <vector>
#include <climits>

class SubsetSumSolver{
public:
	virtual bool solve(std::vector<int>& tab, int s);
	virtual ~SubsetSumSolver();
};


class DpSolver : public SubsetSumSolver{
public:
	bool solve(std::vector<int>& tab, int s);
};
class DpSolverPlus : public SubsetSumSolver{
public:
	bool solve(std::vector<int>& tab, int s);
};
class TwoListSolver: public SubsetSumSolver{
public:
	bool solve(std::vector<int>& tab, int s);
private:
	std::vector<int> generate(std::vector<int>& tab, int s, bool (*comp)(int, int));
	std::vector<int> merge(std::vector<int>& tab_a, std::vector<int>& tab_b, bool (*comp)(int, int));
};

class Helpers{
public:
	std::vector<int> reduce(std::vector<int>& tab);
	std::vector<int> fftSumset(std::vector<int>& tabA, std::vector<int>& tabB);
	std::vector<std::pair<int, int>> fftSumset2d(std::vector<std::pair<int, int>>& tabA, std::vector<std::pair<int, int>>& tabB, int u, int v);

};

class KoiliarisXuSolver : public SubsetSumSolver{
public:
	bool solve(std::vector<int>& tab, int s);
private:
	std::pair<std::vector<int>, std::vector<int>> parseMultiset(std::vector<int> tab);
	std::vector<int> recursiveSolveSet(std::vector<int> tab);
	std::vector<std::vector<int>> logPartition(std::vector<int> tab, int r0);
	Helpers helper;
};

#endif /* SUBSETSUMSOLVER_H_ */
