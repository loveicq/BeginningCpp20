# 第7章 操作字符串

string 类型比char元素数组的C样式字符串更加高效和安全

## 7.1 更强大的string类

- c语言`<cstring>`模块提供很多函数用来操作C样式字符串，但是必须要有空字符，否则会出错
- c++语言`<string>`模块定义了std::string类型，由一个类模板定义，是复合类型。使用时必须导入`<string>`模块

### 7.1.1 定义string对象

1. 用空字符串初始化string对象  
`std::string empty;`//string对象，空字符串长度为0，占用32字节空间
2. 用字符串字面量初始化string对象  
`std::string proverb {"Many a mickle makes a muckle."};`//string对象封装的字符数组总是用空字符终止。
    - 调用string对象的length()函数可以得到字符串的长度  
`std::cout<<proverb.length();`//输出29
    - 可以将std::string对象转换为C样式字符串
        - 调用c_str()成员函数  
        `const char* proverb_c_str=proverb.c_str();`
        - 调用data()成员函数  
        `char* proverb_data=proverb.data();`
3. 用字符串字面量中的初始序列初始化string对象  
`std::string part_literal {"Least said soonest mended.", 5};`//"Least"
4. 用任意多个实例来初始化string对象  
`std::string sleeping(6, 'Z');`//"ZZZZZZ"，注意是小括号，不能用大括号
    - 教材中说“不能用括在单引号的字符来初始化string对象，必须使用放在双引号中的字符串字面量，即使只有一个字符也是如此。”，这得分情况：
        - C++11及以后列表初始化可以用单引号初始化  
        `std::string singleChar{'a'};`//正确！！！
        - C++11之前统一初始化不可以用单引号初始化  
        `std:string singleChar = 'a';`//错误！！！  
        `std:string singleChar = "a";`//正确！！！  
        `std:string singleChar("a");`//正确！！！
    - 要使用重复的字符值初始化string对象，不能使用大括号  
        `std::string sleeping{6,'Z'};`//错误！！！这会得到两个字母，不是6个Z
5. 使用已有的string对象提供初始值来初始化  
`std::string sentence {proverb};`
    - 使用从0开始的索引值可以引用string对象中的字符  
    `std::string phrase {proverb,0,13};`//"Many a mickle"
        - 第一个参数是源字符串
        - 第二个参数是开始索引位置
        - 第三个参数是引用的字符个数
            - 一定要注意第二参数索引是从0开始的，因此提取字符串"mickle"是`{proverb,7,6}`，而不是`{proverb,8,6}`
            - 一定要注意第三参数是字符串长度，而不是索引位置，因此提取字符串"mickle"是`{proverb,7,6}`，而不是`{proverb,7,13}`
6. 通过已有的std::string对象和一个整数初始化std::string对象  

```cpp
std::string string{"Consistency is the key to success"};
std::string part_string{string, 15};//"the key to success"
```

注意这种方式第3种之间的差异！前面是字面量+整数，代表从索引0开始的字符数量；这个是对象和整数，代表索引从整数开始到字符串最后的字符串。意义完全不一样。

### 7.1.2 string对象的操作

可以把字符串字面量或者一个string对象赋予另一个string对象

**1.连接字符串**  

- 使用加号“+”可以把一个字符串字面量和一个string对象连接在一起
- 加号“+”不能连接两个字符串字面量
- 可以通过几种方法将两个字符串字面量连接在一起，如省略加号、使用小括号、使用初始化语法、字符串字面量后面加字母“s”等

```cpp
//Ex7_01.cpp
#include <iostream>
#include <string>

int main(){
    std::string first;
    std::string second;

    std::cout<<"Enter your first name: ";
    std::cin>>first;//string对象赋值
    std::cout<<"Enter your second name: ";
    std::cin>>second;//cin遇到空白字符即停止输入，故名字中间有空格就不合适了

    std::string sentence{"Your full name is "};//字符串字面量初始化
    sentence+=first+" "+second+".";//string对象支持+=运算符

    std::cout<<sentence<<std::endl;
    std::cout<<"The string contains "<<sentence.length()//函数计算string对象包含的字符数量，32个字符
    <<" characters."<<std::endl;
}
```

- +=运算符也可用于string类型的对象，如上例
- 可使用std::string对象的append()函数代替+=运算符，此函数比+=更灵活，允许连接字符串或重复的字符。

