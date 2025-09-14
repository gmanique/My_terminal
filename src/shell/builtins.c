/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:12:50 by gmanique          #+#    #+#             */
/*   Updated: 2025/09/13 19:07:02 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_term.h"

void	handle_builtins(t_minishell *minishell, t_bintree *cmd, int i)
{
	do_dup(minishell, cmd->fd_in, cmd->fd_out);
	if (!ft_strncmp("cd", cmd->cmd->cmd[i], 3))
		change_dir(minishell, cmd->cmd->cmd[i + 1]);
	else if (!ft_strncmp("echo", cmd->cmd->cmd[i], 5))
		do_echo(minishell, cmd->cmd, i);
	else if (!ft_strncmp("env", cmd->cmd->cmd[i], 4))
		print_env(minishell);
	else if (!ft_strncmp("exit", cmd->cmd->cmd[i], 5))
		do_exit(minishell, cmd->cmd, i);
	else if (!ft_strncmp("export", cmd->cmd->cmd[i], 7))
		do_export(minishell, cmd->cmd, i);
	else if (!ft_strncmp("pwd", cmd->cmd->cmd[i], 4))
		print_pwd(minishell);
	else if (!ft_strncmp("unset", cmd->cmd->cmd[i], 6))
		do_unset(minishell, cmd->cmd, i);
	restore_dup(minishell);
}


void	update_pwd(t_minishell *minishell, int pwd)
{
	char	*buf;
	char	*env_var;

	buf = getcwd(NULL, 0);
	if (buf)
	{
		env_var = ft_strjoin("PWD=", buf);
		if (!env_var)
			error_quit(minishell, "Malloc failure.\n");
		else
		{
			if (minishell->env && minishell->env[pwd])
				free(minishell->env[pwd]);
			minishell->env[pwd] = NULL;
			minishell->env[pwd] = env_var;
		}
	}
	free(buf);
	buf = NULL;
}

static void	update_oldpwd(t_minishell *minishell, int old, char *buf)
{
	char	*env_var;

	env_var = ft_strjoin("OLDPWD=", buf);
	if (!env_var)
		error_quit(minishell, "Malloc failure.\n");
	free(minishell->env[old]);
	minishell->env[old] = NULL;
	minishell->env[old] = env_var;
}

static char	*get_home(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (!ft_strncmp(envp[i], "HOME=", 5))
			return (&(envp[i][5]));
		i++;
	}
	return (NULL);
}

void	do_exit(t_minishell *minishell, t_cmd *cmd, int i)
{
	int	exit_val;

	exit_val = minishell->status;
	if (isatty(STDIN_FILENO) || cmd->cmd[1])
		ft_fprintf(1, "exit\n");
	if (!cmd->cmd[i + 1])
	{
		minishell = NULL;
		exit(exit_val);
	}
	if (ft_isnumber(cmd->cmd[i + 1]))
	{
		if (cmd->cmd[i + 2])
			return (error_msg_set_status(minishell,
					"Minishell: exit: too many arguments\n", 1));
		exit_val = ft_atoi(cmd->cmd[i + 1]);
		minishell = NULL;
		exit(exit_val);
	}
	ft_fprintf(2, "Minishell: exit: %s: numeric argument required\n", cmd->cmd[i
		+ 1]);
	exit(2);
}


int	already_exists(char *varname, t_minishell *minishell)
{
	char	*dup;
	int		rep;

	dup = ft_strjoin(varname, "=");
	if (!dup)
		return (0);
	rep = get_var_index(minishell->env, dup);
	free(dup);
	dup = NULL;
	return (rep);
}

/* Un equivalent de strcmp mais qui considere */
/* '_' inferieur a l'alphabet pour export */
static int	custom_cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] == s2[i])
		i++;
	if (s1[i] == '_')
		return (1);
	if (s2[i] == '_')
		return (-1);
	return (s1[i] - s2[i]);
}

/* Checke si la chaine de str est triee dans l'ordre alphabetique */
static int	is_sorted_strs(char **strs)
{
	int	i;

	i = 0;
	if (!strs || !strs[0] || !strs[1])
		return (1);
	while (strs[i + 1])
	{
		if (custom_cmp(strs[i], strs[i + 1]) > 0)
			return (0);
		i++;
	}
	return (1);
}

/* Recupere une version triee de env pour la print */
static char	**get_sorted_env(char **envp)
{
	char	**env_cpy;
	int		i;

	env_cpy = ft_strstrdup(envp);
	if (!env_cpy)
		return (NULL);
	while (!is_sorted_strs(env_cpy))
	{
		i = 0;
		while (env_cpy[i + 1])
		{
			if (custom_cmp(env_cpy[i], env_cpy[i + 1]) > 0)
				swap_str(&env_cpy[i], &env_cpy[i + 1]);
			i++;
		}
	}
	return (env_cpy);
}

