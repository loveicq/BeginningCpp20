// Ex15_02.cpp
import <iostream>;
import boxes;

int main()
{
    Box box{20.0, 30.0, 40.0};
    ToughPack hardcase{20.0, 30.0, 40.0};
    Carton carton{20.0, 30.0, 40.0, "Plastic"};

    box.showVolume();
    hardcase.showVolume();
    carton.showVolume();

    Box* base{&box};
    std::cout << "\nbox volume through base pointer is " << base->volume() << std::endl;
    base->showVolume();

    base = &hardcase;
    std::cout << "hardcase volume through base pointer is " << base->volume() << std::endl;
    base->showVolume();

    base = &carton;
    std::cout << "carton volume through base pointer is " << base->volume() << std::endl;
    base->showVolume();
}