/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:06:00 by jarthaud          #+#    #+#             */
/*   Updated: 2023/03/29 17:30:05 by jarthaud         ###   ########.fr       */
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
	return (paths);
}

char	*get_cmd(char *argv, char **env)
{
	char	**split_paths;
	char	**cmd_option;
	int		i;
	char	*cmd;

	split_paths = get_paths(env);
	cmd_option = ft_split(argv, ' ');
	i = 0;
	while (split_paths[i])
	{
		cmd = ft_strjoin(split_paths[i], "/");
		cmd = ft_strjoin(cmd, cmd_option[0]);
		execve(cmd, cmd_option[1], env);
		perror("Error");
		free(cmd);
		i++;
	}
	free_all(split_paths);
	free_all(cmd_option);
	return (NULL);
}
