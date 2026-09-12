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

## 13.6 成员与非成员函数

运算符重载的三种方式：

- 成员函数：`Box operator+(const Box& aBox) const;`
- 非成员函数：`Box operator+(const Box& aBox, const Box& bBox);`
- 友元函数：`friend Box operator+(const Box& aBox, const Box& bBox);`

运算符重载函数应尽可能避免定义为友元函数，大多数情况下应该定义为成员函数，但下列情况应该定义为非成员函数：

- 在某些场景中，除了实现为非成员函数，没有其它选择，即使意味着要把运算符重载实现为友元函数。例如，重载的  
二元运算符的第一个实参是基本类型，或是与当前正在编写的类不同的类型。如：
    - `bool operator<(double value, const Box& box);`
    - `ostream& operator<<(ostream& stream, const Box& box);`
- 希望二元运算符的左操作数可被隐式转换时，可能首选将运算符重载实现为非成员函数

**运算符函数和隐式转换**  

不是所有单实参构造函数都应该用explicit禁止隐式转换，因为有时候允许转换没有坏处

- 案例Ex13_07
    - Inteter.cppm

        ```cpp
        // Integer.cppm
        export module integer;

        export class Integer
        {
        public:
            Integer(int value = 0) : m_value{value} {}
            int getValue() const { return m_value; }
            void setValue(int value) { m_value = value; }

        private:
            int m_value{};
        };

        Integer operator+(const Integer &one, const Integer &other)
        {
            return one.getValue() + other.getValue();
        }
        Integer operator-(const Integer &one, const Integer &other)
        {
            return one.getValue() - other.getValue();
        }
        Integer operator*(const Integer &one, const Integer &other)
        {
            return one.getValue() * other.getValue();
        }
        Integer operator/(const Integer &one, const Integer &other)
        {
            return one.getValue() / other.getValue();
        }
        Integer operator%(const Integer &one, const Integer &other)
        {
            return one.getValue() % other.getValue();
        }
        ```

    - Ex13_07.cpp

        ```cpp
        // Ex13_07.cpp
        module integer;

        import <iostream>;

        int main()
        {
            const Integer i{1};
            const Integer j{2};
            const auto result = (i * 2 + 4 / j - 1) % j;
            // 因Integer构造函数没有explicit关键字，而+-*/%重载要求左、右操作数为Integer对象，
            // 所以上面表达式的整数隐式转换为Integer对象了
            std::cout << result.getValue() << std::endl;
        }
        ```

        上面程序运行结果如下：

        ---

        ```cpp
        1
        ```

        ---

❗注意：编译器不会对成员函数的左操作数执行转换，如果将operator/()定义为成员函数，上例的表达式4-j将不能编译！

## 13.7 重载一元运算符

如果某个操作很常用，可以引入一个运算符。下例引入一个长度和宽度互换的盒子的一元运算符

- 案例Ex13_08
    - Box.cppm

        ```cpp
        // Box.cppm
        export module box;

        import <compare>;
        import <ostream>;
        import <format>;

        export class Box {
        public:
            Box() = default;
            Box(double length, double width, double height)
                : m_length{length},
                m_width{width},
                m_height{height}
            {}

            Box operator~() const
            {
                return Box{m_width, m_length, m_height};
            }

            double volume() const { return m_length * m_width * m_height; }

            double getLength() const { return m_length; }
            double getWidth() const { return m_width; }
            double getHeight() const { return m_height; }

            std::partial_ordering operator<=>(const Box& otherBox) const
            {
                return volume() <=> otherBox.volume();
            }
            std::partial_ordering operator<=>(double otherValue) const
            {
                return volume() <=> otherValue;
            }

            bool operator==(const Box& otherBox) const = default;

        private:
            double m_length{1.0};
            double m_width{1.0};
            double m_height{1.0};
        };

        export std::ostream& operator<<(std::ostream& stream, const Box& box)
        {
            stream << std::format("Box({:.1f},{:.1f},{:.1f})",
                                box.getLength(), box.getWidth(), box.getHeight());

            return stream;
        }
        ```

    - Ex13_08.cpp

        ```cpp
        // Ex13_08.cpp
        import <iostream>;
        import box;

        int main()
        {
            Box someBox{1, 2, 3};
            std::cout << ~someBox << std::endl;
        }
        ```

        上面程序运行结果如下：

        ---

        ```cpp
        Box(2.0,1.0,3.0) 
        ```

        ---