**2.连接字符串和字符**  

```cpp
//Exer7_01.cpp
#include <iostream>
#include <string>

int main(){
    std::string first;
    std::string second;

    std::cout<<"Enter your first name: ";
    std::cin>>first;
    std::cout<<"Enter your second name: ";
    std::cin>>second;

    std::string sentence{"Your full name is "};
    sentence+=second;
    sentence+=','+' ';//此句会计算','和' '字符的ASCII码之和，再转换成字符（L）与sentence运算
    sentence+=first;

    std::cout<<sentence<<std::endl;//输出“McCavityLPhil”
    std::cout<<"The string contains "<<sentence.length()//只有31个字符
    <<" characters."<<std::endl;
}
```

- std::string连接的一般规则很简单：连接从左向右计算，只要连接运算+有一个操作数是std::string对象，就能正常工作
- 任何地方使用字符串字面量时，都可以使用C样式字符串，即char[]数组或char*变量，“+”连接运算符前后也可以使用C样式字符串，或使用char类型字符

**3.连接字符串和数字**  

- 除了字符串和字符，std::string对象无法连接，否则编译会报错

```cpp
//Test7_01.cpp
#include<iostream>
#include<string>
#include<numbers>

int main()
{
    const std::string result_string{"The result equals: "};
    double result{std::numbers::pi};
    
    std::cout<<result_string+result<<std::endl;//无法编译，std::string对象不能连接double类型
}
```

- 有时候能编译，但结果错误

```cpp
//Test7_02.cpp
#include<iostream>
#include<string>
#include<numbers>

int main()
{
    std::string song_title{"Summer of '"};
    song_title+=69;//69的ASCII字符是E
    std::cout<<song_title<<std::endl;//Summer of 'E
}
```

- 可以通过std::to_string将其它类型转换成字符类型，再连接std::string对象

```cpp
//Test7_03.cpp
#include<iostream>
#include<string>
#include<numbers>

int main()
{
    const std::string result_string{"The result equals: "};
    double result{std::numbers::pi};
    //其实本例无需转换，也无需使用连接符，直接流自动转换即可：std::cout<<result_string<<result<<std::endl;
    std::cout<<result_string+std::to_string(result)<<std::endl;//The result equals: 3.141593

    std::string song_title{"Summer of '"};
    song_title+=std::to_string(69);
    std::cout<<song_title<<std::endl;//Summer of '69

}
```

### 7.1.3 访问字符串中的字符

- 在中括号中使用索引值，就可以引用字符串中的某个字符，std::string对象中的第一个字符索引值是0
- std::string对象是一个范围，可以使用基于范围的for循环操作，但修改字符需使用引用
- 其实不管是中括号加索引还是引用，目的都是为了指定内存地址

```cpp
//Test7_02.cpp
#include<iostream>
#include<string>
#include<cctype>

int main()
{
    //定义并输入名字
    std::string first;
    std::string second;
    std::cout<<"Enter your first name: ";
    std::cin>>first;
    std::cout<<"Enter your second name: ";
    std::cin>>second;

    //定义句子并连接名字
    std::string sentence {"Your full name is "};
    sentence+=first+" "+second+".";

    //输出句子
    std::cout<<sentence<<std::endl;

    //用索引方式修改句子全部字母为大写
    for(size_t i{};i<sentence.length();++i)
    {
        sentence[i]=static_cast<char>(std::toupper(sentence[i]));
    }
    std::cout<<sentence<<std::endl;//YOUR FULL NAME IS PHIL MCCAVITY.

    //用基于范围for循环方式修改句子全部字母为小写
    for(char& ch:sentence)
    {
        ch=static_cast<char>(std::tolower(ch));
    }
    std::cout<<sentence<<std::endl;//your full name is phil mccavity.
}
```

