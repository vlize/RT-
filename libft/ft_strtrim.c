/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/18 10:29:11 by vlize             #+#    #+#             */
/*   Updated: 2014/11/21 12:47:41 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_no_str(char *s)
{
	s = (char *)malloc(sizeof(char) * 1);
	if (!s)
		return (NULL);
	s[0] = '\0';
	return (s);
}

char		*ft_strtrim(char const *s)
{
	char	*p[2];
	size_t	i[2];

	i[0] = 0;
	if (!s)
		return (NULL);
	p[0] = (char *)s;
	i[1] = ft_strlen(p[0]);
	while ((ft_isspace(p[0][i[0]]) == 1) && (i[0] < i[1]))
		i[0]++;
	if (i[0] == i[1])
		return (ft_no_str(p[1]));
	while ((ft_isspace(p[0][i[1] - 1]) == 1) && (i[0] < (i[1] - 1)))
		i[1]--;
	i[1] = i[1] - i[0];
	p[1] = (char *)malloc(sizeof(char) * (i[1] + 1));
	if (!p[1])
		return (NULL);
	p[1][i[1]] = '\0';
	while (i[1] > 0)
	{
		p[1][i[1] - 1] = p[0][i[0] + i[1] - 1];
		i[1]--;
	}
	return (p[1]);
}
