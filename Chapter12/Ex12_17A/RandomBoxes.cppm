// RandomBoxes.cppm
export module box.random;
import box;
import <random>;        // For random number generation
import <functional>;    // For std::bind()
import <memory>;        // For std::make_shared<>() and std::shared_ptr<>;

// Creates a pseudorandom number generator (PRNG) for random doubles between 0 and max
auto createUniformPseudoRandomNumberGenerator(double max)
{
  std::random_device seeder;      // True random number generator to obtain a seed (slow)
  std::default_random_engine generator{ seeder() };    // Efficient pseudo-random generator
  std::uniform_real_distribution distribution{ 0.0, max }; // Generate in [0, max) interval
  return std::bind(distribution, generator);         //... and in the darkness bind them!
}

export Box randomBox()
{
  const int dimLimit{ 100 };          // Upper limit on Box dimensions
  static auto random{ createUniformPseudoRandomNumberGenerator(dimLimit) };
  return { random(), random(), random() };  //列表初始化，返回一个用3个随机值构造的Box对象。
  // 等价于return Box{ random(), random(), random() };
  // 创建了一个临时 Box 对象（无名字）
  // 这个临时对象在 return 语句执行时构造
  // 然后被「移动/拷贝」给函数的调用者
  // 之后临时对象销毁
}

export auto randomSharedBox()
{
  return std::make_shared<Box>(randomBox());   // Uses copy constructor
}
