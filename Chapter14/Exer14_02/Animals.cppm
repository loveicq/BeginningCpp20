// Animals.cppm
export module animals;

import <iostream>;
import <string_view>;
import <string>;

export class Animal
{
public:
    Animal(std::string_view name, int weight)
        : m_name{name}, m_weight{weight} {}

protected:
    void who() const
    {
        std::cout << "My name is " << m_name << ", and I weight " << m_weight << " lbs." << std::endl;
    }

private:
    std::string m_name;
    int m_weight;
};

export class Lion : public Animal
{
public:
    Lion(std::string_view name, int weight)
        : Animal{name, weight} {}
    void who() const { return Animal::who(); }
    // 书中此函数未加const，是瑕疵，否则在调用时"const Lion myLion{"Leo", 400};"
    // 会编译失败！const 对象只能调用 const 成员函数
};

export class Aardvark : public Animal
{
public:
    using Animal::Animal;
    using Animal::who; // 注意此处不能加小括号()，因为using 声明的作用是引入一个名字到当前作用域，而不是调用函数。
};