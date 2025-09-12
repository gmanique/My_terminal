/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:29:29 by gmanique          #+#    #+#             */
/*   Updated: 2025/06/23 23:43:23 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnlft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	is_ft_strchr(char *s, int c)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while(i < gnlft_strlen(s))
	{
		if (s[i] == (unsigned char)c)
			return (1);
		i++;
	}
	return (0);
}

char	*gnlft_strjoin(char const *s1, char const *s2)
{
	char	*rep;
	int		i;
	int		j;

	rep = malloc((gnlft_strlen(s1) + gnlft_strlen(s2) + 1) * sizeof(char));
	if (!rep)
		return (NULL);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			rep[i] = s1[i];
			i++;
		}
	}
	j = 0;
	while (s2[j])
	{
		rep[i + j] = s2[j];
		j++;
	}
	rep[i + j] = '\0';
	return (rep);
}

char	*stock_extend(char *stock, char *buff)
{
	char	*temp;

	temp = gnlft_strjoin(stock, buff);
	free(stock);
	stock = NULL;
	free(buff);
	buff = NULL;
	return (temp);
}
