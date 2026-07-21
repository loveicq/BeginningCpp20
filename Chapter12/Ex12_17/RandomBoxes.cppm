export module box.random;
import box;
import <random>;    // 用于随机数生成
import <functional>;    //用于 std::bind()
import <memory>;    //用于 std::make_shared<>() 和 std::shared_ptr<>

//创建一个伪随机数生成器(PRNG)，用于生成0到max之间的随机双精度数
auto createUniformPseudoRandomNumberGenerator(double max)
{
    std::random_device seeder;  //真随机数生成器，用于获取种子(速度较慢)
    std::default_random_engine generator{ seeder() }; //高效的伪随机数生成器
    std::uniform_real_distribution distribution{ 0.0,max }; // 在[0, max)区间生成随机数
    return std::bind(distribution, generator);   //将分布和生成器绑定
}

export Box randomBox()
{
    const int dimLimit{ 100 };    //Box维度的上限
    static auto random{ createUniformPseudoRandomNumberGenerator(dimLimit) };
    return { random(),random(),random() };
}

export auto randomSharedBox()
{
    return std::make_shared<Box>(randomBox());  //使用拷贝构造函数
}