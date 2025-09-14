/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:48:35 by gmanique          #+#    #+#             */
/*   Updated: 2025/09/13 19:20:55 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_term.h"

int			g_sig;

static void	skip_till_joinorws(char *input, int *i)
{
	char	str;

	str = '\0';
	while (input[*i])
	{
		if (is_quote(input[*i]))
			handle_str(input[*i], &str);
		if (!str && (ft_iswhitespace(input[*i]) || is_token_join(&input[*i])))
			return ;
		*i += 1;
	}
}


static int	handle_eof(char **dest, char *elem)
{
	int	rep;
	int	len;

	if (elem[0] == '\'' && elem[ft_strlen(elem) - 1] == '\'')
		rep = 1;
	else if (elem[0] == '\"' && elem[ft_strlen(elem) - 1] == '\"')
		rep = 0;
	else
		rep = -1;
	len = ft_strlen(elem);
	if (rep != -1)
	{
		*dest = ft_strdup(&elem[1]);
		(*dest)[len - 2] = '\n';
		(*dest)[len - 1] = '\0';
	}
	else
		*dest = ft_strjoin(elem, "\n");
	return (rep > 0);
}

static int	nblen(int nb)
{
	if (nb / 10 == 0 && nb >= 0)
		return (1);
	if (nb == -2147483648)
		return (11);
	if (nb < 0)
		return (nblen(-nb) + 1);
	return (nblen(nb / 10) + 1);
}

static char	*get_exit_expand_heredoc(t_minishell *minishell, char *rep,
		char *tmp, int *i)
{
	tmp = free_join(ft_strndup(rep, (*i)), ft_itoa(minishell->status), 3);
	tmp = free_join(tmp, &rep[(*i) + 2], 1);
	*i += nblen(minishell->status);
	free(rep);
	rep = tmp;
	return (rep);
}

static void	free_in_loop(char **str, char **rep)
{
	free(*str);
	free(*rep);
	*str = NULL;
	*rep = NULL;
}

void	get_input_loop(char *eof, char **rep, char *end_of_file)
{
	char	*str;

	str = readline("> ");
	if (str)
		str = free_join(str, "\n", 1);
	if (g_sig != 0)
		return ;
	while (str && ft_strcmp(str, end_of_file))
	{
		*rep = free_join(*rep, str, 3);
		str = readline("> ");
		if (str)
			str = free_join(str, "\n", 1);
		if (g_sig != 0)
			free_in_loop(&str, rep);
	}
	if (!str && g_sig == 0)
		ft_fprintf(2, "Minishell: warning: %s end-of-file (wanted `%s')\n",
			"here-document delimited by", eof);
	if (str)
	{
		free(str);
		str = NULL;
	}
}


static char	*expand_heredoc(t_minishell *minishell, char *rep)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	if (!rep)
		return (NULL);
	while (rep[i])
	{
		if (rep[i] == '$' && rep[i + 1] == '?')
			rep = get_exit_expand_heredoc(minishell, rep, tmp, &i);
		else if (rep[i] == '$')
		{
			tmp2 = get_varname_expand(&rep[i + 1]);
			tmp = free_join(ft_strndup(rep, i), get_var_content(minishell->env,
						0, tmp2), 1);
			i += ft_strlen(tmp2);
			tmp = free_join(tmp, &rep[i], 1);
			multi_free(tmp2, rep, NULL, NULL);
			rep = tmp;
		}
		else
			i++;
	}
	return (rep);
}


static int	corresponds_to_wc(char *wc, char *filename, int i, int j)
{
	if (!wc || !filename || !wc[0] || !filename[0])
		return (0);
	while (i < ft_strlen(wc) && j < ft_strlen(filename) && wc[i] && filename[j])
	{
		if (wc[i] == '*')
		{
			while (wc[i] == '*')
				i++;
			if (!wc[i])
				return (1);
			while (filename[j] && !corresponds_to_wc(&wc[i], &filename[j], 0,
					0))
				j++;
			if (!filename[j])
				return (0);
		}
		if (filename[j] != wc[i])
			return (0);
		if (!filename[j] && !wc[i])
			return (1);
		if (filename[j])
			j++;
		i++;
	}
	return (wc[i] == filename[j]);
}

static int	do_first_if(t_minishell *minishell, t_bintree *cmd, int i)
{
	safe_close(cmd->fd_in);
	if (cmd->cmd->cmd[i + 1] && is_token_join(cmd->cmd->cmd[i + 1]))
		return (error_msg_set_status(minishell,
				"Minishell: syntax error near unexpected token `newline'\n", 2),
			1);
	else if (cmd->cmd->cmd[i + 1])
		cmd->fd_in = open(cmd->cmd->cmd[i + 1], O_RDONLY, 0644);
	else
		return (error_msg_set_status(minishell,
				"Minishell: syntax error near unexpected token `newline'\n", 2),
			1);
	if (cmd->fd_in == -1)
		return (minishell->status = 1, ft_fprintf(2,
				"Minishell: %s: No such file or directory\n",
				cmd->cmd->cmd[i + 1]), 1);
	return (0);
}

static int	do_second_if(t_minishell *minishell, t_bintree *cmd, int i)
{
	safe_close(cmd->fd_out);
	if (cmd->cmd->cmd[i + 1] && is_token_join(cmd->cmd->cmd[i + 1]))
		return (error_msg_set_status(minishell,
				"Minishell: syntax error near unexpected token `newline'\n", 2),
			1);
	else if (!cmd->cmd->cmd[i][1] && cmd->cmd->cmd[i + 1])
		cmd->fd_out = open(cmd->cmd->cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC,
				0644);
	else if (cmd->cmd->cmd[i][1] == '>' && cmd->cmd->cmd[i + 1])
		cmd->fd_out = open(cmd->cmd->cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND,
				0644);
	else
		return (error_msg_set_status(minishell,
				"Minishell: syntax error near unexpected token `newline'\n", 2),
			1);
	if (cmd->fd_out == -1)
		return (minishell->status = 1, ft_fprintf(2,
				"Minishell: permission denied: %s\n", cmd->cmd->cmd[i + 1]), 1);
	return (0);
}


static char	**insert_wildcard(char **rep, char *wildcard, char **files)
{
	int	i;
	int	found_something;

	found_something = 0;
	i = -1;
	if (!files)
		return (rep);
	while (files[++i])
	{
		if (corresponds_to_wc(wildcard, files[i], 0, 0) && files[i][0] != '.')
		{
			found_something = 1;
			rep = strs_add_free(rep, files[i]);
			if (!rep)
			{
				return (NULL);
			}
		}
	}
	if (!found_something)
		rep = strs_add_free(rep, wildcard);
	return (rep);
}


static t_bintree	*delete_redirs(t_bintree *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd && cmd->cmd && cmd->cmd->cmd && cmd->cmd->cmd[i])
	{
		j = i - 1;
		if (cmd->cmd->cmd[i][0] == '<' && cmd->cmd->cmd[i][1] == '<')
		{
			free(cmd->cmd->cmd[i]);
			while (++j + 1 < ft_strstrlen(cmd->cmd->cmd))
				cmd->cmd->cmd[j] = cmd->cmd->cmd[j + 1];
			cmd->cmd->cmd[j] = NULL;
		}
		else if (cmd->cmd->cmd[i][0] == '<' || cmd->cmd->cmd[i][0] == '>')
		{
			multi_free(cmd->cmd->cmd[i], cmd->cmd->cmd[i + 1], NULL, NULL);
			while (++j + 2 < ft_strstrlen(cmd->cmd->cmd))
				cmd->cmd->cmd[j] = cmd->cmd->cmd[j + 2];
			cmd->cmd->cmd[j] = NULL;
		}
		else
			i++;
	}
	return (cmd);
}

/*	return un strdnup de str jusqu'au prochain pipe	*/
static char	*get_till_pipe(char *str, int *i, char *dep)
{
	int	j;

	j = *i;
	if (!ft_strchr(&str[*i], '|'))
	{
		*i += ft_strlen(&str[*i]);
		return (ft_strdup(&str[j]));
	}
	else
	{
		while (str[*i] && (*dep || str[*i] != '|'))
		{
			if (is_quote(str[*i]))
				handle_str(str[*i], dep);
			*i += 1;
		}
		return (ft_strndup(&str[j], *i - j));
	}
}


