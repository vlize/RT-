/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 08:28:56 by vlize             #+#    #+#             */
/*   Updated: 2016/03/24 16:48:19 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	obj_intersect(t_obj *obj, t_ray *ray, double *k)
{
	if (obj->type == PLANE)
		return (plane(obj, ray, k));
	else if (obj->type == SPHERE)
		return (sphere(obj, ray, k));
	else if (obj->type == CYLINDER)
		return (cylinder(obj, ray, k));
	else if (obj->type == CONE)
		return (cone(obj, ray, k));
// 	else if (obj->type == ELLIPSOID)
// 		return (ellipsoid(obj, ray));
// 	else if (obj->type == PARABOLOID)
// 		return (paraboloid(obj, ray));
// 	else if (obj->type == HYPERBOLOID)
// 		return (hyperboloid(obj, ray));
	return (0);
}

int			ray_collision(t_obj *obj, t_ray *ray, double *k)
{
	if (!obj || !ray || !k)
		return (0);
	k[0] = -DBL_MAX;
	k[1] = -DBL_MAX;
	k[2] = -DBL_MAX;
	k[3] = -DBL_MAX;
	if (obj_intersect(obj, ray, k))
		return (1);
	return (0);
}

int			smallest_k(t_obj *obj, t_ray *ray, double *k)
{
	double	tmp;

	if (!ray_collision(obj, ray, k))
		return (0);
	tmp = DBL_MAX;
	if ((k[0] < tmp) && (k[0] > EPSILON))
		tmp = k[0];
	if ((k[1] < tmp) && (k[1] > EPSILON))
		tmp = k[1];
	if ((k[2] < tmp) && (k[2] > EPSILON))
		tmp = k[2];
	if ((k[3] < tmp) && (k[3] > EPSILON))
		tmp = k[3];
	if (tmp >= DBL_MAX)
		return (0);
	k[0] = tmp;
	return (1);
}
