/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ajouts.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amo <amo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 02:04:19 by gmanique          #+#    #+#             */
/*   Updated: 2025/06/22 17:41:15 by amo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AJOUTS_H
# define AJOUTS_H

# include "../libft.h"
# include "ft_fprintf/ft_fprintf.h"

/* Utils */
# define CLEAR "\033c"
# define RESET_COLOR "\e[m"
# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define ERROR 1

/* Colors */
# define BLACK "\033[0;30m"
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define CYAN "\033[0;36m"
# define PURPLE "\033[0;35m"
# define WHITE "\033[0;37m"

/* Bold Colors */
# define BOLD_BLACK "\033[1;30m"
# define BOLD_GREEN "\033[1;32m"
# define BOLD_RED "\033[1;31m"
# define BOLD_YELLOW "\033[1;33m"
# define BOLD_BLUE "\033[1;34m"
# define BOLD_CYAN "\033[1;36m"
# define BOLD_PURPLE "\033[1;35m"
# define BOLD_WHITE "\033[1;37m"

/* Underline */
# define U_BLACK "\033[4;30m"
# define U_RED "\033[4;31m"
# define U_GREEN "\033[4;32m"
# define U_YELLOW "\033[4;33m"
# define U_BLUE "\033[4;34m"
# define U_PURPLE "\033[4;35m"
# define U_CYAN "\033[4;36m"
# define U_WHITE "\033[4;37m"

/* Background */
# define ON_BLACK "\033[40m"
# define ON_RED "\033[41m"
# define ON_GREEN "\033[42m"
# define ON_YELLOW "\033[43m"
# define ON_BLUE "\033[44m"
# define ON_PURPLE "\033[45m"
# define ON_CYAN "\033[46m"
# define ON_WHITE "\033[47m"

/* High Intensty */
# define I_BLACK "\033[0;90m"
# define I_RED "\033[0;91m"
# define I_GREEN "\033[0;92m"
# define I_YELLOW "\033[0;93m"
# define I_BLUE "\033[0;94m"
# define I_PURPLE "\033[0;95m"
# define I_CYAN "\033[0;96m"
# define I_WHITE "\033[0;97m"

/* Bold High Intensty */
# define BI_BLACK "\033[1;90m"
# define BI_RED "\033[1;91m"
# define BI_GREEN "\033[1;92m"
# define BI_YELLOW "\033[1;93m"
# define BI_BLUE "\033[1;94m"
# define BI_PURPLE "\033[1;95m"
# define BI_CYAN "\033[1;96m"
# define BI_WHITE "\033[1;97m"

/* High Intensty backgrounds */
# define ON_I_BLACK "\033[0;100m"
# define ON_I_RED "\033[0;101m"
# define ON_I_GREEN "\033[0;102m"
# define ON_I_YELLOW "\033[0;103m"
# define ON_I_BLUE "\033[0;104m"
# define ON_I_PURPLE "\033[10;95m"
# define ON_I_CYAN "\033[0;106m"
# define ON_I_WHITE "\033[0;107m"

/* Renvoie la valeur absolue de l'entier passe en parametre. */
long long int	ft_abs(long long int val);

/* Renvoie la valeur absolue du double passe en parametre. */
double			db_abs(double val);

/* Ecrit en binaire la valeur de l'entier passe en parametre. */
void			print_bits(unsigned long long int val);

/* Convertit une chaine de caractere en double. */
double			ft_atod(const char *str);

/* Free une chaine de chaines de caracteres */
void			free_split(char **split);

/* Renvoie 1 si le charactere */
/* est un whitespace, */
/* 0 sinon.*/
int				ft_iswhitespace(int c);

/* Un putnbr_fd mais avec un \n */
void			ft_putnbrendl_fd(int nb, int fd);

/* Renvoie le nombre de chaines de caracteres dans une */
/* chaine de chaines de caractere. */
int				ft_strstrlen(char **strstr);

/* Renvoie 1 si le caractere est une lettre majuscule ou un nombre */
/* Zero sinon. */
int				ft_ismajalnum(char c);

/* Comme ft_strdup mais sur un nb limite de caracteres */
char			*ft_strndup(char *dup, int n);

int				ft_strcmp(const char *s1, const char *s2);

#endif