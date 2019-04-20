//NormalFunction.hpp
//purpose: source file for normal distribution functions 
//author: bondxue
//version: 1.0 11/18/2017

#ifndef NORMALFUNCTION_HPP
#define NORMALFUNCTION_HPP

#include <cmath>
#include <iostream>
#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions.hpp> // For non-member functions of distributions
using namespace boost::math;

namespace OPTION
{
	namespace EUROPEANOPTION
	{
		// standard Normal Cumulative Distribution Function
		double N(const double x)
		{
			normal_distribution<double> myNormal(0.0, 1.0);

			return cdf(myNormal, x);
		}

		// standard Normal Probability Distribution Function
		double n(const double x)
		{
			normal_distribution<double> myNormal(0.0, 1.0);

			return pdf(myNormal, x);
		}
	}
}

#endif


