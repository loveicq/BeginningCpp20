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
- 关键字public是基类访问修饰符，决定了基类成员如何在派生类中访问
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
