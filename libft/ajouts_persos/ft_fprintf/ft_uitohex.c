/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitohex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 04:15:08 by gmanique          #+#    #+#             */
/*   Updated: 2025/06/04 05:51:14 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

static int	nbhexlen(unsigned int nb)
{
	if (nb < 16)
		return (1);
	return (nbhexlen(nb / 16) + 1);
}

static char	*ft_tohexstr(char *dest, unsigned int nb, char c)
{
	int		len;
	char	*base;

	if (c == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	len = nbhexlen(nb);
	dest[len] = '\0';
	while (len--)
	{
		dest[len] = base[nb % 16];
		nb /= 16;
	}
	return (dest);
}

char	*ft_uitohex(unsigned int nb, char c)
{
	char	*rep;
	int		len;

	len = nbhexlen(nb);
	rep = malloc((len + 1) * sizeof(char));
	if (rep == NULL)
		return (NULL);
	rep = ft_tohexstr(rep, nb, c);
	return (rep);
}
