// Exer13_09.cpp
/*************************第13章_练习_第9题************************\
再看看示例Ex13_11中的Truckload类。是不是少了一个运算符？该类有两个原指针，
分别是m_head和m_tail。默认赋值运算符会如何处理这两个原指针？显然，处理
结果不会是我们想要的，所以Truckload类急需一个自定义的赋值运算符。为
Truckload类添加一个赋值运算符，并修改main()函数来练习新编写的赋值运算符。
\*****************************************************************/
import truckload;
import <iostream>;
import <memory>;
import <random>;
import <functional>; // For std::bind()

auto createUniformPseudoRandomNumberGenerator(double max)
{
    std::random_device seeder;
    std::default_random_engine generator{seeder()};
    std::uniform_real_distribution distribution{1.0, max};
    return std::bind(distribution, generator);
}

int main()
{
    const double limit{99.0};
    auto random{createUniformPseudoRandomNumberGenerator(limit)};

    Truckload load;
    const size_t boxCount{20};

    for (size_t i{}; i < boxCount; ++i)
        load.addBox(std::make_shared<Box>(random(), random(), random()));

    std::cout << "The boxes in the Truckload are:\n";
    std::cout << load << std::endl;

    Truckload copied;
    copied = load;

    std::cout << "The boxes in the copied Truckload are:\n";
    std::cout << copied;
}