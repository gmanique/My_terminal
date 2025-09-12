/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:59:37 by gmanique          #+#    #+#             */
/*   Updated: 2025/04/29 03:53:53 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nblen(int nb)
{
	if (nb / 10 == 0 && nb >= 0)
		return (1);
	if (nb == -2147483648)
		return (11);
	if (nb < 0)
		return (nblen(-nb) + 1);
	return (nblen(nb / 10) + 1);
}

static char	*ft_tostr(char *dest, int nb)
{
	int	len;
	int	i;
	int	val;
	int	neg;

	neg = 0;
	i = 0;
	len = nblen(nb);
	while (i < len)
	{
		val = nb % 10;
		if (val < 0)
		{
			val = -val;
			neg = 1;
		}
		dest[(len - i) - 1] = val + '0';
		nb = nb / 10;
		i++;
	}
	if (neg == 1)
		dest[0] = '-';
	dest[len] = '\0';
	return (dest);
}

char	*ft_itoa(int nb)
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
