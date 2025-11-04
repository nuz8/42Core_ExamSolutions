/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BigInt.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 22:41:50 by pamatya           #+#    #+#             */
/*   Updated: 2025/11/04 20:27:39 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BigInt.hpp"

BigInt::BigInt() : _cto(0) {}

BigInt::BigInt(const long long num) : _cto(0) {
	_value = toString(num);
}

BigInt::BigInt(const std::string & num) : _value(num), _cto(0) {}

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

size_t		BigInt::getLlmaxLen() {
	return (toString(static_cast<long long>(LLONG_MAX)).length());
}


std::string	BigInt::toString(const long long n) {
	std::stringstream	nstr;
	nstr << n;
	return (nstr.str());
}

long long	BigInt::toLlong(const std::string num) {
	std::stringstream	nstr(num);
	long long			n;
	nstr >> n;
	return (n);
}

BigInt		BigInt::operator+(const BigInt & rhs) {
	BigInt		ret;
	size_t		Llmax_len = getLlmaxLen() - 1;

	if (_value.length() <= Llmax_len && rhs._value.length() <= Llmax_len)
		ret._value = toString(toLlong(_value) + toLlong(rhs._value));
	
	// more cases to follow here in an else block
	else
	{
		// std::cout << "Got executed from here...Llen_max = " << Llmax_len << std::endl;
			
		std::string	rhs_value, rhs_remval;
		size_t		len = _value.length(), rlen = rhs._value.length();
		size_t		pos = len - Llmax_len, rpos = rlen - Llmax_len;
		if (len > Llmax_len)
		{
			_remVal = _value.substr(0, pos);
			_value = _value.substr(pos -1, Llmax_len);
		}
		if (rlen > Llmax_len)
		{
			rhs_remval = rhs._value.substr(0, rpos);
			rhs_value = rhs._value.substr(pos -1, Llmax_len);
		}
		ret._value = toString(toLlong(_value) + toLlong(rhs._value) + _cto);
		if (ret._value.length() > Llmax_len)
			_cto = 1;
		while (!_remVal.empty() || !rhs_remval.empty())
		{
			if (!_remVal.empty())
			{
				len = _remVal.length();
				pos = len - Llmax_len;
			}
			else
				len = 0;

			if (!rhs_remval.empty())
			{
				rlen = rhs_remval.length();
				rpos = rlen - Llmax_len;
			}
			else
				rlen = 0;


			if (len > Llmax_len)
			{
				_value = _remVal.substr(pos - 1, Llmax_len);
				_remVal = _remVal.substr(0, pos);
			}
			else if (len > 0)
			{
				_value = _remVal;
				_remVal = "";
			}

			if (rlen > Llmax_len)
			{
				rhs_value = rhs_remval.substr(rpos - 1, Llmax_len);
				rhs_remval = rhs_remval.substr(0, rpos);
			}
			else if (rlen > 0)
			{
				rhs_value = rhs_remval;
				rhs_remval = "";
			}


			ret._value = toString(toLlong(_value) + toLlong(rhs_value) + _cto) + ret._value;
			if (ret._value.length() > Llmax_len)
				_cto = 1;
		}
	}
	if (_cto == 1)
		ret._value = "1" + ret._value;
	return (_cto = 0, ret);
}





std::ostream &	operator<<(std::ostream & o, const BigInt & obj) {
	o << obj.getValue() << "$" << std::endl;
	return (o);
}

int	main()
{
	// // TEST 1
	// {
	// 	BigInt	a(1234567890123456789), b("876534871265478156412634"), c(a);
	
	// 	std::cout << a << b << c;
	
	// 	a.setValue(987654321987654321);
	// 	b.setValue(444);
	// 	c = b;
	// 	std::cout << a << b << c;
	// }
	
	// // TEST 2
	// {
	// 	BigInt	a(450), b(565);
	// 	BigInt	c(999999999999999999), d(111111111111111111);

	// 	std::cout << "    " << a << "  + " << b << " = " << (a + b);
	// 	std::cout << "    " << c << "  + " << d << " = " << (c + d);
	// }

	// TEST 3
	{
		BigInt	a(999999999999999999), b(111111111111111111);
		BigInt	c(LLONG_MAX - 1), d("1");
		BigInt	e("2222222222222222222"), f("1111111111111111111");
		
		std::cout << "CD  " << c << "  + " << d << "  = " << (c + d);
		std::cout << "EF  " << e << "  + " << f << "= " << (e + f);
	}

	return (0);
}
