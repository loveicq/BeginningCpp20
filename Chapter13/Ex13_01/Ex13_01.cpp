// Ex13_01.cpp
import <iostream>;
import box;
import <vector>;

int main()
{
    std::vector boxes{Box{2.0, 2.0, 3.0}, Box{1.0, 2.0, 3.0},
                      Box{1.0, 2.0, 1.0}, Box{2.0, 3.0, 3.0}};
    /*
    这里使用了 C++17 的类模板参数推导（Class Template Argument Deduction，简称 CTAD） 特性。
    当编译器看到 std::vector boxes{...} 时，它会：
    1.查看花括号 {} 里的元素类型
    2.发现所有元素都是 Box 类型
    3.自动推导出模板参数为 Box
    4.等价于写成 std::vector<Box>
    */
    Box smallBox{boxes[0]};
    for (const auto& box : boxes)
        if (box < smallBox) // 等价于if(box.operator<(smallBox))
            smallBox = box;

    std::cout << "The smallest box has dimensions "
              << smallBox.getLength() << 'x'
              << smallBox.getWidth() << 'x'
              << smallBox.getHeight() << std::endl;
}