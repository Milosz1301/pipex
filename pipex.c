/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstawski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:05:26 by mstawski          #+#    #+#             */
/*   Updated: 2025/07/24 16:53:21 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"

char	*ft_trunc(char *string)
{
	char	*trunc_string;
	int		i;

	trunc_string = malloc(ft_strlen(string) + 2);
	i = -1;
	while (string[++i])
		trunc_string[i] = string[i];
	trunc_string[i++] = '/';
	trunc_string[i] = '\0';
	return (trunc_string);
}

void	second_child(char *argv[], char *enpv[], int pipe_fd[], int file2_fd)
{
	char	**env_arr;
	char	**arg_arr;
	int		i;

	i = 0;
	while (!(ft_strnstr(enpv[i], "PATH", 4)))
		i++;
	env_arr = ft_split(enpv[i] + 5, ':');
	arg_arr = ft_split(argv[3], ' ');
	i = 0;
	while (access(ft_strjoin(ft_trunc(env_arr[i]), arg_arr[0]), X_OK | F_OK))
		i++;
	if (!(env_arr[i]))
		exit(10);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	dup2(file2_fd, STDOUT_FILENO);
	close(pipe_fd[0]);
	execve(ft_strjoin(ft_trunc(env_arr[i]), arg_arr[0]), arg_arr, env_arr);
	free(env_arr);
	free(arg_arr);
	exit(9);
}

void	first_child(char *argv[], char *enpv[], int pipe_fd[])
{
	char	**env_arr;
	char	**arg_arr;
	int		i;

	i = 0;
	while (!(ft_strnstr(enpv[i], "PATH", 4)))
		i++;
	env_arr = ft_split(enpv[i] + 5, ':');
	arg_arr = ft_split(argv[2], ' ');
	i = 0;
	while (access(ft_strjoin(ft_trunc(env_arr[i]), arg_arr[0]), X_OK | F_OK))
		i++;
	if (!(env_arr[i]))
		exit(6);
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	execve(ft_strjoin(ft_trunc(env_arr[i]), arg_arr[0]), arg_arr, env_arr);
	free(env_arr);
	free(arg_arr);
	exit(7);
}

void	parent(char *argv[], char *enpv[], int file1_fd, int file2_fd)
{
	int	pid1;
	int	pid2;
	int	pipe_fd[2];

	dup2(file1_fd, STDIN_FILENO);
	close(file1_fd);
	if ((pipe(pipe_fd) == -1))
		exit(4);
	pid1 = fork();
	if (pid1 == -1)
		exit(5);
	if (pid1 == 0)
		first_child(argv, enpv, pipe_fd);
	else
	{
		wait(NULL);
		pid2 = fork();
		if (pid2 == -1)
			exit(8);
		if (pid2 == 0)
			second_child(argv, enpv, pipe_fd, file2_fd);
	}
}

int	main(int argc, char *argv[], char *enpv[])
{
	int	file1_fd;
	int	file2_fd;

	if (argc != 5)
		exit(1);
	file1_fd = open(argv[1], O_RDONLY);
	if (file1_fd == -1)
		exit(2);
	file2_fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (file2_fd == -1)
		exit(3);
	parent(argv, enpv, file1_fd, file2_fd);
	return (0);
}
