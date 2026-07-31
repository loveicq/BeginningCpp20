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

- 案例Ex12_10
    - Box.cppm

        ```cpp
        //Box.cppm
        export module Box;
        import <iostream>;

        export class Box
        {
        public:
            Box() = default;
            Box(double length, double width, double height);

            double volume() const;  //计算盒子体积的Const函数

            //非const重载（返回对尺寸变量的引用）
            double& length() { std::cout << "Non-const overload called.\n";
                return m_length; }
            double& width() { std::cout << "Non-const overload called.\n";
                return m_width; }
            double& height() { std::cout << "Non-const overload called.\n";
                return m_height; }

            // Const重载（返回对Const变量的引用）
            const double& length() const 
                { std::cout << "Const overload called.\n";return m_length; }
            const double& width() const 
                { std::cout << "Const overload called.\n";return m_width; }
            const double& height() const 
                { std::cout << "Const overload called.\n";return m_height; }

            //尝试返回对const函数成员变量的非const引用
            // double& length() const { return m_length; }    //不允许编译！
            // double& width() const { return m_width; }
            // double& height() const { return m_height; }

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
        ```

    - Ex12_10.cpp

        ```cpp
        //Ex12_10.cpp
        //重载const
        import <iostream>;
        import Box;

        int main()
        {
            const Box constBox{ 1,2,3 };
            //constBox.length() = 2;    //不编译：好！
            std::cout << constBox.length() << std::endl;

            Box nonConstBox{ 3,2,1 };
            nonConstBox.length() *= 2;
            std::cout << nonConstBox.length() << std::endl;
        }
        ```

        上面程序运行结果如下：

        ---

        ```cpp
        Box constructor called.
        Const overload called.
        1
        Box constructor called.
        Non-const overload called.
        Non-const overload called.
        6 
        ```

        ---

- 多数情况下不推荐用重载const的方式代替setter函数和getter函数
    - 不符合常规做法  
        `box.length() = 2;`没有`box.setLength(2);`清晰
    - 添加public成员函数来返回对private成员变量的**引用**时，实际上就抛弃了数据隐藏的大部分优势
- 在某些情形中，还是得用重载const，例如重载数组访问运算符

### 12.7.4 常量的强制转换

- `const_cast<>()`运算符

    - `const_cast<Type*>(expression) //expression可以为const Type*或Type*`
    - `const_cast<Type&>(expression)    //expression可以为const Type&、Type或Type&`
- 几乎总是不建议使用`const_cast<>()`运算符，意外修改const对象很可能导致bug

### 12.7.5 使用mutable关键字

- `mutable`可以让const类对象成员修改某个成员的值，任何成员函数（包括const和非const成员函数）总是可以修改用mutable声明的成员变量
- 应该很少需要使用mutable成员变量。如果需要在const函数内修改一个对象，则很可能不应该将该函数声明为const
- mutable成员变量的典型用途包括调试或日志记录、缓存和线程同步成员
- 案例Ex12_11
    - Box.cppm

        ```cpp
        //Box.cppm
        export module Box;

        export class Box
        {
        public:
            //构造函数
            Box() = default;
            Box(double length, double width, double height);

            double volume() const;  //计算盒子体积的函数
            void printVolume() const;   ////输出盒子的体积（const!）

            //提供访问成员变量值的函数（都是const!）
            double getLength() const { return m_length; }
            double getWidth()   const { return m_width; }
            double getHeight() const { return m_height; }

            //设置成员变量值的函数（不是const!）
            void setLength(double length) { if (length > 0) m_length = length; }
            void setWidth(double width) { if (width > 0)    m_width = width; }
            void setHeight(double height) 
                { if (height > 0)  m_height = height; }

        private:
            double m_length{ 1.0 };
            double m_width{ 1.0 };
            double m_height{ 1.0 };
            mutable unsigned m_count{}; //计算调用printVolume（）的次数
        };
        ```

    - Box.cpp

        ```cpp
        //Box.cpp
        module Box;
        import <iostream>;

        //构造函数定义
        Box::Box(double length, double width, double height)
        : m_length{length}, m_width{width}, m_height{height}
        {
            std::cout << "Box constructor called." << std::endl;
        }

        // Const成员函数定义
        double Box::volume() const
        {
            return m_length * m_width * m_height;
        }

        //修改const成员函数的可变成员变量
        void Box::printVolume() const
        {
            std::cout << "The volume of this box is " << volume() << std::endl;
            std::cout << "printVolume has been called " << ++m_count 
                << " time(s)" << std::endl;
        }
        ```

    - Ex12_11.cpp

        ```cpp
        //Ex12_11.cpp
        import <iostream>;
        import Box;

        int main()
        {
            const Box myBox{ 3.0,4.0,5.0 };   //const对象

            std::cout << "myBox dimensions are " << myBox.getLength()
                << " by " << myBox.getWidth()
                << " by " << myBox.getHeight()
                << std::endl;

            myBox.printVolume();
            myBox.printVolume();
            myBox.printVolume();
        }
        ```

        上面程序运行结果如下：

        ---

        ```cpp
        Box constructor called.
        myBox dimensions are 3 by 4 by 5
        The volume of this box is 60
        printVolume has been called 1 time(s)
        The volume of this box is 60
        printVolume has been called 2 time(s)
        The volume of this box is 60
        printVolume has been called 3 time(s)
        ```

        ---

## 12.8 友元

声明友元破坏了面向对象编程的一个基石：数据隐藏。因此，只有在绝对有必要时，才应该使用友元，而有这种需求的场合并不多见。

- 友元函数：把一个函数指定为类的友元
- 友元类：把整个类指定为另一个类的友元

### 类的友元函数

