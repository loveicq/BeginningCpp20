# 第13章 运算符重载

给类添加对运算符的支持功能，使它们可以应用于类类型的对象，这会使自己定义的类型更像基本数据类型

## 13.1 为类实现运算符

### 13.1.1 运算符重载

- 要为自定义类型的对象定义运算符，需要编写函数来实现期望的行为。
- 重载给定运算符的函数名由关键字operator和要重载的运算符组成。

### 13.1.2 实现重载运算符

```cpp
class Box
{
public:
    bool operator<(const Box& aBox) const;  //Overloaded 'less-than' operator
    //The rest of the Box class as before...
};
```

operator<()函数将作为对象的一个成员被调用，对象就是左操作数，实参是右操作数，this指针指向左操作数。

```cpp
if(box1 < box2)
    std::cout << "box1 is less than box2" << std::endl;
```

`box1 < box2` 等价于函数调用 `box1.operator<(box2)`

```cpp
if(box1.operator<(box2))
    std::cout << "box1 is less than box2" << std::endl;
```

重载的二元运算符是一个函数：  

- 有一个特殊的名称
- 可以通过在两个操作数之间添加运算符来调用该函数

案例Ex13_01

- Box.cppm

    ```cpp
    //Box.cppm
    export module box;

    export class Box
    {
    public:
        Box() = default;
        Box(double length, double width, double height)
            : m_length{length}, m_width{width}, m_height{height} {}

        bool operator<(const Box& aBox) const { return volume() < aBox.volume(); }

        double volume() const { return m_length * m_width * m_height; }

        double getLength() const { return m_length; }

        double getWidth() const { return m_width; }

        double getHeight() const { return m_height; }

    private:
        double m_length{1.0};
        double m_width{1.0};
        double m_height{1.0};
    };
    ```

- Ex13_01.cpp

    ```cpp
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
    ```