/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 02:39:46 by gmanique          #+#    #+#             */
/*   Updated: 2025/09/12 09:58:11 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

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

typedef enum e_join
{
	none,
	pipex,
	and,
	or,
	l_redirect,
	r_redirect,
	l_redirect2,
	r_redirect2
}	t_join;

typedef enum e_type
{
	type_cmd,
	type_join,
	no_type
}	t_type;

typedef struct s_cmd
{
	char	**cmd;
	int		size;
	int		heredoc;
}	t_cmd;

typedef struct s_bintree
{
	struct s_bintree	*l_branch;
	struct s_bintree	*r_branch;
	t_cmd				*cmd;
	t_join				join;
	t_type				type;
	int					parse_pos;
	int					fd_in;
	int					fd_out;
}	t_bintree;

typedef struct s_minishell
{
	int				status;
	char			*input;
	t_bintree		*parsed_input;
	char			**env;
	char			**builtins;
	int				save_stdin;
	int				save_stdout;
	int				gnl;
	struct termios	*termios_p;
	char			**heredocs;
	int				inc;
}	t_minishell;

typedef struct s_all
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_img			*screen;
	char			input[2048];
	t_keys			keys;
	t_minishell		*shell;
	char			(*digits)[5][5];
	int				mouse_x;
	int				mouse_y;
}	t_all;


#endif