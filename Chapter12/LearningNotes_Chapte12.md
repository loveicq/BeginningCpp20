# 第12章 定义自己的数据类型

## 12.1 类和面向对象编程

1. 面向对象编程OOP（Object-Oriented Programming），根据要解决的问题范围所涉及的对象来编写程序，因此程序开发过程的一部分是设计一组类型来满足这个要求
2. 封装、数据隐藏、继承和多态性

### 12.1.1 封装

1. 给定类的每个对象都组合了下述内容：一组数据值，作为类的成员变量，指定对象的属性；一组操作，作为类的成员函数。把这些数据值和函数打包到一个对象中，就称为封装
2. 在阅读有些图书或同行讨论时，封装常用来指代数据隐藏
    - 一个LoanAccount对象
        - 数据成员(一般应是隐藏的)
            - balance: **$50000**
            - interestRate: **22%**
        - 函数成员（以可控的方式访问和修改数据成员）
            - calcInteres()
            - credit()
            - debit()

**数据隐藏**  

1. 在一般情况下，不允许访问对象的数据值，为此，用到的技术称为数据隐藏，或称为信息隐藏
2. 隐藏对象中的数据，可以禁止直接访问该数据，但可以通过对象的成员函数来访问，以可控的方式来修改或获取数据
3. 成员变量表示对象的状态，操纵它们的成员函数则表示对象与外界的接口
4. 在设计阶段，正确设计类的接口非常重要，以后可以修改其实现方式，而不需要对使用类的程序进行任何修改
    - 增加一个AccountType类对象来计算并提供相关数据
        - 数据成员
            - name: **"Online Star Plus"**
            - interestRate: **1.5**
            - loyalteePremium: **2.5**
        - 函数成员
            - calcInterest(balance)
    - LoanAccount::calcInterest()调用AccountType::calcInterest(balance)
5. 在对象中隐藏数据不是必需的，但一般情况下，这是一种比较好的方法
    - 数据隐藏有助于维护对象的完整性，能够确保对象的内部状态（及其所有成员变量的组合）在任何时候都是有效的
    - 将数据隐藏与精心设计的接口结合起来，能够在维修对象的内部表示（对象的状态）及其成员函数的实现（对象的行为）时，不必修改程序的其余部分。在面向对象的语言中，数据隐藏降低了类和使用类的代码之间的耦合
    - 数据隐藏允许在这些函数中注入一些额外的代码
    - 不允许直接访问数据变量，是为了使调试变得更加容易。大部分开发环境都支持断点，为函数调用或者函数内的具体代码行添加断点要简单得多

### 12.1.2 继承

1. 基类（Base Class）：被继承的原始类，也称为父类
2. 派生类（Derived Class）：从基类继承属性和方法的新类，也称为子类
3. 派生类包含基类所有的成员，也可以有新成员，还可以重新定义继承的函数。在派生类中重新定义基类的函数被称为重写
    - 基类:BankAccount
        - 数据成员
            - balance
            - interestRate
        - 函数成员
            - calcInterest()
            - credit()
            - debit()
    - 派生类：LoanAccount
        - 数据成员
            - balance
            - interestRate
        - 函数成员
            - calcInterest()
            - credit()
            - debit()
    - 派生类：CheckingAccount
        - 数据成员
            - balance
            - interestRate
            - **overdraftFacility(新增成员)**
        - 函数成员
            - calcInterest()
            - credit()
            - debit()

### 12.1.3 多态性

1. 多态性表示在不同的时刻有不同的形式
2. C++中的多态性总是涉及使用指针或引用来调用对象的成员函数
3. 向上转型：基类指针可以指向派生类对象，指针实际上指向的是派生类对象中基类部分的起始地址
    - 隐式转换：不需要显式类型转换，编译器自动完成
    - 安全性：总是安全的，因为派生类对象肯定包含基类部分
    - 访问限制：通过基类指针只能访问基类中定义的成员（除非使用虚函数实现多态）
4. 向下转型：派生类指针不能直接指向基类对象，除非使用显式类型转换，但这通常是不案例的

```cpp
BankAccount* pAcc{};    //Pointer to base class
LoanAccount debt;
CheckingAccount cash;

pAcc = & cash;  //Pointer to check a/c
pAcc->calcInterest();   //Adds interest

pAcc = &debt;   //Pointer to loan a/c
pAcc->calcInterest();   //Debits interest

/*
BankAccount* pAcc{};    // 定义基类指针，初始化为空
LoanAccount debt;       // 创建贷款账户对象
CheckingAccount cash;   // 创建支票账户对象(存款账户)

pAcc = &cash;           // 基类指针指向支票账户
pAcc->calcInterest();   // 根据实际对象类型调用支票账户的 calcInterest()，存：余额+利息

pAcc = &debt;           // 基类指针指向贷款账户  
pAcc->calcInterest();   // 根据实际对象类型调用贷款账户的 calcInterest()，贷：余额-利息
*/
```

## 12.2 术语

- 类是用户定义的数据类型
- 在类中定义的变量和函数称为类的成员。变量称为成员变量，函数称为成员函数。类的成员函数有时也称为方法；成员变量也称为数据成员、成员字段，或直接称为字段
- 类类型的变量用于存储对象。对象有时称为类的实例。定义类的实例称为实例化
- 面向对象编程是一种编程样式，基于的思想是把自己的数据类型定义为类。其中涉及刚才讨论的数据封装、数据隐藏、类的继承和多态性
- 面向对象编程就是根据针对问题的对象来编程。类的主要作用就是使这个过程尽可能完备和灵活

## 12.3 定义类

1. 定义类时要使用**class**关键字

    ```cpp
    class ClassName
    {
        //Code that defines the members of the class...
    };
    ```

