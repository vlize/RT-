/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 13:12:19 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/24 10:58:44 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	normalise(t_vector3 *vec)
{
	double tmp;

	tmp = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	if (tmp != 0)
	{
		vec->x /= tmp;
		vec->y /= tmp;
		vec->z /= tmp;
	}
}

int		quadratic_roots(double *deg, double *x)
{
	double	delta;
	double	k[2];

	delta = deg[1] * deg[1] - (deg[2] * deg[0] * 4);
	if (delta < 0)
		return (0);
	k[0] = 2 * deg[2];
	k[1] = 0 - deg[1];
	delta = sqrt(delta);
	x[0] = (k[1] + delta) / k[0];
	x[1] = (k[1] - delta) / k[0];
	if (x[0] > x[1])
	{
		k[0] = x[0];
		x[0] = x[1];
		x[1] = k[0];
	}
	return (1);
}

void	normal_direction(t_vector3 *norm, t_vector3 *vec)
{
	double	k;

	k = (vec->x * norm->x) + (vec->y * norm->y) + (vec->z * norm->z);
	if (k <= 0)
		return ;
	norm->x *= -1;
	norm->y *= -1;
	norm->z *= -1;
}
