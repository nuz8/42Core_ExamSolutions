/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:36:53 by pamatya           #+#    #+#             */
/*   Updated: 2025/05/13 18:57:30 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bit_wise.h"

void		ft_print_bits(unsigned char byte);
void		my_print_bits(unsigned char byte);

static int	power(int num, int pow);


void	ft_print_bits(unsigned char byte)
{
	unsigned char	bit;
	int				i;

	bit = 0;
	i = 8;
	while (i-- > 0)
	{
		bit = ((byte >> i) & 1) + 48;
		write(1, &bit, 1);
	}
}

void	my_print_bits(unsigned char byte)
{
	int				i;
	unsigned char	bit;
	int				bit_int;
	int				pow;
	

	pow = 0;
	i = 8;
	// while (i-- > 0)
	// {
	// 	if (byte & power(2, i))
	// 		write(1, "1", 1);
	// 	else
	// 		write(1, "0", 1);
	// }
	while (i-- > 0)
	{
		pow = power(2, i);
		bit_int = (byte & pow);
		if (bit_int)
			bit = 49;
		else
			bit = 48;
		write(1, &bit, 1);
	}
}

int	power(int num, int pow)
{
	int	i;
	int	res;

	if (pow < 0)
		return (0);
	if (num == 0 && pow == 0)
		return (0);
	if (num != 0 && pow == 0)
		return (1);
	i = -1;
	res = 1;
	while (++i < pow)
		res *= num;
	return (res);
}
