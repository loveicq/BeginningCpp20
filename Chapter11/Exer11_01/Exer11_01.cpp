// 将 Ex8_17.cpp 中的所有函数（而非文中所说的 Ex8_18.cpp）
//  移到 words 模块中，只导出 main() 函数使用的函数。
import <string>;
import <iostream>;
import words;

int main()
{
	words::Words the_words;				// 重命名以避免与 words 命名空间冲突！
	std::string text;					// 要排序的字符串
	const auto separators{" ,.!?\"\n"}; // 单词分隔符

	// 从键盘读取要处理的字符串
	std::cout << "Enter a string terminated by *:" << std::endl;
	std::getline(std::cin, text, '*');

	words::extract_words(the_words, text, separators);
	if (the_words.empty())
	{
		std::cout << "No words in text." << std::endl;
		return 0;
	}

	words::sort(the_words);		  // 对单词进行排序
	words::show_words(the_words); // 输出单词

	std::cin.get();
}