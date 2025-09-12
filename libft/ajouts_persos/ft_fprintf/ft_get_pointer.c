/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 04:19:11 by gmanique          #+#    #+#             */
/*   Updated: 2025/06/04 05:50:37 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

static int	nbptlen(unsigned long int nb)
{
	if (nb < 16)
		return (1);
	return (nbptlen(nb / 16) + 1);
}

static char	*ft_toptstr(char *dest, unsigned long int nb)
{
	int		len;
	char	*base;

	base = "0123456789abcdef";
	len = nbptlen(nb);
	dest[len] = '\0';
	while (len--)
	{
		dest[len] = base[nb % 16];
		nb /= 16;
	}
	return (dest);
}

static char	*ft_ulitohex(unsigned long int nb)
{
	char	*rep;
	int		len;

	len = nbptlen(nb);
	rep = malloc((len + 1) * sizeof(char));
	if (rep == NULL)
		return (NULL);
	rep = ft_toptstr(rep, nb);
	return (rep);
}

char	*ft_get_pointer(void *p)
{
	unsigned long int	val;

	if (!p)
		return (ft_strdup("(nil)"));
	val = (unsigned long int)p;
	return (free_join("0x", ft_ulitohex(val), 2));
}