- 为了把函数看作类的友元函数，必须在类定义中用关键字`friend`来声明它。类决定了它的友元，无法在类定义的外部将函数设置为类的友元函数。类的友元函数可以是一个全局函数，也可以是另一个类的成员。但是，函数不能是包含它的类的友元函数，因此，访问修饰符不能被应用于类的友元函数
- 案例Ex12_12
    - box.cppm

        ```cpp
        //box.cppm
        export module box;

        export class Box
        {
        public:
            Box() :Box{ 1.0,1.0,1.0 } {}    // 委托默认构造函数
            Box(double length, double width, double height);

            double volume() const;  // 计算盒子体积的函数

            friend double surfaceArea(const Box& box);  // 用于表面积计算的友元函数

        private:
            double m_length, m_width, m_height;
        };
        ```

    - box.cpp

        ```cpp
        //box.cpp
        module box;

        import <iostream>;

        // 构造函数定义
        Box::Box(double length, double width, double height)
            : m_length{ length }, m_width{ width }, m_height{ height }
        {
            std::cout << "Box constructor called." << std::endl;
        }

        // 常量成员函数定义
        double Box::volume() const
        {
            return m_length * m_width * m_height;
        }

        double surfaceArea(const Box& box)
        {
            return 2.0 * (box.m_length * box.m_width + box.m_length * box.m_height
                + box.m_width * box.m_height);
        }
        ```

    - Ex12_12.cpp

        ```cpp
        //Ex12_12.cpp
        // Using a friend function of a class

        import <iostream>;
        import <memory>;
        import box;

        int main()
        {
            Box box1{ 2.2,1.1,0.5 };
            Box box2;
            auto box3{ std::make_unique<Box>(15.0,20.0,8.0) };

            std::cout << "Volume of box1 = " << box1.volume() << std::endl;
            std::cout << "Surface area of box1 = " << surfaceArea(box1) << std::endl;

            std::cout << "Volume of box2 = " << box2.volume() << std::endl;
            std::cout << "Surface area of box2 = " << surfaceArea(box2) << std::endl;

            std::cout << "Volume of box3 = " << box3->volume() << std::endl;
            std::cout << "Surface area of box3 = " << surfaceArea(*box3) << std::endl;
        }
        ```

        上面程序运行结果如下：

        ---

        ```cpp
        Box constructor called.
        Box constructor called.
        Box constructor called.
        Volume of box1 = 1.21
        Surface area of box1 = 8.14
        Volume of box2 = 1
        Surface area of box2 = 6
        Volume of box3 = 2400
        Surface area of box3 = 1160
        ```

        ---

- 延伸阅读——友元函数总结
    - 用途：突破封装边界，允许特定外部函数或类访问私有成员
    - 三种友元关系：
        - 类 A 的成员函数可以是类 B 的友元：

            ```cpp
            class ClassB;   //前向声明
            class ClassA { public: void modifyB(ClassB& b); };
            class ClassB {
            private: int x = 10;
            friend void ClassA::modifyB(ClassB& b);  // 声明成员函数为友元
            };
            void ClassA::modifyB(ClassB& b) { b.x = 20; }// ✅ 可访问私有成员
            ```

        - 类 A 可以是类 B 的友元（整个类）：

            ```cpp
            class ClassB {
            private: int x = 10;
            friend class ClassA;  // 声明整个类为友元
            };
            class ClassA { 
            public: 
                void modifyB(ClassB& b)
                    { b.x = 20; } };    // ✅ 可以访问 ClassB 的私有成员
            ```

        - 模块内的自由函数可以是类的友元：

            ```cpp
            export module box;
            export class Box {
            private: double m_length, m_width, m_height;

            // 声明自由函数为友元
            friend double surfaceArea(const Box& box);
            };
            export double surfaceArea(const Box& box) 
            {  // 同一模块内定义友元函数，也可以放到模块实现文件（.cpp）中
                return 2.0 * (box.m_length * box.m_width + 
                                box.m_length * box.m_height + 
                                box.m_width * box.m_height);
            }
            ```

    - C++20 模块规则：友元关系具有模块作用域限制，跨模块无效
    - 特性：
        - 友元关系是单向的：A 是 B 的友元 ≠ B 是 A 的友元
        - 友元关系不传递：A 是 B 的友元，B 是 C 的友元 ≠ A 是 C 的友元
        - C++20 模块限制：友元关系默认不跨模块边界
        - 实现位置：友元函数的定义必须在同一模块内才能生效
    - 使用建议：谨慎使用，明确意图，模块内定义

### 12.8.2 友元类

- 可以把整个类声明为另一个类的友元。友元类的所有成员函数都可以不受限制地访问原有类的成员

    ```cpp
    class Box
    {
        //Public members of the class...
        friend class Carton;
        //Private members of the class...
    };
    ```

- 友元类并不是一种互惠的关系（单向）
- 类之间的友元关系是不能传递的（不传递）

## 12.9 类的对象数组

类的对象数组的每个元素都由构造函数创建，如果没有指定初始值，编译器会为每个元素调用无参构造函数

- 案例Ex12_13
    - Box.cppm

        ```cpp
        //Box.cppm
        export module box;

        export class Box
        {
        public:
            Box();  //此处不能写成Box()=default;，因为函数定义时有std::...等自定义内容
            Box(double length, double width, double height);
            Box(double side);
            Box(const Box& box);

            double volume() const { return m_length * m_width * m_height; }

        private:
            double m_length{ 1.0 };
            double m_width{ 1.0 };
            double m_height{ 1.0 };
        };
        ```

    - Box.cpp

        ```cpp
        //Box.cpp
        module box;

        import <iostream>;

        Box::Box(double length, double width, double height)
            : m_length{ length }, m_width{ width }, m_height{ height }
        {
            std::cout << "Box constructor 1 called." << std::endl;
        }

        Box::Box(double side) : Box{ side,side,side }
        {
            std::cout << "Box constructor 2 called." << std::endl;
        }

        Box::Box()
        {
            std::cout << "Default Box constructor called." << std::endl;
        }

        Box::Box(const Box& box)
            : m_length{ box.m_length }, m_width{ box.m_width }, 
                m_height{ box.m_height }
        {
            std::cout << "Box copy constructor called." << std::endl;
        }
        ```

    - Ex12_13.cpp

        ```cpp
        //Ex12_13.cpp
        import <iostream>;
        import box;

        int main()
        {
            const Box box1{ 2.0,3.0,4.0 };
            Box box2{ 5.0 };
            std::cout << "box1 volume = " << box1.volume() << std::endl;
            std::cout << "box2 volume = " << box2.volume() << std::endl;
            Box box3{ box2 };
            std::cout << "box3 volume = " << box3.volume() << std::endl;

            std::cout << std::endl;

            Box boxes[6]{ box1,box2,box3,Box{2.0} };    //最后两个函数没有指定初始值，所以编译器调用默认构造函数来创建它们
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
        Box copy constructor called.
        box3 volume = 125

        Box copy constructor called.
        Box copy constructor called.
        Box copy constructor called.
        Box constructor 1 called.
        Box constructor 2 called.
        Default Box constructor called.
        Default Box constructor called.
        ```

        ---

## 12.10 类对象大小

- 使用sizeof运算符可以获得类对象的大小
- 因为内存边界对齐的原因，类对象占用的空间有可能大于各变量实际需要的字节总和

## 12.11 类的静态成员

- 类的成员可以声明为static（static在程序结束之前都有效）
- 静态成员与类本身绑定在一起，而不是绑定到单独的对象

### 12.11.1 静态成员变量

