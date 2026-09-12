// Message.cpp
module message;
import <utility>; // For std::swap()

Message::Message(const Message& message)
    : Message{message.m_text} {} // 委托构造函数

Message& Message::operator=(const Message& message)
{
    auto copy{message}; // ① 用拷贝构造做一份副本（深拷贝，分配新内存）
    swap(copy);         // ② 和自己交换（只交换指针，零内存操作）
    return *this;
} // ③ copy 离开作用域自动析构，带走原来的旧内存

void Message::swap(Message& other) noexcept
{
    std::swap(m_text, other.m_text); // 只交换指针！不分配/不释放内存
}