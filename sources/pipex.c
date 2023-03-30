/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:08:25 by jarthaud          #+#    #+#             */
/*   Updated: 2023/03/30 14:24:35 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_one(f1, cmd1);
{
	dup2(f1, STDIN_FILENO); // f1 = execve() input
	dup2(end[1], STDOUT_FILENO); //end[1] = execve() stdout
	close(end[0]);
	close(f1);
	get_cmd(cmd1, env);
	// execve function for each possible path (see below)
	exit(EXIT_FAILURE);
}

void	pipex(int f1, int f2, char *cmd1, char *cmd2)
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
		child_one(f1, cmd1);
	child2 = fork();
	if (child2 < 0)
		return (perror("Fork: "));
	if (child2 == 0)
		child_two(f2, cmd2);
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
		perror("Invalid number of arguments");
	else
	{
		f1 = open(argv[1], O_RDONLY);
		f2 = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (f1 < 0 || f2 < 0)
			return (-1);
		pipex(f1, f2, argv[2], argv[3]);
	}
	return (0);
}

