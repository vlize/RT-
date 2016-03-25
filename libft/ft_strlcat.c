/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 16:05:43 by vlize             #+#    #+#             */
/*   Updated: 2014/11/28 17:22:42 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	l1;
	size_t	l2;
	char	*s;

	i = 0;
	if (!dst || !(s = ft_strdup((char *)src)))
		return (0);
	l2 = ft_strlen(s);
	if ((l1 = ft_strlen(dst)) >= size)
		return (size + l2);
	while ((i < l2) && (i < (size - l1 - 1)))
	{
		dst[l1 + i] = s[i];
		i++;
	}
	free(s);
	dst[l1 + i] = '\0';
	return (l1 + l2);
}
