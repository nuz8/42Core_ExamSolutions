/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:45:05 by pamatya           #+#    #+#             */
/*   Updated: 2025/11/07 00:57:27 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BigInt.hpp"
#include <iostream>

int	main()
{
	const BigInt a(42);
	BigInt b(21), c, d(1337), e(d);

	std::cout << "a: " << a << std::endl;
	std::cout << "b: " << b << std::endl;
	std::cout << "c: " << c << std::endl;
	std::cout << "d: " << d << std::endl;
	std::cout << "e: " << e << std::endl;
	std::cout << "a + b: " << a + b << std::endl;
	std::cout << "(c += a): " << (c += a) << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "++b: " << ++b << std::endl;
	std::cout << "b++: " << b++ << std::endl;
	std::cout << "(b << 10) + 42 = " << (b << 10) + 42 << std::endl;
	std::cout << "d: " << d << std::endl;
	std::cout << "(d <<= 4) = " << (d <<= 4) << std::endl;
	std::cout << "d: " << d << std::endl;
	std::cout << "(d >>= 2) = " << (d >>= 2) << std::endl;
	std::cout << "d: " << d << std::endl;
	std::cout << "a = " << a << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << "(d < a): " << (d < a) << std::endl;
	std::cout << "(d > a): " << (d > a) << std::endl;
	std::cout << "(d == a): " << (d == a) << std::endl;
	std::cout << "(d != a): " << (d != a) << std::endl;
	std::cout << "(d <= a): " << (d <= a) << std::endl;
	std::cout << "(d >= a): " << (d >= a) << std::endl;
	std::cout << std::endl;
	d = e;
	std::cout << "d = " << d << std::endl;
	std::cout << "e = " << e << std::endl;
	std::cout << "(e <= d): " << (e <= d) << std::endl;
	std::cout << "(e >= d): " << (e >= d) << std::endl;

	BigInt	f((d + 1));
	std::cout << "d = " << d << std::endl;
	std::cout << "f = " << f << std::endl;
	std::cout << "(f > d): " << (f > d) << std::endl;
	std::cout << "(f < d): " << (f < d) << std::endl;
	std::cout << "f >= d: " << (f >= d) << std::endl;
	std::cout << "f <= d: " << (f <= d) << std::endl;
	
	return (0);
}
