// Message.cppm
module;
#include <cstring>

export module message;

export class Message
{
public:
    explicit Message(const char* text = "")
        : m_text{new char[std::strlen(text) + 1]}
    {
        std::strcpy(m_text, text);
    }

    ~Message() { delete[] m_text; }

    Message(const Message& message); // 副本构造函数
    Message& operator=(const Message& message);

    const char* getText() const { return m_text; }

private:
    char* m_text;
};