// Exer12_04.cpp
/*************************第12章_练习_第4题************************\
修改第2题的解决方案，把compare()函数实现为类Integer在友元函数。然后，
思考是否真的有必要将这个函数实现为友元函数。
\*****************************************************************/
import integer;
import <iostream>;

int main()
{
    std::cout << "Create i with the value 10." << std::endl;
    Integer i{10};
    i.show();
    std::cout << "Change value of i to 15." << std::endl;
    i.setValue(15);
    i.show();

    std::cout << "Create j from object i." << std::endl;
    Integer j{i};
    j.show();
    std::cout << "Set value of j to 150 times that of i." << std::endl;
    j.setValue(150 * i.getValue());
    j.show();

    std::cout << "Create k with the value 789." << std::endl;
    Integer k{789};
    k.show();
    std::cout << "Set value of k to sum of i and j values." << std::endl;
    k.setValue(i.getValue() + j.getValue());
    k.show();

    std::cout << "Result of FriendComparing i and j is " << compare(i, j) << std::endl;
    std::cout << "Result of FriendComparing k and j is " << compare(k, j) << std::endl;

    std::cout << "Result of nonFriendComparing i and j is " << nonFriendCompare(i, j) << std::endl;
    std::cout << "Result of nonFriendComparing k and j is " << nonFriendCompare(k, j) << std::endl;
}