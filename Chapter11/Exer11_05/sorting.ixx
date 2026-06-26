//sorting.ixx
export module words:sorting;

import :alias;
import:internals;

export namespace words
{
	void sort(Words& words);
}

namespace words
{
	void sort(Words& words, size_t start, size_t end);
}

void words::sort(Words& words)
{
	if (!words.empty())
		sort(words, 0, words.size() - 1);
}

void words::sort(Words& words, size_t start, size_t end)
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