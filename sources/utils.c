/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:06:00 by jarthaud          #+#    #+#             */
/*   Updated: 2023/03/23 16:12:12 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	**get_paths(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	while (!strnstr(env[i], "PATH", 4))
		i++;
	paths = ft_split(env[i] + 5, ':');
	return (paths);
}

char	*get_cmd(char argv*, char **env)
{
	char	**split_paths;
	char	**mycmd;
	int		i;
	char	*cmd;

	split_paths = get_paths(env);
	mycmd = ft_split(argv[2], " ");
	i = 0;
	while (split_paths[i])
	{
		cmd = ft_strjoin(mypaths[i], argv[2]); // protect join
		cmd = ft_strjoin(cmd, "/");
		execve(cmd, mycmd[1], env); // if execve succeeds, exits
		perror("Error");
		free(cmd); // if execve fails, free and try a new path
		i++;
	}
	return (NULL);
}