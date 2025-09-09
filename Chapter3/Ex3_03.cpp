#include <iostream>
#include <format>

int main()
{
    using namespace std;

    enum class Day
    {
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    };
    Day yesterday{Day::Monday}, today{Day::Tuesday}, tomorrow{Day::Wednesday};
    const Day poets_day{Day::Friday};
    enum class Punctuation : char
    {
        Comma = ',',
        Exclamation = '!',
        Question = '?'
    };
    Punctuation ch{Punctuation::Comma};
    cout << format("yesterday's value is {}{} but poets_day's is {}{}\n",
                   static_cast<int>(yesterday), static_cast<char>(ch),
                   static_cast<int>(poets_day), static_cast<char>(Punctuation::Exclamation));

    today = Day::Thursday;      // assign new...
    ch = Punctuation::Question; //...enumerator values
    tomorrow = poets_day;

    cout << format("Is today's value({}) the same as poets_day({}){}\n",
                   static_cast<int>(today), static_cast<int>(tomorrow), static_cast<char>(ch));
    // ch = tomorrow;     /*不能将 "Day" 类型的值分配到 "Punctuation" 类型的实体C/C++(513)*/
    // tomorrow = Friday; /*未定义标识符 "Friday"C/C++(20)*/
    // today = 6;         /*不能将 "int" 类型的值分配到 "Day" 类型的实体C/C++(513)*/

    return 0;
}