2. 给用户定义的类型使用大写名称，常常便于区分类类型和变量名
3. 类定义的右花括号后面必须有分号
4. 类的所有成员都默认为私有，这表示不能在类的外部访问它们
5. **public**和**private**都是类成员的**访问修饰符**，还有一个访问修饰符**protected**

    ```cpp
    class ClassName
    {
        private:
            //Code that specifies members that are not accessible from outside 
            //the class...
        public:
            //Code that specifies members that are accessible from outside the class...
    };
    ```

6. **public**和**private**将被应用到其后的所有成员上，除非有另一个访问修饰符
7. 成员函数仅使用名称，就可以引用同一个类的任何其他成员，无论访问修饰符是什么

    ```cpp
    class Box
    {
        public:
            //Function to calculate the volume of a box
            double volume()
            {
                return m_length * m_width * m_height;
            }

        private:
            double m_length {1.0};
            double m_width{1.0};
            double m_height{1.0};
    };
    ```

8. 按照惯例，成员变量名称之前都添加前缀m_，如上面示例代码。成员变量的值没有通过某种机制初始化，它们就会包含垃圾值

9. 可以根据需要交替使用public和private部分（即可以在一个类定义中多次出现这些部分），但应该对类的相关成员进行一致的分组并在所有的类中进行一致的排序
    - 将所有公共成员放在所有私有成员之前
    - 对类的相关成员进行分组，并将函数放在变量之后
    - 构造函数和析构函数总是出现在任何其他成员函数之前
10. 在C++中还可以定义结构作为新类型，与类的成员不同，结构的成员默认为公共的。除非是想聚合数据，否则对于其他用途，一般约定应使用类

    **创建类的对象**  

    ```cpp
    Box myBox;  //A box object with all dimensions equal to 1.0
    std::cout << "Volume of myBox is " << myBox.volume() << std::endl;
    //Volume is 1
    ```

11. 可以通过**构造函数**来初始化对象的私有成员变量

## 12.4 构造函数

- 类的构造函数可以在创建新对象时初始化新对象，确保成员变量包含有效的值。它是类中的一种特殊函数，与普通的成员函数在一些重要方面有所不同。
- 构造函数总是与包含它的类同名。
- 另外，构造函数没有返回值，因此没有返回类型。为构造函数指定返回类型是错误的。
- 无论何时定义类的新实例，都会调用构造函数，没有例外。
- 类类型的对象仅可以通过构造函数来创建。

### 12.4.1 默认构造函数

1. 如果没有给类定义构造函数，编译器就会提供默认的默认构造函数

    ```cpp
    class Box
    {
        public:
            // The default constructor that was supplied by the compiler...
            Box()
            {
                //Empty body so it does nothing...
            }

            //Function to calculate the volume of a box
            double volume()
            {
                return m_length * m_width * m_height;
            }

        private:
            double m_length{1.0};
            double m_width{1.0};
            double m_height{1.0};
    };
    ```

2. 如果不通过给定的实参显式地调用构造函数，那么会调用该构造参数
3. 编译器生成的默认构造函数没有参数，其唯一的作用是创建对象
4. 用户定义构造函数后，编译器就不提供默认的构造函数了。有时候我们需要没有参数的构造函数和自己定义的、带参数的构造函数，此时就必须确保类中定义了默认的构造函数

### 12.4.2 定义类的构造函数

1. 案例Ex12_01

    ```cpp
    // Ex12_01.cpp
    // Defining a class constructor
    import <iostream>;

    // Class to represent a box
    class Box
    {
    public:
        // Constructor
        Box(double length, double width, double height) //构造函数也是函数，但无返回类型
        {
            std::cout << "Box constructor called." << std::endl;
            m_length = length;  //类内函数可以直接写private内的变量，类外不行
            m_width = width;
            m_height = height;
        }

        // Function to calculate the volume of a box
        double volume() { return m_length * m_width * m_height; }

    private:
        double m_length{1.0};
        double m_width{1.0};
        double m_height{1.0};
    };

    int main()
    {
        Box firstBox{80.0, 50.0, 40.0};           // Create a box
        double firstBoxVolume{firstBox.volume()}; // Calculate the box volume
        std::cout << "Volume of Box object is " << firstBoxVolume << std::endl;
        // Box secondbox;//Causes a compiler error message
    }
    ```

    上面程序运行结果如下：

    ---

    ```cpp
    Box constructor called.
    Volume of Box object is 160000
    ```

    ---

2. 上面示例程序在构造函数中添加一行输出信息，其它函数调用类对象时，会调用构造函数，就会输出这行信息。这行信息的作用就是证明的确调用了构造函数

### 12.4.3 使用default关键字

1. 添加了自定义构造函数，如果还想要默认的函数体为空的构造函数，除了定义一个函数体为空的默认构造函数，还可以使用default关键字

    ```cpp
    Box()=default;  //Defaulted default constructor
    ```

2. 在现代C++代码中，优先使用default关键字，因为编译器生成的版本更好

3. 案例Ex12_01A

    ```cpp
    import <iostream>;

    class Box
    {
    public:
        // Box(){}    //显式定义的默认构造函数
        Box() = default; // 默认构造函数

        // 构造函数
        Box(double length, double width, double height)
        {
            std::cout << "Box constructor called." << std::endl;
            m_length = length;
            m_width = width;
            m_height = height;
        }

        double volume() { return m_length * m_width * m_height; }

    private:
        double m_length{1.0};
        double m_width{1.0};
        double m_height{1.0};
    };

    int main()
    {
        Box firstBox {80.0, 50.0, 40.0};
        double firstBoxVolume{firstBox.volume()};
        std::cout << "Volume of Box object is " << firstBoxVolume << std::endl;

        Box secondBox; // 不再导致编译器错误消息
    }
    ```

    上面程序运行结果如下：

    ---

    ```cpp
    Box constructor called.
    Volume of Box object is 160000
    ```

    ---

