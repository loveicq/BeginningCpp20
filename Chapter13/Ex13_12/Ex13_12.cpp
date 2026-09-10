// Ex13_12.cpp
import message;
import <iostream>;

int main()
{
    Message beware{"Careful"};
    Message warning;

    warning = beware;

    std::cout << "After assignment beware is: " << beware.getText() << std::endl;
    std::cout << "After assignment warning is: " << warning.getText() << std::endl;
}