- 上面案例重载`~`运算符导致程序可读性差，不如使用普通函数更好，如Box rotate(Box& box)或Box getRotatedBox(Box& box)

## 13.8 重载递增和递减运算符

++和--运算符的前缀和后缀形式通过一个int类型的假参数来区分。这个int参数是固定的，在使用函数时也不用传参，编译器会自动检测  
前缀和后缀来自动使用合适的重载运算符函数

- 任意类MyClass重载++运算符的函数声明如下：

```cpp
class MyClass
{
public:
    MyClass& operator++(); // 重载前置递增运算符
    const MyClass operator++(int); // 重载后置递增运算符
    // MyClass 类的其余定义...
};
```

- 总是应该使用前缀形式的递增运算符operator++()实现后缀形式的递增运算符operator(int)
- 案例Ex13_09
    - Box.cppm

        ```cpp
        // Box.cppm
        export module box;

        import <ostream>;
        import <format>;

        export class Box {
        public:
            Box() = default;
            Box(double length, double width, double height)
                : m_length{length},
                m_width{width},
                m_height{height}
            {}

            double getLength() const { return m_length; }
            double getWidth() const { return m_width; }
            double getHeight() const { return m_height; }

            Box& operator++();
            const Box operator++(int);
            Box& operator--();
            const Box operator--(int);

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

        import <format>;
        import <ostream>;

        Box& Box::operator++()
        {
            ++m_length;
            ++m_width;
            ++m_height;

            return *this;
        }

        const Box Box::operator++(int)
        {
            auto copy(*this);
            ++(*this);

            return copy;
        }

        Box& Box::operator--()
        {
            --m_length;
            --m_width;
            --m_height;

            return *this;
        }

        const Box Box::operator--(int)
        {
            auto copy(*this);
            --(*this);

            return copy;
        }

        std::ostream& operator<<(std::ostream& stream, const Box& box)
        {
            stream << std::format("Box({:.1f},{:.1f},{:.1f})",
                                box.getLength(), box.getWidth(), box.getHeight());
            return stream;
        }
        ```

    - Ex13_09.cpp

        ```cpp
        // Ex13_09.cpp
        import box;
        import <iostream>;

        int main()
        {
            Box theBox{3.0, 1.0, 3.0};
            std::cout << "Our test Box is " << theBox << std::endl;
            std::cout << "Postfix increment evaluates to the original object: "
                    << theBox++ << std::endl;
            std::cout << "After postfix increment: " << theBox << std::endl;
            std::cout << "Prefix decrement evaluates to the decremented object: "
                    << --theBox << std::endl;
            std::cout << "After prefix decrement: " << theBox << std::endl;
        }
        ```

        上面程序运行结果如下：

        ---

        ```cpp
        Our test Box is Box(3.0,1.0,3.0)
        Postfix increment evaluates to the original object: Box(3.0,1.0,3.0)
        After postfix increment: Box(4.0,2.0,4.0)
        Prefix decrement evaluates to the decremented object: Box(3.0,1.0,3.0)
        After prefix decrement: Box(3.0,1.0,3.0)
        ```

        ---

## 13.9 重载下标运算符

下标运算符`[]`的主要作用是从许多可解释为数组的对象中选择，但对象可包含在任意多个不同的容器中。  
重载下标运算符可以访问稀疏数组（许多元素都为空的数组）、关联数组或链表中的元素。

