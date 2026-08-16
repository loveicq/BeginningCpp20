// Integer.cppm
export module integer;

export class Integer
{
public:
    Integer(int value = 0);
    Integer(const Integer& obj);
    ~Integer();

    int getValue() const { return m_value; }
    void setValue(int value) { m_value = value; }

    int compare(const Integer& obj) const;

    void show() const;

    static void printCount();
    // 静态成员函数的本质是「没有this指针的成员函数」——它不依赖任何对象实例
    // 静态成员函数可以在类的作用域，用类名::函数名调用，如Integer::printCount();

private:
    int m_value;

    static inline unsigned int s_count{};
};