// linkedList.cppm
export module linkedList;

import node;
import <memory>;

export class LinkedList
{
public:
    LinkedList() : m_head{nullptr} {}

    void push_front(int value);
    void pop_front();
    void print() const;
    bool empty() const { return m_head== nullptr; }

private:
    std::unique_ptr<Node> m_head;
};