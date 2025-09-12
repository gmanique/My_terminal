/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_it.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 23:02:55 by gmanique          #+#    #+#             */
/*   Updated: 2025/09/12 10:36:02 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_term.h"

void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->mlx_img + y * img->line_len + x * (img->bpp / 8);
	*(int *)pixel = color;
}

static void	put_white_pixel(t_all *all, t_point coords, t_point i_and_j, int size)
{
	int	cptx;
	int	cpty;
	cptx = 0;
	while(cptx < size)
	{
		cpty = 0;
		while(cpty < size)
		{
			if (coords.x + (i_and_j.x * size) + cptx >= WINDOW_WIDTH || coords.y + (i_and_j.y * size) + cpty >= WINDOW_HEIGHT)
				return ;
			draw_pixel(all->screen, coords.x + (i_and_j.x * size) + cptx, coords.y + (i_and_j.y * size) + cpty,
									0xffffff);
			cpty++;
		}
		cptx++;
	}
}

static void	write_char(t_all *all, char	digit[5][5], t_point pos, int size)
{
	int		i;
	int		j;

	i = 0;
	while(i < 5)
	{
		j = 0;
		while(j < 5)
		{
			if (digit[i][j] == '1')
				put_white_pixel(all, pos, make_point(j, i), size);
			j++;
		}
		i++;
	}
}

void	ft_put_mlx_str(t_all *all, char *s, t_point coords, int size)
{
	int	i;
	int	save_x;
	int	decal;

	decal = 0;
	save_x = coords.x;
	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		if (s[i] == '\n')
		{
			coords.y += size * 7;
			coords.x = save_x;
			decal = i;
		}
		else
		{
			// if (s[i] >= 'a' && s[i] <= 'z')
			// 	write_char(all, all->digits[(int)s[i]], make_point(coords.x + (size * i) + size + 2, coords.y + 5*(float)(size/2)), size*0.9);
			// else
			if (decal)
				write_char(all, all->digits[(int)s[i]], make_point(coords.x + (size * (i - decal)) + size - 40, coords.y), size);
			else
				write_char(all, all->digits[(int)s[i]], make_point(coords.x + (size * i) + size, coords.y), size);
			coords.x += 4.5*size;
		}
		i++;
	}
}
