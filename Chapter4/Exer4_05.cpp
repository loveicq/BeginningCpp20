#include <iostream>

int main()
{
    int mice;
    int whiteMouse;
    int brownMouse;

    std::cout << "How many white mice do you have? : ";
    std::cin >> whiteMouse;
    std::cout << "How many brown mice do you have? : ";
    std::cin >> brownMouse;

    if (whiteMouse < 0 || brownMouse < 0)
    {
        std::cout << "One cannot have a negative amount of mice..." << std::endl;
        return 1;
    }

    mice = whiteMouse + brownMouse;

    std::cout << "You have " << mice << (mice == 1 || mice == 0 ? " mouse." : " mice.") << std::endl;

    if (mice == 1)
    {
        std::cout << "It is a " << (brownMouse ? "brown " : "white ") << "mouse." << std::endl;
        return 0;
    }

    if (brownMouse)
    {
        std::cout << "Of these mice, "
                  << brownMouse
                  << (brownMouse == 1 ? " is a brown" : " are brown")
                  << (brownMouse == 1 ? " mouse." : " mice.")
                  << std::endl;
    }
    else
        std::cout << "There is no brown mouse." << std::endl;
}