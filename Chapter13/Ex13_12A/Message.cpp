// Message.cpp
module;
#include <cstring>
module message;

Message::Message(const Message& message)
    : Message{message.m_text} {} // 委托构造函数，message.m_text数据类型即char*指针

Message& Message::operator=(const Message& message)
{
    if (&message != this) {
        delete[] m_text;
        m_text = new char[std::strlen(message.m_text) + 1];
        std::strcpy(m_text, message.m_text);
    }
    return *this;
}