- 案例Ex13_10
    - Box.cppm

        ```cpp
        // Box.cppm
        export module box;

        import <format>;
        import <ostream>;

        export class Box
        {
        public:
            Box() = default;
            Box(double length, double width, double height)
                : m_length{length}, m_width{width}, m_height{height} {}

            double volume() const { return m_height * m_length * m_width; }

            int compare(const Box& box) const
            {
                if (volume() < box.volume())
                    return -1;
                if (volume() == box.volume())
                    return 0;
                return +1;
            }

            friend std::ostream& operator<<(std::ostream& out, const Box& box)
            {
                return out << std::format("Box({:4.1f},{:4.1f},{:4.1f})", box.m_length,
                             box.m_width, box.m_height);
            }

        private:
            double m_width{1.0};
            double m_length{1.0};
            double m_height{1.0};
        };
        ```

    - Truckload.cppm

        ```cpp
        // Truckload.cppm
        export module truckload;

        import box;
        import <memory>;
        import <vector>;
        import <ostream>;

        export using SharedBox = std::shared_ptr<Box>;

        export class Truckload
        {
        public:
            Truckload() = default;
            Truckload(SharedBox box);
            Truckload(const std::vector<SharedBox>& boxes);
            Truckload(const Truckload& src);

            ~Truckload();

            class Iterator;

            Iterator getIterator() const;

            void addBox(SharedBox box);
            bool removeBox(SharedBox box);

            SharedBox operator[](size_t index) const;

        private:
            class Package;

            Package* m_head{};
            Package* m_tail{};
        };

        class Truckload::Iterator
        {
        public:
            SharedBox getFirstBox();
            SharedBox getNextBox();

        private:
            Package* m_head;
            Package* m_current;

            friend class Truckload;
            explicit Iterator(Package* head) : m_head{head}, m_current{nullptr} {}
        };

        export std::ostream& operator<<(std::ostream& stream, const Truckload& load);
        ```

    - Truckload.cpp

        ```cpp
        // Truckload.cpp
        module truckload;

        import <iostream>;
        import <ostream>;

        class Truckload::Package
        {
        public:
            SharedBox m_box;
            Package* m_next;

            Package(SharedBox box) : m_box{box}, m_next{nullptr} {}
            ~Package() { delete m_next; }
        };

        Truckload::Truckload(SharedBox box)
        {
            m_head = m_tail = new Package{box};
        }

        Truckload::Truckload(const std::vector<SharedBox>& boxes)
        {
            for (const auto& box : boxes)
                addBox(box);
        }

        Truckload::Truckload(const Truckload& src)
        {
            for (Package* package{src.m_head}; package; package = package->m_next)
                addBox(package->m_box);
        }

        Truckload::~Truckload()
        {
            delete m_head;
        }

        Truckload::Iterator Truckload::getIterator() const { return Iterator{m_head}; }

        SharedBox Truckload::Iterator::getFirstBox()
        {
            m_current = m_head;
            return m_current ? m_current->m_box : nullptr;
        }

        SharedBox Truckload::Iterator::getNextBox()
        {
            if (!m_current)
                return getFirstBox();

            m_current = m_current->m_next;

            return m_current ? m_current->m_box : nullptr;
        }

        void Truckload::addBox(SharedBox box)
        {
            auto package{new Package{box}};

            if (m_tail)
                m_tail->m_next = package;
            else
                m_head = package;

            m_tail = package;
        }

        bool Truckload::removeBox(SharedBox boxToRemove)
        {
            Package* previous{nullptr};
            Package* current{m_head};
            while (current) 
            {
                if (current->m_box == boxToRemove) 
                {
                    if (previous)
                        previous->m_next = current->m_next;

                    if (current == m_head)
                        m_head = current->m_next;

                    if (current == m_tail)
                        m_tail = previous;

                    current->m_next=nullptr;
                    delete current;

                    return true;
                }

                previous=current;
                current= current->m_next;
            }

            return false;
        }

        SharedBox Truckload::operator[](size_t index) const
        {
            size_t count{};
            for(Package* package{m_head};package;package = package->m_next)
            {
                if(count++==index)
                return package->m_box;
            }

            return nullptr;
        }

        std::ostream& operator<<(std::ostream&stream,const Truckload&load)
        {
            size_t count{};
            auto iterator{load.getIterator()};
            for(auto box{iterator.getFirstBox()}; box; box=iterator.getNextBox())
            {
                std::cout<<*box<<' ';
                if(!(++count%4))
                    std::cout<<std::endl;
            }

            if(count%4)
                std::cout<<std::endl;

            return stream;
        }
        ```

    - Ex13_10.cpp

        ```cpp
        // Ex13_10.cpp
        import <iostream>;
        import <memory>;
        import <random>;
        import <functional>;
        import truckload;

        auto createUniformPseudoRandomNumberGenerator(double max)
        {
            std::random_device seeder;
            std::default_random_engine generator{seeder()};
            std::uniform_real_distribution distribution{1.0,max};
            return std::bind(distribution,generator);
        }

        int main()
        {
            const double limit{99.0};
            auto random=createUniformPseudoRandomNumberGenerator(limit);

            Truckload load;
            const size_t boxCount{16};

            for(size_t i{};i<boxCount;++i)
            {
                load.addBox(std::make_shared<Box>(random(),random(),random()));
            }

            std::cout<<"The boxes in the Truckload are:\n";
            std::cout<<load;

            double maxVolume{};
            size_t maxIndex{};
            size_t i{};
            while(load[i])
            {
                if(load[i]->volume()>maxVolume)
                {
                    maxIndex=i;
                    maxVolume=load[i]->volume();
                }

                ++i;
            }

            std::cout<<"\nThe largest box is ";
            std::cout<<*load[maxIndex]<<std::endl;

            load.removeBox(load[maxIndex]);
            std::cout<<"\nAfter deleting the largest box, the Truckload contains:\n";
            std::cout<<load;
        }
        ```

        以上程序运行结果如下：

        ---

        ```cpp
        The boxes in the Truckload are:
        Box(20.7,82.8,11.9) Box(98.5,48.6,79.4) Box( 7.9,39.2,76.7) Box( 4.0,34.2,56.7)
        Box(51.3,23.4, 5.2) Box(83.1,26.1,68.4) Box(55.4,74.8,25.0) Box(62.0, 9.6,84.1)
        Box(61.1,87.0, 3.9) Box(73.2,43.7,31.0) Box(31.1,23.4,37.1) Box(16.3,81.1,84.9)
        Box(35.0,69.4,44.3) Box(85.4,40.0,77.6) Box(10.7, 4.1,28.8) Box(11.2,83.6,59.0)

        The largest box is Box(98.5,48.6,79.4)

        After deleting the largest box, the Truckload contains:
        Box(20.7,82.8,11.9) Box( 7.9,39.2,76.7) Box( 4.0,34.2,56.7) Box(51.3,23.4, 5.2)
        Box(83.1,26.1,68.4) Box(55.4,74.8,25.0) Box(62.0, 9.6,84.1) Box(61.1,87.0, 3.9)
        Box(73.2,43.7,31.0) Box(31.1,23.4,37.1) Box(16.3,81.1,84.9) Box(35.0,69.4,44.3)
        Box(85.4,40.0,77.6) Box(10.7, 4.1,28.8) Box(11.2,83.6,59.0)
        ```

        ---

