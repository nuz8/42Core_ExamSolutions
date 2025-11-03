/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BigInt.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 22:41:50 by pamatya           #+#    #+#             */
/*   Updated: 2025/11/04 00:52:36 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BigInt.hpp"

BigInt::BigInt() {}

BigInt::BigInt(const long long num) {
	std::stringstream	oss;
	oss << num;
	_value = oss.str();
}

BigInt::BigInt(const std::string & num) : _value(num) {}

BigInt::BigInt(const BigInt & src) {
	*this = src;
}

BigInt::~BigInt() {}

BigInt &	BigInt::operator=(const BigInt & rhs) {
	if (this != &rhs)
		_value = rhs._value;
	return (*this);
}

void		BigInt::setValue(const long long num) {
	std::stringstream	oss;
	oss << num;
	_value = oss.str();
}

void		BigInt::setValue(const std::string & num) {
	_value = num;
}

std::string	BigInt::getValue() const {
	return (_value);
}

std::ostream &	operator<<(std::ostream & o, const BigInt & obj) {
	o << obj.getValue() << std::endl;
	return (o);
}

// BigInt		BigInt::operator+(const BigInt & rhs) {
	
// }

// BigInt		BigInt::operator+=(const BigInt & rhs) {

// }

// BigInt		BigInt::operator+=(const int rhs) {

// }











int	main()
{
	BigInt	a(1234567890123456789), b("876534871265478156412634"), c(a);

	std::cout << a << b << c;

	a.setValue(987654321987654321);
	b.setValue(444);
	c = b;
	std::cout << a << b << c;
	
	return (0);
}
