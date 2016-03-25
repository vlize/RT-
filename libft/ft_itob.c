/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/21 09:56:00 by vlize             #+#    #+#             */
/*   Updated: 2015/03/21 09:56:02 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itob(uintmax_t n)
{
	char		*b;
	size_t		l;
	uintmax_t	i;

	l = ft_nbrblen(n);
	b = (char *)malloc(sizeof(char) * (l + 1));
	if (!b)
		return (NULL);
	b[l] = '\0';
	while (l > 0)
	{
		i = (n % 2);
		b[l - 1] = i + 48;
		n = n / 2;
		l--;
	}
	return (b);
}