**修改重载下标运算符的结果**  

- 有时候需要重载下标运算符，并把返回的对象用在赋值运算符的左侧，或者调用其函数。如下语句不会正确工作，  
因为`operator[]()`函数返回一个智能指针的临时副本：

    ```cpp
    load[0] = load[1];
    load[2].reset();
    ```

- 也不能返回Box对象的引用，因为不能返回对nullptr的引用(C++规定引用不允许为空（指针可以为空）)
- 解决方案是返回一个SharedBox对象，将其定义为Truckload类的静态成员
- 案例Ex13_11
    - Box.cppm

        ```cpp
        // Box.cppm
        export module box;

        import <format>;
        import <ostream>;
        import <algorithm>;

        export class Box
        {
        public:
            Box() = default;
            Box(double length, double width, double height)
                : m_length{length}, m_width{width}, m_height{height} {}

            double volume() const { return m_length * m_width * m_height; }

            int compare(const Box& box) const
            {
                if (volume() < box.volume())
                    return -1;
                if (volume() == box.volume())
                    return 0;
                return +1;
            }

            friend std::ostream& operator<<(std::ostream& out, const Box& box)
            {
                return out << std::format("Box({:4.1f},{:4.1f},{:4.1f})",
                                        box.m_length, box.m_width, box.m_height);
            }

            Box operator+(const Box& aBox) const
            {
                return Box{std::max(m_length, aBox.m_length),
                        std::max(m_width, aBox.m_width),
                        m_height + aBox.m_height};
            }

        private:
            double m_length{1.0};
            double m_width{1.0};
            double m_height{1.0};
        };
        ```

        - Truckload.cppm

        ```cpp
        // Truckload.cppm
        export module truckload;

        import box;

        import <memory>;
        import <vector>;
        import <ostream>;

        export using SharedBox = std::shared_ptr<Box>;

        export class Truckload
        {
        public:
            Truckload() = default;

            Truckload(SharedBox box);
            Truckload(const std::vector<SharedBox>& boxes);
            Truckload(const Truckload& src);

            ~Truckload();

            class Iterator;

            Iterator getIterator() const;

            void addBox(SharedBox box);
            bool removeBox(SharedBox box);

            SharedBox& operator[](size_t index) const;

        private:
            class Package;

            Package* m_head{};
            Package* m_tail{};

            static inline SharedBox nullBox{};
        };

        class Truckload::Iterator
        {
        public:
            SharedBox getFirstBox();
            SharedBox getNextBox();

        private:
            Package* m_head;
            Package* m_current;

            friend class Truckload;
            explicit Iterator(Package* head) : m_head{head}, m_current{nullptr} {}
        };

        export std::ostream& operator<<(std::ostream& stream, const Truckload& load);
        ```

    - Truckload.cpp

        ```cpp
        // Truckload.cpp
        module truckload;

        import <iostream>;

        class Truckload::Package
        {
        public:
            SharedBox m_box;
            Package* m_next;

            Package(SharedBox box) : m_box{box}, m_next{nullptr} {}
            ~Package() { delete m_next; }
        };

        Truckload::Truckload(SharedBox box)
        {
            m_head = m_tail = new Package{box};
        }

        Truckload::Truckload(const std::vector<SharedBox>& boxes)
        {
            for (const auto& box : boxes)
                addBox(box);
        }

        Truckload::Truckload(const Truckload& src)
        {
            for (Package* package{src.m_head}; package; package = package->m_next)
                addBox(package->m_box);
        }

        Truckload::~Truckload()
        {
            delete m_head;
        }

        Truckload::Iterator Truckload::getIterator() const { return Iterator{m_head}; }

        SharedBox Truckload::Iterator::getFirstBox()
        {
            m_current = m_head;
            return m_current ? m_current->m_box : nullptr;
        }

        SharedBox Truckload::Iterator::getNextBox()
        {
            if (!m_current)
                return getFirstBox();

            m_current = m_current->m_next;

            return m_current ? m_current->m_box : nullptr;
        }

        void Truckload::addBox(SharedBox box)
        {
            auto package{new Package{box}};
            if (m_tail)
                m_tail->m_next = package;
            else
                m_head = package;

            m_tail = package;
        }

        bool Truckload::removeBox(SharedBox boxToRemove)
        {
            Package* previous{nullptr};
            Package* current{m_head};

            while (current) {
                if (current->m_box == boxToRemove) {
                    if (previous)
                        previous->m_next = current->m_next;

                    if (current == m_head)
                        m_head = current->m_next;
                    if (current == m_tail)
                        m_tail = previous;

                    current->m_next = nullptr;
                    delete current;

                    return true;
                }

                previous = current;
                current  = current->m_next;
            }

            return false;
        }

        SharedBox& Truckload::operator[](size_t index) const
        {
            size_t count{};
            for (Package* package{m_head}; package; package = package->m_next) {
                if (count++ == index)
                    return package->m_box;
            }

            return nullBox;
        }

        std::ostream& operator<<(std::ostream& stream, const Truckload& load)
        {
            size_t count{};
            auto iterator{load.getIterator()};
            for (auto box{iterator.getFirstBox()}; box; box = iterator.getNextBox()) {
                std::cout << *box << ' ';
                if (!(++count % 4))
                    std::cout << std::endl;
            }

            if (count % 4)
                std::cout << std::endl;

            return stream;
        }
        ```

    - Ex13_11.cpp

        ```cpp
        // Ex13_11.cpp
        import truckload;
        import <iostream>;
        import <random>;
        import <memory>;
        import <functional>;

        auto createUniFormPseudoRandomNumberGenerator(double max)
        {
            std::random_device seeder;
            std::default_random_engine generator{seeder()};
            std::uniform_real_distribution distribution{1.0, max};
            return std::bind(distribution, generator);
        }

        int main()
        {
            const double limit{99.0};
            auto random = createUniFormPseudoRandomNumberGenerator(limit);

            Truckload load;
            const size_t boxCount{16};

            for (size_t i{}; i < boxCount; ++i)
                load.addBox(std::make_shared<Box>(random(), random(), random()));

            std::cout << "The boxes in the Truckload are:\n";
            std::cout << load;

            double maxVolume{};
            size_t maxIndex{};
            size_t i{};

            while (load[i]) {
                if (load[i]->volume() > maxVolume) {
                    maxIndex  = i;
                    maxVolume = load[i]->volume();
                }

                ++i;
            }

            std::cout << "\nThe largest box is ";
            std::cout << *load[maxIndex] << std::endl;

            load.removeBox(load[maxIndex]);
            std::cout << "\nAfter deleting the largest box, the Truckload contains:\n";
            std::cout << load;

            load[0] = load[1];
            std::cout << "\nAfter copying the 2nd element to the 1st, the list contains:\n";
            std::cout << load;

            load[1] = std::make_shared<Box>(*load[2] + *load[3]);
            std::cout << "\nAfter making the 2nd element a pointer to the 3rd plus 4th,"
                        " the list contains:\n";
            std::cout << load;
        }
        ```

        以上程序运行结果如下：

        ---

        ```cpp
        The boxes in the Truckload are:
        Box(64.9,39.8,44.8) Box(92.8,49.3, 3.9) Box(83.3,55.8,53.6) Box(54.1,93.8,21.1)
        Box(65.3,66.4,61.6) Box(91.0,18.2,91.4) Box(76.1,49.7,96.9) Box(51.6,73.8,83.6)
        Box(23.4,84.0,47.3) Box(52.4,88.7,88.4) Box(76.1,77.6, 5.8) Box(13.2,21.9,87.3)
        Box(89.5,27.9,55.3) Box(54.5,69.4,59.2) Box(29.1,94.6,71.4) Box(24.7,83.4,27.4)

        The largest box is Box(52.4,88.7,88.4)

        After deleting the largest box, the Truckload contains:
        Box(64.9,39.8,44.8) Box(92.8,49.3, 3.9) Box(83.3,55.8,53.6) Box(54.1,93.8,21.1) 
        Box(65.3,66.4,61.6) Box(91.0,18.2,91.4) Box(76.1,49.7,96.9) Box(51.6,73.8,83.6) 
        Box(23.4,84.0,47.3) Box(76.1,77.6, 5.8) Box(13.2,21.9,87.3) Box(89.5,27.9,55.3) 
        Box(54.5,69.4,59.2) Box(29.1,94.6,71.4) Box(24.7,83.4,27.4) 

        After copying the 2nd element to the 1st, the list contains:
        Box(92.8,49.3, 3.9) Box(92.8,49.3, 3.9) Box(83.3,55.8,53.6) Box(54.1,93.8,21.1) 
        Box(65.3,66.4,61.6) Box(91.0,18.2,91.4) Box(76.1,49.7,96.9) Box(51.6,73.8,83.6) 
        Box(23.4,84.0,47.3) Box(76.1,77.6, 5.8) Box(13.2,21.9,87.3) Box(89.5,27.9,55.3) 
        Box(54.5,69.4,59.2) Box(29.1,94.6,71.4) Box(24.7,83.4,27.4) 

        After making the 2nd element a pointer to the 3rd plus 4th, the list contains:
        Box(92.8,49.3, 3.9) Box(83.3,93.8,74.7) Box(83.3,55.8,53.6) Box(54.1,93.8,21.1) 
        Box(65.3,66.4,61.6) Box(91.0,18.2,91.4) Box(76.1,49.7,96.9) Box(51.6,73.8,83.6) 
        Box(23.4,84.0,47.3) Box(76.1,77.6, 5.8) Box(13.2,21.9,87.3) Box(89.5,27.9,55.3) 
        Box(54.5,69.4,59.2) Box(29.1,94.6,71.4) Box(24.7,83.4,27.4)
        ```

