/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valids.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:24:44 by pamatya           #+#    #+#             */
/*   Updated: 2025/11/29 00:21:30 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int		parse_first_line(bsq* obj, FILE* file);
int		validate_map(bsq* obj);

int	parse_first_line(bsq* obj, FILE* file)
{
	char*	fline = NULL;
	size_t	len;
	ssize_t	read;

	read = getline(&obj->line, &obj->len, file);
	if (read < 0) {
		if (errno == EINVAL || errno == ENOMEM)
			return (fprintf(stderr, "Error: getline failed\n"), -1);
		else	// means EOF, and that the file is empty
			return (fprintf(stderr, "Error: map error: empty file\n"), -1);
	}
	fline = ft_strdup(obj->line);
	if (!fline)
		return (fprintf(stderr, "Error: ft_strdup(): returned NULL\n"), -1);

	// Validate that the first line has atleast 4 chars
	if (ft_strlen(fline) < 4)
		return (free(fline), fprintf(stderr, "Error: map error: missing characters\n"), -1);

	len = ft_strlen(obj->line);
	obj->empty = fline[len - 3];
	obj->obs = fline[len - 2];
	obj->full = fline[len - 1];
	obj->rows = ft_atoi(fline, 3);
	obj->first_line = fline;
	return (0);
}

int	validate_map(bsq* obj)
{
	int		i = -1, j = -1, rows = obj->rows, width = obj->width;
	char*	fline = obj->first_line;
	char**	map = obj->map;
	char	empty = obj->empty, obs = obj->obs, full = obj->full;

	// Validate control chars are printable
	while (fline[++i])
		if (!ft_isprint(fline[i]))
			return (fprintf(stderr, "Error: map error: non-printable\n"), -1);	

	// Validate that the first char is a number
	if (!(fline[0] >= '0' && fline[0] <= '9'))
		return (fprintf(stderr, "Error: map error: missing rows info-number\n"), -1);	

	// Validate that the control chars are unique
	if (empty == obs || empty == full || obs == full)
		return (fprintf(stderr, "Error: map error: characters not unique\n"), -1);	

	// Validate that the map only contains introduced characters
	while (++j < rows)
	{
		i = -1;
		while (++i < width)
		{
			if (map[j][i] == full)
				return (fprintf(stderr, "Error: map error: map cannot contain 'full' character\n"), -1);
			if (map[j][i] != empty && map[j][i] != obs)
				return (fprintf(stderr, "Error: map error: map contains non-introduced characters\n"), -1);
		}
	}
	return (0);
}
