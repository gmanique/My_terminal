/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:17:24 by gmanique          #+#    #+#             */
/*   Updated: 2025/09/13 18:59:38 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_term.h"

static int	handle_after_exec(t_minishell *minishell, t_bintree *cmd, int i)
{
	if (WIFEXITED(minishell->status))
	{
		minishell->status = WEXITSTATUS(minishell->status);
		if (minishell->status != 0)
			minishell->status = check_error(minishell, cmd, i);
	}
	else if (WIFSIGNALED(minishell->status)
		&& WTERMSIG(minishell->status) == SIGSEGV)
	{
		ft_fprintf(2, "Segmentation fault (core dumped)\n");
		minishell->status = 128 + SIGSEGV;
	}
	else if (WIFSIGNALED(minishell->status))
		minishell->status = 128 + g_sig;
	return (0);
}

static int	my_exec_core(t_minishell *minishell, t_bintree *cmd, int i)
{
	char	*command;
	char	**tmp;

	command = get_path(minishell, cmd->cmd->cmd[i]);
	tmp = ft_strstrdup(&cmd->cmd->cmd[i]);
	if (!tmp)
		return (free_tree(minishell->parsed_input), free(command), 1);
	free_tree(minishell->parsed_input);
	minishell->parsed_input = NULL;
	safe_close(minishell->save_stdin);
	safe_close(minishell->save_stdout);
	if (!command)
	{
		execve(tmp[0], tmp, minishell->env);
		free_split(tmp);
		tmp = NULL;
		free_minishell_in_exec(minishell);
		minishell = NULL;
		exit(126);
	}
	execve(command, tmp, minishell->env);
	free(command);
	command = NULL;
	execve(tmp[0], tmp, minishell->env);
	return (free_split(tmp), tmp = NULL, 1);
}

static int	my_exec(t_minishell *minishell, t_bintree *cmd, int i)
{
	pid_t	pid;

	update_shell_lvl(minishell, 1);
	pid = fork();
	if (pid == -1)
		error_quit(minishell, "Fork failure.\n");
	if (pid == 0)
	{
		if (do_dup(minishell, cmd->fd_in, cmd->fd_out) == ERROR)
			return (ERROR);
		my_exec_core(minishell, cmd, i);
		free_minishell_in_exec(minishell);
		minishell = NULL;
		exit(127);
	}
	safe_close(cmd->fd_in);
	safe_close(cmd->fd_out);
	restore_dup(minishell);
	waitpid(pid, &minishell->status, 0);
	update_shell_lvl(minishell, -1);
	return (handle_after_exec(minishell, cmd, i));
}

static void	exec_one(t_minishell *minishell, t_bintree *cmd)
{
	cmd = parse_redir(minishell, cmd);
	if (!cmd || !handle_expand(minishell, cmd))
		return ;
	if (!cmd->cmd->cmd || !cmd->cmd->cmd[0])
	{
		minishell->status = 0;
		if (cmd && cmd->cmd && cmd->cmd->cmd)
		{
			free_split(cmd->cmd->cmd);
			cmd->cmd->cmd = NULL;
		}
		return ;
	}
	if (cmd->cmd->heredoc != -1)
	{
		exec_heredoc(minishell, cmd);
		return ;
	}
	if (is_builtin(minishell, cmd->cmd->cmd[0]))
		handle_builtins(minishell, cmd, 0);
	else if (cmd->cmd->cmd[0])
		my_exec(minishell, cmd, 0);
	update_underscore_var(minishell, cmd->cmd->cmd);
}


static int	is_closed(int fd)
{
	if ((read(fd, NULL, 0) == -1 && write(fd, "", 0) == -1))
		return (1);
	return (0);
}

/* Permet de close un fd si il est superieur a 2 && pas deja close */
void	safe_close(int fd)
{
	if (fd > 2 && !is_closed(fd))
		close(fd);
}

int	do_dup(t_minishell *minishell, int fd_in, int fd_out)
{
	if (fd_in > 2 && dup2(fd_in, STDIN_FILENO) == -1)
	{
		safe_close(fd_in);
		safe_close(fd_out);
		return (ERROR);
	}
	if (fd_out > 2 && dup2(fd_out, STDOUT_FILENO) == -1)
	{
		safe_close(fd_in);
		safe_close(fd_out);
		return (restore_dup(minishell), ERROR);
	}
	safe_close(fd_in);
	safe_close(fd_out);
	return (0);
}


static void	do_left_pipe(t_minishell *minishell, t_bintree *tree, int *pid)
{
	int	status;

	*pid = fork();
	if (*pid == -1)
		error_quit(minishell, "Error while making pipe.\n");
	if (*pid == 0)
	{
		if ((tree && tree->l_branch && tree->l_branch->cmd
				&& tree->l_branch->cmd->cmd && !is_builtin(minishell,
					tree->l_branch->cmd->cmd[0])) || !(tree && tree->l_branch
				&& tree->l_branch->cmd && tree->l_branch->cmd->cmd))
			safe_close(tree->r_branch->fd_in);
		exec_all(minishell, tree->l_branch);
		safe_close(tree->r_branch->fd_in);
		safe_close(tree->l_branch->fd_out);
		status = minishell->status;
		exit(status);
	}
}

static void	do_right_pipe(t_minishell *minishell, t_bintree *tree, int *pid)
{
	int	status;

	*pid = fork();
	if (*pid == -1)
		error_quit(minishell, "Error while making the fork.\n");
	if (*pid == 0)
	{
		if ((tree && tree->r_branch && tree->r_branch->cmd
				&& tree->r_branch->cmd->cmd && !is_builtin(minishell,
					tree->r_branch->cmd->cmd[0])) || !(tree && tree->r_branch
				&& tree->r_branch->cmd && tree->r_branch->cmd->cmd))
			safe_close(tree->l_branch->fd_out);
		safe_close(minishell->save_stdin);
		exec_all(minishell, tree->r_branch);
		safe_close(tree->l_branch->fd_out);
		safe_close(tree->r_branch->fd_in);
		status = minishell->status;
		exit(status);
	}
}


