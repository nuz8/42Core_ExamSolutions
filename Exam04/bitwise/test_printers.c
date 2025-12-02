/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_printers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:55:51 by pamatya           #+#    #+#             */
/*   Updated: 2025/05/13 19:13:53 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bit_wise.h"

void	test_print_char(unsigned char c);
void	test_print_ints(int num, int mode);
void	test_print_reverse_bit(unsigned char byte);

void	test_print_char(unsigned char c)
{
	int	i;
	int	loop;

	i = (int)(c - 1);
	loop = (int)(c + 1);
	while (++i < loop)
	{
		ft_print_bits(i);
		write(1, "\n", 1);
		my_print_bits(i);
		write(1, "\n", 1);
	}
}

void	test_print_ints(int num, int mode)
{
	int	i;
	int	loop;

	i = -1;
	if (mode == UPTO)
		loop = num;
	else if (mode == ONLY)
	{
		i = num - 1;
		loop = num + 1;
	}
	while (++i <= loop)
	{
		ft_print_bits(i);
		write(1, "\n", 1);
		my_print_bits(i);
		write(1, "\n", 1);
	}
}

void	test_print_reverse_bit(unsigned char byte)
{
	unsigned char	rev_byte;
	
	ft_print_bits(byte);
	write(1, "\n", 1);
	
	rev_byte = my_reverse_bits(byte);
	ft_print_bits(rev_byte);
	write(1, "\n", 1);
	
	rev_byte = ft_reverse_bits(byte);
	ft_print_bits(rev_byte);
	write(1, "\n", 1);
}
