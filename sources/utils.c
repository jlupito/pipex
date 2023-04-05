/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:06:00 by jarthaud          #+#    #+#             */
/*   Updated: 2023/04/05 14:57:34 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void free_all(char **str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[len])
		len++;
	while (i < len)
		free(str[i++]);
	free(str);
}

char	**get_paths(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	while (!ft_strnstr(env[i], "PATH", 4))
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths)
	{
		printf("path; %s\n", paths[i]);
		i++;
	}
	return (paths);
}

char	*exec_cmd(char *argv, char **env)
{
	char	**split_paths;
	char	**cmd_options;
	int		i;
	char	*path;

	split_paths = get_paths(env);
	cmd_options = ft_split(argv, ' ');
	i = 0;
	while (split_paths[i])
	{
		path = ft_strjoin(split_paths[i], "/");
		// cmd = ft_strjoin(cmd, cmd_option[0]);
		printf("cmd: %s\n", path);
		execve(path, cmd_options, env);
		perror("Error");
		free(path);
		i++;
	}
	free_all(split_paths);
	free_all(cmd_options);
	return (NULL);
}
