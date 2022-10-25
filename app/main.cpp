#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "Wordset.hpp"
#include "convert.hpp"

int main()
{


    WordSet words(11);
    std::ifstream in("words.txt");
    loadWordsIntoTable(words, in);
    std::cout <<words.getCapacity() << "\n" << words.getCount() << '\n';
    
    std::vector< std::string > r  = convert("ant", "eat", words);
    for(auto &i : r)
        std::cout << i << "  ";
    return 0;
}

    