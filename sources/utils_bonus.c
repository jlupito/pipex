/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:06:00 by jarthaud          #+#    #+#             */
/*   Updated: 2023/04/13 16:52:26 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	free_all(char **str)
{
	int	i;

	i = ft_strlen(str);
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

char	**get_paths(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	while (!ft_strnstr(env[i], "PATH", 4))
		i++;
	paths = ft_split(env[i] + 5, ':');
	return (paths);
}

void	err_mg(char *arg, char *str, t_pipex pipex, int flag)
{
	if (flag == 1 || flag == 2)
	{
		write(2, arg, ft_strlen(arg));
		write(2, str, ft_strlen(str));
	}
	if (flag == 2)
	{
		if (pipex.split_paths)
			free(pipex.split_paths);
		if (pipex.cmd_args)
			free_all(pipex.cmd_args);
	}
	close_all(pipex);
	exit(EXIT_FAILURE);
}

void	exec_cmd(t_pipex pipex, char *argv, char **env)
{
	int		i;

	i = -1;
	pipex.cmd_args = ft_split(argv, ' ');
	if (!access(argv, X_OK))
	{
		if (execve(pipex.cmd_args[0], pipex.cmd_args, env) == -1)
			err_mg(pipex.cmd_args[0], ": command not found\n", pipex, 2);
	}
	else
	{
		pipex.split_paths = get_paths(env);
		while (pipex.split_paths[++i])
		{
			pipex.path = ft_strjoin(pipex.split_paths[i], "/");
			pipex.path = ft_strjoin(pipex.path, pipex.cmd_args[0]);
			if (!access(pipex.path, X_OK))
			{
				if (execve(pipex.path, pipex.cmd_args, env) == -1)
					err_mg(pipex.cmd_args[0], ": command not found\n", pipex, 2);
			}
			free(pipex.path);
		}
		err_mg(pipex.cmd_args[0], ": command not found\n", pipex, 2);
	}
}
