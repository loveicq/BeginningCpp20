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
8. 如上，通过重载<=>和==即可实现全部比较运算符（6个）  

    **默认比较运算符**  

    ```cpp
    bool Box::operator==(const Box& otherBox) const = default;
    // 默认==比较运算符可实现逐个成员变量比较，而非比较体积
    // 重载==，编译器会自动生成!=，反之变然。可直接调用
    ```

    ```cpp
    std::partial_ordering Box::operator<=>(const Box& otherBox) const = default;
    auto Box::operator<=>(const Box& oterBox) const = default;
    // 默认<=>也是按声明顺序逐个比较成员变量，且包含了上面所提到的6个运算符
    // 但本案例因要比较体积，所以自定义重载<=>，再默认重载==，实现体积和成员变量两种比较
    ```

9. 每当默认生成`<=>`时，编译器也将添加默认生成的`==`运算符，如果所有比较运算符的
默认行为符合要求，就只需要默认生成一个运算符函数：`<=>`。

10. 案例Ex13_03A
    - Box.cppm

        ```cpp
        // Box.cppm
        export module box;

        import <compare>;

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
                { return volume() <=> box.volume(); } // 自定义<=>,比较体积大小，而非比较成员变量大小

            bool operator==(const Box& box) const = default; // 默认==，逐个成员变量比较大小，而非比较体积大小
            // 对象与对象的比较，通过上面的<=>和==重载，即包含了<、<=、>、>=、==、!=这6个运算符了
            // 仅重载<=>是不包括==和!=这2个运算符的

            std::partial_ordering operator<=>(const double value) const 
                { return volume() <=> value; } // 自定义<=>，比较体积，而非成员变量
            // 对象与数值的比较，需要单独重载<=>

            // 如果本例不比较体积大小(自定义)，仅比较成员变量大小(默认)，则只需要一行默认的<=>重载就足够了：
            // std::partial_ordering operator<=>(const Box& box) const = default;
            //包括==、!=、<、<=、>、>=6个运算符

        private:
            double m_length{1.0};
            double m_width{1.0};
            double m_height{1.0};
        };
        ```

    - Ex13_03A.cpp

        ```cpp
        // Ex13_03A.cpp
        import box;
        import <iostream>;
        import <vector>;
        import <string_view>;
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
                    show(theBox, " is greater than ", box);
            std::cout << '\n';

            for (const auto& box : boxes)
                if (theBox != box)
                    show(theBox, " is not equal to ", box);
            std::cout << '\n';

            for (const auto& box : boxes)
                if (6.0 <= box)
                {
                    std::cout << "6 is less than or equal to ";
                    show(box);
                    std::cout << '\n';
                }
        }

        void show(const Box& box)
        {
            std::cout << std::format("Box({:.1f},{:.1f},{:.1f})"
                , box.getLength(), box.getWidth(), box.getHeight());
        }

        void show(const Box& box1, std::string_view relationship, const Box& box2)
        {
            show(box1);
            std::cout << relationship;
            show(box2);
            std::cout << '\n';
        }
        ```

        上面程序运行结果如下：

        ---

        ```cpp

        Box(3.0,1.0,4.0) is greater than Box(2.0,1.5,3.0)
        Box(3.0,1.0,4.0) is greater than Box(1.0,2.0,1.0)

        Box(3.0,1.0,4.0) is not equal to Box(2.0,1.5,3.0)
        Box(3.0,1.0,4.0) is not equal to Box(1.0,3.0,5.0)
        Box(3.0,1.0,4.0) is not equal to Box(1.0,2.0,1.0)
        Box(3.0,1.0,4.0) is not equal to Box(2.0,3.0,2.0)

        6 is less than or equal to Box(2.0,1.5,3.0)
        6 is less than or equal to Box(1.0,3.0,5.0)
        6 is less than or equal to Box(2.0,3.0,2.0)
        ```

        ---

## 13.4 为输出流重载<<运算符

