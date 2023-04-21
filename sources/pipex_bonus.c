/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:08:25 by jarthaud          #+#    #+#             */
/*   Updated: 2023/04/21 17:06:47 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	child_one(t_pipex pipex, char *cmd1, char **env)
{
	pipex.f1 = open(cmd1, O_RDONLY);
	if (access(cmd1, F_OK) < 0)
		err_mg(cmd1, ": No such file or directory\n", pipex, 1);
	if (pipex.f1 < 0)
		err_mg(cmd1, ": Permission denied\n", pipex, 1);
	dup2(pipex.f1, STDIN_FILENO);
	dup2(pipex.pipefd[1], STDOUT_FILENO);
	close_all(pipex);
	exec_cmd(pipex, cmd1, env);
	exit(EXIT_FAILURE);
}

void	child_two(t_pipex pipex, char *cmd2, char **env)
{
	pipex.f2 = open(cmd2, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex.f2 < 0)
		err_mg(cmd2, ": Permission denied\n", pipex, 1);
	dup2(pipex.pipefd[0], STDIN_FILENO);
	dup2(pipex.f2, STDOUT_FILENO);
	close_all(pipex);
	exec_cmd(pipex, cmd2, env);
	exit(EXIT_FAILURE);
}

void	process_pipex(t_pipex pipex, char **argv, char **env, int i)
{
	int		status;

	pipe(pipex.pipefd);
	pipex.child1 = fork();
	if (pipex.child1 < 0)
		err_mg("Error: ", "Failed to fork child process\n", pipex, 1);
	if (pipex.child1 == 0)
		child_one(pipex, argv[i], env);
	pipex.child2 = fork();
	if (pipex.child2 < 0)
		err_mg("Error: ", "Failed to fork child process\n", pipex, 1);
	if (pipex.child2 == 0)
		child_two(pipex, argv[i + 1], env);
	close_all(pipex);
	waitpid(pipex.child1, &status, 0);
	waitpid(pipex.child2, &status, 0);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	int		i;

	i = 1;
	if (argc < 5)
	{
		write(2, "Error: Invalid number of arguments\n", 35);
		exit(EXIT_FAILURE);
	}
	else
	{
		while (++i < argc -2)
			process_pipex(pipex, argv, env, i);
	}
	return (0);
}
