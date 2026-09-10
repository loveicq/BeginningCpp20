// Message.cpp
module;
#include <cstring>
module message;

Message& Message::operator=(const Message& message)
{
    if (&message != this) {
        delete[] m_text; // 因后一句重新赋值给m_text，此处先delete[]是释放堆内存，防止内存泄漏
        m_text = new char[std::strlen(message.m_text) + 1];
        std::strcpy(m_text, message.m_text);
    }
    return *this;
}