static int	write_env_elem(char *env_elem)
{
	int	i;

	i = 0;
	while (env_elem[i] && env_elem[i] != '=')
	{
		if (write(1, &env_elem[i], 1) == -1)
			return (0);
		i++;
	}
	if (!env_elem[i])
		return (1);
	if (write(1, &env_elem[i], 1) == -1)
		return (0);
	i++;
	if (write(1, "\"", 1) == -1)
		return (0);
	while (env_elem[i])
	{
		if (write(1, &env_elem[i], 1) == -1)
			return (0);
		i++;
	}
	if (write(1, "\"", 1) == -1)
		return (0);
	return (1);
}

/* Permet de print l'environnement dans l'ordre alphabetique */
/* quand y'a pas d'arguments a export */
void	print_alphabetical_env(t_minishell *minishell)
{
	char	**sorted_env;
	int		i;

	sorted_env = get_sorted_env(minishell->env);
	if (!sorted_env)
		error_quit(minishell, "Malloc failure while getting sorted envp.\n");
	i = -1;
	while (sorted_env[++i])
	{
		if (ft_strncmp(sorted_env[i], "_=", 2) == 0)
			continue ;
		if (!safe_putstr("export ") || !write_env_elem(sorted_env[i])
			|| !safe_putstr("\n"))
		{
			minishell->status = 1;
			free_split(sorted_env);
			sorted_env = NULL;
			return ;
		}
	}
	minishell->status = 0;
	free_split(sorted_env);
	sorted_env = NULL;
}


/* Permet de modifier une variable dans envp */
void	change_var(t_minishell *minishell, char *var, char *varname)
{
	int		i;
	char	*tmp;

	i = already_exists(varname, minishell);
	tmp = ft_strdup(var);
	if (!tmp)
	{
		free(varname);
		varname = NULL;
		error_quit(minishell,
			"Malloc failure while changing variable in export.\n");
	}
	free(minishell->env[i]);
	minishell->env[i] = NULL;
	minishell->env[i] = tmp;
}


static void	cd_helper(t_minishell *minishell, char *where, char *buf)
{
	int	i;
	int	j;

	i = get_var_index(minishell->env, "OLDPWD");
	j = get_var_index(minishell->env, "PWD=");
	if (chdir(where) != -1)
	{
		if (i != NOT_FOUND && buf)
			update_oldpwd(minishell, i, buf);
		if (j != NOT_FOUND)
			update_pwd(minishell, j);
		minishell->status = 0;
	}
	else
	{
		ft_fprintf(2, "Minishell: cd: %s: No such file or directory\n", where);
		minishell->status = 1;
	}
}

/*	Builtin:
	permet de changer de dossier	*/
void	change_dir(t_minishell *minishell, char *where)
{
	char	*buf;

	if (!where)
		where = get_home(minishell->env);
	if (!where)
	{
		ft_fprintf(2, "Minishell : cd : HOME not set\n");
		return ;
	}
	if (!where[0])
	{
		minishell->status = 0;
		return ;
	}
	buf = getcwd(NULL, 0);
	cd_helper(minishell, where, buf);
	free(buf);
	buf = NULL;
}


/* Permet de savoir si la chaine de caractere */
/* analysee correspond a un flag '-n', -nnnnn' */
static int	is_echo_flag(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-')
		i++;
	else
		return (0);
	while (str[i] == 'n')
		i++;
	if (str[i])
		return (0);
	return (1);
}

/*	Builtin:
	Permet d'afficher le contenu d'un echo,
	avec gestion des flags '-n'	*/
void	do_echo(t_minishell *minishell, t_cmd *cmd, int j)
{
	int	is_flag;
	int	i;

	is_flag = 0;
	if (!cmd || !cmd->cmd || !cmd->cmd[j])
		return ;
	i = 0;
	while (is_echo_flag(cmd->cmd[++i + j]))
		is_flag = 1;
	while (cmd->cmd[i + j])
	{
		if (!safe_putstr(cmd->cmd[i + j]))
		{
			minishell->status = 1;
			return ;
		}
		if (cmd->cmd[++i + j] && !safe_putstr(" "))
		{
			minishell->status = 1;
			return ;
		}
	}
	minishell->status = (!is_flag && !safe_putstr("\n"));
}


/*	Builtin:
	affiche l'environnement	*/
void	print_env(t_minishell *minishell)
{
	int		i;
	char	*str;

	i = -1;
	while (minishell->env && minishell->env[++i])
	{
		if (!ft_strchr(minishell->env[i], '='))
			continue ;
		if (ft_strncmp(minishell->env[i], "_=", 2) == 0)
			str = "_=/usr/bin/env";
		else
			str = minishell->env[i];
		if (!safe_putstr(str) || !safe_putstr("\n"))
		{
			minishell->status = 1;
			ft_fprintf(2, "Minishell: Permission denied.\n");
			return ;
		}
	}
	minishell->status = 0;
}



/* J'ai essaye de la faire en utilisant qu'un malloc,
	en esperant que ca nique pas tout */
