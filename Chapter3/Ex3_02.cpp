#include <iostream>
long count1{999L};
double count2{3.14};
int count3;

int main()
{
    using namespace std;

    int count1{10};
    int count3{50};
    cout << "Value of outer count1 = " << count1 << endl;
    cout << "Value of global count1 = " << ::count1 << endl;
    cout << "Value of global count2 = " << count2 << endl;

    {
        int count1{20};
        int count2{30};
        cout << "\nValue of inner count1 = " << count1 << endl;
        cout << "Value of global count1 = " << ::count1 << endl;
        cout << "Value of inner count2 = " << count2 << endl;
        cout << "Value of global count2 = " << ::count2 << endl;

        count1 = ::count1 + 3;
        ++::count1;
        cout << "\nValue of inner count1 = " << count1 << endl;
        cout << "Value of global count1 = " << ::count1 << endl;
        count3 += count2;
        int count4{};
    }
    // cout<<count4<<endl;//此句显示"未定义标识符"
    cout << "\nValue of outer count1 = " << count1 << endl
         << "Value of outer count3 = " << count3 << endl; // 上面花括号也属于main()范围,所以count3是局部变量
    cout << "Value of global count3 = " << ::count3 << endl;

    cout << "Value of global count2 = " << count2 << endl; // count2局部变量定义在上面花括号内,作用域在右花括号处即结束了,所以此处是全局变量的count2.

    return 0;
}