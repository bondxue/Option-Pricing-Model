//AmericanOption.hpp
//purpose: header file for American option class
//author: bondxue
//version: 1.0 11/24/2017

#ifndef AMERICANOPTION_HPP
#define AMERICANOPTION_HPP

#include "Option.hpp"
#include <vector>

using namespace std;

namespace OPTION
{
	namespace AMERICANOPTION
	{
		class AmericanOption : public Option
		{
		private:

			Ameri_OptionType m_type; // American Option type
			Ameri_OptionData m_data; // American Option parameters
		public:
			AmericanOption(); // default constructor, default type is call 
			AmericanOption(const AmericanOption& option);	// Copy constructor
			AmericanOption(const double K, const double S, const double sig, const double r, const double b, const Ameri_OptionType type); // constructor with all American option parameters 
			AmericanOption(const Ameri_OptionData data, const Ameri_OptionType type); // constructor with Ameri_OptionData struct as parameter
			virtual ~AmericanOption();	// destructor

			AmericanOption& operator = (const AmericanOption& option2); // assignment operator 

			// Setters to update option parameters and type
			// default inline functions for setters
			void Type(const Ameri_OptionType new_type) { m_type = new_type; }  // setter to update the option type
			void S(const double new_S) { m_data.m_S = new_S; }                 // setter to update the stock price
			void K(const double new_K) { m_data.m_K = new_K; }                 // setter to update the strike price
			void sig(const double new_sig) { m_data.m_sig = new_sig; }         // setter to update the volatility
			void r(const double new_r) { m_data.m_r = new_r; }                 // setter to update the interest rate
			void b(const double new_b){ m_data.m_b = new_b; }                  // setter to update the cost of carry

			// overload Getters to access option parameters and type
			// default inline functions for getters
			Ameri_OptionType Type() const { return m_type; }                   // getter to access the option type
			double S() const { return m_data.m_S; }                            // getter to access the stock price
			double K() const { return m_data.m_K; }                            // getter to access the strike price
			double sig() const { return m_data.m_sig; }                        // getter to access the volatility
			double r() const { return m_data.m_r; }                            // getter to access the interest rate
			double b() const { return m_data.m_b; }                            // getter to access the cost of carry

			// Functions that calculate American option price 
			virtual double Price() const; // price funtion 
			virtual vector<vector<double>> Price(vector<vector<double>> S_K_r_sig_b_matrix) const; // overload price function with data matrix (in the order S, K, T, r, sig) as parameter 
			double Price_S(const double S) const; // price function with stock price S
			vector<double> Price_S(const vector<double> S_vec) const; // overload price function with stock price vector as parameter 
			double Price_sig(const double sig) const; // price function with vloatility sig
			double Price_r(const double r) const; // price function with risk-free intereset rate r
			double Price_K(const double K) const; // price function with strike K
			double Price_b(const double b) const; // price function with cost of carry b

		};
	}
}

#endif