#include "utility.h"
#include <iostream>

MATRIX GS_solution(int dimension, MATRIX Left_Matrix, MATRIX Right_Matrix, double threshold)
{
	MATRIX solution(dimension, 1);

	double convergence_CKR = 1000;
	double convergence_threshold = threshold;

	int interation = 0;

	while (abs(solution[0][0] - convergence_CKR) > convergence_threshold)
	{
		convergence_CKR = solution[0][0];

		for (int i = 0; i < dimension; i++)
		{
			double sigma = 0;
			for (int j = 0; j < dimension; j++)
			{
				if (i != j)
				{
					sigma += Left_Matrix[i][j] * solution[j][0];
				}
			}
			solution[i][0] = (Right_Matrix[i][0] - sigma) / Left_Matrix[i][i];

		}

		interation++;
		//cout << "Total iterations done = " << interation << "                           \r";
	}

	return solution;
}