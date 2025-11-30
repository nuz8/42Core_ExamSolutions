/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:30:39 by pamatya           #+#    #+#             */
/*   Updated: 2025/11/27 20:49:56 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Allowed functions and globals: malloc, calloc, realloc, free, fopen, fclose,
getline, fscanf, fputs, fprintf, stderr, stdout, stdin, errno
*/

#include "bsq.h"

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
