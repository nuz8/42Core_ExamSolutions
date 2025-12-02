/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 00:43:46 by pamatya           #+#    #+#             */
/*   Updated: 2025/11/30 22:51:14 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int	ft_print_to_stderr(char *str, char *arg)
{
	while (*str)
		write(STDERR_FILENO, str++, 1);
	if (arg)
		while (*arg)
			write(STDERR_FILENO, arg++, 1);
	write(STDERR_FILENO, "\n", 1);
	return (EXIT_FAILURE);
}

int	ft_cd(char **argv, int i)
{
	if (i != 2)
		ft_print_to_stderr("error: cd: bad arguments", NULL);
	if (chdir(argv[1]) == -1)
		ft_print_to_stderr("error: cd: cannot change directory to ", argv[1]);
	return (0);
}

int	ft_execute(char **argv, int i, int tmp_fd, char **env)
{
	int		pid;
	int		status;
	int		fd[2];
	int		has_pipe;

	
	has_pipe = argv[i] && !strcmp(argv[i], "|");
	if (!has_pipe && !strcmp(*argv, "cd"))
		return (ft_cd(argv, i));
	if (has_pipe && pipe(fd) == -1)
		return (ft_print_to_stderr("error: fatal", NULL));
	pid = fork();
	if (pid == -1)
		return (ft_print_to_stderr("error: fatal", NULL));
	if (pid == 0)
	{
		argv[i] = NULL;
		if (has_pipe)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
		}
		execve(*argv, argv, env);
		ft_print_to_stderr("error: cannot execute ", *argv);
		exit(EXIT_FAILURE);
	}
	if (has_pipe)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	waitpid(pid, &status, 0);
	return (WIFEXITED(status) && WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	int		tmp_fd;
	int		status;
	
	(void)argc;
	i = 0;
	tmp_fd = dup(STDIN_FILENO);
	while (argv[i] && argv[i + 1])
	{
		argv = argv + i + 1;
		i = 0;
		while (argv[i] && (!strcmp(argv[i], "|") || !strcmp(argv[i], ";")))
			i++;
		if (i)
			status = ft_execute(argv, i, tmp_fd, env);
	}
	return (status);	
}
