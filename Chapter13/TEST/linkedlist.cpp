// 注意：此代码需要 C++20 模块支持
// 编译命令示例（MSVC）： cl /std:c++20 /experimental:module /EHsc main.cpp
// GCC/Clang 需加 -fmodules-ts 并确保标准库模块已编译（视具体实现）

import <iostream>; // 替代 #include <iostream>
import <memory>;   // 替代 #include <memory>

// ---------- 节点类 ----------
class IntNode
{
private:
    int data;                      // 数据
    std::unique_ptr<IntNode> next; // 指向下一节点的智能指针

public:
    // 列表初始化构造函数：使用 {} 初始化成员
    explicit IntNode(int value) : data{value}, next{nullptr} {}

    // 只读访问数据
    int getData() const { return data; }

    // 设置下一节点（转移所有权）
    void setNext(std::unique_ptr<IntNode>&& newNext)
    {
        next = std::move(newNext);
    }

    // 获取下一节点的裸指针（仅供观察，不转移所有权）
    IntNode* getNext() const { return next.get(); }

    // 把 next 的所有权移交给调用者（用于删除头部）
    std::unique_ptr<IntNode> takeNext()
    {
        return std::move(next);
    }
};

// ---------- 链表类 ----------
class LinkedList
{
private:
    std::unique_ptr<IntNode> head; // 头节点

public:
    LinkedList() : head{nullptr} {}

    // 头部插入
    void push_front(int value)
    {
        // 使用 new + 列表初始化创建节点，然后交给 unique_ptr 管理
        auto new_node = std::unique_ptr<IntNode>(new IntNode{value});
        new_node->setNext(std::move(head)); // 新节点指向原头
        head = std::move(new_node);         // 更新头
    }

    // 删除头部
    void pop_front()
    {
        if (head)
        {
            head = head->takeNext(); // 头移到下一个，原头自动释放
        }
    }

    // 打印所有元素
    void print() const
    {
        const IntNode* current = head.get();
        while (current)
        {
            std::cout << current->getData() << " -> ";
            current = current->getNext();
        }
        std::cout << "nullptr\n";
    }

    bool empty() const
    {
        return head == nullptr;
    }
};

// ---------- 测试 ----------
int main()
{
    LinkedList list;

    list.push_front(10);
    list.push_front(20);
    list.push_front(30);
    list.print(); // 输出: 30 -> 20 -> 10 -> nullptr

    list.pop_front();
    list.print(); // 输出: 20 -> 10 -> nullptr

    return 0;
}