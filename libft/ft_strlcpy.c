/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:56:53 by gmanique          #+#    #+#             */
/*   Updated: 2025/04/29 03:55:23 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcpy(char *s1, const char *s2, size_t size)
{
	size_t	i;
	size_t	size_str;

	size_str = ft_strlen(s2);
	if (size == 0)
		return (size_str);
	i = 0;
	while (s2[i] && i < size - 1)
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (size_str);
}
