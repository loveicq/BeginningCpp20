export module words;

import <iostream>;
import <format>;
import <memory>;
import <string>;
import <vector>;

export namespace words
{
	using Words = std::vector<std::shared_ptr<std::string>>;

	void sort(Words &words);
	void extract_words(Words &words, const std::string &text, const std::string &separators);
	void show_words(const Words &words);
}

namespace words
{
	size_t max_word_length(const Words &words);
}

void words::extract_words(Words &words, const std::string &text, const std::string &separators)
{
	size_t start{text.find_first_not_of(separators)}; // 第一个单词的起始索引

	while (start != std::string::npos)
	{
		size_t end{text.find_first_of(separators, start + 1)}; // 查找单词的结束位置
		if (end == std::string::npos)						   // 找到分隔符了吗？
			end = text.length();							   // 是的，所以设置为文本末尾
		words.push_back(std::make_shared<std::string>(text.substr(start, end - start)));
		start = text.find_first_not_of(separators, end + 1); // 查找下一个单词的起始位置
	}
}

/* word::sort(Words&) 的附加辅助函数 */
namespace words
{
	void swap(Words &words, size_t first, size_t second)
	{
		auto temp{words[first]};
		words[first] = words[second];
		words[second] = temp;
	}

	void sort(Words &words, size_t start, size_t end);
}

// 按升序对字符串排序

void words::sort(Words &words)
{
	if (!words.empty())
		sort(words, 0, words.size() - 1);
}

void words::sort(Words &words, size_t start, size_t end)
{
	// 对于2个或更多元素，起始索引必须小于结束索引
	if (!(start < end))
		return;

	// 选择中间位置来分割集合
	swap(words, start, (start + end) / 2); // 将中间位置与起始位置交换

	// 将单词与选中的单词进行比较
	size_t current{start};
	for (size_t i{start + 1}; i <= end; i++)
	{
		if (*words[i] < *words[start]) // 该单词是否小于选中的单词？
			swap(words, ++current, i); // 是的，所以交换到左边
	}

	swap(words, start, current); // 交换选中的单词和最后交换的单词

	if (current > start)
		sort(words, start, current - 1); // 如果存在左子集则排序
	if (end > current + 1)
		sort(words, current + 1, end); // 如果存在右子集则排序
}

size_t words::max_word_length(const Words &words)
{
	size_t max{};
	for (auto &pword : words)
		if (max < pword->length())
			max = pword->length();
	return max;
}

void words::show_words(const Words &words)
{
	const size_t field_width{max_word_length(words) + 1};
	const size_t words_per_line{8};
	std::cout << std::format("{:{}}", *words[0], field_width); // 输出第一个单词

	size_t words_in_line{}; // 当前行的单词数
	for (size_t i{1}; i < words.size(); ++i)
	{
		// 当初始字母改变或每行达到8个单词时输出换行
		if ((*words[i])[0] != (*words[i - 1])[0] || ++words_in_line == words_per_line)
		{
			words_in_line = 0;
			std::cout << std::endl;
		}
		std::cout << std::format("{:{}}", *words[i], field_width); // 输出一个单词
	}
	std::cout << std::endl;
}