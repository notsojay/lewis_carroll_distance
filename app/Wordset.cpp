#include "Wordset.hpp"
#include <string>


// returns s, as a number in the given base, mod the given modulus
unsigned polynomialHashFunction(const std::string & s, unsigned base, unsigned mod)
{
	return 0; // this is probably not correct.
}




WordSet::WordSet(unsigned initialCapacity, unsigned evictionThreshold)
{

}

WordSet::~WordSet()
{

}

void WordSet::insert(const std::string & s)
{

}


bool WordSet::contains(const std::string & s) const
{
	return false;  // stub, not correct.
}

// return how many distinct strings are in the set
unsigned WordSet::getCount() const
{
	return BASE_H1 + BASE_H2; // this is not the right answer. 
}

// return how large the underlying array is.
unsigned WordSet::getCapacity() const
{
	return 1729; // that isn't even a prime number!
}
