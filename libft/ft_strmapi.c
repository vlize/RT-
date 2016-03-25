/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/17 15:36:03 by vlize             #+#    #+#             */
/*   Updated: 2014/11/24 10:45:03 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
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
		str[i] = f(i, str[i]);
		i++;
	}
	return (str);
}
