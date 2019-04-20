//Option.hpp
//purpose: header file for abstract class Option 
//author: bondxue
//version: 1.0 11/23/2017

#ifndef OPTION_HPP
#define OPTION_HPP

namespace OPTION
{

	class Option
	{
	public:
		Option(); // default constructor
		Option(const Option& source); // copy constructor
		virtual ~Option(); // virtual destructor

		// assignment operator. Since no member data, nothing to assign.
		// so it has no corresponding code in the source file
		Option& operator = (const Option& source);

		// pure virtual member function Price(), which has an empty implement. 
		// so it has no corresponding code in the source file
		virtual double Price() const = 0;
	};

	// European option type enum
	enum Euro_OptionType
	{
		EuroCall, // European Call type
		EuroPut   // European Put type
	};

	// struct to store European option data
	// 1. create outside the European Option calss to increase the reusablilty of the struct
	// 2. add stock price S in the struct so that each batch will be regarded as an instance of Euro_OptionData 
	struct Euro_OptionData
	{
		double m_S; // stock price
		double m_K; // strike price
		double m_T; // maturity date
		double m_r; // risk-free interest rate
		double m_sig; // volatility
		double m_b; // cost of carry

		// constructor with initial values 
		Euro_OptionData(double S, double K, double T, double r, double sig, double b) : m_S(S), m_K(K), m_T(T), m_r(r), m_sig(sig), m_b(b)
		{
		}
	};

	// American option type enum
	enum Ameri_OptionType
	{
		AmeriCall, // American Call type
		AmeriPut   // American Put type
	};

	// struct to store American option data
	// notice that American option does not have maturity date T parameter.That's why I create Ameri_OptionData separately from Euro_OptionData.
	// I didn't put the common parameters for Eurpean and American option into the base class Option in case some other options may have different parameters.
	struct Ameri_OptionData
	{
		double m_S; // stock price
		double m_K; // strike price
		double m_r; // risk-free interest rate
		double m_sig; // volatility
		double m_b; // cost of carry

		// constructor with initial values 
		Ameri_OptionData(double K, double S, double sig, double r, double b) : m_K(K), m_S(S), m_sig(sig), m_r(r), m_b(b)
		{
		}
	};

}

#endif