- 类的静态成员变量可以在**类的范围内**存储数据，这种数据独立于类类型的任何对象，但可以由这些对象访问
- 可以使用静态成员变量存储类的特定常量，或存储类中对象的一般信息，例如类有多少个对象等  
`static inline size_t s_object_cont {};`
- 静态成员一般声明为private，但是也可以声明为public或protected。
- s_object_count变量还被声明为inline，在类定义和初始化静态成员变量时，必须添加这个额外的inline关键字
- 案例Ex12_14
    - Box.cppm

        ```cpp
        //Box.cppm
        export module box;
        import <iostream>;

        export class Box
        {
        public:
            Box();  //默认构造函数
            Box(double side);   //立方体构造函数
            Box(const Box& box);    //副本构造函数
            Box(double length, double width, double height);

            double volume() const { return m_length * m_width * m_height; }

            size_t getObjectCount() const { return s_object_count; }
        private:
            double m_length{ 1.0 };
            double m_width{ 1.0 };
            double m_height{ 1.0 };
            static inline size_t s_object_count{};  //创建过的对象总数
        };
        ```

    - Box.cpp

        ```cpp
        //Box.cpp
        module box;
        import <iostream>;

        Box::Box()  //默认构造函数
        {
            ++s_object_count;
            std::cout << "Default Box constructor called." << std::endl;
        }
        Box::Box(double side) : Box{ side,side,side } //立方体构造函数
        {
            // 不要在委托构造函数中增加 s_object_count：
            // 该计数器已在被委托的构造函数中增加过了！
            std::cout << "Box constructor 2 called." << std::endl;
        }
        Box::Box(const Box& box)    //副本构造函数
            : m_length{ box.m_length }, m_width{ box.m_width },
                m_height{ box.m_height }
        {
            ++s_object_count;
            std::cout << "Box copy constructor called." << std::endl;
        }
        Box::Box(double length, double width, double height)
            : m_length{ length }, m_width{ width }, m_height{ height }
        {
            ++s_object_count;
            std::cout << "Box constructor 1 called." << std::endl;
        }
        ```

    - Ex12_14.cpp

        ```cpp
        //Ex12_14.cpp
        import <iostream>;
        import box;

        int main()
        {
            const Box box1{ 2.0,3.0,4.0 };    // 一个任意尺寸的盒子
            Box box2{ 5.0 };  // 一个立方体盒子
            std::cout << "box1 volume = " << box1.volume() << std::endl;
            std::cout << "box2 volume = " << box2.volume() << std::endl;
            Box box3{ box2 };
            std::cout << "box3 volume = " << box3.volume() << std::endl;

            std::cout << std::endl;

            Box boxes[6]{ box1,box2,box3,Box{2.0} };

            std::cout << "\nThere are now " << box1.getObjectCount() << " Box objects.\n";
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
        Box copy constructor called.
        box3 volume = 125

        Box copy constructor called.
        Box copy constructor called.
        Box copy constructor called.
        Box constructor 1 called.
        Box constructor 2 called.
        Default Box constructor called.
        Default Box constructor called.

        There are now 9 Box objects.
        ```

        ---

- s_object_count只记录了已创建的对象个数，输出的数字对应于这里创建的对象个数，一般无法确定对象何时释放，所以该记数不一定反映某一时刻存在的对象个数
- 静态成员变量不是任何对象的一部分，它们属于类。由于静态成员变量不是类对象的一部分，因此const成员函数就可以修改非const静态成员变量，而不会影响函数的const性质
- 延伸阅读：inline内联

    - 内联函数（Inline Function）

        - 隐式内联（类内定义）

            ```cpp
            class Box 
            {
                double volume() const { return m_length * m_width * m_height; }
                  // 隐式 inline
            };
            ```

            - **规则**：类体内直接定义的非虚成员函数自动视为 `inline`
            - **优势**：代码简洁，适合短小高频函数

        - 显式内联（类外定义）

            ```cpp
            class Box 
            {
                double volume() const;
            };
            inline double Box::volume() const 
            {
                return m_length * m_width * m_height;
            }
            ```

            - **适用场景**：头文件中定义，需多文件包含

        - 优势

            | 优势 | 说明 |
            | ------ | ------ |
            | 消除调用开销 | 无参数传递、栈帧操作、跳转指令 |
            | 提升执行速度 | 特别适合高频调用的小函数 |
            | 提高缓存命中率 | 代码局部性更好 |

        - 限制

            | 限制 | 说明 |
            | ------ | ------ |
            | `inline` 是建议 | 编译器可忽略（如函数过大、有递归） |
            | 虚函数通常不内联 | 运行时多态无法确定调用目标 |
            | 代码膨胀风险 | 过度内联会增加可执行文件体积 |

    - 内联变量（Inline Variable）【C++17 引入】

        - 基本概念

            ```cpp
            inline int global_counter = 0;  // 头文件中定义内联变量
            ```

            - **解决的问题**：允许在头文件中定义变量，避免重复定义错误
            - **链接类型**：`internal linkage`（内部链接）

        - 静态内联成员变量

            **C++17 写法**：

            ```cpp
            class Box 
            {
            private:
                static inline size_t s_object_count{};  // 直接在类内定义
            };
            ```

            **对比 C++17 之前的写法**：

            ```cpp
            // 头文件
            class Box {
                static size_t s_object_count;  // 仅声明
            };
            // 源文件
            size_t Box::s_object_count{};  // 必须在 .cpp 中定义
            ```

            **优势**：
            - 可直接在类内定义初始化
            - 无需单独的 `.cpp` 文件
            - 支持模块（如 `Box.cppm`）

        - 适用场景

            | 场景 | 示例 |
            | ------ | ------ |
            | 静态成员变量 | `static inline size_t s_count{};` |
            | 头文件中的全局常量 | `inline constexpr double PI = 3.14159;` |
            | 需要跨模块共享的变量 | `inline std::string app_name = "MyApp";` |

    - `static inline` 的组合效果

        **代码示例**：

        ```cpp
        static inline size_t s_object_count{};
        ```

        | 关键字 | 作用 |
        | --- | --- |
        | `static` | 所有对象共享同一份数据（类级别变量） |
        | `inline` | 允许在类内直接定义，支持头文件/模块包含 |

    - 关键区别汇总

        | 特性 | 类内定义函数 | 类外定义函数 | 内联变量 |
        | --- | --- | --- | --- |
        | 隐式/显式 | 隐式 `inline` | 非 `inline`（默认） | 显式 `inline` |
        | 重复定义 | 允许 | 不允许 | 允许 |
        | 典型场景 | 短小成员函数 | 复杂成员函数 | 静态成员、全局常量 |

    - 实战建议

        - 内联函数
            - ✅ 推荐：短小访问器（如 `getVolume()`）、高频计算函数
            - ❌ 不推荐：大型函数、递归、虚函数

        - 内联变量
            - ✅ 推荐：类的静态成员（如计数器）、头文件中的常量
            - ❌ 不推荐：频繁修改的全局变量（影响性能）

    - 复习小贴士
        1. **内联函数**：代码展开，消除调用开销，类内定义默认内联
        2. **内联变量**：C++17 特性，解决头文件变量重复定义问题
        3. **`static inline`**：组合优势，适合类的静态成员变量
        4. **编译器决定**：`inline` 只是建议，最终由编译器决定是否展开

