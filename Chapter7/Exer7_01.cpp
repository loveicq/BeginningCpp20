/*************************第7章_练习_第1题************************
编写一个程序，读取并存储任意多个学生的名字及其成绩。计算并输出平均成绩，
在一个表格中输出所有学生的名字和成绩，每一行输出3个学生的名字和成绩。
*****************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <format>
#include <cctype>

int main()
{
	std::vector<double> grades;
	std::vector<std::string> names;
	double totalGrade{};
	size_t maxLength{};

	while (true)
	{
		std::string name;
		std::cout << "请输入学生姓名：";
		std::getline(std::cin, name);
		while (!name.length())
		{
			std::cout << "请输入学生姓名：";
			std::getline(std::cin, name);
		}
		names.push_back(name);
		if (maxLength < name.length())
		{
			maxLength = name.length();
		}

		double grade{};
		std::cout << "请输入成绩：";
		std::cin >> grade;
		while (grade < 0 || grade > 100)
		{
			std::cout << "成绩必须为0~100之间，请输入成绩：";
			std::cin >> grade;
		}
		grades.push_back(grade);
		totalGrade += grade;

		char confirmChar{};
		std::cout << "输入另一组记录？(Y/N):";
		std::cin >> confirmChar;
		confirmChar = std::toupper(confirmChar);
		while (confirmChar != 'Y' && confirmChar != 'N')
		{
			std::cout << "请输入Y或N：";
			std::cin >> confirmChar;
			confirmChar = std::toupper(confirmChar);
		}
		if (confirmChar == 'N')
		{
			break;
		}

		std::cin.ignore();
	}

	if (names.size())
	{
		std::cout << std::format("\n共有{}名学生，平均成绩为{:.2f}。\n", names.size(), totalGrade / names.size());
	}

	size_t perline{3};
	for (size_t i{}; i < names.size(); ++i)
	{
		std::cout << std::format("{:<{}} {:>4}  ", names[i], maxLength, grades[i]);
		if ((i + 1) % perline == 0)
		{
			std::cout << std::endl;
		}
	}

	std::cout << std::endl;
}
