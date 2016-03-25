/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 17:23:16 by vlize             #+#    #+#             */
/*   Updated: 2015/03/02 17:23:17 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putwnbr(intmax_t nb)
{
	char		c;
	uintmax_t	n;

	c = 48;
	if (nb < 0)
	{
		ft_putchar('-');
		n = -nb;
	}
	else
		n = nb;
	if (n < 10)
	{
		c += n;
		ft_putchar(c);
	}
	else
	{
		ft_putwnbr(n / 10);
		c += n % 10;
		ft_putchar(c);
	}
}