### 12.11.2 访问静态成员变量

- 把静态成员变量s_object_count声明为公共类成员，可以直接在main()中输出对象的个数  
`std::cout << "Object count is " << box1.s_object_count << std::endl;`
- 即使没有创建对象，静态变量也存在，推荐使用这种语法来访问静态变量  
`std::cout << "Object count is " << Box::s_object_count << std::endl;`

### 12.11.3 静态常量

- 静态成员变量常用于定义常量
- 常常定义一些公共常量来包含函数参数的边界值或建议的默认值
- 对关键字static、inline和const的出现没有顺序要求
- 案例Ex12_15
    - cylindrical.cppm

        ```cpp
        // cylindrical.cppm
        export module cylindrical;

        import <string_view>;
        import <string>;

        export class cylindricalBox
        {
        public:
            const static inline float s_max_radius{35.0f};
            const static inline float s_max_height{60.0f};
            const static inline std::string_view s_default_material{"paperboard"};
            cylindricalBox(float radius, float height,
                        std::string_view material = s_default_material);
            float volume() const;

        private:
            const static inline float PI{3.141592f};

            float m_radius;
            float m_height;
            std::string m_material;
        };
        ```

    - cylindrical.cpp

        ```cpp
        // cylindrical.cpp
        module cylindrical;

        import <iostream>;

        cylindricalBox::cylindricalBox(float radius, float height, 
            std::string_view material)
            : m_radius{radius}, m_height{height}, m_material{material}
        {
            std::cout << "Box constructed consisting of " << material;
            if (material == s_default_material)
            {
                std::cout << " (the default material!)";
            }
            std::cout << std::endl;
        }

        float cylindricalBox::volume() const
        {
            return PI * m_radius * m_radius * m_height;
        }
        ```

    - Ex12_15.cpp

        ```cpp
        // Ex12_15.cpp
        import <iostream>;
        import cylindrical;

        int main()
        {
            cylindricalBox bigBox{1.23f, cylindricalBox::s_max_height,
                                cylindricalBox::s_default_material};
            std::cout << "The volume of bigBox is " << bigBox.volume() << std::endl;
        }
        ```

        上面程序运行结果如下：

        ---

        ```cpp
        Box constructed consisting of paperboard (the default material!)  
        The volume of bigBox is 285.175 
        ```

        ---

### 12.11.4 类类型的静态成员变量

- 静态成员变量不是类对象的一部分，所以它可以与类具有相同的类型
    - 静态成员常量声明

        ```cpp
        class Box
        {
            //Rest of the class as before
            //此处声明包含三参数的构造函数

        private:
            const static Box s_reference_box;   //Standard reference box
            // ...
        };
        ```

    - 必须在**类的外部**定义和初始化静态成员  
  `const Box Box::s_reference_box{10.0,10.0,10.0}; //Box构造函数包含三参数`
    - 注意：static关键字仅用于类定义中的静态成员声明，而不能用于定义静态成员
    - 类对象的任何静态和非静态成员函数都可以访问s_reference_box，但不能从类的外部访问它，因为它被声明为私有成员

### 12.11.5 静态成员函数

- 静态成员函数独立于任何单个类对象，任何类对象都可以调用静态成员函数。如果静态成员函数是一个公共成员，还可以从类的外部调用。
- 静态成员函数的一个常见用法是无论是否声明了类的对象，都可以**操作静态成员变量**
- 如果某个成员函数不访问任何非静态成员变量，则应该声明为静态成员函数
- 即使没有创建类的对象，也可以调用公共的静态成员函数。声明类中的静态函数只需要使用关键字static即可
- 调用静态成员函数时，将类名用作限定符  
`std::cout << "Object count is " << Box::getObjectCount() << std::endl;`
- 静态成员函数不能是const。因为静态成员函数与类对象无关，所以它没有this指针，也就不能使用const

## 12.12 析构函数

- 如果对类对象应用delete运算符(堆，new的对象，手动释放)，或者处在创建类对象的块末尾(栈，自动释放)，就会释放类对象，就像基本类型的变量一样

    ```cpp
    #include <iostream>
    #include <string>

    class MyClass {
    private:
        std::string name;
    public:
        // 构造函数 - 对象创建时调用
        MyClass(const std::string& n) : name{n} {
            std::cout << "[构造] " << name << " 被创建\n";
        }
        
        // 析构函数 - 对象释放时调用
        ~MyClass() {
            std::cout << "[析构] " << name << " 被释放\n";
        }
    };

    void testFunction() {
        // 栈上创建对象 - 块作用域结束时自动释放
        MyClass stackObj("栈上对象");
        
        // 堆上创建对象 - 需要手动delete释放
        MyClass* heapObj = new MyClass("堆上对象");
        
        // 使用完堆对象后手动释放
        delete heapObj;
    } // 函数结束，栈对象 stackObj 自动释放

    int main() {
        std::cout << "进入main函数\n";
        
        testFunction();
        
        std::cout << "离开main函数\n";
        return 0;
    }
    ```

    上面程序运行结果如下：

    ---

    ```cpp
    进入main函数
    [构造] 栈上对象 被创建
    [构造] 堆上对象 被创建
    [析构] 堆上对象 被释放
    [析构] 栈上对象 被释放
    离开main函数
    ```

    ---

