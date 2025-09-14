/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 21:21:54 by gmanique          #+#    #+#             */
/*   Updated: 2025/09/13 23:36:55 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_term.h"

t_mylist	*init_list(char	*input, char *output)
{
	t_mylist	*list;

	list = malloc(sizeof(t_mylist));
	if (!list)
		return (NULL);
	list->input = input;
	list->output = output;
	list->next = NULL;
	return (list);
}

t_mylist	*add_back(t_mylist *list, char *input, char *output)
{
	if (list == NULL)
		return (init_list(input, output));
	list->next = init_list(input, output);
	return (list);
}

t_mylist	*add_front(t_mylist *list, char *input, char *output)
{
	t_mylist	*rep = init_list(input, output);
	rep->next = list;
	return (rep);
}

int	nb_lines(char *s)
{
	int	i = 0;
	int	cpt = 1;
	
	if (!s)
		return (0);
	while(s && s[i])
	{
		if (s[i] == '\n')
			cpt++;
		i++;
	}
	return (cpt);
}

int	cpt_lines(t_mylist	*list)
{
	t_mylist	*tmp = list;
	int	cpt;
	
	cpt = 1;
	while(tmp)
	{
		if (tmp->input)
			cpt += nb_lines(tmp->input);
		if (tmp->output)
			cpt += nb_lines(tmp->output);
		cpt++;
		tmp = tmp->next;
	}
	return (cpt);
}