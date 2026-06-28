# 第11章 模块和名称空间

## 11.1 模块

- C++实体：变量、函数、类、枚举、模板等  
- C++中首选的机制是创建相关功能的自包含的子组件，它们被称为模块  
- 模块导出的所有实体的组合称为模块接口  
- 通常会为实现了某个公共用途的每个代码集合使用一个单独的模块

### 11.1.1 第一个模块

1. 模块命名：`module 模块名称;`，如`module math;`，如果要导出模块里面的实体，则module前面再加关键字`export`。如果module前面带有export关键字，则该文件是**模块接口文件**
2. 模块名称中允许使用点号"."，用作子模块的连接符号：`math.polynomials`
3. 在编译.cpp文件前，一般要先编译它导入的所有模块的接口文件

    - Ex11_01.cpp

        ```cpp
        // Ex11_01.cpp - Consuming your own module
        import<iostream>;
        import<format>;
        import math;

        int main()
        {
            std::cout << "Lambda squared: " << square(lambda) << std::endl;

            int number;
            std::cout << "\nPlease enter an odd number: ";
            std::cin >> number;
            std::cout << std::endl;

            switch (getOddity(number))
            {
                using enum Oddity;
            case Odd:
                std::cout
                    << "Well done! And remember:
                     you have to be odd to be number one!";
                break;
            case Even:
                std::cout << std::format("Odd, {} seems to be even?", number);
                break;
            }
            std::cout << std::endl;

            std::cin.ignore();
            std::cin.get();
        }
        ```

    - math.cppm

        ```cpp
        //math.cppm - Your first module
        export module math;

        export auto square(const auto& x) { return x * x; }
        //An abbreviated function template

        export const double lambda{ 1.303577269034296391257 };//Conway's constant

        export enum class Oddity { Even, Odd };

        bool isOdd(int x) { return x % 2 != 0; }//Module-local function (not exported)
        export auto getOddity(int x) { return isOdd(x) ? Oddity::Odd 
        : Oddity::Even; }
        ```

    - 以上程序运行结果如下：

        ---

        ```cpp
        Lambda squared: 1.69931

        Please enter an odd number: 555

        Well done! And remember: you have to be odd to be number one!
        ```

        ---

### 11.1.2 导出块

1. 通过把多个实体放到一个导出块中，也可以一次性导出多个实体

    ```cpp
    //math.cppm - Exporting multiple entities at once
    export module math;

    bool isOdd(int x){return x%2 != 0;}//Module-local function (not exported)

    export
    {
        auto square(const auto& x){return x*x;}
        const module lambda{1.303577269034296391257};//Conway's constant

        enum class Oddity{Even,Odd};
        auto getOddity(int x){return isOdd(x) ? Oddity::Odd : Oddity::Even;}
    }
    ```

### 11.1.3 将接口与实现分开

1. 如果在第一次声明实体时，没有使用export，那么就不能在后面声明该实体时添加export

    ```cpp
    //math.cppm - Exporting multiple entities at once
    export module math;

    export
    {
        auto square(const auto& x);
        const module lambda{1.303577269034296391257};//Conway's constant

        enum class Oddity{Even,Odd};
        auto getOddity(int x);
    }

    //The implementation of the module's function (+ local helpers)
    auto square(const auto&x){return x*x;}

    bool isOdd(int x){return x%2 != 0;}
    auto getOddity(int x){return isOdd(x) ? Oddity::Odd : Oddity::Even;}
    ```

**1. 模块实现文件**  

- 在一个模块文件中，所有import声明必须出现在module声明之后，其他任何声明之前

    ```cpp
    //roman.ixx
    export module roman;//模块文件，除了注释行，第一行必须是module
    import <iostream>;//import声明必须在module之后，其他任何声明之前
    import <string_view>;

    export std::string to_roman(unsigned int i);
    ```

- 模块实现文件是.cpp格式，必须包含一个module声明。

    ```cpp
    //to_roman.cpp
    module roman;//模块实现文件必须包含module声明

    std::string to_roman(unsigned int i)
    {
        ...
    }
    ```

    - Ex11_02.cpp

        ```cpp
        //Ex11_02.cpp
        import <iostream>;
        import <string>;
        import roman;

        int main()
        {
            std::cout << "1234 in Roman numerals is " << to_roman(1234) << std::endl;
            std::cout << "MMXX in Arabic numerals is " << from_roman("MMXX") 
            << std::endl;
        }
        ```

    - roman.ixx

        ```cpp
        // roman.ixx - Interface file for a Roman numerals module
        //这个接口单元有两个实现单元，to_roman.cpp和from_roman.cpp
        //如果两个或多个实现单元还不够，可以使用模块分区实现
        export module roman;
        import <string>;
        import <string_view>;

        export std::string to_roman(unsigned i);
        export unsigned from_roman(std::string_view roman);
        ```

    - to_roman.cpp

        ```cpp
        //to_roman.cpp
        module roman;   //roman.ixx实现单元1

        std::string to_roman(unsigned i)
        {
            if (i > 3999) return{ };
            static const std::string ms[]
            { "","M","MM","MMM" };
            static const std::string cds[]
            { "","C","CC","CCC","CD","D","DC","DCC","DCCC","CM" };
            static const std::string xls[]
            { "","X","XX","XXX","XL","L","LX","LXX","LXXX","XC" };
            static const std::string ivs[]
            { "","I","II","III","IV","V","VI","VII","VIII","IX" };

            return ms[i / 1000] + cds[(i % 1000) / 100] + xls[(i % 100) / 10] 
            + ivs[i % 10];
        }
        ```

    - from_roman.cpp

        ```cpp
        //from_roman.cpp
        module roman;   //roman.ixx实现单元2

        unsigned from_roman(char c)
        {
            switch (c)
            {
                case 'I': return 1;
                case 'V': return 5;
                case 'X': return 10;
                case 'L': return 50;
                case 'C': return 100;
                case 'D': return 500;
                case 'M': return 1000;
                default: return 0;
            }
        }

        unsigned from_roman(std::string_view roman)
        {
            unsigned result{};
            const auto n{roman.length()};
            for (size_t i{};i < n;++i)
            {
                const auto j{ from_roman(roman[i]) };
                if (i + 1 == n || j >= from_roman(roman[i + 1]))
                    result += j;
                else
                    result -= j;
            }

            return result;
        }
        ```

    - 上面程序运行结果如下：

        ---

        ```cpp
        1234 in Roman numerals is MCCXXXIV
        MMXX in Arabic numerals is 2020 
        ```

        ---

**2.实现文件的限制**  

- 一般来说，导入模块的文件在使用某个导出的功能时所需要的内容，必须的模块接口文件中存在
- 要使auto返回类型推断能够工作，编译器需要函数定义是模块接口的一部分

**3.实现文件中的隐式导入**  

- 可以想象为，`module roman;`这样的声明在下一行隐式添加了`import roman;`
（不允许在`module roman;`后面显式添加`import roman;`）
- 每当把模块的一个部分导入同一个模块的另一个部分，后者实际上能够访问前者的所有声明，
甚至是未被导出的声明。例如Ex11_02案例中from_roman.cpp和to_roman.cpp能够访问
roman.ixx中的`import <string>;`和`import <string_view>;`声明，所以不用再重复import这两个模块
- 只有`module my_module;`这种形式的module声明才会添加隐式的`import my_module;`声明
（并因而阻止了显式的`import my_module;`声明）。模块分区的`module my_module:Partition;`声明没有这种行为。
要在分区文件中访问模块接口文件的全部声明，必须显式添加`import my_module;`

### 11.1.4 可达性与可见性

