/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_term.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 02:32:50 by gmanique          #+#    #+#             */
/*   Updated: 2025/09/13 21:25:13 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_TERM_H
# define MY_TERM_H

# include <float.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <curses.h>
# include <term.h> 
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>

# include "../minilibx-linux/mlx.h"
# include "shell.h"
# include "structures.h"
# include "fonctions.h"
# include "libft.h"

# define WINDOW_WIDTH 1600
# define WINDOW_HEIGHT 900
# define NOT_FOUND -404
# define EXPORT_SIZE 5000

#endif