### 12.4.4 在类的外部定义函数

1. 类的成员函数的定义可以放在类定义的外部。类的构造函数也是这样。对于函数体较长的成员函数，或者包含大量成员的类而言，这样做非常有意义

    ```cpp
    //Class to represent a box
    class Box
    {
        public:
            Box()=default;
            Box(double length,double width,double height);

            double volume();

        private:
            double m_length{1.0};
            double m_width{1.0};
            double m_height{1.0};
    }
    ```

2. 可将Box成员的定义放在其类定义之后，每个成员的名称都必须用类名来限定

    ```cpp
    //  Constructor definition
    Box::Box(double length,double width,double height)
    {
        std::cout << "Box constructor called." << std::endl;
        m_length = length;
        m_width = width;
        m_height = height;
    }

    //Member function definition
    double Box::volume()
    {
        return m_length * m_width * m_height;
    }
    ```

3. 从动机和技术方面讲，类的接口和实现的这种分享完全类似于第11章中介绍的模块。也可以将**类外部的成员函数的定义**移到实现文件中，仅让**类的定义**保留在接口文件（头文件或模块接口文件）中

4. 案例Ex12_02

    ```cpp
    // Ex12_02.cpp
    import <iostream>;

    class Box
    {
    public:
        Box() = default;
        Box(double length, double width, double height);

        double volume();

    private:
        double m_length{1.0};
        double m_width{1.0};
        double m_height{1.0};
    };

    int main()
    {
        Box firstBox{80.0, 50.0, 40.0}; // 初始化列表赋值给构造函数
        double firstBoxVolume{firstBox.volume()};

        std::cout << "Volume of Box object is " << firstBoxVolume << std::endl;

        Box secondBox;
    }

    Box::Box(double length, double width, double height)
    {
        std::cout << "Box constructor called." << std::endl;

        m_length = length;
        m_width = width;
        m_height = height;
    }

    double Box::volume() { return m_length * m_width * m_height; }
    ```

    上面程序运行结果如下：

    ---

    ```cpp
    Box constructor called.
    Volume of Box object is 160000
    ```

    ---

### 12.4.5 默认构造函数的参数值

1. 构造函数也可以指定参数的默认值

    ```cpp
    class Box
    {
        public:
            Box() = default;    //此行应删除，因为下面带实参的构造函数可以充当默认构造函数
            Box(double length = 1.0, double width = 1.0, double height = 1.0);
            //上面这个带三实参的构造函数也可以"Box();"的形式调用，所以可以充当默认构造函数，会与上一行产生调用歧义

            double volume();

        private:
            //Same member variables as always...

    };
    ```

2. 构造函数和成员函数的默认实参值总是放在类中，不放在外部构造函数和成员函数中。这一点与普通函数的声明和定义规定是一样的，默认参数都只能放在声明中，不能放在定义中

### 12.4.6 使用成员初始化列表

1. 更高效地设置成员变量的值的方法：成员初始化列表，构造函数的初始化列表与参数列表用冒号分隔开，每个初始值用逗号分开开

    ```cpp
    Box::Box(double length, double width, double height)
    : m_length{length}, m_width{width}, m_height{height}
    {
        std::cout << "Box constructor called." << std::endl;
    }
    ```

2. 案例Ex12_03

    ```cpp
    // Ex12_03.cpp
    import <iostream>;

    class Box
    {
    public:
        // Box() = default;
        Box(double length = 1.0, double width = 1.0, double height = 1.0);

        double volume();

    private:
        double m_length;
        double m_width;
        double m_height;
    };

    int main()
    {
        Box firstBox{80.0, 50.0, 40.0};
        double firstBoxVolume{firstBox.volume()};

        std::cout << "Volume of Box object is " << firstBoxVolume << std::endl;

        Box secondBox; // 会调用默认构造函数创建对象secondBox
    }

    Box::Box(double length, double width, double height)
        : m_length{length}, m_width{width}, m_height{height}
    {
        std::cout << "Box constructor called." << std::endl;
    }

    double Box::volume() { return m_length * m_width * m_height; }
    ```

    上面程序运行结果如下：

    ---

    ```cpp
    Box constructor called.
    Volume of Box object is 160000
    Box constructor called.  //因为创建secondBox对象，第二次调用默认构造函数了
    ```

    ---

3. 在构造函数中初始化参数之所以非常重要除了更高效，还有一个原因是因为它是某些类型的成员变量设置值的唯一方式
4. 一般来说，首选在构造函数的成员初始化列表中初始化所有成员变量。这样做一般**更高效**。为了避免产生混淆，最好按照类定义中成员变量的声明顺序，在初始化列表中列举成员变量。只有当需要更复杂的逻辑时，或者当初始化成员变量的顺序很重要时，才应该在构造函数体内初始化成员变量

### 12.4.7 使用explicit关键字

1. 类的构造函数只有一个参数是有问题的，因为编译器可以使用这种构造函数把参数的类型隐式转换为类类型。在某些情况下，这会产生不良的后果

    ```cpp
    // Ex12_04.cpp
    import <iostream>;

    class Cube
    {
    public:
        /*explicit*/ Cube(double side);      // Constructor
        double volume();                     // Calculate volume of a sube
        bool hasLargerVolumeThan(Cube cube); // Compare volume of a cube with another

    private:
        double m_side;
    };

    Cube::Cube(double side) : m_side{side}
    {
        std::cout << "Cube constructor called." << std::endl;
    }

    double Cube::volume()
    {
        return m_side * m_side * m_side;
    }

    bool Cube::hasLargerVolumeThan(Cube cube)
    {
        return volume() > cube.volume();
    }

    int main()
    {
        Cube box1{7.0};
        Cube box2{3.0};
        if (box1.hasLargerVolumeThan(box2))
            std::cout << "box1 is larger than box2." << std::endl;
        else
            std::cout << "Volume of box1 is less than or equal to that of box2."
                 << std::endl;

        std::cout << "Volume of box1 is " << box1.volume() << std::endl;
        if (box1.hasLargerVolumeThan(50.0)) //此处的(50)相当于(Cube{50})，因为类型隐式转换
            std::cout << "Volume of box1 is greater than 50" << std::endl;
        else
            std::cout << "Volume of box1 is less than or equal to 50" << std::endl;
    }
    ```

    上面程序运行结果如下：

    ---

    ```cpp
    Cube constructor called.
    Cube constructor called.
    box1 is larger than box2. 
    Volume of box1 is 343
    Cube constructor called.
    Volume of box1 is less than or equal to 50  
    ```

    ---

