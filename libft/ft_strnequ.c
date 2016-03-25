/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/17 16:42:22 by vlize             #+#    #+#             */
/*   Updated: 2014/11/17 16:53:03 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strnequ_null(char *s1, char *s2)
{
	if ((s1) && (!s2))
		free(s1);
	else if ((!s1) && (s2))
		free(s2);
	return (0);
}

int			ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	i;
	char	*tmp[2];

	tmp[0] = ft_strdup((char *)s1);
	tmp[1] = ft_strdup((char *)s2);
	if ((!tmp[0]) || (!tmp[1]))
		return (ft_strnequ_null(tmp[0], tmp[1]));
	i = 0;
	if (ft_strncmp(tmp[0], tmp[1], n) >= 0)
		i++;
	free(tmp[0]);
	free(tmp[1]);
	return (i);
}
