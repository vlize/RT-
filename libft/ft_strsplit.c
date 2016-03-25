/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 17:02:04 by vlize             #+#    #+#             */
/*   Updated: 2014/11/28 13:39:02 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	str_nbr(char *s, char c)
{
	size_t	n;
	size_t	i;

	i = 0;
	n = 0;
	while (s[i] == c)
		i++;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			n++;
			while ((s[i] != c) && (s[i] != '\0'))
				i++;
		}
		else
			i++;
	}
	return (n);
}

static size_t	str_len(char *s, char c)
{
	size_t	l;

	l = 0;
	if (!s)
		return (0);
	while ((s[l] != c) && (s[l] != '\0'))
		l++;
	return (l);
}

static char		*split_str(char *tmp, unsigned long l)
{
	size_t	i;
	char	*s;

	i = 0;
	s = (char *)malloc(sizeof(*s) * (l + 1));
	if (!s)
		return (NULL);
	s[l] = '\0';
	while (i < l)
	{
		s[i] = tmp[i];
		i++;
	}
	return (s);
}

static int		make_tab(char *tmp, char c, char **tab, unsigned long n)
{
	size_t	l;
	size_t	i;

	l = 0;
	i = 0;
	while (i < n)
	{
		while (tmp[l] == c)
			l++;
		tmp = &tmp[l];
		l = str_len(tmp, c);
		tab[i] = split_str(tmp, l);
		if (!tab[i])
			return (0);
		i++;
	}
	return (1);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	n;
	char	*tmp[2];
	char	**tab;

	tmp[0] = ft_strdup(s);
	if (!tmp[0])
		return (NULL);
	tmp[1] = tmp[0];
	n = str_nbr(tmp[1], c);
	tab = (char **)malloc(sizeof(char *) * (n + 1));
	if (!tab)
		return (NULL);
	tab[n] = NULL;
	n = make_tab(tmp[1], c, tab, n);
	if (n == 0)
		return (NULL);
	free(tmp[0]);
	return (tab);
}
