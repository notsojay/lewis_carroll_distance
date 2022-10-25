#ifndef ___PROJECT_3_CONVERT_HPP
#define ___PROJECT_3_CONVERT_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include "Wordset.hpp"

void loadWordsIntoTable(WordSet & words, std::istream & in);


std::vector< std::string > convert(const std::string & s1, const std::string & s2, const WordSet & words);

void getPath(const std::unordered_map<std::string, std::string> & paths, std::vector< std::string > & ret, const std::string & s2, const int & distance);

#endif