- 释放类对象时，会执行类的一个特殊成员，称为**析构函数**，默认的析构函数：`~ClassName(){}`。
- 类的析构函数与类同名，但名称前面有一个符号`~`
- 类的析构函数没有参数，也没有返回类型
- 如果该定义位于类的外部，析构函数的名称就要加上类名作为前缀  
`Box::~Box(){}`
- 如果析构函数的函数体为空，最好使用`default`关键字  
`Box::~Box()=default; //让编译器生成一个默认的析构函数`
- 类的析构函数总是在释放对象时自动调用，需要显式调用析构函数的情况很少见，可以忽略不计
- 案例Ex12_16
    - Box.cppm

        ```cpp
        // Box.cppm
        export module Box;
        import <iostream>;

        export class Box
        {
        public:
            Box();
            Box(double side);
            Box(const Box &box);
            Box(double length, double width, double height);
            ~Box();

            double volume() const { return m_length * m_width * m_height; }

            static size_t getObjectCount() { return s_object_count; }

        private:
            double m_length{1.0};
            double m_width{1.0};
            double m_height{1.0};
            static inline size_t s_object_count{};
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
            ++s_object_count;
            std::cout << "Box constructor 1 called." << std::endl;
        }

        Box::Box(double side) : Box{side, side, side}
        {
            // 不要在转发构造函数中增加 s_object_count：
            // 在被转发的构造函数中已经增加过了！
            std::cout << "Box constructor 2 called." << std::endl;
        }

        Box::Box()
        {
            ++s_object_count;
            std::cout << "Default Box constructor called." << std::endl;
        }

        Box::Box(const Box &box)
            : m_length{box.m_length}, m_width{box.m_width}, m_height{box.m_height}
        {
            ++s_object_count;
            std::cout << "Box copy constructor called." << std::endl;
        }

        Box::~Box()
        {
            std::cout << "Box destructor called." << std::endl;
            --s_object_count;
        }
        ```

    - Ex12_16.cpp

        ```cpp
        // Ex12_16.cpp
        import <iostream>;
        import <memory>;
        import Box;

        int main()
        {
            std::cout << "There are now " << Box::getObjectCount() 
                << " Box objects." << std::endl;

            const Box box1{2.0, 3.0, 4.0};
            Box box2{5.0};

            std::cout << "There are now " << Box::getObjectCount() 
                << " Box objects." << std::endl;

            for (double d{}; d < 3.0; ++d)
            {
                Box box{d, d + 1.0, d + 2.0};
                std::cout << "Box volume is " << box.volume() << std::endl;
            }

            std::cout << "There are now " << Box::getObjectCount() 
                << " Box objects." << std::endl;

            auto pBox{std::make_unique<Box>(1.5, 2.5, 3.5)};
            std::cout << "Box volume is " << pBox->volume() << std::endl;
            std::cout << "There are now " << pBox->getObjectCount() 
                << " Box objects." << std::endl;
        }
        ```

        上面程序运行结果如下：

        ---

        ```cpp
        There are now 0 Box objects.
        Box constructor 1 called.
        Box constructor 1 called.
        Box constructor 2 called.
        There are now 2 Box objects.
        Box constructor 1 called.
        Box volume is 0
        Box destructor called.
        Box constructor 1 called.
        Box volume is 6
        Box destructor called.
        Box constructor 1 called.
        Box volume is 24
        Box destructor called.
        There are now 2 Box objects.
        Box constructor 1 called.
        Box volume is 13.125
        There are now 3 Box objects.
        Box destructor called.
        Box destructor called.
        Box destructor called.
        ```

        ---

## 12.13 使用指针作为类成员

