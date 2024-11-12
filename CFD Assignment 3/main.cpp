#include <fstream>
#include <iostream>
#include "utility.h"
#include <chrono>


using namespace std;
using namespace std::chrono;

void Crank_Nikolson(MATRIX& left, MATRIX& right, double time_step, double grid_points, int total_steps)
{
	double r = time_step / (grid_points * grid_points);

	ofstream fout;
	fout.open("Crank_Nikolson.txt");

	MATRIX solution(grid_points, 1);
	MATRIX prev_solution(grid_points, 1);

	for (int i = 0; i < grid_points; i++)
	{
		prev_solution[i][0] = 1;
	}

	left[0][0] = 1 + r;
	left[0][1] = -r/2;
	left[grid_points - 1][grid_points - 1] = 1 + r;
	left[grid_points - 1][grid_points - 2] = -r;

	for (int i = 1; i < grid_points - 1; i++)
	{
		for (int j = 0; j < grid_points; j++)
		{
			if (j == i - 1)
			{
				left[i][j] = -r / 2;
			}
			else if (j == i)
			{
				left[i][j] = 1 + r;
			}
			else if (j == i + 1)
			{
				left[i][j] = -r / 2;
			}
		}
	}

	right[0][0] = 1 - r;
	right[0][1] = r / 2;
	right[grid_points - 1][grid_points - 1] = 1 - r;
	right[grid_points - 1][grid_points - 2] = r;

	for (int i = 1; i < grid_points - 1; i++)
	{
		for (int j = 0; j < grid_points; j++)
		{
			if (j == i - 1)
			{
				right[i][j] = r / 2;
			}
			else if (j == i)
			{
				right[i][j] = 1 - r;
			}
			else if (j == i + 1)
			{
				right[i][j] = r / 2;
			}
		}
	}
	
	MATRIX T_right(grid_points, 1);

	for (int i = 0; i < total_steps; i++)
	{
		T_right = right * prev_solution;
		fout << "Time Step: " << (i + 1) * time_step << "\n";

		solution = GS_solution(grid_points, left, T_right, 0.001);
		
		for (int i = 0; i < grid_points; i++)
		{
			fout << "T" << i + 1 << ": " << solution[i][0] << "\t";
		}
		prev_solution = solution;
		fout << "\n\n";
	}

	cout << "Output written to Crank_Nikolson.txt\n";
}

void Euler_Method(MATRIX& left, MATRIX& right, double time_step, double grid_points, int total_steps)
{
	double r = time_step / (grid_points * grid_points);

	ofstream fout;
	fout.open("Euler_Method.txt");

	MATRIX solution(grid_points, 1);
	MATRIX prev_solution(grid_points, 1);

	for (int i = 0; i < grid_points; i++)
	{
		prev_solution[i][0] = 1;
	}


	right[0][0] = 1 - 2*r;
	right[0][1] = r;
	right[grid_points - 1][grid_points - 1] = 1 - 2*r;
	right[grid_points - 1][grid_points - 2] = 2*r;

	for (int i = 1; i < grid_points - 1; i++)
	{
		for (int j = 0; j < grid_points; j++)
		{
			if (j == i - 1)
			{
				right[i][j] = r;
			}
			else if (j == i)
			{
				right[i][j] = 1 - 2*r;
			}
			else if (j == i + 1)
			{
				right[i][j] = r ;
			}
		}
	}


	for (int i = 0; i < total_steps; i++)
	{
		solution = right * prev_solution;
		fout << "Time Step: " << (i+1) * time_step << "\n";
		for (int i = 0; i < grid_points; i++)
		{
			fout << "T" << i + 1 << ": " << solution[i][0] << "\t";
		}
		fout << "\n\n";
		prev_solution = solution;
	}
	
	cout << "Output written to Euler_Method.txt\n";
}

void Pure_Implicit(MATRIX& left, MATRIX& right, double time_step, double grid_points, int total_steps)
{

	ofstream fout;
	fout.open("Pure_Implicit.txt");

	double r = time_step / (grid_points * grid_points);


	MATRIX solution(grid_points, 1);
	MATRIX prev_solution(grid_points, 1);

	for (int i = 0; i < grid_points; i++)
	{
		prev_solution[i][0] = 1;
	}

	left[0][0] = 1 + 2 * r;
	left[0][1] = -r;
	left[grid_points - 1][grid_points - 1] = 1 + 2 * r;
	left[grid_points - 1][grid_points - 2] = -2 * r;

	for (int i = 1; i < grid_points - 1; i++)
	{
		for (int j = 0; j < grid_points; j++)
		{
			if (j == i - 1)
			{
				left[i][j] = -r;
			}
			else if (j == i)
			{
				left[i][j] = 1 + 2 * r;
			}
			else if (j == i + 1)
			{
				left[i][j] = -r;
			}
		}
	}

	for (int i = 0; i < total_steps; i++)
	{
		fout << "Time Step: " << (i+1)*time_step << "\n";
		solution = GS_solution(grid_points, left, prev_solution, 0.001);
		for (int i = 0; i < grid_points; i++)
		{
			fout << "T"<<i+1<<": "<<solution[i][0] << "\t";
		}
		prev_solution = solution;
		fout << "\n\n";
	}

	cout << "Output written to Pure_Implicit.txt\n";

}

int main()
{
	int grid_points = 4;
	double time_step = 1;
	int total_steps = 100;

	cout << "Enter the number of grid points (ex: 10 for grid spacing of 0.1): ";
	cin >> grid_points;
	cout << "Enter the time step to be taken: ";
	cin >> time_step;
	cout << "Enter the total number of time steps to be taken: ";
	cin >> total_steps;
	cout << "\n\n";

	MATRIX left(grid_points, grid_points);
	MATRIX right(grid_points, grid_points);

	cout << "PLEASE WAIT...." << "               \r";

	double r = time_step / (grid_points * grid_points);
	if (r < 0.5)
	{
		Crank_Nikolson(left, right, time_step, grid_points, total_steps);
	}
	else
	{
		cout << "NOT A VALID TIME STEP FOR CRANK NIKOLSON METHOD\n";
		cout << "Enter a new time step for Crank Nikolson method: ";
		double CN_time_step;
		cin >> CN_time_step;
		Crank_Nikolson(left, right, CN_time_step, grid_points, total_steps);
	}
	Euler_Method(left, right, time_step, grid_points, total_steps);
	Pure_Implicit(left, right, time_step, grid_points, total_steps);

	return 0;
}