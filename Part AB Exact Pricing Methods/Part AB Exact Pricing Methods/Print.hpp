//Print.hpp
//purpose: header file for print functions for vectors and matrices 
//author: bondxue
//version: 1.0 11/22/2017

#ifndef PRINT_HPP
#define PRINT_HPP

#include <vector>
#include <iostream>

using namespace std;

// function that prints a vector
void print(const vector<double>& vec)
{
	for (int i = 0; i < vec.size(); ++i)
	{
		cout << vec[i] << " "; 
	}
	cout << endl;
}

// overload function that prints a matrix
void print(const vector<vector<double>> & matrix)
{
	for (int i = 0; i < matrix.size(); ++i)
	{
		print(matrix[i]); // print row i of matrix as a vector in each loop
	}
}


#endif