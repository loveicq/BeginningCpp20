// Ex14_05.cpp
import carton;
import <iostream>;

int main() {
    Carton cart;
    Carton cube{4.0};
    Carton copy{cube}; // 编译器隐式生成的副本构造函数，没有输出语句
    Carton carton{1.0, 2.0, 3.0};
    Carton cerealCarton(50.0, 30.0, 20.0, "Chipboard");
}