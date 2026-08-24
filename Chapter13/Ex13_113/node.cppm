// node.cppm
export module node;

import <memory>;

export class Node
{
public:
    explicit Node(int value) : m_data{value}, m_next{nullptr} {}

    int getData() const { return m_data; }
    void setNext(std::unique_ptr<Node>&& newNode) { m_next = std::move(newNode); }
    Node* getNext() const { return m_next.get(); }
    std::unique_ptr<Node> takeNext() { return std::move(m_next); }

private:
    int m_data{};
    std::unique_ptr<Node> m_next{};
};