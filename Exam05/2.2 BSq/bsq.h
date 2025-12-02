/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:34:19 by pamatya           #+#    #+#             */
/*   Updated: 2025/11/27 18:35:43 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <string.h>

typedef struct bsq
{
	char**	map;
	int**	dpTable;
	char*	line;
	size_t	len;
	ssize_t	read;
	int		rows;
	int		width;
	int		index_mxX;
	int		index_mxY;
	int		bSq;
	char	empty;
	char	obs;
	char	full;
}	bsq;

#endif
