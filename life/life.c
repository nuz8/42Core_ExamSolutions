/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 23:45:49 by pamatya           #+#    #+#             */
/*   Updated: 2025/11/25 20:23:10 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <string.h>

// Allowed: atoi, read, putchar, malloc, calloc, realloc, free
// echo 'sdxssdswdxddddsxaadwxwdxwaa' | ./a.out 10 6 0 | cat -e

char***	allocate_board(int iter, int width, int height);
void	initialize_board(char ***board, int iter, int width, int height);
void	simulate_board(char*** board, int iter, int width, int height);
int		get_neighbours(char** prev_instance, int x, int y, int width, int height);
char	get_new_state(char old_state, int nbrs);
void	map_board(char ***board, int width, int height);
void	print_board_instance(char **board, int width, int height);
void	clear_board(char*** board);

void	printF_board_instance(char **board, int height);
void	show_evolution(char*** board, int iter, int width, int height);

int main(int ac, char** av)
{
	int		width, height, iter;
	char***	board;
	
	if (ac != 4)
		return (putchar('e'), 1);

	width = atoi(av[1]);
	height = atoi(av[2]);
	iter = atoi(av[3]);
	
	board = allocate_board(iter, width, height);
	if (!board)
		return (clear_board(board), putchar('e'), 1);

	initialize_board(board, iter, width, height);
	map_board(board, width, height);
	if (iter)
		simulate_board(board, iter, width, height);
	print_board_instance(board[iter], width, height);
	show_evolution(board, iter, width, height);
	return (clear_board(board), 0);
}

char***	allocate_board(int iter, int width, int height)
{
	char***	board;
	int		i, j;

	board = malloc((iter + 2) * (sizeof(char**)));	// Allocating 'iter + 1' copies of board(height x width) for each evolution-step; +1 for current set-up w/o evolution, and +1 for final pointer to be set to NULL
	if (!board)
		return (NULL);
	i = -1;
	while (++i < iter + 1)								// Iterate from 0 to (iter - 1) as board[iter] is NULL
	{
		board[i] = malloc((height + 2) * sizeof(char*));
		if (!(board[i]))
			return (NULL);
		j = -1;
		while (++j < (height + 1))						// Allocating char* at indices starting form 0 to (height+2) to use board indices from 1 to height and then set height+1 index as NULL
		{
			board[i][j] = malloc((width + 2) * sizeof(char));	// Allocating strings of length 'width+2'
			if (!(board[i][j]))
				return (NULL);
			board[i][j][width + 1] = '\0';						// Setting the last char of the allocated string to '\0'
		}
		board[i][height + 1] = NULL;					// Setting the pointer at index 'height+1' as NULL
	}
	board[iter + 1] = NULL;							// Final pointer set to null to identify end of evolution-iteration
	return (board);
}

void	initialize_board(char ***board, int iter, int width, int height)
{
	int		i = -1, j = -1, k = -1;
	while (++i < (iter + 1))
	{
		j = -1;
		while (++j < (height + 1))
		{
			k = -1;
			while (++k < (width + 1))
				board[i][j][k] = ' ';
			board[i][j][k] = '\0';
		}
	}
}

void	map_board(char ***board, int width, int height)
{
	int		x = 1, y = 1;
	bool	pen = false;
	char	cmd;

	while (read(STDIN_FILENO, &cmd, 1) > 0)
	{
		if (cmd == 'w' && y > 1)
			y--;
		else if (cmd == 's' && y < height)
			y++;
		else if (cmd == 'a' && x > 1)
			x--;
		else if (cmd == 'd' && x < width)
			x++;
		else if (cmd == 'x')
			pen = !pen;
		if (pen)
			board[0][y][x] = 'O';
	}
}

void	simulate_board(char*** board, int iter, int width, int height)
{
	int		x = 0, y = 0, i = 0, nbrs = 0;
	char**	prev_instance;
	char**	new_instance;

	while (++i <= iter)
	{
		prev_instance = board[i - 1];
		new_instance = board[i];
		y = 0;
		while (++y <= height)
		{
			x = 0;
			while (++x <= width)
			{
				nbrs = get_neighbours(prev_instance, x, y, width, height);
				new_instance[y][x] = get_new_state(prev_instance[y][x], nbrs);
			}
		}
	}
}

int	get_neighbours(char** prev_instance, int x, int y, int width, int height)
{
	int ix, iy, sx, sy, ex, ey, nbrs = 0;

	sx = (x - 1 >= 1) ? x - 1 : 1;
	ex = (x + 1 <= width) ? x + 1 : width;
	sy = (y - 1 >= 1) ? y - 1 : 1;
	ey = (y + 1 <= height) ? y + 1 : height;
	
	iy = sy;
	while (iy <= ey)
	{
		ix = sx;
		while (ix <= ex)
		{
			if (!(ix == x && iy == y) && prev_instance[iy][ix] == 'O')
				nbrs++;
			ix++;
		}
		iy++;
	}
	return (nbrs);
}

char	get_new_state(char old_state, int nbrs)
{
	if (old_state == ' ')			// Previously dead cell
	{
		if (nbrs == 3)
			return ('O');			// Dead cell comes alive i.e. reproduction
		else
			return (' ');			// Dead cell stays dead
	}
	else							// Previously alive cell
	{
		if (nbrs < 2 || nbrs > 3)	// Under-population or over-population
			return (' ');			// Alive cell dies
		else						// Optimum population
			return ('O');			// Alive cell stays alive
	}
}

void	print_board_instance(char **board, int width, int height)
{
	int x = 1, y = 0;
	while (++y <= height)
	{
		x = 0;
		while (++x <= width)
			putchar(board[y][x]);
		putchar('\n');
	}
}

void	clear_board(char*** board)
{
	int	i, j;
	
	if (board)
	{
		i = -1;
		while (board[++i])
		{
			j = -1;
			while (board[i][++j])
				free(board[i][j]);
			free(board[i]);	
		}
		free(board);
	}
}

void	printF_board_instance(char **board, int height)
{
	int y = 0;
	while (++y <= height)
		printf("%s\n", (board[y] + 1));
	fflush(STDIN_FILENO);
}

void	show_evolution(char*** board, int iter, int width, int height)
{
	int i = 0;
	(void)width;
	while (++i <= iter)
	{
		printF_board_instance(board[i], height);
		putchar('\n');
		usleep(500000);
	}
}