t_bintree	*parse_redir(t_minishell *minishell, t_bintree *cmd)
{
	int	i;

	if (empty_redir(minishell, cmd))
		return (NULL);
	cmd->cmd->heredoc = -1;
	i = 0;
	while (cmd && cmd->cmd && cmd->cmd->cmd && cmd->cmd->cmd[i])
	{
		if (cmd->cmd->cmd[i][0] == '<' && cmd->cmd->cmd[i][1] == '<')
			cmd->cmd->heredoc = ft_atoi(&cmd->cmd->cmd[i][2]);
		else if (cmd->cmd->cmd[i][0] == '<' && !cmd->cmd->cmd[i][1])
		{
			if (do_first_if(minishell, cmd, i))
				return (NULL);
		}
		else if (cmd->cmd->cmd[i][0] == '>')
		{
			if (do_second_if(minishell, cmd, i))
				return (NULL);
		}
		i++;
	}
	if (cmd->cmd->heredoc != -1)
		safe_close(cmd->fd_in);
	return (delete_redirs(cmd));
}


char	**replace_wildcards(t_minishell *minishell, t_cmd *cmd)
{
	int		i;
	char	**files;
	char	**rep;

	i = -1;
	rep = malloc(sizeof(char *));
	if (!rep)
		return (NULL);
	rep[0] = NULL;
	files = get_files();
	while (cmd->cmd[++i])
	{
		if (!ft_strchr(cmd->cmd[i], '*') || cmd->cmd[i][0] == '\''
			|| cmd->cmd[i][0] == '\"')
			rep = strs_add_free(rep, cmd->cmd[i]);
		else
			rep = insert_wildcard(rep, cmd->cmd[i], files);
		if (!rep)
			return (free_split(files), error_quit(minishell,
					"Malloc failure.\n"), NULL);
	}
	free_split(cmd->cmd);
	return (free_split(files), rep);
}


t_cmd	*delete_eof(int index, t_cmd *cmd)
{
	int	i;
	int	len;

	len = ft_strstrlen(cmd->cmd);
	i = index;
	free(cmd->cmd[i]);
	while (i < len)
	{
		cmd->cmd[i] = cmd->cmd[i + 1];
		i++;
	}
	cmd->cmd[i] = NULL;
	return (cmd);
}

int	ft_isnumber(char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '-')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

t_bintree	*get_heredoc_content(t_minishell *minishell, t_bintree *tree)
{
	if (!tree)
		return (NULL);
	if (tree->l_branch)
		tree->l_branch = get_heredoc_content(minishell, tree->l_branch);
	if (tree->type == type_cmd && tree->cmd && tree->cmd->cmd
		&& has_heredoc(tree->cmd->cmd))
		tree->cmd = get_heredocs_in_cmd(minishell, tree->cmd);
	if (tree->r_branch)
		tree->r_branch = get_heredoc_content(minishell, tree->r_branch);
	return (tree);
}

int	count_heredocs(t_bintree *tree)
{
	int	cpt;
	int	i;

	i = 0;
	cpt = 0;
	if (!tree)
		return (0);
	if (tree->l_branch)
		cpt += count_heredocs(tree->l_branch);
	if (tree->r_branch)
		cpt += count_heredocs(tree->r_branch);
	while (tree->type == type_cmd && tree->cmd && tree->cmd->cmd
		&& tree->cmd->cmd[i])
	{
		if (tree->cmd->cmd[i][0] == '<' && tree->cmd->cmd[i][1] == '<')
			cpt++;
		i++;
	}
	return (cpt);
}

/*	lexe en separant sur les pipes	*/
static char	**lex_pipes(char *str)
{
	char	**rep;
	int		i;
	char	*tmp;
	char	dep;

	dep = '\0';
	i = 0;
	if (!str)
		return (NULL);
	rep = ft_calloc(1, sizeof(char *));
	if (!rep)
		return (NULL);
	while (str[i] && rep)
	{
		while (ft_iswhitespace(str[i]))
			i++;
		if (!dep && (str[i] == '|') && ++i)
			rep = strs_add_free(rep, "|");
		else
		{
			rep = strs_add_free(rep, tmp = get_till_pipe(str, &i, &dep));
			free(tmp);
		}
	}
	return (rep);
}


