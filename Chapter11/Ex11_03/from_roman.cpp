//from_roman.cpp
module roman;

unsigned from_roman(char c)
{
	switch (c)
	{
		case 'I': return 1;
		case 'V': return 5;
		case 'X': return 10;
		case 'L': return 50;
		case 'C': return 100;
		case 'D': return 500;
		case 'M': return 1000;
		default: return 0;
	}
}

unsigned from_roman(std::string_view roman)
{
	unsigned result{};
	const auto n{roman.length()};
	for (size_t i{};i < n;++i)
	{
		const auto j{ from_roman(roman[i]) };
		if (i + 1 == n || j >= from_roman(roman[i + 1]))
			result += j;
		else
			result -= j;
	}

	return result;
}