// Ingeter.cppm
export module integer;

// Option 1: zero-initialize n and add a default constructor
export class Integer
{
public:
    Integer() = default;         // Zero-arg constructor
    Integer(int value);          // Constructor with given value
    Integer(const Integer &obj); // Copy constructor

    int getValue() const { return m_value; }
    void setValue(int value) { m_value = value; }

    // int compare(Integer obj) const;  //Compare function with value parameter
    int compare(const Integer &obj) const; // Compare function with reference parameter

    void show() const;

private:
    int m_value{};
};

// Option 2: use zero a default parameter value

/* export class Integer
{
public:
    Integer(int value = 0);      // Constructor with given value
    Integer(const Integer &obj); // Copy constructor

    int getValue() const { return m_value; }
    void setValue(int value) { m_value = value; }

    // int compare(Ingeter obj) const;  //Compare function with value parameter
    int compare(const Integer &obj) const; // Compare function with reference parameter

    void show() const;

private:
    int m_value;
}; */
