/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:45:40 by gmanique          #+#    #+#             */
/*   Updated: 2025/09/13 17:46:00 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_term.h"


/* Permet de free une commande passee en parametre. */
void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	i = -1;
	if (cmd->cmd)
	{
		while (cmd->cmd[++i])
		{
			free(cmd->cmd[i]);
			cmd->cmd[i] = NULL;
		}
		free(cmd->cmd);
		cmd->cmd = NULL;
	}
	free(cmd);
	cmd = NULL;
}

/* Permet de free entierement un arbre binaire passe en parametres. */
void	*free_tree(t_bintree *tree)
{
	if (!tree)
		return (NULL);
	if (tree->l_branch)
	{
		free_tree(tree->l_branch);
		tree->l_branch = NULL;
	}
	if (tree->r_branch)
	{
		free_tree(tree->r_branch);
		tree->r_branch = NULL;
	}
	if (tree->cmd)
	{
		free_cmd(tree->cmd);
		tree->cmd = NULL;
	}
	free(tree);
	tree = NULL;
	return (NULL);
}

void	free_minishell_in_exec(t_minishell *minishell)
{
	if (minishell->gnl)
		get_next_line(-1);
	if (minishell->termios_p)
		free(minishell->termios_p);
	free_split(minishell->heredocs);
	minishell->heredocs = NULL;
	free_split(minishell->builtins);
	minishell->builtins = NULL;
	free_split(minishell->env);
	minishell->env = NULL;
	safe_close(minishell->save_stdin);
	safe_close(minishell->save_stdout);
}

void	multi_free(char *s1, char *s2, char *s3, char *s4)
{
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	if (s2)
	{
		free(s2);
		s2 = NULL;
	}
	if (s3)
	{
		free(s3);
		s3 = NULL;
	}
	if (s4)
	{
		free(s4);
		s4 = NULL;
	}
}