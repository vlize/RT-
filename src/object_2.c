/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 14:01:42 by vlize             #+#    #+#             */
/*   Updated: 2016/03/24 13:06:55 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	cone_2_inter(double *k)
{
	k[3] = DBL_MAX;
	k[2] = k[1];
	k[1] = k[0];
	k[0] = -DBL_MAX;
	return (1);
}

static int	cone_1_inter(double pt0_z, double vec_z, double *k)
{
	double	tmp;

	if (fabs(vec_z) < EPSILON)
		return (cone_2_inter(k));
	tmp = vec_z * k[0] + pt0_z;
	if (vec_z < 0)
	{
		if (tmp < 0)
			k[1] = DBL_MAX;
		else
			k[0] = -DBL_MAX;
		return (1);
	}
	if (tmp < 0)
		k[0] = -DBL_MAX;
	else
		k[1] = DBL_MAX;
	return (1);
}

int			cone(t_obj *obj, t_ray *ray, double *k)
{
	t_vector3	pt0;
	t_vector3	vec;
	double		deg[3];
	double		tmp[2];

	vec_cpy(&vec, ray->vec);
	vector_rotation(&vec, obj, 1);
	set_vec(&pt0, obj->crd, ray->crd);
	vector_rotation(&pt0, obj, 1);
	tmp[0] = fabs(tan(obj->r * RADIAN));
	tmp[1] = pt0.x * pt0.x + pt0.y * pt0.y;
	deg[0] = tmp[0] * tmp[0];
	deg[2] = vec.x * vec.x + vec.y * vec.y - vec.z * vec.z * deg[0];
	deg[1] = 2 * (vec.x * pt0.x + vec.y * pt0.y - vec.z * pt0.z * deg[0]);
	deg[0] = tmp[1] - pt0.z * pt0.z * deg[1];
	if (!quadratic_roots(deg, k))
		return (0);
	if (sqrt(tmp[1]) / fabs(pt0.z) > tmp[0])
		return (1);
	if (k[0] == k[1])
		return (cone_1_inter(pt0.z, vec.z, k));
	return (cone_2_inter(k));
}
