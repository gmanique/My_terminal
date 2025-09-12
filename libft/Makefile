# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amo <amo@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 12:53:13 by gmanique          #+#    #+#              #
#    Updated: 2025/06/22 17:41:51 by amo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -g3
NAME = libft.a
SRC = ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_lstnew_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstsize_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstmap_bonus.c \
	ft_printf/ft_printf.c \
	ft_printf/ft_put_unsigned_nbr.c \
	ft_printf/ft_putbhexa.c \
	ft_printf/ft_puthexa.c \
	ft_printf/ft_putnbr.c \
	ft_printf/ft_putstr.c \
	ft_printf/ft_write_pointer.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c	\
	ajouts_persos/abs.c	\
	ajouts_persos/ft_strstrlen.c	\
	ajouts_persos/print_bit.c	\
	ajouts_persos/ft_atod.c	\
	ajouts_persos/ft_strndup.c	\
	ajouts_persos/ft_putnbrendl_fd.c	\
	ajouts_persos/free_split.c	\
	ajouts_persos/ft_ismajalnum.c	\
	ajouts_persos/ft_iswhitespace.c	\
	ajouts_persos/ft_fprintf/ft_fprintf.c	\
	ajouts_persos/ft_fprintf/ft_get_pointer.c	\
	ajouts_persos/ft_fprintf/ft_uitoa.c			\
	ajouts_persos/ft_fprintf/ft_uitohex.c		\
	ajouts_persos/ft_strcmp.c


OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@ar -rsc libft.a $(OBJ)

clean : 
	@rm -rf $(OBJ)

fclean : clean
	@rm -f libft.a

re : fclean all