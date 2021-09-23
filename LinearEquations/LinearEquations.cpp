﻿// LinearEquations.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MatrixGeneration.h"
#include <sstream>

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

	//Искомый вектор X и дополнительный
	vector<double> matrixX(N, 0.0), matrixXX(N, 0.0);
	bool flag = 1;
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
			if (fabs(matrixXX[i]-matrixX[i])>xMax)
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
	cout << matrixX;
	
}
ostream& operator<<(ostream& stream, const vector<double>& vec)
{
	for (const auto& b : vec)
		stream << b << endl;
	return stream;
}
