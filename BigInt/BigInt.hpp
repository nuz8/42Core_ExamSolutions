#ifndef BIGINT_HPP
# define BIGINT_HPP

# include <iostream>
# include <sstream>
# include <climits>

class BigInt
{
private:
	std::string	_value;
	long long	_cto;		// carry the one
	std::string	_remVal;
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
	size_t		getLlmaxLen();
	std::string	toString(const long long n);
	long long	toLlong(const std::string num);

	BigInt		operator+(const BigInt & rhs);
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
