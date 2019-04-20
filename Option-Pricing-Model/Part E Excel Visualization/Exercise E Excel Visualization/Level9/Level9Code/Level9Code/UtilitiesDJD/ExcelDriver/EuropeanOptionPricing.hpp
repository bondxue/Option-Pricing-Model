//EuropeanOptionPricing.hpp
//purpose: header file for all European Option pricing functions 
//author: bondxue
//version: 1.0 11/18/2017

#ifndef EUROPEANOPTIONPRICING_HPP
#define EUROPEANOPTIONPRICING_HPP

#include <cmath>
#include "NormalFunction.hpp"

namespace OPTION
{
	namespace EUROPEANOPTION
	{
		// function to obtain d1
		double cal_d1(const double S, const double K, const double T, const double sig, const double b)
		{
			double d1;
			d1 = (log(S / K) + (b + sig*sig*0.5)*T) / (sig*sqrt(T));
			return d1;
		}

		// function to obtain d2
		double cal_d2(const double d1, const double sig, const double T)
		{
			double d2;
			d2 = d1 - sig* sqrt(T);
			return d2;
		}

		// function to obtain European call option price 
		double EuropeanCall(const double S, const double K, const double T, const double r, const double b, const double sig)
		{
			double d1 = cal_d1(S, K, T, sig, b);
			double d2 = cal_d2(d1, sig, T);
			double C = S*exp((b - r)*T)*N(d1) - K*exp(-r*T)*N(d2);

			return C;
		}

		// function to obtain European put option price
		double EuropeanPut(const double S, const double K, const double T, const double r, const double b, const double sig)
		{
			double d1 = cal_d1(S, K, T, sig, b);
			double d2 = cal_d2(d1, sig, T);
			double P = K*exp(-r*T)* N(-d2) - S* exp((b - r)*T)* N(-d1);

			return P;
		}

		// functoin to obatain European call option price using put-call parity
		double EuropeanCall_parity(const double S, const double K, const double T, const double r, const double P)
		{
			double C = P + S - K*exp(-r*T);
			return C;
		}

		// functoin to obatain European put option price using put-call parity
		double EuropeanPut_parity(const double S, const double K, const double T, const double r, const double C)
		{
			double P = C - S + K*exp(-r*T);
			return P;
		}
	}
}

#endif