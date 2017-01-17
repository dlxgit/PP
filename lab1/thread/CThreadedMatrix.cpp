#include "CThreadedMatrix.h"

void CThreadedMatrix::FillMatrixWithCofactorValues()
{
	m_result = Matrix(m_matrix.size(), std::vector<double>(m_matrix.size()));
	std::vector<DWORD> threadId(m_threadsCount);
	HANDLE *threadsHandles = new HANDLE[m_threadsCount];
	const size_t ELEMENTS_COUNT = m_matrix.size() * m_matrix.size();
	std::vector<MatrixParameter> lpParameters;

	for (size_t i = 0; i < m_threadsCount; ++i)
	{
		lpParameters.push_back(std::make_pair(&m_matrix, std::make_pair(i, m_threadsCount)));
	}

 	for(size_t i = 0; i < m_threadsCount && i < ELEMENTS_COUNT; ++i)
	{
		threadsHandles[i] = CreateThread(NULL, 0, CalculateCellOfResultMatrix, &lpParameters[i], 0, &threadId[i]);
	}

	WaitForMultipleObjects(m_threadsCount, threadsHandles, true, INFINITE);
	delete[] threadsHandles;
}


void CalculateElementPosition(const MatrixParameter & param, size_t & maxCount, size_t & indexI, size_t & indexJ)
{
	Matrix * matrix = param.first;
	const size_t threadId = param.second.first + 1;
	const size_t threadsCount = param.second.second;
	const size_t MATRIX_SIZE = matrix->size();
	const size_t ELEMENTS_COUNT = MATRIX_SIZE * MATRIX_SIZE;


	size_t nElement = 0;

	if (ELEMENTS_COUNT / threadsCount < 2)
	{

		if (ELEMENTS_COUNT < threadsCount) //threads > size of matrix
		{
			maxCount = (ELEMENTS_COUNT - threadId) >= 0 ? 1 : 0;
			nElement = maxCount * (threadId - 1);
		}
		else
		{
			if (threadId <= ELEMENTS_COUNT - threadsCount) //threadId is at beginning and calculates 2 elements
			{
				maxCount = 2;
				nElement = (threadId - 1) * 2;
			}
			else //threadId is at the end and calculates 1 element
			{
				maxCount = 1;
				nElement = (ELEMENTS_COUNT - threadsCount) * 2 - 1 + threadId - (ELEMENTS_COUNT - threadsCount);
			}
		}
	}
	else
	{
		maxCount = ELEMENTS_COUNT / threadsCount;
		size_t mod = ELEMENTS_COUNT % threadsCount;

		if (mod > 0 && threadId <= ELEMENTS_COUNT - threadsCount * maxCount)
		{
			++maxCount;
		}

		size_t quantityOfMax = (ELEMENTS_COUNT - threadsCount * maxCount);
		size_t elementsBelow;
		if (quantityOfMax >= threadId)
		{
			quantityOfMax = threadId - 1;
			elementsBelow = quantityOfMax * (maxCount + 1);
		}
		else
		{
			elementsBelow = quantityOfMax * (maxCount + 1) +
				(threadId - 1 - quantityOfMax) * maxCount; //quantityofMin
		}
		
		nElement = elementsBelow;
	}
	indexI = nElement / MATRIX_SIZE;
	indexJ = nElement % MATRIX_SIZE;
}


DWORD CThreadedMatrix::CalculateCellOfResultMatrix(const LPVOID lpParam)
{
	MatrixParameter parameter = *((MatrixParameter*)lpParam);
	Matrix matrix = *parameter.first;
	size_t threadId = parameter.second.first + 1;
	size_t threadsCount = parameter.second.second;

	const size_t MATRIX_SIZE = matrix.size();

	size_t maxCount, i, j = 0;

	CalculateElementPosition(parameter, maxCount, i, j);

	for (size_t calculatedElementsCount = 0; calculatedElementsCount < maxCount; ++calculatedElementsCount)
	{
		FillCellOfMatrix(matrix, i, j);

		if (j == MATRIX_SIZE - 1) {
			++i;
			j = 0;
		}
		else
		{
			++j;
		}
	}
	ExitThread(0);
	return 0;
}