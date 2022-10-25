#include "Wordset.hpp"
#include <string>
#include <cmath>
#include <iostream>

// returns s, as a number in the given base, mod the given modulus
unsigned polynomialHashFunction(const std::string & s, unsigned base, unsigned mod)
{
	unsigned hashVal = 0, size = s.size()-1;
	for(const auto &i : s)
	{
		unsigned power = 1;
		for(int i = 0; i < size; ++i)
		{
			power *= base;
		}
		hashVal = (hashVal + (i - 'a' + 1) * power) % mod;
		--size;
	}
	hashVal %= mod;
	return hashVal;
}

WordSet::WordSet(unsigned long long initialCapacity, unsigned evictionThreshold):hashTbalecapacity(initialCapacity), strCount(0), evictionThreshold(evictionThreshold)
{
	hashTable1 = new std::string[hashTbalecapacity];
	hashTable2 = new std::string[hashTbalecapacity];
	for(size_t i = 0; i < hashTbalecapacity; ++i)
	{
		hashTable1[i] = std::string();
		hashTable2[i] = std::string();
	}
}

WordSet::~WordSet()
{
	if(!hashTable1)
	{
		delete [] hashTable1;
		hashTable1 = nullptr;
	}
	if(!hashTable2)
	{
		delete [] hashTable2;
		hashTable2 = nullptr;
	}
}

void WordSet::insert(const std::string & s)
{
	insertHelper(s);
	++strCount;
}

void WordSet::insertHelper(const std::string & s)
{
	if(contains(s)) return;
	bool switcher = true;
	std::string newStr = s;
	for(int i = 0; i < evictionThreshold; ++i)
	{
		unsigned index1 = polynomialHashFunction(newStr, BASE_H1, hashTbalecapacity);
		unsigned index2 = polynomialHashFunction(newStr, BASE_H2, hashTbalecapacity);
		if(hashTable1[index1] == std::string())
		{
			hashTable1[index1] = newStr;
			break;
		}
		else if(hashTable2[index2] == std::string())
		{
			hashTable2[index2] = newStr;
			break;
		}
		if(switcher)
		{
			std::string temp = newStr;
			newStr = hashTable1[index1];
			hashTable1[index1] = temp;
		}
		else 
		{
			std::string temp = newStr;
			newStr = hashTable2[index2];
			hashTable2[index2] = temp;
		}
		switcher = !switcher;
		if(i + 1 == evictionThreshold)
		{
			unsigned prevCapacity = hashTbalecapacity;
			hashTbalecapacity = getNextPrimeNum(hashTbalecapacity);
			std::string* table1 = hashTable1;
			std::string* table2 = hashTable2;
			hashTable1 = new std::string[hashTbalecapacity];
			hashTable2 = new std::string[hashTbalecapacity];
			resize(table1, table2, prevCapacity);
			delete [] table1;
			table1 = nullptr;
			delete [] table2;
			table2 = nullptr;
			i = -1;
		}
	}
}


bool WordSet::contains(const std::string & s) const
{
	unsigned hashVal = polynomialHashFunction(s, BASE_H1, hashTbalecapacity);
	if(hashTable1[hashVal] == s) return true;
	hashVal = polynomialHashFunction(s, BASE_H2, hashTbalecapacity);
	if(hashTable2[hashVal] == s) return true;
	return false;
}

// return how many distinct strings are in the set
unsigned WordSet::getCount() const
{
	return strCount; // this is not the right answer. 
}

// return how large the underlying array is.
unsigned WordSet::getCapacity() const
{
	return hashTbalecapacity; // that isn't even a prime number!
}

void WordSet::resize(std::string* table1, std::string* table2, unsigned prevCapacity)
{
	for(size_t i = 0; i < prevCapacity; ++i)
	{
		if(table1[i] != std::string())
		{
			insertHelper(table1[i]);
		}
		if(table2[i] != std::string())
		{
			insertHelper(table2[i]);
		}
	}
}

bool WordSet::isPrimeNum(const unsigned long long & num)
{
	auto squareRoot = std::sqrt(num);
	for(unsigned i = 2; i <= squareRoot; ++i)
	{
		if(num % i == 0) return false;
	}
	return true;
}

unsigned long WordSet::getNextPrimeNum(const unsigned long & currentPrimeNum)
{
	unsigned result = currentPrimeNum * 2;
	while(!isPrimeNum(result))
	{
		result += 1;
	}
	return result;
}

void WordSet::erase(const std::string & s)
{
	if(!contains(s)) return;
	unsigned hashVal = polynomialHashFunction(s, BASE_H1, hashTbalecapacity);
	if(hashTable1[hashVal] == s)
	{
		hashTable1[hashVal] = std::string();
	}
	hashVal = polynomialHashFunction(s, BASE_H2, hashTbalecapacity);
	if(hashTable2[hashVal] == s)
	{
		hashTable2[hashVal] = std::string();
	}
}