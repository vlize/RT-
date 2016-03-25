/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/08 10:03:34 by vlize             #+#    #+#             */
/*   Updated: 2015/06/08 10:04:01 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_sqrt(double x)
{
	double	tmp;
	double	rt;
	double	s;
	size_t	i;

	if (x == -0)
		return (-0);
	else if (x < 0)
		return (x / 0);
	tmp = 1;
	rt = 0;
	i = 0;
	while ((rt != tmp) && (i < 1000))
	{
		rt = tmp;
		s = (x - (tmp * tmp)) / (2 * tmp);
		tmp += s;
		i++;
	}
	return (rt);
}
