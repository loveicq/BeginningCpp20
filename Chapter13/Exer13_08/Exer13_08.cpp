// Exer13_08.cpp
/*************************第13章_练习_第8题************************\
创建自己的伪随机数生成器函数对象，生成0和100之间的整数值，用该函数对象
替换Ex13_06中的createUniformPseudoRandomIntGenerator()函数。当然，
为了实现合适的伪随机性，仍然应该使用std::random_device函数对象为这个
生成器提供种子值。提示：第12章中给出了一个有关生成伪随机数的简单数学公式。
\*****************************************************************/
import <iostream>;
import <format>;
import <vector>;
import <random>;
import <functional>;
import box;
import PRNG;

int main()
{
    const double limit{99};

    std::random_device seeder;
    auto random{PseudoRandomNumberGenerator{static_cast<int>(seeder())}};

    const size_t boxCount{20};
    std::vector<Box> boxes;

    for (size_t i{}; i < boxCount; ++i)
        boxes.push_back(Box{static_cast<double>(random()), static_cast<double>(random()), static_cast<double>(random())});

    size_t first{};
    size_t second{1};
    double minVolume{(boxes[first] + boxes[second]).volume()};

    for (size_t i{}; i < boxCount - 1; ++i) {
        for (size_t j{i + 1}; j < boxCount; j++) {
            if (boxes[i] + boxes[j] < minVolume) {
                first     = i;
                second    = j;
                minVolume = (boxes[i] + boxes[j]).volume();
            }
        }
    }

    std::cout << "The two boxes that sum to the smallest volume are "
              << boxes[first] << " and " << boxes[second] << '\n';
    std::cout << std::format("The volume of the first box is {:.1f}\n",
                             boxes[first].volume());
    std::cout << std::format("The volume of the second box is {:.1f}\n",
                             boxes[second].volume());
    std::cout << "The sum of these boxes is " << (boxes[first] + boxes[second]) << '\n';
    std::cout << std::format("The volume of the sum is {:.1f}", minVolume) << std::endl;

    Box sum{0, 0, 0};
    for (const auto& box : boxes)
        sum += box;

    std::cout << "The sum of " << boxCount << " random boxes is " << sum << std::endl;
}