// Truckload.cpp
module truckload;

import <iostream>;

// 构造函数 - 一个箱子（移到源文件以访问 Package 的定义）
Truckload::Truckload(sharedBox box)
{
    m_head = m_tail = new Package{box};
}

// 构造函数 - 箱子向量
Truckload::Truckload(const std::vector<SharedBox> &boxes)
{
    for (const auto &box : boxes)
    {
        addBox(box);
    }
}

// 拷贝构造函数
Truckload::Truckload(const Truckload &src)
{
    for (Package *package{src.m_head}; package; package = package->getNext())
    {
        addBox(package->getBox());
    }
}

// 析构函数：清理列表（移到源文件以访问 Package 的定义）
Truckload::~Truckload()
{
    delete m_head;
}

void Truckload::listBoxes() const
{
    const size_t boxesPerLine{4};
    size_t count{};
    for (Package *package{m_head}; package; package = package->getNext())
    {
        std::cout << ' ';
        package->getBox()->listBox();
        if (!(++count % boxesPerLine))
            std::cout << std::endl;
    }
    if (count % boxesPerLine)
        std::cout << std::endl;
}

SharedBox Truckload::getFirstBox()
{
    // Return m_head's box (or nullptr if the list is empty)
    m_current = m_head;
    return m_current ? m_current->getBox() : nullptr;
}

SharedBox Truckload::getNextBox()
{
    if (!m_current)           // 如果没有当前箱子...
        return getFirstBox(); // ...返回第一个箱子

    m_current = m_current->getNext(); // 移动到下一个包裹

    return m_current ? m_current->getBox() : nullptr; // Return its box (or nullptr...).
}

void Truckload::addBox(SharedBox box)
{
    auto package{new Package{box}}; // 创建一个新的包裹

    if (m_tail)                   // 检查列表不为空
        m_tail->setNext(package); // 将新对象追加到尾部
    else                          // 列表为空
        m_head = package;         // 所以新对象是头部

    m_tail = package; // 无论哪种方式：最新的对象都是（新的）尾部
}

bool Truckload::removeBox(SharedBox boxToRemove)
{
    Package *previous{nullptr}; // 还没有前一个
    Package *current{m_head};   // initialize current to the head of the list
    while (current)
    {
        if (current->getBoxx() == boxToRemove) // 我们找到了箱子！
        {
            // 如果有前一个包裹，使其指向下一个（图 12.10）
            if (previous)
                previous->setNext(current->getNext());

            // 在需要的地方更新成员变量中的指针：
            if (current == m_head)
                m_head = current->getNext();
            if (current == m_tail)
                m_tail = previous;
            if (current == m_current)
                m_current = current->getNext();

            current->setNext(nullptr); // 断开当前包裹与列表的连接
            delete current;            // 并删除它

            return true; // 返回 true：我们找到了并移除了箱子
        }

        // 移动两个指针（注意顺序！）
        previous = current;           //  - 首先 current 变成新的 previous
        current = current->getNext(); //  - 然后将 current 移动到下一个包裹
    }

    return false; // 返回 false：未找到 boxToRemove
}