1. 当把一个`模块`导入`其他模块`的文件时，不会隐式继承模块接口文件中的所有导入（注意，这是.ixx文件导入其它的.ixx的关系时）
2. C++区分实体声明的可达性与其名称的可见性

    - Ex11_03.cpp

        ```cpp
        //Ex11_03.cpp
        import<iostream>;
        import roman;

        int main()
        {
            std::cout << "MMXX in Arabic numerals is " << from_roman("MMXX") <<std::endl;
            std::cout << "1234 in Roman numerals is " << to_roman(1234).data() 
            << std::endl;
            std::cout << "This consists of " << to_roman(1234).size() 
            << " numerals" << std::endl;

            auto roman{ to_roman(567) };
            std::cout << "567 in Roman numerals is " << roman.c_str() << std::endl;

            //to_roman(1234).data()、to_roman.c_str()和to_roman(1234)三者的区别是什么？
            //教材中的to_roman(1234).c_data()是错的，没有这个成员函数

            //教材说没有import<string>;的话此行会出错，但我测试了没有问题，可能是编译器的原因
            std::cout << "1234 in Roman numerals is " << to_roman(1234) << std::endl;

            std::cin.get();
        }
        ```

    - roman.ixx

        ```cpp
        //roman.ixx
        export module roman;
        import<string>;
        import<string_view>;

        export std::string to_roman(unsigned i);
        export unsigned from_roman(std::string_view roman);
        ```

    - from_roman.cpp

        ```cpp
        //from_roman.cpp
        module roman;

        unsigned from_roman(char c)
        {
            switch (c)
            {
                case 'I': return 1;
                case 'V': return 5;
                case 'X': return 10;
                case 'L': return 50;
                case 'C': return 100;
                case 'D': return 500;
                case 'M': return 1000;
                default: return 0;
            }
        }

        unsigned from_roman(std::string_view roman)
        {
            unsigned result{};
            const auto n{roman.length()};
            for (size_t i{};i < n;++i)
            {
                const auto j{ from_roman(roman[i]) };
                if (i + 1 == n || j >= from_roman(roman[i + 1]))
                    result += j;
                else
                    result -= j;
            }

            return result;
        }
        ```

    - to_roman.cpp

        ```cpp
        //to_roman.cpp
        module roman;

        std::string to_roman(unsigned i)
        {
            if (i > 3999) return{ };
            static const std::string ms[]{ "","M","MM","MMM" };
            static const std::string cds[]
            { "","C","CC","CCC","CD","D","DC","DCC","DCCC","CM" };
            static const std::string xls[]
            { "","X","XX","XXX","XL","L","LX","LXX","LXXX","XC" };
            static const std::string ivs[]
            { "","I","II","III","IV","V","VI","VII","VIII","IX" };

            return ms[i / 1000] + cds[(i % 1000) / 100] + xls[(i % 100) / 10] 
            + ivs[i % 10];
        }
        ```

    - 上面程序运行结果如下：

        ---

        ```cpp
        MMXX in Arabic numerals is 2020
        1234 in Roman numerals is MCCXXXIV
        This consists of 8 numerals
        567 in Roman numerals is DLXVII
        1234 in Roman numerals is MCCXXXIV
        ```

        ---

3. 在通过局部声明或者import声明导入的模块接口文件(如roman.ixx)中可达的任何声明，在导入该模块的文件中也是可达的，如上例的Ex11_03.cpp中导入roman.ixx，则Ex11_03.cpp也可达roman.ixx中的声明
4. 可达类定义的成员的名称是可见的
5. 声明的可达性隐式地传递给模块的所有使用者（可能是间接使用），但声明的名称的可见性则不会传递，见下例：

    ```cpp
    //base.ixx
    export module base;

    export void hello_base()
    {
        std::cout << "Hello from base module!\n";
    }

    //middle.ixx
    export module middle;

    import base;  // 导入base模块，但不export

    export void hello_middle() 
    {
        hello_base();  // middle内部可以使用base的函数
        std::cout << "Hello from middle module!\n";
    }

    //main.cpp
    import middle;

    int main() 
    {
        // 可达性传递：middle的使用者也能"间接"使用base
        hello_middle();  // ✅ 可以调用（middle导出了这个函数）
        
        // 可见性不传递：base的名称对main不可见
        hello_base();    // ❌ 编译错误！虽然可达（通过middle），但不可见
        
        // 如果想使用base的函数，必须显式导入
        // import base;  // 取消注释后下面就可以用了
        // hello_base(); // ✅ 现在可见了
    }

    /*
    关键说明
    1. 可达性传递：
        - main导入middle
        - middle导入base
        - 因此base中的声明对main也是可达的（理论上可以使用）
    2. 可见性不传递：
        - middle虽然能看到hello_base，但没有将其导出
        - 所以hello_base这个名称对main是不可见的
        - main必须显式import base;才能直接使用hello_base
    */
    ```

### 11.1.5 导出import声明

1. 与模块接口文件中的大部分声明一样，也可以在import声明的前面添加export。导入一个模块的文件也会隐式继续该模块中导入的所有import声明
2. 不应该系统地导出一个模块中使用的所有模块导入
3. 导出import声明还有一个合理的理由：创建所谓的子模块

### 11.1.6 管理较大的模块

**1.模拟子模块**  

- 开头案例

    ```cpp
    //roman.ixx
    export module roman;
    //再次export，是为了统一接口，只要import roman;就可以使用roman.from和roman.to的实体了
    export import roman.from;
    export import roman.to;

    //roman.from.ixx
    export module roman.from;
    import <string_view>;
    export unsigned int from_roman(std::string_view roman);

    //roman.to.ixx
    export module roman.to;
    import <string>;
    export std::string to_roman(unsigned int i);
    ```

- roman.from和roman.to就是模块名称，和其他模块名称没有区别，如上例，可以单独import roman、roman.from、
roman.to，import roman就相当于同时import后两者了

**2.模块分区**  

子模块与分区之间的关键区别是，应用程序的其余部分可以单独导入子模块，而分区仅在模块内可见。

- **模块实现分区**

    - Ex11_04案例

        ```cpp
        //Ex11_04.cpp
        import <iostream>;
        import <string>;
        import roman;

        int main()
        {
            std::cout << "1234 in Roman numerals is " << to_roman(1234) << std::endl;
            std::cout << "MMXX in Arabic numerals is " << from_roman("MMXX") 
            << std::endl;
            std::cin.get();
        }
        ```

        ```cpp
        //roman.ixx
        export module roman;
        import <string>;
        import <string_view>;

        export std::string to_roman(unsigned int i);
        export unsigned int from_roman(std::string_view roman);
        ```

        ```cpp
        //from_roman.cpp
        module roman;
        import :internals;

        unsigned int from_roman(std::string_view roman)
        {
            unsigned int result{};
            for (size_t i{}, n{ roman.length() }; i < n; ++i)
            {
                const auto j{ from_roman(roman[i]) };
                if (i + 1 == n || j >= from_roman(roman[i + 1])) 
                    result += j; 
                else 
                    result -= j;
            }
            return result;
        }
        ```

        ```cpp
        //to_roman.cpp
        module roman;

        std::string to_roman(unsigned int i)
        {
            if (i > 3999) return {};
            static const std::string ms[]{ "","M","MM","MMM" };
            static const std::string cds[]
            { "","C","CC","CCC","CD","D","DC","DCC","DCCC","CM" };
            static const std::string xls[]
            { "","X","XX","XXX","XL","L","LX","LXX","LXXX","XC" };
            static const std::string ivs[]
            { "","I","II","III","IV","V","VI","VII","VIII","IX" };
            return ms[i / 1000] + cds[(i % 1000) / 100] + xls[(i % 100) / 10] 
            + ivs[i % 10];
        }
        ```

        ```cpp
        //roman-internals.cpp
        module roman:internals;

        unsigned int from_roman(char c)
        {
            switch (c)
            {
                case 'I': return 1;    case 'V': return 5;   case 'X': return 10;
                case 'L': return 50;   case 'C': return 100; case 'D': return 500;
                case 'M': return 1000; default:  return 0;
            }
        }
        ```

        上面程序运行结果如下：

        ---

        ```cpp
        1234 in Roman numerals is MCCXXXIV
        MMXX in Arabic numerals is 2020 
        ```

        ---

    - 模块分区文件的module声明与其他任何模块文件的module声明相似，只不过会在模块名称的后面添加冒号，然后跟上分区的名称
    - 模块分区声明中没有`export`关键字，因此不允许它导出任何实体
    - 只能在相同模块的其他文件中导入模块分区，并且只能使用`import :partition_name;`进行导入

