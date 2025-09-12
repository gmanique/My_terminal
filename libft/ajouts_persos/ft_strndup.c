/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:52:22 by gmanique          #+#    #+#             */
/*   Updated: 2025/05/24 18:25:33 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ajouts.h"

char	*ft_strndup(char *dup, int n)
{
	char	*rep;
	int		i;

	rep = ft_calloc(n + 1, sizeof(char));
	if (!rep)
		return (NULL);
	i = 0;
	while (i < n)
	{
		rep[i] = dup[i];
		i++;
	}
	return (rep);
}
