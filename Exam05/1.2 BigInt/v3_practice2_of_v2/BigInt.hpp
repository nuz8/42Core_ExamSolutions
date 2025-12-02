/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BigInt.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:50:27 by pamatya           #+#    #+#             */
/*   Updated: 2025/11/20 02:05:29 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGINT_HPP
# define BIGINT_HPP

# include <iostream>
# include <sstream>
# include <algorithm>
# include <string>

class BigInt
{
private:
	std::string	_value;
	std::string	addStrings(const std::string & s1, const std::string & s2) const;
	void	removeZeros();

public:
	BigInt();
	BigInt(unsigned int n);
	BigInt(const std::string & num);
	BigInt(const BigInt & src);
	~BigInt();
	BigInt &		operator=(const BigInt & rhs);

	std::string		getVal() const;
	unsigned int	toInt(const std::string & str) const;

	BigInt			operator+(const BigInt & rhs) const;
	BigInt &		operator+=(const BigInt & rhs);

	BigInt			operator++(int);
	BigInt &		operator++();

	bool			operator==(const BigInt & rhs) const;
	bool			operator!=(const BigInt & rhs) const;
	bool			operator>(const BigInt & rhs) const;
	bool			operator>=(const BigInt & rhs) const;
	bool			operator<(const BigInt & rhs) const;
	bool			operator<=(const BigInt & rhs) const;

	BigInt			operator<<(const BigInt & shift) const;
	BigInt			operator>>(const BigInt & shift) const;

	BigInt &		operator<<=(const BigInt & shift);
	BigInt &		operator>>=(const BigInt & shift);
};

std::ostream &		operator<<(std::ostream & o, const BigInt & obj);

#endif
