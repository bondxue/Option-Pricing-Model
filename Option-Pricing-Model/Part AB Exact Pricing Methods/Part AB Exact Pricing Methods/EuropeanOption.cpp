//EuropeanOption.hpp
//purpose: source file for European option class
//author: bondxue
//version: 1.0 11/24/2017


#include "EuropeanOption.hpp"
#include "EuropeanOptionPricing.hpp"
#include "EuropeanOptionGreek.hpp"
#include <cmath>
#include <vector>
#include <iostream>

namespace OPTION
{
	namespace EUROPEANOPTION
	{
		// Default call option with default option parameters and type
		EuropeanOption::EuropeanOption() : m_data(60.0, 110.0, 0.25, 0.05, 0.2, 0.05), m_type(EuroCall)
		{
		}


		// Copy constructor
		EuropeanOption::EuropeanOption(const EuropeanOption& option) : m_data(option.m_data), m_type(option.m_type)
		{
		}

		// constructor with all option parameters
		EuropeanOption::EuropeanOption(const double S, const double T, const double K, const double sig, const double r, const double b, const Euro_OptionType type) : m_data(S, K, T, r, sig, b), m_type(type)
		{
		}

		// constructor with optiondata struct as parameter
		EuropeanOption::EuropeanOption(const Euro_OptionData data, const Euro_OptionType type) : m_data(data), m_type(type)
		{
		}

		// destructor 
		EuropeanOption::~EuropeanOption()
		{

		}

		// assignment operator
		EuropeanOption& EuropeanOption::operator = (const EuropeanOption& option2)
		{
			if (this == &option2) // avoid self assignment 
			{
				return *this;
			}
			m_type = option2.m_type;
			m_data = option2.m_data;

			return *this;
		}

		// Delta of European option function
		double EuropeanOption::Delta() const
		{
			if (m_type == EuroCall)
			{
				return CallDelta(m_data.m_S, m_data.m_K, m_data.m_T, m_data.m_r, m_data.m_sig, m_data.m_b);
			}
			else // m_type = EuroPut
			{
				return PutDelta(m_data.m_S, m_data.m_K, m_data.m_T, m_data.m_r, m_data.m_sig, m_data.m_b);
			}
		}

		// Delta function with stock price S
		double EuropeanOption::Delta_S(const double S) const
		{
			if (m_type == EuroCall)
			{
				return CallDelta(S, m_data.m_K, m_data.m_T, m_data.m_r, m_data.m_sig, m_data.m_b);
			}
			else // m_type = EuroPut
			{
				return PutDelta(S, m_data.m_K, m_data.m_T, m_data.m_r, m_data.m_sig, m_data.m_b);
			}

		}

		// Delta function with expiry time T
		double EuropeanOption::Delta_T(const double T) const
		{
			if (m_type == EuroCall)
			{
				return CallDelta(m_data.m_S, m_data.m_K, T, m_data.m_r, m_data.m_sig, m_data.m_b);
			}
			else // m_type = EuroPut
			{
				return PutDelta(m_data.m_S, m_data.m_K, T, m_data.m_r, m_data.m_sig, m_data.m_b);
			}
		}

		// Delta function with vloatility sig
		double EuropeanOption::Delta_sig(const double sig) const
		{
			if (m_type == EuroCall)
			{
				return CallDelta(m_data.m_S, m_data.m_K, m_data.m_T, m_data.m_r, sig, m_data.m_b);
			}
			else // m_type = EuroPut
			{
				return PutDelta(m_data.m_S, m_data.m_K, m_data.m_T, m_data.m_r, sig, m_data.m_b);
			}
		}

		// Delta function with risk-free intereset rate r
		double EuropeanOption::Delta_r(const double r) const
		{
			if (m_type == EuroCall)
			{
				return CallDelta(m_data.m_S, m_data.m_K, m_data.m_T, r, m_data.m_sig, m_data.m_b);
			}
			else // m_type = EuroPut
			{
				return PutDelta(m_data.m_S, m_data.m_K, m_data.m_T, r, m_data.m_sig, m_data.m_b);
			}
		}

