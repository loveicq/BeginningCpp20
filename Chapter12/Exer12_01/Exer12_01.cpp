/*************************第12章_练习_第1题************************
创建一个Integer类，它只有一个int类型的私有成员变量。为这个类提供构造函
数，并使用它输出创建对象的消息。定义类的成员函数，获取和设置成员变量，并
输出它们的值。编写一个测试程序，创建和操作至少3个Integer对象，验证不能
直接给成员变量赋值。在测试程序中获取、设置和输出每个对象的成员变量值，以
验证这些函数。确保创建至少一个const Integer对象，并验证可以对该对象执行
的操作，以及不能执行的操作。
*****************************************************************/
// Implementing an Integer class
import integer;
import std;

int main()
{
    std::cout << "Create i with the value 10." << std::endl;
    Integer i{10};
    i.show();
    std::cout << "Change value of i to 15." << std::endl;
    //  i.m_value=15;   //Cannot assign directly to m_value
    //  error C2248:“Integer::m_value”: 无法访问 private
    //  成员(在“Integer”类中声明)
    i.setValue(15);
    i.show();

    std::cout << "Create j with a value that is 150 times that of i."
              << std::endl;
    const Integer j{150 * i.getValue()};
    j.show();
    std::cout << "Set value of j to ." << std::endl;
    // j.setValue(5000);//Cannot call setValue() on const object
    //(show() and getValue() work,though)
    // error C2662: “void Integer::setValue(int)”: 不能将“this”指针从“const
    // Integer”转换为“Integer &”

    std::cout << "Create k with the value 789." << std::endl;
    Integer k{789};
    k.show();
    std::cout << "Set value of k to sum of i and j values." << std::endl;
    k.setValue(i.getValue() + j.getValue());
    k.show();
}