#include <fstream>
#include <string>
#include <iostream>
#include <math.h>
#include <sstream>
#include <iomanip>
#include <array>
#include <vector>
#include <windows.h>
#include "CThreadedMatrix.h"
#include <time.h>

std::vector<std::vector<double>> mtr3 = {
								{1,2,3},
								{4,5,6},
								{7,8,-9}
};

void SaveResult(const std::string & fileName = "res.txt")
{
	std::ofstream outputFile(fileName);
	
	for (size_t i = 1; i < 17; ++i)
	{
		CThreadedMatrix matrix(CThreadedMatrix::LoadMatrix(150), i);
		//CThreadedMatrix matrix(mtr3, (atoi(argv[1])));

		float firstTime = float(clock());
		matrix.FillMatrixWithCofactorValues();
		float newTime = clock();

		outputFile << i << " "<< (float(clock()) - firstTime) / (double)CLOCKS_PER_SEC << std::endl;
	}
}

int main(int argc, char* argv[])
{
	argc = 2;
	argv[1] = "1";

	if (argc != 2)
	{
		std::cout << "Error: incorrect parameters";
		return 1;
	}

    //BOOL success = SetProcessAffinityMask(GetCurrentProcess(), 1);

// 	CThreadedMatrix matrix(CThreadedMatrix::LoadMatrix(150), (atoi(argv[1])));
// 	
// 	float firstTime = float(clock());
// 	matrix.FillMatrixWithCofactorValues();
// 	float newTime = clock();
// 
// 	std::cout << "Calculation time: " << (float(clock()) - firstTime) / (double)CLOCKS_PER_SEC << std::endl;
	SaveResult();
	return 0;
}