		// Delta function with strike K
		double EuropeanOption::Delta_K(const double K) const
		{
			if (m_type == EuroCall)
			{
				return CallDelta(m_data.m_S, K, m_data.m_T, m_data.m_r, m_data.m_sig, m_data.m_b);
			}
			else // m_type = EuroPut
			{
				return PutDelta(m_data.m_S, K, m_data.m_T, m_data.m_r, m_data.m_sig, m_data.m_b);
			}
		}

		// Delta function with cost of carry b
		double EuropeanOption::Delta_b(const double b) const
		{
			if (m_type == EuroCall)
			{
				return CallDelta(m_data.m_S, m_data.m_K, m_data.m_T, m_data.m_r, m_data.m_sig, b);
			}
			else // m_type = EuroPut
			{
				return PutDelta(m_data.m_S, m_data.m_K, m_data.m_T, m_data.m_r, m_data.m_sig, b);
			}
		}

		// overload Delta function with stock price vector as parameter 
		vector<double> EuropeanOption::Delta_S(const vector<double> S_vec) const
		{
			vector<double> Delta_vec; // create a vector to store the Delta corresponding to each element in stock price vector
			for (int i = 0; i < S_vec.size(); ++i)
			{
				Delta_vec.push_back(Delta_S(S_vec[i])); // calculate the Delta for the given stock price, and push it into the Delta vector
			}
			return Delta_vec;
		}

		// Gamma of European option function
		double EuropeanOption::Gamma() const
		{
			if (m_type == EuroCall)
			{
				return CallGamma(m_data.m_S, m_data.m_K, m_data.m_T, m_data.m_r, m_data.m_sig, m_data.m_b);
			}
			else // m_type = EuroPut
			{
				return PutGamma(m_data.m_S, m_data.m_K, m_data.m_T, m_data.m_r, m_data.m_sig, m_data.m_b);
			}
		}

		// finite difference approximation of Delta 
		// h is the paramter that controls the accuracy of the approxmiation 
		double EuropeanOption::Delta_f(const double h) const
		{
			double Delta_f = (Price_S(m_data.m_S + h) - Price_S(m_data.m_S - h)) / (2.0*h);

			return Delta_f;
		}

		// finite difference approximation of Gamma
		// h is the paramter that controls the accuracy of the approxmiation 
		double EuropeanOption::Gamma_f(const double h) const
		{
			double Gamma_f = (Price_S(m_data.m_S + h) - 2.0*Price() + Price_S(m_data.m_S - h)) / (h*h);

			return Gamma_f;
		}


		// function that calculate option price 
		double EuropeanOption::Price() const
		{
			if (m_type == EuroCall)
			{
				return EuropeanCall(m_data.m_S, m_data.m_K, m_data.m_T, m_data.m_r, m_data.m_b, m_data.m_sig);
			}
			else // m_type = EuroPut
			{
				return EuropeanPut(m_data.m_S, m_data.m_K, m_data.m_T, m_data.m_r, m_data.m_b, m_data.m_sig);
			}
		}

		// function that calculate option price with S as parameter
		double EuropeanOption::Price_S(const double S) const
		{
			if (m_type == EuroCall)
			{
				return EuropeanCall(S, m_data.m_K, m_data.m_T, m_data.m_r, m_data.m_b, m_data.m_sig);
			}
			else // m_type = EuroPut
			{
				return EuropeanPut(S, m_data.m_K, m_data.m_T, m_data.m_r, m_data.m_b, m_data.m_sig);
			}
		}

		// overload price function with stock price vector as parameter 
		vector<double> EuropeanOption::Price_S(const vector<double> S_vec) const
		{
			vector<double> OptPrice_vec; // create a vector to store the option prices corresponding to each element in stock price vector
			for (int i = 0; i < S_vec.size(); ++i)
			{
				OptPrice_vec.push_back(Price_S(S_vec[i])); // calculate the option price for the given stock price, and push it into the option price vector
			}
			return OptPrice_vec;
		}