2. 一般单参数构造函数都需要加上`explicit`，除非是特意要使用构造函数的隐式转换功能，如下：

   ```cpp
    void print(const std::string& s) { ... }

    print("hello");  // 隐式把 const char* 转换成 std::string
   ```

3. 不仅单个实参，任何构造函数都可以声明为explicit。假设有构造函数
`Box(double length, double width, double height);`和`processBox(Box box);`函数，则调用processBox({1.0,2.0,3.0})就会隐式转换。为了强制在每次创建实例时显式指定Box类型，
可以将三元Box(double,double,double)构造函数声明为explicit

### 12.4.8 委托构造函数

1. 一个构造函数的代码可以在**初始化列表**中调用同一个类的另一个构造函数，这被称为委托构造函数，因为它把构造工作委托给了另一个构造函数

    ```cpp
    // Ex12_05.cpp
    import <iostream>;

    class Box
    {
    public:
        Box() = default;
        Box(double length, double width, double height);
        Box(double side);

        double volume();

    private:
        double m_length{1.0};
        double m_width{1.0};
        double m_height{1.0};
    };

    int main()
    {
        Box box1{2.0, 3.0, 4.0};
        Box box2{5.0};
        std::cout << "box1 volume = " << box1.volume() << std::endl;
        std::cout << "box2 volume = " << box2.volume() << std::endl;
    }

    Box::Box(double length, double width, double height)
        : m_length{length}, m_width{width}, m_height{height}
    {
        std::cout << "Box constructor 1 called." << std::endl;
    }

    Box::Box(double side) : Box{side, side, side}   //在初始化列表调用另一个构造函数来构造对象
    {
        std::cout << "Box constructor 2 called." << std::endl;
    }

    double Box::volume()
    {
        return m_length * m_width * m_height;
    }
    ```

    上面程序运行结果如下：

    ---

    ```cpp
    Box constructor 1 called.
    Box constructor 1 called.
    Box constructor 2 called.
    box1 volume = 24
    box2 volume = 125
    ```

    ---

2. 在构造函数的初始化列表中，应只调用一次同一个类的构造函数
3. 在委托构造函数**体**中调用同一个类的构造函数是不同的，而且不能在委托构造函数的初始化列表中初始化成员变量，否则代码不会编译成功

### 12.4.9 副本构造函数

编译器会提供一个默认的副本构造函数，它通过复制已有对象来创建对象。默认的副本构造函数会把实参对象的成员变量值复制给新对象，但是当类的一个或多个成员变量是指针时，就会产生不良后果。

**1. 实现副本构造函数**  

- 错误的副本构造函数定义--按值传递实参，造成无限递归调用

    ```cpp
    Box::Box(Box box)
    : m_length{box.m_length},m_width{box.m_width}, m_height{box.m_height}
    {}
    ```

- 正确的副本构造函数--const引用参数定义（这样的定义与编译器提供的默认副本构造函数等效）

    ```cpp
    Box::Box(const Box& box)
    : m_length{box.m_length},m_width{box.m_width}, m_height{box.m_height}
    {}
    ```

- 通常，不应该自己编写这样的副本构造函数，编译器提供的默认副本构造函数就足够了。但是构造函数有指针的情况下就必须要自定义副本构造函数，否则会导致编译错误！

