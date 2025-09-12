/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amados-s <amados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:59:31 by gmanique          #+#    #+#             */
/*   Updated: 2025/06/24 11:06:55 by amados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cpt_words(const char *s, char c)
{
	int	i;
	int	cpt;

	cpt = 0;
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		cpt++;
		while (s[i] && s[i] != c)
			i++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (cpt);
}

static int	word_len(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	free_all(char **str, int word)
{
	while (word > 0)
	{
		free(str[word - 1]);
		word--;
	}
	free(str);
}

static char	**mal_all(char const *s, char c, int letter, int i)
{
	char	**mall;

	mall = malloc((cpt_words(s, c) + 1) * sizeof(char *));
	if (mall == NULL)
		return (NULL);
	while (s[letter] && s[letter] == c)
		letter++;
	while (letter < ft_strlen(s) && s[letter] && i < cpt_words(s, c))
	{
		mall[i] = malloc((word_len(&s[letter], c) + 1) * sizeof(char));
		if (mall[i] == NULL)
			return (free_all(mall, i), NULL);
		i++;
		letter += word_len(&s[letter], c);
		while (letter < ft_strlen(s) && s[letter] == c)
			letter++;
	}
	return (mall);
}

char	**ft_split(char const *s, char c)
{
	char	**rep;
	int		word;
	int		i;

	word = 0;
	i = 0;
	if (!s)
		return (NULL);
	rep = mal_all(s, c, i, word);
	if (rep == NULL)
		return (NULL);
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && word < cpt_words(s, c))
	{
		ft_strlcpy(rep[word], &s[i], word_len(&s[i], c) + 1);
		i += word_len(&s[i], c);
		while (i < ft_strlen(s) && s[i] == c)
			i++;
		word++;
	}
	rep[word] = NULL;
	return (rep);
}
