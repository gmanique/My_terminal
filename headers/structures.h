/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 02:39:46 by gmanique          #+#    #+#             */
/*   Updated: 2025/09/13 22:24:30 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "my_term.h"

typedef struct s_keys
{
	int	shift;
}	t_keys;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_img
{
	void	*mlx_img;
	void	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	t_point	size;
}	t_img;



typedef struct s_mylist
{
	char			*input;
	char			*output;
	struct s_mylist	*next;
}	t_mylist;

typedef struct s_all
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_img			*screen;
	char			input[2048];
	char			output[2048];
	t_keys			keys;
	t_minishell		*shell;
	char			(*digits)[5][5];
	int				mouse_x;
	int				mouse_y;
	int				fd;
	t_mylist		*history;
	int				scroll;
}	t_all;


#endif