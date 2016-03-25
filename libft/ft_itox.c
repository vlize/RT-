/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 12:44:57 by vlize             #+#    #+#             */
/*   Updated: 2015/03/02 12:44:59 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itox(uintmax_t n, int cl)
{
	char		*x;
	size_t		l;
	uintmax_t	i;

	l = ft_nbrxlen(n);
	x = (char *)malloc(sizeof(char) * (l + 1));
	if (!x)
		return (NULL);
	x[l] = '\0';
	while (l > 0)
	{
		i = (n % 16);
		if (i < 10)
			x[l - 1] = i + 48;
		else if (cl == 1)
			x[l - 1] = i + 55;
		else
			x[l - 1] = i + 87;
		n = n / 16;
		l--;
	}
	return (x);
}
