/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 11:35:47 by vlize             #+#    #+#             */
/*   Updated: 2014/11/28 17:17:24 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char const *s1)
{
	size_t	l;
	char	*s2;
	char	*tmp;

	if (!s1)
		return (NULL);
	tmp = (char *)s1;
	l = ft_strlen(tmp);
	s2 = (char *)malloc(sizeof(*s2) * (l + 1));
	if (!s2)
		return (NULL);
	s2[l] = '\0';
	while (l > 0)
	{
		s2[l - 1] = tmp[l - 1];
		l--;
	}
	return (s2);
}
