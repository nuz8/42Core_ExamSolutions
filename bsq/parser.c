/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:24:44 by pamatya           #+#    #+#             */
/*   Updated: 2025/11/27 20:50:52 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int		parse_map(bsq* obj, FILE* file);

static int		parse_first_line(bsq* obj, FILE* file);


int	parse_map(bsq* obj, FILE* file)
{
	if (parse_first_line(obj, file) < 0)
		return (-1);

	

	return (0);
}

static int	parse_first_line(bsq* obj, FILE* file)
{
	char*	tline = NULL;
	size_t	len;

	obj->read = getline(&obj->line, &obj->len, file);
	if (obj->read == -1)
		return (fprintf(stderr, "Error: getline failed on first read\n"), -1);
	tline = ft_strdup(obj->line);
	if (!tline)
		return (fprintf(stderr, "Error: ft_strdup returned NULL pointer\n"), -1);	
	len = ft_strlen(obj->line);
	obj->empty = tline[len - 3];
	obj->obs = tline[len - 2];
	obj->full = tline[len - 1];
	obj->rows = ft_atoi(tline, 3);
	free(tline);
	return (0);
}
