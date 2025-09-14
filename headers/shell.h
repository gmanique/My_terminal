/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:05:38 by gmanique          #+#    #+#             */
/*   Updated: 2025/09/13 21:24:57 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_STRUCT_H
# define SHELL_STRUCT_H

#include "my_term.h"

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


/* global var for signals */
extern int	g_sig;

/*	BUILTINS FCT	*/

void		error_quit(t_minishell *minishell, char *msg);
void		handle_builtins(t_minishell *minishell, t_bintree *cmd, int i);
void		change_dir(t_minishell *minishell, char *where);
void		do_echo(t_minishell *minishell, t_cmd *cmd, int j);
void		update_pwd(t_minishell *minishell, int pwd);
void		init_env(t_minishell *minishell, char **envp);
void		update_underscore_var(t_minishell *minishell, char **cmd);
void		print_env(t_minishell *minishell);
void		do_exit(t_minishell *minishell, t_cmd *cmd, int i);
void		do_export(t_minishell *minishell, t_cmd *cmd, int j);
void		print_pwd(t_minishell *minishell);
void		do_unset(t_minishell *minishell, t_cmd *cmd, int j);

/*	EXEC FCT	*/
void		exec_all(t_minishell *minishell, t_bintree *tree);
void		handle_join(t_minishell *minishell, t_bintree *tree);
void		handle_and(t_minishell *minishell, t_bintree *tree);
void		handle_or(t_minishell *minishell, t_bintree *tree);
void		handle_pipe(t_minishell *minishell, t_bintree *tree);
int			exec_heredoc(t_minishell *minishell, t_bintree *cmd);
t_bintree	*get_heredoc_content(t_minishell *minishell, t_bintree *tree);
int			ft_isnumber(char *s);
t_cmd		*delete_eof(int index, t_cmd *cmd);

/*	FREE FCT	*/
void		free_cmd(t_cmd *cmd);
void		*free_tree(t_bintree *tree);
void		free_minishell_in_exec(t_minishell *minishell);
void		multi_free(char *s1, char *s2, char *s3, char *s4);

/*	LEXER FCT	*/
t_cmd		*get_heredocs_in_cmd(t_minishell *minishell, t_cmd *cmd);
int			is_quote(char c);
int			has_pipe(char *str);
char		*delete_useless_bracks(t_minishell *minishell, char *input);
char		**lexer_step1(char *input);
char		**lexer_step2(t_minishell *minishell, char **lex);
char		**lexer_step3(t_minishell *minishell, char *input);

/*	INIT FCT	*/
void		init_minishell(t_minishell *minishell, char **envp, int ac, int shell_fd);
t_cmd		*init_cmd(char **lex, int start, int size);
t_bintree	*init_tree(t_cmd *cmd, t_join join, t_type type);

/*	PARSING FCT	*/
char		**delete_empty(char **cmd);
char		**takeoff_quotes(char **cmd);
char		**replace_wildcards(t_minishell *minishell, t_cmd *cmd);
char		**expand_variables(t_minishell *minishell, char **cmd);
t_bintree	*parse(t_minishell *minishell, char ***lex);
t_bintree	*parse_redir(t_minishell *minishell, t_bintree *cmd);

/*	SIGNALS FCT	*/
// void		sig_interactive_mode(void);
// void		sig_execution_mode(void);
// void		sig_heredoc_mode(void);
int			save_terminal(t_minishell *minishell);
int			load_terminal(t_minishell *minishell);

/*	UTILS FCT	*/
int			is_useless_brack(char *input, int i);
void		restore_dup(t_minishell *minishell);
int			do_dup(t_minishell *minishell, int fd_in, int fd_out);
void		safe_close(int fd);
int			get_var_index(char **env, char *var);
char		*get_var_content(char **env, int i, char *varname);
void		update_shell_lvl(t_minishell *minishell, int change);
int			check_error(t_minishell *minishell, t_bintree *cmd, int i);
char		*get_path(t_minishell *minishell, char *cmd);
int			handle_expand(t_minishell *minishell, t_bintree *cmd);
char		*get_varname_expand(char *content);
char		last_char(char *str);
char		*get_expand(t_minishell *minishell, char *varname);
int			already_exists(char *varname, t_minishell *minishell);
void		change_var(t_minishell *minishell, char *var, char *varname);
char		*get_input_heredoc(t_minishell *minishell, char	*eof);
int			check_input(t_minishell *minishell);
int			correct_quotes(t_minishell *minishell, char *input);
char		*delete_newline(char *str);
int			is_join(char *input);
int			is_token_join(char *input);
int			is_two_join(char *input);
t_join		get_join(char *input);
int			is_not_only_join(char *input);
void		handle_str(char c, char *str);
char		*get_till_end_of_word(char *input, int *i);
int			set_closed(char c, int cpt, int *closed);
void		error_msg_set_status(t_minishell *minishell, char *msg, int status);
int			safe_putstr(char *str);
void		error_quit(t_minishell *minishell, char *msg);
int			is_builtin(t_minishell *minishell, char *elem);
// void		write_minishell(char *color);
int			get_nb_tokens(char *input);
void		print_alphabetical_env(t_minishell *minishell);
void		swap_str(char **s1, char **s2);
char		**ft_strstrdup(char **strstr);
char		**strs_insert(char **strs, char *str, int index);
char		**strs_add_free(char **strs, char *str);
t_bintree	*new_node(t_minishell *minishell, t_bintree *left, t_bintree *right,
				t_join join);
t_bintree	*get_next_node(t_minishell *minishell, char ***lex, int *i);
void		append_node_tree(t_bintree **tree, t_bintree **node);
t_bintree	*fix_empty_nodes(t_bintree *tree);
char		**get_files(void);
void		get_input_loop(char	*eof, char **rep, char *end_of_file);
int			has_heredoc(char **strs);
int			count_heredocs(t_bintree *tree);
int	empty_redir(t_minishell *minishell, t_bintree *cmd);


#endif