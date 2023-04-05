/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:08:25 by jarthaud          #+#    #+#             */
/*   Updated: 2023/04/05 16:53:42 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_one(int f1, int *pipefd, char *cmd1, char **env)
{
	dup2(pipefd[0], STDOUT_FILENO);
	dup2(f1, STDIN_FILENO);
	printf("fd child1 out: %d\n", f1);
	printf("fd child1 in: %d\n", pipefd[0]);
	close(pipefd[0]);
	close(f1);
	exec_cmd(cmd1, env);
	exit(EXIT_FAILURE);
}

void	child_two(int f2, int *pipefd, char *cmd2, char **env)
{
	dup2(pipefd[1], STDIN_FILENO);
	dup2(f2, STDOUT_FILENO);
	printf("fd child2 out: %d\n", f2);
	printf("fd child2 in: %d\n", pipefd[1]);
	close(pipefd[1]);
	close(f2);
	exec_cmd(cmd2, env);
	exit(EXIT_FAILURE);
}

void	pipex(int f1, int f2, char **argv, char **env)
{
	int		pipefd[2];
	int		status;
	pid_t	child1;
	pid_t	child2;

	pipe(pipefd);
	child1 = fork();
	if (child1 < 0)
		return (perror("Fork: "));
	if (child1 == 0)
		child_one(f1, pipefd, argv[2], env);
	printf("pid1: %d\n", child1);
	child2 = fork();
	if (child2 < 0)
		return (perror("Fork: "));
	if (child2 == 0)
		child_two(f2, pipefd, argv[3], env);
	printf("pid2: %d\n", child2);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
}

int	main(int argc, char **argv, char **env)
{
	int	f1;
	int	f2;

	if (argc != 5)
	{
		perror("Invalid number of arguments");
		exit(EXIT_FAILURE);
	}
	else
	{
		f1 = open(argv[1], O_RDONLY);
		f2 = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		printf("fd1: %d\n", f1);
		printf("fd2: %d\n", f2);
		if (f1 < 0 || f2 < 0)
			return (-1);
		pipex(f1, f2, argv, env);
	}
	return (0);
}
