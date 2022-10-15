#ifndef ___PROJECT_3_CONVERT_HPP
#define ___PROJECT_3_CONVERT_HPP

#include <string>
#include <vector>
#include "Wordset.hpp"

void loadWordsIntoTable(WordSet & words, std::istream & in);


std::vector< std::string > convert(const std::string & s1, const std::string & s2, const WordSet & words);



#endif
