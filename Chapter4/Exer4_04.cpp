#include <iostream>
#include <cctype>

int main()
{
    // 处理年龄
    unsigned int age{};
    std::cout << "请输入你的年龄: ";
    std::cin >> age;
    if (age >= 130)
    {
        std::cout << "你在开玩笑吗?" << std::endl;
        return 1;
    }

    // 处理性别
    char gender{};
    std::cout << "请输入你的性别,男[m],女[f],其他[o]: ";
    std::cin >> gender;
    gender = std::tolower(gender);
    if (gender != 'f' && gender != 'm' && gender != 'o')
    {
        std::cout << "你在开玩笑吗?" << std::endl;
        return 1;
    }

    // 处理学历
    enum class AcademicDegree
    {
        none,
        associate,
        bachelor,
        professional,
        master,
        doctor
    };
    AcademicDegree degree;
    std::cout
        << "可能的学历:\n"
        << "\tn: 无学历\n"
        << "\ta: 副学士\n"
        << "\tb: 学士\n"
        << "\tp: 本科\n"
        << "\tm: 硕士\n"
        << "\td: 博士\n"
        << "你的最高学历是:";
    char degreeChar{};
    std::cin >> degreeChar;

    switch (degreeChar)
    {
    case 'n':
        degree = AcademicDegree::none;
        break;
    case 'a':
        degree = AcademicDegree::associate;
        break;
    case 'b':
        degree = AcademicDegree::bachelor;
        break;
    case 'p':
        degree = AcademicDegree::professional;
        break;
    case 'm':
        degree = AcademicDegree::master;
        break;
    case 'd':
        degree = AcademicDegree::doctor;
        break;
    default:
        std::cout << "你在开玩笑?\n";
        return 1;
    }

    char yes_no{};

    // 处理婚姻情况
    bool married{};
    std::cout << "你结婚了吗?已婚[y],未婚[n]: ";
    std::cin >> yes_no;
    yes_no = std::tolower(yes_no);
    if (yes_no == 'y')
        married = true;
    else if (yes_no == 'n')
        married = false;
    else
    {
        std::cout << "你在开玩笑吗?" << std::endl;
        return 1;
    }

    // 处理语言
    bool speaksHindi{};
    std::cout << "你会说印地语吗?会[y],不会[n]: ";
    std::cin >> yes_no;
    yes_no = std::tolower(yes_no);
    if (yes_no == 'y')
        speaksHindi = true;
    else if (yes_no == 'n')
        speaksHindi = false;
    else
    {
        std::cout << "你在开玩笑吗?" << std::endl;
        return 1;
    }

    bool speaksUrdu{};
    std::cout << "你会说乌尔都语吗?会[y],不会[n]:";
    std::cin >> yes_no;
    yes_no = std::tolower(yes_no);
    if (yes_no == 'y')
        speaksUrdu = true;
    else if (yes_no == 'n')
        speaksUrdu = false;
    else
    {
        std::cout << "你在开玩笑吗?" << std::endl;
        return 1;
    }

    // 判断是否符合要求
    if ((age > 21 && age < 35) && gender == 'f' && (degree == AcademicDegree::bachelor || degree == AcademicDegree::master) && !married && (speaksHindi || speaksUrdu))
    {
        std::cout << "恭喜你,你被录取了!" << std::endl;
    }
    else
    {
        std::cout << "对不起,你不符合我们的要求." << std::endl;
    }
}