1. 标准输出流cout的类型是std::ostream
2. 重载运算符并不是必须等效于对应的内置运算符，如<<和>>运算符原本是整数的移位操作；+和+=连接字符串等
3. 案例Ex13_04
    - Box.cppm

        ```cpp
        // Box.cppm
        export module box;

        import <compare>;
        import <ostream>;
        import <format>;

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

            auto operator<=>(const Box& box) const { return volume() 
                <=> box.volume(); }
            auto operator<=>(double value) const { return volume() <=> value; }

            bool operator==(const Box& box) const = default;

        private:
            double m_length{1.0};
            double m_width{1.0};
            double m_height{1.0};
        };

        export std::ostream& operator<<(std::ostream& stream, const Box& box)
        {
            stream << std::format("Box({:.1f},{:.1f},{:.1f})", box.getLength()
                , box.getWidth(), box.getHeight());
            return stream;
        }
        ```

    - Ex13_04.cpp

        ```cpp
        // Ex13_04.cpp
        import box;
        import <iostream>;
        import <format>;
        import <string_view>;
        import <vector>;

        int main()
        {
            const std::vector boxes{Box{2.0, 1.5, 3.0}, Box{1.0, 3.0, 5.0},
                                    Box{1.0, 2.0, 1.0}, Box{2.0, 3.0, 2.0}};
            const Box theBox{3.0, 1.0, 4.0};

            for (const auto& box : boxes)
                if (theBox > box)
                    std::cout << theBox << " is greater than " << box << std::endl;

            std::cout << std::endl;

            for (const auto& box : boxes)
                if (theBox != box)
                    std::cout << theBox << " is not equal to " << box << std::endl;

            std::cout << std::endl;

            for (const auto& box : boxes)
                if (6.0 <= box)
                    std::cout << "6 is less than or equal to " << box << std::endl;
        }
        ```

        上面程序运行结果如下：

        ---

        ```cpp
        Box(3.0,1.0,4.0) is greater than Box(2.0,1.5,3.0)
        Box(3.0,1.0,4.0) is greater than Box(1.0,2.0,1.0)

        Box(3.0,1.0,4.0) is not equal to Box(2.0,1.5,3.0)
        Box(3.0,1.0,4.0) is not equal to Box(1.0,3.0,5.0)
        Box(3.0,1.0,4.0) is not equal to Box(1.0,2.0,1.0)
        Box(3.0,1.0,4.0) is not equal to Box(2.0,3.0,2.0)

        6 is less than or equal to Box(2.0,1.5,3.0)
        6 is less than or equal to Box(1.0,3.0,5.0)
        6 is less than or equal to Box(2.0,3.0,2.0)

        ```

        ---

        ♻通过本例理解重载<<运算符  
        调用语句：`std::cout << "6 is less than or equal to " << box << std::endl;`  
            三个<<运算符都是函数调用，每一个调用都返回std::cout引用，通过引用实现链式调用
        1. std::ostream 定义在 `<ostream>` 头文件中，它是 C++ 标准库中的"输出流"类。
            - std::cout，是 std::ostream 的直接实例，代表流出到屏幕
            - std::ofstream，是std::ostream的派生实例，代表流出到文件
            - std::ostringstream也是std::ostream的派生实例，代表流出到字符串输出流
        2. std::cout<< "6 is less than or equal to "，右边操作数是字符串字面量  
        （类型是 const char*），调用的重载：标准库自带的 operator<<：  
            `std::ostream& operator<<(std::ostream&, const char*);`
        3. （上一步返回的 std::cout 引用）<< box，右边操作数是自定义类型 Box，  
            调用的重载是我们自己写的那个版本：  
            `std::ostream& operator<<(std::ostream& stream, const Box& box);`
        4. 上一步返回的 std::cout 引用）<< std::endl，右边操作数：std::endl（它是一个输出操纵器，  
            本质是一个函数指针类型），调用的重载：标准库自带的 operator<<：  
            `std::ostream& operator<<(std::ostream&, std::ostream& (*)(std::ostream&));`

## 13.5 重载算术运算符

1. 总是应该根据相应的算术赋值运算符op=()来实现二元算术运算符op()
2. 案例Ex13_06
    - Box.cppm

        ```cpp
        // Box.cppm
        export module box;

        import <compare>;
        import <ostream>;

        export class Box {
        public:
            Box() = default;
            Box(double length, double width, double height)
                : m_length{std::max(length, width)},
                m_width{std::min(length, width)},
                m_height{height}
            {}

            double volume() const { return m_length * m_width * m_height; }

            double getLength() const { return m_length; }
            double getWidth() const { return m_width; }
            double getHeight() const { return m_height; }

            std::partial_ordering operator<=>(const Box& aBox) const;
            std::partial_ordering operator<=>(double value) const;
            bool operator==(const Box& aBox) const = default;

            Box& operator+=(const Box& aBox);
            Box operator+(const Box& aBox) const;

        private:
            double m_length{1.0};
            double m_width{1.0};
            double m_height{1.0};
        };

        export std::ostream& operator<<(std::ostream& stream, const Box& box);
        ```

    - Box.cpp

        ```cpp
        // Box.cpp
        module box;

        import <cmath>;
        import <format>;

        Box& Box::operator+=(const Box& aBox)
        {
            m_length = std::max(m_length, aBox.m_length);
            m_width  = std::max(m_width, aBox.m_width);
            m_height += aBox.m_height;
            return *this;
        }

        Box Box::operator+(const Box& aBox) const
        {
            Box copy{*this};
            copy += aBox;
            return copy;
        }

        std::partial_ordering Box::operator<=>(const Box& aBox) const
        {
            return volume() <=> aBox.volume();
        }

        std::partial_ordering Box::operator<=>(double value) const
        {
            return volume() <=> value;
        }

        std::ostream& operator<<(std::ostream& stream, const Box& box)
        {
            stream << std::format("Box({:.1f},{:.1f},{:.1f})",
                                box.getLength(), box.getWidth(), box.getHeight());
            return stream;
        }
        ```

    - Ex13_06.cpp

        ```cpp
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
            std::cout << "The sum of these boxes is " << (boxes[first] 
                        + boxes[second]) << '\n';
            std::cout << std::format("The volume of the sum is {:.1f}"
                                        , minVolume) << std::endl;

            Box sum{0, 0, 0};
            for (const auto& box : boxes)
                sum += box;

            std::cout << "The sum of " << boxCount << " random boxes if " 
            << sum << std::endl;
        }
        ```

        上面程序运行结果如下：

        ---

        ```cpp
        The two boxes that sum to the smallest volume are Box(77.6,1.8,41.7)
             and Box(89.0,1.2,20.4)
        The volume of the first box is 5723.0
        The volume of the second box is 2139.8
        The sum of these boxes is Box(89.0,1.8,62.1)
        The volume of the sum is 9777.6
        The sum of 20 random boxes if Box(96.7,86.5,1011.6)  
        ```

        ---
