/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:00:36 by gmanique          #+#    #+#             */
/*   Updated: 2025/04/29 03:57:06 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		aff;
	char	c;
	char	tiret;

	if (fd < 0)
		return ;
	if (n > 9 || n < -9)
		ft_putnbr_fd(n / 10, fd);
	if (n >= 0)
	{
		aff = n % 10;
		c = aff + '0';
		write(fd, &c, 1);
	}
	else
	{
		if (n > -10)
		{
			tiret = '-';
			write(fd, &tiret, 1);
		}
		aff = (n % 10) * (-1);
		c = aff + '0';
		write(fd, &c, 1);
	}
}
