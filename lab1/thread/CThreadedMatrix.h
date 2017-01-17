#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip> 
#include <windows.h>
#include "CMatrix.h"

class CThreadedMatrix : public CMatrix
{
public:
	CThreadedMatrix(const Matrix & matrix, size_t threadsCount)
		:CMatrix(matrix),
		m_threadsCount(threadsCount)
	{
		
	}
	void FillMatrixWithCofactorValues() override;
	static DWORD WINAPI CalculateCellOfResultMatrix(const LPVOID lpParam);
private:
	size_t m_threadsCount;
};