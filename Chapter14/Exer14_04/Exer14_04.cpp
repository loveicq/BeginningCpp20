// Exer14_04.cpp
/*************************第14章_练习_第4题************************\
定义一个Person类，它包含的成员变量分别用于存储年龄、姓名和性别。从Person
类派生一个类Empliyee，在新类中添加一个成员变量，存储个人的编号。再从
Employee类派生一个类Executive。每个派生类都应定义一个成员函数who()，
以显示相关的信息。仔细思考并实现合适的数据隐藏和访问修饰符。在这个程序中，
由于考虑到隐私，不应该公开个人的细节，但对象的who()成员输出的信息除外。
每个类可显式决定可以公开的信息（姓名和类型是可以接受的，如“Fred Smith is
an Employee”）。另外，不允许个人修改姓名或性别，但允许有生日。编写一个
main()函数，生成两个向量：一个向量包含5个Executive对象，另一个向量包含
5个普通的Employee对象，然后显示它们的信息。另外，调用从Employee类继承的
成员函数，显示Executive对象的信息。
\*****************************************************************/
import <iostream>;
import <vector>;
import person;

int main()
{
    std::vector<Employee> employees{
        Employee{21, "Randy Marathon", Gender::male, 34567},
        Employee{32, "Anna Pothecary", Gender::female, 34578},
        Employee{46, "Peter Out", Gender::male, 34589},
        Employee{37, "Sheila Rangeit", Gender::female, 34598},
        Employee{65, "Jack Ittin", Gender::male, 34667}};

    for (const auto& employee : employees)
        employee.who();

    std::cout << std::endl;

    std::vector<Executive> executives{
        {44, "Irwin Pootlemeyer", Gender::other, 35567},
        {32, "Alexa Workwell", Gender::female, 35578},
        {42, "Steve Stove", Gender::male, 35589},
        {33, "Sue Neenuf", Gender::female, 35598},
        {29, "Melanie Clair", Gender::female, 35667},
    };

    for (const auto& executive : executives)
    {
        executive.who();
        executive.Employee::who();
    }
}