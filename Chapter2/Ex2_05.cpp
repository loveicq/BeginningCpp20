// Ex2_05.cpp
//  The width,alignment,fill,and 0 formatting options of format()
#include <iostream>
#include <format>
using std::cout;
using std::endl;
using std::format;

int main()
{
    // Default alignment:right for numbers,left otherwise
    cout << format("{:7}|{:7}|{:7}|{:7}|{:7}\n", 1, -0.2, "str", 'c', true);
    // left and right alignment + custom fill character
    cout << format("{:*<7}|{:*<7}|{:*>7}|{:*>7}|{:*>7}\n", 1, -0.2, "str", 'c', true);
    // centered alignment +0 formatting option for numbers
    cout << format("{:0^7}|{:0^7}|{:^7}|{:^7}|{:^7}\n", 1, -0.2, "str", 'c', true);

    return 0;
}
