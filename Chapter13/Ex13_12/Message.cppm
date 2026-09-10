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

    Message& operator=(const Message& message);

    // Rule of Three(三法则)：如果需要自定义析构、拷贝构造、拷贝赋值中任意一个，那通常三个都需要！

    const char* getText() const { return m_text; }

private:
    char* m_text;
};