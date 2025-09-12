/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:28:55 by gmanique          #+#    #+#             */
/*   Updated: 2025/06/24 00:39:07 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_line_len(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	return (i);
}

char	*read_till_nl(char *stock, int fd)
{
	int		nb_read;
	char	*buff;

	nb_read = 1;
	buff = NULL;
	while (!is_ft_strchr(stock, '\n') && nb_read != 0)
	{
		buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buff)
		{
			free(stock);
			stock = NULL;
			return (NULL);
		}
		buff[0] = '\0';
		nb_read = read(fd, buff, BUFFER_SIZE);
		if (nb_read < 0)
			return (free(buff), free(stock), buff = NULL, stock = NULL, NULL);
		buff[nb_read] = '\0';
		stock = stock_extend(stock, buff);
	}
	return (stock);
}

char	*get_precise_line(char *s)
{
	char	*rep;
	int		i;
	int		len;

	if (!is_ft_strchr(s, '\n'))
		return (s);
	len = get_line_len(s);
	i = 0;
	rep = malloc((len + 1) * sizeof(char));
	if (!rep)
	{
		free(s);
		s = NULL;
		return (NULL);
	}
	while (i < len)
	{
		rep[i] = s[i];
		i++;
	}
	rep[i] = '\0';
	return (rep);
}

char	*takeoff_line(char *s)
{
	int		i;
	int		len;
	char	*new_stock;

	if (!is_ft_strchr(s, '\n'))
		return (NULL);
	i = 0;
	len = 0;
	len = get_line_len(s);
	new_stock = malloc(((gnlft_strlen(s) - len) + 1) * sizeof(char));
	if (!new_stock)
	{
		free(s);
		s = NULL;
		return (NULL);
	}
	while (s[i + len])
	{
		new_stock[i] = s[i + len];
		i++;
	}
	new_stock[i] = '\0';
	free(s);
	s = NULL;
	return (new_stock);
}

char	*get_next_line(int fd)
{
	static char	*stock[1024];
	char		*rep;

	rep = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (free(stock[0]), NULL);
	if (!stock[fd])
	{
		stock[fd] = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!stock[fd])
			return (NULL);
		stock[fd][0] = '\0';
	}
	stock[fd] = read_till_nl(stock[fd], fd);
	if (!stock[fd] || stock[fd][0] == '\0')
		return (free(stock[fd]), stock[fd] = NULL, NULL);
	rep = get_precise_line(stock[fd]);
	if (!rep)
		return (NULL);
	stock[fd] = takeoff_line(stock[fd]);
	return (rep);
}

/*
#include <stdio.h>
int main()
{
	int fd = open("test.txt", O_RDONLY);
	// int fd= 42;
	char	*s = "a";
	while(s)
	{
		s = get_next_line(fd);
		printf("%s", s);
		free(s);
	}
	close(fd);
}*/