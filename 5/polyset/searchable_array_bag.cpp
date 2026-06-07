#include "searchable_array_bag.hpp"

searchable_array_bag::searchable_array_bag()
{
}

searchable_array_bag::searchable_array_bag(const& searchable_array_bag other) : tree_bag(other)
{
}

searchable_array_bag& searchable_array_bag::operator=(const& searchable_array_bag other)
{
	if (this != &other)
	{
		array_bag::operator=(other);
	}
}

~searchable_array_bag()
{
}

bool has(int value)
{
	for (int i = 0; i < size; ++i)
	{
		if (data[i] == value)
			return true;
	}
	return false;
}
