/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BigInt.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:36:58 by pamatya           #+#    #+#             */
/*   Updated: 2025/11/07 16:55:42 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BigInt.hpp"

BigInt::BigInt() {}

BigInt::BigInt(unsigned int n) {
	std::ostringstream oss;
	oss << n;
	_value = oss.str();
	std::reverse(_value.begin(), _value.end());
}

BigInt::BigInt(const std::string & num) {
	bool	isNum = true;
	size_t	n_size = num.size();
	for (size_t i = 0; i < n_size; i++)
	{
		if (!::isdigit(num[i])) {
			isNum = false;
			break ;
		}
	}
	if (num.empty() || isNum == false)
		_value = '0';
	else
		_value = num;
	std::reverse(_value.begin(), _value.end());
	removeZeros();
}

BigInt::BigInt(const BigInt & src) : _value(src._value) {}

BigInt::~BigInt() {}

BigInt &	BigInt::operator=(const BigInt & rhs) {
	if (this != &rhs)
		_value = rhs._value;
	return (*this);
}

void	BigInt::removeZeros() {
	while ((_value.size() - 1) == '0')
		_value.erase(_value.size() - 1);
}

std::string	BigInt::addStrings(const std::string & s1, const std::string & s2) const {
	std::string	result;
	size_t		len, i;
	int			s1_r, s2_r, res, cto;
	
	len = (s1.size() > s2.size()) ? s1.size() : s2.size();
	cto = 0;
	i = 0;
	while (i < len)
	{
		s1_r = (i < s1.size()) ? s1[i] - '0' : 0;
		s2_r = (i < s2.size()) ? s2[i] - '0' : 0;
		res = s1_r + s2_r + cto;
		cto = res / 10;
		res = res % 10;
		result.push_back(res + '0');
		i++;
	}
	if (cto)
		result.push_back(cto + '0');
	return (result);
}

// Returns the string in the right order, ready to be printed (by reversing the copy of the _value)
std::string		BigInt::getVal() const {
	std::string	ret;
	ret = _value;
	std::reverse(ret.begin(), ret.end());
	return (ret);
}

// Returns a string equivalent of the integer n (in the same order as the input)
std::string		BigInt::toString(unsigned int n) {
	std::ostringstream oss;
	oss << n;
	return (oss.str());
}

// Returns the integer equivalent of the string num (in the same order as the input)
unsigned int	BigInt::toInt(const std::string & num) const {
	unsigned int		n;
	std::istringstream	iss(num);
	iss >> n;
	return (n);
}

BigInt	BigInt::operator+(const BigInt & rhs) const {
	BigInt	result;
	result._value = addStrings(_value, rhs._value);
	return (result);
}

BigInt	BigInt::operator+(unsigned int n) const {
	BigInt	rhs(n);
	return (*this + rhs);
}

BigInt &	BigInt::operator+=(const BigInt & rhs) {
	*this = *this + rhs;
	return (*this);
}


BigInt &	BigInt::operator+=(unsigned int n) {
	*this = *this + n;
	return (*this);
}

BigInt	BigInt::operator++(int) {
	BigInt	temp = *this;
	*this = *this + 1;
	return (temp);
}

BigInt &	BigInt::operator++() {
	*this = *this + 1;
	return (*this);
}

bool	BigInt::operator==(const BigInt & rhs) const {
	if (_value == rhs._value)
		return (true);
	return (false);
}

bool	BigInt::operator==(unsigned int n) const {
	BigInt	rhs(n);
	if (_value == rhs._value)
		return (true);
	return (false);
}

bool	BigInt::operator!=(const BigInt & rhs) const {
	if (_value != rhs._value)
		return (true);
	return (false);
}

bool	BigInt::operator!=(unsigned int n) const {
	BigInt	rhs(n);
	if (_value != rhs._value)
		return (true);
	return (false);
}

bool	BigInt::operator>(const BigInt & rhs) const {
	if (_value.size() > rhs._value.size())
		return (true);
	else if (_value.size() < rhs._value.size())
		return (false);
	else
	{
		std::string	val = getVal();
		std::string	rval = rhs.getVal();
		size_t		i = 0, len = _value.size();
		while (i < len)
		{
			if (val[i] > rval[i])
				return (true);
			else if (val[i] < rval[i])
				return (false);
			else
				i++;											// !!!
		}
	}
	return (false);
}

bool	BigInt::operator>(unsigned int n) const {
	BigInt	rhs(n);
	return (*this > rhs);
}

bool	BigInt::operator<(const BigInt & rhs) const {
	if (!(*this > rhs) && (*this != rhs))
		return (true);
	return (false);
}

bool	BigInt::operator<(unsigned int n) const {
	BigInt	rhs(n);
	if (!(*this > rhs) && (*this != rhs))
		return (true);
	return (false);
}

bool	BigInt::operator>=(const BigInt & rhs) const {
	if (*this > rhs || *this == rhs)
		return (true);
	return (false);
}

bool	BigInt::operator>=(unsigned int n) const {
	BigInt	rhs(n);
	if (*this > rhs || *this == rhs)
		return (true);
	return (false);
}

bool	BigInt::operator<=(const BigInt & rhs) const {
	if (!(*this > rhs) || *this == rhs)
		return (true);
	return (false);
}

bool	BigInt::operator<=(unsigned int n) const {
	BigInt	rhs(n);
	if (!(*this > rhs) || *this == rhs)
		return (true);
	return (false);
}

BigInt	BigInt::operator<<(const BigInt & shift) const {
	BigInt	result;
	result = result << toInt(shift.getVal());	
	return (result);
}

BigInt	BigInt::operator<<(unsigned int shift) const {
	BigInt	result;
	result._value = _value;
	unsigned int	i = 0;
	while (i < shift)
	{
		result._value = '0' + result._value;
		i++;
	}
	return (result);
}

BigInt	BigInt::operator>>(const BigInt & shift) const {
	BigInt	result;
	result = result >> toInt(shift.getVal());
	return (result);
}

BigInt	BigInt::operator>>(unsigned int shift) const {
	BigInt	result;
	result._value = _value;
	std::reverse(result._value.begin(), result._value.end());

	unsigned int	i = 0;
	while (i < shift && result._value != "0")
	{
		result._value.erase(result._value.size() - 1);
		i++;										// !!!
	}
	std::reverse(result._value.begin(), result._value.end());
	return (result);
}

BigInt &	BigInt::operator<<=(const BigInt & shift) {
	_value = (*this << shift)._value;
	return (*this);
}

BigInt &	BigInt::operator<<=(unsigned int shift) {
	_value = (*this << shift)._value;
	return (*this);
}

BigInt &	BigInt::operator>>=(const BigInt & shift) {
	_value = (*this >> shift)._value;
	return (*this);
}

BigInt &	BigInt::operator>>=(unsigned int shift) {
	_value = (*this >> shift)._value;
	return (*this);
}

std::ostream &	operator<<(std::ostream & o, const BigInt & obj)
{
	std::cout << obj.getVal() << std::endl;
	return (o);
}
