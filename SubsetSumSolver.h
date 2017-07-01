/*
 * SubsetSumSolver.h
 *
 *  Created on: Jun 30, 2017
 *      Author: kolesnikov
 */

#ifndef SUBSETSUMSOLVER_H_
#define SUBSETSUMSOLVER_H_

class SubsetSumSolver{
public:
	virtual bool solve(int* tab, int n, int s) = 0;
	virtual ~SubsetSumSolver() = 0;
};


class DpSolver : public SubsetSumSolver{
public:
	bool solve(int* tab, int n, int s);
};
class DpSolverPlus : public SubsetSumSolver{
public:
	bool solve(int* tab, int n, int s);
};
class TwoListSolver: public SubsetSumSolver{
public:
	bool solve(int* tab, int n, int s);
private:
	int* generateIncreasing(int* tab, int n, int s);
	int* mergeIncreasing(int* tab_a, int* tab_b, int n);
};

#endif /* SUBSETSUMSOLVER_H_ */
