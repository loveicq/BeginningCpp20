// Exer12_07.cpp
/*************************第12章_练习_第7题************************\
修改第6题的Package类，使其包含另外一个指针，指向链表中的前一个对象。这就
创建了所谓的“双向链表”，相应地，之前使用的数据结构称为“单向链表”。修改
Package、Truckload和Iterator类来使用这个新指针，包括提供反向遍历链表中
Box对象的能力，以及以相反顺序列出Truckload中Box对象的能力。设计一个
main()函数来演示新功能。
\*****************************************************************/
import box.random;
import truckload;
import <iostream>;

SharedBox findLargestBox(const Truckload& truckload);
SharedBox findSmallestBox(const Truckload& truckload);

int main()
{
    Truckload load;

    const size_t boxCount{12};
    for (size_t i{}; i < boxCount; ++i)
        load.addBox(randomSharedBox());

    std::cout << "The random truckload:\n";
    load.listBoxes();
    std::cout << std::endl;

    std::cout << "The same random truckload in reverse:\n";
    load.listBoxesReversed();
    std::cout << std::endl;

    std::cout << "The largest box (found using forward iteration) is ";
    findLargestBox(load)->listBox();
    std::cout << std::endl;

    std::cout << "The smallest box(found using reverse iteration) is ";
    findSmallestBox(load)->listBox();
    std::cout << std::endl;
}

SharedBox findLargestBox(const Truckload& truckload)
{
    auto iterator{truckload.getIterator()};
    SharedBox largestBox{iterator.getFirstBox()};

    SharedBox nextBox{iterator.getNextBox()};
    while (nextBox)
    {
        if (nextBox->compare(*largestBox) > 0)
            largestBox = nextBox;
        nextBox = iterator.getNextBox();
    }

    return largestBox;
}

SharedBox findSmallestBox(const Truckload& truckload)
{
    auto iterator{truckload.getIterator()};
    SharedBox smallestBox{iterator.getLastBox()};

    SharedBox nextBox{iterator.getPreviousBox()};
    while (nextBox)
    {
        if (nextBox->compare(*smallestBox) < 0)
            smallestBox = nextBox;
        nextBox = iterator.getPreviousBox();
    }

    return smallestBox;
}