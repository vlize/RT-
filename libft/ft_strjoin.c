/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/18 10:05:22 by vlize             #+#    #+#             */
/*   Updated: 2014/11/28 17:26:06 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	l[2];
	char	*join;
	char	*tmp[2];

	i = 0;
	tmp[0] = (char *)s1;
	tmp[1] = (char *)s2;
	l[0] = ft_strlen(tmp[0]);
	l[1] = ft_strlen(tmp[1]);
	join = (char *)malloc(sizeof(*join) * (l[0] + l[1] + 1));
	if (!join)
		return (NULL);
	while (i < l[0])
	{
		join[i] = tmp[0][i];
		i++;
	}
	while (i < (l[0] + l[1]))
	{
		join[i] = tmp[1][i - l[0]];
		i++;
	}
	join[i] = '\0';
	return (join);
}