- **模块接口分区**

    - 模块接口有时候也可能变得太大，应该被进一步拆分为多个部分。此时，可以使用模块接口分区
    - Ex11_05案例

        ```cpp
        //Ex11_05.cpp
        import <iostream>;
        import<string>;
        import roman;

        int main()
        {
            std::cout << "1234 in Roman numerals is " << to_roman(1234) << std::endl;
            std::cout << "MMXX in Arabic numerals is " << from_roman("MMXX") 
            << std::endl;
        }
        ```

        ```cpp
        //roman.ixx
        export module roman;

        export import :to;
        export import :from;
        ```

        ```cpp
        //roman-to.ixx
        export module roman:to;
        import <string>;

        export std::string to_roman(unsigned i)
        {
            if (i > 3999) return {};
            static const std::string ms[]{ "","M","MM","MMM" };
            static const std::string cds[]
            { "","C","CC","CCC","CD","D","DC","DCC","DCCC","CM" };
            static const std::string xls[]
            { "","X","XX","XXX","XL","L","LX","LXX","LXXX","XC" };
            static const std::string ivs[]
            { "","I","II","III","IV","V","VI","VII","VIII","IX" };
            return ms[i / 1000] + cds[(i % 1000) / 100] + xls[(i % 100) / 10] 
            + ivs[i % 10];
        }
        ```

        ```cpp
        //roman-internals.cpp
        module roman:internals;

        unsigned int from_roman(char c)
        {
            switch (c)
            {
                case 'I': return 1;    case 'V': return 5;   case 'X': return 10;
                case 'L': return 50;   case 'C': return 100; case 'D': return 500;
                case 'M': return 1000; default:  return 0;
            }
        }
        ```

        ```cpp
        //roman-from.ixx
        export module roman:from;
        import<string_view>;

        export unsigned from_roman(std::string_view roman);
        ```

        ```cpp
        //from_roman.cpp
        module roman;
        import :internals;

        unsigned int from_roman(std::string_view roman)
        {
            unsigned int result{};
            for (size_t i{}, n{ roman.length() }; i < n; ++i)
            {
                const auto j{ from_roman(roman[i]) }; 
                if (i + 1 == n || j >= from_roman(roman[i + 1]))
                    result += j;
                else
                    result -= j;
            }
            return result;
        }
        ```

        上面程序运行结果如下：

        ---

        ```cpp
        1234 in Roman numerals is MCCXXXIV
        MMXX in Arabic numerals is 2020 
        ```

        ---

        ```cpp
        重要知识点：
        ┌─────────────────────────────────────────────────────────┐
        │                      导出分区                            │
        │    export module roman:to;                              │
        │                                                         │
        │    ┌─────────────────┐                                  │
        │    │ 模块内部可见     │ ← import :to;                    │
        │    │ 可被重新导出     │ ← export import :to;             │
        │    └─────────────────┘                                  │
        └─────────────────────────────────────────────────────────┘

        ┌─────────────────────────────────────────────────────────┐
        │                    非导出分区                            │
        │    module roman:to;  ← 去掉 export                      │
        │                                                         │
        │    ┌─────────────────┐                                  │
        │    │ 模块内部可见     │ ← import :to;                    │
        │    │ 不可被重新导出   │ × export import :to; 失败         │
        │    └─────────────────┘                                  │
        └─────────────────────────────────────────────────────────┘

        关键要点：

        1. 所有分区的实体对模块内部都是可见的（通过 import :name;）
        2. export module 的唯一作用是允许主模块通过 export import 重新导出其内容
        3. 非导出分区的实体虽然在模块内部可见，但永远无法被导出到模块外部，如internals分区
        ```

    - 模块分区实现文件不能与模块分区同名，但可以将分区的函数实现放到普通的模块实现文件中(.cpp文件)，如上例roman:from分区声明的from_roman()函数放到from_roman.cpp文件中定义
    - 必须在模块的主模块接口中导出每个接口分区，如上例，只能在roman.ixx中导出to和from分区，然后才能使用分区中的实体

### 11.1.7 全局模块片段

- 除了来自C标准库的那些头文件（`<cmath>`、`<cctype>`等；它们的名称都带有字母c作为前缀）以外，C++标准库中的所有头文件都是可以导入的
- 一般来说，在模块文件中，应该把所有`#include`指令放到所谓的全局模块片段中

    ```cpp
    module; //全局模块片段开始
    #include<cmath> //可以有任意数量的非模块化代码的#include（无分号！）

    /*export*/  module my Module;   //模块权限开始

    import <string>;    //可以有任意数量的模块化代码的import
    import myOtherModule;

    //使用<cmath>、<string>和myOtherModule中实体的模块代码...
    ```

- 全局模块版本总是出现在模块文件的module声明之前
- 全局模块片段自身只能包含预处理器指令，如`#include`和`#define`，而不能包含其他内容

## 11.2 名称空间

使用名称空间防止名称冲突十分重要：

- 多人开发一个应用程序时
- 应用程序包含各种第三方C++库代码时

### 11.2.1 全局名称空间

- 实体：变量、函数和类等
- 没有放在自定义的名称空间的实体就默认放在全局名称空间
- 要显式访问全局名称空间的实体，就使用"::"作用域解析运算符，注意，是不带左操作数的!

    ```cpp
    #include <iostream>

    int global_var = 10;

    int main()
    {
        int global_var = 5; // 局部变量，和全局的同名

        // 直接用，访问的是局部的 global_var
        std::cout << global_var << std::endl; // 输出：5

        // 用 :: 前缀，访问的是全局的 global_var
        std::cout << ::global_var << std::endl; // 输出：10
    }
    ```

### 11.2.2 定义名称空间

1. 名称空间定义形式如下(注意，名称空间定义的大括号后面没有分号)：

    ```cpp
    namespace mySpace{
        int var{};
        void func();
        ......
    }
    ```

2. main()函数必须放在全局名称空间中
3. 可以在不同的位置或不同的源文件中定义相同名称的名称空间，它们属于同一个名称空间
4. 通常会把名称空间的声明放在头文件（.h）中，然后在多个源文件中包含这个头文件

    ```cpp
    // Ex11_06.cpp
    // Defining and using a namespace
    #include <iostream>
    #include <numbers>

    namespace math
    {
        const double sqrt2{1.414213562373095}; // the square root of 2
        auto square(const auto &x) { return x * x; }
        auto pow4(const auto &x){return square(square(x));}
        // 这里square就在本名称空间内，不需要"math::"限定
    } // namespace math

    int main()
    {
        std::cout << "math::sqrt2 has the value " << math::sqrt2 << std::endl;
        std::cout << "This should be 0: " << (math::sqrt2 - std::numbers::sqrt2)
                << std::endl;
        std::cout << "This should be 2: " << math::square(math::sqrt2) << std::endl;
        std::cout << "pow4(math::sqrt2) = " << math::pow4(math::sqrt2)
                << std::endl; // 这里pow4与sqrt2不在名称空间内，必须要"math::"限定
    }
    ```

    上面程序运行结果如下：

    ---

    ```cpp
    math::sqrt2 has the value 1.41421
    This should be 0: -2.22045e-16
    This should be 2: 2
    pow4(math::sqrt2) = 4
    ```

    ---

### 11.2.3 嵌套名称空间

两个嵌套方式：

- 直接嵌套

    ```cpp
    namespace outer
    {
        ...;
        namespace inter
        {
            ...;
        }
    }
    ```

- 简洁嵌套

    ```cpp
    namespace outer
    {
        ...;
    }

    namespace outer::inter//outer名称空间位于全局名称空间，前面不需要"::"限定。但也可以用"::"，更明确
    {
        ...;
    }
    ```

### 11.2.4 名称空间和模块

- 尽管没必要这么做，但使模块的名称和名称空间的名称保持一致通常是一个好主意
- 名称空间和模块在C++中是完全不相关的
    - 案例Ex11_06A
        - Ex11_06A.cpp

            ```cpp
            //Ex11_06A.cpp
            import<iostream>;
            import<numbers>;
            import squaring;

            int main()
            {
                std::cout << "math::sqrt2 has the value " << math::sqrt2 << std::endl;
                std::cout << "This should be 0: " 
                            << math::sqrt2 - std::numbers::sqrt2 << std::endl;
                std::cout << "This should be 2: " << math::square(math::sqrt2) 
                            << std::endl;

                std::cin.get();
            }
            ```

        - squaring.ixx

            ```cpp
            // squaring.ixx
            export module squaring;

            namespace math
            {
                export const double sqrt2{1.4142134562373095};
                // the square root of 2
                export auto square(const auto &x) { return x * x; }
                export auto pow4(const auto &x) { return square(square(x)); }
            } // namespace math
            ```

            上面程序运行结果如下：

            ---

            ```cpp
            math::sqrt2 has the value 1.41421
            This should be 0: -1.06136e-07
            This should be 2: 2 
            ```

            ---

    - 案例Ex11_06B
        - Ex11_06B.cpp

            ```cpp
            // Ex11_06B.cpp
            import <iostream>;
            import <numbers>;
            import squaring;

            int main()
            {
                std::cout << "math::sqrt2 has the value " << math::sqrt2 << std::endl;
                std::cout << "This should be 0: " << math::sqrt2 - std::numbers::sqrt2
                        << std::endl;
                std::cout << "This should be 2: " << math::square(math::sqrt2) 
                << std::endl;

                std::cin.get();
            }
            ```

        - squaring.ixx

            ```cpp
            //squaring.ixx
            export module squaring;

            export namespace math
            {
                const double sqrt2{ 1.4142134562373095 };
                auto square(const auto& x) { return x * x; }
                auto pow4(const auto& x) { return square(square(x)); }
            }
            ```

            上面程序运行结果如下：

            ---

            ```cpp
            math::sqrt2 has the value 1.41421
            This should be 0: -1.06136e-07 
            This should be 2: 2 
            ```

            ---

