// Ex13_06.cpp
import <iostream>;
import <format>;
import <vector>;
import <random>;
import <functional>;
import box;

auto createUniformPseudoRandomNumberGenerator(double max)
{
    std::random_device seeder;
    std::default_random_engine generator{seeder()};
    std::uniform_real_distribution distribution{1.0, max};
    return std::bind(distribution, generator);
}

int main()
{
    const double limit{99};
    auto random{createUniformPseudoRandomNumberGenerator(limit)};

    const size_t boxCount{20};
    std::vector<Box> boxes;

    for (size_t i{}; i < boxCount; ++i)
        boxes.push_back(Box{random(), random(), random()});

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

    std::cout << "The sum of " << boxCount << " random boxes if " << sum << std::endl;
}