## 13.10 函数对象

- 函数对象是重载运算符()的类对象，也被称为functor。  

    ```cpp
    class ComputerVolume
    {
    public:
        double operator()(double x, double y, double z) const {return x * y * z;} // 超过一个参数的成员函数！
    };

    ComputerVolume computerVolume;
    double roomVolume{computerVolume(16, 12, 8.5)};
    ```

- ComputerVolume对象(omputerVolume)代表一个函数，可使用其函数调用运算符进行调用。roomVolume的初始化列表中  
的值是调用ComputerVolume对象的operator()()函数的结果，等价于computerVolume.operator()(16,12,8.5)。  
可以在类中定义operator()()的多个重载：  

    ```cpp
    class ComputerVolume
    {
    public:
        double operator()(double x, double y, double z) const {return x * y * z;}
        double operator()(const Box& box) const {return box.volume();}
    };

    Box box{1.0, 2.0,3.0};
    ComputerVolume computerVolume;
    std::cout<< "The volume of the box is " << computerVolume(box) << std::endl;
    ```

- 函数调用运算符必须被重载为成员函数，不能把它们定义为普通函数。函数调用运算符也是唯一不限制参数个数且能够有默认实参的运算符。

## 13.11 重载类型转换

- 转换任意类MyClass的对象的运算符函数的形式如下：

    ```cpp
    class MyClass
    {
    public:
        operator OtherType() const; //将MyClass类型转换为OtherType类型
    };
    ```

