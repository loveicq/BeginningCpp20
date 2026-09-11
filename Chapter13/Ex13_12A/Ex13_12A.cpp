// Ex13_12A.cpp
import message;
import <iostream>;

int main()
{
    Message beware{"Careful"};
    Message warning;

    warning = beware;

    Message caution{warning};

    std::cout << "After assignment beware is: " << beware.getText() << std::endl;
    std::cout << "After assignment warning is: " << warning.getText() << std::endl;
    std::cout << "As a copy of warning, caution is: " << caution.getText() << std::endl;
}