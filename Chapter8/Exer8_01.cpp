/*************************第8章_练习_第1题************************
编写一个函数validate_input()，它接收两个整数实参，表示所输入整数的上
下限。它接收的第三个实参是描述输入的字符串，用于提示用户进行输入。该函
数会提示所输入的值应在前两个实参指定的范围内，并包含标识输入值类型的字
符串。该函数应检查输入并一直提示用户输入值，直到输入的值有效为止。在程
序中使用validate_input()函数，获取用户的生日并以下面的格式输出：
You were born on the 21st of November,2012
这个程序应使各个函数month()、year()和day()管理对应数字的输入，不要忘
了闰年。2017年2月29日是不允许输入的。
*****************************************************************/

#include <iostream>
#include <format>
#include <string>

int validate_input(int lower, int upper, const std::string &description);
int year();
int month();
int date(int month_value, int year_value);
std::string ending(int date_day);

int main()
{
    std::cout << "Enter your date of borth." << std::endl;
    int date_year{year()};
    int date_month{month()};
    int date_day{date(date_month, date_year)};

    std::string months[]{"January", "February", "March",
                         "April", "May", "June",
                         "July", "August", "September",
                         "October", "November", "December"};

    std::cout << std::endl;
    std::cout << std::format("You were born on the {} of {}, {}.",
                             std::to_string(date_day) + ending(date_day),
                             months[date_month - 1],
                             date_year)
              << std::endl;
}

// 读取一个介于最小值和最大值之间的整数
int validate_input(int lower, int upper, const std::string &description)
{
    int data{};
    std::cout << std::format("Please enter {} from {} to {}: ", description, lower, upper);
    std::cin >> data;
    while (data < lower || data > upper)
    {
        std::cout << "Invalid entry; please re-enter " << description << ": ";
        std::cin >> data;
    }

    return data;
}

// 读取年份
int year()
{
    const int low_year{1870};
    const int high_year{2020};
    return validate_input(low_year, high_year, "a year");
}

// 读取月份
int month()
{
    const int low_month{1};
    const int high_month{12};
    return validate_input(low_month, high_month, "a month number");
}

// 读取给定年份和月份的日期
int date(int month, int year)
{
    const int date_min{1};
    const int feb{2};

    // Days in month:           Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec
    static const int date_max[]{31, 28, 31, 30, 31, 30, 31, 30, 31, 30, 31, 30};
    /*由于上面的数组被声明为静态，它只会在函数第一次被调用时被创建。当然，在这个例子中
    ，这并没有保存任何东西，因为我们只调用它一次…*/

    // 闰年的二月有29天。闰年是指能被4整除的年份，但能被100整除而不能被400整除的年份除外。
    if (month == feb && year % 4 == 0 && !(year % 100 == 0 && year % 400 != 0))
        return validate_input(date_min, 29, "a date");
    else
        return validate_input(date_min, date_max[month - 1], "a date");
}

/*如果数字结尾是：
├─ 1 → st  (1st, 21st, 31st...)
├─ 2 → nd  (2nd, 22nd...)
├─ 3 → rd  (3rd, 23rd...)
└─ 4,5,6,7,8,9,0 → th  (4th, 15th, 26th, 30th...)

但 11, 12, 13 例外，都用 th！
加后缀都是英文日期的习惯表示法而已*/
std::string ending(int date_day)
{
    if (date_day == 1 || date_day == 21 || date_day == 31)
        return "st";
    else if (date_day == 2 || date_day == 22)
        return "nd";
    else if (date_day == 3 || date_day == 23)
        return "rd";
    else
        return "th";
}