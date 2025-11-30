/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BigInt.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:36:58 by pamatya           #+#    #+#             */
/*   Updated: 2025/11/20 02:34:11 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BigInt.hpp"

BigInt::BigInt() : _value("0") {}

BigInt::BigInt(unsigned int n) {
	std::ostringstream	oss;
	oss << n;
	_value = oss.str();
	std::reverse(_value.begin(), _value.end());
}

BigInt::BigInt(const std::string & num) {
	bool	isNum = true;
	size_t	i = 0, len = num.size();
	while (i < len)
	{
		if (!(::isdigit(num[i])))
		{
			isNum = false;
			break ;
		}
		i++;
	}
	if (num.empty() || isNum == false)
		_value = '0';
	else
		_value = num;
	std::reverse(_value.begin(), _value.end());
	removeZeros();
}

BigInt::BigInt(const BigInt & src) {
	_value = src._value;
}

BigInt::~BigInt() {}

BigInt &	BigInt::operator=(const BigInt & rhs) {
	if (this != &rhs)
		_value = rhs._value;
	return (*this);
}

std::string	BigInt::addStrings(const std::string & s1, const std::string & s2) const {
	std::string	result;
	size_t i = 0, l1 = s1.size(), l2 = s2.size(), len;
	len = l1 > l2 ? l1 : l2;
	unsigned int	s1_r, s2_r, res, cto = 0;;
	while (i < len)
	{
		s1_r = i < l1 ? (s1[i] - '0') : 0;
		s2_r = i < l2 ? (s2[i] - '0') : 0;
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

void	BigInt::removeZeros() {
	while (_value[_value.size() - 1] == '0')
		_value.erase(_value.size() - 1);
}

std::string		BigInt::getVal() const {
	std::string ret = _value;
	std::reverse(ret.begin(), ret.end());
	return (ret);
}

unsigned int	BigInt::toInt(const std::string & str) const {
	unsigned int		num;
	std::istringstream	iss(str);
	iss >> num;
	return (num);
}

BigInt			BigInt::operator+(const BigInt & rhs) const {
	BigInt	result;
	result._value = addStrings(_value, rhs._value);
	return (result);
}

BigInt &		BigInt::operator+=(const BigInt & rhs) {
	_value = addStrings(_value, rhs._value);
	return (*this);
}

BigInt			BigInt::operator++(int) {
	BigInt	tmp(getVal());
	*this = *this + 1;
	return (tmp);
}

BigInt &		BigInt::operator++() {
	*this = *this + 1;
	return (*this);
}

bool			BigInt::operator==(const BigInt & rhs) const {
	if (_value == rhs._value)
		return (true);
	return (false);
}

bool			BigInt::operator!=(const BigInt & rhs) const {
	if (_value != rhs._value)
		return (true);
	return (false);
}

bool			BigInt::operator>(const BigInt & rhs) const {
	if (_value.size() > rhs._value.size())
		return (true);
	else if (_value.size() < rhs._value.size())
		return (false);
	else if (getVal() > rhs.getVal())
		return (true);
	return (false);
}

bool			BigInt::operator>=(const BigInt & rhs) const {
	if (*this > rhs || *this == rhs)
		return (true);
	return (false);
}

bool			BigInt::operator<(const BigInt & rhs) const {
	if (!(*this > rhs) && (*this != rhs))
		return (true);
	return (false);
}

bool			BigInt::operator<=(const BigInt & rhs) const {
	if (!(*this > rhs) || *this == rhs)
		return (true);
	return (false);
}


BigInt			BigInt::operator<<(const BigInt & shift) const {
	unsigned int	n = toInt(shift.getVal());
	unsigned int	i = 0;
	BigInt			result = *this;
	while (i < n)
	{
		result._value = '0' + result._value;
		i++;
	}
	return (result);
}

BigInt			BigInt::operator>>(const BigInt & shift) const {
	unsigned int	n = toInt(shift.getVal());
	unsigned int	i = 0;
	BigInt			result = *this;
	while (i < n && !(result._value.empty()))
	{
		result._value.erase(0, 1);
		i++;
	}
	return (result);
}


BigInt &		BigInt::operator<<=(const BigInt & shift) {
	_value = (*this << shift)._value;
	return (*this);
}

BigInt &		BigInt::operator>>=(const BigInt & shift) {
	_value = (*this >> shift)._value;
	return (*this);
}


std::ostream &		operator<<(std::ostream & o, const BigInt & obj) {
	o << obj.getVal() << std::endl;
	return (o);
}
