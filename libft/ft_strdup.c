/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amados-s <amados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:58:36 by gmanique          #+#    #+#             */
/*   Updated: 2025/06/24 08:39:14 by amados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char	*src)
{
	char	*rep;
	int		i;

	if (!src)
		return (NULL);
	rep = malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!rep)
		return (NULL);
	i = 0;
	while (src[i])
	{
		rep[i] = src[i];
		i++;
	}
	rep[i] = '\0';
	return (rep);
}
