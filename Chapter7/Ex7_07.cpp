// Ex7_07.cpp
// Replacing words in a string
#include <iostream>
#include <string>

int main()
{
    std::string text;
    std::cout << "Enter a string terminated by *:\n";
    std::getline(std::cin, text, '*');

    std::string word;
    std::cout << "Enter the word to be replaced: ";
    std::cin >> word;

    std::string replacement;
    std::cout << "Enter the string to be substituted for " << word << ": ";
    std::cin >> replacement;

    if (word == replacement)
    {
        std::cout << "The word its replacement are the same.\n"
                  << "Operation aborted." << std::endl;
        return 1;
    }

    size_t start{text.find(word)};
    while (start != std::string::npos)
    {
        text.replace(start, word.length(), replacement);
        start = text.find(word, start + replacement.length());
    }

    std::cout << "\nThe string you entered is now:\n"
              << text << std::endl;
}