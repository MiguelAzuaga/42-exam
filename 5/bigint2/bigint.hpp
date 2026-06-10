#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <string>
#include <iostream>

class bigint
{
private:
	std::string _str;

public:
	bigint();
	bigint(const bigint& other);
	bigint(unsigned int n);
	bigint& operator=(const bigint& other);
	~bigint();

	bigint operator+(const bigint& other) const;
	bigint& operator+=(const bigint& other);

	bigint& operator++();
	bigint operator++(int);

	bigint operator<<(unsigned int n) const;
	bigint operator>>(unsigned int n) const;
	bigint& operator<<=(unsigned int n);
	bigint& operator>>=(unsigned int n);

	bigint operator<<(const bigint& other) const;
	bigint operator>>(const bigint& other) const;
	bigint& operator<<=(const bigint& other);
	bigint& operator>>=(const bigint& other);

	bool operator==(const bigint& other) const;
	bool operator!=(const bigint& other) const;
	bool operator<(const bigint& other) const;
	bool operator>(const bigint& other) const;
	bool operator<=(const bigint& other) const;
	bool operator>=(const bigint& other) const;

	const std::string get_str() const;
};

std::ostream& operator<<(std::ostream& out, const bigint& in);

#endif