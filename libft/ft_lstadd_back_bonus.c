/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:29:35 by gmanique          #+#    #+#             */
/*   Updated: 2025/04/29 03:54:01 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tampon;

	if (!new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		tampon = *lst;
		while (tampon->next)
		{
			tampon = tampon->next;
		}
		tampon->next = new;
	}
}
