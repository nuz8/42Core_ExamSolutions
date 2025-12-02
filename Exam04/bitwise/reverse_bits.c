/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:27:49 by pamatya           #+#    #+#             */
/*   Updated: 2025/05/13 19:25:50 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bit_wise.h"

unsigned char	my_reverse_bits(unsigned char byte);
unsigned char	ft_reverse_bits(unsigned char byte);

unsigned char	my_reverse_bits(unsigned char byte)
{
	int				i;
	unsigned char	rev_byte;
	
	rev_byte = 0;
	i = 8;
	while (i-- > 0)
		rev_byte = (((byte >> i) & 1) << (7 - i)) | rev_byte;
	return (rev_byte);	
}

unsigned char	ft_reverse_bits(unsigned char byte)
{
	int				i;
	unsigned char	rev_byte;
	
	rev_byte = 0;
	i = 8;
	while (i-- > 0)
	{
		rev_byte = (rev_byte << 1) | (byte & 1);
		byte = byte >> 1;
	}
	return (rev_byte);
}
