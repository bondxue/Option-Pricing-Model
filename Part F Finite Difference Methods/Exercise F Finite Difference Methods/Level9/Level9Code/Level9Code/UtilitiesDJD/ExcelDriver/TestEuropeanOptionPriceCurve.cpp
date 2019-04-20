//TestEuropeanOptionPriceCurve.cpp
//purpose: source file to display European Put and Call option prices on one Excel sheet
//author: bondxue
//version: 1.0 21/01/2017

#include <iostream>
#include <cmath>
#include <list>
#include <string>
#include <iostream>
#include "EuropeanOption.hpp"
#include "Mesher.hpp"
#include "ExcelDriverLite.hpp"
#include "Utilities.hpp"

using namespace std;
using namespace OPTION;
using namespace OPTION::EUROPEANOPTION;

int main()
{
	//// Batch 1 data
	//double T = 0.25;
	//double K = 65.0;
	//double sig = 0.30;
	//double r = 0.08;
	//double b = r; // b = r for stock option model
	//double S = 60.0;

	//// Batch 2 data
	//double T = 1.0;
	//double K = 100.0;
	//double sig = 0.20;
	//double r = 0.0;
	//double b = r; // b = r for stock option model
	//double S = 100.0;

	//// Batch 3 data
	//double T = 1.0;
	//double K = 10.0;
	//double sig = 0.50;
	//double r = 0.12;
	//double b = r; // b = r for stock option model
	//double S = 5.0;

	// Batch 4 data
	double T = 30.0;
	double K = 100.0;
	double sig = 0.30;
	double r = 0.08;
	double b = r; // b = r for stock option model
	double S = 100.0;

	EuropeanOption Batch(Euro_OptionData(S, K, T, r, sig, b), EuroCall); // create an European call option object 
	double start_S = Batch.S() * 0.5;  // set the start value as 0.05 times of stock price of the batch 
	double end_S = start_S * 5.0; // set the end value as 5 times of initial value
	int num_S = 40;               // set the number of stock prices we need

	vector<double> S_vec = CreateMesh(start_S, end_S, num_S); // create a vector of of monotonically increasing stock prices
	cout << "stock price vector: " << endl;
	print(S_vec); // print the stock price vector 
	cout << endl;

	vector<double> C_vec = Batch.Price_S(S_vec); // create a vector to store  a sequence of call prices

	Batch.Type(EuroPut);  // set the option type as European put
	vector<double> P_vec = Batch.Price_S(S_vec); // create a vector to store  a sequence of put prices

	long N = 40;

	ExcelDriver xl; xl.MakeVisible(true);
	xl.CreateChart(S_vec, C_vec, "Call price");
	xl.CreateChart(S_vec, P_vec, "Put price");

	// C++11 style initializer lists
	// std::list<std::string> labels{ "Call price", "Put price" };
	std::list<std::string> labels;
	labels.push_back("Call price");
	labels.push_back("Put price");

	// C++11 style initializer lists
	// std::list<std::vector<double>> curves{ C_vec, P_vec };
	std::list<std::vector<double>> curves;
	curves.push_back(C_vec);
	curves.push_back(P_vec);

	xl.CreateChart(S_vec, labels, curves, "Option Prices", "S", "V");

	return 0;
}
