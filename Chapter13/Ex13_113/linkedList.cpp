// linkedList.cpp
module linkedList;

import <iostream>;

void LinkedList::push_front(int value)
{
    auto new_node = std::unique_ptr<Node>(new Node{value});
    new_node->setNext(std::move(m_head));
    m_head = std::move(new_node);
}

void LinkedList::pop_front()
{
    if (m_head)
        m_head = m_head->takeNext();
}

void LinkedList::print() const
{
    auto current = m_head.get();
    while (current)
    {
        std::cout << current->getData() << " -> ";
        current = current->getNext();
    }
    std::cout << "nullptr\n";
}