#include <sstream>
#include <algorithm>
#include "bigint.hpp"

static std::string uitoa(unsigned int n)
{
	std::stringstream ss;

	ss << n;
	return (ss.str());
}


static unsigned int atoui(std::string str)
{
	std::stringstream ss(str);
	unsigned int res;

	ss >> res;

	return res;
}


static std::string trimZeros(const std::string& str)
{
	size_t i = 0;

	while (i < str.size() && str[i] == '0')
		i++;
	if (i == str.size())
		return "0";
	return (str.substr(i));
}


bigint::bigint() : _str("0")
{

}

bigint::bigint(const bigint& other) : _str(other._str)
{

}

bigint::bigint(unsigned int n)
{
	_str = uitoa(n);
}

bigint& bigint::operator=(const bigint& other)
{
	if (this != &other)
		_str = other._str;
	return *this;
}

bigint::~bigint()
{

}


bigint bigint::operator+(const bigint& other) const
{
	std::string a = _str;
	std::string b = other._str;
	size_t i = a.size() - 1;
	size_t j = b.size() - 1;
	int carry = 0;
	std::string res;

	while (i >= 0 || j >= 0 || carry)
	{
		int dA = i >= 0 ? a[i] - '0' : 0;
		int dB = j >= 0 ? b[j] - '0' : 0;

		int sum = dA + dB + carry;
		res += (sum % 10) + '0';
		carry = sum / 10;

		i--;
		j--;
	}

	std::reverse(res.begin(), res.end());
	bigint tmp;
	tmp._str = trimZeros(res);
	return tmp;
}

bigint& bigint::operator+=(const bigint& other)
{
	*this = *this + other;

	return *this;
}


bigint bigint::operator++(int)
{
	bigint tmp = *this;
	*this += bigint(1);

	return tmp;
}

bigint& bigint::operator++()
{
	*this += bigint(1);

	return *this;
}


bigint bigint::operator<<(unsigned int n) const
{
	bigint tmp = *this;
	tmp._str.insert(tmp._str.size(), n, '0');

	tmp._str = trimZeros(tmp._str);
	return tmp;
}

bigint bigint::operator>>(unsigned int n) const
{
	bigint tmp = *this;
	if (tmp._str.size() <= n)
		tmp._str = "0";
	else
		tmp._str.erase(tmp._str.size() - n, n);

	return tmp;
}

bigint& bigint::operator<<=(unsigned int n)
{
	*this = *this << n;
	return *this;
}

bigint& bigint::operator>>=(unsigned int n)
{
	*this = *this >> n;
	return *this;
}


bigint bigint::operator<<(const bigint& other) const
{
	return (*this << atoui(other._str));
}

bigint bigint::operator>>(const bigint& other) const
{
	return (*this >> atoui(other._str));
}

bigint& bigint::operator<<=(const bigint& other)
{
	return (*this <<= atoui(other._str));

}

bigint& bigint::operator>>=(const bigint& other)
{
	return (*this >>= atoui(other._str));

}


bool bigint::operator==(const bigint& other) const
{
	if (_str.size() != other._str.size())
		return false;
	for (size_t i = 0; i < _str.size(); ++i)
	{
		if (_str[i] != other._str[i])
			return false;
	}
	return true;
}

bool bigint::operator!=(const bigint& other) const
{
	return !(*this == other);
}

bool bigint::operator<(const bigint& other) const
{
	if (_str.size() != other._str.size())
		return _str.size() < other._str.size();
	for (size_t i = 0; i < _str.size(); ++i)
	{
		if (_str[i] != other._str[i])
			return _str[i] < other._str[i];
	}
	return false;
}

bool bigint::operator>(const bigint& other) const
{
	if (_str.size() != other._str.size())
		return _str.size() > other._str.size();
	for (size_t i = 0; i < _str.size(); ++i)
	{
		if (_str[i] != other._str[i])
			return _str[i] > other._str[i];
	}
	return false;
}

bool bigint::operator<=(const bigint& other) const
{
	return !(*this > other);
}

bool bigint::operator>=(const bigint& other) const
{
	return !(*this < other);
}


const std::string& bigint::get_str() const
{
	return _str;
}

std::ostream& operator<<(std::ostream& out, const bigint& in)
{
	out << in.get_str();
	return out;
}
