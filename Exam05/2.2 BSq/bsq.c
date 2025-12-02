/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 01:58:07 by pamatya           #+#    #+#             */
/*   Updated: 2025/12/02 15:45:32 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

/*
Allowed functions and globals: malloc, calloc, realloc, free, fopen, fclose,
getline, fscanf, fputs, fprintf, stderr, stdout, stdin, errno
Note: also recently - printf
*/

int		solveBSQ(FILE *file);
void	init_bsq(bsq* obj);
int		parse_map(bsq* obj, FILE* file);
int		parse_first_line(bsq* obj, FILE* file);
char*	ft_strdup(char* str);
size_t	ft_strlen(char* str);
int		ft_atoi(char* str, size_t n_chars);
int		init_map(bsq *obj, FILE* file);
int		init_dpTable(bsq *obj);
void	fillDPTable(bsq* obj);
void	findIndex(bsq* obj);
void	fillMap(bsq* obj);
void	printBSQ(bsq* obj);
void	cleanAll(bsq *obj);

int	main(int ac, char** av)
{
	int		i = 0, ret = 1;
	FILE*	file;

	if (ac == 1)
	{
		FILE*	file = stdin;
		return (solveBSQ(file));
	}
	else
	{
		while (++i < ac)
		{
			file = fopen(av[i], "r");
			if (!file)
			{
				fprintf(stderr, "Error: cannot open file: %s\n", av[i]);
				continue;
			}
			ret = solveBSQ(file);
			fclose(file);
		}
	}
	return (ret);
}

int	solveBSQ(FILE *file)
{
	bsq		*obj = malloc(sizeof(bsq));

	if (!obj)
		return (fprintf(stderr, "malloc error\n"), -1);
	init_bsq(obj);
	if (parse_map(obj, file) < 0)
		return (cleanAll(obj), -1);
	if (init_map(obj, file) == -1)
		return (cleanAll(obj), -1);
	if (init_dpTable(obj) == -1)
		return (cleanAll(obj), -1);
	fillDPTable(obj);
	findIndex(obj);
	fillMap(obj);
	printBSQ(obj);
	cleanAll(obj);
	return (0);
}

void	init_bsq(bsq* obj)
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

int	parse_map(bsq* obj, FILE* file)
{
	if (parse_first_line(obj, file) < 0)
		return (-1);
	return (0);
}

int	parse_first_line(bsq* obj, FILE* file)
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

char*	ft_strdup(char* str)
{
	char*	new = NULL;
	size_t	len, i = 0;

	if (!str || !*str)
		return (NULL);
	len = ft_strlen(str);
	new = malloc((len + 1) * sizeof(char));
	if (!new)
		return (fprintf(stderr, "Error: ft_strdup malloc failed\n"), NULL);
	while (i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[len] = '\0';
	return (new);
}

// Fn to get the length of the string upto and not including the '\n' or '\0', whichever comes first
size_t	ft_strlen(char* str)
{
	int	i = 0;

	if (!str || !*str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

/*
Simpler form of atoi fn, with an additional parameter n_chars 
	- only for +ve integers
	- returns -1 when str is NULL
	- returns 0 when str is empty
	- n_chars parameter is to only proceed conversion upto and
	  not including that many characters at the end of str
*/
int	ft_atoi(char* str, size_t n_chars)
{
	int		ret = 0;
	size_t	i = 0, len;

	if (!str)
		return (-1);
	if (!*str)
		return (0);
	while (str[i] && str[i] == ' ')
		i++;
	len = ft_strlen(str) - n_chars;
	while (i < len && str[i] >= '0' && str[i] <= '9')
	{
		ret = ret * 10 + (str[i] - '0');
		i++;
	}
	return (ret);
}

int	init_map(bsq *obj, FILE* file)
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

int	init_dpTable(bsq *obj)
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

void	fillDPTable(bsq* obj)
{
	int		i = -1, j = -1, rows = obj->rows, width = obj->width;
	int		top, left, topLeft;
	char**	map = obj->map;
	int**	dpTable = obj->dpTable;
	char	empty = obj->empty, obs = obj->obs;

	// initializing first row of dpTable
	while (++i < width)
	{
		if (map[0][i] == empty)
			dpTable[0][i] = 1;
		else if (map[0][i] == obs)
			dpTable[0][i] = 0;
	}

	// initializing first column of dpTable
	while (++j < rows)
	{
		if (map[j][0] == empty)
			dpTable[j][0] = 1;
		else if (map[j][0] == obs)
			dpTable[j][0] = 0;
	}

	// filling the rest of the DP table
	j = 0;
	while (++j < rows)
	{
		i = 0;
		while (++i < width)
		{
			if (map[j][i] == empty)
			{
				top = dpTable[j - 1][i];
				left = dpTable[j][i - 1];
				topLeft = dpTable[j - 1][i - 1];
				dpTable[j][i] = 1 + (top < left ? (top < topLeft ? top : topLeft) : (left < topLeft ? left : topLeft));
			}
			else
				dpTable[j][i] = 0;
		}
	}
}

void	findIndex(bsq* obj)
{
	int**	dpTable = obj->dpTable;
	int		i = -1, j = -1, rows = obj->rows, width = obj->width;
	int		ix = 0, iy = 0, newMax = 0;

	while (++j < rows)
	{
		i = -1;
		while (++i < width)
		{
			if (dpTable[j][i] > newMax)
			{
				newMax = dpTable[j][i];
				ix = i;
				iy = j;
			}
		}
	}
	obj->index_mxX = ix;
	obj->index_mxY = iy;
	obj->bSq = newMax;
}

void	fillMap(bsq* obj)
{
	int		ex = obj->index_mxX, ey = obj->index_mxY;
	int		sx = ex - obj->bSq, sy = ey - obj->bSq;
	int		i = sx, j = sy;
	char**	map = obj->map;
	char	full = obj->full;

	while (++j <= ey)
	{
		i = sx;
		while (++i <= ex)
			map[j][i] = full;
	}
}

void	printBSQ(bsq* obj)
{
	if (obj->map)
	{
		int	i = -1;
		while (obj->map[++i])
			fprintf(stdout, "%s\n", obj->map[i]);
	}
}

void	cleanAll(bsq *obj)
{
	int	i = -1;
	if (obj->map)
	{
		while (obj->map[++i])
			free(obj->map[i]);
		free(obj->map);
		obj->map = NULL;
	}

	if (obj->dpTable)
	{
		i = -1;
		while (obj->dpTable[++i])
			free(obj->dpTable[i]);
		free(obj->dpTable);
		obj->dpTable = NULL;
	}
	if (obj->line)
		free(obj->line);
	if (obj)
		free(obj);
}
