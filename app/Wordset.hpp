#ifndef __WORD_SET___HPP
#define __WORD_SET___HPP


#include <string>
#include <cmath>

// You may assume, in writing this function, that the given
// string consists solely of lower-case letters.

// To get the "number" that a letter-digit represents,
// subtract 'a' from it.
// e.g., (s[0]-'a') is the most significant "digit" of s.
// That would give you a 0 for a, etc;  add one to get 'a' = 1, 'b' = 2, etc. 

// After every "digit" is processed, mod the current value by mod.
// This will keep you from having overflow.
unsigned polynomialHashFunction(const std::string & s, unsigned base, unsigned mod);


class WordSet
{
public: 
	explicit WordSet(unsigned initialCapacity, unsigned evictionThreshold = DEFAULT_EVICT_THRESHOLD);
	
	~WordSet();

	// adds the given string to the WordSet, so that any 
	// future calls to contains(s) will return true.
	// Note that we are not implementing remove in this
	// project.
	// 
	void insert(const std::string & s);

	bool contains(const std::string & s) const;

	// return how many distinct strings are in the set
	unsigned getCount() const; 

	// return how large the underlying array is.
	unsigned getCapacity() const;

private:
	void insertHelper(const std::string & s, std::string* table1, std::string* table2, unsigned & currentCapacity);
	
	void resize(std::string* table1, std::string* table2, unsigned & currentCapacity);
	
	bool isPrimeNum(const unsigned & num);
	
	unsigned getNextPrimeNum(const unsigned & currentPrimeNum);
	
private:
	std::string* hashTable1;
	std::string* hashTable2;
	unsigned hashTbalecapacity;
	unsigned strCount;
	unsigned evictionThreshold;
	static constexpr unsigned BASE_H1 = 37;
	static constexpr unsigned BASE_H2 = 41; 
	// You may declare private functions and member variables here.
	static constexpr unsigned DEFAULT_EVICT_THRESHOLD = 5; 
};


#endif
