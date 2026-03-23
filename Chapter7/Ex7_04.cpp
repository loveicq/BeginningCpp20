// Ex7_04.cpp
// Searching within strings
#include <iostream>
#include <string>

int main()
{
    std::string sentence{"Manners maketh man"};
    std::string word{"man"};

    std::cout << sentence.find(word) << std::endl;
    std::cout << sentence.find("Ma") << std::endl;
    std::cout << sentence.find('k') << std::endl;
    std::cout << sentence.find('x') << std::endl;
}