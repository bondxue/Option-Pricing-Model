//AmericanOption.cpp
//purpose: source file for American option class
//author: bondxue
//version: 1.0 11/24/2017

#include "AmericanOption.hpp"
#include "AmericanOptionPricing.hpp"
#include <cmath>
#include <vector>

namespace OPTION
{
	namespace AMERICANOPTION
	{
		// default constructor
		AmericanOption::AmericanOption() : m_data(60.0, 110.0, 0.05, 0.2, 0.05), m_type(AmeriCall)
		{
		}

		// Copy constructor
		AmericanOption::AmericanOption(const AmericanOption& option) : m_data(option.m_data), m_type(option.m_type)
		{
		}

		// constructor with all American option parameters 
		AmericanOption::AmericanOption(const double K, const double S, const double sig, const double r, const double b, const Ameri_OptionType type) : m_data(K, S, sig, r, b), m_type(type)
		{
		}

		// constructor with Ameri_OptionData struct as parameter
		AmericanOption::AmericanOption(const Ameri_OptionData data, const Ameri_OptionType type) : m_data(data), m_type(type)
		{
		}

		// destructor
		AmericanOption::~AmericanOption()
		{
		}

		// assignment operator 
		AmericanOption& AmericanOption::operator = (const AmericanOption& option2)
		{
			if (this == &option2) // avoid self assignment 
			{
				return *this;
			}
			m_type = option2.m_type;
			m_data = option2.m_data;

			return *this;
		}

		// price funtion 
		double  AmericanOption::Price() const
		{
			if (m_type == AmeriCall)
			{
				return AmericanCall(m_data.m_K, m_data.m_S, m_data.m_sig, m_data.m_r, m_data.m_b);
			}
			else // m_type = AmeriPut
			{
				return AmericanPut(m_data.m_K, m_data.m_S, m_data.m_sig, m_data.m_r, m_data.m_b);
			}
		}

		// function that calculate option price with S as parameter
		double AmericanOption::Price_S(const double S) const
		{
			if (m_type == AmeriCall)
			{
				return AmericanCall(m_data.m_K, S, m_data.m_sig, m_data.m_r, m_data.m_b);
			}
			else // m_type = AmeriPut
			{
				return AmericanPut(m_data.m_K, S, m_data.m_sig, m_data.m_r, m_data.m_b);
			}
		}

		// price function with vloatility sig
		double AmericanOption::Price_sig(const double sig) const
		{
			if (m_type == AmeriCall)
			{
				return AmericanCall(m_data.m_K, m_data.m_S, sig, m_data.m_r, m_data.m_b);
			}
			else // m_type = AmeriPut
			{
				return AmericanPut(m_data.m_K, m_data.m_S, sig, m_data.m_r, m_data.m_b);
			}
		}

		// price function with risk-free intereset rate r
		double AmericanOption::Price_r(const double r) const
		{
			if (m_type == AmeriCall)
			{
				return AmericanCall(m_data.m_K, m_data.m_S, m_data.m_sig, r, m_data.m_b);
			}
			else // m_type = AmeriPut
			{
				return AmericanPut(m_data.m_K, m_data.m_S, m_data.m_sig, r, m_data.m_b);
			}
		}

		// price function with strike K
		double AmericanOption::Price_K(const double K) const
		{
			if (m_type == AmeriCall)
			{
				return AmericanCall(K, m_data.m_S, m_data.m_sig, m_data.m_r, m_data.m_b);
			}
			else // m_type = AmeriPut
			{
				return AmericanPut(K, m_data.m_S, m_data.m_sig, m_data.m_r, m_data.m_b);
			}
		}

		// price function with cost of carry b
		double AmericanOption::Price_b(const double b) const
		{
			if (m_type == AmeriCall)
			{
				return AmericanCall(m_data.m_K, m_data.m_S, m_data.m_sig, m_data.m_r, b);
			}
			else // m_type = AmeriPut
			{
				return AmericanPut(m_data.m_K, m_data.m_S, m_data.m_sig, m_data.m_r, b);
			}
		}

		// overload price function with stock price vector as parameter 
		vector<double> AmericanOption::Price_S(const vector<double> S_vec) const
		{
			vector<double> OptPrice_vec; // create a vector to store the option prices corresponding to each element in stock price vector
			for (int i = 0; i < S_vec.size(); ++i)
			{
				OptPrice_vec.push_back(Price_S(S_vec[i])); // calculate the option price for the given stock price, and push it into the option price vector
			}
			return OptPrice_vec;
		}

		// overload price function with data matrix as parameter 
		// notice the input matrix contain the parameter vector following the order S, K, r, sig, and b. 
		vector<vector<double>> AmericanOption::Price(vector<vector<double>> S_K_r_sig_b_matrix) const
		{
			vector<vector<double>> OptPrice_matrix; // create an option price matrix corresponding to the input parameter matrix 
			vector<double> OptPrice_vec; // create a vector to store option prices corresponding to each increasing parameter
			for (int i = 0; i < S_K_r_sig_b_matrix.size(); ++i)
			{
				for (int j = 0; j < S_K_r_sig_b_matrix[i].size(); ++j)
				{
					switch (i)
					{
					case 0: OptPrice_vec.push_back(Price_S(S_K_r_sig_b_matrix[i][j])); break;   // push option price corresponding to the changing S in row one 
					case 1: OptPrice_vec.push_back(Price_K(S_K_r_sig_b_matrix[i][j])); break;   // push option price corresponding to the changing K in row two 
					case 2: OptPrice_vec.push_back(Price_r(S_K_r_sig_b_matrix[i][j])); break;   // push option price corresponding to the changing r in row four 
					case 3: OptPrice_vec.push_back(Price_sig(S_K_r_sig_b_matrix[i][j])); break; // push option price corresponding to the changing sig in row five
					case 4: OptPrice_vec.push_back(Price_b(S_K_r_sig_b_matrix[i][j])); break;   // push option price corresponding to the changing b in row six

					default: break;
					}
				}
				OptPrice_matrix.push_back(OptPrice_vec); // push the option price vector into the option price matrix 
				OptPrice_vec.clear(); // clear the option price vector at the end of each loop 
			}

			return OptPrice_matrix;
		}

	}
}

