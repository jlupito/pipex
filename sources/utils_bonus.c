/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:06:00 by jarthaud          #+#    #+#             */
/*   Updated: 2023/04/21 16:58:15 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
		free(str[i--]);
	if (str)
		free(str);
}

void	close_all(t_pipex pipex)
{
	close(pipex.f1);
	close(pipex.f2);
	close(pipex.pipefd[0]);
	close(pipex.pipefd[1]);
}

void	err_mg(char *argv, char *str, t_pipex pipex, int flag)
{
	write(2, argv, ft_strlen(argv));
	write(2, str, ft_strlen(str));
	if (flag == 2)
	{
		free_all(pipex.cmd_args);
		free(pipex.split_paths);
		close_all(pipex);
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(EXIT_FAILURE);
}

void	get_paths(char **env, t_pipex *pipex)
{
	int		i;

	i = -1;
	while (env[++i])
	{
		if (ft_strnstr(env[i], "PATH", 4))
		{
			pipex->split_paths = ft_split(env[i] + 5, ':');
			return ;
		}
	}
	pipex->split_paths = ft_split(pipex->cmd_args[0], ' ');
}

void	exec_cmd(t_pipex pipex, char *argv, char **env)
{
	int	i;

	i = 0;
	pipex.cmd_args = ft_split(argv, ' ');
	get_paths(env, &pipex);
	if (!access(pipex.cmd_args[0], F_OK))
	{
		if (execve(pipex.cmd_args[0], pipex.cmd_args, env) < 0)
			err_mg(pipex.cmd_args[0], ": command not found\n", pipex, 2);
	}
	i = -1;
	while (pipex.split_paths[++i])
	{
		pipex.path = ft_strjoin(pipex.split_paths[i], "/");
		pipex.path = ft_strjoin(pipex.path, pipex.cmd_args[0]);
		if (!access(pipex.path, X_OK))
		{
			if (execve(pipex.path, pipex.cmd_args, env) < 0)
				err_mg(pipex.cmd_args[0], ": command not found\n", pipex, 2);
		}
		free(pipex.path);
	}
	err_mg(pipex.cmd_args[0], ": command not found\n", pipex, 2);
}
