/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BigInt.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:50:27 by pamatya           #+#    #+#             */
/*   Updated: 2025/11/06 20:07:41 by pamatya          ###   ########.fr       */
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
	void		removeZeros();
	std::string	addStrings(const std::string & s1, const std::string & s2) const;
	
public:	
	BigInt();
	BigInt(unsigned int n);
	BigInt(const std::string & num);
	BigInt(const BigInt & src);
	~BigInt();

	BigInt &		operator=(const BigInt & rhs);

	std::string		getVal() const;
	std::string		toString(unsigned int n);
	unsigned int	toInt(const std::string & num) const;

	BigInt			operator+(const BigInt & rhs) const;
	BigInt			operator+(unsigned int n) const;

	BigInt & 		operator+=(const BigInt & rhs);
	BigInt & 		operator+=(unsigned int n);

	BigInt			operator++(int);
	BigInt &		operator++();

	bool			operator==(const BigInt & rhs) const;
	bool			operator==(unsigned int n) const;

	bool			operator!=(const BigInt & rhs) const;
	bool			operator!=(unsigned int n) const;

	bool			operator>(const BigInt & rhs) const;
	bool			operator>(unsigned int n) const;
	
	bool			operator<(const BigInt & rhs) const;
	bool			operator<(unsigned int n) const;
	
	bool			operator>=(const BigInt & rhs) const;
	bool			operator>=(unsigned int n) const;
	
	bool			operator<=(const BigInt & rhs) const;
	bool			operator<=(unsigned int n) const;

	BigInt			operator<<(const BigInt & shift) const;
	BigInt			operator<<(unsigned int shift) const;
	BigInt			operator>>(const BigInt & shift) const;
	BigInt			operator>>(unsigned int shift) const;
	
	BigInt &		operator<<=(const BigInt & shift);
	BigInt &		operator<<=(unsigned int shift);
	BigInt &		operator>>=(const BigInt & shift);
	BigInt &		operator>>=(unsigned int shift);
};

std::ostream &	operator<<(std::ostream & o, const BigInt & obj);

#endif
