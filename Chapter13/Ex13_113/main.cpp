// main.cpp
import linkedList;

int main()
{
    LinkedList list;

    list.push_front(10);
    list.push_front(20);
    list.push_front(30);
    list.print();

    list.pop_front();
    list.print();
}