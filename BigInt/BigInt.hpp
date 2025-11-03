#ifndef BIGINT_HPP
# define BIGINT_HPP

# include <iostream>
# include <sstream>


class BigInt
{
private:
	std::string	_value;
public:	
	BigInt();
	BigInt(const long long num);
	BigInt(const std::string & num);
	BigInt(const BigInt & src);
	~BigInt();

	BigInt &	operator=(const BigInt & rhs);
	void		setValue(const long long num);
	void		setValue(const std::string & num);
	std::string	getValue() const;

	// BigInt		operator+(const BigInt & rhs);
	// BigInt		operator+=(const BigInt & rhs);
	// BigInt		operator+=(const int rhs);

	// BigInt &	operator++();
	// BigInt		operator++(int);

	// bool		operator==(const BigInt & rhs);
	// bool		operator!=(const BigInt & rhs);
	// bool		operator>(const BigInt & rhs);
	// bool		operator>=(const BigInt & rhs);
	// bool		operator<(const BigInt & rhs);
	// bool		operator<=(const BigInt & rhs);

	// BigInt		operator<<(const int shift);
	// BigInt		operator>>(const int shift);
};

std::ostream &	operator<<(std::ostream & o, const BigInt & obj);

#endif