```cpp
//Ex7_02.cpp
//Accessing characters in a string
#include<iostream>
#include<cctype>
#include<string>

int main()
{
    //使用std::getline()输入字符串，包含空格字符
    std::string text;
    std::cout<<"Enter a line of text:\n";
    std::getline(std::cin,text);//和std::cin.getline()有差别

    //统计字符串元音字符和辅音字符的数量
    unsigned vowels{};//元音数量
    unsigned consonants{};//辅音数量
    for(size_t i{};i<text.length();++i)
    {
        if(std::isalpha(text[i]))//判断是否为字母
        {
            switch (std::tolower(text[i]))
            {
            case 'a' :case 'e':case 'i':case 'o':case 'u':
                ++vowels;
                break;
            
            default:
                ++consonants;
                break;
            }
        }
    }

    //输出元音和辅音的数量
    std::cout<<"Your input contained "<<vowels<<" voewls and "
            <<consonants<<" consonants."<<std::endl;
}
````

- std::getline()读取一行字符，直到遇到换行符为止
- std::getline()可以修改表示输入行结尾的分隔符，使用第三个参数
`std::getline(std::cin,text,'#');`,此时换行符不是结束，可以输入任意多行内容

### 7.1.4 访问子字符串

- 使用substr()函数可以获取string对象的一个子字符串。第一个实参指定子字字符串开始索引位置，第二个实参指定子字符串中的字符个数。该字符串返回一个包含子字符串的string对象。

```cpp
//Test7_03.cpp
//substr()函数获取子字符串
#include<iostream>
#include<string>

int main()
{
    std::string phrase{"The higher the fewer."};
    std::string word1{phrase.substr(4,6)};

    std::cout<<word1<<std::endl;//higher
}
```

- substr()第二个实参超过string对象的结尾，则返回从指定位置开始直到该字符串最后的所有字符

```cpp
//Test7_04.cpp
//substr()函数获取子字符串,第二个实参超过string对象长度
#include<iostream>
#include<string>

