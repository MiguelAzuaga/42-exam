#include "bigint.hpp"

static std::string uitoa(unsigned int n)
{
	std::stringstream ss;
	ss << n;
	return ss.str();
}

static unsigned int atoui(std::string str)
{
	std::stringstream ss(str);
	unsigned int res;
	ss >> res;

	return (res);
}

static std::string trimZeros(const std::string& str)
{
	size_t start = str.find_first_not_of('0');
	if (start == std::string::npos)
		return "0";
	return str.substr(start);
}

bigint::bigint() : _str("0") {}

bigint::bigint(const bigint& other) : _str(trimZeros(other.get_str())) {}

bigint::bigint(unsigned int n)
{
	_str = uitoa(n);
}

bigint& bigint::operator=(const bigint& other)
{
	if (this != &other)
		this->_str = other.get_str();
	return (*this);
}

bigint::~bigint() {}

bigint bigint::operator+(const bigint& other) const
{
	std::string a = this->_str;
	std::string b = other.get_str();
	int i = a.size() - 1;
	int j = b.size() - 1;
	int carry = 0;
	std::string res;

	while (i >= 0 || j >= 0 || carry)
	{
		int digitA = i >= 0 ? a[i] - '0' : 0;
		int digitB = j >= 0 ? b[j] - '0' : 0;

		int sum = digitA + digitB + carry;

		res += (sum % 10) + '0';
		carry = sum / 10;

		i--;
		j--;
	}

	std::reverse(res.begin(), res.end());
	bigint tmp;
	tmp._str = trimZeros(res);

	return (tmp);
}

bigint& bigint::operator+=(const bigint& other)
{
	(*this) = ((*this) + other);
	return (*this);
}

bigint& bigint::operator++()
{
	(*this) += (const bigint)1;
	return (*this);
}

bigint bigint::operator++(int)
{
	bigint tmp = *this;
	(*this)++;

	return tmp;
}

bigint bigint::operator<<(unsigned int n) const
{
	bigint tmp = *this;
	tmp._str.insert(tmp._str.size(), n, '0');

	return tmp;
}

bigint bigint::operator>>(unsigned int n) const
{
	bigint tmp = *this;
	if (tmp._str.size() < n)
		tmp._str = "0";
	else
		tmp._str.erase(tmp._str.size() - n, n);

	return tmp;
}

bigint& bigint::operator<<=(unsigned int n)
{
	this->_str.insert(this->_str.size(), n, '0');

	return (*this);
}

bigint& bigint::operator>>=(unsigned int n)
{
	if (this->_str.size() < n)
		this->_str = "0";
	else
		this->_str.erase(this->_str.size() - n, n);

	return (*this);
}

bigint bigint::operator<<(const bigint& other) const
{
	return ((*this) << atoui(other._str));
}

bigint bigint::operator>>(const bigint& other) const
{
	return ((*this) >> atoui(other._str));
}

bigint& bigint::operator<<=(const bigint& other)
{
	return ((*this) <<= atoui(other._str));
}

bigint& bigint::operator>>=(const bigint& other)
{
	return ((*this) >>= atoui(other._str));
}

bool bigint::operator==(const bigint& other) const
{
	if (this->_str.size() != other._str.size())
		return false;
	for (size_t i = 0; i < this->_str.size(); ++i)
	{
		if (this->_str[i] != other._str[i])
			return false;
	}
	return true;
}

bool bigint::operator!=(const bigint& other) const
{
	if (this->_str.size() != other._str.size())
		return true;
	for (size_t i = 0; i < this->_str.size(); ++i)
	{
		if (this->_str[i] != other._str[i])
			return true;
	}
	return false;
}

bool bigint::operator<(const bigint& other) const
{
	if (this->_str.size() != other._str.size())
		return (this->_str.size() < other._str.size());
	for (size_t i = 0; i < this->_str.size(); ++i)
	{
		if (this->_str[i] != other._str[i])
			return this->_str[i] < other._str[i];
	}
	return false;
}

bool bigint::operator>(const bigint& other) const
{
	if (this->_str.size() != other._str.size())
		return (this->_str.size() > other._str.size());
	for (size_t i = 0; i < this->_str.size(); ++i)
	{
		if (this->_str[i] != other._str[i])
			return this->_str[i] > other._str[i];
	}
	return false;
}

bool bigint::operator<=(const bigint& other) const
{
	return !((*this) > other);
}

bool bigint::operator>=(const bigint& other) const
{
	return !((*this) < other);
}

const std::string bigint::get_str() const { return this->_str; }

std::ostream& operator<<(std::ostream& out, const bigint& in)
{
	out << in.get_str();
	return (out);
}
