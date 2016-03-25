/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 13:02:54 by vlize             #+#    #+#             */
/*   Updated: 2014/11/19 15:06:00 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while ((i < n) && (src[i] != '\0') && (dst[i] != '\0'))
	{
		dst[i] = src[i];
		i++;
	}
	if ((i < n) && (src[i] != '\0'))
		dst[i] = src[i];
	else
	{
		while ((i < n) && (dst[i] != '\0'))
		{
			dst[i] = '\0';
			i++;
		}
	}
	return (dst);
}
