/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:23:54 by pamatya           #+#    #+#             */
/*   Updated: 2025/11/27 20:40:03 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

char*	ft_strdup(char* str);
size_t	ft_strlen(char* str);
int		ft_atoi(char* str, size_t n_chars);
void	cleanAll(bsq *obj);
void	print_struct_bsq(bsq* obj);

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

void	print_struct_bsq(bsq* obj)
{	
	int	i, j;
	
	fprintf(stdout, "rows	:	%d\n", obj->rows);
	fprintf(stdout, "width	:	%d\n", obj->width);
	fprintf(stdout, "empty	:	%c\n", obj->empty);
	fprintf(stdout, "obs	:	%c\n", obj->obs);
	fprintf(stdout, "full	:	%c\n", obj->full);
	fprintf(stdout, "index	:	(%d, %d)\n", obj->index_mxX, obj->index_mxY);
	fprintf(stdout, "bSq	:	%d\n", obj->bSq);
	fprintf(stdout, "\n");

	// printing the map
	if (obj->map)
	{
		i = -1;
		while (obj->map[++i])
			fprintf(stdout, "%d:\t:%d\t%s\n", i + 1, obj->width, obj->map[i]);
	}
	fprintf(stdout, "\n");

	// printing dpTable
	if (obj->dpTable)
	{
		j = -1;
		while (++j < obj->rows)
		{
			i = -1;
			fprintf(stdout, "%d:\t:%d\t", j + 1, obj->width);
			while (++i < obj->width)
				fprintf(stdout, "%d", obj->dpTable[j][i]);
			fprintf(stdout, "\n");
		}
	}
	fprintf(stdout, "\n");
}
