/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:08:19 by jarthaud          #+#    #+#             */
/*   Updated: 2023/04/05 14:45:54 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

void	child_two(int f2, int *pipefd, char *cmd2, char **env);
void	child_one(int f1, int *pipefd, char *cmd1, char **env);
void	pipex(int f1, int f2, char **argv, char **env);
char	**get_paths(char **env);
char	*exec_cmd(char *argv, char **env);

#endif
