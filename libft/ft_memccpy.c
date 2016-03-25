/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 17:33:45 by vlize             #+#    #+#             */
/*   Updated: 2014/11/19 12:17:08 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;
	char	*s1;
	char	*s2;

	i = 0;
	s1 = (char *)dst;
	s2 = (char *)src;
	if (!src || !dst)
		return (dst);
	while (i < n)
	{
		s1[i] = s2[i];
		if (s2[i] == (char)c)
			return ((void *)&(s1[i + 1]));
		i++;
	}
	return (NULL);
}