### 11.2.5 函数和名称空间

1. 要想让函数在名称空间内存在，将函数原型添加到名称空间块中就够了
    - 案例Ex11_07
        - Ex11_07.cpp

            ```cpp
            //Ex11_07.cpp
            import <iostream>;
            import math;

            int main()
            {
                const double values[]{ 10,2,1,8,3,7,4,5,6,9 };
                std::cout << "Arithmetic mean: " 
                        << math::averages::arithmetic_mean(values) << std::endl;
                std::cout << "Geometric mean: " 
                        << math::averages::geometric_mean(values) << std::endl;
                std::cout << "Root mean square: " << math::averages::rms(values)
                        << std::endl;
                std::cout << "Median: " << math::averages::median(values) << std::endl;

                std::cin.get();
            }
            ```

        - math.ixx

            ```cpp
            // math.ixx
            export module math;

            import <span>;

            export namespace math
            {
                auto square(const auto &x) { return x * x; }
                //函数模板，不会自动导出，如果要导出，需要前面加export显式导出

                namespace averages
                {
                    double arithmetic_mean(std::span<const double> data); //普通函数，会自动导出
                    double geometric_mean(std::span<const double> data);
                    double rms(std::span<const double> data);
                    double median(std::span<const double> data);
                    //此处可以复习一下span的用法，已经封装了指向数据起始位置的指针和数据长度
                    //所以它天然具有引用语义，不需要再额外加 &
                } // namespace averages
            } // namespace math
            ```

        - math.cpp

            ```cpp
            //math.cpp
            module;//全局模块片段
            #include<cmath>// 用于 std::pow()、std::sqrt() 等函数
            module math;

            import <limits>;//用于 std::numeric_limits<double>::quiet_NaN()
            import<vector>;//用于 std::vector 容器

            void quicksort(std::vector<double>& data);
            //这是前向声明，因为下面在定义之前已经使用了此函数，参见第8章

            //选项1：在嵌套命名空间块中定义（紧凑语法）
            namespace math::averages
            {
                double arithmetic_mean( std::span<const double>data)
                {
                    //算术平均数是最常用的平均值，
                    //定义为所有元素的总和除以元素个数。
                    double sum{ };
                    for (auto value : data)
                        sum += value;

                    return data.empty()
                        ? std::numeric_limits<double>::quiet_NaN()//或 std::nan("")
                        : sum / data.size();
                }
            }

            //选项2：在嵌套命名空间块中定义
            namespace math
            {
                namespace averages
                {
                    double geometric_mean(std::span<const double>data)
                    {
                        //n个元素的几何平均数
                        //定义为所有n个元素乘积的n次方根
                        double product{ 1 };
                        for (auto value : data)
                            product *= value;

                        return data.empty()
                            ? std::numeric_limits<double>::quiet_NaN()
                            : std::pow(product, 1.0 / data.size());//pow()计算幂（乘方）的函数
                        //计算：product^(1/n) = ⁿ√product
                    }
                }
            }

            //选项3：使用完全限定函数名定义
            double math::averages::rms(std::span<const double>data)
            {
                //RMS（均方根）定义为
                //元素平方的算术平均值的平方根。
                double sum_squares{};
                for (auto value : data)
                    sum_squares += square(value);

                return data.empty()
                    ? std::numeric_limits<double>::quiet_NaN()//或 std::nan("")
                    : std::sqrt(sum_squares / data.size());
            }

            //选项4：在外层命名空间块中使用限定名定义
            namespace math
            {
                double averages::median(std::span<const double>data)
                {
                    //奇数个元素的中位数是
                    //这些元素排序后出现在中间位置的值。
                    //偶数个元素的中位数通常
                    //定义为排序范围内两个中间元素的平均值。

                    //我们不能直接对data span排序，因为其元素是const的。
                    //因此，我们首先复制const输入数据以便能够排序
                    std::vector<double>sorted;

                    //使用范围for循环复制输入数据。
                    //有关复制数据范围的内置方法，请参见第20章。
                    for (auto value : data)
                        sorted.push_back(value);

                    //有关（部分）排序数据的内置方法，请参见第20章
                    quicksort(sorted);

                    const size_t mid = data.size() / 2;
                    return data.empty() ? std::numeric_limits<double>::quiet_NaN()
                    //或 std::nan
                        : data.size() % 2 == 1 ? sorted[mid]
                        : (sorted[mid - 1] + sorted[mid]) / 2;
                }
            }

            void quicksort(std::vector<double>& data, size_t start, rsize_t end);
            void quicksort(std::vector<double>& data)
            {
                if (!data.empty())
                    quicksort(data, 0, data.size() - 1);
            }

            void quicksort(std::vector<double>& data, rsize_t start, rsize_t end)
            {
                //对于2个或更多元素，起始索引必须小于结束索引
                if (!(start < end))
                    return;

                //选择中间值作为分区基准，
                //并将其移动到当前范围的前端
                std::swap(data[start], data[(start + end) / 2]);

                //将所有其他值与索引start处的选定值进行比较
                size_t current{ start };
                for (rsize_t i{ start + 1 }; i <= end; ++i)
                {
                    if (data[i] < data[start])//该值是否小于选定值？
                        std::swap(data[++current], data[i]);
                        //是，因此交换到左侧
                }

                std::swap(data[start], data[current]);
                //交换选定值和最后交换的值

                if (current > start)quicksort(data, start, current - 1);
                //如果存在左子集，则排序
                if (end > current + 1)quicksort(data, current + 1, end);
                //如果存在右子集，则排序
            }
            ```

        - 上面程序运行结果如下：

            ---

            ```cpp
            Arithmetic mean: 5.5
            Geometric mean: 4.52873
            Root mean square: 6.20484
            Median: 5.5 
            ```

            ---

2. 要导出函数模板（如上例square()），其**定义**必须是模块接口的一部分，定义不能放到模块实现文件中
3. export namespace math{}中的函数模板如果要导出，前面得加export显式导出。普通函数在里面已经默认自动导出

### 11.2.6 using使用指令和声明

- 使用using指令可以引用一个名称空间中的任意名称
- 声明或指令会一直应用到包含它们的块的末尾
- 应尽量少使用using指令和声明，并且尽量总是局部使用它们
- 案例Ex11_08
    - Ex11_08.cpp

        ```cpp
        //Ex11_08.cpp
        // 注意：示例在正文中没有命名
        import<iostream>;
        import squaring;

        /* 使得 math 命名空间中的名称在本地可用 */
        // 注意：正文使用 hypot()，但在 Visual Studio 中这会与 <cmath> 的 hypot() 函数冲突导致二义性
        auto hypotenuse(const auto& x, const auto& y)
        {
            using namespace math;
        // 或者：
        // using math::square;
        // using math::sqrt; /* 当然，这与 using std::sqrt; 相同 */
            return sqrt(square(x) + square(y));//此处直接使用sqrt,不用再std::开头
        }

        int main()
        {
            std::cout << "math::sqrt2 has the value " << math::sqrt2 << std::endl;
            std::cout << "This should be 0: " 
                    << math::sqrt2 - std::numbers::sqrt2 << std::endl;
            /* 其实math::sqrt2和std::numbers::sqrt2指向同一个实体，值相同 */
            std::cout << "This should be 2: " << math::square(math::sqrt2) << std::endl;
            std::cout << "This should be 5: " << hypotenuse(3, 4) << std::endl;

            std::cin.get();
        }
        ```

    - squaring.ixx

        ```cpp
        //squaring.ixx
        module;//Start of the blobal module fragment (for #include directives)
        // 为了使用 std::sqrt()
        #include<cmath>
        export module squaring;
        import <numbers>;//For std::numbers::sqrt2

        /* 使用 using 声明从 math 命名空间重新导出两个已有实体 */
        export namespace math// 导出所有嵌套声明
        {
        using std::numbers::sqrt2;// 切勿写成 'using std::sqrt();' 或 'using std::sqrt(double);'！
        using std::sqrt;// 切勿写成 'using std::sqrt();' 或 'using std::sqrt(double);'！
        /* 此处using std::sqrt 在其它import math 的地方就可以直接写sqrt，而不用写std::sqrt了 */
        auto square(const auto& x) { return x * x; }// 计算平方
        auto pow4(const auto& x) { return square(square(x)); }// 计算四次方
        }
        ```

    - 上面程序运行结果如下：

        ---

        ```cpp
        math::sqrt2 has the value 1.41421
        This should be 0: 0
        This should be 2: 2
        This should be 5: 5  
        ```

        ---

