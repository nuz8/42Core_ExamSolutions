/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 22:41:54 by pamatya           #+#    #+#             */
/*   Updated: 2025/11/05 20:38:59 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "bigint.hpp"

int main() {
    // Création de bigints
    bigint num1("242"), num2("10"), num3, num4(100);
    bigint num5 = num2;
    const bigint numC(60);

    // Test des opérateurs arithmétiques
    std::cout << num1 << num2 << num3 << num4 << num5 << numC << std::endl;
    std::cout << "num1 + num2 = " << (num1 + num2) << std::endl;
    num3 = num1;
    num3 += num2;
    std::cout << "num3 += num2: " << num3 << std::endl;

    bigint num8("999"), num9("999");
    
    // Test des comparaisons
    std::cout << "num8 == num9: " << (num8 == num9) << std::endl;
    std::cout << "num8 != num9: " << (num8 != num9) << std::endl;
    std::cout << "num8 < num9: " << (num8 < num9) << std::endl;
    std::cout << "num8 <= num9: " << (num8 <= num9) << std::endl;
    std::cout << "num8 > num9: " << (num8 > num9) << std::endl;
    std::cout << "num8 >= num9: " << (num8 >= num9) << std::endl;

    bigint num10("4254");
    // Test des décalages avec entiers
    std::cout << "num10 << 2 = " << (num10 << 2) << std::endl;
    std::cout << "num10 >> 3 = " << (num10 >> 3) << std::endl;

    bigint num11("2");
    // // Test des décalages avec bigint
    std::cout << "num10 << num11 = " << (num10 << num11) << std::endl;
    std::cout << "num10 >> num11 = " << (num10 >> num11) << std::endl;

    bigint num12("2");
    // // Test des décalages avec bigint
    std::cout << num12.getVal() << ": num12++ = " << (num12++) << std::endl;
    std::cout << num12.getVal() << ": ++num10 = " << (++num12) << std::endl;


    // Test des décalages avec bigint constant
    std::cout << num10.getVal() << " << " << numC.getVal() << " = " << (num10 << numC) << std::endl;
    std::cout << num10.getVal() << " >> " << numC.getVal() << " = " << (num10 >> numC) << std::endl;

    // Test des affectations combinées avec décalages
    num3 = num1;
    std::cout << num3.getVal();
    num3 <<= 2;
    std::cout << " <<= 2: " << num3 << std::endl;

    std::cout << num3.getVal();
    num3 >>= 1;
    std::cout << " >>= 1: " << num3 << std::endl;

    // Test des affectations combinées avec bigint
    num3 = num1;
    std::cout << num3.getVal();
    num3 <<= num5;
    std::cout << " <<= " << num5.getVal() << ": " << num3 << std::endl;
    
    std::cout << num3.getVal();
    num3 >>= num5;
    std::cout << " >>= " << num5.getVal() << ": " << num3 << std::endl;

    return 0;
}