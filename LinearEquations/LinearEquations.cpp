// LinearEquations.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MatrixGeneration.h"
#include <sstream>

const int N = 10;
const double eps = 1e-4;
vector<double> ParseStringToArray(const string& s)
{
	stringstream stream(s);
	
	return { 0.0 };
}
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
	vector<double> matrixX(N, 1.0), matrixXX(N, 1.0);
	
}

