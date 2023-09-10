/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:02:29 by jutrera-          #+#    #+#             */
/*   Updated: 2022/09/27 19:31:59 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*aux;
	void	*temp;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		temp = f(lst->content);
		aux = ft_lstnew(temp);
		if (!aux)
		{
			free(temp);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, aux);
		lst = lst->next;
	}
	return (new_list);
}
/*
	t_list	*newlst;
	t_list	*q1;
	t_list	*q2;

	if (!lst || !f || !del)
		return (0);
	newlst = ft_lstnew(f(lst->content));
	if (!newlst)
		return (0);
	q1 = newlst;
	lst = lst->next;
	while (lst)
	{
		q2 = ft_lstnew(f(lst->content));
		if (!q2)
		{
			ft_lstclear(&newlst, del);
			return (0);
		}
		q1->next = q2;
		lst = lst->next;
		q1 = q2;
	}
	return (newlst);
}
*/