		// overload price function with data matrix as parameter 
		// notice the input matrix contain the parameter vector following the order S, K, T, r, sig, and b. 
		vector<vector<double>> EuropeanOption::Price(vector<vector<double>> S_K_T_r_sig_b_matrix) const
		{
			vector<vector<double>> OptPrice_matrix; // create an option price matrix corresponding to the input parameter matrix 
			vector<double> OptPrice_vec; // create a vector to store option prices corresponding to each increasing parameter
			for (int i = 0; i < S_K_T_r_sig_b_matrix.size(); ++i)
			{
				for (int j = 0; j < S_K_T_r_sig_b_matrix[i].size(); ++j)
				{
					switch (i)
					{
					case 0: OptPrice_vec.push_back(Price_S(S_K_T_r_sig_b_matrix[i][j])); break;   // push option price corresponding to the changing S in row one 
					case 1: OptPrice_vec.push_back(Price_K(S_K_T_r_sig_b_matrix[i][j])); break;   // push option price corresponding to the changing K in row two 
					case 2: OptPrice_vec.push_back(Price_T(S_K_T_r_sig_b_matrix[i][j])); break;   // push option price corresponding to the changing T in row three 
					case 3: OptPrice_vec.push_back(Price_r(S_K_T_r_sig_b_matrix[i][j])); break;   // push option price corresponding to the changing r in row four 
					case 4: OptPrice_vec.push_back(Price_sig(S_K_T_r_sig_b_matrix[i][j])); break; // push option price corresponding to the changing sig in row five
					case 5: OptPrice_vec.push_back(Price_b(S_K_T_r_sig_b_matrix[i][j])); break;   // push option price corresponding to the changing b in row six

					default: break;
					}
				}
				OptPrice_matrix.push_back(OptPrice_vec); // push the option price vector into the option price matrix 
				OptPrice_vec.clear(); // clear the option price vector at the end of each loop 
			}

			return OptPrice_matrix;
		}

		// overload Delta function with data matrix as parameter 
		// notice the input matrix contain the parameter vector following the order S, K, T, r, sig, and b. 
		vector<vector<double>> EuropeanOption::Delta(vector<vector<double>> S_K_T_r_sig_b_matrix) const
		{
			vector<vector<double>> Delta_matrix; // create an option price matrix corresponding to the input parameter matrix 
			vector<double> Delta_vec; // create a vector to store option prices corresponding to each increasing parameter
			for (int i = 0; i < S_K_T_r_sig_b_matrix.size(); ++i)
			{
				for (int j = 0; j < S_K_T_r_sig_b_matrix[i].size(); ++j)
				{
					switch (i)
					{
					case 0: Delta_vec.push_back(Delta_S(S_K_T_r_sig_b_matrix[i][j])); break;   // push Delta corresponding to the changing S in row one 
					case 1: Delta_vec.push_back(Delta_K(S_K_T_r_sig_b_matrix[i][j])); break;   // push Delta corresponding to the changing K in row two 
					case 2: Delta_vec.push_back(Delta_T(S_K_T_r_sig_b_matrix[i][j])); break;   // push Delta corresponding to the changing T in row three 
					case 3: Delta_vec.push_back(Delta_r(S_K_T_r_sig_b_matrix[i][j])); break;   // push Delta corresponding to the changing r in row four 
					case 4: Delta_vec.push_back(Delta_sig(S_K_T_r_sig_b_matrix[i][j])); break; // push Delta corresponding to the changing sig in row five
					case 5: Delta_vec.push_back(Delta_b(S_K_T_r_sig_b_matrix[i][j])); break;   // push Delta corresponding to the changing b in row six

					default: break;
					}
				}
				Delta_matrix.push_back(Delta_vec); // push the Delta vector into the Delta matrix 
				Delta_vec.clear(); // clear the Delta vector at the end of each loop 
			}

			return Delta_matrix;
		}