### 11.2.7 名称空间别名

一般形式：`namespace alias_name = original_namespace_name;`

```cpp
namespace v2 = my_excessively_very_long_namespace_name_version2;
namespace MyGroup = MyCompany::MyModule::MySubmodule::MyGrouping;

int fancyNumber{ v2::doFancyComputation(MyGroup::queryUserInput()) };
```

## 11.3 本章小结

## 11.4 练习

1. 第1题
    - Exer11_01.cpp

        ```cpp
        /*************************第11章_练习_第1题************************
        截止到现在，Ex8_17.cpp是我们看过的一个较大程序。提取该程序的所有函数，
        把它们放到只有一个文件的words模块中，并让所有的函数都包含在words名称
        空间中。该模块只应该导出与main()函数相关的那些函数，而main()函数基本上
        应该保持不变。其他函数，特别是sort()的三参数重载，只是为支持导出的函数
        而存在的。
        *****************************************************************/
        // 将 Ex8_17.cpp 中的所有函数（而非书中所说的 Ex8_18.cpp）
        //  移到 words 模块中，只导出 main() 函数使用的函数。
        import <string>;
        import <iostream>;
        import words;

        int main()
        {
            words::Words the_words;// 重命名以避免与 words 命名空间冲突！
            std::string text;// 要排序的字符串
            const auto separators{" ,.!?\"\n"}; // 单词分隔符

            // 从键盘读取要处理的字符串
            std::cout << "Enter a string terminated by *:" << std::endl;
            std::getline(std::cin, text, '*');

            words::extract_words(the_words, text, separators);
            if (the_words.empty())
            {
                std::cout << "No words in text." << std::endl;
                return 0;
            }

            words::sort(the_words);  // 对单词进行排序
            words::show_words(the_words); // 输出单词

            std::cin.get();
        }
        ```

    - words.ixx

        ```cpp
        // words.ixx
        export module words;

        import <iostream>;
        import <format>;
        import <memory>;
        import <string>;
        import <vector>;

        export namespace words
        {
        using Words = std::vector<std::shared_ptr<std::string>>;

        void sort(Words &words);
        void extract_words(Words &words, const std::string &text,
                        const std::string &separators);
        void show_words(const Words &words);
        } // namespace words

        namespace words
        {
        size_t max_word_length(const Words &words);
        }

        void words::extract_words(Words &words, const std::string &text,
                                const std::string &separators)
        {
            size_t start{text.find_first_not_of(separators)}; // 第一个单词的起始索引

            while (start != std::string::npos)
            {
                size_t end{
                    text.find_first_of(separators, start + 1)}; // 查找单词的结束位置
                if (end == std::string::npos)                   // 找到分隔符了吗？
                    end = text.length(); // 是的，所以设置为文本末尾
                words.push_back(
                    std::make_shared<std::string>(text.substr(start, end - start)));
                start = text.find_first_not_of(separators,
                                            end + 1); // 查找下一个单词的起始位置
            }
        }

        /* word::sort(Words&) 的附加辅助函数 */
        namespace words
        {
        void swap(Words &words, size_t first, size_t second)
        {
            auto temp{words[first]};
            words[first] = words[second];
            words[second] = temp;
        }

        void sort(Words &words, size_t start, size_t end);
        } // namespace words

        // 按升序对字符串排序

        void words::sort(Words &words)
        {
            if (!words.empty())
                sort(words, 0, words.size() - 1);
        }

        void words::sort(Words &words, size_t start, size_t end)
        {
            // 对于2个或更多元素，起始索引必须小于结束索引
            if (!(start < end))
                return;

            // 选择中间位置来分割集合
            swap(words, start, (start + end) / 2); // 将中间位置与起始位置交换

            // 将单词与选中的单词进行比较
            size_t current{start};
            for (size_t i{start + 1}; i <= end; i++)
            {
                if (*words[i] < *words[start]) // 该单词是否小于选中的单词？
                    swap(words, ++current, i); // 是的，所以交换到左边
            }

            swap(words, start, current); // 交换选中的单词和最后交换的单词

            if (current > start)
                sort(words, start, current - 1); // 如果存在左子集则排序
            if (end > current + 1)
                sort(words, current + 1, end); // 如果存在右子集则排序
        }

        size_t words::max_word_length(const Words &words)
        {
            size_t max{};
            for (auto &pword : words)
                if (max < pword->length())
                    max = pword->length();
            return max;
        }

        void words::show_words(const Words &words)
        {
            const size_t field_width{max_word_length(words) + 1};
            const size_t words_per_line{8};
            std::cout << std::format("{:{}}", *words[0], field_width); // 输出第一个单词

            size_t words_in_line{}; // 当前行的单词数
            for (size_t i{1}; i < words.size(); ++i)
            {
                // 当初始字母改变或每行达到8个单词时输出换行
                if ((*words[i])[0] != (*words[i - 1])[0] ||
                    ++words_in_line == words_per_line)
                {
                    words_in_line = 0;
                    std::cout << std::endl;
                }
                std::cout << std::format("{:{}}", *words[i],
                                        field_width); // 输出一个单词
            }
            std::cout << std::endl;
        }
        ```

    - 上面程序运行结果如下（因行宽MD报错原因，每行8个单词硬回车变成了6个）：

        ---

        ```cpp
        Enter a string terminated by *:
        The old lighthouse stood on the cliff, its beam a silent guardian 
        against the raging sea. For decades, it had witnessed storms that 
        could splinter ships and fogs that could swallow the moon. The 
        keeper, a man with salt-crusted skin and weary eyes, maintained the 
        flame with a ritual precision. He knew every groan of the ancient 
        structure, every whisper of the wind. One night, the light flickered
        and died, plunging the world into absolute blackness. He climbed 
        the spiral stairs, his heart pounding against the rising tide of 
        panic, and found a single, stubborn spark waiting to be reborn. *
        For
        He           He
        One
        The          The          
        a            a            a            a            absolute     
        against      against      ancient      
        and          and          and          and          
        be           beam         blackness    
        cliff        climbed      could        could        
        decades      died         
        every        every        eyes         
        flame        flickered    fogs         found        
        groan        guardian     
        had          heart        his          
        into         it           its          
        keeper       knew         
        light        lighthouse   
        maintained   man          moon         
        night        
        of           of           of           old          on           
        panic        plunging     pounding     precision    
        raging       reborn       rising       ritual       
        salt-crusted sea          ships        silent       single       
        skin         spark        spiral       
        splinter     stairs       stood        storms       structure    
        stubborn     swallow      
        that         that         the          the          the          
        the          the          the          
        the          the          the          the          tide         
        to           
        waiting      weary        whisper      wind         with         
        with         witnessed    world 
        ```

        ---

