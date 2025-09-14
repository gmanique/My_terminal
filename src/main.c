/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 02:31:55 by gmanique          #+#    #+#             */
/*   Updated: 2025/09/13 23:46:38 by gmanique         ###   ########.fr       */
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

int	init_all(t_all **all, int ac, char **envp)
{
	int	shell_fd[2];
	*all = malloc(sizeof(t_all));
	if (init_mlx(*all))
		return (free(*all), 1);
	(*all)->digits = calloc(129, sizeof(char[5][5]));
	if (!(*all)->digits)
		return (free_all((*all)), 1);
	init_chars((*all)->digits);
	ft_bzero((*all)->input, 2048);
	
	(*all)->keys.shift = 0;
	(*all)->mouse_x = 0;
	(*all)->mouse_y = 0;
	(*all)->history = NULL;
	(*all)->shell = malloc(sizeof(t_minishell));
	if (pipe(shell_fd) == -1)
		return (free_all((*all)), 1);
	init_minishell((*all)->shell, envp, ac, shell_fd[1]);
	(*all)->scroll = 0;
	(*all)->fd = shell_fd[0];
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

void	print_full_history(t_all *all)
{
	t_mylist	*tmp = all->history;

	while(tmp)
	{
		ft_put_mlx_str(all, "$>", make_point(10, 12 * (cpt_lines(tmp->next)) - all->scroll), 2);
		// ft_put_mlx_str(all, all->output, make_point(50, cpt_lines(tmp)), 5);
		ft_put_mlx_str(all, tmp->input, make_point(50, 12 * (cpt_lines(tmp->next)) - all->scroll), 2);
		ft_put_mlx_str(all, tmp->output, make_point(15, 12 * (cpt_lines(tmp->next) + nb_lines(tmp->input)) - all->scroll + 5), 2);
		
		tmp = tmp->next;
	}
}

int	update_screen(t_all *all)
{
	struct timeval time;
	
	gettimeofday(&time, NULL);
	ft_bzero(all->screen->mlx_img, WINDOW_HEIGHT * all->screen->line_len);
	print_full_history(all);
	ft_put_mlx_str(all, "$>", make_point(10, 12 * (cpt_lines(all->history)) - all->scroll), 2);
	ft_put_mlx_str(all, all->input, make_point(50, 12 * (cpt_lines(all->history)) - all->scroll), 2);
	if ((time.tv_sec & 1) == 1)
		ft_put_mlx_str(all, "_", make_point(51 + ft_strlen(all->input)*11, 12 * cpt_lines(all->history) - all->scroll), 2);
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

void	clear_all(t_all *all)
{
	all->history = NULL;
	all->scroll = 0;
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
		// if (all->keys.shift && ft_strlen(all->input) < 2046)
		// 	ft_strlcat(all->input, "\n", ft_strlen(all->input)+2);
		// else if (!all->keys.shift)
		// {
			if (!ft_strncmp("exit", all->input, 6))
				exit(0);
			all->shell->input = ft_strdup(all->input);
			all->history = add_front(all->history, ft_strdup(all->input), "");
			ft_bzero(all->input, 2048);
			if (!ft_strncmp("clear", all->shell->input, 6))
				clear_all(all);
			else
			{
				pid_t pid = fork();
				if (pid == 0)
				{
					do_shell(all->shell);
					close(all->fd);
					exit(0);
				}
				else
				{
					waitpid(pid, NULL, 0);
					ssize_t n = read(all->fd, all->output, sizeof(all->output) - 1);
					if (n > 0)
						all->output[n] = '\0';
					all->history->output = ft_strdup(all->output);
					// ft_put_mlx_str(all, all->output, make_point(100, 100), 5);
				}
			}
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

int	handle_scroll(int button, int x, int y, t_all *all)
{
	(void)x;
	(void)y;
	if (button == 5)
		all->scroll +=10;
	if (button == 4)
		all->scroll -=10;
	if (all->scroll < 0)
		all->scroll = 0;
	if (all->scroll > cpt_lines(all->history)*12 - 10)
		all->scroll = cpt_lines(all->history)*12 - 10;
	return (0);
}


void	do_the_loop(t_all *all)
{
	mlx_loop_hook(all->mlx_ptr, &update_screen, all);
	mlx_hook(all->win_ptr, KeyRelease, KeyReleaseMask, &handle_release, all);
	mlx_hook(all->win_ptr, KeyPress, KeyPressMask, &handle_press, all);
	mlx_hook(all->win_ptr, DestroyNotify, KeyPressMask, &close_window, all);
	
	mlx_hook(all->win_ptr, ButtonPress, ButtonPressMask, &handle_scroll, all);
	// mlx_hook(all->win_ptr, MotionNotify, PointerMotionMask, &mouse_move, all);
	// mlx_hook(all->win_ptr, ButtonPress, ButtonPressMask, &handle_mousepress, all);
	// mlx_hook(all->win_ptr, ButtonRelease, ButtonReleaseMask, &handle_mouserelease, all);
	mlx_loop(all->mlx_ptr);
}

int	main(int ac, char **av, char **envp)
{
	t_all *all;

	all = NULL;
	(void)av;
	if (init_all(&all, ac, envp) == 1)
		return (1);

	do_the_loop(all);
	return (0);
}