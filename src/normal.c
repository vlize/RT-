/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 14:58:06 by vlize             #+#    #+#             */
/*   Updated: 2016/03/24 13:02:45 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	plane_normal(t_vector3 *norm, t_obj *hit_obj)
{
	norm->x = 0;
	norm->y = 0;
	norm->z = 1;
	vector_rotation(norm, hit_obj, 0);
}

static void	sphere_normal(t_vector3 *norm, t_obj *hit_obj, t_vector3 *hit_pt)
{
	norm->x = hit_pt->x - hit_obj->crd->x;
	norm->y = hit_pt->y - hit_obj->crd->y;
	norm->z = hit_pt->z - hit_obj->crd->z;
	normalise(norm);
}

static void	cylinder_normal(t_vector3 *norm, t_obj *hit_obj, t_vector3 *hit_pt)
{
	set_vec(norm, hit_obj->crd, hit_pt);
	vector_rotation(norm, hit_obj, 1);
	norm->z = 0;
	vector_rotation(norm, hit_obj, 0);
	normalise(norm);
}

static void	cone_normal(t_vector3 *norm, t_obj *hit_obj, t_vector3 *hit_pt)
{
	set_vec(norm, hit_obj->crd, hit_pt);
	vector_rotation(norm, hit_obj, 1);
	norm->z = (norm->x * norm->x + norm->y * norm->y) / -norm->z;
	vector_rotation(norm, hit_obj, 0);
	normalise(norm);
}

void		get_normal(t_vector3 *norm, t_obj *hit_obj, t_vector3 *hit_pt)
{
	if (hit_obj->type == PLANE)
		plane_normal(norm, hit_obj);
	else if (hit_obj->type == SPHERE)
		sphere_normal(norm, hit_obj, hit_pt);
	else if (hit_obj->type == CONE)
		cone_normal(norm, hit_obj, hit_pt);
	else if (hit_obj->type == CYLINDER)
		cylinder_normal(norm, hit_obj, hit_pt);
	// else
	// 	normal2(n, env);
	// normal_direction(n, env->ray_cur->vec);
}
