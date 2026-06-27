//from_roman.cpp
module roman;
import :internals;

unsigned int from_roman(std::string_view roman)
{
    unsigned int result{};
    for (size_t i{}, n{ roman.length() }; i < n; ++i)
    {
        const auto j{ from_roman(roman[i]) }; 
        if (i + 1 == n || j >= from_roman(roman[i + 1])) result += j; else result -= j;
    }
    return result;
}