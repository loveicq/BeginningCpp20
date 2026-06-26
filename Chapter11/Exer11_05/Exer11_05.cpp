//Exer11_05.cpp
import<string>;
import<iostream>;
import words;

int main()
{
	words::Words the_words;
	std::string text;
	const auto separators{ " ,.!?\"\n" };

	std::cout << "Enter a string terminated by *:" << std::endl;
	getline(std::cin, text, '*');

	words::extract_words(the_words, text, separators);
	if (the_words.empty())
	{
		std::cout << "No words in text." << std::endl;
		return 0;
	}

	words::sort(the_words);
	words::show_words(the_words);
}