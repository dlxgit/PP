#include "CCalculator.h"

float CCalculator::CalculatePi(size_t nIterations)
{
	const int MAX_VALUE = 1000;
	int inCircleCount = 0;

	std::random_device e;
	std::mt19937 gen(e());
	std::uniform_int_distribution<> range(0, MAX_VALUE);

	for (int i = 0; i < nIterations; i++)
	{
		if (MAX_VALUE * MAX_VALUE >= std::pow(range(gen), 2) + std::pow(range(gen), 2))
		{
			inCircleCount++;
		}
	}
	return inCircleCount * 4.0 / nIterations;
}