int	ft_strstrcmp(char **strs1, char **strs2)
{
	int	i;
	int	n;

	i = 0;
	if (!strs1 && !strs2)
		return (0);
	if (!strs1)
		return (ft_strcmp(NULL, strs2[0]));
	if (!strs2)
		return (ft_strcmp(strs1[0], NULL));
	while (strs1[i] && strs2[i])
	{
		n = ft_strcmp(strs1[i], strs2[i]);
		if (n != 0)
			return (n);
		i++;
	}
	return (ft_strcmp(strs1[i], strs2[i]));
}

/*	return true si elem n'a ni &&, ni ||, ni ()	*/
static int	no_par_no_and_no_or(char *elem)
{
	int		i;
	char	str;

	i = -1;
	str = '\0';
	while (elem[++i])
	{
		if (is_quote(elem[i]))
			handle_str(elem[i], &str);
		if (!str && ((elem[i] == '|' && elem[i + 1] == '|') || (elem[i] == '&'
					&& elem[i + 1] == '&') || elem[i] == '('))
			return (0);
	}
	return (1);
}

/*	return true s'il y a des parentheses dans elem	*/
static int	has_a_par(char *elem)
{
	int		i;
	char	str;

	i = 0;
	str = '\0';
	while (elem && elem[i])
	{
		if (!str && elem[i] == '(')
			return (1);
		else if (is_quote(elem[i]))
			handle_str(elem[i], &str);
		i++;
	}
	return (0);
}

static char	**lexer_step2_helper(char **lex, char **tmp, int i, int *j)
{
	*j = 0;
	while (tmp[*j])
	{
		if (*j == 0)
		{
			free((lex)[i]);
			(lex)[i] = ft_strdup(tmp[0]);
		}
		else
			lex = strs_insert(lex, tmp[*j], i + *j);
		*j += 1;
	}
	return (lex);
}

char	**delete_empty(char **cmd)
{
	int		i;
	char	**rep;

	i = 0;
	if (!cmd)
		return (NULL);
	rep = ft_calloc(1, sizeof(char *));
	if (!rep)
		return (NULL);
	while (cmd[i])
	{
		if (cmd[i][0] != '\0')
		{
			rep = strs_add_free(rep, cmd[i]);
			if (!rep)
				return (free_split(cmd), cmd = NULL, NULL);
		}
		i++;
	}
	free_split(cmd);
	cmd = NULL;
	return (rep);
}

static char	*takeoff_quotes_from_one(char *cmd)
{
	int		i;
	char	str;
	char	*rep;

	i = 0;
	str = '\0';
	rep = ft_calloc(1, sizeof(char));
	if (!rep)
		return (NULL);
	while (cmd[i])
	{
		if (is_quote(cmd[i]))
		{
			if (cmd[i] == str || !str)
				handle_str(cmd[i++], &str);
			else
			{
				handle_str(cmd[i], &str);
				rep = free_join(rep, get_char(cmd[i++]), 3);
			}
		}
		else
			rep = free_join(rep, get_char(cmd[i++]), 3);
	}
	return (free(cmd), cmd = NULL, rep);
}


static char	*quote_case(char *rep, char *cmd, int *i, char *str)
{
	rep = free_join(rep, get_char(cmd[*i]), 3);
	handle_str(cmd[(*i)], str);
	*i += 1;
	return (rep);
}

static char	*not_dollar_case(t_minishell *mini, char *rep, char *tmp, int *i)
{
	rep = free_join(rep, get_expand(mini, tmp), 3);
	*i += ft_strlen(tmp) + (last_char(tmp) != '=') - 1;
	return (rep);
}

static char	*expand_loop(t_minishell *mini, char str, char *rep, char *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmd[i])
	{
		if (is_quote(cmd[i]))
			rep = quote_case(rep, cmd, &i, &str);
		else if (str != '\'' && cmd[i] == '$')
		{
			tmp = get_varname_expand(&cmd[i + 1]);
			if (tmp && tmp[0] != '$')
				rep = not_dollar_case(mini, rep, tmp, &i);
			else if (str || !is_quote(cmd[i + 1]))
				rep = free_join(rep, tmp, 1);
			free(tmp);
			tmp = NULL;
			i++;
		}
		else
			rep = free_join(rep, get_char(cmd[i++]), 3);
	}
	return (rep);
}

static char	*expand_variables_from_one(t_minishell *minishell, char *cmd)
{
	char	*rep;
	char	str;

	if (!cmd)
		return (NULL);
	rep = ft_calloc(1, sizeof(char));
	if (!rep)
		return (NULL);
	str = '\0';
	rep = expand_loop(minishell, str, rep, cmd);
	return (free(cmd), cmd = NULL, rep);
}

/* Renvoie l'index d'une variable d'environnement donnee. */
/* Format var : "PATH=", "PWD=", etc. */
/* Si variable non trouvee, renvoie NOT_FOUND  (-404) */
int	get_var_index(char **env, char *var)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], var, ft_strlen(var)))
			return (i);
	}
	return (NOT_FOUND);
}

static char	*get_bracket(char *input, int *i)
{
	char	*rep;
	int		j;
	int		cpt;

	cpt = 0;
	j = (*i) + 1;
	while (input[j])
	{
		if (input[j] == '(')
			cpt++;
		if (input[j] == ')')
			cpt--;
		if (cpt == -1)
			break ;
		j++;
	}
	rep = malloc((j - *i + 1) * sizeof(char));
	if (!rep)
		return (NULL);
	ft_strlcpy(rep, &input[*i + 1], j - *i);
	rep[j - *i - 1] = '\0';
	*i = j + 1;
	return (rep);
}

/* Permet de recuperer la variable (exemple "$PATH")*/
static char	*get_dollar_var(char *input, int *i)
{
	int		j;
	char	*rep;

	j = *i;
	*i += 1;
	if (input[*i] == '?')
		return (*i += 1, ft_strdup("$?"));
	if (!ft_isalpha(input[*i]) && input[*i] != '_')
		return (*i += 1, get_till_end_of_word(input, i));
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		*i += 1;
	rep = malloc((((*i) - j) + 1) * sizeof(char));
	if (!rep)
		return (NULL);
	ft_strlcpy(rep, &input[j], *i - j + 1);
	rep[*i - j + 1] = '\0';
	return (rep);
}