2. 第2题
    - Exer11_02.cpp

        ```cpp
        // Exer11_02.cpp
        /*************************第11章_练习_第2题************************
        对于第1题的解决方案，通过把所有函数定义移动到一个实现文件中，将模块的接口
        与实现分开。在实现文件中，不要使用名称空间块。在练习时，将所有未导出的
        函数从words名称空间中移出来，放到全局名称空间内，然后想清楚在导出单参数
        sort()函数中如何仍然能够调用三参数的sort()函数。
        *****************************************************************/
        import <string>;
        import <iostream>;
        import words;

        int main()
        {
            words::Words the_words;
            std::string text;
            const auto separators{" ,.!?\"\n"};
            std::cout << "Enter a string terminated by *:" << std::endl;
            std::getline(std::cin, text, '*');

            words::extract_words(the_words, text, separators);
            if (the_words.empty())
            {
                std::cout << "No words in text." << std::endl;
                return 0;
            }

            words::sort(the_words);
            words::show_words(the_words);
        }
        ```

    - words.ixx

        ```cpp
        //words.ixx
        export module words;

        import<memory>;
        import<string>;
        import<vector>;

        export namespace words
        {
            using Words = std::vector<std::shared_ptr<std::string>>;

            void sort(Words& words);
            void extract_words(Words& words, const std::string& text, 
                const std::string& separators);
            void show_words(const Words& words);
        }
        ```

    - words.cpp

        ```cpp
        //words.cpp
        module words;

        import<iostream>;
        import<format>;

        size_t max_word_length(const words::Words& words);

        void words::extract_words(Words& words, const std::string& text, 
            const std::string& separators)
        {
            size_t start{ text.find_first_not_of(separators) };//Start index of 
                first word

            while (start != std::string::npos)
            {
                size_t end{ text.find_first_of(separators,start + 1) };
                //Find end of a word
                if (end == std::string::npos)
                    end = text.length();
                words.push_back(std::make_shared<std::string>
                    (text.substr(start, end - start)));
                start = text.find_first_not_of(separators, end + 1);
                //Find start next word
            }
        }

        void swap(words::Words& words, size_t first, size_t second)
        {
            auto temp{ words[first] };
            words[first] = words[second];
            words[second] = temp;
        }

        void sort(words::Words& words, size_t start, size_t end);

        void words::sort(Words& words)
        {
            if (!words.empty())
                ::sort(words, 0, words.size() - 1);
        }

        void sort(words::Words& words, size_t start, size_t end)
        {
            if (!(start < end))
                return;

            swap(words, start, (start + end) / 2);

            size_t current{ start };
            for (size_t i{ start + 1 };i <= end;i++)
            {
                if (*words[i] < *words[start])
                    swap(words, ++current, i);
            }

            swap(words, start, current);

            if (current > start) sort(words, start, current - 1);
            if (end > current + 1) sort(words, current + 1, end);
        }

        size_t max_word_length(const words::Words& words)
        {
            size_t max{};
            for (auto& pword : words)
                if (max < pword->length()) max = pword->length();
            return max;
        }

        void words::show_words(const Words& words)
        {
            const size_t field_width{ max_word_length(words) + 1 };
            const size_t words_per_line{ 8 };
            std::cout << std::format("{:{}}", *words[0], field_width);

            size_t words_in_line{};
            for (size_t i{1};i < words.size();++i)
            {
                if ((*words[i])[0] != (*words[i - 1])[0] || ++words_in_line == words_per_line)
                {
                    words_in_line = 0;
                    std::cout << std::endl;
                }

                std::cout << std::format("{:{}}", *words[i], field_width);
            }
            std::cout  << std::endl;
        }
        ```

    - 上面程序运行结果如下（因MD文件行宽80报错，部分单词有硬回车换行）：

        ---

        ```cpp
        Enter a string terminated by *:
        The old lighthouse stood on the cliff, its beam a silent guardian 
        against the raging sea. For decades, it had witnessed storms that could 
        splinter ships and fogs that could swallow the moon. The keeper, a man 
        with salt-crusted skin and weary eyes, maintained the flame with a 
        ritual precision. He knew every groan of the ancient structure, every 
        whisper of the wind. One night, the light flickered and died, plunging 
        the world into absolute blackness. He climbed the spiral stairs, his 
        heart pounding against the rising tide of panic, and found a single, 
        stubborn spark waiting to be reborn. *
        For
        He           He
        One
        The          The          
        a            a            a            a            absolute     
        against      against      ancient      
        and          and          and          and          
        be           beam         blackness    
        cliff        climbed      could        could        
        decades      died         
        every        every        eyes         
        flame        flickered    fogs         found        
        groan        guardian     
        had          heart        his          
        into         it           its          
        keeper       knew         
        light        lighthouse   
        maintained   man          moon         
        night        
        of           of           of           old          on           
        panic        plunging     pounding     precision    
        raging       reborn       rising       ritual       
        salt-crusted sea          ships        silent       single       
        skin         spark        spiral       
        splinter     stairs       stood        storms       structure    
        stubborn     swallow      
        that         that         the          the          the          
        the          the          the          
        the          the          the          the          tide         
        to           
        waiting      weary        whisper      wind         with         
        with         witnessed    world 
        ```

        ---

3. 第3题
    - Exer11_03.cpp

        ```cpp
        // Exer11_03.cpp
        /*************************第11章_练习_第3题************************
        将第2题的words模块拆分为两个恰当命名的子模块：一个子模块包含所有排序
        功能，另一个子模块包含剩余的实用工具（程序员常用utils表示实用工具）。
        另外，将函数放到嵌套的名称空间中，其名称与子模块的名称对应。
        *****************************************************************/
        import words;
        import <string>;
        import <iostream>;

        int main()
        {
            words::Words the_words;
            std::string text;
            const auto separators{" ,.!?\"\n"};

            std::cout << "Enter a string terminated by *:" << std::endl;
            getline(std::cin, text, '*');

            words::utils::extract_words(the_words, text, separators);
            if (the_words.empty())
            {
                std::cout << "No words in text." << std::endl;
                return 0;
            }

            words::sorting::sort(the_words);
            words::utils::show_words(the_words);
        }
        ```

    - words.ixx

        ```cpp
        //words.ixx
        export module words;

        export import words.sorting;
        export import words.utils;
        ```

    - words.sorting.ixx

        ```cpp
        //words.sorting.ixx
        export module words.sorting;

        import<memory>;
        import<string>;
        import<vector>;

        export namespace words
        {
            using Words = std::vector<std::shared_ptr<std::string>>;

            namespace sorting
            {
                void sort(Words& words);
            }
        }
        ```

    - words.sorting.cpp

        ```cpp
        //words.sorting.cpp
        module words.sorting;

        void swap(words::Words& words, size_t first, size_t second)
        {
            auto temp{ words[first] };
            words[first] = words[second];
            words[second] = temp;
        }

        void sort(words::Words& words, size_t start, size_t end);

        void words::sorting::sort(Words& words)
        {
            if (!words.empty())
                ::sort(words, 0, words.size() - 1);
        }

        void sort(words::Words& words, size_t start, size_t end)
        {
            if (!(start < end))
                return;

            swap(words, start, (start + end) / 2); 

            size_t current{ start };
            for (size_t i{ start + 1 }; i <= end; i++)
            {
                if (*words[i] < *words[start]) 
                    swap(words, ++current, i); 
            }

            swap(words, start, current);  

            if (current > start) sort(words, start, current - 1); 
            if (end > current + 1) sort(words, current + 1, end); 
        }
        ```

    - words.utils.ixx

        ```cpp
        //words.utils.ixx
        export module words.utils;

        import<memory>;
        import<string>;
        import<vector>;

        namespace words
        {
            export using Words = std::vector<std::shared_ptr<std::string>>;

        }

        export namespace words::utils
        {
            void extract_words(Words& words, const std::string& text, 
            const std::string& separators);
            void show_words(const Words& words);
        }
        ```

    - words.utils.cpp

        ```cpp
        // words.utils.cpp
        export module words.utils;

        import <memory>;
        import <string>;
        import <vector>;

        namespace words
        {
        export using Words = std::vector<std::shared_ptr<std::string>>;

        }

        export namespace words::utils
        {
        void extract_words(Words &words, const std::string &text,
                        const std::string &separators);
        void show_words(const Words &words);
        } // namespace words::utils
        module words.utils;

        import <iostream>;
        import <format>;

        size_t max_word_length(const words::Words &words)
        {
            size_t max{};
            for (auto &pword : words)
                if (max < pword->length())
                    max = pword->length();
            return max;
        }

        void words::utils::extract_words(Words &words, const std::string &text,
                                        const std::string &separators)
        {
            size_t start{text.find_first_not_of(separators)};

            while (start != std::string::npos)
            {
                size_t end{text.find_first_of(separators, start + 1)};
                if (end == std::string::npos)
                    end = text.length();
                words.push_back(
                    std::make_shared<std::string>(text.substr(start, end - start)));
                start = text.find_first_not_of(separators, end + 1);
            }
        }

        void words::utils::show_words(const Words &words)
        {
            const size_t field_width{max_word_length(words) + 1};
            const size_t words_per_line{8};
            std::cout << std::format("{:{}}", *words[0], field_width);

            size_t words_in_line{};
            for (size_t i{1}; i < words.size(); ++i)
            {
                if ((*words[i])[0] != (*words[i - 1])[0] ||
                    ++words_in_line == words_per_line)
                {
                    words_in_line = 0;
                    std::cout << std::endl;
                }
                std::cout << std::format("{:{}}", *words[i], field_width);
            }
            std::cout << std::endl;
        }
        ```

    - 上面程序运行结果如下：

        ---

        ```cpp
        Enter a string terminated by *:
        The old lighthouse stood on the cliff, its beam a silent guardian 
        against the raging sea. For decades, it had witnessed storms that could 
        splinter ships and fogs that could swallow the moon. The keeper, a man 
        with salt-crusted skin and weary eyes, maintained the flame with a 
        ritual precision. He knew every groan of the ancient structure, every 
        whisper of the wind. One night, the light flickered and died, plunging 
        the world into absolute blackness. He climbed the spiral stairs, his 
        heart pounding against the rising tide of panic, and found a single, 
        stubborn spark waiting to be reborn. *
        For
        He           He
        One
        The          The          
        a            a            a            a            absolute     
        against      against      ancient      
        and          and          and          and          
        be           beam         blackness    
        cliff        climbed      could        could        
        decades      died         
        every        every        eyes         
        flame        flickered    fogs         found        
        groan        guardian     
        had          heart        his          
        into         it           its          
        keeper       knew         
        light        lighthouse   
        maintained   man          moon         
        night        
        of           of           of           old          on           
        panic        plunging     pounding     precision    
        raging       reborn       rising       ritual       
        salt-crusted sea          ships        silent       single       
        skin         spark        spiral       
        splinter     stairs       stood        storms       structure    
        stubborn     swallow      
        that         that         the          the          the          
        the          the          the          
        the          the          the          the          tide         
        to           
        waiting      weary        whisper      wind         with         
        with         witnessed    world 
        ```

        ---

