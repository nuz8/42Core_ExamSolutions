/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:30:53 by pamatya           #+#    #+#             */
/*   Updated: 2025/11/19 20:17:31 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECT2_HPP
# define VECT2_HPP

# include <iostream>

class vect2
{
private:
	int	_x;
	int	_y;

public:
	vect2();
	vect2(int value);
	vect2(int x, int y);
	vect2(const vect2 & src);
	~vect2();
	vect2	operator=(const vect2 & rhs);

	int		getX() const ;
	int		getY() const ;

	vect2	operator+(const vect2 & rhs);
	vect2 &	operator+=(const vect2 & rhs);	
	vect2	operator-(const vect2 & rhs);
	vect2 &	operator-=(const vect2 & rhs);	
	vect2	operator*(const vect2 & rhs);
	vect2 &	operator*=(const vect2 & rhs);

	vect2	operator-() const ;

	vect2	operator++(int);
	vect2 &	operator++();
	vect2	operator--(int);
	vect2 &	operator--();

	int &	operator[](int index);
	int		operator[](int index) const ;
	// const int &	operator[](int index) const ;
	
	bool	operator==(const vect2 & rhs);
	bool	operator!=(const vect2 & rhs);

	friend vect2	operator+(int scalar, const vect2 & rhs);
	friend vect2	operator-(int scalar, const vect2 & rhs);
	friend vect2	operator*(int scalar, const vect2 & rhs);
};

std::ostream &	operator<<(std::ostream & o, const vect2 & obj);

#endif
