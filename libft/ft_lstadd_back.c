/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:17:53 by jarthaud          #+#    #+#             */
/*   Updated: 2022/11/24 12:28:04 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*add_last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	else
	{
		add_last = ft_lstlast(*lst);
		add_last->next = new;
	}
}

// int main(void)
// {
// 	t_list	*a;
// 	t_list	*b;

// 	a = ft_lstnew("salut");
// 	b = ft_lstnew("ca va");
// 	ft_lstadd_back(&a, b);
// 	printf("%s\n", (char *)a->content);
// 	printf("%s\n", (char *)a->next->content);
// 	return (0);
// }