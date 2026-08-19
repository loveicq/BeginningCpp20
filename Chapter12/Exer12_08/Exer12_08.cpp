// Exer12_08.cpp
/*************************第12章_练习_第8题************************\
认真分析示例Ex12_17（以及示例Ex12_18和前面两个练习题）中的main()函数，
会发现下面的性能缺陷：要移除最大的Box对象，我们需要对链表执行两次线性遍历。
首先，找到最大的Box对象，然后在removeBox()内找到要取消链接的Package对象。
以第7题的Tterator类为基础，设计一种解决方案来避免第二次遍历。
提示一下，解决方案依赖于具有如下签名的成员函数：
bool removeBox(Iterator iterator);
\*****************************************************************/
import box.random;
import truckload;
import <iostream>;

Truckload::Iterator findLargestBox(const Truckload& truckload);
Truckload::Iterator findSmallestBox(const Truckload& truckload);

int main()
{
    Truckload load;

    const size_t boxCount{12};
    for (size_t i{}; i < boxCount; ++i)
        load.addBox(randomSharedBox());

    std::cout << "The random truckload:\n";
    load.listBoxes();
    std::cout << std::endl;

    const auto largestIter{findLargestBox(load)};
    const auto smallestIter{findSmallestBox(load)};

    std::cout << "The largest box(found using forward iteration) is ";
    largestIter.getCurrentBox()->listBox();
    std::cout << '\n'
              << std::endl;

    load.removeBox(largestIter);

    std::cout << "The truckload without its largest box:\n";
    load.listBoxes();
    std::cout << std::endl;

    std::cout << "The smallest box (found using reverse iteration) is ";
    smallestIter.getCurrentBox()->listBox();
    std::cout << '\n'
              << std::endl;

    load.removeBox(smallestIter);

    std::cout << "The truckload without its smallest box (in reverse order):\n";
    load.listBoxesReversed();
}

Truckload::Iterator findLargestBox(const Truckload& truckload)
{
    auto iterator{truckload.getIterator()};
    iterator.getFirstBox();
    auto largestBoxIterator{iterator};

    while (iterator.getNextBox())
    {
        if (iterator.getCurrentBox()->compare(*largestBoxIterator.getCurrentBox()) > 0)
            largestBoxIterator = iterator;
    }
    return largestBoxIterator;
}

Truckload::Iterator findSmallestBox(const Truckload& truckload)
{
    auto iterator{truckload.getIterator()};
    iterator.getLastBox();
    auto smallestBoxIterator{iterator};

    while (iterator.getPreviousBox())
    {
        if (iterator.getCurrentBox()->compare(*smallestBoxIterator.getCurrentBox()) < 0)
            smallestBoxIterator = iterator;
    }

    return smallestBoxIterator;
}