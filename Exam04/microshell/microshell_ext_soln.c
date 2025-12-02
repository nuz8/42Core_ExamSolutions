/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell_ext_soln.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:57:55 by pamatya           #+#    #+#             */
/*   Updated: 2025/05/15 00:41:27 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int err(char *str)
{
    while (*str)
        write(2, str++, 1);
    return (1);
}

int ft_cd(char **argv, int i)
{
    if (i != 2)
        return(err("error: cd: bad arguments\n"));
    if (chdir(argv[1]) == -1)
        return (err("error: cd: cannot change directory to "), err(argv[1]), err("\n"));
    return (0);
}

void set_pipe(int has_pipe, int *fd, int end)
{
    if (has_pipe && (dup2(fd[end], end) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
        err("error: fatal\n");
}

int exec(char **argv, int i, char **envp)
{
    int pid;
    int status;
    int fd[2];
    int has_pipe;

    has_pipe = argv[i] && !strcmp(argv[i], "|");
    if (!has_pipe && !strcmp(*argv, "cd"))
        return (ft_cd(argv, i));
    if (has_pipe && pipe(fd) == -1)
        return (err("error: fatal\n"));
    if ((pid = fork()) == -1)
        return (err("error: fatal\n"));
    if (pid == 0)
    {
        argv[i] = 0;
        set_pipe(has_pipe, fd, 1);
        if (!strcmp(*argv, "cd"))
            return(ft_cd(argv, i));
        execve(*argv, argv, envp);
        return (err("error: cannot execute "), err(*argv), err("\n"));
    }
    set_pipe(has_pipe, fd, 0);
    waitpid(pid, &status, 0);
    return (WIFEXITED(status) && WEXITSTATUS(status));
}

int main(int argc, char **argv, char **envp)
{
    int i;
    int status;

    i = 0;
    status = 0;
    (void)argc;

    while (argv[i])
    {
        argv += i + 1;
        i = 0;
        while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
            i++;
        if (i)
            status = exec(argv, i, envp);
    }
    return (status);
}
