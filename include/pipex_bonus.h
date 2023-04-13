/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:08:19 by jarthaud          #+#    #+#             */
/*   Updated: 2023/04/13 14:50:15 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		f1;
	int		f2;
	int		child1;
	int		child2;
	int		pipefd[2];
	char	**split_paths;
	char	**cmd_args;
	char	*path;
}			t_pipex;

void	child_two(t_pipex pipex, char *cmd2, char **env);
void	child_one(t_pipex pipex, char *cmd1, char **env);
void	close_all(t_pipex pipex);
void	free_all(char **str);
void	process_pipex(t_pipex pipex, char **argv, char **env, int argc);
char	**get_paths(char **env);
void	exec_cmd(t_pipex pipex, char *argv, char **env);
void	err_mg(char *argv, char *str, t_pipex pipex, int flag);

#endif
