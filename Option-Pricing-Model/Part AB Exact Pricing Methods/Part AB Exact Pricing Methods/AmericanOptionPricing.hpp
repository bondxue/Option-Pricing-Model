//AmericanOptionPricing.hpp
//purpose: header file for percetural American Option pricing functions 
//author: bondxue
//version: 1.0 11/18/2017

#ifndef AMERICANOPTIONPRICING_HPP
#define AMERICANOPTIONPRICING_HPP

#include <cmath>

namespace OPTION
{
	namespace AMERICANOPTION
	{
		// function that obtain perpetual American call option price
		double AmericanCall(double K, double S, double sig, double r, double b)
		{
			double sig2 = sig*sig;
			double fac = b / sig2 - 0.5; fac *= fac;
			double y1 = 0.5 - b / sig2 + sqrt(fac + 2.0*r / sig2);

			if (y1 == 1.0)
			{
				return S;
			}


			double fac2 = ((y1 - 1.0)*S) / (y1 * K);
			double c = K * pow(fac2, y1) / (y1 - 1.0);

			return c;
		}

		// function that obtain perpetual American put option price
		double AmericanPut(double K, double S, double sig, double r, double b)
		{
			double sig2 = sig*sig;
			double fac = b / sig2 - 0.5; fac *= fac;
			double y2 = 0.5 - b / sig2 - sqrt(fac + 2.0*r / sig2);

			if (y2 == 0.0)
			{
				return S;
			}

			double fac2 = ((y2 - 1.0)*S) / (y2 * K);
			double p = K * pow(fac2, y2) / (1.0 - y2);

			return p;
		}
	}
}

#endif