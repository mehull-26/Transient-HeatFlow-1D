#pragma once
#include <vector>
using namespace std;

class MATRIX
{
private:
	vector<vector<double>> data;
	int Drows, Dcolumns;

public:
	MATRIX(int rows, int columns) : data(rows, vector<double>(columns)) { Drows = rows; Dcolumns = columns; }

	MATRIX(int rows, int columns, vector<vector<double>> matrix) : data(rows, vector<double>(columns))
	{
		Drows = rows;
		Dcolumns = columns;

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				data[i][j] = matrix[i][j];
			}
		}
	}

	vector<double>& operator[](int i) { return data[i]; }
	const vector<double>& operator[](int i) const { return data[i]; }

	//MATRIX operator=(MATRIX& other)
	//{
	//	Drows = other.Drows;
	//	Dcolumns = other.Dcolumns;
	//	data = other.data;

	//	return *this;
	//}

	MATRIX operator*(MATRIX& other)
	{
		int rows = Drows;
		int columns = other.Dcolumns;
		MATRIX result(rows, columns);

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				for (int k = 0; k < other.data.size(); k++)
				{
					result[i][j] += data[i][k] * other[k][j];
				}
			}
		}

		return result;
	}
};

MATRIX GS_solution(int dimension, MATRIX Left_Matrix, MATRIX Right_Matrix, double threshold);
