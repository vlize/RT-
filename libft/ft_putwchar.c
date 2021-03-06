/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/26 10:06:30 by vlize             #+#    #+#             */
/*   Updated: 2015/02/26 10:06:31 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putwchar(wchar_t wc)
{
	int	n[5];

	ft_unicode(wc, n);
	while (n[4] > 0)
	{
		write(1, &n[n[4] - 1], 1);
		n[4]--;
	}
}
