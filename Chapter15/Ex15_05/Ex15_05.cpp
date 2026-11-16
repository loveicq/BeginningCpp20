// Ex15_05.cpp
import <iostream>;
import boxes;

void showVolume(const Box& box) // 如果去掉引用&，则输出结果均为24000
{
    std::cout << "Box usable volume is " << box.volume() << std::endl;
}

int main()
{
    Box box{20.0, 30.0, 40.0};
    ToughPack hardcase{20.0, 30.0, 40.0};
    Carton carton{20.0, 30.0, 40.0, "Plastic"};

    showVolume(box);
    showVolume(hardcase);
    showVolume(carton);
}