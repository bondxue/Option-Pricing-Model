//StandardDeviation_StandardError.hpp
//purpose: header file for standard deriation
//author: bondxue
//version: 1.0 11/22/2017

#ifndef STANDARDDEVIATION_STANDARDERROR_HPP
#define STANDARDDEVIATION_STANDARDERROR_HPP

#include <iostream>
#include <cmath>
#include <vector>

#include <boost/tuple/tuple.hpp> // include tuple class
#include <boost/tuple/tuple_io.hpp> // include I/O for tuple

using namespace std;
using boost::tuple;

// function to obtain standard deviation and standard error
boost::tuple <double, double> get_SD_SE(vector<double> price_vec, double r, double T)
{
	int price_size = price_vec.size();
	double sum_price = 0.0;
	double square_sum_price = 0.0;

	for (int i = 0; i < price_size; i++)
	{
		sum_price += price_vec[i];
		square_sum_price += pow(price_vec[i], 2);
	}

	double temp = sqrt((square_sum_price - pow(sum_price, 2)/double(price_size))/(double(price_size)-1.0)); // use temp to store the square root part in SD formula 
	double SD = temp * exp(-r*T);
	double SE = SD / sqrt(double(price_size));

	return boost::tuple<double, double>(SD, SE);
}

#endif