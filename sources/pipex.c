/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:08:25 by jarthaud          #+#    #+#             */
/*   Updated: 2023/04/07 15:34:20 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_one(t_pipex pipex, char *cmd1, char **env)
{
	dup2(pipex.f1, STDIN_FILENO);
	dup2(pipex.pipefd[1], STDOUT_FILENO);
	close_all(pipex);
	exec_cmd(pipex, cmd1, env);
	exit(EXIT_FAILURE);
}

void	child_two(t_pipex pipex, char *cmd2, char **env)
{
	dup2(pipex.f2, STDOUT_FILENO);
	dup2(pipex.pipefd[0], STDIN_FILENO);
	close_all(pipex);
	exec_cmd(pipex, cmd2, env);
	exit(EXIT_FAILURE);
}

void	process_pipex(t_pipex pipex, char **argv, char **env)
{
	int		status;

	pipe(pipex.pipefd);
	pipex.child1 = fork();
	if (pipex.child1 < 0)
		return (perror("Fork: "));
	if (pipex.child1 == 0)
		child_one(pipex, argv[2], env);
	pipex.child2 = fork();
	if (pipex.child2 < 0)
		return (perror("Fork: "));
	if (pipex.child2 == 0)
		child_two(pipex, argv[3], env);
	close_all(pipex);
	waitpid(pipex.child1, &status, 0);
	waitpid(pipex.child2, &status, 0);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc != 5)
		perror("Invalid number of arguments");
	else
	{
		pipex.f1 = open(argv[1], O_RDONLY);
		pipex.f2 = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (pipex.f1 < 0 || pipex.f2 < 0)
			return (-1);
		process_pipex(pipex, argv, env);
	}
	return (0);
}
