/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 01:58:07 by pamatya           #+#    #+#             */
/*   Updated: 2025/11/26 02:24:31 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

/*
Allowed functions and globals: malloc, calloc, realloc, free, fopen, fclose,
getline, fscanf, fputs, fprintf, stderr, stdout, stdin, errno
*/



int	main(int ac, char** av)
{
	int		i = 0, nFiles = ac - 1;
	FILE	*files[nFiles];
	bool	validMaps[nFiles];
	
	// Check maps openable/valid
	while (++i <= nFiles)
	{
		files[i - 1] = fopen(av[i], "r");
		if (!files[i - 1])
		{
			fprintf(STDERR_FILENO, "Error: %s: invalid map\n", av[i]);
			validMaps[i - 1] = false;
		}
		else
			validMaps[i - 1] = true;
	}
	

	


	return (0);
}

