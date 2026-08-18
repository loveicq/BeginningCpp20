// RandomBoxes.cppm
export module box.random;

import box;
import <functional>;
import <random>;
import <memory>;

auto createUniformPseudoRandomNumberGenerator(double max)
{
    std::random_device seeder;
    std::default_random_engine generator{seeder()};
    std::uniform_real_distribution distribution{0.0, max};

    return std::bind(distribution, generator);
}

export Box randomBox()
{
    const int dimLimit{100};
    static auto random{createUniformPseudoRandomNumberGenerator(dimLimit)};
    return Box{random(), random(), random()};
}

export auto randomSharedBox()
{
    return std::make_shared<Box>(randomBox());
}