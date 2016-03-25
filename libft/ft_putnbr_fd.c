/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 13:30:30 by vlize             #+#    #+#             */
/*   Updated: 2014/11/28 17:24:01 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	char	c;

	c = 48;
	if ((nb < 0) && (nb > -2147483648))
	{
		ft_putchar_fd('-', fd);
		nb = -nb;
	}
	else if (nb == -2147483648)
		return (ft_putstr_fd("-2147483648", fd));
	if (nb < 10)
	{
		c += nb;
		ft_putchar_fd(c, fd);
	}
	else
	{
		ft_putnbr_fd((nb / 10), fd);
		c += nb % 10;
		ft_putchar_fd(c, fd);
	}
}
