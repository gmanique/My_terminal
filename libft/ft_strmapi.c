/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:47:42 by gmanique          #+#    #+#             */
/*   Updated: 2025/04/29 03:55:34 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*rep;

	rep = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (rep == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		rep[i] = f(i, s[i]);
		i++;
	}
	rep[i] = '\0';
	return (rep);
}
