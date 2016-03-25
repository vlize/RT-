/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 15:32:04 by vlize             #+#    #+#             */
/*   Updated: 2014/11/28 17:22:58 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_atoi_limit(char *s, int *i)
{
	if ((i[2] == -1) && (ft_memcmp(&s[i[0]], "9223372036854775808", 19) > 0))
	{
		i[3] = 0;
		return (0);
	}
	if ((i[2] == 1) && (ft_memcmp(&s[i[0]], "9223372036854775807", 19) > 0))
	{
		i[3] = -1;
		return (0);
	}
	return (1);
}

static int	ft_atoi_check(char *s, int *i)
{
	i[0] = 0;
	i[2] = 1;
	while (ft_isspace(s[i[0]]) == 1)
		i[0]++;
	if ((s[i[0]] == '-') || (s[i[0]] == '+'))
	{
		if (s[i[0]] == '-')
			i[2] = -1;
		i[0]++;
	}
	i[1] = i[0];
	while (ft_isdigit((int)s[i[1]]) == 1)
		i[1]++;
	if ((i[1] - i[0]) > 19)
	{
		if (i[2] == 1)
			i[3] = -1;
		return (0);
	}
	if ((i[1] - i[0]) == 19)
		return (ft_atoi_limit(s, i));
	return (1);
}

int			ft_atoi(const char *str)
{
	int		i[4];
	int		l[2];
	int		n[2];
	char	*tmp;

	n[0] = 0;
	i[3] = 0;
	if (!(tmp = (char *)str))
		return (0);
	if ((ft_atoi_check(tmp, i) == 0) || (ft_isdigit((int)str[i[0]]) == 0))
		return (i[3]);
	l[0] = i[1];
	while (i[1] > i[0])
	{
		n[1] = 1;
		l[1] = l[0] - i[1];
		while (l[1] > 0)
		{
			n[1] = n[1] * 10;
			l[1]--;
		}
		n[0] = n[0] + (((int)tmp[i[1] - 1] - 48) * n[1] * i[2]);
		i[1]--;
	}
	return (n[0]);
}
