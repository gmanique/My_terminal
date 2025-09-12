/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:59:22 by gmanique          #+#    #+#             */
/*   Updated: 2025/04/29 03:55:44 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	dedans(char c, char const *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		deb;
	int		fin;
	char	*rep;
	int		i;

	deb = 0;
	fin = ft_strlen(s1);
	while (dedans(s1[deb], set) == 1)
		deb += 1;
	while (dedans(s1[fin - 1], set) == 1)
		fin -= 1;
	if (fin > deb)
		rep = malloc((1 + fin - deb) * sizeof(char));
	else
		rep = malloc(1 * sizeof(char));
	if (rep == NULL)
		return (NULL);
	i = 0;
	while (i < fin - deb)
	{
		rep[i] = s1[deb + i];
		i++;
	}
	rep[i] = '\0';
	return (rep);
}
