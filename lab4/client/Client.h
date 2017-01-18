#pragma once
#include "CPipe.h"
#include <random>
#include <string>
#include<math.h> 
#include <ctime>

class Client
{
public:
	Client(const std::string & name);

private:
	static float CalculatePi(size_t nIterations);
private:
	std::string m_name;
};