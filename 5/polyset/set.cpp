#include "set.hpp"

set::set(searchable_bag& other) : sBag(other)
{
}

set::~set()
{
}

bool set::has(int value) const
{
	return (sBag.has(value));
}

void set::insert(int value)
{
	if (!(this->has(value)))
		sBag.insert(value);
}

void set::insert(int *data, int size)
{
	for (int i = 0; i < size; ++i)
		insert(data[i]);
}

void set::print() const
{
	sBag.print();
}

void set::clear()
{
	sBag.clear();
}

const searchable_bag set::get_bag() { return(this->sBag); }