/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:30:09 by gmanique          #+#    #+#             */
/*   Updated: 2024/11/21 15:13:42 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	void	*buff;

	new_list = 0;
	if (!lst || !f || !del)
		return (NULL);
	buff = f(lst->content);
	new_list = ft_lstnew(buff);
	lst = lst->next;
	while (lst)
	{
		buff = f(lst->content);
		ft_lstadd_back(&new_list, ft_lstnew(buff));
		if (!new_list)
		{
			ft_lstclear(&new_list, del);
			del(buff);
			return (NULL);
		}
		lst = lst->next;
	}
	return (new_list);
}
