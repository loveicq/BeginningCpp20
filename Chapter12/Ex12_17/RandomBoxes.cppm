// RandomBoxes.cppm
export module box.random;
import box;
import <random>;            // 随机数库
import <functional>;        // std::bind()
import <memory>;            // std::make_shared<>(), std::shared_ptr<>

// 创建一个伪随机数生成器（PRNG），用于生成 [0, max) 之间的随机双精度数
auto createUniformPseudoRandomNumberGenerator(double max)
{
    std::random_device seeder;                  // 真随机数生成器，提供种子（速度慢）
    std::default_random_engine generator{ seeder() };   // 高效的伪随机数引擎
    std::uniform_real_distribution distribution{ 0.0, max }; // 均匀分布 [0, max)
    // 将生成器和分布绑定成一个可调用对象，每次调用返回一个随机数
    return std::bind(distribution, generator);
}

export Box randomBox()
{
    const int dimLimit{ 100 };   // 盒子尺寸上限
    static auto random{ createUniformPseudoRandomNumberGenerator(dimLimit) };
    // 返回三个随机数作为长、宽、高
    return { random(), random(), random() };
}

export auto randomSharedBox()
{
    // 用随机 Box 创建一个 shared_ptr
    return std::make_shared<Box>(randomBox());
}