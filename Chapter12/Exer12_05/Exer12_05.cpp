// Exer12_05.cpp
/*************************第12章_练习_第5题************************\
为第2题创建的Integer类实现一个静态函数printCount()，使其输出存在的
Integer对象的数量。修改main()函数，测试这个数字是否根据情况增加或减少。
\*****************************************************************/
import integer;
import <iostream>;

void showIntegerVal(Integer it);
void showIntegerRef(const Integer& it);

int main()
{
    std::cout << "Create i with the value 0." << std::endl;
    Integer i;
    i.show();

    Integer::printCount();

    if (i.getValue() == 0)
    {
        std::cout << "Create j from object i." << std::endl;
        Integer j{i};
        j.show();
        Integer::printCount();
    }

    Integer::printCount();

    Integer array[]{1, 2, 3};

    Integer::printCount();

    showIntegerRef(array[0]); // 按引用传递不创建对象
    showIntegerVal(array[1]); // 按值传递创建临时对象

    Integer::printCount();

    return 0;
}

void showIntegerVal(Integer it)
{
    it.show();
    Integer::printCount();
}

void showIntegerRef(const Integer& it)
{
    it.show();
    Integer::printCount();
}