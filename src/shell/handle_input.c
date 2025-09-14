/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:09:48 by gmanique          #+#    #+#             */
/*   Updated: 2025/09/13 21:15:59 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_term.h"

/*	gere les cas des unexpected tokens :, #, !, |& et les joins seuls 	*/
static int	check_unexpected_token(t_minishell *minishell, char *input, int i)
{
	if (minishell->input[i] == ':' || minishell->input[i] == '#')
		return ((minishell->status = 0) + 1);
	else if (minishell->input[i] == '!')
		return (minishell->status = 1);
	else if (input[i] == ';' || input[i] == '\\' || input[i] == '|'
		|| input[i] == '&' || ((minishell->input[i] == '<'
				|| minishell->input[i] == '>')
			&& minishell->input[i] == minishell->input[i + 1]
			&& minishell->input[i] == minishell->input[i + 2]))
	{
		if (input[i] == '|' && input[i + 1] == '&')
			ft_fprintf(2,
				"Minishell: syntax error near unexpected token `%c%c'\n",
				input[i], input[i + 1]);
		else if (!input[i + 1] || input[i + 1] != input[i])
			ft_fprintf(2,
				"Minishell: syntax error near unexpected token `%c'\n",
				input[i]);
		else
			ft_fprintf(2,
				"Minishell: syntax error near unexpected token `%c%c'\n",
				input[i], input[i + 1]);
		return (minishell->status = 2, 1);
	}
	return (0);
}

/* Verifie qu'il n'y a pas d'erreur de recuperation de l'input */
/* Et l'ajoute a l'historique */
int	check_input(t_minishell *minishell)
{
	int	i;

	i = -1;
	if (!minishell->input)
		return (0);
	while (ft_iswhitespace(minishell->input[++i]))
		;
	if (check_unexpected_token(minishell, minishell->input, i))
		return (0);
	return (1);
}



void	do_shell(t_minishell *minishell)
{
	char	**lexed_input;

	dup2(minishell->save_stdout, STDOUT_FILENO);
	dup2(minishell->save_stdout, STDERR_FILENO);
	minishell->input = delete_useless_bracks(minishell, minishell->input);
	if (!minishell->input)
		return ;

	if (!correct_quotes(minishell, minishell->input))
		return ;

	lexed_input = lexer_step1(minishell->input);
	if (!lexed_input)
		return ;

	if (has_heredoc(lexed_input))
		minishell->status = 0;

	minishell->parsed_input = parse(minishell, &lexed_input);
	free_split(lexed_input);

	// sig_heredoc_mode();

	minishell->inc = 0;
	minishell->heredocs = ft_calloc(count_heredocs(minishell->parsed_input) + 1,
			sizeof(char *));

	if (!minishell->heredocs)
		return ;

	minishell->parsed_input = get_heredoc_content(minishell,
			minishell->parsed_input);

	restore_dup(minishell);
	// sig_execution_mode();

	exec_all(minishell, minishell->parsed_input);

	free_split(minishell->heredocs);
	minishell->heredocs = NULL;
	load_terminal(minishell);
	
	free_tree(minishell->parsed_input);
	minishell->parsed_input = NULL;
}