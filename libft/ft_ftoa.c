/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/21 10:56:59 by vlize             #+#    #+#             */
/*   Updated: 2015/03/21 10:57:01 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_ftoa_move(char *str, size_t i)
{
	while (i > 0)
	{
		str[i] = str[i - 1];
		i--;
	}
	if (str[i] == '-')
		str[i + 1] = '1';
	else
		str[i] = '1';
	return (str);
}

static char	*ft_ftoa_prec(char *str, size_t i, size_t *l)
{
	while ((i > 0) && (str[i] == '9') && (str[i] != '-'))
	{
		str[i] = '0';
		i--;
		if (str[i] == '.')
			i--;
	}
	if ((str[i] == '9') || (str[i] == '-'))
	{
		l[1]++;
		if (str[i] == '9')
			str[i] = '0';
		return (ft_ftoa_move(str, (l[1] + l[3])));
	}
	else
		str[i]++;
	return (str);
}

static char	*ft_ftoa_float(char *str, size_t *l, int *i, double long n)
{
	size_t		j;
	uintmax_t	u;

	j = 1;
	str[l[1]] = '.';
	while (j < l[0])
	{
		u = (double long)(n * i[0]);
		n = n - ((double long)u * i[0]);
		str[j + l[1]] = ((int)(n * 10) * i[0]) + 48;
		n *= 10;
		j++;
	}
	if ((l[3] < l[0]) && (l[3] > 0) && (i[1] == 1) && (str[l[3] + l[1]] > '4'))
		str = ft_ftoa_prec(str, (l[1] + l[3] - 1), l);
	j = l[1] + l[3];
	while (str[j - 1] == '0')
		j--;
	if (str[j - 1] == '.')
		j--;
	str[j] = '\0';
	return (str);
}

static char	*ft_ftoa_dec(char *str, size_t *l, int *i, double long n)
{
	uintmax_t	u;
	size_t		j;

	j = l[1];
	u = (double long)(n * i[0]);
	while (j > l[2])
	{
		str[j - 1] = u % 10 + 48;
		u /= 10;
		j--;
	}
	return (str);
}

char		*ft_ftoa(double long n, size_t p, int r)
{
	size_t	l[4];
	int		i[2];
	char	*str;

	l[2] = 0;
	l[3] = p;
	if (p > 0)
		l[3]++;
	i[0] = 1;
	i[1] = r;
	ft_nbrflen(n, l);
	str = (char *)malloc(sizeof(char) * (l[0] + l[1] + 1));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		l[2]++;
		i[0] = -1;
	}
	str[l[0] + l[1]] = '\0';
	str = ft_ftoa_dec(str, l, i, n);
	if (l[0] > 0)
		return (ft_ftoa_float(str, l, i, n));
	return (str);
}