static int	get_heredocs_in_cmd_helper(t_minishell *minishell, t_cmd *cmd,
		int i)
{
	if (!cmd->cmd[i + 1])
		return (error_msg_set_status(minishell,
				"Minishell: syntax error near unexpected token `newline'\n", 2),
			free_cmd(cmd), 1);
	if (cmd->cmd[i + 1][0] == '<' || cmd->cmd[i + 1][0] == '>')
		return (ft_fprintf(2,
				"Minishell: syntax error near unexpected token `%s'\n",
				cmd->cmd[i + 1]), minishell->status = 2, free_cmd(cmd), 1);
	minishell->heredocs[minishell->inc] = get_input_heredoc(minishell,
			cmd->cmd[i + 1]);
	if (minishell->heredocs[minishell->inc] == NULL)
		return (free_cmd(cmd), 1);
	cmd->cmd[i] = free_join(cmd->cmd[i], ft_itoa(minishell->inc), 3);
	if (!cmd->cmd[i])
		error_quit(minishell, "Malloc failure.\n");
	minishell->inc++;
	cmd = delete_eof(i + 1, cmd);
	return (0);
}

t_cmd	*get_heredocs_in_cmd(t_minishell *minishell, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[i])
	{
		if (cmd->cmd[i][0] == '<' && cmd->cmd[i][1] == '<' && !cmd->cmd[i][2])
		{
			if (get_heredocs_in_cmd_helper(minishell, cmd, i))
				return (NULL);
		}
		i++;
	}
	return (cmd);
}


/*	gere l'exec pour le join |	*/
void	handle_pipe(t_minishell *minishell, t_bintree *tree)
{
	int		fd[2];
	pid_t	pid[2];

	if (!tree->l_branch || !tree->r_branch)
		return (error_msg_set_status(minishell,
				"Minishell: syntax error near unexpected token `|'\n", 2));
	if (pipe(fd) == -1)
		error_quit(minishell, "Error while making pipe.\n");
	if (tree->l_branch->type == type_join && (tree->l_branch->join == r_redirect
			|| tree->l_branch->join == r_redirect2))
		safe_close(fd[1]);
	else
		tree->l_branch->fd_out = fd[1];
	tree->r_branch->fd_in = fd[0];
	do_left_pipe(minishell, tree, &pid[1]);
	do_right_pipe(minishell, tree, &pid[0]);
	safe_close(tree->l_branch->fd_out);
	safe_close(tree->r_branch->fd_in);
	waitpid(pid[1], &minishell->status, 0);
	waitpid(pid[0], &minishell->status, 0);
	if (WIFEXITED(minishell->status))
		minishell->status = WEXITSTATUS(minishell->status);
}


int	has_pipe(char *str)
{
	char	str_dep;
	int		par_dep;
	int		i;

	i = 0;
	str_dep = 0;
	par_dep = 0;
	while (str && str[i])
	{
		if (is_quote(str[i]))
			handle_str(str[i], &str_dep);
		if (!str_dep && str[i] == '(')
			par_dep += 1;
		if (!str_dep && str[i] == ')')
			par_dep -= 1;
		if (!str_dep && par_dep == 0 && str[i] == '|' && str[i + 1] != '|'
			&& (i == 0 || str[i - 1] != '|'))
			return (1);
		i++;
	}
	return (0);
}

/*	gere l'exec pour le join &&	*/
void	handle_and(t_minishell *minishell, t_bintree *tree)
{
	if (!tree->l_branch || !tree->r_branch)
		return (error_msg_set_status(minishell,
				"Minishell: syntax error near unexpected token `&&'\n", 2));
	exec_all(minishell, tree->l_branch);
	if (minishell->status == 0)
		exec_all(minishell, tree->r_branch);
}

/*	gere l'exec pour le join ||	*/
void	handle_or(t_minishell *minishell, t_bintree *tree)
{
	if (!tree->l_branch || !tree->r_branch)
		return (error_msg_set_status(minishell,
				"Minishell: syntax error near unexpected token `||'\n", 2));
	exec_all(minishell, tree->l_branch);
	if (minishell->status != 0)
		exec_all(minishell, tree->r_branch);
}


void	handle_join(t_minishell *minishell, t_bintree *tree)
{
	if (tree->fd_in != -1 || tree->fd_out != -1)
		do_dup(minishell, tree->fd_in, tree->fd_out);
	if (tree->join == pipex)
		handle_pipe(minishell, tree);
	else if (tree->join == and)
		handle_and(minishell, tree);
	else if (tree->join == or)
		handle_or(minishell, tree);
	restore_dup(minishell);
}


int	exec_heredoc(t_minishell *minishell, t_bintree *cmd)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (ft_fprintf(2, "Minishell: Failure making the pipe.\n"));
	ft_fprintf(fd[1], "%s", minishell->heredocs[cmd->cmd->heredoc]);
	cmd->fd_in = fd[0];
	safe_close(fd[1]);
	exec_all(minishell, cmd);
	safe_close(fd[0]);
	return (0);
}


void	exec_all(t_minishell *minishell, t_bintree *tree)
{
	if (!tree)
		return ;
	if (tree->type == type_join)
	{
		if (tree->join == none && tree->l_branch)
			exec_all(minishell, tree->l_branch);
		else if (tree->join != none)
			handle_join(minishell, tree);
	}
	else
		exec_one(minishell, tree);
}