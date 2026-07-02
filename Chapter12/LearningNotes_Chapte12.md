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
