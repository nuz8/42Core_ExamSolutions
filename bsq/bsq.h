/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:34:19 by pamatya           #+#    #+#             */
/*   Updated: 2025/11/29 00:08:16 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <stdbool.h>
#include <string.h>

typedef struct bsq
{
	char**	map;
	int**	dpTable;
	char*	first_line;
	char*	line;
	size_t	len;
	int		rows;
	int		width;
	int		index_mxX;
	int		index_mxY;
	int		bSq;
	char	empty;
	char	obs;
	char	full;
}	bsq;

int		init_bsq(bsq* obj, FILE* file);
int		parse_first_line(bsq* obj, FILE* file);
int		validate_map(bsq* obj);
int		solveBSQ(FILE *file);

// utils.c

char*	ft_strdup(char* str);
size_t	ft_strlen(char* str);
int		ft_atoi(char* str, size_t n_chars);
int		ft_isprint(int c);
void	cleanAll(bsq *obj);
void	print_struct_bsq(bsq* obj);

#endif
