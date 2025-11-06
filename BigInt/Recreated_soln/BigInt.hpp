/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BigInt.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 21:10:47 by pamatya           #+#    #+#             */
/*   Updated: 2025/11/05 21:13:48 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGINT_HPP
# define BIGINT_HPP

# include <iostream>
# include <sstream>
# include <algorithm>

class BigInt
{
private:
	std::string	_val;
	void		removeZeros();
	std::string	addStrings(const std::string & s1, const std::string & s2);

public:
	BigInt();
	BigInt(unsigned int n);
	BigInt(const std::string & num);
	BigInt(const BigInt & obj);
	BigInt &	operator=(const BigInt & rhs);
	~BigInt();

	std::string	getVal() const;

	BigInt		operator+(const BigInt & rhs);
	BigInt &	operator+=(const BigInt & rhs);

	BigInt &	operator++(int);
	BigInt &	operator++();

	bool		operator==(const BigInt & rhs) const;
	bool		operator!=(const BigInt & rhs) const;
	bool		operator>(const BigInt & rhs) const;
	bool		operator<(const BigInt & rhs) const;
	bool		operator>=(const BigInt & rhs) const;
	bool		operator<=(const BigInt & rhs) const;

	BigInt		operator>>(unsigned int shift) const;
	BigInt		operator>>(const BigInt & shift) const;
	BigInt		operator<<(unsigned int shift) const;
	BigInt		operator<<(const BigInt & shift) const;

	BigInt &	operator>>=(unsigned int shift);
	BigInt &	operator>>=(const BigInt & shift);
	BigInt &	operator<<=(unsigned int shift);
	BigInt &	operator<<=(const BigInt & shift);
};

std::ostream	operator<<(std::ostream & o, const BigInt & obj);

#endif
