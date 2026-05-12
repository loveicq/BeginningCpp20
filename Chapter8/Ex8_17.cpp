// Ex8_17.cpp
//  Sorting words recursively
#include <iostream>
#include <format>
#include <memory>
#include <vector>

using Words = std::vector<std::shared_ptr<std::string>>;

void swap(Words &words, size_t first, size_t second);
void sort(Words &words);
void sort(Words &words, size_t start, size_t end);
void extract_words(Words &words, const std::string &text, const std::string &separators);
void show_words(const Words &words);
size_t max_word_length(const Words &words);

int main()
{
    Words words;
    std::string text;                   // The string to be sorted
    const auto separators{" ,.!?\"\n"}; // Word delimiters

    // Read the string to be processed from the dkyboard
    std::cout << "Enter a string terminated by *:" << std::endl;
    getline(std::cin, text, '*');
    extract_words(words, text, separators);
    if (words.empty())
    {
        std::cout << "No words in text." << std::endl;
        return 0;
    }

    sort(words);       // Sort the words
    show_words(words); // Output the words
}
