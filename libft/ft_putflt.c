/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putflt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 11:07:11 by vlize             #+#    #+#             */
/*   Updated: 2015/06/05 11:07:58 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	ft_putflt_round(double flt, size_t *precision)
{
	double		r;
	double		i;
	size_t		l;
	uintmax_t	n;

	n = (uintmax_t)flt;
	l = ft_nbrulen(n);
	if ((n != 0) && ((*precision - l) > 16))
		*precision = 16 - l;
	else if (*precision > 16)
		*precision = 16;
	if ((*precision == 16) || (flt == n))
		return (flt);
	r = 0.5;
	i = *precision;
	while (i > 0)
	{
		r /= 10;
		i--;
	}
	return (flt + r);
}

static void		ft_putflt_write(uintmax_t n, size_t *i, int *pt)
{
	if (n != 0)
	{
		if (*pt == 0)
		{
			ft_putchar('.');
			(*pt) += 1;
		}
		while (*i != 0)
		{
			ft_putchar('0');
			(*i)--;
		}
		n += 48;
		write(1, &n, 1);
	}
	else
		(*i)++;
}

void			ft_putflt(double flt, size_t precision)
{
	uintmax_t	n;
	size_t		i;
	int			pt;

	if ((flt < 0) && (flt = 0 - flt))
		ft_putchar('-');
	flt = ft_putflt_round(flt, &precision);
	ft_putunbr((n = (uintmax_t)flt));
	if (((flt -= n) == 0) || (precision == 0))
		return ;
	i = 0;
	pt = 0;
	while ((flt != 0) && (precision > 0))
	{
		flt *= 10;
		n = (uintmax_t)flt;
		ft_putflt_write(n, &i, &pt);
		flt -= n;
		precision--;
	}
}
