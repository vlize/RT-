/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 13:36:10 by vlize             #+#    #+#             */
/*   Updated: 2015/03/04 13:36:11 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoo(uintmax_t n)
{
	char		*o;
	size_t		l;
	uintmax_t	i;

	l = ft_nbrolen(n);
	o = (char *)malloc(sizeof(char) * (l + 1));
	if (!o)
		return (NULL);
	o[l] = '\0';
	while (l > 0)
	{
		i = (n % 8);
		o[l - 1] = i + 48;
		n = n / 8;
		l--;
	}
	return (o);
}
