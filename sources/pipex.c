/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:08:25 by jarthaud          #+#    #+#             */
/*   Updated: 2023/04/26 11:22:35 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_one(t_pipex pipex, char *cmd1, char **env)
{
	dup2(pipex.f1, STDIN_FILENO);
	dup2(pipex.pipefd[1], STDOUT_FILENO);
	close(pipex.pipefd[0]);
	exec_cmd(pipex, cmd1, env);
	exit(EXIT_FAILURE);
}

void	child_two(t_pipex pipex, char *cmd2, char **env)
{
	dup2(pipex.pipefd[0], STDIN_FILENO);
	dup2(pipex.f2, STDOUT_FILENO);
	close(pipex.pipefd[1]);
	exec_cmd(pipex, cmd2, env);
	exit(EXIT_FAILURE);
}

int	process_pipex(t_pipex pipex, char **argv, char **env, int i)
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
	waitpid(pipex.child1, NULL, 0);
	waitpid(pipex.child2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	int		i;
	int		return_value;

	i = 2;
	if (argc != 5)
	{
		write(2, "Error: Invalid number of arguments\n", 35);
		exit(EXIT_FAILURE);
	}
	else
	{
		pipex.f1 = open(argv[1], O_RDONLY);
		pipex.f2 = open(argv[argc -1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (access(argv[1], F_OK) < 0)
			err_mg(argv[1], ": No such file or directory\n", pipex, 4);
		if (pipex.f1 < 0)
			err_mg(argv[1], ": Permission denied\n", pipex, 4);
		if (pipex.f2 < 0)
			err_mg(argv[argc -1], ": Permission denied\n", pipex, 1);
		return_value = process_pipex(pipex, argv, env, i);
	}
	return (return_value);
}