- 案例Ex12_05A

    ```cpp
    import <iostream>;

    class Box
    {
    public:
        Box() = default;
        Box(double length, double width, double height);
        Box(const Box &box);
        explicit Box(double side);

        double volume();

    private:
        double m_length{1.0};
        double m_width{1.0};
        double m_height{1.0};
    };

    Box::Box(const Box &box)
        : m_length{box.m_length}, m_width{box.m_width}, m_height{box.m_height}
    {
        std::cout << "Copy constructor called." << std::endl;
    }

    int main()
    {
        Box box1{2.0, 3.0, 4.0};
        Box box2{5.0};
        std::cout << "box1 volume = " << box1.volume() << std::endl;
        std::cout << "box2 volume = " << box2.volume() << std::endl;

        Box box3{box2};
        std::cout << "box3 volume = " << box3.volume() << std::endl;
    }

    Box::Box(double length, double width, double height)
        : m_length{length}, m_width{width}, m_height{height}
    {
        std::cout << "Box constructor 1 called." << std::endl;
    }

    double Box::volume()
    {
        return m_length * m_width * m_height;
    }

    Box::Box(double side) : Box{side, side, side}
    {
        std::cout << "Box constructor 2 called." << std::endl;
    }
    ```

    上面程序运行结果如下：

    ---

    ```cpp
    Box constructor 1 called.
    Box constructor 1 called.
    Box constructor 2 called.24
    box2 volume = 125 
    Copy constructor called.
    box3 volume = 125
    ```

    ---

    - **拓展：副本构造函数演示案例**

        以下代码演示了副本构造函数的工作原理、浅拷贝问题及深拷贝解决方案：

        ```cpp
        #include <iostream>
        #include <cstring>

        // 演示1：简单的盒子类（没有指针成员）
        class Box {
        public:
            double length{1.0};
            double width{1.0};
            double height{1.0};
            
            Box(double l, double w, double h) : length(l), width(w), height(h) {
                std::cout << "构造函数: 创建盒子 " << this << std::endl;
            }
            
            // 自定义副本构造函数（const引用参数）
            Box(const Box& other) 
                : length(other.length), width(other.width), height(other.height)
                {
                std::cout << "副本构造函数: 从 " << &other << " 复制到 " << this << std::endl;
            }
            
            double volume() const {
                return length * width * height;
            }
        };

        // 演示2：有指针成员的类（浅拷贝问题）
        class StringBad {
        private:
            char* str;
        public:
            StringBad(const char* s) {
                str = new char[std::strlen(s) + 1];
                std::strcpy(str, s);
                std::cout << "构造函数: 创建字符串 " << str << " (" << this << ")" << std::endl;
            }
            
            // 默认副本构造函数（编译器生成）会简单复制指针
            // 这会导致两个对象指向同一块内存！
            
            ~StringBad() {
                std::cout << "析构函数: 销毁字符串 " << str << " (" << this << ")" << std::endl;
                delete[] str;
            }
            
            void print() const {
                std::cout << str << std::endl;
            }
        };

        // 演示3：有指针成员但实现了深拷贝的类
        class StringGood {
        private:
            char* str;
        public:
            StringGood(const char* s) {
                str = new char[std::strlen(s) + 1];
                std::strcpy(str, s);
                std::cout << "构造函数: 创建字符串 " << str << " (" << this << ")" << std::endl;
            }
            
            // 自定义副本构造函数 - 深拷贝
            StringGood(const StringGood& other) {
                str = new char[std::strlen(other.str) + 1];  // 分配新内存
                std::strcpy(str, other.str);                 // 复制内容
                std::cout << "副本构造函数: 深拷贝 " << other.str << " 到 " << this << std::endl;
            }
            
            ~StringGood() {
                std::cout << "析构函数: 销毁字符串 " << str << " (" << this << ")" << std::endl;
                delete[] str;
            }
            
            void print() const {
                std::cout << str << std::endl;
            }
        };

        void test_box() {
            std::cout << "\n=== 测试1: 简单盒子类 ===" << std::endl;
            Box box1{2.0, 3.0, 4.0};
            Box box2 = box1;  // 调用副本构造函数
            std::cout << "box1体积: " << box1.volume() << std::endl;
            std::cout << "box2体积: " << box2.volume() << std::endl;
        }

        void test_string_bad() {
            std::cout << "\n=== 测试2: 有指针但没有副本构造函数（浅拷贝问题）===" << std::endl;
            StringBad str1{"Hello"};
            StringBad str2 = str1;  // 编译器默认副本构造函数 - 只复制指针！
            
            str1.print();
            str2.print();
            
            // 注意：程序结束时会崩溃，因为两个对象指向同一块内存，会被delete两次
        }

        void test_string_good() {
            std::cout << "\n=== 测试3: 有指针且实现了深拷贝 ===" << std::endl;
            StringGood str1{"World"};
            StringGood str2 = str1;  // 调用自定义副本构造函数 - 深拷贝
            
            str1.print();
            str2.print();
        }

        int main() {
            test_box();
            // test_string_bad();  // 取消注释会崩溃！
            test_string_good();
            
            return 0;
        }
        ```

        上面程序运行结果如下：

        ---

        ```cpp
        === 测试1: 简单盒子类 ===
        构造函数: 创建盒子 0x5ffe20
        副本构造函数: 从 0x5ffe20 复制到 0x5ffe00
        box1体积: 24
        box2体积: 24

        === 测试3: 有指针且实现了深拷贝 ===
        构造函数: 创建字符串 World (0x5ffe38)
        副本构造函数: 深拷贝 World 到 0x5ffe30
        World
        World
        析构函数: 销毁字符串 World (0x5ffe30)
        析构函数: 销毁字符串 World (0x5ffe38)
        ```

        ---

    - 重点须知

        - Q1：为什么副本构造函数必须用 `const` 引用参数？

            - **按值传递的问题**：如果参数是 `Box box`，调用 `Box box2 = box1` 时需要先把 `box1` 复制给
  参数 `box`，而复制参数又需要调用副本构造函数，形成**无限递归**！
            - **引用传递的优势**：引用只是传递对象的地址，不需要复制对象，完美避免了递归问题。
            - **`const` 的作用**：保证不会修改源对象，符合"复制"的语义。

        - Q2：每个类都必须有副本构造函数吗？

            | 情况 | 是否有副本构造函数？ |
            | ---- | ------------------ |
            | 默认情况 | ✅ 编译器自动生成 |
            | 显式定义了移动构造/赋值 | ❌ 编译器不会生成 |
            | 显式删除副本构造函数 | ❌ 被禁用 |
            | 有未初始化的引用成员 | ❌ 编译器无法生成 |

            - **不是必须有**副本构造函数
            - 如果没有，对象就**不能被复制**（无法按值传递、返回或赋值）
            - **禁用副本构造函数的场景**：管理独占资源的类（如文件句柄）、单例类等

        - Q3：什么时候需要自己编写副本构造函数？

            | 情况 | 是否需要自定义？ |
            | ---- | -------------- |
            | 类只有基本类型成员（int, double等） | ❌ 不需要，编译器默认的就够了 |
            | 类有指针成员，且指向堆内存 | ✅ **必须写！** 否则会浅拷贝导致崩溃 |
            | 类管理其他资源（文件句柄、网络连接等） | ✅ 需要写 |

        - 核心要点：
            - 现代 C++ 推荐使用 `std::string`、`std::vector` 等标准库类型，它们已正确实现深拷贝
            - 日常编程中很少需要自己写副本构造函数，但必须理解其原理以避免内存错误

