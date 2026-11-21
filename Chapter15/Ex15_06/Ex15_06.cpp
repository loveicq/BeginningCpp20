// Ex15_06.cpp
import <iostream>;
import boxes;
import <memory>;
import <vector>;

int main()
{
    std::vector<Box> boxes;
    boxes.push_back(Box{20.0, 30.0, 40.0});
    boxes.push_back(Carton{20.0, 30.0, 40.0, "plastic"});
    boxes.push_back(ToughPack{20.0, 30.0, 40.0});

    for (const auto& box : boxes)
        box.showVolume();

    std::cout << std::endl;

    std::vector<std::unique_ptr<Box>> polymorphicBoxes;
    polymorphicBoxes.push_back(std::make_unique<Box>(20.0, 30.0, 40.0));
    polymorphicBoxes.push_back(std::make_unique<Carton>(20.0, 30.0, 40.0));
    polymorphicBoxes.push_back(std::make_unique<ToughPack>(20.0, 30.0, 40.0));

    for (const auto& box : polymorphicBoxes)
        box->showVolume();
}