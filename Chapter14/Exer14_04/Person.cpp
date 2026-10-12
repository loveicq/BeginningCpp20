// Person.cpp

module person;
import <iostream>;

Person::Person(size_t age, std::string_view name, Gender gender)
    : m_age{age}, m_name{name}, m_gender{gender} {}

void Person::who() const
{
    std::cout << "\nThis is " << m_name << " who is " << m_age << " years old." << std::endl;
}

void Person::haveBirthday()
{
    ++m_age;
}

std::string_view Person::getGenderString() const
{
    switch (m_gender)
    {
    case Gender::male  : return "a male";
    case Gender::female: return "a female";
    case Gender::other : return "an other-gendered";
    }

    return {};
}

void Employee::who() const
{
    std::cout << getName() << " is " << getGenderString() << " employee aged " << getAge() << "." << std::endl;
}

void Executive::who() const
{
    std::cout << getName() << " is " << getGenderString() << " executive." << std::endl;
}