**2.删除副本构造函数**  

- 通过在类定义中向其声明添加`=delete;`，就可以指示编译器不生成副本构造函数

    ```cpp
    class Box
    {
        public:
            Box()=default;
            Box(double length, double width, double height);
            Box(const Box& box) = delete;   //  Prohibit copy construction

            //Reset of the class as always
    };
    ```

- 如果类的任何一个成员变量有一个`deleted` 或`private`副本构造函数，那么该类的默认副本构造函数会自动地隐式删除。实际上，即使是显式的默认副本构造函数（可以使用`=default;`定义）也会被删除

**3.定义模块中的类**  

- 案例Ex12_06
    - Box.cppm

        ```cpp
        // Box.cppm
        export module box;
        import <iostream>;

        export class Box
        {
        public:
            Box() = default;
            Box(double length, double width, double height);

            double volume();

        private:
            double m_length{1.0};
            double m_width{1.0};
            double m_height{1.0};
        };

        Box::Box(double length, double width, double height)
            : m_length{length}, m_width{width}, m_height{height}
        {
            std::cout << "Box constructor called." << std::endl;
        }

        double Box::volume()
        {
            return m_length * m_width * m_height;
        }
        ```

    - Ex12_06.cpp

        ```cpp
        // Ex12_06.cpp
        import <iostream>;
        import box;

        int main()
        {
            Box myBox{6.0, 6.0, 18.5};
            std::cout << "Volume of the first Box object is " << myBox.volume() 
                << std::endl;
        }
        ```

        上面程序运行结果如下：

        ---

        ```cpp
        Box constructor called.
        Volume of the first Box object is 666
        ```

        ---

- 案例Ex12_06A
    - Box.cppm

        ```cpp
        // Box.cppm
        export module Box;

        export class Box
        {
        public:
            Box() = default;
            Box(double length, double width, double height);

            double volume();

        private:
            double m_length{ 1.0 };
            double m_width{ 1.0 };
            double m_height{ 1.0 };
        };
        ```

    - Box.cpp

        ```cpp
        //Box.cpp
        module Box;
        import <iostream>;

        Box::Box(double length, double width, double height)
            : m_length{ length }, m_width{ width }, m_height{ height }
        {
            std::cout << "Box constructor called." << std::endl;
        }

        double Box::volume()
        {
            return m_length * m_width * m_height;
        }
        ```

    - Ex12_06A.cpp

        ```cpp
        //Ex12_06A.cpp
        import <iostream>;
        import Box;

        int main()
        {
            Box myBox{ 6.0, 6.0, 18.5 };
            std::cout << "Volume of the first Box object is " 
                << myBox.volume() << std::endl;
        }
        ```

        上面程序运行结果如下：

        ---

        ```cpp
        Box constructor called.
        Volume of the first Box object is 666 
        ```

        ---

- 案例Ex12_06B
    - Box.cppm

        ```cpp
        //Box.cppm
        export module Box;
        import<iostream>;

        export class Box
        {
        public:
            Box() = default;
            Box(double length, double width, double height)
                : m_length{ length }, m_width{ width }, m_height{ height }
            {
                std::cout << "Box constructor called." << std::endl;
            }

            double volume()
            {
                return m_length * m_width * m_height;
            }

        private:
            double m_length{ 1.0 };
            double m_width{ 1.0 };
            double m_height{ 1.0 };
        };
        ```

    - Ex12_06B.cpp

        ```cpp
        //Ex12_06B.cpp
        import <iostream>;
        import Box;

        int main()
        {
            Box myBox{ 6.0, 6.0, 18.5 };
            std::cout << "Volume of the first Box object is " << myBox.volume() 
                << std::endl;
        }
        ```

        上面程序运行结果如下：

        ---

        ```cpp
        Box constructor called.
        Volume of the first Box object is 666 
        ```

        ---

- 总结：在模块接口中声明并定义的类，其成员函数在类外定义（案例Ex12_06）和类内定义（案例Ex12_06B），甚至在模块实现文件中定义（案例Ex12_06A）都是可以的。类的完整定义必须在模块接口文件中（.cppm），这样其他模块才能看到完整的类型信息。成员函数的定义可以分离到实现文件中（.cpp），但类本身必须在接口中定义完整。

## 12.5 访问私有类成员

- 在类中只需要添加成员函数(public)，就可以访问私有成员变量的值
- 提取成员变量的值的函数通常被称为访问器函数
- 允许修改成员变量的成员函数常称为更改器成员函数
- 按照流行约定，访问成员变量m_member的成员的函数常被命名为getMember()，更新该成员变量的函数被命名为setMember()。因此，这种成员函数常被简单地称为getter和setter。有一个例外，bool类型的成员变量的访问器常被命名为isMember()。布尔成员变量m_valid的getter常被命名为isValid()而不是getValid()
- 案例Ex12_07
    - Box.cppm

        ```cpp
        // Box.cppm
        export module Box;

        export class Box
        {
        public:
            Box() = default;
            Box(double length, double width, double height);

            double volume();

            double getLength() { return m_length; }
            double getWidth() { return m_width; }
            double getHeight() { return m_height; }

            void setLength(double length)
            {
                if (length > 0)
                    m_length = length;
            }
            void setWidth(double width)
            {
                if (width > 0)
                    m_width = width;
            }
            void setHeight(double height)
            {
                if (height > 0)
                    m_height = height;
            }

        private:
            double m_length{1.0};
            double m_width{1.0};
            double m_height{1.0};
        };
        ```

    - Box.cpp

        ```cpp
        // Box.cpp
        module Box;
        import <iostream>;

        Box::Box(double length, double width, double height)
            : m_length{length}, m_width{width}, m_height{height}
        {
            std::cout << "Box constructor is called." << std::endl;
        }

        double Box::volume()
        {
            return m_length * m_width * m_height;
        }
        ```

    - Ex12_07.cpp

        ```cpp
        // Ex12_07.cpp
        import <iostream>;
        import Box;

        int main()
        {
            Box myBox{3.0, 4.0, 5.0};
            std::cout << "myBox dimensions are " << myBox.getLength()
                    << " by " << myBox.getWidth()
                    << " by " << myBox.getHeight() << std::endl;

            myBox.setLength(-20.0);
            myBox.setWidth(40.0);
            myBox.setHeight(10.0);

            std::cout << "myBox dimensions are now " << myBox.getLength()
                    << " by " << myBox.getWidth()
                    << " by " << myBox.getHeight() << std::endl;
        }
        ```

        上面程序运行结果如下：

        ---

        ```cpp
        Box constructor is called.
        myBox dimensions are 3 by 4 by 5
        myBox dimensions are now 3 by 40 by 10
        ```

        ---

