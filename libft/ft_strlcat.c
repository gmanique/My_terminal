/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:57:02 by gmanique          #+#    #+#             */
/*   Updated: 2024/11/12 19:24:51 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcat(char *s1, const char *s2, size_t n)
{
	int		i;
	int		j;
	size_t	len;

	len = ft_strlen(s1);
	i = 0;
	j = len;
	if (len >= n)
		return (ft_strlen(s2) + n);
	while (s2[i] && (size_t)i < (n - len - 1))
	{
		s1[i + j] = s2[i];
		i++;
	}
	s1[i + j] = '\0';
	return (ft_strlen(s2) + len);
}
