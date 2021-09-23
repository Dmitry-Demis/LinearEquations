// LinearEquations.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MatrixGeneration.h"
#include <sstream>
#include <iomanip>

const int N = 100;
const double eps = 1e-4;
ostream& operator<<(ostream& stream, const vector<double>& vec);
int main()
{
	if (!MatrixGeneration()) // Matrix Generation
	{
		cout << "Files were created" << endl;
	}

	string 
		fileNameA = "matrixA" + to_string(N) + ".txt", //a file name of matrices
		fileNameB = "matrixB" + to_string(N) + ".txt";
	double sum1 = 0.0, sum2 = 0.0, xMax = -1;
	ifstream matrixA, matrixB;
	matrixA.open(fileNameA); //opening of files
	matrixB.open(fileNameB);

	string str;  //for parsing data
	vector<vector<double>> a(N); // a[n][n]
	vector<double> b(N); // b[n]
	bool correctOpening = true, loading = true;
	// Считывание из файлов матрицы А и вектора B
	if (matrixA.is_open())
	{
		int i = 0;
		while (getline(matrixA, str))
		{
			stringstream stream(str);
			while (getline(stream, str, '\t'))
			{
				a[i].push_back(stod(str));
			}
			i++;
						
		};
		matrixA.close();
	}
	else
	{
		cout << "A Matrix A is absent " << endl;
		correctOpening = false;
	}
	if (matrixB.is_open())
	{
		int i = 0;
		while (getline(matrixB, str))
		{
			stringstream stream(str);
			while (getline(stream, str, '\t'))
			{
				b[i++] = stod(str);
			}
		};
		matrixB.close();
	}
	else
	{
		cout << "A Matrix B is absent" << endl;
		correctOpening = false;
	}
	cout << setw(8) << setfill(' ') << "SIM | GSM" << endl;
	//Искомый вектор X и дополнительный
	vector<double> matrixX(N, 0.0), matrixXX(N, 0.0);
	if (correctOpening && loading)
	{
		
		//cout << "Simple Iteration Method" << endl;
		do
		{
			xMax = -1;
			for (int i = 0; i < N; i++)
			{
				sum1 = 0;
				for (int j = 0; j < N; j++)
				{
					if (i != j)
					{
						sum1 += a[i][j] * matrixX[j];
					}
				}
				matrixXX[i] = 1.0 / a[i][i] * (b[i] - sum1);
				if (fabs(matrixXX[i] - matrixX[i]) > xMax)
				{
					xMax = fabs(matrixXX[i] - matrixX[i]);
				}

			}
			/*xMax = fabs(matrixXX[0] - matrixX[0]);
			double buf = xMax;
			for (int i = 1; i < N; i++)
			{
				buf = fabs(matrixXX[i] - matrixX[i]);
				if (xMax < buf)
				{
					xMax = buf;
				}

			}*/
			//xMax = -1;
			matrixX = matrixXX;
		} while (xMax > eps);
		//cout << matrixX;
	}
	vector<double> previousX(N, 0.0), currentX(N, 0.0);
	if (correctOpening && loading)
	{
		//cout << "Gauss-Seidel's method" << endl;
		
		do
		{
			for (int i = 0; i < N; i++)
			{
				currentX[i] = b[i];
				for (int j = 0; j < N; j++)
				{
					if (j < i)
					{
						currentX[i] -= a[i][j] * currentX[j];
					}
					if (j > i)
					{
						currentX[i] -= a[i][j] * previousX[j];
					}
				}
				currentX[i] /= a[i][i];

			}
			// Посчитаем текущую погрешность относительно предыдущей итерации
			double error = 0.0;
			for (int i = 0; i < N; i++)
			{
				error += fabs(currentX[i] - previousX[i]);
			}
			if (error < eps)
			{
				break;
			}
			previousX = currentX;
		} while (true);
		//cout << currentX;
	}
	
	for (int i = 0; i < N; i++)
	{
		cout << setw(3) << i + 1 << "." << setw(10) << fixed << setprecision(5) << matrixX[i] << " -> " << previousX[i] << endl;
	}
	
}
ostream& operator<<(ostream& stream, const vector<double>& vec)
{

	for (const auto& b : vec)
		stream << fixed << setprecision(5) << b << endl;
	return stream;
}
