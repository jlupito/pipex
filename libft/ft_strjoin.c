/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:48:22 by jarthaud          #+#    #+#             */
/*   Updated: 2023/02/16 14:37:28 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_mallocone(char *s1)
// {
// 	s1 = malloc(sizeof(char));
// 	if (!s1)
// 		return (NULL);
// 	s1[0] = '\0';
// 	return (s1);
// }

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*dst;

	if (!s1)
		s1 = ft_mallocone();
	i = 0;
	dst = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dst)
		return (NULL);
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		dst[i++] = s2[j++];
	dst[i] = '\0';
	free(s1);
	return (dst);
}

// int main(int argc, char **argv)
// {
//     if (argc == 3)
// 	{
// 		char	*res;
//
//         res = ft_strjoin(argv[1], argv[2]);
// 		printf("%s\n", res);
// 	}
// 	return (0);
// }