- 转换Box类型为double类型

    ```cpp
    class Box
    {
    public:
        operator double() const {return volume();}
        // Box 类的其他定义……
    };
    Box box {1.0,2.0,3.0};
    double boxVolume{box}; // 调用double类型转换
    ```

    - 编译器会插入一个隐式转换，下面的语句可以显式调用该运算符函数：

        ```cpp
        double total {10.0 + static_cast<double>(box)};
        ```

    - 在类中把转换运算符函数指定为explicit，就可以避免隐式调用它。

        ```cpp
        explicit operator double() const {return volume;}
        ```

        现在编译器不会使用这个成员将Box对象隐式转换为double类型

- 转换运算符必须被重载为成员函数，而且也是仅有的没有把返回类型放到operator关键字前面，  
而是放到operator关键字后面的运算符

**转换的模糊性**  

假设类Box的构造函数如下声明：

```cpp
class Box
{
public:
    Box(const Ball& theObject);
};
```

与类Ball中的转换运算符有冲突：

```cpp
class Ball
{
public:
    operator Box() const;
};
```

解决的方法是将其中一个成员或两个成员都声明为`explicit`

## 13.12 重载赋值运算符

- 编译器会提供一个默认的复制赋值运算符，与其它默认函数一样，默认复制赋值运算符简单地逐个复制类的成员成员变量

    ```cpp
    class Box
    {
    public:
        Box& operator=(const Box& rightHandSide);
    };
    ```

