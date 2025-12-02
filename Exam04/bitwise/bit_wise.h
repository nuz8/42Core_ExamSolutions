/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_wise.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:38:21 by pamatya           #+#    #+#             */
/*   Updated: 2025/11/30 22:15:03 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIT_WISE_H
# define BIT_WISE_H

# include <unistd.h>

#define UPTO -10
#define ONLY -20


int				main(void);	

void			ft_print_bits(unsigned char byte);
void			my_print_bits(unsigned char byte);

unsigned char	ft_reverse_bits(unsigned char byte);
unsigned char	my_reverse_bits(unsigned char byte);


void			test_print_char(unsigned char c);
void			test_print_ints(int num, int mode);
void			test_print_reverse_bit(unsigned char byte);

#endif