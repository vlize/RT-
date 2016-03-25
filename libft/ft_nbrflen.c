/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrflen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/21 11:08:40 by vlize             #+#    #+#             */
/*   Updated: 2015/03/21 11:08:42 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_floatlen(size_t *l, double long f)
{
	int	i;

	while (f != 0)
	{
		f *= 10;
		i = f;
		f = f - i;
		l[0]++;
	}
}

void		ft_nbrflen(double long f, size_t *l)
{
	uintmax_t	u;
	int			i;

	i = 1;
	l[0] = 0;
	l[1] = 1;
	if (f < 0)
	{
		i = -1;
		l[1]++;
	}
	u = (double long)(f * i);
	ft_floatlen(l, (f - ((double long)u * i)));
	while ((f >= 10) || (f <= -10))
	{
		f /= 10;
		l[1]++;
	}
}
