#include "SubsetSumSolver.h"
#include "Runner.h"
#include <iostream>
#include <vector>
#include <utility>
#include <fftw3.h>


int main(){
	fftw_import_wisdom_from_filename("wisdom.wis");
	KoiliarisXuSolver solver;
	TestRunner runner;
	runner.compare();
	fftw_export_wisdom_to_filename("wisdom.wis");

	return 0;
}
