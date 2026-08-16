// Exer12_06.cpp
/*************************第12章_练习_第6题************************\
完成本章结尾处创建的嵌套的Truckload::Iterator类。以Ex12_18作为基础，
按照前面的示范将Iterator类添加到Truckload类的定义中，并实现其成员函数。
按照示范，使用Iterator类实现findLargestBox()函数（读者是否能够不看答案
就实现这个函数？），并修改Ex12——18的main()函数来使用新创建的这个函数。
对类似的findSmallestBox()函数进行类似的处理。
\*****************************************************************/
import <iostream>;
import box.random;
import truckload;

/*****************************************************************\
原来将getFirstBox()和getLastBox()函数移到嵌套的迭代器类中是很容易的。
我们复用了相同的成员变量名称，所以只需要将
Truckload::改为Truckload::Iterator::即可。

这很合理：遍历链表的逻辑并没有改变。唯一的区别是，现在每次迭代都有自己的
m_current和m_head指针，而不是Truckload对象中只有一对这样的指针。这支持
嵌套迭代、并发迭代等场景。你将在第19章和第20章再次遇到这种迭代器模式。

顺便提一句：如果你觉得我们的findLargestBox()和findSmallestBox()函数
过于相似（这似乎不够理想），别担心——在第19章我们将教你必要的技术来避免
这种所谓的代码重复。
\*****************************************************************/

SharedBox findLargestBox(const Truckload& truckload);
SharedBox findSmallestBox(const Truckload& truckload);

int main()
{
    Truckload load1;

    const size_t boxCount{12};
    for (size_t i{}; i < boxCount; ++i)
        load1.addBox(randomSharedBox());

    std::cout << "The first list:\n";
    load1.listBoxes();

    Truckload copy{load1};
    std::cout << "The copied truckload:\n";
    copy.listBoxes();

    const auto largestBox{findLargestBox(load1)};

    std::cout << "\nThe largest box in the first list is ";
    largestBox->listBox();
    std::cout << std::endl;
    load1.removeBox(largestBox);
    std::cout << "\nAfter deleting the largest box, the list contains:\n";
    load1.listBoxes();

    const size_t nBoxes{20};
    std::vector<SharedBox> boxes;

    for (size_t i{}; i < nBoxes; ++i)
        boxes.push_back(randomSharedBox());

    Truckload load2{boxes};
    std::cout << "\nThe second list:\n";
    load2.listBoxes();

    const auto smallestBox{findSmallestBox(load2)};

    std::cout << "\nThe smallest box in the second list is ";
    smallestBox->listBox();
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
    SharedBox smallestBox{iterator.getFirstBox()};

    SharedBox nextBox{iterator.getNextBox()};
    while (nextBox)
    {
        if (nextBox->compare(*smallestBox) < 0)
            smallestBox = nextBox;
        nextBox = iterator.getNextBox();
    }

    return smallestBox;
}