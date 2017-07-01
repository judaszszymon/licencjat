#ifndef SUBSETSUMSOLVER_H_
#define SUBSETSUMSOLVER_H_

#include <vector>

class SubsetSumSolver{
public:
	virtual bool solve(std::vector<int>& tab, int s) = 0;
	virtual ~SubsetSumSolver() = 0;
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

#endif /* SUBSETSUMSOLVER_H_ */
