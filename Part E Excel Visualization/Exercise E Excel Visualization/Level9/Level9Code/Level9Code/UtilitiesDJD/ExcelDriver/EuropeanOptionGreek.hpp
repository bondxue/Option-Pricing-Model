//EuropeanOptionGreek.hpp
//purpose: header file for European option Greeks
//author: bondxue
//version: 1.0 11/21/2017

#ifndef EUROPEANOPTIONGREEK_H
#define EUROPEANOPTIONGREEK_H

#include "NormalFunction.hpp"
#include <cmath>

namespace OPTION
{
	namespace EUROPEANOPTION
	{
		// Delta of Call option
		double CallDelta(double S, double K, double T, double r, double sig, double b)
		{
			double temp = sig* sqrt(T);
			double d1 = (log(S / K) + (b + sig*sig*0.5) * T) / temp;

			return exp((b - r)*T) * N(d1);
		}

		// Delta of Put option
		double PutDelta(double S, double K, double T, double r, double sig, double b)
		{
			double temp = sig * sqrt(T);
			double d1 = (log(S / K) + (b + (sig*sig)*0.5) * T) / temp;

			return exp((b - r)*T) * (N(d1) - 1.0);
		}

		// Gamma of Call option
		double CallGamma(double S, double K, double T, double r, double sig, double b)
		{
			double temp = sig* sqrt(T);
			double d1 = (log(S / K) + (b + sig*sig*0.5) * T) / temp;

			return (n(d1)*exp((b - r)*T)) / (S*temp);
		}

		// Gamma of Put option
		double PutGamma(double S, double K, double T, double r, double sig, double b)
		{
			return CallGamma(S, K, T, r, sig, b); // since Gamma(P) = Gamma(C)
		}
	}
}

#endif