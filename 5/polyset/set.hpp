#ifndef SET_HPP
#define SET_HPP

#include "searchable_bag.hpp"

class set
{
private:
	searchable_bag& sBag;
	set();
	set(const& set source);
	set& operator=(const& set other);

public:
	set(searchable_bag& other);
	~set();

	bool has (int) const;
	void insert (int);
	void insert (int *, int);
	void print() const;
	void clear();

	const searchable_bag& get_bag();

};

#endif