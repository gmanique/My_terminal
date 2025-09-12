/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 03:49:44 by gmanique          #+#    #+#             */
/*   Updated: 2025/06/04 05:49:57 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include "../../libft.h"

/* 
	Permet de strjoin en freeant en meme temps 
	free_type = 0: free rien
	free_type = 1: free s1
	free_type = 2: free s2
	free_type = 3: free s1 et s2
*/
char	*free_join(char *s1, char *s2, int free_type);
char	*get_char(int c);

/* ft_itoa pour undigned int */
char	*ft_uitoa(unsigned int nb);

/* ft_uitoa mais en hexadecimal */
char	*ft_uitohex(unsigned int nb, char c);
char	*ft_get_pointer(void *p);
int		ft_fprintf(int fd, char *str, ...);

#endif