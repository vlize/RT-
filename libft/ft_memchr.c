/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 10:46:51 by vlize             #+#    #+#             */
/*   Updated: 2014/11/15 12:48:02 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if (!s)
		return (NULL);
	tmp = (char *)s;
	while (i < n)
	{
		if (tmp[i] == (char)c)
			return ((void *)&tmp[i]);
		i++;
	}
	return (NULL);
}