- `std::unique_ptr<>`确保不会意外忘记对自由存储区中分配的对象应用delete运算符
- 当多个对象指向并不时地（甚至并发地）使用同一个对象，并且无法推断出什么时候全部使用完该共享对象时，`std::shared_ptr<>`非常有帮助
- 总是应该使用智能指针来管理动态分配的对象。这种原则被称为“资源获取即初始化”(**RAII**)（Resource Acquisition Is Initialization）
- 案例Ex12_17(无模块分区方式)
    - Box.cppm

        ```cpp
        // Box.cppm
        export module box;          // 声明模块 box

        import <iostream>;          // 导入标准库头文件作为模块
        import <format>;

        export class Box            // 导出 Box 类
        {
        public:
            Box() = default;        // 默认构造函数，使用成员初始值 1.0
            Box(double length, double width, double height)
                : m_length{ length }, m_width{ width }, m_height{ height }
            {
            }

            double volume() const   // 计算体积
            {
                return m_length * m_width * m_height;
            }

            int compare(const Box& box) const
            {
                if (volume() < box.volume())
                    return -1;
                if (volume() == box.volume())
                    return 0;
                return +1;
            }

            void listBox() const
            {
                // 使用 std::format 格式化输出（C++20 特性）
                std::cout << std::format("Box({:.1f},{:.1f},{:.1f})",
                    m_length, m_width, m_height);
            }

        private:
            double m_length{ 1.0 };   // 默认尺寸均为 1.0
            double m_width{ 1.0 };
            double m_height{ 1.0 };
        };
        ```

    - RandomBoxes.cppm

        ```cpp
        // RandomBoxes.cppm
        export module box.random;
        import box;
        import <random>;            // 随机数库
        import <functional>;        // std::bind()
        import <memory>;            // std::make_shared<>(), std::shared_ptr<>

        // 创建一个伪随机数生成器（PRNG），用于生成 [0, max) 之间的随机双精度数
        auto createUniformPseudoRandomNumberGenerator(double max)
        {
            std::random_device seeder;                  // 真随机数生成器，提供种子（速度慢）
            std::default_random_engine generator{ seeder() };   // 高效的伪随机数引擎
            std::uniform_real_distribution distribution{ 0.0, max };
            // 均匀分布 [0, max)
            // 将生成器和分布绑定成一个可调用对象，每次调用返回一个随机数
            return std::bind(distribution, generator);
        }

        export Box randomBox()
        {
            const int dimLimit{ 100 };   // 盒子尺寸上限
            static auto random{ createUniformPseudoRandomNumberGenerator
                (dimLimit) };
            // 返回三个随机数作为长、宽、高
            return { random(), random(), random() };
        }

        export auto randomSharedBox()
        {
            // 用随机 Box 创建一个 shared_ptr
            return std::make_shared<Box>(randomBox());
        }
        ```

    - Truckload.cppm

        ```cpp
        // Truckload.cppm
        export module truckload;

        import <memory>;
        import <vector>;
        import box;                  // 需要完整的 Box 定义

        export using SharedBox = std::shared_ptr<Box>;   // 导出共享指针类型别名

        class Package;              // 前置声明，隐藏内部链表节点的定义

        export class Truckload      // 导出卡车装载类
        {
        public:
            Truckload() = default;                          // 默认构造函数 - 空卡车
            Truckload(SharedBox box);                       // 构造函数 - 添加单个箱子
            Truckload(const std::vector<SharedBox>& boxes); // 构造函数 - 从向量初始化
            Truckload(const Truckload& src);                // 拷贝构造函数

            ~Truckload(); // 析构函数，负责释放链表

            SharedBox getFirstBox();       // 获取第一个箱子，并重置遍历指针
            SharedBox getNextBox();        // 获取下一个箱子
            void addBox(SharedBox box);    // 向链表尾部添加箱子
            bool removeBox(SharedBox box); // 从链表移除指定箱子（成功返回 true）
            void listBoxes() const;        // 打印所有箱子

        private:
            Package* m_head{};    // 链表头节点
            Package* m_tail{};    // 链表尾节点（用于快速追加）
            Package* m_current{}; // 遍历时指向当前节点
        };
        ```

    - Truckload.cpp

        ```cpp
        // Truckload.cpp
        module truckload;          // 模块实现单元（无 export）

        import <iostream>;
        import <format>;

        // 链表节点类：模块内部使用，外界不可见
        class Package
        {
        public:
            Package(SharedBox box) : m_box{ box }, m_next{ nullptr } {}
            ~Package() { delete m_next; }   // 递归删除后续节点，实现整条链表清理

            SharedBox getBox() const { return m_box; }   // 获取本节点箱子
            Package* getNext() { return m_next; }        // 获取下一节点地址
            void setNext(Package* package) { m_next = package; }

        private:
            SharedBox m_box;      // 指向共享 Box 的智能指针
            Package* m_next;      // 原生指针指向下一个节点
        };

        // --- Truckload 成员函数实现 ---

        // 构造函数：创建一个只包含一个箱子的链表
        Truckload::Truckload(SharedBox box)
        {
            m_head = m_tail = new Package{ box };
        }

        // 构造函数：从 shared_ptr 向量批量添加
        Truckload::Truckload(const std::vector<SharedBox>& boxes)
        {
            for (const auto& box : boxes)
                addBox(box);
        }

        // 拷贝构造函数：遍历源链表，逐个添加箱子（深拷贝）
        Truckload::Truckload(const Truckload& src)
        {
            for (Package* package{ src.m_head }; package; package = package->getNext())
            {
                addBox(package->getBox());
            }
        }

        // 析构函数：只需删除头节点，Package 的析构函数会递归清理整个链表
        Truckload::~Truckload()
        {
            delete m_head;
        }

        void Truckload::listBoxes() const
        {
            const size_t boxesPerLine{ 4 };    // 每行打印 4 个箱子
            size_t count{};
            for (Package* package{ m_head }; package; package = package->getNext())
            {
                std::cout << ' ';
                package->getBox()->listBox();   // 调用 Box 的格式化输出
                if (!(++count % boxesPerLine))  // 满 4 个换行
                    std::cout << std::endl;
            }
            if (count % boxesPerLine)           // 最后一行不足 4 个也换行
                std::cout << std::endl;
        }

        SharedBox Truckload::getFirstBox()
        {
            // 将当前遍历指针设为链表头，并返回其箱子（或空链表则返回 nullptr）
            m_current = m_head;
            return m_current ? m_current->getBox() : nullptr;
        }

        SharedBox Truckload::getNextBox()
        {
            if (!m_current)               // 若当前指针为空，从头开始
                return getFirstBox();

            m_current = m_current->getNext();  // 移动到下一节点
            return m_current ? m_current->getBox() : nullptr;
        }

        void Truckload::addBox(SharedBox box)
        {
            auto package{ new Package{box} };   // 创建新节点

            if (m_tail)                       // 链表非空
                m_tail->setNext(package);     // 将新节点挂到尾节点之后
            else                              // 链表为空
                m_head = package;             // 新节点成为头节点

            m_tail = package;                 // 更新尾节点
        }

        bool Truckload::removeBox(SharedBox boxToRemove)
        {
            Package* previous{ nullptr };       // 跟踪前驱节点
            Package* current{ m_head };        // 从头开始搜索

            while (current)
            {
                if (current->getBox() == boxToRemove)   // 找到目标箱子
                {
                    // 调整前驱节点的 next 指针，绕过当前节点
                    if (previous)
                        previous->setNext(current->getNext());

                    // 更新头、尾、当前指针（如果它们指向被删除的节点）
                    if (current == m_head)
                        m_head = current->getNext();
                    if (current == m_tail)
                        m_tail = previous;
                    if (current == m_current)
                        m_current = current->getNext();

                    current->setNext(nullptr);   // 断开与被删除节点的连接
                    delete current;              // 删除节点（仅此一个，不递归删除后续）
                    return true;
                }

                // 未找到，继续向后移动
                previous = current;
                current = current->getNext();
            }
            return false;   // 未找到
        }
        ```

    - Ex12_17.cpp

        ```cpp
        // Ex12_17.cpp
        // 使用链表管理卡车上的箱子
        import box.random;
        import truckload;
        import <iostream>;
        import <vector>;

        int main()
        {
            Truckload load1;                // 创建一个空的卡车装载列表

            // 向列表中添加 12 个随机 Box 对象
            const size_t boxCount{12};
            for (size_t i{}; i < boxCount; ++i)
                load1.addBox(randomSharedBox());

            std::cout << "The first list:\n";
            load1.listBoxes();

            // 拷贝整个卡车装载
            Truckload copy{load1};
            std::cout << "The copied truckload:\n";
            copy.listBoxes();

            // 寻找最大的箱子
            SharedBox largestBox{load1.getFirstBox()};
            SharedBox nextBox{load1.getNextBox()};
            while (nextBox)
            {
                if (nextBox->compare(*largestBox) > 0)   // 调用 Box::compare
                    largestBox = nextBox;
                nextBox = load1.getNextBox();
            }

            std::cout << "\nThe largest box in the first list is ";
            largestBox->listBox();
            std::cout << std::endl;

            load1.removeBox(largestBox);
            std::cout << "\nAfter deleting the largest box, the list contains:\n";
            load1.listBoxes();

            // 用 std::vector 初始化第二个装载
            const size_t nBoxes{20};
            std::vector<SharedBox> boxes;
            for (size_t i{}; i < nBoxes; ++i)
                boxes.push_back(randomSharedBox());

            Truckload load2{boxes};
            std::cout << "\nThe second list:\n";
            load2.listBoxes();

            // 寻找最小的箱子
            auto smallestBox{load2.getFirstBox()};
            for (auto box{load2.getNextBox()}; box; box = load2.getNextBox())
                if (box->compare(*smallestBox) < 0)
                    smallestBox = box;

            std::cout << "\nThe smallest box in the second list is ";
            smallestBox->listBox();
            std::cout << std::endl;
        }
        ```

        上面程序运行结果如下：

        ---

        ```cpp
        The first list:
        Box(30.3,59.0,38.5) Box(97.8,63.7,7.4) Box(0.5,86.6,80.2) Box(76.0,9.9,87.0)
        Box(79.1,11.5,84.2) Box(53.8,29.6,93.9) Box(58.0,14.6,11.7) Box(26.2,82.7,76.5)
        Box(45.4,98.5,35.0) Box(43.4,95.8,34.0) Box(35.8,68.6,86.2) Box(51.3,92.5,97.3)
        The copied truckload:
        Box(30.3,59.0,38.5) Box(97.8,63.7,7.4) Box(0.5,86.6,80.2) Box(76.0,9.9,87.0)
        Box(79.1,11.5,84.2) Box(53.8,29.6,93.9) Box(58.0,14.6,11.7) Box(26.2,82.7,76.5)
        Box(45.4,98.5,35.0) Box(43.4,95.8,34.0) Box(35.8,68.6,86.2) Box(51.3,92.5,97.3)

        The largest box in the first list is Box(51.3,92.5,97.3)

        After deleting the largest box, the list contains:
        Box(30.3,59.0,38.5) Box(97.8,63.7,7.4) Box(0.5,86.6,80.2) Box(76.0,9.9,87.0)
        Box(79.1,11.5,84.2) Box(53.8,29.6,93.9) Box(58.0,14.6,11.7) Box(26.2,82.7,76.5)
        Box(45.4,98.5,35.0) Box(43.4,95.8,34.0) Box(35.8,68.6,86.2)

        The second list:
        Box(24.4,83.8,54.6) Box(11.6,4.8,14.9) Box(89.4,73.1,67.5) Box(43.3,59.8,1.0)
        Box(31.9,94.8,1.8) Box(76.5,30.0,34.7) Box(9.6,45.7,75.4) Box(49.5,93.9,19.4)
        Box(10.0,43.1,53.6) Box(3.6,60.3,22.2) Box(19.3,47.5,66.7) Box(17.6,86.6,6.4)
        Box(11.4,28.1,62.9) Box(83.9,43.3,68.1) Box(86.6,16.7,73.6) Box(92.1,76.3,95.0)
        Box(15.8,73.7,36.6) Box(72.4,3.0,25.5) Box(26.1,67.1,13.7) Box(65.3,0.2,17.5)

        The smallest box in the second list is Box(65.3,0.2,17.5)
        ```

        ---

