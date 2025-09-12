/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 04:35:49 by gmanique          #+#    #+#             */
/*   Updated: 2025/03/27 04:54:35 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ajouts.h"

int	ft_strstrlen(char **strstr)
{
	int	i;

	i = 0;
	if (!strstr)
		return (0);
	while (strstr[i])
		i++;
	return (i);
}
