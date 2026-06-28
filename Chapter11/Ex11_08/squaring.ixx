// squaring.ixx
module; // Start of the blobal module fragment (for #include directives)
// 为了使用 std::sqrt()
#include <cmath>
export module squaring;
import <numbers>; // For std::numbers::sqrt2

/* 使用 using 声明从 math 命名空间重新导出两个已有实体 */
export namespace math // 导出所有嵌套声明
{
using std::sqrt;           // 切勿写成 'using std::sqrt();' 或 'using
                           // std:;sqrt(double);'！
using std::numbers::sqrt2; // 切勿写成 'using std::sqrt();' 或 'using
                           // std:;sqrt(double);'！
/* 此处using std::sqrt 在其它import math
 * 的地方就可以直接写sqrt，而不用写std::sqrt了 */
auto square(const auto &x) { return x * x; }           // 计算平方
auto pow4(const auto &x) { return square(square(x)); } // 计算四次方
} // namespace math