/* Permet de recuperer un "" ou '' entierement */
static char	*get_till_end_of_str(char *input, int *i)
{
	char	c;
	int		j;
	char	*rep;
	int		cpt;

	c = input[*i];
	j = *i;
	*i += 1;
	while (input[*i] && input[*i] != c)
		*i += 1;
	rep = malloc((((*i) - j) + 2) * sizeof(char));
	if (!rep)
		return (NULL);
	cpt = 0;
	while (j <= *i)
	{
		rep[cpt] = input[j];
		cpt++;
		j++;
	}
	rep[cpt] = '\0';
	*i += 1;
	return (rep);
}

static char	*get_token(char *input, int *i)
{
	char	*c;

	if (input[*i] == '\'' || input[*i] == '\"')
		return (get_till_end_of_str(input, i));
	if (input[*i] == '$')
		return (get_dollar_var(input, i));
	if (input[*i] == '(')
		return (get_bracket(input, i));
	if (input[*i] == '>' && input[*i + 1] == '>')
		return (*i += 2, ft_strdup(">>"));
	if (input[*i] == '<' && input[*i + 1] == '<')
		return (*i += 2, ft_strdup("<<"));
	if (input[*i] == '&' && input[*i + 1] == '&')
		return (*i += 2, ft_strdup("&&"));
	if (input[*i] == '|' && input[*i + 1] == '|')
		return (*i += 2, ft_strdup("||"));
	c = malloc(2);
	if (!c)
		return (NULL);
	c[0] = input[*i];
	c[1] = '\0';
	*i += 1;
	return (c);
}

/*	Premiere partie du lexer:
	tokenise en separant sur les redirs	*/
char	**lexer_step3(t_minishell *minishell, char *input)
{
	char	**tokens;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!input)
		return (NULL);
	tokens = malloc((get_nb_tokens(input) + 1) * sizeof(char *));
	if (!tokens)
		error_quit(minishell, "Malloc failure.\n");
	while (input[i])
	{
		while (ft_iswhitespace(input[i]))
			i++;
		if (input[i] && (input[i] == '>' || input[i] == '|' || input[i] == '<'))
			tokens[j++] = get_token(input, &i);
		else if (input[i])
			tokens[j++] = get_till_end_of_word(input, &i);
		if (input[i] && tokens[j - 1] == NULL)
			return (free_split(tokens), tokens = NULL, error_quit(minishell,
					"Malloc failure.\n"), NULL);
	}
	tokens[j] = NULL;
	return (tokens);
}



int	is_token_join(char *input)
{
	if (!input || !input[0])
		return (0);
	return (input[0] == '>' || input[0] == '|' || input[0] == '<'
		|| (input[0] == '&' && input[1] == '&'));
}


char	*delete_newline(char *str)
{
	int		i;
	char	*rep;

	i = 0;
	if (!str)
		return (str);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
	{
		rep = ft_strndup(str, i);
		free(str);
		str = NULL;
	}
	else
		return (str);
	return (rep);
}

/* Utiliser soit l'index par i, soit le */
/* nom sous le format "PWD=", "SHLVL=", etc. */
char	*get_var_content(char **env, int i, char *varname)
{
	int	j;

	if (varname)
		i = get_var_index(env, varname);
	if (i == NOT_FOUND)
		return (NULL);
	j = 0;
	while (env[i][j] && env[i][j] != '=')
		j++;
	if (env[i][j])
		return (&(env[i][j + 1]));
	return (NULL);
}

/* Permet de restorer STDIN et STDOUT en cas de besoin */
void	restore_dup(t_minishell *minishell)
{
	dup2(minishell->save_stdout, STDOUT_FILENO);
	dup2(minishell->save_stdin, STDIN_FILENO);
}

/* Permet d'augmenter ou diminuer le SHLVL. */
void	update_shell_lvl(t_minishell *minishell, int change)
{
	int		i;
	int		nb;
	char	*new_lvl;

	i = get_var_index(minishell->env, "SHLVL=");
	if (i == NOT_FOUND)
		return ;
	nb = ft_atoi(&(minishell->env[i][6]));
	nb += change;
	new_lvl = ft_itoa(nb);
	if (!new_lvl)
		return ;
	free(minishell->env[i]);
	minishell->env[i] = NULL;
	minishell->env[i] = ft_strjoin("SHLVL=", new_lvl);
	free(new_lvl);
	new_lvl = NULL;
	if (!minishell->env[i])
	{
		free_split(&(minishell->env[i + 1]));
		error_quit(minishell, "SHLVL Update failed.\n");
	}
}

char	**expand_variables(t_minishell *minishell, char **cmd)
{
	int	i;

	i = -1;
	if (!cmd)
		return (NULL);
	while (cmd[++i])
		cmd[i] = expand_variables_from_one(minishell, cmd[i]);
	return (cmd);
}



/* retire les quotes avant d'executer */
char	**takeoff_quotes(char **cmd)
{
	int	i;

	i = -1;
	if (!cmd)
		return (NULL);
	while (cmd[++i])
		cmd[i] = takeoff_quotes_from_one(cmd[i]);
	cmd[i] = NULL;
	return (cmd);
}


/*	Premiere partie du lexer:
	tokenise en separant sur les pipes	*/
char	**lexer_step2(t_minishell *minishell, char **lex)
{
	int		i;
	int		j;
	char	**tmp;

	i = -1;
	while (lex[++i])
	{
		if (has_pipe(lex[i]))
		{
			tmp = lex_pipes(lex[i]);
			if (!tmp)
				return (free_split(lex), error_quit(minishell,
						"Malloc failure.\n"), NULL);
			lex = lexer_step2_helper(lex, tmp, i, &j);
			free_split(tmp);
			if (!lex)
				error_quit(minishell, "Malloc failure.\n");
			i += j;
		}
		if (i >= ft_strstrlen(lex))
			break ;
	}
	return (lex);
}

/* return le lexer necessaire en fonction de
   s'il y a besoin de faire lexer_step 1, 2 ou 3 */
