/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:13:46 by jarthaud          #+#    #+#             */
/*   Updated: 2022/11/17 11:22:50 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = '\0';
		i++;
	}
}

// int	main(int argc, char **argv)
// {
// 	if (argc == 3)
// 		{
// 		//char	p1;
// 		char	p2;

// 		//p1 = bzero(argv[1], atoi(argv[2]));
// 		p2 = bzero(argv[1], atoi(argv[2]));
// 		//printf("good: %d\n", p1);
// 		printf("mine: %d", p2);
// 		}
// 	return(0);
// }