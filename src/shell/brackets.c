/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:42:29 by gmanique          #+#    #+#             */
/*   Updated: 2025/09/13 17:43:39 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_term.h"

/* Permet de changer le caractere passe en parametre */
/* pour savoir si on est dans une str ou non */
/* (utile pour le parsing) */
void	handle_str(char c, char *str)
{
	if (*str == c)
		*str = '\0';
	else if (*str == '\0')
		*str = c;
}


static int	count_brackets(char *input, int j)
{
	int	cpt;

	cpt = 0;
	while (input[j])
	{
		while (ft_iswhitespace(input[j]))
			j++;
		if (input[j] == '(')
			cpt++;
		else if (input[j] == ')')
			cpt--;
		if (cpt < 0)
			return (0);
		else
			break ;
	}
	return (1);
}

static int	no_empty_brackets(char *input)
{
	int		i;
	char	str;

	i = -1;
	str = '\0';
	while (input[++i])
	{
		if (input[i] == '\"' || input[i] == '\'')
			handle_str(input[i], &str);
		else if (!str && input[i] == '(' && count_brackets(input, i + 1) == 0)
			return (0);
	}
	return (1);
}

static int	is_correct_brack(char *input, int *closed)
{
	int		i;
	int		cpt;
	char	str;

	i = 0;
	cpt = 0;
	*closed = 0;
	str = '\0';
	if (!input)
		return (1);
	while (input[i])
	{
		if (input[i] == '\"' || input[i] == '\'')
			handle_str(input[i], &str);
		else if ((input[i] == '(' || input[i] == ')') && str == '\0')
			cpt = set_closed(input[i], cpt, closed);
		if (cpt < 0)
			break ;
		i++;
	}
	return (cpt == 0 && no_empty_brackets(input));
}

static int	get_closed_brack_index(char *input, int i)
{
	int		cpt;
	char	str;

	cpt = 1;
	str = '\0';
	i++;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			handle_str(input[i], &str);
		else if (!str && input[i] == '(')
			cpt++;
		else if (!str && input[i] == ')')
			cpt--;
		if (cpt == 0)
			return (i);
		i++;
	}
	return (-1);
}

/* Permet de supprimer les brackets inutiles/en trop */
char	*delete_useless_bracks(t_minishell *minishell, char *input)
{
	int		i;
	char	str;
	int		closed;

	if (!is_correct_brack(input, &closed))
		return (minishell->status = 2, ft_fprintf(2,
				"Minishell: syntax error near unexpected token `%c'\n", '('
				+ closed), free(input), input = NULL, NULL);
	i = 0;
	str = '\0';
	while (input[i])
	{
		if (input[i] != '(' || str != '\0' || !is_useless_brack(input, i))
		{
			if (input[i] == '\"' || input[i] == '\'')
				handle_str(input[i], &str);
		}
		else
		{
			input[i] = ' ';
			input[get_closed_brack_index(input, i)] = ' ';
		}
		i++;
	}
	return (input);
}