/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:54:52 by gmanique          #+#    #+#             */
/*   Updated: 2025/03/13 01:57:11 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include "get_next_line/get_next_line.h"
# include "ft_printf/ft_printf.h"
# include "ajouts_persos/ajouts.h"

// Partie Mandatory :

/* Retourne 1 si le caractere est alphabetique, 0 sinon. */
int		ft_isalpha(int c);

/* Retourne 1 si le caractere est un nombre, 0 sinon. */
int		ft_isdigit(int c);

/* Retourne 1 si le caractere est alphanumerique, 0 sinon. */
int		ft_isalnum(int c);

/* Retourne 1 si le caractere est ascii, 0 sinon. */
int		ft_isascii(int c);

/* Retourne 1 si le caractere est printable, 0 sinon. */
int		ft_isprint(int c);

/* Renvoie la taille d'une chaine de caractere passee en parametre. */
int		ft_strlen(char const *str);

/* Permet de remplir une zone mémoire, identifiée par son adresse */
/* et sa taille, avec une valeur précise. */
void	*ft_memset(void *s, int c, size_t n);

/* Permet de remplir une zone mémoire, identifiée par son adresse et */
/* sa taille, avec des 0. */
void	ft_bzero(void *s, size_t n);

/* Copie un bloc de mémoire spécifié par le paramètre source, */
/* et dont la taille est spécifiée via le paramètre size, */
/* dans un nouvel emplacement désigné par le paramètre */
/* destination. */
void	*ft_memcpy(void *dest, const void *src, size_t size);

/* Copie un bloc de mémoire spécifié par le paramètre source, */
/* et dont la taille est spécifiée via le paramètre size, */
/* dans un nouvel emplacement désigné par le paramètre */
/* destination a condition que les deux emplacements ne */
/* se chevauchent pas. */
void	*ft_memmove(void *dest, const void *src, size_t size);

/* Copie une chaine de caractere et renvoie la taille de la dite chaine */
int		ft_strlcpy(char *s1, const char *s2, size_t size);

/* Concatene 2 chaines de caracteres et renvoie la taille */
/* de la nouvelle chaine. */
int		ft_strlcat(char *s1, const char *s2, size_t n);

/* Transforme un caractere minuscule en majuscule si c'est une */
/* lettre, ne fais rien sinon */
int		ft_toupper(int c);

/* Transforme un caractere majuscule en minuscule si c'est une */
/* lettre, ne fais rien sinon */
int		ft_tolower(int c);

/* Renvoie un pointeur sur la premiere apparition du caractere */
/* recherche, NULL sinon */
char	*ft_strchr(const char *s, int c);

/* Renvoie un pointeur sur la derniere apparition du caractere */
/* recherche, NULL sinon */
char	*ft_strrchr(const char *s, int c);

/* Compare 2 chaines de caracteres sur la longueur */
/* passee en parametre et renvoie la difference */
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/* Eamine les n premiers octets de la zone mémoire */
/* pointée par s à la recherche du caractère c */
/* et renvoie la premiere occurence de ce caractere, ou NULL. */
void	*ft_memchr(const void *memoryBlock, int searchedChar, size_t size);

/* Compare le contenu de deux blocs de mémoire spécifiés */
/* par les deux premiers paramètres de la fonction. */
/* Le troisième paramètre, size, permet de spécifier */
/* le nombre d'octets sur lequel comparer les deux blocs. */
int		ft_memcmp(const void *p1, const void *p2, size_t size);

/* Renvoie un pointeur sur la premiere apparition de la chaine s2 */
/* dans s1, NULL sinon */
char	*ft_strnstr(const char *s1, const char *s2, size_t n);

/* Transforme une chaine de caractere passee en parametre en int */
int		ft_atoi(const char *str);

/* Alloue la place demandee et l'initialise integralement a 0 */
void	*ft_calloc(size_t elementCount, size_t elementSize);

/* Alloue une copie de la chaine de caractere passee en parametre */
/* et la renvoie */
char	*ft_strdup(char *src);

/* Renvoie une partie de la chaine de caractere passee en parametre, */
/* a partir du caractere a l'emplacement start et de longueur len */
char	*ft_substr(char const *s, unsigned int start, size_t len);

/* Alloue une chaine de caractere etant la */
/* concatenation des 2 chaines passees en parametre */
char	*ft_strjoin(char const *s1, char const *s2);

/* Alloue et retourne une copie de */
/* la chaîne ’s1’, sans les caractères spécifiés */
/* dans ’set’ au début et à la fin de la chaîne de */
/* caractères. */
char	*ft_strtrim(char const *s1, char const *set);

/* Renvoie une chaine de chaines de caracteres, */
/* contenant toutes les parties decoupees de la */
/* chaine passee en parametre par rapport au */
/* caractere passe en parametre. */
char	**ft_split(char const *s, char c);

/* Transforme un entier passe en parametre en chaine */
/* de caractere et la renvoie, alloue de l'espace */
char	*ft_itoa(int val);

/* Applique la fonction ’f’ à chaque caractère de */
/* la chaîne de caractères ’s’, passant son index */
/* comme premier argument et le caractère lui-même */
/* comme second argument. Une nouvelle chaîne de */
/* caractères est créée (avec malloc(3)), résultant */
/* des applications successives de ’f’. */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/* Applique la fonction ’f’ à chaque caractère de la */
/* chaîne de caractères transmise comme argument, */
/* et en passant son index comme premier argument. */
/* Chaque caractère est transmis par adresse à ’f’ */
/* afin d’être modifié si nécessaire. */
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

/* Ecrit le caractere demande dans le fd demande */
void	ft_putchar_fd(char c, int fd);

/* Ecrit la chaine de caracteres demandee dans le fd demande */
void	ft_putstr_fd(char *s, int fd);

/* Ecrit la chaine de caracteres demandee avec un NewLine dans le fd demande */
void	ft_putendl_fd(char *s, int fd);

/* Ecrit l'entier demande dans le fd demande */
void	ft_putnbr_fd(int n, int fd);

// Partie Bonus :

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/* Permet de creer une nouvelle liste. */
t_list	*ft_lstnew(void *content);

/* Ajoute une liste au devant de la premiere liste. */
void	ft_lstadd_front(t_list **lst, t_list *new);

/* Renvoie la taille d'une liste. */
int		ft_lstsize(t_list *lst);

/* Renvoie le dernier element d'une liste. */
t_list	*ft_lstlast(t_list *lst);

/* Ajoute une liste a l'arriere de la premiere liste. */
void	ft_lstadd_back(t_list **lst, t_list *new);

/* Retire un element de la liste grace a la fonction passee en parametre. */
void	ft_lstdelone(t_list *lst, void (*del)(void *));

/* Clear une liste grace a la fonction passee en parametre. */
void	ft_lstclear(t_list **lst, void (*del)(void *));

/* Applique la fonction ’f’ à chaque element de la */
/* liste transmise comme argument. */
void	ft_lstiter(t_list *lst, void (*f)(void *));

/* Applique la fonction ’f’ à chaque element de la */
/* liste transmise comme argument et renvoie la nouvelle */
/* liste cree. */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
