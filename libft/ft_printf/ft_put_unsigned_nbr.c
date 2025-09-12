/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_unsigned_nbr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:08:59 by gmanique          #+#    #+#             */
/*   Updated: 2024/11/18 18:37:30 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_unsigned_nbr(unsigned int nb)
{
	unsigned int	aff;
	char			c;
	int				rep;

	rep = 1;
	if (nb > 9)
		rep += ft_put_unsigned_nbr(nb / 10);
	aff = nb % 10;
	c = aff + '0';
	write(1, &c, 1);
	return (rep);
}