4. 第4题
    - Exer11_04.cpp

        ```cpp
        // Exer11_04.cpp
        /*************************第11章_练习_第4题************************
        仍然将第2题的解决方案作为起点，将swap()和max_word_length()函数移动到
        一个internals模块实现分区中。
        *****************************************************************/
        import <string>;
        import <iostream>;
        import words;

        int main()
        {
            words::Words the_words;
            std::string text;
            const auto separators{" ,.!?\"\n"};

            std::cout << "Enter a string terminated by *:" << std::endl;
            getline(std::cin, text, '*');

            words::extract_words(the_words, text, separators);
            if (the_words.empty())
            {
                std::cout << "No words in text." << std::endl;
                return 0;
            }

            words::sort(the_words);
            words::show_words(the_words);
        }
        ```

    - words.ixx

        ```cpp
        //words.ixx
        export module words;

        import<memory>;
        import<string>;
        import<vector>;

        export namespace words
        {
            using Words = std::vector<std::shared_ptr<std::string>>;

            void sort(Words& words);
            void extract_words(Words& words, const std::string& text, 
                const std::string& separators);
            void show_words(const Words& words);
        }
        ```

    - words.cpp

        ```cpp
        //words.cpp
        module words;

        import<iostream>;
        import<format>;
        import :internals;

        void words::extract_words(Words& words, const std::string& text, 
            const std::string& separators)
        {
            size_t start{ text.find_first_not_of(separators) };
            while (start != std::string::npos)
            {
                size_t end{ text.find_first_of(separators,start + 1) };
                if (end == std::string::npos)
                    end = text.length();
                words.push_back(std::make_shared<std::string>(text.substr
                    (start, end - start)));
                start = text.find_first_not_of(separators, end + 1);
            }
        }

        void sort(words::Words& words, size_t start, size_t end);

        void words::sort(Words& words)
        {
            if (!words.empty())
                ::sort(words, 0, words.size() - 1);
        }

        void sort(words::Words& words, size_t start, size_t end)
        {
            if (!(start < end))
                return;

            swap(words, start, (start + end) / 2);

            size_t current{ start };
            for (size_t i{ start + 1 }; i <= end; i++)
            {
                if (*words[i] < *words[start])
                    swap(words, ++current, i);
            }

            swap(words, start, current);

            if (current > start) sort(words, start, current - 1);
            if (end > current + 1) sort(words, current + 1, end);
        }

        void words::show_words(const Words& words)
        {
            const size_t field_width{ max_word_length(words) + 1 };
            const size_t words_per_line{ 8 };
            std::cout << std::format("{:{}}", *words[0], field_width);

            size_t words_in_line{};
            for (size_t i{ 1 }; i < words.size(); ++i)
            {
                if ((*words[i])[0] != (*words[i - 1])[0] || ++words_in_line == words_per_line)
                {
                    words_in_line = 0;
                    std::cout << std::endl;
                }
                std::cout << std::format("{:{}}", *words[i], field_width);
            }
            std::cout << std::endl;
        }
        ```

    - nternals.cpp

        ```cpp
        // nternals.cpp
        module words:internals;

        import words;

        void swap(words::Words &words, size_t first, size_t second)
        {
            auto temp{words[first]};
            words[first] = words[second];
            words[second] = temp;
        }

        size_t max_word_length(const words::Words &words)
        {
            size_t max{};
            for (auto &pword : words)
            {
                if (max < pword->length())
                    max = pword->length();
            }
            return max;
        }
        ```

    - 上面程序运行结果如下：

        ---

        ```cpp
        Enter a string terminated by *:
        The old lighthouse stood on the cliff, its beam a silent guardian 
        against the raging sea. For decades, it had witnessed storms that could 
        splinter ships and fogs that could swallow the moon. The keeper, a man 
        with salt-crusted skin and weary eyes, maintained the flame with a 
        ritual precision. He knew every groan of the ancient structure, every 
        whisper of the wind. One night, the light flickered and died, plunging 
        the world into absolute blackness. He climbed the spiral stairs, his
        heart pounding against the rising tide of panic, and found a single, 
        stubborn spark waiting to be reborn. *
        For
        He           He
        One
        The          The          
        a            a            a            a            absolute     
        against      against      ancient      
        and          and          and          and          
        be           beam         blackness    
        cliff        climbed      could        could        
        decades      died         
        every        every        eyes         
        flame        flickered    fogs         found        
        groan        guardian     
        had          heart        his          
        into         it           its          
        keeper       knew         
        light        lighthouse   
        maintained   man          moon         
        night        
        of           of           of           old          on           
        panic        plunging     pounding     precision    
        raging       reborn       rising       ritual       
        salt-crusted sea          ships        silent       single       
        skin         spark        spiral       
        splinter     stairs       stood        storms       structure    
        stubborn     swallow      
        that         that         the          the          the          
        the          the          the          
        the          the          the          the          tide         
        to           
        waiting      weary        whisper      wind         with         
        with         witnessed    world   
        ```

        ---

