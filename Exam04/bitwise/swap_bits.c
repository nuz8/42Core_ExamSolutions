/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:28:23 by pamatya           #+#    #+#             */
/*   Updated: 2025/05/13 19:47:11 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bit_wise.h"

unsigned char	ft_swap_bits(unsigned char byte)
{
	unsigned char	swapped_byte;

	swapped_byte = (byte >> 4) | (byte << 4);
	return (swapped_byte);
}
