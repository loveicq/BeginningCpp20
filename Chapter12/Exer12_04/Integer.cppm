// Integer.cppm
export module integer;

export class Integer
{
public:
    Integer(int value = 0);
    Integer(const Integer& obj);

    int getValue() const { return m_value; }
    void setValue(int value) { m_value = value; }

    void show() const;

    friend int compare(const Integer& obj1, const Integer& obj2);

private:
    int m_value;
};

export int nonFriendCompare(const Integer& obj1, const Integer& obj2);