/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:06:00 by jarthaud          #+#    #+#             */
/*   Updated: 2023/04/07 15:59:32 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_all(char **str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[len])
		len++;
	while (i < len)
		free(str[i++]);
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

char	*exec_cmd(t_pipex pipex, char *argv, char **env)
{
	int		i;

	i = 0;
	pipex.split_paths = get_paths(env);
	pipex.cmd_options = ft_split(argv, ' ');
	while (pipex.split_paths[i])
	{
		pipex.path = ft_strjoin(pipex.split_paths[i], "/");
		pipex.path = ft_strjoin(pipex.path, pipex.cmd_options[0]);
		if (!access(pipex.path, X_OK))
			execve(pipex.path, pipex.cmd_options, env);
		free(pipex.path);
		i++;
	}
	perror("Command not found:");
	free(pipex.split_paths);
	free_all(pipex.cmd_options);
	return (NULL);
}