- 赋值运算符是仅有的必须重载为类的成员函数的二元运算符

### 13.12.1 实现复制赋值运算符

- 默认赋值运算符对于Box类可以接受，但是对于Message类这种C样式的字符串（char*），在构造函数和析构函数中  
会涉及new和delete堆内存，则不合适。两个Message对象的(char*) m_text成员变量引用同一个内存地址，delete[]  
将导致不可控的结果
- 最容易和最安全的解决方案是始终先检查复制赋值运算符中的左右操作数是否相等
- 用户定义的每个复制赋值运算符都应该首先检查自我赋值的情况。忘记检查自我赋值，可能会在不小心将对象赋值给自身时发生致命错误

- 案例Ex13_12
    - Message.cppm

        ```cpp
        // Message.cppm
        module;
        #include <cstring>
        export module message;

        export class Message
        {
        public:
            explicit Message(const char* text = "")
                : m_text{new char[std::strlen(text) + 1]}
            {
                std::strcpy(m_text, text);
            }

            ~Message() { delete[] m_text; }

            Message& operator=(const Message& message);

            // Rule of Three(三法则)：如果需要自定义析构、拷贝构造、拷贝赋值中任意一个，那通常三个都需要！

            const char* getText() const { return m_text; }

        private:
            char* m_text;
        };
        ```

    - Message.cpp

        ```cpp
        // Message.cpp
        module;
        #include <cstring>
        module message;

        Message& Message::operator=(const Message& message)
        {
            if (&message != this) {
                delete[] m_text;    // 释放 m_text 原来指向的堆内存，防止内存泄漏
                m_text = new char[std::strlen(message.m_text) + 1]; // 为新内容分配堆内存
                std::strcpy(m_text, message.m_text);
            }
            return *this;
        }
        ```

    - Ex13_12.cpp

        ```cpp
        // Ex13_12.cpp
        import message;
        import <iostream>;

        int main()
        {
            Message beware{"Careful"};
            Message warning;

            warning = beware;

            std::cout << "After assignment beware is: " << beware.getText() << std::endl;
            std::cout << "After assignment warning is: " << warning.getText() << std::endl;
        }
        ```

        以上程序运行结果如下：

        ---

        ```cpp
        After assignment beware is: Careful
        After assignment warning is: Careful 
        ```

        ---
- 编译器自动生成的副本构造函数：`Message(const Message& message) : m_text{message.m_text}{}`  
，如`Message danger{beware};`这样的语句会逐一复制成员变量，这会导致导致两个对象的成员变量指向同一个指针，析构就会发生未定义行为  
- 案例Ex13_12A
    - Message.cppm

        ```cpp
        // Message.cppm
        module;
        #include <cstring>

        export module message;

        export class Message
        {
        public:
            explicit Message(const char* text = "")
                : m_text{new char[std::strlen(text) + 1]}
            {
                std::strcpy(m_text, text);
            }

            ~Message() { delete[] m_text; }

            Message(const Message& message);    // 副本构造函数
            Message& operator=(const Message& message);

            const char* getText() const { return m_text; }

        private:
            char* m_text;
        };
        ```

    - Message.cpp

        ```cpp
        // Message.cpp
        module;
        #include <cstring>
        module message;

        Message::Message(const Message& message)
            : Message{message.m_text} {} // 委托构造函数，message.m_text数据类型即char*指针

        Message& Message::operator=(const Message& message)
        {
            if (&message != this) {
                delete[] m_text;
                m_text = new char[std::strlen(message.m_text) + 1];
                std::strcpy(m_text, message.m_text);
            }
            return *this;
        }
        ```

    - Ex13_12A.cpp

        ```cpp
        // Ex13_12A.cpp
        import message;
        import <iostream>;

        int main()
        {
            Message beware{"Careful"};
            Message warning;

            warning = beware;

            Message caution{warning};

            std::cout << "After assignment beware is: " << beware.getText() << std::endl;
            std::cout << "After assignment warning is: " << warning.getText() << std::endl;
            std::cout << "As a copy of warning, caution is: " << caution.getText() << std::endl;
        }
        ```

        以上程序运行结果如下：

        ---

        ```cpp
        After assignment beware is: Careful
        After assignment warning is: Careful
        As a copy of warning, caution is: Careful
        ```

        ---

