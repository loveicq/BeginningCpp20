// 测试insert()函数
#include <iostream>
#include <string>

int main()
{
    const std::string ORIGINAL_PHRASE{"We can insert a string."};
    std::string phrase{ORIGINAL_PHRASE};
    std::string words{"a string into "};

    phrase.insert(14, words);         // 插入string对象,phrase字符串第14位字符是'a'
    std::cout << phrase << std::endl; //"We can insert a string into a string."

    phrase = ORIGINAL_PHRASE;
    phrase.insert(14, "a string into "); // 插入C样式字符串
    std::cout << phrase << std::endl;    //"We can insert a string into a string."

    phrase = ORIGINAL_PHRASE;
    phrase.insert(13, words, 8, 5);   // 插入string对象其中一部分内容,words第8位开始,取5个字符,即" into"
    std::cout << phrase << std::endl; //"We can insert into a string.
}