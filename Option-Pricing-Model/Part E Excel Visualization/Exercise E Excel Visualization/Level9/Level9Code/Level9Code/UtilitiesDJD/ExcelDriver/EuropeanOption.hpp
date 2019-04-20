//EuropeanOption.hpp
//purpose: header file for European option class
//author: bondxue
//version: 1.0 11/24/2017

#ifndef EUROPEANOPTION_HPP
#define EUROPEANOPTION_HPP

#include "Option.hpp"
#include <vector>

using namespace std;

namespace OPTION
{
	namespace EUROPEANOPTION
	{
		class EuropeanOption : public Option
		{
		private:
			Euro_OptionData m_data; // European option parameters 
			Euro_OptionType m_type; // European option type

		public:
			EuropeanOption(); // Default constructor 
			EuropeanOption(const EuropeanOption& option);	// Copy constructor
			EuropeanOption(const double S, const double T, const double K, const double sig, const double r, const double b, const Euro_OptionType type); // constructor with all option parameters 
			EuropeanOption(const Euro_OptionData data, const Euro_OptionType type); // constructor with optiondata struct as parameter
			virtual ~EuropeanOption();	// destructor

			EuropeanOption& operator = (const EuropeanOption& option2); // assignment operator 

			// Setters to update option parameters and type
			// default inline functions for setters
			void Type(const Euro_OptionType new_type) { m_type = new_type; } // setter to update the option type, it has the similar function as the previous toggle() function, which I delete 
			void S(const double new_S) { m_data.m_S = new_S; } // setter to update the stock price
			void K(const double new_K) { m_data.m_K = new_K; } // setter to update the strike price
			void T(const double new_T) { m_data.m_T = new_T; } // setter to update the maturity date
			void sig(const double new_sig) { m_data.m_sig = new_sig; } // setter to update the volatility
			void r(const double new_r) { m_data.m_r = new_r; } // setter to update the interest rate
			void b(const double new_b){ m_data.m_b = new_b; } // setter to update the cost of carry

			// overload Getters to access option parameters and type
			// default inline functions for getters
			Euro_OptionType Type() const { return m_type; } // getter to access the option type
			double S() const { return m_data.m_S; } // getter to access the stock price
			double K() const { return m_data.m_K; } // getter to access the strike price
			double T() const { return m_data.m_T; } // getter to access the maturity date
			double sig() const { return m_data.m_sig; } // getter to access the volatility
			double r() const { return m_data.m_r; } // getter to access the interest rate
			double b() const { return m_data.m_b; } // getter to access the cost of carry

			// Functions that calculate European option price 
			virtual double Price() const; // price funtion 
			virtual vector<vector<double>> Price(vector<vector<double>> S_K_T_r_sig_b_matrix) const; // overload price function with data matrix (in the order S, K, T, r, sig, b) as parameter 
			double Price_S(const double S) const; // price function with stock price S
			vector<double> Price_S(const vector<double> S_vec) const; // overload price function with stock price vector as parameter 
			double Price_T(const double T) const; // price function with expiry time T
			double Price_sig(const double sig) const; // price function with vloatility sig
			double Price_r(const double r) const; // price function with risk-free intereset rate r
			double Price_K(const double K) const; // price function with strike K
			double Price_b(const double b) const; // price function with cost of carry b

			double Price(double optPrice, Euro_OptionType type); // overload price function using put-call parity 
			void PutCallParity_Checking(double optPrice1, Euro_OptionType optType1, double optPrice2, Euro_OptionType optType2);// function to check put-call parity

			// Functions that calculate European option greeks
			double Delta() const; // function that calculates Delta 
			double Gamma() const; // funciton that calculates Gamma
			vector<vector<double>> Delta(vector<vector<double>> S_K_T_r_sig_matrix) const; // overload Delta function with data matrix (in the order S, K, T, r, sig) as parameter


			double Delta_S(const double S) const; // Delta function with stock price S
			vector<double> Delta_S(const vector<double> S_vec) const; // overload Delta function with stock price vector as parameter 
			double Delta_T(const double T) const; // Delta function with expiry time T
			double Delta_sig(const double sig) const; // Delta function with vloatility sig
			double Delta_r(const double r) const; // Delta function with risk-free intereset rate r
			double Delta_K(const double K) const; // Delta function with strike K
			double Delta_b(const double b) const; // Delta function with cost of carry b


			// finite difference approximation of Greeks
			double Delta_f(const double h) const; // finite difference approximation of Delta
			double Gamma_f(const double h) const; // finite difference approximation of Gamma

		};
	}
}


#endif