5. 第5题
    - Ex11_05.cpp

        ```cpp
        // Exer11_05.cpp
        /*************************第11章_练习_第5题************************
        回到第1题的解决方案，但这一次不是像第2题那样创建实现文件，而是创建多个
        接口分区文件，让每个分区文件仍然包含它们的函数定义。一个分区仍然包含所有
        排序功能，另一个分区仍然包含剩余的实用工具(utils)。另外，重用第4题的
        internals分区。
        *****************************************************************/
        import <string>;
        import <iostream>;
        import words;

        int main()
        {
            words::Words the_words;
            std::string text;
            const auto separators{" ,.!?\"\n"};

            std::cout << "Enter a string terminated by *:" << std::endl;
            getline(std::cin, text, '*');

            words::extract_words(the_words, text, separators);
            if (the_words.empty())
            {
                std::cout << "No words in text." << std::endl;
                return 0;
            }

            words::sort(the_words);
            words::show_words(the_words);
        }
        ```

    - words.ixx

        ```cpp
        //words.ixx
        export module words;

        export import :alias;
        export import :sorting;
        export import :utils;
        ```

    - utils.ixx

        ```cpp
        //utils.ixx
        export module words:utils;

        import :alias; 
        import :internals;

        import <iostream>;
        import <format>;

        export namespace words
        {
            void extract_words(Words& words, const std::string& text, 
                const std::string& separators);
            void show_words(const Words& words);
        }

        void words::extract_words(Words& words, const std::string& text, 
            const std::string& separators)
        {
            size_t start{ text.find_first_not_of(separators) };

            while (start != std::string::npos)
            {
                size_t end{ text.find_first_of(separators, start + 1) };
                if (end == std::string::npos)
                    end = text.length();
                words.push_back(std::make_shared<std::string>
                    (text.substr(start, end - start)));
                start = text.find_first_not_of(separators, end + 1);
            }
        }

        void words::show_words(const Words& words)
        {
            const size_t field_width{ max_word_length(words) + 1 };
            const size_t words_per_line{ 8 };
            std::cout << std::format("{:{}}", *words[0], field_width);

            size_t words_in_line{};
            for (size_t i{ 1 }; i < words.size(); ++i)
            {
                if ((*words[i])[0] != (*words[i - 1])[0] || ++words_in_line == words_per_line)
                {
                    words_in_line = 0;
                    std::cout << std::endl;
                }
                std::cout << std::format("{:{}}", *words[i], field_width);
            }
            std::cout << std::endl;
        }
        ```

    - sorting.ixx

        ```cpp
        //sorting.ixx
        export module words:sorting;

        import :alias;
        import:internals;

        export namespace words
        {
            void sort(Words& words);
        }

        namespace words
        {
            void sort(Words& words, size_t start, size_t end);
        }

        void words::sort(Words& words)
        {
            if (!words.empty())
                sort(words, 0, words.size() - 1);
        }

        void words::sort(Words& words, size_t start, size_t end)
        {
            if (!(start < end))
                return;

            swap(words, start, (start + end) / 2);

            size_t current{ start };
            for (size_t i{ start + 1 }; i <= end; i++)
            {
                if (*words[i] < *words[start])
                    swap(words, ++current, i);
            }

            swap(words, start, current);

            if (current > start) sort(words, start, current - 1);
            if (end > current + 1) sort(words, current + 1, end);
        }
        ```

    - internals.ixx

        ```cpp
        //internals.ixx
        export module words:internals;

        import :alias;

        void swap(words::Words& words, size_t first, size_t second)
        {
            auto temp{ words[first] };
            words[first] = words[second];
            words[second] = temp;
        }

        size_t max_word_length(const words::Words& words)
        {
            size_t max{};
            for (auto& pword : words)
                if (max < pword->length()) max = pword->length();
            return max;
        }
        ```

    - alias.ixx

        ```cpp
        //alias.ixx
        export module words:alias;

        import<iostream>;
        import<string>;
        import<vector>;

        namespace words
        {
            export using Words = std::vector<std::shared_ptr<std::string>>;
        }
        ```

    - 上面程序运行结果如下：

        ---

        ```cpp
        Enter a string terminated by *:
        The old lighthouse stood on the cliff, its beam a silent guardian 
        against the raging sea. For decades, it had witnessed storms that could 
        splinter ships and fogs that could swallow the moon. The keeper, a man 
        with salt-crusted skin and weary eyes, maintained the flame with a 
        ritual precision. He knew every groan of the ancient structure, every 
        whisper of the wind. One night, the light flickered and died, plunging 
        the world into absolute blackness. He climbed the spiral stairs, his 
        heart pounding against the rising tide of panic, and found a single, 
        stubborn spark waiting to be reborn. *
        For
        He           He
        One
        The          The          
        a            a            a            a            absolute     
        against      against      ancient      
        and          and          and          and          
        be           beam         blackness    
        cliff        climbed      could        could        
        decades      died         
        every        every        eyes         
        flame        flickered    fogs         found        
        groan        guardian     
        had          heart        his          
        into         it           its          
        keeper       knew         
        light        lighthouse   
        maintained   man          moon         
        night        
        of           of           of           old          on           
        panic        plunging     pounding     precision    
        raging       reborn       rising       ritual       
        salt-crusted sea          ships        silent       single       
        skin         spark        spiral       
        splinter     stairs       stood        storms       structure    
        stubborn     swallow      
        that         that         the          the          the          
        the          the          the          
        the          the          the          the          tide         
        to           
        waiting      weary        whisper      wind         with         
        with         witnessed    world  
        ```

        ---

6. 第6题
    - Exer11_06.cpp

        ```cpp
        //Exer11_06.cpp
        /*************************第11章_练习_第6题************************
        仍然将第2题的解决方案作为起点，确保也能够使用wrds和w限定这个名称空间中
        的所有名称。应该使用两种不同的方法。需要注意，在生产质量的代码中，不应该
        使用晦涩难懂的缩写词（如wrds）或只有一个字母的标识符（如w）：清晰性总是
        比简洁性更重要。
        *****************************************************************/
        import<string>;
        import<iostream>;
        import words;

        namespace wrds
        {
            using namespace words;
        }

        int main()
        {
            wrds::Words the_words;
            std::string text;
            const auto separators{ " ,.!?\"\n" };

            std::cout << "Enter a string terminated by *:" << std::endl;
            getline(std::cin, text, '*');

            w::extract_words(the_words, text, separators);
            if (the_words.empty())
            {
                std::cout << "No words in text." << std::endl;
                return 0;
            }

            wrds::sort(the_words);
            w::show_words(the_words);
        }
        ```

    - words.ixx

        ```cpp
        //words.ixx
        export module words;

        import <memory>;
        import <string>;
        import <vector>;

        export namespace words
        {
            using Words = std::vector<std::shared_ptr<std::string>>;

            void sort(Words& words);
            void extract_words(Words& words, const std::string& text, 
                const std::string& separators);
            void show_words(const Words& words);
        }

        export namespace w = words;
        ```

    - words.cpp

        ```cpp
        //words.cpp
        module words;

        import <iostream>;
        import <format>;

        size_t max_word_length(const words::Words& words);

        void words::extract_words(Words& words, const std::string& text, 
            const std::string& separators)
        {
            size_t start{ text.find_first_not_of(separators) };

            while (start != std::string::npos)
            {
                size_t end{ text.find_first_of(separators, start + 1) };
                if (end == std::string::npos)
                    end = text.length();
                words.push_back(std::make_shared<std::string>
                    (text.substr(start, end - start)));
                start = text.find_first_not_of(separators, end + 1);
            }
        }

        void swap(words::Words& words, size_t first, size_t second)
        {
            auto temp{ words[first] };
            words[first] = words[second];
            words[second] = temp;
        }

        void sort(words::Words& words, size_t start, size_t end);

        void words::sort(Words& words)
        {
            if (!words.empty())
                ::sort(words, 0, words.size() - 1);
        }

        void sort(words::Words& words, size_t start, size_t end)
        {
            if (!(start < end))
                return;

            swap(words, start, (start + end) / 2);

            size_t current{ start };
            for (size_t i{ start + 1 }; i <= end; i++)
            {
                if (*words[i] < *words[start])
                    swap(words, ++current, i);
            }

            swap(words, start, current);

            if (current > start) sort(words, start, current - 1);
            if (end > current + 1) sort(words, current + 1, end);
        }

        size_t max_word_length(const words::Words& words)
        {
            size_t max{};
            for (auto& pword : words)
                if (max < pword->length()) max = pword->length();
            return max;
        }

        void words::show_words(const Words& words)
        {
            const size_t field_width{ max_word_length(words) + 1 };
            const size_t words_per_line{ 8 };
            std::cout << std::format("{:{}}", *words[0], field_width);

            size_t words_in_line{};
            for (size_t i{ 1 }; i < words.size(); ++i)
            {
                if ((*words[i])[0] != (*words[i - 1])[0] || ++words_in_line == words_per_line)
                {
                    words_in_line = 0;
                    std::cout << std::endl;
                }
                std::cout << std::format("{:{}}", *words[i], field_width);
            }
            std::cout << std::endl;
        }
        ```

    - 上面程序运行结果如下：

        ---

        ```cpp
        Enter a string terminated by *:
        The old lighthouse stood on the cliff, its beam a silent guardian 
        against the raging sea. For decades, it had witnessed storms that could 
        splinter ships and fogs that could swallow the moon. The keeper, a man 
        with salt-crusted skin and weary eyes, maintained the flame with a 
        ritual precision. He knew every groan of the ancient structure, every 
        whisper of the wind. One night, the light flickered and died, plunging 
        the world into absolute blackness. He climbed the spiral stairs, his 
        heart pounding against the rising tide of panic, and found a single, 
        stubborn spark waiting to be reborn. *
        For
        He           He
        One
        The          The          
        a            a            a            a            absolute     
        against      against      ancient      
        and          and          and          and          
        be           beam         blackness    
        cliff        climbed      could        could        
        decades      died         
        every        every        eyes         
        flame        flickered    fogs         found        
        groan        guardian     
        had          heart        his          
        into         it           its          
        keeper       knew         
        light        lighthouse   
        maintained   man          moon         
        night        
        of           of           of           old          on           
        panic        plunging     pounding     precision    
        raging       reborn       rising       ritual       
        salt-crusted sea          ships        silent       single       
        skin         spark        spiral       
        splinter     stairs       stood        storms       structure    
        stubborn     swallow      
        that         that         the          the          the          
        the          the          the          
        the          the          the          the          tide         
        to           
        waiting      weary        whisper      wind         with         
        with         witnessed    world 
        ```

        ---
