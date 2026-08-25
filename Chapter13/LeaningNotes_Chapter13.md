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
- 案例Ex13_01

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

            bool operator<(const Box& aBox) const { return volume() 
                < aBox.volume(); }

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

### 13.1.3 非成员运算符函数

```cpp
export bool operator<(const Box& box1, const Box& box2)
{
    return box1.volume() < box2.volume();
}
```

- 不能把这个版本的运算符函数声明为const， const只能应用于类的成员函数
- 如果要访问类的私有成员，也可以把它声明为类的友元函数，但如果必须访问类的私有成员，
最好将它定义为类的成员
- 应该将非成员运算符与它们操作的对象的类放在同一个名称空间中

### 13.1.4 提供对运算符的全部支持

- 编写支持`box1 < 15.0`或`10.0 < box2`这样的重载运算符
- explicit关键字可以防止单参数构造函数隐式转换，防止`box1 < 25.0`表达式被构造函数  
`Box(double side):Box(side,side,side)`隐式转换成`box1 < 25.0 * 25.0 * 25.0`这样的结果
- 案例Ex13_02
    - Box.cppm

        ```cpp
        // Box.cppm
        export module box;

        export class Box
        {
        public:
            Box() = default;
            Box(double length, double width, double height)
                : m_length{length}, m_width{width}, m_height{height} {}

            double volume() const { return m_length * m_width * m_height; }

            bool operator<(const Box& box) const { return volume() 
                < box.volume(); }
            bool operator<(double value) const { return volume() < value; }

            double getLength() const { return m_length; }
            double getWidth() const { return m_width; }
            double getHeight() const { return m_height; }

        private:
            double m_length{1.0};
            double m_width{1.0};
            double m_height{1.0};
        };

        export bool operator<(double value, const Box& box) // 因成员函数只能有一个参数，所以此函数只能声明为非成员运算符函数
        {
            return value < box.volume();
        }
        ```

    - Ex13_02.cpp

        ```cpp
        // Ex13_02.cpp
        import box;
        import <iostream>;
        import <vector>;
        import <format>;

        void show(const Box& box);

        int main()
        {
            std::vector boxes{Box{2.0, 2.0, 3.0}, Box{1.0, 3.0, 2.0},
                            Box{1.0, 2.0, 1.0}, Box{2.0, 3.0, 3.0}};
            const double minVolume{6.0};
            std::cout << "Objects with volumes less than " << minVolume << " are:\n";
            for (const auto& box : boxes)
                if (box < minVolume)
                    show(box);

            std::cout << "Objects with volumes greater than " << minVolume 
                << " are:\n";
            for (const auto& box : boxes)
                if (minVolume < box)
                    show(box);
        }

        void show(const Box& box)
        {
            std::cout << std::format("Box {:g}x{:g}x{:g}", box.getLength()
                , box.getWidth(), box.getHeight())<< std::endl;
        }
        ```

        上面程序运行结果如下：

        ---

        ```cpp
        Objects with volumes less than 6 are:
        Box 1x2x1
        Objects with volumes greater than 6 are:
        Box 2x2x3
        Box 2x3x3
        ```

        ---

## 13.2 可以重载的运算符

1. 不能重载的主要运算符包括条件运算符`?:`、`sizeof`、`::`、`.*`和`.`
2. 运算符重载的限制：
    - 不能发明新的运算符，如？、===或<>
    - 不能修改现有的运算符的操作数个数、相关性或优先级，也不能改变运算符的操作数的计算顺序
    - 不能重写内置的运算符，并且重载运算符的签名必须涉及至少一种类类型，  
    即不能修改现有运算符操作基本类型或数组类型的方式
3. 重载运算符的重要指导原则：运算符重载的主要目的是让使用自己的类的代码更容易编写和阅读，  
以及降低发生问题的可能性。确保代码易于编写和理解，才是真正重要的。如下：

    ```cpp
    bool Box::operator == (const Box& box) const {return volume()==box.volume();}
    ```

    ```cpp
    bool Box::operator == (const Box& box) const
    {
        return m_width == box.m_width
            && m_length == box.m_wdith
            && m_height == box.m_height;
    }
    ```

    一般人都会认为盒子大小相等是指长宽高边长相等，而不是指体积相等。通过上例，得知绝不应该重载逻辑
    运算符&&或||，因为这些会影响短路计算。而重载&和|运算符表明不期望进行短路计算。

## 13.3 运算符函数习语

1. 在重载运算符Op时，左操作数是类对象，定义重载成员函数的一般形式如下：  
    `ReturnType operator Op (Type right_operand);`
