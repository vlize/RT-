/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/17 14:47:10 by vlize             #+#    #+#             */
/*   Updated: 2014/11/24 10:43:52 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	size_t	l;
	char	*str;

	i = 0;
	l = ft_strlen(s);
	str = (char *)malloc(sizeof(*str) * (l + 1));
	if (!str)
		return (NULL);
	str[l] = '\0';
	while (i < l)
	{
		str[i] = (char)s[i];
		str[i] = f(str[i]);
		i++;
	}
	return (str);
}
