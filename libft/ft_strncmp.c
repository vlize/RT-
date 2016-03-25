/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 14:56:56 by vlize             #+#    #+#             */
/*   Updated: 2014/11/15 12:33:29 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	char	*t1;
	char	*t2;

	i = 0;
	t1 = (char *)s1;
	t2 = (char *)s2;
	if (!s1 && !s2 && !n)
		return (0);
	if (!s1 && s2)
		return (-(t2[0]));
	if (s1 && !s2)
		return (t1[0]);
	while ((t1[i] != '\0') && (t2[i] != '\0') && (i < n))
	{
		if (t1[i] != t2[i])
			return (t1[i] - t2[i]);
		i++;
	}
	if (i < n)
		return (t1[i] - t2[i]);
	return (0);
}
