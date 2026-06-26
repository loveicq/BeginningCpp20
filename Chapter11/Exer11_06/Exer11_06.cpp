//Exer11_06.cpp
import<string>;
import<iostream>;
import words;

namespace wrds
{
	using namespace words;
}

int main()
{
	wrds::Words the_words;
	std::string text;
	const auto separators{ " ,.!?\"\n" };

	std::cout << "Enter a string terminated by *:" << std::endl;
	getline(std::cin, text, '*');

	w::extract_words(the_words, text, separators);
	if (the_words.empty())
	{
		std::cout << "No words in text." << std::endl;
		return 0;
	}

	wrds::sort(the_words);
	w::show_words(the_words);
}