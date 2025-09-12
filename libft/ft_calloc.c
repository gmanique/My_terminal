/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:58:27 by gmanique          #+#    #+#             */
/*   Updated: 2025/04/29 03:53:42 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	void	*rep;
	size_t	len;

	len = elementSize * elementCount;
	if ((int)len < 0 || ((int)elementSize < 0 && (int)elementCount < 0))
		return (NULL);
	rep = (void *)malloc(len);
	if (!rep)
		return (NULL);
	ft_memset(rep, 0, len);
	return (rep);
}