- 类特定 swap（class-specific swap），配合 Copy-and-Swap 惯用法，是实现拷贝赋值运算符的最佳实践之一  
下面的案例演示了 Message 类应该怎么完整地设计（包括 Rule of Five + Copy-and-Swap + ADL swap）
- 案例Ex13_12B
    - Message.cppm

        ```cpp
        // Message.cppm
        module;
        #include <cstring>
        export module message;

        export class Message
        {
        public:
            explicit Message(const char* text = "")
                : m_text{new char[std::strlen(text) + 1]}
            {
                std::strcpy(m_text, text);
            }

            ~Message() { delete[] m_text; }

            Message(const Message& message);
            Message& operator=(const Message& message);

            void swap(Message& other) noexcept;

            const char* getText() const { return m_text; }

        private:
            char* m_text{nullptr};
        };

        export void swap(Message& one, Message& other) noexcept // 此程序没调用此函数，但是类完整设计的一部分，所以应该加上它
        {
            return one.swap(other);
        }
        ```

    - Message.cpp

        ```cpp
        // Message.cpp
        module message;
        import <utility>; // For std::swap()

        Message::Message(const Message& message)
            : Message{message.m_text} {} // 委托构造函数

        Message& Message::operator=(const Message& message)
        {
            auto copy{message}; // ① 用拷贝构造做一份副本（深拷贝，分配新内存）
            swap(copy);         // ② 和自己交换（只交换指针，零内存操作）
            return *this;
        } // ③ copy 离开作用域自动析构，带走原来的旧内存

        void Message::swap(Message& other) noexcept
        {
            std::swap(m_text, other.m_text); // 只交换指针！不分配/不释放内存
        }
        ```

    - Ex13_12B.cpp

        ```cpp
        // Ex13_12B
        import message;
        import <iostream>;

        int main()
        {
            Message beware{"Careful"};
            Message warning;

            warning = beware;

            Message caution{warning};

            std::cout << "After assignment beware is: " << beware.getText() << std::endl;
            std::cout << "After assignment warning is: " << warning.getText() << std::endl;
            std::cout << "As a copy of warning, caution is: " << caution.getText() << std::endl;
        }
        ```

        以上程序运行结果如下：

        ---

        ```cpp
        After assignment beware is: Careful
        After assignment warning is: Careful
        As a copy of warning, caution is: Careful 
        ```

        ---

### 13.12.2 复制赋值运算符与副本构造函数

- 在两个已有的对象之间赋值，就会调用复制赋值运算符；在新建对象和已有对象之间赋值，就会调用副本构造函数

    ```cpp
    Message beware {"Careful"};
    Message warning;
    warning = beware; // 两个对象都是已有的，调用复制赋值运算符
    Message otherWarning {warning}; // otherWarning对象是新建的，调用副本构造函数
    ```

- ♻ 延伸阅读——深拷贝与浅拷贝

    如果没有自定义副本构造函数，在包含裸指针成员变量情况下，会导致浅拷贝

    ```cpp
    // ❌ 浅拷贝（默认行为，两个对象共享同一块内存）
    m_text = other.m_text; // 在析构时会重复释放内存，导致崩溃

    // ✅ 深拷贝（每个对象拥有独立的内存）
    m_text = new char[std::strlen(other.m_text) + 1];
    std::strcpy(m_text, other.m_text);
    ```

**删除复制赋值运算符**  

因各种原因需要不能被复制的对象，可在声明时用delete关键字。为阻止复制，应同时删掉复制赋值运算符与副本构造函数