2. 可以将大部分二元运算符实现为非成员函数，形式如下：  
    `ReturnType operator Op(const ClassType& left_operand`
        `, Type right_operand);`  
    唯一例外是赋值运算符`operator=()`
3. 如果二元运算符的左操作数根本不是本类时（其它类或基本类型），且这个类不是定义运算符函数的类，那么该函数必须实现为全局运算符函数，形式如下：  
    `ReturnType operator Op(Type left_operand, const ClassType& right_operand);`
4. 将一元运算符Op实现为类ClassType的成员，形式如下：  
    `ClassType& operator Op();`  
    当一元运算符被定义为全局运算符函数时，其唯一的参数就是操作数。原型如下：  
    `ClassType& operator Op(/*const*/ ClassType& obj);`  

    **在类中实现所有的比较运算符**  

5. 案例Ex13_03
    - Box.cppm

        ```cpp
        // Box.cppm
        export module box;

        import <compare>; // For std::partial_ordering

        export class Box
        {
        public:
            Box() = default;
            Box(double length, double width, double height)
                : m_length{length}, m_width{width}, m_height{height} {}

            double volume() const { return m_length * m_width * m_height; }
            double getLength() const { return m_length; }
            double getWidth() const { return m_width; }
            double getHeight() const { return m_height; }

            std::partial_ordering operator<=>(const Box& box) const
            {
                return volume() <=> box.volume();
            }
            std::partial_ordering operator<=>(double value) const
            {
                return volume() <=> value;
            }

            bool operator==(const Box& box) const
            {
                return m_length == box.m_length
                    && m_width == box.m_width
                    && m_height == box.m_height;
            }

        private:
            double m_length{1.0};
            double m_width{1.0};
            double m_height{1.0};
        };
        ```

    - Ex13_03.cpp

        ```cpp
        // Ex13_03.cpp
        import box;
        import <iostream>;
        import <string_view>;
        import <vector>;
        import <format>;

        void show(const Box& box);
        void show(const Box& box1, std::string_view relationship, const Box& box2);

        int main()
        {
            const std::vector boxes{Box{2.0, 1.5, 3.0}, Box{1.0, 3.0, 5.0},
                                    Box{1.0, 2.0, 1.0}, Box{2.0, 3.0, 2.0}};
            const Box theBox{3.0, 1.0, 4.0};

            for (const auto& box : boxes)
                if (theBox > box)
                    show(theBox, " is greater than ", box); // > works

            std::cout << std::endl;

            for (const auto& box : boxes)
                if (theBox != box)
                    show(theBox, " is not equal to ", box); // != works

            std::cout << std::endl;

            for (const auto& box : boxes)
                if (6.0 <= box) // Yes, even double <= Box works!!
                {
                    std::cout << "6 is less than or equal to ";
                    show(box);
                    std::cout << std::endl;
                }
        }

        void show(const Box& box)
        {
            std::cout << std::format("Box {}x{}x{}",
                                    box.getLength(), box.getWidth(), box.getHeight());
        }
        void show(const Box& box1, std::string_view relationship, const Box& box2)
        {
            show(box1);
            std::cout << relationship;
            show(box2);
            std::cout << std::endl;
        }
        ```

        上面程序运行结果如下：

        ---

        ```cpp
        Box 3x1x4 is greater than Box 2x1.5x3
        Box 3x1x4 is greater than Box 1x2x1

        Box 3x1x4 is not equal to Box 2x1.5x3
        Box 3x1x4 is not equal to Box 1x3x5
        Box 3x1x4 is not equal to Box 1x2x1
        Box 3x1x4 is not equal to Box 2x3x2

        6 is less than or equal to Box 2x1.5x3
        6 is less than or equal to Box 1x3x5
        6 is less than or equal to Box 2x3x2
        ```

        --

6. 本例重载了`<=>`运算符，编译器会自动生成下面4个比较运算符，这些运算符直接可以使用：
    - `<`
    - `<=`
    - `>`
    - `>=`
7. 本例重载了`==`运算符，编译器会自动生成`!=`比较运算符
8. 如上，通过重载<=>和==即可实现全部比较运算符（7个）  

    **默认比较运算符**  

    `bool Box::operator==(const Box& otherBox) const = default;`  
    `std::partial_ordering Box::operator<=>(const Box& otherBox) const = default;`  

9. 每当默认生成`<=>`时，编译器也将添加默认生成的`==`运算符，如果所有比较运算符的默认行为符合要求，就只需要默认生成一个运算符函数：`<=>`。