- Ex12_17A(分区模块方式，须在vscode+msvc+cmake+minja环境编译(后三者在vs2026中包含))
    - Box.cppm

        ```cpp
        // Box.cppm
        export module box;

        import <iostream>;
        import <format>;

        export class Box
        {
        public:
        Box() = default;
        Box(double length, double width, double height)
            : m_length{ length }, m_width{ width }, m_height{ height } {
        };

        double volume() const
        {
            return m_length * m_width * m_height;
        }

        int compare(const Box& box) const
        {
            if (volume() < box.volume()) return -1;
            if (volume() == box.volume()) return 0;
            return +1;
        }

        void listBox() const
        {
            std::cout << std::format("Box({:.1f},{:.1f},{:.1f})", m_length,
            m_width, m_height);
        }

        private:
        double m_length{ 1.0 };
        double m_width{ 1.0 };
        double m_height{ 1.0 };
        };
        ```

    - RandomBoxes.cppm

        ```cpp
        // RandomBoxes.cppm
        export module box.random;
        import box;
        import <random>;        // For random number generation
        import <functional>;    // For std::bind()
        import <memory>;        // For std::make_shared<>() and std::shared_ptr<>;

        // Creates a pseudorandom number generator (PRNG) for random
        // doubles between 0 and max
        auto createUniformPseudoRandomNumberGenerator(double max)
        {
        std::random_device seeder;
        // True random number generator to obtain a seed (slow)
        std::default_random_engine generator{ seeder() };    
        // Efficient pseudo-random generator
        std::uniform_real_distribution distribution{ 0.0, max }; 
        // Generate in [0, max) interval
        return std::bind(distribution, generator);
        //... and in the darkness bind them!
        }

        export Box randomBox()
        {
        const int dimLimit{ 100 };          // Upper limit on Box dimensions
        static auto random{ createUniformPseudoRandomNumberGenerator(dimLimit) };
        return { random(), random(), random() };
        }

        export auto randomSharedBox()
        {
        return std::make_shared<Box>(randomBox());   // Uses copy constructor
        }
        ```

    - SharedBox.cppm

        ```cpp
        // SharedBox.cppm
        export module truckload:shared_box;

        import <memory>;
        import box;

        export using SharedBox = std::shared_ptr<Box>;
        ```

    - Package.cpp

        ```cpp
        // Package.cpp
        export module truckload:package;

        import :shared_box;

        class Package
        {
        public:
        Package(SharedBox box) : m_box{ box }, m_next{ nullptr } {}  // Constructor
        ~Package() { delete m_next; }                            // Destructor

        // Retrieve the Box pointer
        SharedBox getBox() const { return m_box; }

        // Retrieve or update the pointer to the next Package
        Package* getNext() { return m_next; }
        void setNext(Package* package) { m_next = package; }

        private:
        SharedBox m_box;    // Pointer to the Box object contained in this Package
        Package* m_next;    // Pointer to the next Package in the list
        };
        ```

    - Truckload.cppm

        ```cpp
        // Truckload.cppm
        export module truckload;

        export import :shared_box;
        import :package;
        import <vector>;

        export class Truckload
        {
        public:
        Truckload() = default;            // Default constructor - empty truckload

        Truckload(SharedBox box);         // Constructor - one Box
        Truckload(const std::vector<SharedBox>& boxes);  
        // Constructor - vector of Boxes
        Truckload(const Truckload& src);  // Copy constructor

        ~Truckload();                     // Destructor

        SharedBox getFirstBox();          // Get the first Box
        SharedBox getNextBox();           // Get the next Box
        void addBox(SharedBox box);       // Add a new SharedBox
        bool removeBox(SharedBox box);    // Remove a Box from the Truckload
        void listBoxes() const;           // Output the Boxes

        private:
        Package* m_head {};               // First in the list
        Package* m_tail {};               // Last in the list
        Package* m_current {};            // Last retrieved from the list
        };
        ```

    - Truckload-impl.cpp

        ```cpp
        // Truckload-impl.cpp
        module truckload;

        import <iostream>;

        // Constructor - one Box (moved to source file to gain access to 
        // definition of Package)
        Truckload::Truckload(SharedBox box)          
        {
        m_head = m_tail = new Package{ box };
        }

        // Constructor - vector of Boxes
        Truckload::Truckload(const std::vector<SharedBox>& boxes)
        {
        for (const auto& box : boxes)
        {
            addBox(box);
        }
        }

        // Copy constructor
        Truckload::Truckload(const Truckload& src)
        {
        for (Package* package{ src.m_head }; package; package = package->getNext())
        {
            addBox(package->getBox());
        }
        }

        // Destructor: clean up the list (moved to source file to gain access to
        // definition of Package)
        Truckload::~Truckload()
        {
        delete m_head;
        }

        void Truckload::listBoxes() const
        {
        const size_t boxesPerLine{ 4 };
        size_t count {};  
        for (Package* package{m_head}; package; package = package->getNext())
        {
            std::cout << ' ';
            package->getBox()->listBox();
            if (! (++count % boxesPerLine)) std::cout << std::endl;
        }
        if (count % boxesPerLine) std::cout << std::endl;
        }


        SharedBox Truckload::getFirstBox()
        {
        // Return m_head's box (or nullptr if the list is empty)
        m_current = m_head;
        return m_current? m_current->getBox() : nullptr;
        }

        SharedBox Truckload::getNextBox()
        {
        if (!m_current)                                    // If there's no current...
            return getFirstBox();                            
            // ...return the 1st Box

        m_current = m_current->getNext();                  // Move to the next package

        return m_current? m_current->getBox() : nullptr;   
        // Return its box (or nullptr...).
        }

        void Truckload::addBox(SharedBox box)
        {
        auto package{ new Package{box} }; // Create a new Package

        if (m_tail)                      // Check list is not empty
            m_tail->setNext(package);      // Append the new object to the tail
        else                             // List is empty
            m_head = package;              // so new object is the head

        m_tail = package;                
        // Either way: the latest object is the (new) tail
        }

        bool Truckload::removeBox(SharedBox boxToRemove)
        {
        Package* previous {nullptr};      // no previous yet
        Package* current {m_head};        // initialize current to the head of 
        // the list
        while (current)
        {
            if (current->getBox() == boxToRemove)      // We found the Box!
            {
            // If there is a previous Package make it point to the next one 
            // (Figure 12.10)
            if (previous) previous->setNext(current->getNext());

            // Update pointers in member variables where required:
            if (current == m_head) m_head = current->getNext();
            if (current == m_tail) m_tail = previous;
            if (current == m_current) m_current = current->getNext();

            current->setNext(nullptr);        // Disconnect the current 
            // Package from the list
            delete current;                   // and delete it

            return true;                      
            // Return true: we found and removed the box
            }
            // Move both pointers along (mind the order!)
            previous = current; //  - first current becomes the new previous
            current = current->getNext();       
            //  - then move current along to the next Package
        }

        return false;     // Return false: boxToRemove was not found
        }
        ```

    - Ex12_17.cpp

        ```cpp
        // Ex12_17.cpp
        // Using a linked list
        import box.random;
        import truckload;
        import <iostream>;
        import <vector>;

        int main()
        {
        Truckload load1; // Create an empty list

        // Add 12 random Box objects to the list
        const size_t boxCount{12};
        for (size_t i{}; i < boxCount; ++i)
            load1.addBox(randomSharedBox());

        std::cout << "The first list:\n";
        load1.listBoxes();

        // Copy the truckload
        Truckload copy{load1};
        std::cout << "The copied truckload:\n";
        copy.listBoxes();

        // Find the largest Box in the list
        SharedBox largestBox{load1.getFirstBox()};

        SharedBox nextBox{load1.getNextBox()};
        while (nextBox)
        {
            if (nextBox->compare(*largestBox) > 0)
            largestBox = nextBox;
            nextBox = load1.getNextBox();
        }

        std::cout << "\nThe largest box in the first list is ";
        largestBox->listBox();
        std::cout << std::endl;
        load1.removeBox(largestBox);
        std::cout << "\nAfter deleting the largest box, the list contains:\n";
        load1.listBoxes();

        const size_t nBoxes{20};      // Number of vector elements
        std::vector<SharedBox> boxes; // Array of Box objects

        for (size_t i{}; i < nBoxes; ++i)
            boxes.push_back(randomSharedBox());

        Truckload load2{boxes};
        std::cout << "\nThe second list:\n";
        load2.listBoxes();

        auto smallestBox{load2.getFirstBox()};
        for (auto box{load2.getNextBox()}; box; box = load2.getNextBox())
            if (box->compare(*smallestBox) < 0)
            smallestBox = box;

        std::cout << "\nThe smallest box in the second list is ";
        smallestBox->listBox();
        std::cout << std::endl;
        }
        ```

        上面程序运行结果如下：

        ---

        ```cpp
        The first list:
        Box(33.9,11.0,3.6) Box(55.1,7.3,72.6) Box(6.2,7.5,97.2) Box(22.6,88.9,53.0)
        Box(49.6,64.6,95.1) Box(26.5,29.3,31.2) Box(40.2,52.4,15.2) Box(46.1,7.3,9.3)
        Box(91.3,62.4,97.5) Box(74.5,78.1,9.0) Box(18.3,77.0,34.6) Box(24.6,48.3,36.1)
        The copied truckload:
        Box(33.9,11.0,3.6) Box(55.1,7.3,72.6) Box(6.2,7.5,97.2) Box(22.6,88.9,53.0)
        Box(49.6,64.6,95.1) Box(26.5,29.3,31.2) Box(40.2,52.4,15.2) Box(46.1,7.3,9.3)
        Box(91.3,62.4,97.5) Box(74.5,78.1,9.0) Box(18.3,77.0,34.6) Box(24.6,48.3,36.1)
        The largest box in the first list is Box(91.3,62.4,97.5)

        After deleting the largest box, the list contains:
        Box(33.9,11.0,3.6) Box(55.1,7.3,72.6) Box(6.2,7.5,97.2) Box(22.6,88.9,53.0)
        Box(49.6,64.6,95.1) Box(26.5,29.3,31.2) Box(40.2,52.4,15.2) Box(46.1,7.3,9.3)
        Box(74.5,78.1,9.0) Box(18.3,77.0,34.6) Box(24.6,48.3,36.1)

        The second list:
        Box(13.8,2.1,85.7) Box(62.3,19.9,68.4) Box(40.0,11.2,27.0) Box(57.2,27.3,71.8)
        Box(13.7,9.3,9.7) Box(58.4,47.8,43.1) Box(51.9,18.7,62.4) Box(5.4,66.4,58.9)
        Box(9.3,86.0,96.9) Box(85.7,23.4,86.2) Box(18.1,35.0,84.9) Box(28.2,55.6,76.8)
        Box(66.7,34.7,55.6) Box(98.2,19.8,81.1) Box(52.3,67.7,36.7) Box(42.0,47.3,5.5)
        Box(47.7,55.4,31.5) Box(72.6,85.8,51.9) Box(45.0,88.8,48.2) Box(93.8,2.6,9.7)

        The smallest box in the second list is Box(13.7,9.3,9.7)
        ```

        ---
