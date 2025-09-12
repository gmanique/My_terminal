/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:29:43 by gmanique          #+#    #+#             */
/*   Updated: 2025/06/09 16:14:00 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

int		gnlft_strlen(const char *s);
int		is_ft_strchr(char *s, int c);
char	*gnlft_strjoin(char const *s1, char const *s2);
char	*stock_extend(char *stock, char *buff);
int		get_line_len(char *s);
char	*read_till_nl(char *stock, int fd);
char	*get_precise_line(char *s);
char	*takeoff_line(char *s);
/* Renvoie le contenu du fd, ligne par ligne */
/* (Un appel a la fonction = une ligne du fd) */
char	*get_next_line(int fd);

#endif