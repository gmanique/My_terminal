/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:57:56 by gmanique          #+#    #+#             */
/*   Updated: 2025/04/29 03:54:31 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *p1, const void *p2, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && ((unsigned char *)p1)[i] == ((unsigned char *)p2)[i])
		i++;
	if (size == 0 || i == size)
		return (0);
	return (((unsigned char *)p1)[i] - ((unsigned char *)p2)[i]);
}
