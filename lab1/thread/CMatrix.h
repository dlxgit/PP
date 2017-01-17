#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip> 
#include <windows.h>


typedef std::vector<std::vector<double>> Matrix;
typedef std::pair<Matrix*, std::pair<size_t, size_t>> MatrixParameter;


class CMatrix
{
public:
	CMatrix() {};
	CMatrix(const Matrix & matrix)
		: m_matrix(matrix)
	{

	}

	static Matrix LoadMatrix(size_t dimension);
	virtual void FillMatrixWithCofactorValues();
	static void CMatrix::Print(Matrix matrix);
protected:
	static double CalculateDeterminant(const Matrix & matrix);
	static Matrix CalculateCofactorMatrix(const Matrix & sourceMatrix, unsigned i, unsigned j);
protected:
	Matrix m_matrix;
	static Matrix m_result;
};