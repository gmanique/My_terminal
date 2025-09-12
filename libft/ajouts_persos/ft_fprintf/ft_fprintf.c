/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 03:49:28 by gmanique          #+#    #+#             */
/*   Updated: 2025/06/20 23:05:45 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

char	*get_char(int c)
{
	char	*rep;

	rep = ft_calloc(2, sizeof(char));
	if (!rep)
		return (NULL);
	rep[0] = c;
	rep[1] = '\0';
	return (rep);
}

char	*free_join(char *s1, char *s2, int free_type)
{
	char	*rep;

	rep = ft_strjoin(s1, s2);
	if ((free_type & 1) && s1)
	{
		free(s1);
		s1 = NULL;
	}
	if ((free_type & 2) && s2)
	{
		free(s2);
		s2 = NULL;
	}
	return (rep);
}

char	*get_param(char c, va_list ap)
{
	if (c == '%')
		return (ft_strdup("%"));
	else if (c == 'c')
		return (get_char(va_arg(ap, int)));
	else if (c == 's')
		return (ft_strdup(va_arg(ap, char *)));
	else if (c == 'd' || c == 'i')
		return (ft_itoa(va_arg(ap, int)));
	else if (c == 'u')
		return (ft_uitoa(va_arg(ap, unsigned int)));
	else if (c == 'x' || c == 'X')
		return (ft_uitohex(va_arg(ap, unsigned int), c));
	else if (c == 'p')
		return (ft_get_pointer(va_arg(ap, void *)));
	write(2,
		"Unrecognized parameter on ft_fprintf. Expected undefined behaviours.\n",
		70);
	return (NULL);
}

int	ft_fprintf(int fd, char *str, ...)
{
	int		i;
	va_list	ap;
	char	*rep;

	i = 0;
	rep = ft_calloc(1, sizeof(char));
	if (!rep)
		return (-1);
	va_start(ap, str);
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] != '%')
			rep = free_join(rep, get_char(str[i++]), 3);
		else
			rep = free_join(rep,
					get_param(str[(i += ((str[i + 1] != 0) + 1)) - 1],
						ap), 3);
	}
	va_end(ap);
	i = ft_strlen(rep);
	write(fd, rep, i);
	return (free(rep), i);
}
