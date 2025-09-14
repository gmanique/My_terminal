/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:08:01 by gmanique          #+#    #+#             */
/*   Updated: 2025/09/13 18:26:51 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_term.h"

char	**ft_strstrdup(char **strstr)
{
	int		i;
	char	**rep;

	i = 0;
	if (!strstr)
		return (NULL);
	rep = malloc((ft_strstrlen(strstr) + 1) * sizeof(char *));
	if (!rep)
		return (NULL);
	while (strstr[i])
	{
		rep[i] = ft_strdup(strstr[i]);
		if (!rep[i])
		{
			rep[i] = NULL;
			free_split(rep);
			return (NULL);
		}
		i++;
	}
	rep[i] = NULL;
	return (rep);
}

/* Initialise un t_cmd. */
t_cmd	*init_cmd(char **lex, int start, int size)
{
	t_cmd	*new;
	char	**cmd;
	int		i;

	if (!lex)
		return (NULL);
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	cmd = malloc(sizeof(char *) * (size + 1));
	if (!cmd)
		return (free(new), NULL);
	i = -1;
	while (++i < size)
	{
		cmd[i] = ft_strdup(lex[start + i]);
		if (!cmd[i])
			return (free_split(cmd), free(new), NULL);
	}
	cmd[i] = NULL;
	new->cmd = cmd;
	new->size = size;
	return (new);
}

int	load_terminal(t_minishell *minishell)
{
	int	ret;

	if (minishell && minishell->termios_p)
		ret = tcsetattr(0, TCSANOW, minishell->termios_p);
	else
		ret = -1;
	return (ret);
}

/* Initialise un arbre binaire. */
t_bintree	*init_tree(t_cmd *cmd, t_join join, t_type type)
{
	t_bintree	*new;

	new = malloc(sizeof(t_bintree));
	if (!new)
		return (NULL);
	new->join = join;
	new->type = type;
	new->cmd = cmd;
	new->fd_in = -1;
	new->fd_out = -1;
	new->l_branch = NULL;
	new->r_branch = NULL;
	return (new);
}

int	save_terminal(t_minishell *minishell)
{
	int	ret;

	ret = tcgetattr(0, minishell->termios_p);
	return (ret);
}


void	setup_minimal_env(t_minishell *minishell)
{
	minishell->env = malloc(5 * sizeof(char *));
	// if (!minishell->env)
	// 	error_quit(minishell, "Malloc failure.\n");
	minishell->env[0] = NULL;
	update_pwd(minishell, 0);
	minishell->env[1] = ft_strdup("SHLVL=1");
	// if (!minishell->env[1])
	// 	error_quit(minishell, "Malloc failure.\n");
	minishell->env[2] = ft_strdup("_=minishell");
	// if (!minishell->env[2])
	// 	error_quit(minishell, "Malloc failure.\n");
	minishell->env[3] = ft_strdup("OLDPWD");
	// if (!minishell->env[3])
	// 	error_quit(minishell, "Malloc failure.\n");
	minishell->env[4] = NULL;
}

void	init_env(t_minishell *minishell, char **envp)
{
	if (envp && envp[0])
		minishell->env = ft_strstrdup(envp);
	else
		setup_minimal_env(minishell);
	// if (!minishell->env)
	// 	error_quit(NULL, "Malloc failure.\n");
}

void	init_minishell(t_minishell *minishell, char **envp, int ac, int shell_fd)
{
	(void)ac;
	init_env(minishell, envp);
	minishell->heredocs = NULL;
	minishell->termios_p = NULL;
	minishell->input = NULL;
	minishell->parsed_input = NULL;
	minishell->status = 0;
	minishell->builtins = ft_split("pwd,env,cd,echo,exit,export,unset", ',');
	// if (!minishell->builtins)
	// 	error_quit(minishell, "Malloc failure.\n");
	minishell->save_stdin = dup(STDIN_FILENO);
	minishell->save_stdout = dup(shell_fd);
	minishell->gnl = 0;
	minishell->termios_p = malloc(sizeof(struct termios));
	// if (!minishell->termios_p)
	// 	error_quit(minishell, "Malloc failure\n");
	save_terminal(minishell);
}