## 12.6 this指针

- 在执行任何成员函数时，该成员函数都会自动包含一个隐藏的指针，称为this指针，该指针包含调用该成员函数的对象的地址
- 在执行volume()函数的过程中访问成员变量`m_length`，该成员变量就表示为`this->m_length`，这是完全限定的对象成员的引用

**从函数中返回this指针**  

- 可以从类对象函数成员返回this指针
- 案例Ex12_08
    - Box.cppm

        ```cpp
        // Box.cppm
        export module Box;

        export class Box
        {
        public:
            Box() = default;
            Box(double length, double width, double height);

            double volume();

            double getLength() { return m_length; }
            double getWidth() { return m_width; }
            double getHeight() { return m_height; }

            Box *setLength(double length);
            Box *setWidth(double width);
            Box *setHeight(double height);

        private:
            double m_length{1.0};
            double m_width{1.0};
            double m_height{1.0};
        };
        ```

    - Box.cpp

        ```cpp
        // Box.cpp
        module Box;
        import <iostream>;

        Box::Box(double length, double width, double height)
            : m_length{length}, m_width{width}, m_height{height}
        {
            std::cout << "Box constructor is called." << std::endl;
        }

        double Box::volume()
        {
            return m_length * m_width * m_height;
        }

        Box *Box::setLength(double length)
        {
            if (length > 0)
                m_length = length;
            return this;
        }
        Box *Box::setWidth(double width)
        {
            if (width > 0)
                m_width = width;
            return this;
        }
        Box *Box::setHeight(double height)
        {
            if (height > 0)
                m_height = height;
            return this;
        }
        ```

    - Ex12_08.cpp

        ```cpp
        // Ex12_08.cpp
        import <iostream>;
        import Box;

        int main()
        {
            Box myBox{3.0, 4.0, 5.0};

            std::cout << "myBox dimensions are "
                    << myBox.getLength()
                    << " by " << myBox.getWidth()
                    << " by " << myBox.getHeight()
                    << std::endl;

            myBox.setLength(-20.0)->setWidth(40.0)->setHeight(10.0);

            std::cout << "myBox dimensions are now "
                    << myBox.getLength()
                    << " by " << myBox.getWidth()
                    << " by " << myBox.getHeight()
                    << std::endl;
        }
        ```

        以上程序运行结果如下：

        ---

        ```cpp
        Box constructor is called.
        myBox dimensions are 3 by 4 by 5
        myBox dimensions are now 3 by 40 by 10  
        ```

        ---

- 可以从类对象函数成员返回引用
- 案例Ex12_08A
    - Box.cppm

        ```cpp
        // Box.cppm
        export module Box;

        export class Box
        {
        public:
            Box() = default;
            Box(double length, double width, double height);

            double volume();

            double getLength() { return m_length; }
            double getWidth() { return m_width; }
            double getHeight() { return m_height; }

            Box& setLength(double length);
            Box& setWidth(double width);
            Box& setHeight(double height);

        private:
            double m_length;
            double m_width;
            double m_height;
        };
        ```

    - Box.cpp

        ```cpp
        // Box.cpp
        module Box;
        import <iostream>;

        Box::Box(double length, double width, double height)
            : m_length{length}, m_width{width}, m_height{height}
        {
            std::cout << "Box constructor called." << std::endl;
        }

        double Box::volume()
        {
            return m_length * m_width * m_height;
        }

        Box &Box::setLength(double length)
        {
            if (length > 0)
                m_length = length;
            return *this;
        }
        Box &Box::setWidth(double width)
        {
            if (width > 0)
                m_width = width;
            return *this;
        }
        Box &Box::setHeight(double height)
        {
            if (height > 0)
                m_height = height;
            return *this;
        }

        ```

    - Ex12_08A.cpp

        ```cpp
        // Ex12_08A.cpp
        import <iostream>;
        import Box;

        int main()
        {
            Box myBox{3.0, 4.0, 5.0};

            std::cout << "myBox dimensions are "
                    << myBox.getLength()
                    << " by " << myBox.getWidth()
                    << " by " << myBox.getHeight()
                    << std::endl;

            myBox.setLength(-20.0).setWidth(40.0).setHeight(10.0);

            std::cout << "myBox dimensions are now "
                    << myBox.getLength()
                    << " by " << myBox.getWidth()
                    << " by " << myBox.getHeight()
                    << std::endl;
        }
        ```

        上面程序运行结果如下：

        ---

        ```cpp
        Box constructor called.
        myBox dimensions are 3 by 4 by 5
        myBox dimensions are now 3 by 40 by 10  
        ```

        ---

    - 链式调用，重点在于声明函数时是`Box&`，而函数定义时返回解引用`return *this;`
    - 重点注意，一般使用引用返回Box&而不是指针Box*，因为：
        - 更安全：不会有空指针问题
        - 更直观：语法上和普通对象调用一致
        - 效率更高：不需要额外的指针解引用
    - 引用与指针的区别：  

        | 操作符 | 使用场景 | 含义 | 备注 |
        | --- | --- | --- | --- |
        | . | 对象或引用 | 直接访问对象的成员 | 引用相当于对象（即变量）的别名，访问对象成员直接用"." |
        | -> | 指针 | 解引用指针后访问成员（等价于 (*p).） | 对象（即变量）指针须解引用才能访问成员 |

