/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 02:08:25 by gmanique          #+#    #+#             */
/*   Updated: 2025/03/11 02:09:29 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	print_bits(unsigned long long int val)
{
	int	size;
	int	i;

	size = sizeof(unsigned long long int);
	i = size * 8 - 1;
	while (i > 0 && !((val >> i) & 1))
		i--;
	while (i >= 0)
	{
		if ((val >> i) & 1)
			write(1, "1", 1);
		else
			write(1, "0", 1);
		i--;
	}
}
