/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 14:40:19 by vlize             #+#    #+#             */
/*   Updated: 2014/11/15 12:52:27 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if ((!s2) || (!s1))
		return (NULL);
	if (s2[0] == '\0')
		return ((char *)s1);
	while ((s1[i] != '\0') && (i < n))
	{
		j = 0;
		if (s2[j] == s1[i])
		{
			while ((i + j < n) && (s2[j] != '\0') && (s2[j] == s1[i + j]))
				j++;
			if (s2[j] == '\0')
				return ((char *)&(s1[i]));
			if (i + j == n)
				return (NULL);
		}
		i++;
	}
	return (NULL);
}
