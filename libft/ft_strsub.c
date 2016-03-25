/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/18 09:47:12 by vlize             #+#    #+#             */
/*   Updated: 2014/11/20 09:36:29 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*tmp;
	char	*sub;

	i = 0;
	if (!s)
		return (NULL);
	tmp = (char *)s;
	sub = (char *)malloc(sizeof(*sub) * (len + 1));
	if (!sub)
		return (NULL);
	sub[len] = '\0';
	while (i < len)
	{
		sub[i] = tmp[start + i];
		i++;
	}
	return (sub);
}
