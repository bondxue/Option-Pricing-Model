//TestEuropean_AmericanOption.cpp
//purpose: source file to test EuropeanOption and AmericanOption classes
//author: bondxue
//version: 1.0 11/24/2017

#include "EuropeanOption.hpp"
#include "AmericanOption.hpp"
#include "Mesher.hpp"
#include "Print.hpp"

#include <iostream>

using namespace std;
using namespace OPTION;
using namespace OPTION::EUROPEANOPTION;
using namespace OPTION::AMERICANOPTION;

int main()
{ 
	/*======================Group A Part I (a)=========================*/
	cout << "=================Group A Part I (a)======================" << endl;
	/*=========test for Batch 1 data==========*/
	double T1 = 0.25;
	double K1 = 65.0;
	double sig1 = 0.30;
	double r1 = 0.08;
	double b1 = r1; // b = r for stock option model
	double S1 = 60.0;

	EuropeanOption Batch1(Euro_OptionData(S1, K1, T1, r1, sig1, b1), EuroCall); // create an European call option object for Batch 1 data
	double C1 = Batch1.Price(); // calculate the European call price
	Batch1.Type(EuroPut);       // change the option type to European put 
	double P1 = Batch1.Price(); // calculate the European put price
	cout << "Batch 1: C1 = " << C1 << ", P1 = " << P1 << endl; // print out the call and put price for Batch 1

	/*=========test for Batch 2 data==========*/
	double T2 = 1.0;
	double K2 = 100.0;
	double sig2 = 0.20;
	double r2 = 0.0;
	double b2 = r2; // b = r for stock option model
	double S2 = 100.0;

	EuropeanOption Batch2(Euro_OptionData(S2, K2, T2, r2, sig2, b2), EuroCall); // create an european call option object for Batch 2 data
	double C2 = Batch2.Price();  // calculate the call price
	Batch2.Type(EuroPut);        // change the option type to put 
	double P2 = Batch2.Price();  // calculate the put price
	cout << "Batch 2: C2 = " << C2 << ", P2 = " << P2 << endl; // print out the call and put price for Batch 2

	/*=========test for Batch 3 data==========*/
	double T3 = 1.0;
	double K3 = 10.0;
	double sig3 = 0.50;
	double r3 = 0.12;
	double b3 = r3; // b = r for stock option model
	double S3 = 5.0;

	EuropeanOption Batch3(Euro_OptionData(S3, K3, T3, r3, sig3, b3), EuroCall); // create an european call option object for Batch 3 data
	double C3 = Batch3.Price(); // calculate the call price
	Batch3.Type(EuroPut);       // change the option type to put 
	double P3 = Batch3.Price(); // calculate the put price
	cout << "Batch 3: C3 = " << C3 << ", P3 = " << P3 << endl; // print out the call and put price for Batch 3

	/*=========test for Batch 4 data==========*/
	double T4 = 30.0;
	double K4 = 100.0;
	double sig4 = 0.30;
	double r4 = 0.08;
	double b4 = r4; // b = r for stock option model
	double S4 = 100.0;

	EuropeanOption Batch4(Euro_OptionData(S4, K4, T4, r4, sig4, b4), EuroCall); // create an european call option object for Batch 4 data
	double C4 = Batch4.Price(); // calculate the call price
	Batch4.Type(EuroPut);       // change the option type to put 
	double P4 = Batch4.Price(); // calculate the put price
	cout << "Batch 4: C4 = " << C4 << ", P4 = " << P4 << endl; // print out the call and put price for Batch 4

	cout << endl;
	/*======================Group A Part I (b)=========================*/
	cout << "=================Group A Part I (b)======================" << endl;
	cout << "************Method 1************" << endl;
	cout << endl;
	// Method 1: calculate the call (or put) price for the corresponding put (or call) price
	// test put-call parity for Batch 1
	double  C1_parity = Batch1.Price(P1, EuroPut); // give put price to calculate call price
	double P1_parity = Batch1.Price(C1, EuroCall); // give call price to calculate put price 
	cout << "Batch 1: Given P1 = " << P1 << ", C1 = " << C1_parity << endl; // print out the call price given put price
	cout << "Batch 1: Given C1 = " << C1 << ", P1 = " << P1_parity << endl; // print out the put price given call price

	cout << endl;
	// test put-call parity for Batch 2
	double C2_parity = Batch2.Price(P2, EuroPut); // give put price to calculate call price
	double P2_parity = Batch2.Price(C2, EuroCall); // give call price to calculate put price 
	cout << "Batch 2: Given P2 = " << P2 << ", C2 = " << C2_parity << endl; // print out the call price given put price
	cout << "Batch 2: Given C2 = " << C2 << ", P2 = " << P2_parity << endl; // print out the put price given call price

	cout << endl;
	// test put-call parity for Batch 3
	double C3_parity = Batch3.Price(P3, EuroPut);  // give put price to calculate call price
	double P3_parity = Batch3.Price(C3, EuroCall); // give call price to calculate put price 
	cout << "Batch 3: Given P3 = " << P3 << ", C3 = " << C3_parity << endl; // print out the call price given put price
	cout << "Batch 3: Given C3 = " << C3 << ", P3 = " << P3_parity << endl; // print out the put price given call price

	cout << endl;
	// test put-call parity for Batch 4
	double C4_parity = Batch4.Price(P4, EuroPut);  // give put price to calculate call price
	double P4_parity = Batch4.Price(C4, EuroCall); // give call price to calculate put price 
	cout << "Batch 4: Given P4 = " << P4 << ", C4 = " << C4_parity << endl; // print out the call price given put price
	cout << "Batch 4: Given C4 = " << C4 << ", P4 = " << P4_parity << endl; // print out the put price given call price

	cout << endl;
	// Method 2: give a set of put/ call prices to check whether satisfy the parity
	cout << "************Method 2************" << endl;
	cout << endl;
	// test put-call parity for Batch 1
	cout << "Batch 1: C1 = " << C1 << ", P1 = " << P1 << ": " << endl;
	Batch1.PutCallParity_Checking(P1, EuroPut, C1, EuroCall); 

	cout << endl;
	// test put-call parity for Batch 2
	cout << "Batch 2: C2 = " << C2 << ", P2 = " << P2 << ": " << endl;
	Batch2.PutCallParity_Checking(P2, EuroPut, C2, EuroCall); 

	cout << endl;
	// test put-call parity for Batch 3
	cout << "Batch 3: C3 = " << C3 << ", P3 = " << P3 << ": " << endl;
	Batch3.PutCallParity_Checking(P3, EuroPut, C3, EuroCall); 

	cout << endl;
	// test put-call parity for Batch 4
	cout << "Batch 4: C4 = " << C4 << ", P4 = " << P4 << ": " << endl;
	Batch4.PutCallParity_Checking(P4, EuroPut, C4, EuroCall);

	cout << endl;
	/*======================Group A Part I (c)=========================*/
	cout << "=================Group A Part I (c)======================" << endl;
	//calculate call and put price vector for Batch 1
	double start_S = Batch1.S();  // set the start value as stock price of Batch 1 (here I use the Batch 1 S data)
	double end_S = start_S * 1.5; // set the end value as 1.5 times of initial value
	int num_S = 11;               // set the number of stock prices we need

	vector<double> S1_vec = CreateMesh(start_S, end_S, num_S); // create a vector of of monotonically increasing stock prices
	cout << "stock price vector: " << endl;
	print(S1_vec); // print the stock price vector 
	cout << endl;

	Batch1.Type(EuroCall); // set the option type as European call
	vector<double> C1_vec = Batch1.Price_S(S1_vec); // create a vector to store  a sequence of call prices

	Batch1.Type(EuroPut);  // set the option type as European put
	vector<double> P1_vec = Batch1.Price_S(S1_vec); // create a vector to store  a sequence of put prices

	cout << "European call price vector: " << endl; 
	print(C1_vec);  // print the call price vector
	cout << endl;

	cout << "European put price vector: " << endl;
	print(P1_vec);  // print the put price vector 

	cout << endl;
	/*======================Group A Part I (d)=========================*/
	cout << "=================Group A Part I (d)======================" << endl;
	// test using the Batch 1 data 
	int num_data = 5; // set the size of each paramater vector as 5

	// create S vector 
	S1_vec = CreateMesh(start_S, end_S, num_data); // create the vector of S parameter

	// create K vector 
	double start_K = Batch1.K();  // set the start point as the same K in Batch 1
	double end_K = start_K * 1.5; // set the end point as the 1.5 times of K in Batch 1
	vector<double> K1_vec = CreateMesh(start_K, end_K, num_data); // create the vector of K parameter

	// create T vector 
	double start_T = Batch1.T();  // set the start point as the same T in Batch 1
	double end_T = start_T * 1.5; // set the end point as the 1.5 times of T in Batch 1
	vector<double> T1_vec = CreateMesh(start_T, end_T, num_data); // create the vector of T parameter

	// create r vector 
	double start_r = Batch1.r();  // set the start point as the same r in Batch 1
	double end_r = start_r * 1.5; // set the end point as the 1.5 times of r in Batch 1
	vector<double> r1_vec = CreateMesh(start_r, end_r, num_data); // create the vector of r parameter

	// create sig vector 
	double start_sig = Batch1.sig();  // set the start point as the same sig in Batch 1
	double end_sig = start_sig * 1.5; // set the end point as the 1.5 times of sig in Batch 1
	vector<double> sig1_vec = CreateMesh(start_sig, end_sig, num_data); // create the vector of sig paramete

	// create b vector 
	double start_b = Batch1.b();  // set the start point as the same b in Batch 1
	double end_b = start_b * 1.5; // set the end point as the 1.5 times of b in Batch 1
	vector<double> b1_vec = CreateMesh(start_b, end_b, num_data); // create the vector of b paramete


	vector<vector<double>> parameter_matrix1; // create a paramater matrix as the input for the Price() function

	// notice that the construction of the input matrix should follow the order as S_vec, K_vec, T_vec, r_vec, sig_vec, and b_vec, 
	// which is defined for the memeber function Price()
	parameter_matrix1.push_back(S1_vec);
	parameter_matrix1.push_back(K1_vec);
	parameter_matrix1.push_back(T1_vec);
	parameter_matrix1.push_back(r1_vec);
	parameter_matrix1.push_back(sig1_vec);
	parameter_matrix1.push_back(b1_vec);

	Batch1.Type(EuroCall); // set the option type as European call
	vector<vector<double>> C1_matrix = Batch1.Price(parameter_matrix1); // create the European call price matrix corresponding to the parameter matrix

	Batch1.Type(EuroPut); // set the option type as European call
	vector<vector<double>> P1_matrix = Batch1.Price(parameter_matrix1); // create the European put price matrix corresponding to the parameter matrix

	// print out the parameter matrix
	cout << "Parameter matrix: " << endl;
	print(parameter_matrix1); 

	cout << endl;
	// print out the European call price matrix 
	cout << "European Call price matrix: " << endl;
    print(C1_matrix);

	cout << endl;
	// print out the European put price matrix
	cout << "European Put price matrix: " << endl;
	print(P1_matrix);


	cout << endl;
	/*======================Group A Part II (a)=========================*/
	cout << "=================Group A Part II (a)======================" << endl;
	// compute the Delta and Gamma for the given batch data
	double K5 = 100.0;
	double S5 = 105.0;
	double T5 = 0.5;
	double r5 = 0.1;
	double b5 = 0.0; // b = 0 for furture option model 
	double sig5 = 0.36;

	EuropeanOption Batch5(Euro_OptionData(S5, K5, T5, r5, sig5, b5), EuroCall); // create an European call option object 
	double DeltaC5 = Batch5.Delta(); // European call option Delta
	double GammaC5 = Batch5.Gamma(); // European call option Gamma

	Batch5.Type(EuroPut); // set option type to European put 
	double DeltaP5 = Batch5.Delta(); // European put option Delta
	double GammaP5 = Batch5.Gamma(); // European put option Gamma
	
	cout << "Batch 5: " << endl;
	cout << "DeltaC5 = " << DeltaC5 << ", GammaC5 = " << GammaC5 << endl; // print out European call Delta and Gamma
	cout << "DeltaP5 = " << DeltaP5 << ", GammaP5 = " << GammaP5 << endl; // print out European put Delta and Gamma

	cout << endl;
	/*======================Group A Part II (b)=========================*/
	cout << "=================Group A Part II (b)======================" << endl;
	//calculate call Delta vector for Batch 5
	int num_S5 = 5; // set the size of S vector as 5
	double start_S5 = Batch5.S();  // set the start value as stock price of Batch 5 (here I use the Batch 5 S data)
	double end_S5 = start_S5 * 1.5; // set the end value as 1.5 times of initial value

	vector<double> S5_vec = CreateMesh(start_S5, end_S5, num_S5); // create a vector of of monotonically increasing stock prices
	cout << "stock price vector: " << endl;
	print(S5_vec); // print the stock price vector 

	Batch5.Type(EuroCall); // set the option type as European call
	vector<double> DeltaC5_vec = Batch5.Delta_S(S5_vec); // create a vector to store  a sequence of call Delta

	cout << "European call Delta vector: " << endl;
	print(DeltaC5_vec);  // print the call Delta vector

	cout << endl;
	/*======================Group A Part II (c)=========================*/
	cout << "=================Group A Part II (c)======================" << endl;
	// test using the Batch 5 data 
	int num_data5 = 5; // set the size of each paramater vector as 5

	// create S vector 
	S5_vec = CreateMesh(start_S5, end_S5, num_data5); // create the vector of S parameter

	// create K vector 
	double start_K5 = Batch5.K();  // set the start point as the same K in Batch 5
	double end_K5 = start_K5 * 1.5; // set the end point as the 1.5 times of K in Batch 5
	vector<double> K5_vec = CreateMesh(start_K5, end_K5, num_data5); // create the vector of K parameter

	// create T vector 
	double start_T5 = Batch5.T();  // set the start point as the same T in Batch 5
	double end_T5 = start_T5 * 1.5; // set the end point as the 1.5 times of T in Batch 5
	vector<double> T5_vec = CreateMesh(start_T5, end_T5, num_data5); // create the vector of T parameter

	// create r vector 
	double start_r5 = Batch5.r();  // set the start point as the same r in Batch 5
	double end_r5 = start_r5 * 1.5; // set the end point as the 1.5 times of r in Batch 5
	vector<double> r5_vec = CreateMesh(start_r5, end_r5, num_data5); // create the vector of r parameter

	// create sig vector 
	double start_sig5 = Batch5.sig();  // set the start point as the same sig in Batch 5
	double end_sig5 = start_sig5 * 1.5; // set the end point as the 1.5 times of sig in Batch 5
	vector<double> sig5_vec = CreateMesh(start_sig5, end_sig5, num_data5); // create the vector of sig paramete

	// create b vector 
	double start_b5 = Batch5.b();  // set the start point as the same b in Batch 5
	double end_b5 = 0.2; // set the end point as 0.2
	vector<double> b5_vec = CreateMesh(start_b5, end_b5, num_data5); // create the vector of b paramete


	vector<vector<double>> parameter_matrix5; // create a paramater matrix as the input for the Price() function

	// notice that the construction of the input matrix should follow the order as S_vec, K_vec, T_vec, r_vec, sig_vec, and b_vec, 
	// which is defined for the memeber function Price()
	parameter_matrix5.push_back(S5_vec);
	parameter_matrix5.push_back(K5_vec);
	parameter_matrix5.push_back(T5_vec);
	parameter_matrix5.push_back(r5_vec);
	parameter_matrix5.push_back(sig5_vec);
	parameter_matrix5.push_back(b5_vec);

	Batch5.Type(EuroCall); // set the option type as European call
	vector<vector<double>> DeltaC5_matrix = Batch5.Delta(parameter_matrix5); // create the European call Delta matrix corresponding to the parameter matrix

	// print out the parameter matrix
	cout << "Parameter matrix: " << endl;
	print(parameter_matrix5);

	cout << endl;
	// print out the European call Delta matrix 
	cout << "European Call Delta matrix: " << endl;
	print(DeltaC5_matrix);

	cout << endl;
	/*======================Group A Part II (d)=========================*/
	cout << "=================Group A Part II (d)======================" << endl;
	
	double h; // the paramter that controls the accuracy of the approxmiation 
	Batch5.Type(EuroCall); // set option type as European call 

	for (int i = 0; i < 10; ++i)
	{
		h = pow(10, -i); // h = 10^(-i)
		// print out the approx Delta and the relative error for each chosen h
		cout << "h = " << h << ", Delta_f = " << Batch5.Delta_f(h) << ", Error = " << abs(Batch5.Delta_f(h) -DeltaC5) << endl;
	}

	cout << endl;

	for (int i = 0; i < 10; ++i)
	{
		h = pow(10, -i); // h = 10^(-i)
		// print out the approx Gamma and the relative error for each chosen h
		cout << "h = " << h << ", Gamma_f = " << Batch5.Gamma_f(h) << ", Error = " << abs(Batch5.Gamma_f(h) -GammaC5) << endl;
	}

	cout << endl;
	/*======================Group B (b)=========================*/
	cout << "=================Group B (b)======================" << endl;
	// compute the American call and put prices for Batch 6 data
	double K6 = 100.0;
	double sig6 = 0.1;
	double r6 = 0.1;
	double b6 = 0.02;
	double S6 = 110.0;

	AmericanOption Batch6(Ameri_OptionData(K6, S6, sig6, r6, b6), AmeriCall); // create an American call option object 

	double C6 = Batch6.Price(); // American call price
	Batch6.Type(AmeriPut); // change the option type to put 
	double P6 = Batch6.Price(); // American put price
	cout << "Batch 6: C6 = " << C6 << ", P6 = " << P6 << endl; // print out American call and put prices for Batch 6

	cout << endl;
	/*======================Group B (c)=========================*/
	cout << "=================Group B (c)======================" << endl;
	//calculate American call and put price vector for Batch 6
	double start_S6 = Batch6.S();  // set the start value as stock price of Batch 6 (here I use the Batch 6 S data)
	double end_S6 = start_S6 * 1.5; // set the end value as 1.5 times of initial value
	int num_S6 = 5;               // set the number of stock prices we need

	vector<double> S6_vec = CreateMesh(start_S6, end_S6, num_S6); // create a vector of of monotonically increasing stock prices
	cout << "stock price vector: " << endl;
	print(S6_vec); // print the stock price vector 
	cout << endl;

	Batch6.Type(AmeriCall); // set the option type as American call
	vector<double> C6_vec = Batch6.Price_S(S6_vec); // create a vector to store a sequence of American call prices

	Batch6.Type(AmeriPut);  // set the option type as American put
	vector<double> P6_vec = Batch6.Price_S(S6_vec); // create a vector to store a sequence of American put prices

	cout << "American call price vector: " << endl;
	print(C6_vec);  // print the call price vector
	cout << endl;

	cout << "American put price vector: " << endl;
	print(P6_vec);  // print the put price vector 

	cout << endl;
	/*======================Group B (d)=========================*/
	cout << "=================Group B (d)======================" << endl;
	// test using the Batch 6 data 
	int num_data6 = 5; // set the size of each paramater vector as 5

	// create S vector 
	S6_vec = CreateMesh(start_S6, end_S6, num_data6); // create the vector of S parameter

	// create K vector 
	double start_K6 = Batch6.K();  // set the start point as the same K in Batch 6
	double end_K6 = start_K6 * 1.5; // set the end point as the 1.5 times of K in Batch 6
	vector<double> K6_vec = CreateMesh(start_K6, end_K6, num_data6); // create the vector of K parameter

	// create r vector 
	double start_r6 = Batch6.r();  // set the start point as the same r in Batch 6
	double end_r6 = start_r * 1.5; // set the end point as the 1.5 times of r in Batch 6
	vector<double> r6_vec = CreateMesh(start_r6, end_r6, num_data6); // create the vector of r parameter

	// create sig vector 
	double start_sig6 = Batch6.sig();  // set the start point as the same sig in Batch 6
	double end_sig6 = start_sig6 * 1.5; // set the end point as the 1.5 times of sig in Batch 6
	vector<double> sig6_vec = CreateMesh(start_sig6, end_sig6, num_data6); // create the vector of sig paramete

	// create b vector 
	double start_b6 = Batch6.b();  // set the start point as the same b in Batch 6
	double end_b6 = start_b6 * 1.5; // set the end point as the 1.5 times of b in Batch 6
	vector<double> b6_vec = CreateMesh(start_b6, end_b6, num_data6); // create the vector of b paramete


	vector<vector<double>> parameter_matrix6; // create a paramater matrix as the input for the Price() function

	// notice that the construction of the input matrix should follow the order as S_vec, K_vec, r_vec, sig_vec, and b_vec, 
	// which is defined for the memeber function Price()
	parameter_matrix6.push_back(S6_vec);
	parameter_matrix6.push_back(K6_vec);
	parameter_matrix6.push_back(r6_vec);
	parameter_matrix6.push_back(sig6_vec);
	parameter_matrix6.push_back(b6_vec);

	Batch6.Type(AmeriCall); // set the option type as American call
	vector<vector<double>> C6_matrix = Batch6.Price(parameter_matrix6); // create the American call price matrix corresponding to the parameter matrix

	Batch6.Type(AmeriPut); // set the option type as American call
	vector<vector<double>> P6_matrix = Batch6.Price(parameter_matrix6); // create the American put price matrix corresponding to the parameter matrix

	// print out the parameter matrix
	cout << "Parameter matrix: " << endl;
	print(parameter_matrix6);

	cout << endl;
	// print out the American call price matrix 
	cout << "American Call price matrix: " << endl;
	print(C6_matrix);

	cout << endl;
	// print out the American put price matrix
	cout << "American Put price matrix: " << endl;
	print(P6_matrix);


	cout << endl;

	system("Pause"); 

	return 0;
}
