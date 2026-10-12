// Exer14_02.cpp
/*************************第14章_练习_第2题************************\
在Animal类中，把who()函数的访问修饰符改为protected，但类的其它内容不变。
现在修改派生类，使原来的main()函数仍能工作。
\*****************************************************************/
import animals;

int main()
{
    Lion myLion{"Leo", 400};
    Aardvark myAardvark{"Algernon", 50};
    myLion.who();
    myAardvark.who();
}