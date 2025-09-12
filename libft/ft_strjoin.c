/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amados-s <amados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:59:13 by gmanique          #+#    #+#             */
/*   Updated: 2025/06/24 08:44:02 by amados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*rep;
	int		i;
	int		j;

	if (!s1)
		return (ft_strdup((char *)s2));
	if (!s2)
		return (ft_strdup((char *)s1));
	rep = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (rep == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		rep[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		rep[i + j] = s2[j];
		j++;
	}
	rep[i + j] = '\0';
	return (rep);
}
