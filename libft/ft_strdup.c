/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:59:12 by jarthaud          #+#    #+#             */
/*   Updated: 2022/11/15 18:32:34 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dst;
	int		i;

	i = 0;
	dst = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dst)
		return (NULL);
	while (s[i])
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

// int	main(int argc, char **argv)
// {
//     if (argc == 2)
// 	{
//         char    *p1;
//         char    *p2;

//         p1 = printf("true: %s", strdup(argv[1]));
//         p2 = printf("mine: %s", ft_strdup(argv[1]));
//     }
// 	return (0);
// }