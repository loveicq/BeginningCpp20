// Ex2_04.cpp
// Using explicit type conversions
#include <iostream>
int main()
{
    using namespace std;
    const unsigned feet_per_yard{3};
    const unsigned inches_per_foot{12};
    const unsigned inches_per_yard{feet_per_yard * inches_per_foot};
    double length{};
    unsigned int yards{};
    unsigned int feet{};
    unsigned int inches{};

    cout << "Enter a length in yards as a decimal: ";
    cin >> length;

    yards = static_cast<unsigned int>(length);
    feet = static_cast<unsigned int>((length - yards) * feet_per_yard);
    // 总英寸数与inches_per_foot取模（除以12取余数）即是英寸数
    inches = static_cast<unsigned int>(length * inches_per_yard) % inches_per_foot;

    cout << length << " yards converts to "
         << yards << " yards "
         << feet << " feet "
         << inches << " inches." << endl;

    return 0;
}