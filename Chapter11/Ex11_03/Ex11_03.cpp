//Ex11_03.cpp
import<iostream>;
import roman;

int main()
{
	std::cout << "MMXX in Arabic numerals is " << from_roman("MMXX") <<std::endl;
	std::cout << "1234 in Roman numerals is " << to_roman(1234).data() << std::endl;
	std::cout << "This consists of " << to_roman(1234).size() << " numerals" << std::endl;

	auto roman{ to_roman(567) };
	std::cout << "567 in Roman numerals is " << roman.c_str() << std::endl;

	//to_roman(1234).data()、to_roman.c_str()和to_roman(1234)三者的区别是什么？
	//教材中的to_roman(1234).c_data()是错的，没有这个成员函数

	//教材说没有import<string>;的话此行会出错，但我测试了没有问题，可能是编译器的原因
	std::cout << "1234 in Roman numerals is " << to_roman(1234) << std::endl;

	std::cin.get();
}