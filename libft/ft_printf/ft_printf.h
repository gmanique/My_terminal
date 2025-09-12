/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 23:04:54 by gmanique          #+#    #+#             */
/*   Updated: 2025/03/12 19:41:39 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int		ft_put_unsigned_nbr(unsigned int nb);
int		ft_putbhexa(unsigned int nb);
int		ft_puthexa(unsigned int nb);
int		ft_write_pointer(void *p);
int		write_param(char c, va_list ap);
int		ft_putstr(char *str);
/* Reproduction de la fonction d'affichage */
/* formatte printf(). */
int		ft_printf(const char *str, ...);
int		ft_putnbr(int nb);
void	ft_putchar(int c);
int		ft_printf(const char *str, ...);

#endif