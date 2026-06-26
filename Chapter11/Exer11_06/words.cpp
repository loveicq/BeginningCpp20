//words.cpp
module words;

import <iostream>;
import <format>;

size_t max_word_length(const words::Words& words);

void words::extract_words(Words& words, const std::string& text, const std::string& separators)
{
	size_t start{ text.find_first_not_of(separators) };

	while (start != std::string::npos)
	{
		size_t end{ text.find_first_of(separators, start + 1) };
		if (end == std::string::npos)
			end = text.length();
		words.push_back(std::make_shared<std::string>(text.substr(start, end - start)));
		start = text.find_first_not_of(separators, end + 1);
	}
}

void swap(words::Words& words, size_t first, size_t second)
{
	auto temp{ words[first] };
	words[first] = words[second];
	words[second] = temp;
}

void sort(words::Words& words, size_t start, size_t end);

void words::sort(Words& words)
{
	if (!words.empty())
		::sort(words, 0, words.size() - 1);
}

void sort(words::Words& words, size_t start, size_t end)
{
	if (!(start < end))
		return;

	swap(words, start, (start + end) / 2);

	size_t current{ start };
	for (size_t i{ start + 1 }; i <= end; i++)
	{
		if (*words[i] < *words[start])
			swap(words, ++current, i);
	}

	swap(words, start, current);

	if (current > start) sort(words, start, current - 1);
	if (end > current + 1) sort(words, current + 1, end);
}

size_t max_word_length(const words::Words& words)
{
	size_t max{};
	for (auto& pword : words)
		if (max < pword->length()) max = pword->length();
	return max;
}

void words::show_words(const Words& words)
{
	const size_t field_width{ max_word_length(words) + 1 };
	const size_t words_per_line{ 8 };
	std::cout << std::format("{:{}}", *words[0], field_width);

	size_t words_in_line{};
	for (size_t i{ 1 }; i < words.size(); ++i)
	{
		if ((*words[i])[0] != (*words[i - 1])[0] || ++words_in_line == words_per_line)
		{
			words_in_line = 0;
			std::cout << std::endl;
		}
		std::cout << std::format("{:{}}", *words[i], field_width);
	}
	std::cout << std::endl;
}