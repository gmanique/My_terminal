/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 04:14:09 by gmanique          #+#    #+#             */
/*   Updated: 2025/06/04 05:50:51 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

static int	nblen(unsigned int nb)
{
	if (nb < 10)
		return (1);
	return (nblen(nb / 10) + 1);
}

static char	*ft_tostr(char *dest, unsigned int nb)
{
	int	len;
	int	i;
	int	val;

	i = 0;
	len = nblen(nb);
	while (i < len)
	{
		val = nb % 10;
		dest[(len - i) - 1] = val + '0';
		nb = nb / 10;
		i++;
	}
	dest[len] = '\0';
	return (dest);
}

char	*ft_uitoa(unsigned int nb)
{
	char	*rep;
	int		len;

	len = nblen(nb);
	rep = malloc((len + 1) * sizeof(char));
	if (rep == NULL)
		return (NULL);
	rep = ft_tostr(rep, nb);
	return (rep);
}
