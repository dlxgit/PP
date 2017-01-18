#pragma once
#include "CPipeWorker.h"
#include <random>
#include <string>
#include<math.h> 
#include <ctime>
#include "CCalculator.h"


class Client
{
public:
	Client(const std::string & name);
private:
	std::string m_name;
};