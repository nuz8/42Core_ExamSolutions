/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:41:02 by pamatya           #+#    #+#             */
/*   Updated: 2025/11/27 20:47:46 by pamatya          ###   ########.fr       */
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
	if (parse_map(obj, file) < 0)
		return (cleanAll(obj), -1);
	if (init_map(obj, file) == -1)
		return (cleanAll(obj), -1);
	if (init_dpTable(obj) == -1)
		return (cleanAll(obj), -1);
	return (0);
}

static void	init_obj(bsq* obj)
{
	obj->map = NULL;
	obj->dpTable = NULL;
	obj->line = NULL;
	obj->len = 0;
	obj->read = 0;
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
	int	i = -1, j = -1;

	obj->read = getline(&obj->line, &obj->len, file);	// line now has already the 1st row of the map
	obj->width = (int)(obj->read) - 1;

	obj->map = malloc((obj->rows + 1) * sizeof(char*));
	if (!obj->map)
		return (cleanAll(obj), -1);

	obj->map[obj->rows] = NULL;
	while (++i < obj->rows)
	{
		obj->map[i] = calloc((obj->width + 1), sizeof(char));
		if (!obj->map[i])
			return (cleanAll(obj), -1);
	}
	while (++j < (obj->rows) && !(obj->read < 0))
	{
		i = -1;
		while (++i < (obj->width))
			obj->map[j][i] = obj->line[i];
		obj->read = getline(&obj->line, &obj->len, file);
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
