#include "CMatrix.h"

Matrix CMatrix::m_result = Matrix();

/*
-93 78 -3
42 -30 6
-3 6 -3
*/


Matrix CMatrix::CalculateCofactorMatrix(const Matrix & sourceMatrix, unsigned i, unsigned j)
{
	Matrix resultMatrix = Matrix(sourceMatrix);
	resultMatrix.erase(resultMatrix.begin() + i);
	for (size_t indexI = 0; indexI < resultMatrix.size(); ++indexI)
	{
		resultMatrix[indexI].erase(resultMatrix[indexI].begin() + j);
	}
	return resultMatrix;
}

void CMatrix::Print(Matrix matrix)
{
	std::cout << "Matrix: " << std::endl;

	for (size_t i = 0; i < matrix.size(); i++)
	{
		for (size_t j = 0; j < matrix.size(); j++)
		{
			std::cout << std::fixed << std::setprecision(3) << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

double CMatrix::CalculateDeterminant(const Matrix & matrix) //gauss method
{
	if (matrix.size() == 2)
	{
		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	}

	int l;
	double result;

	double sum11 = 1, sum12 = 0, sum21 = 1, sum22 = 0;
	for (int i = 0; i < matrix.size(); i++)
	{
		sum11 = 1;
		l = 2 * matrix.size() - 1 - i;
		sum21 = 1;
		for (int j = 0; j < matrix.size(); j++)
		{
			sum21 *= matrix[j][l%matrix.size()];
			l--;
			sum11 *= matrix[j][(j + i) % (matrix.size())];
		}
		sum22 += sum21;
		sum12 += sum11;
	}
	result = sum12 - sum22;
	return result;
}

void CMatrix::FillMatrixWithCofactorValues()
{
	m_result = Matrix(m_matrix.size(), std::vector<double>(m_matrix.size()));
	const size_t MATRIX_SIZE = m_matrix.size();

	for (size_t i = 0; i < MATRIX_SIZE; ++i)
	{
		for (size_t j = 0; j < MATRIX_SIZE; ++j)
		{
			Matrix cofactorMatrix = CalculateCofactorMatrix(m_matrix, i, j);
			double cofactorDet = CalculateDeterminant(cofactorMatrix);
			double resultValue = cofactorDet;
			if ((i + j) % 2)
			{
				resultValue = -resultValue;
			}
			m_result[i][j] = resultValue;
		}
	}
}

Matrix CMatrix::LoadMatrix(size_t dimension)
{
	Matrix matrix;
	for (size_t i = 1; i <= dimension; ++i)
	{
		matrix.push_back(std::vector<double>());
		for (size_t j = 1; j <= dimension; ++j)
		{
			matrix[i - 1].push_back(j);
		}
	}
	return matrix;
}