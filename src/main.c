/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 02:31:55 by gmanique          #+#    #+#             */
/*   Updated: 2025/09/12 10:39:24 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_term.h"

void	free_all(t_all *all)
{
	mlx_destroy_window(all->mlx_ptr, all->win_ptr);
	mlx_destroy_display(all->mlx_ptr);
	free(all->mlx_ptr);
	free(all);
}

static t_img	*init_img(t_all *all)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
	{
		perror("Malloc error");
		return (NULL);
	}
	img->addr = mlx_new_image(all->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	img->mlx_img = mlx_get_data_addr(img->addr, &img->bpp, &img->line_len,
			&img->endian);
	return (img);
}

int	init_mlx(t_all *all)
{
	if (!all)
		return (ERROR);
	all->mlx_ptr = mlx_init();
	if (all->mlx_ptr == NULL)
		return (ERROR);
	all->win_ptr = mlx_new_window(all->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
			"My Terminal");
	if (all->win_ptr == NULL)
		return (mlx_destroy_display(all->mlx_ptr), free(all->mlx_ptr), ERROR);
	all->screen = init_img(all);
	if (!all->screen)
		return (mlx_destroy_window(all->mlx_ptr, all->win_ptr),
			mlx_destroy_display(all->mlx_ptr), free(all->mlx_ptr), ERROR);
	return (0);
}

int	init_all(t_all **all)
{
	*all = malloc(sizeof(t_all));
	if (init_mlx(*all))
		return (free(*all), 1);
	(*all)->digits = calloc(129, sizeof(char[5][5]));
	if (!(*all)->digits)
		return (free_all((*all)), 1);
	init_chars((*all)->digits);
	ft_bzero((*all)->input, 2048);
	return (0);
}

int	cpt_nl(char *input)
{
	int	i;
	int	cpt;

	cpt = 0;
	i = 0;
	while(input[i])
	{
		if (input[i] == '\n')
			cpt++;
		i++;
	}
	return (cpt);
}

int	update_screen(t_all *all)
{
	struct timeval time;
	
	gettimeofday(&time, NULL);
	ft_bzero(all->screen->mlx_img, WINDOW_HEIGHT * all->screen->line_len);
	ft_put_mlx_str(all, "$>", make_point(10, 10), 3);
	ft_put_mlx_str(all, all->input, make_point(50, 10), 3);
	if ((time.tv_sec & 1) == 1 && ft_strchr(all->input, '\n'))
		ft_put_mlx_str(all, "_", make_point(50 + ft_strlen(ft_strrchr(all->input, '\n'))*16.1 - 40, 12 + 20*(cpt_nl(all->input))), 3);
	else if ((time.tv_sec & 1) == 1)
		ft_put_mlx_str(all, "_", make_point(50 + ft_strlen(all->input)*16.1, 12), 3);
	mlx_put_image_to_window(all->mlx_ptr, all->win_ptr, all->screen->addr, 0, 0);
	return (0);
}

int	close_window(t_all *all)
{
	mlx_destroy_image(all->mlx_ptr, all->screen->addr);
	mlx_destroy_window(all->mlx_ptr, all->win_ptr);
	mlx_destroy_display(all->mlx_ptr);
	free(all->mlx_ptr);
	// free_all(all);
	exit(0);
}

int	handle_shift(char c)
{
	c = ft_toupper(c);
	switch (c){
		case '1' : return ('!');
		case '2' : return ('@');
		case '3' : return ('#');
		case '4' : return ('$');
		case '5' : return ('%');
		case '6' : return ('^');
		case '7' : return ('&');
		case '8' : return ('*');
		case '9' : return ('(');
		case '0' : return (')');
		case '\\' : return ('|');
		case '[' : return ('{');
		case ']' : return ('}');
		case '-' : return ('_');
		case '=' : return ('+');
		case '\'' : return ('"');
		case ';' : return (':');
		case '/' : return ('?');
		case ',' : return ('<');
		case '.' : return ('>');
		case '`' : return ('~');
	}
	return (c);
}

int		handle_press(int keysym, t_all *all)
{
	printf("%d\nlen : %d\n", keysym, ft_strlen(all->input));
	if (keysym < 128 && ft_strlen(all->input) < 2046)
	{
		if (all->keys.shift)
			keysym = handle_shift(keysym);
		ft_strlcat(all->input, (const char *)&keysym, ft_strlen(all->input)+2);
	}
	if (keysym == XK_BackSpace)
		all->input[ft_strlen(all->input)-1] = '\0';
	if (keysym == XK_Escape)
		close_window(all);
	if (keysym == XK_Shift_L)
		all->keys.shift = 1;
	if (keysym == XK_Return)
	{
		if (all->keys.shift && ft_strlen(all->input) < 2046)
			ft_strlcat(all->input, "\n", ft_strlen(all->input)+2);
		// else if (!all->keys.shift)
		// {
		// 	all->shell->input = ft_strdup(all->input);
		// 	ft_bzero(all->input, 2048);
		// }
	}
	return (0);
}

int	handle_release(int keysym, t_all *all)
{
	if (keysym == XK_Shift_L)
		all->keys.shift = 0;
	return (0);
}

void	do_the_loop(t_all *all)
{
	mlx_loop_hook(all->mlx_ptr, &update_screen, all);
	mlx_hook(all->win_ptr, KeyRelease, KeyReleaseMask, &handle_release, all);
	mlx_hook(all->win_ptr, KeyPress, KeyPressMask, &handle_press, all);
	mlx_hook(all->win_ptr, DestroyNotify, KeyPressMask, &close_window, all);
	// mlx_hook(all->win_ptr, MotionNotify, PointerMotionMask, &mouse_move, all);
	// mlx_hook(all->win_ptr, ButtonPress, ButtonPressMask, &handle_mousepress, all);
	// mlx_hook(all->win_ptr, ButtonRelease, ButtonReleaseMask, &handle_mouserelease, all);
	mlx_loop(all->mlx_ptr);
}

int	main()
{
	t_all *all;

	all = NULL;

	if (init_all(&all) == 1)
		return (1);

	do_the_loop(all);
	return (0);
}