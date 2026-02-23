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