		// function that calculate option price with T as parameter
		double EuropeanOption::Price_T(const double T) const
		{
			if (m_type == EuroCall)
			{
				return EuropeanCall(m_data.m_S, m_data.m_K, T, m_data.m_r, m_data.m_b, m_data.m_sig);
			}
			else // m_type = EuroPut
			{
				return EuropeanPut(m_data.m_S, m_data.m_K, T, m_data.m_r, m_data.m_b, m_data.m_sig);
			}
		}

		// function that calculate option price with sig as parameter
		double EuropeanOption::Price_sig(const double sig) const
		{
			if (m_type == EuroCall)
			{
				return EuropeanCall(m_data.m_S, m_data.m_K, m_data.m_T, m_data.m_r, m_data.m_b, sig);
			}
			else // m_type = EuroPut
			{
				return EuropeanPut(m_data.m_S, m_data.m_K, m_data.m_T, m_data.m_r, m_data.m_b, sig);
			}
		}

		// function that calculate option price with r as parameter
		double EuropeanOption::Price_r(const double r) const
		{
			if (m_type == EuroCall)
			{
				return EuropeanCall(m_data.m_S, m_data.m_K, m_data.m_T, r, m_data.m_b, m_data.m_sig);
			}
			else // m_type = EuroPut
			{
				return EuropeanPut(m_data.m_S, m_data.m_K, m_data.m_T, r, m_data.m_b, m_data.m_sig);
			}
		}

		// function that calculate option price with K as parameter
		double EuropeanOption::Price_K(const double K) const
		{
			if (m_type == EuroCall)
			{
				return EuropeanCall(m_data.m_S, K, m_data.m_T, m_data.m_r, m_data.m_b, m_data.m_sig);
			}
			else // m_type = EuroPut
			{
				return EuropeanPut(m_data.m_S, K, m_data.m_T, m_data.m_r, m_data.m_b, m_data.m_sig);
			}
		}

		// price function with cost of carry b as parameter
		double EuropeanOption::Price_b(const double b) const
		{
			if (m_type == EuroCall)
			{
				return EuropeanCall(m_data.m_S, m_data.m_K, m_data.m_T, m_data.m_r, b, m_data.m_sig);
			}
			else // m_type = EuroPut
			{
				return EuropeanPut(m_data.m_S, m_data.m_K, m_data.m_T, m_data.m_r, b, m_data.m_sig);
			}
		}

		// overload price function using put-call parity 
		double EuropeanOption::Price(double optPrice, Euro_OptionType type)
		{
			if (type == EuroCall)
			{
				double C = optPrice;
				return EuropeanPut_parity(m_data.m_S, m_data.m_K, m_data.m_T, m_data.m_r, C);
			}
			else // m_type = EuroPut
			{
				double P = optPrice;
				return EuropeanCall_parity(m_data.m_S, m_data.m_K, m_data.m_T, m_data.m_r, P);
			}
		}


		// function to check put-call parity
		void EuropeanOption::PutCallParity_Checking(double optPrice1, Euro_OptionType optType1, double optPrice2, Euro_OptionType optType2)
		{
			double C; // call price 
			double P; // put price 
			if (optType1 == EuroCall && optType2 == EuroPut)
			{
				C = optPrice1;
				P = optPrice2;
			}
			else // optType1 == EuroPut && optType2 == EuroCall
			{
				P = optPrice1;
				C = optPrice2;
			}

			double tol = 0.000001; // tol = 10^-6
			// the left side and right side of put-call parity cannot be exactly the same, since we use approximation to obtain N(d1) and N(d2) in the Black-Scholes formula
			// thus the call and put prices calculation is also approximate. That's why I apply the tolerance here 

			if (abs(C + m_data.m_K*exp(-m_data.m_r*m_data.m_T) - P - m_data.m_S) < tol) // when |left side - right side| < tol, assume the put-call parity is satisfied
			{
				cout << "Given set put/call prices satisfy parity." << endl;
			}
			else // when | left side - right side| > tol 
			{
				cout << "Given set put/call prices do not satisfy parity." << endl;
			}
		}
	}
}




