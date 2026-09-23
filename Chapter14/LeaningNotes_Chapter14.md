# 第14章 继承

## 14.1 类和面向对象编程

本章介绍“是”和“有”这两种关系如何用类来表示

**类层次结构**  

- class Box -> class Carton -> class FoodCarton
- UML是面积对象软件程序的可视化设计的事实标准

## 14.2 类的继承

- 基类（父类）：Carton类是FoodCarton类的直接基类；Box类是FoodCarton类的间接基类
- 派生类（子类）：派生类继承了基类的成员变量和成员函数，还有自己的成员变量和成员函数

### 14.2.1 继承和聚合

- 种类测试：任何派生类对象都是基类类型的对象
- 基类中是否有特性不能应用于派生类？
- 包含测试: automobile对象可以把engine对象、transmission对象和differential对象作为成员变量，这种关系称为聚合
    - 组合：House和Room的关系，Room不能脱离House存在
    - 聚合：Class和Student的关系，即使课程取消，学生也仍然存在

### 14.2.2 派生类

- 语法：派生类名:基类名 `export class Carton : public Box`
- 关键字public是**基类访问修饰符**，决定了基类成员如何在派生类中访问
- 案例Ex14_01
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

            double getLength() const { return m_length; }
            double getWidth() const { return m_width; }
            double getHeight() const { return m_height; }

        private:
            double m_length{1.0};
            double m_width{1.0};
            double m_height{1.0};
        };
        ```

    - Carton.cppm

        ```cpp
        export module carton;

        import <string>;
        import <string_view>;
        import box;

        export class Carton : public Box
        {
        public:
            explicit Carton(std::string_view material = "Cardboard")
                : m_material{material} {}

        private:
            std::string m_material;
        };
        ```

    - Ex14_01.cpp

        ```cpp
        // Ex14_01.cpp
        import <iostream>;
        import box;
        import carton;

        int main()
        {
            Box box{40.0, 30.0, 20.0};
            Carton carton;
            Carton chocolateCarton{"Solid bleached board"}; // Good old SBB

            std::cout << "box occupies " << sizeof box << " bytes" << std::endl;
            std::cout << "carton occupies " << sizeof carton << " bytes" << std::endl;
            std::cout << "candyCarton occupies " << sizeof chocolateCarton << " bytes"
                        << std::endl;

            std::cout << "box's volume is " << box.volume() << std::endl;
            std::cout << "carton's volume is " << carton.volume() << std::endl;
            std::cout << "chocolateCarton's volume is " << chocolateCarton.volume() << std::endl;

            std::cout << "chocolateCarton's length is " << chocolateCarton.getLength() 
                        << std::endl;

            // Uncomment any of the following for an error...
            // box.m_length = 10.0;
            // chocolateCarton.m_length = 10.0;
        }
        ```

        以上程序运行结果如下：

        ---

        ```cpp
        box occupies 24 bytes
        carton occupies 64 bytes
        candyCarton occupies 64 bytes
        box volume is 24000
        carton volume is 1
        chocolateCarton volume is 1
        chocolateCarton length is 1
        ```

        ---

- 访问器函数是继承的，可供派生类对象调用
- 基类的成员变量如果是私有的，它们在派生类对象中仍然是私有的，不能在类的外部访问。基类和派生类以外都不能访问基类的private成员变量

## 14.3 把类的成员声明为protected

- 声明为protected的类成员不能在类的外部访问，但可以由声明为friend的函数访问
- 声明为protected的基类成员可以在派生类的成员函数中访问，而基类的私有成员则不能

## 14.4 派生类成员的访问级别

- 有3种基类访问修饰符：`public`、`protected`和`private`
- 默认的访问修饰符是`private`
- 一张表搞定访问权限规则如下（第一列是**基类成员自身的修饰符**，在基类中声明；
  后三列是**继承方式**，在派生类声明基类时指定）：

    | 基类成员修饰符 | public继承方式 | protected继承方式 | private继承方式 |
    | :---: | :---: | :---: | :---: |
    | public 成员 | 还是public | 变成protected | 变成private |
    | protected 成员 | 还是protected | 变成protected | 变成private |
    | private 成员 | 不可见 | 不可见 | 不可见 |

    - 成员修饰符：写在基类里，管的是"我自己的成员"
    - 继承方式：写在派生类里，管的是"我怎么接收基类的成员"

### 14.4.1 在类层次结构中使用访问修饰符

这节的核心内容就是教具体怎么写代码（纯语法）：

- 访问修饰符（public/protected/private）可以出现在两个地方
- 出现在类体内 → 修饰成员
- 出现在派生列表中 → 修饰继承方式
- 两者组合起来决定最终访问权限（就是那上面张表的内容）

### 14.4.2 在类层次结构中选择访问修饰符

这节主要教实际开发中该用哪个（设计决策）

- 关于成员修饰符的选择

    ```cpp
    class Base {
        // ✅ 首选 private：封装，不让外部乱改
        //    派生类也不能直接访问，只能通过 public 的 getter/setter
        int secret;

        // ⚠️ 选 protected：确实希望派生类能直接访问
        //    但外部不能访问。实际项目里很少用，因为会破坏封装
    protected:
        int data;

        // ✅ 选 public：就是给外部和派生类用的接口
    public:
        void setSecret(int v) { secret = v; }
        int getSecret() const { return secret; }
    };
    ```

- 关于继承方式的选择

    ```cpp
    // ✅ 几乎永远是 public 继承：
    // "Derived 是一种 Base"——是 is-a 关系
    class Dog : public Animal { };

    // ⚠️ protected 继承：极少用
    // 表示"我继承了，但不想让我的外部使用者知道"
    // 相当于把基类的 public 全变成 protected

    // ⚠️ private 继承：相当于"has-a"（组合）的替代
    // 表示"我用了 Base 的实现，但不想暴露任何接口"
    // 实际项目中几乎被组合（成员对象）取代
    class MyString : private std::string { }; // 不如直接用成员
    ```

### 14.4.3 改变继承成员的访问修饰符

使用using声明，可以把某个继承成员的访问状态恢复为基类的public

- 在对基类的成员名应用using声明时，必须用基类名限定成员名，因为这指定了成员名的上下文
- 不应该给函数提供参数列表或返回类型，仅提供成员函数的限定名即可
- using声明也被应用于派生类的继承成员变量
- 可以使用using声明重写基类中的public或protected基类访问修饰符。如，如果volume()防火建筑在Box基类中是受保护成员，就可以在派生类Carton的public部分使用using声明，使它成员公共成员
- 不能把using声明应用于基类的私有成员
