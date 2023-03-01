/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42quebec.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:26:21 by vjean             #+#    #+#             */
/*   Updated: 2022/05/09 13:01:49 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;

	if (!lst)
		return (NULL);
	newlst = ft_lstnew(f(lst->content));
	lst = lst->next;
	while (lst)
	{
		ft_lstadd_back(&newlst, ft_lstnew(f(lst->content)));
		if (ft_lstlast(newlst) == NULL)
		{
			ft_lstclear(&newlst, *del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (newlst);
}
