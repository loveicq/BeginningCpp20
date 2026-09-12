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

    Message(const Message& message);
    Message& operator=(const Message& message);

    void swap(Message& other) noexcept;

    const char* getText() const { return m_text; }

private:
    char* m_text{nullptr};
};

export void swap(Message& one, Message& other) noexcept // 此程序没调用此函数，但是类完整设计的一部分，所以应该加上它
{
    return one.swap(other);
}