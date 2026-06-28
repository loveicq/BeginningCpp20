//Exer11_06.cpp
/*************************第11章_练习_第6题************************
仍然将第2题的解决方案作为起点，确保也能够使用wrds和w限定这个名称空间中
的所有名称。应该使用两种不同的方法。需要注意，在生产质量的代码中，不应该
使用晦涩难懂的缩写词（如wrds）或只有一个字母的标识符（如w）：清晰性总是
比简洁性更重要。
*****************************************************************/
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