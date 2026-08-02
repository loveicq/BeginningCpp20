// Ex12_17.cpp
// 使用链表管理卡车上的箱子
import box.random;
import truckload;
import <iostream>;
import <vector>;

int main()
{
    Truckload load1;                // 创建一个空的卡车装载列表

    // 向列表中添加 12 个随机 Box 对象
    const size_t boxCount{12};
    for (size_t i{}; i < boxCount; ++i)
        load1.addBox(randomSharedBox());

    std::cout << "The first list:\n";
    load1.listBoxes();

    // 拷贝整个卡车装载
    Truckload copy{load1};
    std::cout << "The copied truckload:\n";
    copy.listBoxes();

    // 寻找最大的箱子
    SharedBox largestBox{load1.getFirstBox()};
    SharedBox nextBox{load1.getNextBox()};
    while (nextBox)
    {
        if (nextBox->compare(*largestBox) > 0)   // 调用 Box::compare
            largestBox = nextBox;
        nextBox = load1.getNextBox();
    }

    std::cout << "\nThe largest box in the first list is ";
    largestBox->listBox();
    std::cout << std::endl;

    load1.removeBox(largestBox);
    std::cout << "\nAfter deleting the largest box, the list contains:\n";
    load1.listBoxes();

    // 用 std::vector 初始化第二个装载
    const size_t nBoxes{20};
    std::vector<SharedBox> boxes;
    for (size_t i{}; i < nBoxes; ++i)
        boxes.push_back(randomSharedBox());

    Truckload load2{boxes};
    std::cout << "\nThe second list:\n";
    load2.listBoxes();

    // 寻找最小的箱子
    auto smallestBox{load2.getFirstBox()};
    for (auto box{load2.getNextBox()}; box; box = load2.getNextBox())
        if (box->compare(*smallestBox) < 0)
            smallestBox = box;

    std::cout << "\nThe smallest box in the second list is ";
    smallestBox->listBox();
    std::cout << std::endl;
}