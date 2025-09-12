/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:57:24 by gmanique          #+#    #+#             */
/*   Updated: 2024/11/13 18:36:40 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		ind;
	int		trouve;
	char	*str;

	str = (char *)s;
	while (!ft_isascii(c))
		c -= 128;
	trouve = 0;
	i = 0;
	if (c == 0)
		return (str + ft_strlen(s));
	while (s[i])
	{
		if (s[i] == c)
		{
			ind = i;
			trouve = 1;
		}
		i ++;
	}
	if (trouve)
		return (&str[ind]);
	return (0);
}
