//Using using declarations and using directives
// 注意：示例在正文中没有命名
import<iostream>;
import squaring;

/* 使得 math 命名空间中的名称在本地可用 */
// 注意：正文使用 hypot()，但在 Visual Studio 中这会与 <cmath> 的 hypot() 函数冲突导致二义性
auto hypotenuse(const auto& x, const auto& y)
{
	using namespace math;
// 或者：
//	using math::square;
//	using math::sqrt;	/* 当然，这与 using std::sqrt; 相同 */
	return sqrt(square(x) + square(y));//此处直接使用sqrt,不用再std::开头
}

int main()
{
	std::cout << "math::sqrt2 has the value " << math::sqrt2 << std::endl;
	std::cout << "This should be 0: " << math::sqrt2 - std::numbers::sqrt2 << std::endl;
	/* 其实math::sqrt2和std::numbers::sqrt2指向同一个实体，值相同 */
	std::cout << "This should be 2: " << math::square(math::sqrt2) << std::endl;
	std::cout << "This should be 5: " << hypotenuse(3, 4) << std::endl;

	std::cin.get();
}