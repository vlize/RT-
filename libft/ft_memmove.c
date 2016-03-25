/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 09:19:43 by vlize             #+#    #+#             */
/*   Updated: 2014/11/28 17:13:35 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*s1;
	char	*s2;

	i = 0;
	if (!src || !dst)
		return (dst);
	s1 = (char *)dst;
	s2 = ft_strdup((char *)src);
	if (!s2)
		return (dst);
	while (i < len)
	{
		s1[i] = s2[i];
		i++;
	}
	free(s2);
	return (dst);
}
