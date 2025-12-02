/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:47:31 by pamatya           #+#    #+#             */
/*   Updated: 2025/11/30 22:14:24 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bit_wise.h"

int	main(void)
{
	// Testing print_bits fn ---------------------
	test_print_ints(11, UPTO);
	write(1, "\n", 1);
	test_print_char('a');
	write(1, "\n", 1);
	test_print_char('A');
	write(1, "\n", 1);
	test_print_char('a');
	write(1, "\n", 1);
	
	// Testing reverse_bits fn -------------------
	test_print_reverse_bit('a');
	write(1, "\n", 1);

	test_print_reverse_bit(38);
	write(1, "\n", 1);

	test_print_reverse_bit(3);
	write(1, "\n", 1);
	
	// Testing swap_bits fn ----------------------
	
	
	return (0);
}
