// Animals.cppm
export module animals;

import <iostream>;
import <string>;
import <string_view>;

export class Animal
{
public:
    Animal(std::string_view name, int weight)
        : m_name{name}, m_weight{weight} {}

    void who() const
    {
        std::cout << "My name is " << m_name << " and I weight " << m_weight << " lbs." << std::endl;
    }

private:
    std::string m_name;
    int m_weight;
};

export class Lion : public Animal
{
public:
    Lion(std::string_view name, int weight)
        : Animal{name, weight} {}

    void who() const
    {
        std::cout << "Rrroarrrr... I am a lion. " << std::endl;
        Animal::who();
    }
};

export class Aardvark : public Animal
{
public:
    using Animal::Animal;

    void who() const
    {
        Animal::who();
        std::cout << "Oh. And I'm an aardvark. " << std::endl;
    }
};