/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:41:02 by pamatya           #+#    #+#             */
/*   Updated: 2025/11/29 00:08:34 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int			init_bsq(bsq* obj, FILE* file);

static void	init_obj(bsq* obj);
static int	init_map(bsq *obj, FILE* file);
static int	init_dpTable(bsq *obj);

int	init_bsq(bsq* obj, FILE* file)
{
	init_obj(obj);
	if (parse_first_line(obj, file) < 0)
		return (cleanAll(obj), -1);
	if (init_map(obj, file) == -1)
		return (cleanAll(obj), -1);
	if (validate_map(obj) < 0)
		return (cleanAll(obj), -1);
	if (init_dpTable(obj) == -1)
		return (cleanAll(obj), -1);
	return (0);
}

static void	init_obj(bsq* obj)
{
	obj->map = NULL;
	obj->dpTable = NULL;
	obj->first_line = NULL;
	obj->line = NULL;
	obj->len = 0;
	obj->rows = 0;
	obj->width = 0;
	obj->empty = 0;
	obj->obs = 0;
	obj->full = 0;
	obj->index_mxX = 0;
	obj->index_mxY = 0;
	obj->bSq = 0;
}

static int	init_map(bsq *obj, FILE* file)
{
	int	i = -1, j = -1, rows = obj->rows;
	ssize_t	read, prev_read;

	read = getline(&obj->line, &obj->len, file);	// line now has already the 1st row of the map
	if (read < 0) {
		if (errno == EINVAL || errno == ENOMEM)
			return (fprintf(stderr, "Error: getline failed\n"), -1);
		else	// means EOF; validating that there is atleast one line
			return (fprintf(stderr, "Error: map error: zero rows\n"), -1);
	}
	if (read == 1 && obj->line[0] == '\n')	// means only '\n' is present after the control line
		return (fprintf(stderr, "Error: map error: zero rows, only newline\n"), -1);
	prev_read = read;
	obj->width = (int)(read) - 1;

	obj->map = malloc((rows + 1) * sizeof(char*));
	if (!obj->map)
		return (fprintf(stderr, "Error: map malloc failed\n"), -1);

	obj->map[rows] = NULL;
	while (++i < rows)
	{
		obj->map[i] = calloc((obj->width + 1), sizeof(char));
		if (!obj->map[i])
			return (fprintf(stderr, "Error: map calloc failed\n"), -1);
	}
	while (++j < (rows))
	{
		i = -1;
		if (obj->line[read - 1] != '\n')	// Checking for line-break at the end of each line
			return (fprintf(stderr, "Error: map error: no line-break at the end of line\n"), -1);
		while (++i < (obj->width))
			obj->map[j][i] = obj->line[i];
		read = getline(&obj->line, &obj->len, file);
		if ((j + 1) < rows && read < 0) {
			if (errno == EINVAL || errno == ENOMEM)
				return (fprintf(stderr, "Error: getline failed\n"), -1);
			else	// means EOF; checking that there are atleast 'rows' number of lines in the map
				return (fprintf(stderr, "Error: map error: less rows (%d) than expected (%d)\n", (j + 1), rows), -1);
		}
		if ((j + 1) < rows && read != prev_read)	// means that atleast one row has more/less chars
			return (fprintf(stderr, "Error: map error: varying width\n"), -1);
		prev_read = read;
	}
	return (0);
}

static int	init_dpTable(bsq *obj)
{
	int	i = -1;
	obj->dpTable = malloc((obj->rows + 1) * sizeof(int*));
	if (!obj->dpTable)
		return (cleanAll(obj), -1);
	obj->dpTable[obj->rows] = NULL;
	while (++i < obj->rows)
	{
		obj->dpTable[i] = calloc((obj->width), sizeof(int));
		if (!obj->dpTable[i])
			return (fprintf(stderr, "Calloc error\n"), cleanAll(obj), -1);
	}
	return (0);
}
