#include <iostream>
#include <array>

int main()
{
    const char *pstars[]{// const不能省略,否则提示编译错误:"ISO c++禁止将字符串常量转换为‘char*’ "
                         "Fatty Arbuckle",
                         "Clara Bow",
                         "Lassie",
                         "Slim Pickens",
                         "Boris Karloff",
                         "Mae West",
                         "Oliver Hardy",
                         "Greta Garbo"};

    std::cout << "Pick a lucky star! Enter a number between 1 and "
              << std::size(pstars) << ": ";
    size_t choice{};
    std::cin >> choice;

    if (choice >= 1 && choice <= std::size(pstars))
    {
        std::cout << "Your lucky star is " << pstars[choice - 1] << "." << std::endl;
    }
    else
    {
        std::cout << "Sorry,you haven't got a lucky star." << std::endl;
    }
}