#include "Wordset.hpp"
#include <string>
#include <cmath>

// returns s, as a number in the given base, mod the given modulus
unsigned polynomialHashFunction(const std::string & s, unsigned base, unsigned mod)
{
	unsigned hashVal = 0, size = s.size()-1;
	for(const auto &i : s)
	{
		unsigned power = power = std::pow(base, size);
		hashVal = (hashVal + (i - 'a' + 1) * power) % mod;
		--size;
	}
	return hashVal;
}

WordSet::WordSet(unsigned initialCapacity, unsigned evictionThreshold):hashTbalecapacity(initialCapacity), strCount(0), evictionThreshold(evictionThreshold)
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
	if(contains(s)) return;
	insertHelper(s, hashTable1, hashTable2, hashTbalecapacity);
	++strCount;
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

void WordSet::insertHelper(const std::string & s, std::string* table1, std::string* table2, unsigned & currentCapacity)
{
	bool switcher = true;
	std::string newStr = s;
	for(int i = 0; i < evictionThreshold; ++i)
	{
		unsigned hashVal1 = polynomialHashFunction(newStr, BASE_H1, currentCapacity);
		unsigned hashVal2 = polynomialHashFunction(newStr, BASE_H2, currentCapacity);
		if(table1[hashVal1] == std::string())
		{
			table1[hashVal1] = newStr;
			break;
		}
		else if(hashTable2[hashVal2] == std::string())
		{
			table2[hashVal2] = newStr;
			break;
		}
		if(switcher)
		{
			std::string temp = newStr;
			newStr = table1[hashVal1];
			table1[hashVal1] = temp;
		}
		else 
		{
			std::string temp = newStr;
			newStr = table2[hashVal2];
			table2[hashVal2] = temp;
		}
		switcher = !switcher;
		if(i + 1 == evictionThreshold)
		{
			resize(table1, table2, currentCapacity);
			i = -1;
		}
	}
}

void WordSet::resize(std::string* table1, std::string* table2, unsigned & currentCapacity)
{
	unsigned newSize = getNextPrimeNum(currentCapacity);
	std::string* newHashTable1 = new std::string[newSize];
	std::string* newHashTable2 = new std::string[newSize];
	for(size_t i = 0; i < hashTbalecapacity; ++i)
	{
		newHashTable1[i] = std::string();
		newHashTable2[i] = std::string();
	}
	for(unsigned i = 0; i < hashTbalecapacity; ++i)
	{
		if(table1[i] != std::string())
		{
			insertHelper(table1[i], newHashTable1, newHashTable2, newSize);
		}
		if(table2[i] != std::string())
		{
			insertHelper(table2[i], newHashTable1, newHashTable2, newSize);
		}
	}
	currentCapacity = newSize;
	std::swap(table1, newHashTable1);
	std::swap(table2, newHashTable2);
	delete [] newHashTable1;
	newHashTable1 = nullptr;
	delete [] newHashTable2;
	newHashTable2 = nullptr;
}

bool WordSet::isPrimeNum(const unsigned & num)
{
	auto squareRoot = std::sqrt(num);
	for(unsigned i = 2; i <= squareRoot; ++i)
	{
		if(num % i == 0) return false;
	}
	return true;
}

unsigned WordSet::getNextPrimeNum(const unsigned & currentPrimeNum)
{
	if(currentPrimeNum < 2) return 2;
	unsigned result = currentPrimeNum * 2;
	while(!isPrimeNum(result))
	{
		result += 1;
	}
	return result;
}