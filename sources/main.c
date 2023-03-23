/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:08:25 by jarthaud          #+#    #+#             */
/*   Updated: 2023/03/23 11:35:45 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	pipex(int f1, int f2, char *cmd1, char *cmd 2)
{
	int		pipefd[2];
	int		status;
	pid_t	child1;
	pid_t	child2;

	pipe(pipefd);
	child1 = fork();
	if (child1 < 0)
		return (perror("Fork: child1"));
	if (child1 == 0)
		child_one(f1, cmd1);
	child2 = fork();
	if (child2 < 0)
		return (perror("Fork: child2"));
	if (child2 == 0)
		child_two(f2, cmd2);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
}

int	main(int argc, char **argv, char **env)
{
	if (argc != 5)
		perror("Invalid number of arguments");
	else
	{
		
	}
}

