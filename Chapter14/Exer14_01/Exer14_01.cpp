// Exer14_01.cpp
/*************************第14章_练习_第1题************************\
定义一个基类Animal，它包含两个私有成员变量：一个是string成员m_name，存储
动物的名称（例如“Fido”或“Yogi”）；另一个是整数成员m_weight，存储动物的
重量（单位是磅）。该类还包含一个公共成员函数who()，它可以显示一条信息，
给出Animal对象的名称和重量。把Animal用作公共基类，派生两个类：Lion和
Aardvark。再编写一个main()函数，创建Lion和Aardvark对象（“Leo”，400磅；
“Algernon”，50磅）。为派生类对象调用who()成员，说明who()成员在两个派生类
中是继承得来的。
\*****************************************************************/
import animals;

int main()
{
    Lion myLion{"Leo", 400};
    Aardvark myAardvark{"Algernon", 50};
    myLion.who();
    myAardvark.who();
}