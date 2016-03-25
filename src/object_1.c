/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 14:52:54 by vlize             #+#    #+#             */
/*   Updated: 2016/03/24 15:31:22 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			plane(t_obj *obj, t_ray *ray, double *k)
{
	t_vector3	vec;
	t_vector3	pt0;

	vec_cpy(&vec, ray->vec);
	vector_rotation(&vec, obj, 1);
	set_vec(&pt0, obj->crd, ray->crd);
	vector_rotation(&pt0, obj, 1);
	if (fabs(vec.z) < EPSILON)
	{
		if (pt0.z > 0)
			return (0);
		k[1] = DBL_MAX;
		return (1);
	}
	if (fabs(k[1] = -pt0.z / vec.z) < EPSILON)
		return (0);
	if (vec.z > 0)
		return (1);
	k[0] = k[1];
	k[1] = DBL_MAX;
	return (1);
}

int			sphere(t_obj *obj, t_ray *ray, double *k)
{
	t_vector3	vec;
	double		deg[3];

	set_vec(&vec, obj->crd, ray->crd);
	deg[2] = ray->vec->x * ray->vec->x + ray->vec->y * ray->vec->y \
			+ ray->vec->z * ray->vec->z;
	deg[1] = ray->vec->x * vec.x + ray->vec->y * vec.y + ray->vec->z * vec.z;
	deg[1] *= 2;
	deg[0] = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z - obj->r * obj->r;
	if (!quadratic_roots(deg, k))
		return (0);
	return (1);
}

int			cylinder(t_obj *obj, t_ray *ray, double *k)
{
	t_vector3	pt0;
	t_vector3	vec;
	double		deg[3];
	double		tmp;

	vec_cpy(&vec, ray->vec);
	vector_rotation(&vec, obj, 1);
	set_vec(&pt0, obj->crd, ray->crd);
	vector_rotation(&pt0, obj, 1);
	deg[2] = vec.x * vec.x + vec.y * vec.y;
	deg[1] = (vec.x * pt0.x + vec.y * pt0.y) * 2;
	tmp = pt0.x * pt0.x + pt0.y * pt0.y;
	deg[0] = tmp - obj->r * obj->r;
	if (quadratic_roots(deg, k))
		return (1);
	if (sqrt(tmp) > obj->r)
		return (0);
	k[1] = DBL_MAX;
	return (1);
}
