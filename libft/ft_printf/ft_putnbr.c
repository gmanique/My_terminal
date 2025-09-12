/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:06:17 by gmanique          #+#    #+#             */
/*   Updated: 2024/11/19 16:15:07 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	aff_negat(int nb)
{
	int		aff;
	char	tiret;
	char	c;
	int		rep;

	rep = 0;
	if (nb > -10)
	{
		tiret = '-';
		write(1, &tiret, 1);
		rep = 1;
	}
	aff = (nb % 10) * (-1);
	c = aff + '0';
	write(1, &c, 1);
	return (rep);
}

int	ft_putnbr(int nb)
{
	int		aff;
	char	c;
	int		rep;

	rep = 1;
	if (nb > 9 || nb < -9)
		rep += ft_putnbr(nb / 10);
	if (nb >= 0)
	{
		aff = nb % 10;
		c = aff + '0';
		write(1, &c, 1);
	}
	else
		rep += aff_negat(nb);
	return (rep);
}
