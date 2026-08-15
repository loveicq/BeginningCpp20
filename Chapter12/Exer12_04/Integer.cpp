// Integer.cpp
/*****************************************************************\
将 compare() 实现为友元函数非常简单。我们必须在类定义中将该函数声明为
友元。现在我们需要两个对象作为参数，函数体内的代码只需比较参数的成员变量
即可。两个参数都是常量引用。

然而，除了练习友元函数使用这一需求之外，compare() 函数实际上没有真正的
理由要成为 Integer 类的友元：它完全可以使用公有的 getValue() 函数来
实现。因此，下面给出的 nonFriendCompare() 函数相比友元函数更值得推荐。
\*****************************************************************/
module integer;
import <iostream>;

Integer::Integer(int value)
    : m_value{value}
{
    std::cout << "Object created." << std::endl;
}

Integer::Integer(const Integer& obj)
    : m_value{obj.m_value}
{
    std::cout << "Object created by copy constructor." << std::endl;
}

void Integer::show() const
{
    std::cout << "Value is " << m_value << std::endl;
}

int compare(const Integer& obj1, const Integer& obj2)
{
    if (obj1.m_value < obj2.m_value)
        return -1;
    else if (obj1.m_value == obj2.m_value)
        return 0;
    return 1;
}

int nonFriendCompare(const Integer& obj1, const Integer& obj2)
{
    if (obj1.getValue() < obj2.getValue())
        return -1;
    else if (obj1.getValue() == obj2.getValue())
        return 0;
    return 1;
}