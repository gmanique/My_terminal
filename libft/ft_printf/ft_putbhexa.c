/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbhexa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:09:27 by gmanique          #+#    #+#             */
/*   Updated: 2024/11/19 12:21:47 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putbhexa(unsigned int nb)
{
	int		aff;
	char	c;
	int		rep;

	rep = 1;
	if (nb > 15)
		rep += ft_putbhexa(nb / 16);
	aff = nb % 16;
	if (aff < 10)
		c = aff + '0';
	else
		c = (aff % 10) + 'A';
	write(1, &c, 1);
	return (rep);
}