static char	**get_lex(t_minishell *minishell, t_bintree **tree, char *str)
{
	char	**lex;
	char	**dup;

	lex = NULL;
	if (str && !no_par_no_and_no_or(str))
		lex = lexer_step1(str);
	else if (str && has_pipe(str))
	{
		dup = ft_strstrdup((*tree)->cmd->cmd);
		lex = lexer_step2(minishell, (*tree)->cmd->cmd);
		(*tree)->cmd->cmd = NULL;
		if (ft_strstrcmp(lex, dup) == 0)
		{
			free_split(lex);
			lex = lexer_step3(minishell, dup[0]);
		}
		free_split(dup);
	}
	else if (str)
		lex = lexer_step3(minishell, str);
	if (str && !lex)
		error_quit(minishell, "Malloc failure.\n");
	return (lex);
}

/* gestion recursive du parsing dans l'arbre,
	verifie chaque noeud pour voir s'il a
	encore besoin d'etre lexé et le lexe
	en consequence  */
static int	recursive_parse(t_minishell *minishell, t_bintree **tree)
{
	int			cpt;
	t_bintree	*node;
	t_bintree	*tmp;
	char		**lex;

	cpt = 0;
	lex = NULL;
	if (!*tree)
		return (0);
	if ((*tree)->l_branch)
		cpt += recursive_parse(minishell, &(*tree)->l_branch);
	if ((*tree)->r_branch)
		cpt += recursive_parse(minishell, &(*tree)->r_branch);
	if ((*tree)->cmd && ((get_nb_tokens((*tree)->cmd->cmd[0]) > 1)
			|| has_a_par((*tree)->cmd->cmd[0])))
	{
		lex = get_lex(minishell, tree, (*tree)->cmd->cmd[0]);
		if (!lex)
			return (free_tree(*tree), -1);
		return (node = parse(minishell, &lex), tmp = *tree, *tree = node,
			free_tree(tmp), free_split(lex), ++cpt);
	}
	return (cpt);
}

/* fonction principale du parsing,
	return l'arbre definitif a partir du lexer */
t_bintree	*parse(t_minishell *minishell, char ***lex)
{
	t_bintree	*node;
	t_bintree	*tree;
	int			i;

	if (!lex)
		return (NULL);
	i = 0;
	tree = NULL;
	while (i < ft_strstrlen(*lex))
	{
		node = get_next_node(minishell, lex, &i);
		append_node_tree(&tree, &node);
	}
	i = 1;
	while (i > 0)
		i = recursive_parse(minishell, &tree);
	if (i == -1)
		error_quit(minishell, "Allocation error recursive_parse");
	return (fix_empty_nodes(tree));
}

int	is_quote(char c)
{
	return (c == '\"' || c == '\'');
}

int	has_heredoc(char **strs)
{
	int		i;
	int		j;
	char	sstr;

	sstr = '\0';
	i = -1;
	while (strs[++i])
	{
		j = -1;
		sstr = '\0';
		while (strs[i][++j])
		{
			if (is_quote(strs[i][j]))
				handle_str(strs[i][j], &sstr);
			if (!sstr && strs[i][j] == '<')
				return (1);
		}
	}
	return (0);
}


static char	*get_brack(char *input, int *index)
{
	int		i;
	int		depth;
	char	str;

	i = *index;
	depth = 1;
	str = '\0';
	*index += 1;
	while (input[*index])
	{
		if (is_quote(input[*index]))
			handle_str(input[*index], &str);
		if (str == '\0')
		{
			if (input[*index] == '(')
				depth++;
			else if (input[*index] == ')')
				depth--;
			if (depth == 0)
				break ;
		}
		*index += 1;
	}
	return (ft_strndup(&input[i + 1], *index - i - 1));
}

static char	*get_other(char *input, int *index)
{
	int		i;
	char	str;

	i = *(index);
	str = '\0';
	while (input[*(index)])
	{
		if (is_quote(input[*(index)]))
			handle_str(input[*(index)], &str);
		if (str == '\0')
		{
			if (input[*(index)] == '(' || (input[*(index)] == '&'
					&& input[(*(index)) + 1] == '&') || (input[*(index)] == '|'
					&& input[(*(index)) + 1] == '|'))
				break ;
		}
		*(index) += 1;
	}
	while (*(index)-1 >= 0 && ft_iswhitespace(input[*(index)-1]))
		*index -= 1;
	return (ft_strndup(&input[i], (*(index)) - i));
}

static char	*get_content(char *input, int *i)
{
	char	*tmp;

	tmp = NULL;
	if (input[*i] == '(')
	{
		tmp = get_brack(input, i);
		*i += 1;
	}
	else if (((input[*i] == '&' && input[*i + 1] == '&') || (input[*i] == '|'
				&& input[*i + 1] == '|')))
	{
		*i += 2;
		tmp = ft_strndup(&input[*i - 2], 2);
	}
	else if (input[*i])
		tmp = get_other(input, i);
	return (tmp);
}

/*	Premiere partie du lexer:
	tokenise en separant sur les (), &&, ||	*/
char	**lexer_step1(char *input)
{
	int		i;
	char	**rep;
	char	*tmp;

	i = 0;
	rep = ft_calloc(1, sizeof(char *));
	if (!rep)
		return (NULL);
	while (input && i < ft_strlen(input))
	{
		while (ft_iswhitespace(input[i]))
			i++;
		if (!input[i])
			break ;
		tmp = get_content(input, &i);
		if (!tmp)
			return (free_split(rep), NULL);
		rep = strs_add_free(rep, tmp);
		free(tmp);
		tmp = NULL;
		if (!rep)
			return (NULL);
	}
	return (rep);
}

int	correct_quotes(t_minishell *minishell, char *input)
{
	int		i;
	char	str;

	i = 0;
	str = '\0';
	if (!input)
		return (1);
	while (input[i])
	{
		if (input[i] == '\"' || input[i] == '\'')
			handle_str(input[i], &str);
		i++;
	}
	if (str != '\0')
	{
		ft_fprintf(2, "Minishell: Unclosed quote: `%c'\n", str);
		minishell->status = 2;
		return (0);
	}
	return (1);
}

