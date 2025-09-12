/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:12:20 by gmanique          #+#    #+#             */
/*   Updated: 2024/11/19 17:19:57 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putulhexa(unsigned long int nb)
{
	unsigned int	aff;
	char			c;
	int				rep;

	rep = 1;
	if (nb > 15)
		rep += ft_putulhexa(nb / 16);
	aff = nb % 16;
	if (aff < 10)
		c = aff + '0';
	else
		c = (aff % 10) + 'a';
	write(1, &c, 1);
	return (rep);
}

int	ft_write_pointer(void *p)
{
	if (!p)
		return (ft_putstr("(nil)"));
	ft_putstr("0x");
	return (ft_putulhexa((unsigned long int)p) + 2);
}
