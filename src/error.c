/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 09:54:26 by thibautp          #+#    #+#             */
/*   Updated: 2016/03/25 15:05:46 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	malloc_error()
{
	ft_putstr_fd("Malloc error\n", 2);
	exit(0);
}

void	seg_fault()
{
	ft_putstr_fd("Segmentation fault\n", 2);
	exit(0);
}

void	arg_error(int ac)
{
	if (ac < 2)
		ft_putstr_fd("File name missing\n", 2);
	else if (ac > 2)
		ft_putstr_fd("Too many arguments\n", 2);
	exit(0);
}