/* Ca permet d'ajouter une variable a envp */
static void	add_var(t_minishell *minishell, char *var)
{
	int		i;
	char	**new_env;

	new_env = malloc((ft_strstrlen(minishell->env) + 2) * sizeof(char *));
	if (!new_env)
		error_quit(minishell,
			"Malloc failure while adding the variable in export.\n");
	i = 0;
	while (minishell->env[i])
	{
		new_env[i] = minishell->env[i];
		i++;
	}
	new_env[i] = ft_strdup(var);
	if (!new_env[i])
		error_quit(minishell, "Malloc failure.\n");
	new_env[i + 1] = NULL;
	if (minishell->env)
		free(minishell->env);
	minishell->env = NULL;
	minishell->env = new_env;
	if (!minishell->env[i])
		error_quit(minishell,
			"Malloc failure while adding the variable in export.\n");
}

static int	is_correct_format(char *varname)
{
	int	i;

	i = 0;
	if (!varname[0] || ft_isdigit(varname[0]))
		return (0);
	while (varname[i])
	{
		if (!ft_isalnum(varname[i]) && varname[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/* recupere tout ce qui est avant le '=' avec le '=' si il y en a un */
static char	*get_varname_export(char *arg)
{
	int		i;
	char	*rep;

	i = 0;
	if (!arg)
		return (NULL);
	while (arg[i] && arg[i] != '=')
		i++;
	rep = ft_calloc(i + 1 + (arg[i] == '='), sizeof(char));
	if (!rep)
		return (NULL);
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		rep[i] = arg[i];
		i++;
	}
	rep[i] = '\0';
	return (rep);
}

static int	do_export_loop(t_minishell *minishell, t_cmd *cmd, int i)
{
	char	*varname;

	varname = get_varname_export(cmd->cmd[i]);
	if (!varname)
		error_quit(minishell, "Malloc failure within do_export.\n");
	if (!is_correct_format(varname))
	{
		ft_fprintf(2, "Minishell: export: `%s': not a valid identifier\n",
			cmd->cmd[i]);
		minishell->status = 1;
		free(varname);
		varname = NULL;
		return (1);
	}
	else if (already_exists(varname, minishell) == NOT_FOUND)
		add_var(minishell, cmd->cmd[i]);
	else
		change_var(minishell, cmd->cmd[i], varname);
	free(varname);
	varname = NULL;
	return (0);
}

/*	Builtin:
	Permet de savoir a quel type d'export on a affaire
	et agit en consequence. */
void	do_export(t_minishell *minishell, t_cmd *cmd, int j)
{
	int	i;

	i = j;
	minishell->status = 0;
	if (!cmd->cmd[1 + j])
		print_alphabetical_env(minishell);
	else
	{
		while (cmd->cmd[++i])
		{
			if (ft_strlen(cmd->cmd[i]) > EXPORT_SIZE)
				continue ;
			if (do_export_loop(minishell, cmd, i))
				continue ;
		}
	}
}

void	error_quit(t_minishell *minishell, char *msg)
{
	(void)minishell;
	if (msg)
		ft_fprintf(2, "%s", msg);
	exit(1);
}

void	update_underscore_var(t_minishell *minishell, char **cmd)
{
	int	i;
	int	j;

	if (!cmd || !cmd[0])
		return ;
	i = -1;
	while (cmd[++i])
		;
	j = get_var_index(minishell->env, "_=");
	if (j == NOT_FOUND)
		return ;
	free(minishell->env[j]);
	minishell->env[j] = NULL;
	minishell->env[j] = ft_strjoin("_=", cmd[i - 1]);
	if (!minishell->env[j])
	{
		free_split(&(minishell->env[j + 1]));
		error_quit(minishell, "_ Update failed.\n");
	}
}


/*	Builtin:
	affiche le dossier courant	*/
void	print_pwd(t_minishell *minishell)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
	{
		ft_fprintf(2, "Minishell: pwd: No pwd.\n");
		minishell->status = 1;
		return ;
	}
	if (!safe_putstr(buf) || !safe_putstr("\n"))
	{
		ft_fprintf(2, "Minishell: Permission denied.\n");
		free(buf);
		buf = NULL;
		minishell->status = 1;
		return ;
	}
	minishell->status = 0;
	free(buf);
	buf = NULL;
}


static void	delete_var(t_minishell *minishell, int i)
{
	free(minishell->env[i]);
	while (minishell->env[i + 1])
	{
		minishell->env[i] = minishell->env[i + 1];
		i++;
	}
	minishell->env[i] = NULL;
}

/*	Builtin:
	sert a retirer une variable de l'environnement	*/
void	do_unset(t_minishell *minishell, t_cmd *cmd, int j)
{
	int	i;
	int	var_index;
	int	exit_value;

	exit_value = 0;
	i = 1 + j;
	while (cmd->cmd[i])
	{
		var_index = get_var_index(minishell->env, cmd->cmd[i]);
		if (var_index != NOT_FOUND)
			delete_var(minishell, var_index);
		i++;
	}
	minishell->status = exit_value;
}
