// Truckload.cpp
module truckload;          // 模块实现单元（无 export）

import <iostream>;
import <format>;

// 链表节点类：模块内部使用，外界不可见
class Package
{
public:
    Package(SharedBox box) : m_box{ box }, m_next{ nullptr } {}
    ~Package() { delete m_next; }   // 递归删除后续节点，实现整条链表清理

    SharedBox getBox() const { return m_box; }   // 获取本节点箱子
    Package* getNext() { return m_next; }        // 获取下一节点地址
    void setNext(Package* package) { m_next = package; }

private:
    SharedBox m_box;      // 指向共享 Box 的智能指针
    Package* m_next;      // 原生指针指向下一个节点
};

// --- Truckload 成员函数实现 ---

// 构造函数：创建一个只包含一个箱子的链表
Truckload::Truckload(SharedBox box)
{
    m_head = m_tail = new Package{ box };
}

// 构造函数：从 shared_ptr 向量批量添加
Truckload::Truckload(const std::vector<SharedBox>& boxes)
{
    for (const auto& box : boxes)
        addBox(box);
}

// 拷贝构造函数：遍历源链表，逐个添加箱子（深拷贝）
Truckload::Truckload(const Truckload& src)
{
    for (Package* package{ src.m_head }; package; package = package->getNext())
    {
        addBox(package->getBox());
    }
}

// 析构函数：只需删除头节点，Package 的析构函数会递归清理整个链表
Truckload::~Truckload()
{
    delete m_head;
}

void Truckload::listBoxes() const
{
    const size_t boxesPerLine{ 4 };    // 每行打印 4 个箱子
    size_t count{};
    for (Package* package{ m_head }; package; package = package->getNext())
    {
        std::cout << ' ';
        package->getBox()->listBox();   // 调用 Box 的格式化输出
        if (!(++count % boxesPerLine))  // 满 4 个换行
            std::cout << std::endl;
    }
    if (count % boxesPerLine)           // 最后一行不足 4 个也换行
        std::cout << std::endl;
}

SharedBox Truckload::getFirstBox()
{
    // 将当前遍历指针设为链表头，并返回其箱子（或空链表则返回 nullptr）
    m_current = m_head;
    return m_current ? m_current->getBox() : nullptr;
}

SharedBox Truckload::getNextBox()
{
    if (!m_current)               // 若当前指针为空，从头开始
        return getFirstBox();

    m_current = m_current->getNext();  // 移动到下一节点
    return m_current ? m_current->getBox() : nullptr;
}

void Truckload::addBox(SharedBox box)
{
    auto package{ new Package{box} };   // 创建新节点

    if (m_tail)                       // 链表非空
        m_tail->setNext(package);     // 将新节点挂到尾节点之后
    else                              // 链表为空
        m_head = package;             // 新节点成为头节点

    m_tail = package;                 // 更新尾节点
}

bool Truckload::removeBox(SharedBox boxToRemove)
{
    Package* previous{ nullptr };       // 跟踪前驱节点
    Package* current{ m_head };        // 从头开始搜索

    while (current)
    {
        if (current->getBox() == boxToRemove)   // 找到目标箱子
        {
            // 调整前驱节点的 next 指针，绕过当前节点
            if (previous)
                previous->setNext(current->getNext());

            // 更新头、尾、当前指针（如果它们指向被删除的节点）
            if (current == m_head)
                m_head = current->getNext();
            if (current == m_tail)
                m_tail = previous;
            if (current == m_current)
                m_current = current->getNext();

            current->setNext(nullptr);   // 断开与被删除节点的连接
            delete current;              // 删除节点（仅此一个，不递归删除后续）
            return true;
        }

        // 未找到，继续向后移动
        previous = current;
        current = current->getNext();
    }
    return false;   // 未找到
}