int main()
{
    std::string phrase{"The higher the fewer."};
    std::string word1{phrase.substr(4,100)};

    std::cout<<word1<<std::endl;//higher the fewer.
}
```

- 如果省略第二个实参，则从第一个实参指定的索引位置开始到最后的所有字符返回给子字符串
`std::string word1{phrase.substr(4)};`
- 如果省略第一和第二实参，则把字符串所有字符返回给子字符串
`std::string word1{phrase.substr()};`
- 如果第一实参超出string对象的有效边界，就会抛出一个std::out_of_range类型的异常，程序将异常终止

### 7.1.5 比较字符串

- 比较运算符:>、>=、<、<=、==、!=、<=>
- 比较运算符用于比较两个string对象，或者比较string对象与字符串字面量或C样式字符串
- 比较运算符逐个比较其中的字符，直到找到不同的字符，或到达一个或两个操作数的结尾
- 如果没有找到不同的字符，但字符串有不同的长度，则较短的字符串就小于较长的字符串
- 如果两个字符串包含相同数量的字符，且对应的字符都相同，则这两个字符串相等
- 比较是区分大小写的（因为比较的是ASCII码）
- ❗要特别注意：如果没有String对象，只比较char[]或者char*类型字符串，不能用比较运算符，因为这样比较的是指针地址，不是每个字符的ASCII码。要比较这两种类型，可以用strcmp()函数，如下例

    ```cpp
    // Test7_05.cpp
    // 测试比较运算符
    #include <iostream>
    #include <string>
    #include <cstring>
    #include <string.h>

    int main()
    {
        const std::string word1{"age"};
        const std::string word2{"beauty"};
        const char word3[] = "cout";
        const char *word4{new char[]{"cout"}};

        // 比较两个string对象
        if (word1 < word2)
            std::cout << word1 << " comes before " << word2 << '.' << std::endl;
        else
            std::cout << word2 << " comes before " << word1 << '.' << std::endl;

        // 比较一个string对象和char[]字符串
        if (word2 < word3) // 只要有string对象参与比较，就重载了运算符，可以直接与char[]或char*
            std::cout << word2 << " is less than " << word3 << '.' << std::endl;
        else
            std::cout << word3 << " is less than " << word2 << '.' << std::endl;

        // 比较char[]字符串数组和char*字符串
        if (strcmp(word3, word4) < 0) // char*和char[]之间比较，不能用比较运算符，因为比较的是指针地址
            std::cout << word4 << " is greater than " << word3 << '.' << std::endl;
        else if (strcmp(word3, word4) > 0)
            std::cout << word3 << " is greater than " << word4 << '.' << std::endl;
        else
            std::cout << word3 << " is equal to " << word4 << '.' << std::endl;

        delete[] word4;
        word4 = nullptr;
    }
    ```

- 采用条件运算符写比较语句比较简洁：

    ```cpp
    std::cout << word1 << word1<word2 ? " comes " : " does not comes "  
            << "before "<<word2<<'.' << std::endl;
    ```

    ```cpp
    // Ex7_03.cpp
    // Comparing strings
    #include <iostream>
    #include <string>
    #include <format>
    #include <vector>

    int main()
    {
        // 创建一个字符串向量来存储名字
        std::vector<std::string> names; // 因为是类类型，调用构造函数把内部状态置为空，有没有{}都是一样的
        std::string input_name;

        // 输入名字，直到用户输入空行
        for (;;)
        {
            std::cout << "输入名称,然后按Enter(空行停止): ";
            std::getline(std::cin, input_name);
            if (input_name.empty())
                break;
            names.push_back(input_name);
        }

        // 名字按字母顺序排序
        bool sorted{};
        do
        {
            sorted = true; // 假设已经排好序
            for (size_t i{1}; i < names.size(); ++i)
                if (names[i - 1] > names[i])
                {
                    names[i].swap(names[i - 1]);
                    sorted = false; // 如果有交换,则还未排好序
                }
        } while (!sorted); // 如果没排好序,为false;!false=true,继续循环

        // 找出最长名字的长度
        size_t max_length{};
        for (const auto &name : names)
            if (max_length < name.length())
                max_length = name.length();

        // 按每行5个名字输出
        const size_t field_width = max_length + 2;
        size_t count{};

        std::cout << "名字按字母先后排序:\n";
        for (const auto &name : names)
        {
            std::cout << std::format("{:>{}}", name, field_width); // 右对齐+动态宽度
            if (!(++count % 5))
                std::cout << std::endl;
        }

        std::cout << std::endl;
    }
    ```

- 可以使用empty()函数来检查输入是否为空行，这是std::string与std::vector<>共有的这么多函数之一
- std::string可以存储在容器中，而C样式字符串不能
- std名称空间还定义了一个非成员函数模板：`std::swap(names[i],names[i-1]);`。这个函数模板也可以用于基本类型。使用此函数需要先导入`<utility>`模块
- ❗format格式化输出，`宽度`和`精度`可以用嵌套的替代字段来动态指定，如：`std::format("{:>{}}",name,field_width)`,外部的{}用第0个参数替代，内部的{}用第1个参数替代。也可以写作:`std::format("{1:>{0}}",field_width,name)`,这样外部的{}就用第1个参数替代，内部的{}就用第0个参数替代。也即可以有多个参数，如`format("{:>{}}",name,field_width,1,5,8)`也是可以的，但最终要么按顺序调用，要么直接指定。除了宽度和精度，格式说明符的其它部分不能替代。

**1.三向比较运算符**  
三向比较函数可以解决string对象比较的低效问题

- <=>运算符

    ```cpp
    const auto order = s1 <=> s2;
    if(std::is_lt(order))//is_lt(),is less than,小于
        ...
    else if(std::is_gt(order))//is_gt(),is greater than,大于
        ...
    else //is_eq(),is equivalent,等价(与相等(equal)不一样)。这三个函数在<compare>模块中定义
        ...
    ```

❗注意：<=>的结果是类类型，不是Boolean类型，不能用于if()等判断场合。

- compare()函数

    ```cpp
    const int comp = s1.compare(s2);
    if(comp<0)
        ...
    else if(comp>0)
        ...
    else
        ...
    ```

- ❗注意：compare()函数的结果int类型，s1 > s2,返回正整数；s1 = s2, 返回0；s1 < s2，返回负整数。

**2.使用compare()比较字符串**  

- 对齐

    ```cpp
    // 使用compare()比较子字符串
    #include <iostream>
    #include <string>

    int main()
    {
        std::string word1{"A jackhammer"};
        std::string word2{"jack"};

        const int result{word1.compare(2, word2.length(), word2)};

        if (result == 0)
        {
            std::cout << word1 << " contains " << word2 
                    << " starting at index 2" << std::endl;
        }
    }
    ```

- ❗注意,compare()函数有多种重载模式，上面测试案例就是其中一种。

    ```cpp
    // compare()函数搜索子字符串
    #include <iostream>
    #include <string>

    int main()
    {
        std::string text{"Peter Piper picked a peck of pickled peppers."};
        std::string word{"pick"};

        for(size_t i{};i<text.length()-word.length()+1;++i) //+1是为了最少循环一次，假设text和word内容一样，也能正确输出结果（即包含，从索引0开始）
        {
            if(text.compare(i,word.length(),word)==0)
            {
                std::cout<<"text contains "<<word<<" starting at index "<<i<<std::endl;
            }
        }
    }
    ```

- 上面测试案例是用compare()成员函数搜索子字符串的方法。

- 可以利用compare()函数比较一个string对象的子字符串和另一个String对象的子字符串,这需要传送5个参数

    ```cpp
    // 利用compare()函数比较string对象子字符串和另一个string对象子字符串
    #include <iostream>
    #include <string>

    int main()
    {
        std::string text{"Peter Piper picked a peck of pickled peppers."};
        std::string phrase{"Got to pick a pocker or two."};

        for (size_t i{}; i < text.length() - 3; ++i) //or i<=text.length()-4;防止越界访问
        {
            if (text.compare(i, 4, phrase, 7, 4) == 0)
            {
                std::cout << "text contains " << phrase.substr(7, 4)
                        << " starting at index " << i << std::endl;
            }
        }
    }
    ```

- compare()函数还可以比较string对象的子字符串和C样式字符串  
`if(text.compare(i,4,"pick")==0)`

- compare()函数还可以指定要使用的字符个数,从C样式字符串中选择前n个字符  
`if(text.compare(i,4,"picked",4)==0)`

**使用substr()进行比较**  

- substr()函数用于提取String对象子字符串

    ```cpp
    // substr()函数提取string()对象子字符串
    #include <iostream>
    #include <string>

    int main()
    {
        std::string text{"Peter Piper picked a peck of pickled peppers."};
        std::string phrase{"Got to pick a pocket or two."};

        for (size_t i{}; i < text.length() - 3; ++i)
        {
            if (text.substr(i, 4) == phrase.substr(7, 4))
            {
                std::cout << "text contains " << phrase.substr(7, 4)
                        << " starting at index " << i << std::endl;
            }
        }
    }
    ```

- substr()函数效率比compare()函数略低,但代码的清晰性和可读性要比性能的些许提高要重要得多

**检查字符串的开始或结束**  

- C++20引入starts_with()和ends_with()两个有用的成员函数来检查字符串的开始和结尾

    ```cpp
    // 检查字符串的开始或结尾
    #include <iostream>
    #include <string>

    int main()
    {
        std::string text{"Start with the end in mind."};

        if (text.starts_with("Start"))
        {
            std::cout << "The text starts with 'Start'." << std::endl;
        }
        if (!text.ends_with("end"))
        {
            std::cout << "The text does not end with 'end'." << std::endl;
        }
    }
    ```

- 这两个函数还可以比较单个字符  

    `if(text.ends_with('.'))`  
    `std::cout<<"The text ends with a period."`

- 在空字符串上使用这两个函数也是案例的(对空字符串返回false)。对于[]、front()、back()和substr()这一点不成立。

### 7.1.6 搜索字符串

- find()函数

    ```cpp
    // Ex7_04.cpp
    // Searching within strings
    #include <iostream>
    #include <string>

    int main()
    {
        std::string sentence{"Manners maketh man"};
        std::string word{"man"};

        std::cout << sentence.find(word) << std::endl;
        std::cout << sentence.find("Ma") << std::endl;
        std::cout << sentence.find('k') << std::endl;
        std::cout << sentence.find('x') << std::endl;
    }
    ```

**1.在子字符串内搜索**  

- find()函数允许从指定位置开始搜索

    ```cpp
    // find()函数在子字符串内搜索
    #include <iostream>
    #include <string>

    int main()
    {
        std::string sentence{"Manners maketh man"};
        std::string word{"an"};
        int count{};

        for (size_t i{}; i <= sentence.length() - word.length();)
        {
            size_t position = sentence.find(word, i);
            if (position == std::string::npos)
            {
                break;
            }
            ++count;
            i = position + 1;
        }

        std::cout << '"' << word << "\" occurs in \"" << sentence
                << "\" " << count << " times." << std::endl;
    }
    ```

- find()三个实参,第一个是要搜索的字符串,第二个是从源字符串开始搜索的索引,第三个是要搜索的字符串开始搜索的索引`sentence.find("ananas",8,2)`

    ```cpp
    // Ex7_05.cpp
    // Searching within string
    #include <iostream>
    #include <string>

    int main()
    {
        std::string text;
        std::string word;
        std::cout << "Enter the string to be searched and press Enter:\n";
        std::getline(std::cin, text);
        std::cout << "Enter the string to be found and press Enter:\n";
        std::getline(std::cin, word);

        size_t count{};
        size_t index{};
        while ((index = text.find(word, index)) != std::string::npos) // 从本题来说,完全没必要在本行赋值index=...
        {
            ++count;
            index += word.length();
        }

        std::cout << "You text contained " << count << " occurrences of \""
                << word << "\"." << std::endl;
    }
    ```

**2.搜索任意字符集合**  

- find_first_of()函数  
此函数可以从**前面**开始搜索string对象或C风格字符串中任意一个字符最先出现的位置(size_t)

    ```cpp
    // 练习find_first_of()函数
    #include <iostream>
    #include <string>

    int main()
    {
        std::string text{"Smith,where Jones had had \"had had\",had had \"had \"."
                        " \"Had had\" had had the examiners' approval."};
        std::string separators{" ,.\""};//先遇到字符','，位于索引位置5
        std::cout << text.find_first_of(separators) << std::endl;//输出5
    }
    ```

- find_last_of()函数  
此函数可以从**后面**开始搜索string对象或C风格字符串中任意一个字符最先出现的位置

    ```cpp
    // 练习find_last_of()函数
    #include <iostream>
    #include <string>

    int main()
    {
        std::string text{"Smith,where Jones had had \"had had\", had had \"had\"."
                        " \"Had had\" had had the examiners' approval."};
        std::cout << text.find_last_of("AaEeIiOoUu") << std::endl; // 输出91
    }
    ```

    ```cpp
    // Ex7_06.cpp
    // Searching a string for characters from a set
    #include <iostream>
    #include <string>
    #include <format>
    #include <vector>

    int main()
    {
        std::string text;
        std::cout << "Enter som text terminated by *:\n";
        std::getline(std::cin, text, '*');

        const std::string separators{" ,;:.\"!?'\n"};
        std::vector<std::string> words;
        size_t start{text.find_first_not_of(separators)};

        while (start != std::string::npos)
        {
            size_t end = text.find_first_of(separators, start + 1);
            if (end == std::string::npos)
            {
                end = text.length(); // 最后一个词到末尾
            }
            words.push_back(text.substr(start, end - start));
            start = text.find_first_not_of(separators, end + 1);
        }

        std::cout << "Your string contains the following " << words.size() << " words:\n";
        size_t count{};
        for (const auto &word : words)
        {
            std::cout << std::format("{:15}", word);
            if (!(++count % 5))
            {
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }
    ```

**3.逆向搜索字符串**  

- rfind()函数可以从一个std::string对象的末尾向前搜索子字符串(可以是std::string,也可以是C样式字符串)
- rfind()得到的结果是后面搜索遇到的第一个符合条件的字符的位置(这个位置是从前面第0个字符开始数的)
- rfind()如果未搜索到符合条件的字符串,则返回npos值(-1)
- 和find()一样,有多种重载函数,如两个参数,三个参数等

    ```cpp
    // rfind()测试
    #include <iostream>
    #include <string>

    int main()
    {
        std::string sentence{"Manners maketh man"};
        std::string word{"an"};

        std::cout << sentence.rfind(word) << std::endl;  // 16 搜索string对象
        std::cout << sentence.rfind("man") << std::endl; // 15 搜索C样式字符串
        std::cout << sentence.rfind('e') << std::endl;   // 11 搜索字符,注意是单引号
    }
    ```

### 7.1.7 修改字符串

- **insert()函数插入字符串**  

    ```cpp
    // 测试insert()函数
    #include <iostream>
    #include <string>

    int main()
    {
        const std::string ORIGINAL_PHRASE{"We can insert a string."};
        std::string phrase{ORIGINAL_PHRASE};
        std::string words{"a string into "};

        phrase.insert(14, words);         // 插入string对象,phrase字符串第14位字符是'a'
        std::cout << phrase << std::endl; //"We can insert a string into a string."

        phrase = ORIGINAL_PHRASE;
        phrase.insert(14, "a string into "); // 插入C样式字符串
        std::cout << phrase << std::endl;    //"We can insert a string into a string."

        phrase = ORIGINAL_PHRASE;
        phrase.insert(13, words, 8, 5);   // 插入string对象其中一部分内容,words第8位开始,取5个字符,即" into"
        std::cout << phrase << std::endl; //"We can insert into a string.
    }
    ```

- **replace()函数替换子字符串**  

    ```cpp
    // Ex7_07.cpp
    // Replacing words in a string
    #include <iostream>
    #include <string>

    int main()
    {
        std::string text;
        std::cout << "Enter a string terminated by *:\n";
        std::getline(std::cin, text, '*');

        std::string word;
        std::cout << "Enter the word to be replaced: ";
        std::cin >> word;

        std::string replacement;
        std::cout << "Enter the string to be substituted for " << word << ": ";
        std::cin >> replacement;

        if (word == replacement)
        {
            std::cout << "The word its replacement are the same.\n"
                    << "Operation aborted." << std::endl;
            return 1;
        }

        size_t start{text.find(word)};
        while (start != std::string::npos)
        {
            text.replace(start, word.length(), replacement);
            start = text.find(word, start + replacement.length());
        }

        std::cout << "\nThe string you entered is now:\n"
                << text << std::endl;
    }
    ```

    注意.length()取得某个字符串的长度的用法

- **erase()删除字符串中的字符**  

  - `text.erase(0,6);` 从第几(实参1)位删除几(实参2)个字符
  - `text.erase(6);` 删除第几(实参)位以后的字符
  - `text.erase();` 删除全部字符,text成为空字符串,与`text.clear();`作用一样
  - `text.erase('v')` 删除字符串中所有的字母'v'(实参)

### 7.1.8 对比`std::string`与`std::vector<char>`

- `std::string`对象支持`std::vector<char>`的几乎全部成员函数，如push_back()、at()、size()、front()和back()、assign()等
- `std::string`对象还有专属的更方便的函数,如连接字符串、访问子字符串、搜索和替换字符串等

## 7.2 将字符串转换为数字

- `std::to_string()`数字转换字符串
- `std::stoi()`字符串转换数字

    ```cpp
    std::string s{"123"};
    int i{std::stoi(s)};
    ```

- `<string>`提供stol()、stoll()、stoul()、stoull()、stof()、stod()和stold()函数

## 7.3 国际字符串

- `std::wstring`对象，包含wchar_t类型的字符串，是C++内置的宽字符类型
- `std::unstring`对象，类型是charn_t
- 可以使用`std::string`的所有函数

### 7.3.1 存储wchar_t字符的字符串

**声明、赋值和输出的方式**  

```cpp
// 测试wchar_t字符串
#include <iostream>
#include <string>

int main()
{
    std::wstring saying{L"Test!"};     // 定义使用wstring,赋值使用"L"
    std::wcout << saying << std::endl; // 使用wcout输出
}
```

### 7.3.2 包含Unicode字符串的对象

- Unicode字符串对象的定义

    | 字符串类型 | 字符类型 | 字符序列 | 前缀 |
    | :-------- | :------- | :------- | :------- |
    | std::u8string | char8_t | UTF-8 | u8 |
    | std::u16string | char16_t | UTF-16 | u |
    | std::u32string | char32_t | UTF-32 | U |

- Unicode字符串不能直接用cout或wcout输出，需要转换，但是C++没有直接的转换功能，需要用第三方库

    ```cpp
    // 测试Unicode字符串对象
    #include <iostream>
    #include <string>

    int main()
    {
        // 注意声明和赋值的关键字
        std::u8string u8{u8"u8string！你好，中文!"}; // UTF-8
        std::u16string u16{u"u16string!"};           // UTF-16
        std::u32string u32{U"u32string!"};           // UTF-32

        // Unicode字符串对象需要转换才能输出，这样转换可以输出UTF-8编码的中文
        std::string s(reinterpret_cast<const char *>(u8.data()), u8.size());
        std::cout << s << std::endl;

        // 或者用范围循环输出每个字符
        for (char16_t c : u16)
        {
            std::cout << static_cast<char>(c);
        }
        std::cout << std::endl;

        for (char32_t c : u32)
        {
            std::cout << static_cast<char>(c);
        }
        std::cout << std::endl;
    }
    ```