static int	get_brack_content_len(char *input, int i)
{
	int		cpt;
	char	str;
	int		j;

	j = ++i;
	str = '\0';
	cpt = 0;
	while (input[i] && cpt >= 0)
	{
		if (input[i] == '\"' && str == '\0')
			str = '\"';
		else if (input[i] == '\"' && str == '\"')
			str = '\0';
		else if (input[i] == '\'' && str == '\0')
			str = '\'';
		else if (input[i] == '\'' && str == '\'')
			str = '\0';
		else if (input[i] == '(' && str == '\0')
			cpt++;
		else if (input[i] == ')' && str == '\0')
			cpt--;
		i++;
	}
	return (i - j - 1);
}

static char	*get_brack_content(char *input, int i)
{
	char	*rep;
	int		len;

	len = get_brack_content_len(input, i);
	rep = malloc((len + 1) * sizeof(char));
	if (!rep)
		return (ft_fprintf(2, "Error Malloc in get_brack_content().\n"), NULL);
	ft_strlcpy(rep, &input[i], len);
	rep[len] = '\0';
	return (rep);
}

static int	no_join_around(char *input, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (!ft_iswhitespace(input[j]))
			return (0);
		j++;
	}
	i += 2 + get_brack_content_len(input, i);
	while (input[i])
	{
		if (!ft_iswhitespace(input[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	case_not_sub_brack(char *brack, int j, int str)
{
	return ((is_join(&brack[j]) || brack[j] == '>' || brack[j] == '<')
		&& str == '\0' && brack[j] != ')' && brack[j] != '('
		&& brack[j] != '$');
}

int	is_useless_brack(char *input, int i)
{
	char	*brack;
	int		j;
	char	str;
	int		sub_brack;

	sub_brack = 0;
	str = '\0';
	j = 0;
	if (no_join_around(input, i))
		return (1);
	brack = get_brack_content(input, i);
	if (!brack || !brack[0])
		return (-1);
	while (brack[++j])
	{
		if (brack[j] == ')')
			sub_brack--;
		if (brack[j] == '(')
			sub_brack++;
		if (brack[j] == '\"' || brack[j] == '\'')
			handle_str(brack[j], &str);
		else if (!sub_brack && case_not_sub_brack(brack, j, str))
			return (free(brack), brack = NULL, 0);
	}
	return (free(brack), brack = NULL, 1);
}



static int	is_a_directory(char *elem)
{
	struct stat	buf;
	int			rep;

	if (stat(elem, &buf) != 0)
		return (0);
	rep = S_ISDIR(buf.st_mode);
	return (rep);
}

int	check_error(t_minishell *minishell, t_bintree *cmd, int i)
{
	if (!minishell || !cmd || !cmd->cmd || !cmd->cmd->cmd || !cmd->cmd->cmd[i])
		return (1);
	if (is_a_directory(cmd->cmd->cmd[i]))
	{
		ft_fprintf(2, "Minishell: %s: Is a directory\n", cmd->cmd->cmd[i]);
		return (126);
	}
	else if (minishell->status == 127)
		ft_fprintf(2, "Minishell: %s: command not found\n", cmd->cmd->cmd[i]);
	else if (minishell->status == 126)
		ft_fprintf(2, "Minishell: %s: No such file or directory\n",
			cmd->cmd->cmd[i]);
	return (minishell->status + (minishell->status == 126
			&& get_var_index(minishell->env, "PATH=") == NOT_FOUND));
}

/* Permet de tranformer par exemple "/usr/bin" et "ls" en "/usr/bin/ls" */
static char	*turn_to_cmd(char *path, char *cmd)
{
	char	*rep;
	char	*temp;

	temp = ft_strjoin(path, "/");
	if (!temp)
		return (NULL);
	rep = ft_strjoin(temp, cmd);
	free(temp);
	temp = NULL;
	if (!rep)
		return (NULL);
	return (rep);
}

/* Permet de tranformer par exemple "ls" en "/usr/bin/ls" */
char	*get_path(t_minishell *minishell, char *cmd)
{
	int		i;
	char	**paths;
	char	*path;
	char	*fullcmd;

	path = get_var_content(minishell->env, 0, "PATH=");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		fullcmd = turn_to_cmd(paths[i], cmd);
		if (!fullcmd)
			return (free_split(paths), NULL);
		if (access(fullcmd, F_OK) == 0)
			return (free_split(paths), paths = NULL, fullcmd);
		free(fullcmd);
		fullcmd = NULL;
		i++;
	}
	free_split(paths);
	return (ft_strdup(cmd));
}

/*	gere les expand, wildcards et quotes, return 0 si qqch s'est mal passe	*/
int	handle_expand(t_minishell *minishell, t_bintree *cmd)
{
	if (!cmd || !cmd->cmd)
		return (0);
	cmd->cmd->cmd = expand_variables(minishell, cmd->cmd->cmd);
	if (!cmd || !cmd->cmd || !cmd->cmd->cmd)
		return (0);
	cmd->cmd->cmd = replace_wildcards(minishell, cmd->cmd);
	if (!cmd || !cmd->cmd || !cmd->cmd->cmd)
		return (0);
	cmd->cmd->cmd = delete_empty(cmd->cmd->cmd);
	if (!cmd || !cmd->cmd || !cmd->cmd->cmd)
		return (0);
	cmd->cmd->cmd = takeoff_quotes(cmd->cmd->cmd);
	if (!cmd || !cmd->cmd || !cmd->cmd->cmd)
		return (0);
	return (1);
}

char	*get_varname_expand(char *content)
{
	int	i;

	i = 0;
	if (content[0] == '?' || ft_isdigit(content[0]))
		return (get_char(content[0]));
	if (!ft_isalnum(content[0]) && content[0] != '_')
		return (ft_strdup("$"));
	while (ft_isdigit(content[i]))
		i++;
	if (i != 0)
		return (free_join(ft_strndup(content, i), "=", 1));
	while (ft_isalnum(content[i]) || content[i] == '_')
		i++;
	return (free_join(ft_strndup(content, i), "=", 1));
}

/* Renvoie le dernier caractere d'une chaine de caractere */
char	last_char(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return ('\0');
	while (str[i])
		i++;
	i--;
	return (str[i]);
}


static char	*get_expand_part2(char *elem)
{
	int	i;
	int	j;

	i = 0;
	if (!elem)
		return (NULL);
	j = ft_strlen(elem) - 1;
	while (elem[i] && ft_iswhitespace(elem[i]))
		i++;
	while (j >= i && elem[j] && ft_iswhitespace(elem[j]))
		j--;
	return (ft_strndup(&elem[i], j - i + 1));
}

char	*get_expand(t_minishell *minishell, char *varname)
{
	int	i;
	int	len;

	if (!varname)
		return (NULL);
	if (varname[0] == '?')
		return (ft_itoa(minishell->status));
	i = -1;
	len = ft_strlen(varname);
	while (minishell->env[++i])
	{
		if (!ft_strncmp(minishell->env[i], varname, len))
			return (get_expand_part2(&minishell->env[i][len]));
	}
	return (ft_strdup(""));
}


char	*get_input_heredoc(t_minishell *minishell, char *eof)
{
	char	*end_of_file;
	char	*rep;
	int		type;

	end_of_file = NULL;
	if (!eof)
		return (NULL);
	rep = ft_strdup("");
	if (!rep)
		return (NULL);
	type = handle_eof(&end_of_file, eof);
	get_input_loop(eof, &rep, end_of_file);
	free(end_of_file);
	end_of_file = NULL;
	if (g_sig != 0)
	{
		minishell->status = 128 + g_sig;
		g_sig = 0;
		if (rep)
			free(rep);
		return (NULL);
	}
	if (type != 1)
		rep = expand_heredoc(minishell, rep);
	return (rep);
}

/* Sert a savoir si on est sur une jointure comme un pipe, un redirect,
	etc pour le lexer */
int	is_join(char *input)
{
	if (!input || !input[0])
		return (0);
	return (input[0] == '|' || (input[0] == '&' && input[1] == '&'));
}

/* Sert a savoir si on est sur un &&, un ||, un >>, etc de 2 caracteres */
int	is_two_join(char *input)
{
	if (!input)
		return (0);
	return ((input[0] == '|' && input[1] == '|') || (input[0] == '&'
			&& input[1] == '&') || (input[0] == '>' && input[1] == '>')
		|| (input[0] == '<' && input[1] == '<'));
}

/* Permet de recuperer le join sous forme de e_join depuis un char * */
t_join	get_join(char *input)
{
	if (!input)
		return (none);
	if (input[0] == '|' && input[1] == '|')
		return (or);
	if (input[0] == '&' && input[1] == '&')
		return (and);
	if (input[0] == '|')
		return (pipex);
	return (none);
}

int	is_not_only_join(char *input)
{
	int	i;

	i = -1;
	if (!input)
		return (0);
	if (input[0] == '<' && input[1] == '<')
		i += 2;
	if (input[0] == '>' && input[1] == '>')
		i += 2;
	if (input[0] == '&' && input[1] == '&')
		i += 2;
	while (is_join(&input[++i]))
		;
	if (i == 0)
		return (0);
	while (ft_iswhitespace(input[i]))
		i++;
	if (input[i] != '\0')
		return (i);
	return (0);
}

static void	get_word_len(char *input, int *i)
{
	char	str;

	str = '\0';
	while (input[*i])
	{
		if (input[*i] == '\'' || input[*i] == '\"')
		{
			str = input[*i];
			*i += 1;
			while (input[*i] && input[*i] != str)
				(*i)++;
			if (input[*i])
				(*i)++;
		}
		else
		{
			if (is_token_join(&input[*i]) || ft_iswhitespace(input[*i]))
				return ;
			(*i)++;
		}
	}
}

/* Permet de tout recuperer jusquau whitespace */
char	*get_till_end_of_word(char *input, int *i)
{
	char	*rep;
	int		j;
	int		cpt;

	j = *i;
	cpt = 0;
	get_word_len(input, i);
	rep = malloc((((*i) - j) + 1) * sizeof(char));
	if (!rep)
		return (NULL);
	while (j < *i)
	{
		rep[cpt] = input[j];
		cpt++;
		j++;
	}
	rep[cpt] = '\0';
	return (rep);
}


int	set_closed(char c, int cpt, int *closed)
{
	if (c == '(')
	{
		cpt++;
	}
	else if (c == ')')
	{
		cpt--;
		*closed = 1;
	}
	return (cpt);
}

void	error_msg_set_status(t_minishell *minishell, char *msg, int status)
{
	ft_fprintf(2, msg);
	minishell->status = status;
}

/* Un putstr classique mais avec une verification du write, */
/* pcq on sait jamais */
int	safe_putstr(char *str)
{
	if (!str)
		return (0);
	if (write(1, str, ft_strlen(str)) == -1)
		return (0);
	return (1);
}

int	is_builtin(t_minishell *minishell, char *elem)
{
	int	i;

	i = 0;
	while (minishell->builtins[i])
	{
		if (!ft_strncmp(minishell->builtins[i], elem,
				ft_strlen(minishell->builtins[i]) + 1))
			return (1);
		i++;
	}
	return (0);
}

/* Utile pour le lexer, pour savoir combien de tokens il y a */
int	get_nb_tokens(char *input)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	if (!input)
		return (0);
	while (input[i])
	{
		while (ft_iswhitespace(input[i]))
			i++;
		if (is_token_join(&input[i]))
		{
			i += 1 + is_two_join(&input[i]);
			nb++;
		}
		else
		{
			skip_till_joinorws(input, &i);
			nb++;
		}
	}
	return (nb);
}


/* swap 2 chaines de caracteres pour le tri */
void	swap_str(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}



/*	insert un char * a l'index voulu dans un char **	*/
char	**strs_insert(char **strs, char *str, int index)
{
	char	**new;
	int		i;

	new = malloc((ft_strstrlen(strs) + 2) * sizeof(char *));
	if (!new)
		return (perror("strs insert"), free_split(strs), strs = NULL, NULL);
	i = -1;
	while (strs && strs[++i] && i < index)
	{
		new[i] = ft_strdup(strs[i]);
		if (!new[i])
			return (free_split(new), free_split(strs), NULL);
	}
	i += (i == -1);
	new[i] = ft_strdup(str);
	while (strs && strs[i])
	{
		new[i + 1] = ft_strdup(strs[i]);
		if (!new[i + 1])
			return (free_split(new), free_split(strs), NULL);
		i++;
	}
	new[++i] = NULL;
	return (free_split(strs), strs = NULL, new);
}

/*	ajoute une string a la fin d'une chaine de strings
	free egalement strs */
char	**strs_add_free(char **strs, char *str)
{
	char	**new;
	int		i;

	new = malloc((ft_strstrlen(strs) + 2) * sizeof(char *));
	if (!new)
		return (perror("strs join"), free_split(strs), strs = NULL, NULL);
	i = -1;
	while (strs[++i])
	{
		new[i] = ft_strdup(strs[i]);
		if (!new[i])
			return (free_split(new), free_split(strs), NULL);
	}
	new[i] = ft_strdup(str);
	if (!new[i])
		return (free_split(new), free_split(strs), NULL);
	new[++i] = NULL;
	free_split(strs);
	strs = NULL;
	return (new);
}

t_bintree	*new_node(t_minishell *minishell, t_bintree *left, t_bintree *right,
		t_join join)
{
	t_bintree	*node;

	node = init_tree(NULL, join, type_join);
	if (!node)
	{
		free_tree(left);
		free_tree(right);
		error_quit(minishell, "Allocation error new_node node\n");
	}
	node->cmd = NULL;
	node->join = join;
	node->type = type_join;
	node->fd_in = -1;
	node->fd_out = -1;
	node->l_branch = left;
	node->r_branch = right;
	return (node);
}


/*	sert a recuperer un tree et sa commande a partir du lexer	*/
static t_bintree	*get_tree(t_minishell *minishell, char **lex, int i)
{
	t_cmd		*cmd;
	t_bintree	*tree;
	int			j;

	j = 0;
	tree = NULL;
	if (i >= ft_strstrlen(lex))
		return (NULL);
	while (lex[j + i] && (!is_join(lex[j + i]) || lex[j + i][0] == '<'))
		j++;
	if (j > 0)
	{
		cmd = init_cmd(lex, i, j);
		if (!cmd)
			error_quit(minishell, "Allocation error get_tree cmd\n");
		tree = init_tree(cmd, none, type_cmd);
		if (!tree)
		{
			free_cmd(cmd);
			error_quit(minishell, "Allocation error get_tree tree\n");
		}
	}
	return (tree);
}

/*	cree la prochaine node (deux tree separes d'un join)
	a partir du lexer	*/
t_bintree	*get_next_node(t_minishell *minishell, char ***lex, int *i)
{
	t_bintree	*ltree;
	t_bintree	*rtree;
	t_bintree	*node;
	t_join		join;

	node = NULL;
	ltree = get_tree(minishell, *lex, *i);
	if (ltree)
		*i += ltree->cmd->size;
	join = get_join((*lex)[*i]);
	if (is_not_only_join((*lex)[*i]))
		*lex = strs_add_free(*lex, (*lex)[*i] + is_not_only_join((*lex)[*i]));
	*i += 1;
	rtree = get_tree(minishell, *lex, *i);
	if (rtree)
		*i += rtree->cmd->size;
	node = new_node(minishell, ltree, rtree, join);
	return (node);
}

/*	ajoute la node au tree	*/
void	append_node_tree(t_bintree **tree, t_bintree **node)
{
	if (!node)
		return ;
	if (!(*tree))
	{
		(*tree) = (*node);
		return ;
	}
	if (!(*node)->l_branch)
		(*node)->l_branch = *tree;
	else if (!(*node)->r_branch)
		(*node)->l_branch = *tree;
	(*tree) = (*node);
}

/*	fonction qui supprime les nodes inutiles (none)	*/
t_bintree	*fix_empty_nodes(t_bintree *tree)
{
	t_bintree	*tmp;

	if (!tree)
		return (NULL);
	if (tree->l_branch)
		tree->l_branch = fix_empty_nodes(tree->l_branch);
	if (tree->r_branch)
		tree->r_branch = fix_empty_nodes(tree->r_branch);
	if (tree->type == type_join && tree->join == none)
	{
		if (tree->l_branch)
			tmp = tree->l_branch;
		else if (tree->r_branch)
			tmp = tree->r_branch;
		else
			tmp = NULL;
		free_cmd(tree->cmd);
		free(tree);
		tree = tmp;
	}
	return (tree);
}



static int	my_cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (ft_tolower(s1[i]) > ft_tolower(s2[i]))
			return (1);
		if (ft_tolower(s1[i]) < ft_tolower(s2[i]))
			return (-1);
		i++;
	}
	return (0);
}

