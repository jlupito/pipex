/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:58:32 by jarthaud          #+#    #+#             */
/*   Updated: 2022/11/24 12:18:18 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tab;

	if (size && ((nmemb * size) / size != nmemb))
		return (NULL);
	tab = malloc(size * nmemb);
	if (!tab)
		return (NULL);
	ft_bzero(tab, (nmemb * size));
	return (tab);
}

// int main(int argc, char **argv)
// {
//     if (argc == 2)
//     {
//         char    *res;
//         int i;
//
//         i = 0;
//         res = ft_calloc(atoi(argv[1]), sizeof(int));
//         while (i < atoi(argv[1]) * (int)sizeof(int))
//         {
//             printf("%c", res[i]);
//             i++;
//         }
//         write(1, &res[i], 1);
// }
//     return (0);
// }
