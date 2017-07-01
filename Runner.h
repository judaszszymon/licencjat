#ifndef RUNNER_H_
#define RUNNER_H_
#include <vector>
#include <tuple>
#include "SubsetSumSolver.h"

class TestLoader{
public:
	std::vector<std::tuple<std::vector<int>, int, char*>> loadTests();
private:
	std::tuple<std::vector<int>, int, char*> loadTestFromFile(char* filename);

};


class TestRunner{
public:
	void compare();
private:
	void compareSolversOnOneTest(std::tuple<std::vector<int>, int, char*> testInstance);
	std::pair<std::vector<SubsetSumSolver>, std::vector<char*>> prepareSolvers();
};



#endif /* RUNNER_H_ */
