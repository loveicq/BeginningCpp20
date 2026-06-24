module words.sorting;

void swap(words::Words& words, size_t first, size_t second)
{
	auto temp{ words[first] };
	words[first] = words[second];
	words[second] = temp;
}

void sort(words::Words& words, size_t start, size_t end);

void words::sorting::sort(Words& words)
{
	if (!words.empty())
		::sort(words, 0, words.size() - 1);
}

void sort(words::Words& words, size_t start, size_t end)
{
	if (!(start < end))
		return;

	swap(words, start, (start + end) / 2); 

	size_t current{ start };
	for (size_t i{ start + 1 }; i <= end; i++)
	{
		if (*words[i] < *words[start]) 
			swap(words, ++current, i); 
	}

	swap(words, start, current);  

	if (current > start) sort(words, start, current - 1); 
	if (end > current + 1) sort(words, current + 1, end); 
}