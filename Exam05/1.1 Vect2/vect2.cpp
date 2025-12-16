/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:30:37 by pamatya           #+#    #+#             */
/*   Updated: 2025/12/16 20:11:33 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect2.hpp"

vect2::vect2() : _x(0), _y(0) {}

vect2::vect2(int value) : _x(value), _y(value) {}

vect2::vect2(int x, int y) : _x(x), _y(y) {}

vect2::vect2(const vect2 & src) : _x(src._x), _y(src._y) {}

vect2::~vect2() {}

vect2	vect2::operator=(const vect2 & rhs) {
	if (this != &rhs)
	{
		_x = rhs._x;
		_y = rhs._y;
	}
	return (*this);
}

int		vect2::getX() const { return (_x); }
int		vect2::getY() const { return (_y); }

vect2	vect2::operator+(const vect2 & rhs) { return (vect2(_x + rhs._x, _y + rhs._y)); }
vect2 &	vect2::operator+=(const vect2 & rhs)
{
	_x = _x + rhs._x;
	_y = _y + rhs._y;
	return (*this);
}

/*
This won't work without the parenthesis separating the two args either side of
the comma, because the compiler thinks it is one argument and hence throws away 
the resulf of the left hand operand. This means that if it were to work, the 
wrong constructor would be called i.e. single param constructor instead of the 
double one. The -Werror flag helps here to flag it as an error and avoid a 
hard-to-detect symantic error situation.
So, either the extra parenthesis should be removed altogether, or the two args
need to be separately enclosed by separate pairs of parenthesis to explicitly
let the compiler know which constructor the programer intends to call. This
is an ambiguous call warning converted to error, which would otherwise compile
create an unintended bug that would be hard to detect.
*/
// vect2	vect2::operator-(const vect2 & rhs) { return (vect2((_x - rhs._x, _y - rhs._y))); }
vect2	vect2::operator-(const vect2 & rhs) { return (vect2(_x - rhs._x, _y - rhs._y)); }

vect2 &	vect2::operator-=(const vect2 & rhs)
{
	_x = _x - rhs._x;
	_y = _y - rhs._y;
	return (*this);
}
vect2	vect2::operator*(const vect2 & rhs) { return (vect2(_x * rhs._x, _y * rhs._y)); }
vect2 &	vect2::operator*=(const vect2 & rhs)
{
	_x = _x * rhs._x;
	_y = _y * rhs._y;
	return (*this);
}

// vect2	vect2::operator+(int scalar)
// {
// 	vect2	tmp(_x + scalar, _y + scalar);
// 	return (tmp);
// }
// vect2 &	vect2::operator+=(int scalar)
// {
// 	_x = _x + scalar;
// 	_y = _y + scalar;
// 	return (*this);
// }
// vect2	vect2::operator-(int scalar)
// {
// 	vect2	tmp(_x - scalar, _y - scalar);
// 	return (tmp);
// }
// vect2 &	vect2::operator-=(int scalar)
// {
// 	_x = _x - scalar;
// 	_y = _y - scalar;
// 	return (*this);
// }
// vect2	vect2::operator*(int scalar)
// {
// 	vect2	tmp(_x * scalar, _y * scalar);
// 	return (tmp);
// }
// vect2 &	vect2::operator*=(int scalar)
// {
// 	_x = _x * scalar;
// 	_y = _y * scalar;
// 	return (*this);
// }

vect2	vect2::operator-() const { return (vect2(-1 * _x, -1 * _y)); }

vect2	vect2::operator++(int)
{
	vect2	tmp(_x, _y);
	_x++;
	_y++;
	return (tmp);
}
vect2 &	vect2::operator++()
{
	_x++;
	_y++;
	return (*this);
}
vect2	vect2::operator--(int)
{
	vect2	tmp(_x, _y);
	_x--;
	_y--;
	return (tmp);
}
vect2 &	vect2::operator--()
{
	_x--;
	_y--;
	return (*this);
}

int &	vect2::operator[](int index) { return (index == 0 ? _x : _y); }
int		vect2::operator[](int index) const { return (index == 0 ? _x : _y); }
// const int &	vect2::operator[](int index) const { return (index == 0 ? _x : _y); }

bool	vect2::operator==(const vect2 & rhs)
{
	if (_x == rhs._x && _y == rhs._y)
		return (true);
	return (false);
}

bool	vect2::operator!=(const vect2 & rhs)
{
	if (_x != rhs._x || _y != rhs._y)
		return (true);
	return (false);
}

vect2	operator+(int scalar, const vect2 & rhs)
{
	vect2	tmp(scalar + rhs._x, scalar + rhs._y);
	return (tmp);
}

vect2	operator-(int scalar, const vect2 & rhs)
{
	vect2	tmp(scalar - rhs._x, scalar - rhs._y);
	return (tmp);
}

vect2	operator*(int scalar, const vect2 & rhs)
{
	vect2	tmp(scalar * rhs._x, scalar * rhs._y);
	return (tmp);
}

std::ostream &	operator<<(std::ostream & o, const vect2 & obj)
{
	// o << "{" << obj.getX() << ", " << obj.getY() << "}" << std::endl;
	o << "{" << obj[0] << ", " << obj[1] << "}" << std::endl;
	return (o);
}
