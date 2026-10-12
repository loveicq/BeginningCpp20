// Person.cppm
export module person;
import <string>;
import <string_view>;

export enum class Gender { male,
                           female,
                           other };

export class Person
{
public:
    Person() = default;
    Person(size_t age, std::string_view name, Gender gender);

    void who() const;
    void haveBirthday();

protected:
    size_t getAge() const { return m_age; }
    const std::string& getName() const { return m_name; } // 因为是&引用，前面的const是防止修改返回值（成员变量m_name）
    Gender getGender() const { return m_gender; }

    std::string_view getGenderString() const;

private:
    std::string m_name;
    size_t m_age{};
    Gender m_gender{Gender::female};
};

export class Employee : public Person
{
public:
    Employee() = default;
    Employee(size_t age, std::string_view name, Gender gender, long num)
        : Person{age, name, gender}, m_personnelNumber{num} {}

    void who() const;

protected:
    long getPersonnelNumber() { return m_personnelNumber; }

private:
    long m_personnelNumber{};
};

export class Executive : public Employee
{
public:
    using Employee::Employee;

    void who() const;
};