## 12.7 const对象和const成员函数

- 类类型的const变量称为**const对象**，构成const对象状态的任何成员变量都不能被修改  
`const Box myBox{3.0, 4.0, 5.0}; //注意const关键字`
- 当通过const指针或const引用访问对象时，具有与直接访问const对象相同的限制  
    - `const Box* boxPointer = &myBox;`，这个boxPointer指针无法修改myBox对象的任何成员
    - `void printBox(const Box& box);`，这个printBox函数无法修改box对象的任何成员

### 12.7.1 const成员函数

- 按照Ex12_07中的Box类定义，const对象既不能调用setter函数，也不能调用getter函数  
`const Box myBox{3.0, 4.0, 5.0};`，这个myBox对象既不能调用setLength()，也不能调用getLength()，也不能调用volume()函数，这样的对象等于没什么用
- 要使用const对象，须在定义类的时候把不修改对象的函数指定为const
- 案例Ex12_09

    - Box.cppm

        ```cpp
        //Box.cppm
        export module Box;

        export class Box
        {
        public:
            Box() = default;
            Box(double length, double width, double height);

            double volume() const;

            double getLength() const;
            double getWidth() const;
            double getHeight() const;

            void setLength(double length);
            void setWidth(double width);
            void setHeight(double height);

        private:
            double m_length{ 1.0 };
            double m_width{ 1.0 };
            double m_height{ 1.0 };
        };
        ```

    - Box.cpp

        ```cpp
        //Box.cpp
        module Box;
        import <iostream>;

        Box::Box(double length, double width, double height)
            : m_length{ length }, m_width{ width }, m_height{ height }
        {
            std::cout << "Box constructor called." << std::endl;
        }

        double Box::volume() const
        {
            return m_length * m_width * m_height;
        }

        double Box::getLength() const
        {
            return m_length;
        }

        double Box::getWidth() const
        {
            return m_width;
        }

        double Box::getHeight() const
        {
            return m_height;
        }

        void Box::setLength(double length)
        {
            if (length > 0)
                m_length = length;
        }

        void Box::setWidth(double width)
        {
            if (width > 0)
                m_width = width;
        }

        void Box::setHeight(double height)
        {
            if (height > 0)
                m_height = height;
        }
        ```

    - Ex12_09.cpp

        ```cpp
        //Ex12_09.cpp
        import <iostream>;
        import Box;

        int main()
        {
            const Box myBox{ 3.0, 4.0, 5.0 };

            std::cout << "myBox dimensions are " << myBox.getLength()
                << " by " << myBox.getWidth()
                << " by " << myBox.getHeight()
                << std::endl;

            //由于myBox对象是const对象，而下面三个函数声明时都没有const，所以都无法调用，编译不能通过
            // myBox.setLength(-20.0);
            // myBox.setWidth(40.0);
            // myBox.setHeight(10.0);

            std::cout << "myBox dimensions are " << myBox.getLength()
                << " by " << myBox.getWidth()
                << " by " << myBox.getHeight()
                << std::endl;

            std::cout << "myBox's volume is " << myBox.volume() << std::endl;
        }
        ```

        上面程序运行结果如下：

        ---

        ```cpp
        Box constructor called.
        myBox dimensions are 3 by 4 by 5
        myBox dimensions are 3 by 4 by 5
        myBox's volume is 60 
        ```

        ---

- 对于const对象，只能调用const成员函数，因此，应该将不修改对象的所有成员函数指定为const。注意，const是在函数名的小括号后面！

### 12.7.2 const正确性

- const对象只能调用const函数
- 将成员函数指定为const，实际上会使该成员函数的this指针成为const指针
- 在const成员函数内不能调用任何非const成员函数，但可以调用const成员函数

### 12.7.3 重载const

- 可以用const版本来重载一个非const版本的成员函数。这种重载有很用，对于返回某个对象封装的（部分）内部数据的指针或引用的函数，常常要进行重载

    ```cpp
    export class Box
    {
        public:
            //Rest of the class definition as before

            // 非 const 对象调用：返回引用，允许修改
            double& length()    {return m_length;};
            double& width() {return m_width;};
            double& height()    {return m_height;};

            //重载const函数，注意，引用必须加const限定
            const double& length()   const   {return m_length;};
            const double& width() const   {return m_width;};
            const double& height()    const   {return m_height;};

            // const 对象调用：返回值（副本），禁止修改
            double length()   const   {return m_length;};
            double width() const   {return m_width;};
            double height()    const   {return m_height;};

        private:
            double m_length{1.0};
            double m_width{1.0};
            double m_height{1.0};
    }
    ```

- 多数情况下不推荐用重载const的方式代替setter函数和getter函数
    - 不符合常规做法  
        `box.length() = 2;`没有`box.setLength(2);`清晰
    - 添加public成员函数来返回对private成员变量的引用时，实际上就抛弃了数据隐藏的大部分优势
- 在某些情形中，还是得用重载const，例如重载数组访问运算符

### 12.7.4 常量的强制转换

- `const_cast<>()`运算符

    - `const_cast<Type*>(expression) //expression可以为const Type*或Type*`
    - `const_cast<Type&>(expression)    //expression可以为const Type&、Type或Type&`
- 几乎总是不建议使用`const_cast<>()`运算符，意外修改const对象很可能导致bug
