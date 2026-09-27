// Ex14_04A.cpp
import carton;
import <iostream>;

int main()
{
    Carton carton1; // error C2280: “Carton::Carton(void) noexcept(false)”: 尝试引用已删除的函数
    std::cout << std::endl;
    Carton carton2{4.0, 5.0, 6.0, "PET"};
    std::cout << std::endl;
    Carton carton3{2.0, "Folding boxboard"};
    std::cout << std::endl;

    std::cout << "carton1 volume is " << carton1.volume() << std::endl;
    std::cout << "carton2 volume is " << carton2.volume() << std::endl;
    std::cout << "carton3 volume is " << carton3.volume() << std::endl;
}