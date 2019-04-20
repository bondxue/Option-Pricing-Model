//Mesher.hpp
//purpose: header file for mesh creation
//author: bondxue
//version: 1.0 11/21/2017

#ifndef MESHER_HPP
#define MESHER_HPP

#include <vector>
#include <iostream>

using namespace std;

// global function that creates a mesh array of doubles with size n
// I use the vector size n instead of the mesh size h as parameter to avoid the non-uniform size between second last and last elements in vector
vector<double> CreateMesh(double startValue, double endValue, int n)
{ // n-1 number of equal divisions of [startValue, endValue]


	vector<double> x(n); // create a vector with size (n+1)
	x[0] = startValue; // assign the begin element of vector 
	x[x.size() - 1] = endValue; // assign the end element of vector 

	double h = (endValue - startValue) / (double(n)-1.0);  // h is the mesh size
	for (int j = 1; j < x.size() - 1; ++j)
	{
		x[j] = x[j - 1] + h; // calculate the rest elements in the vector
	}

	return x;
}

#endif