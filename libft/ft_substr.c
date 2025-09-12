/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:59:05 by gmanique          #+#    #+#             */
/*   Updated: 2024/11/19 15:29:26 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	char			*rep;
	unsigned int	mal_size;

	if ((unsigned long)ft_strlen(s) - (unsigned long)start < (unsigned long)len)
		mal_size = ft_strlen(s) - start + 1;
	else if (start > (unsigned int)ft_strlen(s))
		mal_size = 1;
	else
		mal_size = len + 1;
	rep = malloc(mal_size * sizeof(char));
	if (rep == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[i] && i + start < (unsigned int)ft_strlen(s))
	{
		rep[i] = s[i + start];
		i++;
	}
	rep[i] = '\0';
	return (rep);
}
