// Ex15_04.cppm
import boxes;
import <iostream>;

int main()
{
    Box box{20.0, 30.0, 40.0};
    Carton carton{20.0, 30.0, 40.0, "Plastic"};
    ToughPack hardcase{20.0, 30.0, 40.0};

    box.showVolume();
    carton.showVolume();
    hardcase.showVolume();

    std::cout << "\nhardcase volume is " << hardcase.volume() << std::endl;

    Box* base{&box};
    std::cout << "\nbox volume through base pointer is " << base->volume() << std::endl;
    base->showVolume();

    base = &carton;
    std::cout << "carton volume through base pointer is " << base->volume() << std::endl;
    base->showVolume();

    base = &hardcase;
    std::cout << "hardcase volume through base pointer is " << base->volume() << std::endl;
    base->showVolume();
}