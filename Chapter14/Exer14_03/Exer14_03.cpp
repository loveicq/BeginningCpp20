// Exer14_03.cpp
/*************************第14章_练习_第3题************************\
在上一题中，把基类成员who()的访问修饰符改为public，但把who()函数实现为
每个派生类的成员，且在输出消息中显示类名。现在修改main()函数，为每个派生
类对象调用who()的基类版本和派生类版本。
\*****************************************************************/
import animals;
import <iostream>;

int main()
{
    Lion myLion{"Leo", 400};
    Aardvark myAardvark{"Algernon", 50};

    std::cout << "Calling derived versions of who():\n";
    myLion.who();
    myAardvark.who();

    std::cout << "\nCalling base versions of who():\n";
    myLion.Animal::who();
    myAardvark.Animal::who();
    // static_cast<Animal&>(myAardvark).who();
}