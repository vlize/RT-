/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xtoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 15:52:17 by vlize             #+#    #+#             */
/*   Updated: 2015/11/03 15:52:18 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

intmax_t	ft_xtoi(char *x)
{
	intmax_t	n;
	int			i;

	if (!ft_ishexa(x[0]))
		return (-1);
	n = 0;
	i = -1;
	while (ft_ishexa(x[i += 1]))
	{
		n *= 16;
		if (ft_isdigit(x[i]))
			n += x[i] - 48;
		else if ((x[i] >= 'A') && (x[i] <= 'F'))
			n += x[i] - 55;
		else
			n += x[i] - 87;
	}
	return (n);
}