static char	**sort_files(char **files)
{
	int	i;
	int	j;

	i = 0;
	while (i < ft_strstrlen(files))
	{
		j = 0;
		while (files[j] && files[j + 1])
		{
			if (my_cmp(files[j], files[j + 1]) == 1)
				swap_str(&files[j], &files[j + 1]);
			j++;
		}
		i++;
	}
	return (files);
}

/* Doit faire l'equivalent d'un ls mais en renvoyant un char **,
	fonctionne grace a opendir, readdir et closedir */
char	**get_files(void)
{
	DIR				*dir;
	struct dirent	*file;
	char			**rep;

	dir = opendir(".");
	if (!dir)
		return (ft_fprintf(2, "Opendir failed.\n"), NULL);
	rep = malloc(sizeof(char *));
	if (!rep)
		return (perror("Malloc failed in get_files.\n"), NULL);
	rep[0] = NULL;
	file = readdir(dir);
	while (file)
	{
		rep = strs_add_free(rep, file->d_name);
		if (!rep)
			return (NULL);
		file = readdir(dir);
	}
	closedir(dir);
	return (sort_files(rep));
}


int	empty_redir(t_minishell *minishell, t_bintree *cmd)
{
	int	len;

	if (!cmd || !cmd->cmd || !cmd->cmd->cmd)
		return (1);
	len = ft_strstrlen(cmd->cmd->cmd) - 1;
	if ((cmd->cmd->cmd[len][0] == '<' && cmd->cmd->cmd[len][1] != '<')
		|| cmd->cmd->cmd[len][0] == '>')
	{
		return (error_msg_set_status(minishell,
				"Minishell: syntax error near unexpected token `newline'\n", 2),
			1);
	}
	return (0);
}
