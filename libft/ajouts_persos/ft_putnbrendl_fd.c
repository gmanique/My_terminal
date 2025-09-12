/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrendl_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:20:28 by gmanique          #+#    #+#             */
/*   Updated: 2025/03/13 10:22:27 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ajouts.h"

void	ft_putnbrendl_fd(int nb, int fd)
{
	ft_putnbr_fd(nb, fd);
	ft_putchar_fd('\n', fd);
}
