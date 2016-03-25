/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 08:38:00 by vlize             #+#    #+#             */
/*   Updated: 2016/03/25 12:08:34 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	check_shadow(t_obj *obj, t_color *color, double dist)
{
	if ((obj->mat->trans == 0) && (dist < 0))
		return (1);
	else if (dist < EPSILON)
	{
		color->r += obj->mat->color->r * (100 - obj->mat->trans) / 100;
		color->g += obj->mat->color->r * (100 - obj->mat->trans) / 100;
		color->b += obj->mat->color->r * (100 - obj->mat->trans) / 100;
	}
	return (0);
}

static int	interval_shadow(t_ray *l_ray, t_interval *i, \
							t_color *color, double l_dist)
{
	t_vector3	hit_pt;
	double		dist;

	if (i->min > EPSILON)
	{
		new_point(&hit_pt, l_ray->vec, l_ray->crd, i->min);
		dist = get_dist(l_ray->crd, &hit_pt) - l_dist;
		if (check_shadow(i->obj_min, color, dist))
			return (1);
	}
	if (i->max > EPSILON)
	{
		new_point(&hit_pt, l_ray->vec, l_ray->crd, i->max);
		dist = get_dist(l_ray->crd, &hit_pt) - l_dist;
		if (check_shadow(i->obj_max, color, dist))
			return (1);
	}
	return (0);
}

static int	csg_shadow(t_ray *l_ray, t_csg *csg, t_color *color, double l_dist)
{
	t_ray		ray_tmp;
	t_csg		*csg_tmp;
	t_interval	*i_tmp;
	t_interval	*i;

	csg_tmp = csg;
	while (csg_tmp)
	{
		make_csg_ray(&ray_tmp, l_ray, csg_tmp);
		i = get_interval(csg_tmp->tree, &ray_tmp);
		i_tmp = i;
		while (i_tmp)
		{
			if (interval_shadow(&ray_tmp, i_tmp, color, l_dist))
				return (free_shadow(i, &ray_tmp));
			i_tmp = i_tmp->next;
		}
		free_shadow(i, &ray_tmp);
		csg_tmp = csg_tmp->next;
	}
	return (0);
}

static int	obj_shadow(t_ray *l_ray, t_obj *obj, t_color *color, double l_dist)
{
	t_obj		*obj_tmp;
	t_vector3	hit_pt;
	double		dist;
	double		k[4];

	obj_tmp = obj;
	while (obj_tmp)
	{
		if (smallest_k(obj, l_ray, k))
		{
			new_point(&hit_pt, l_ray->vec, l_ray->crd, k[0]);
			dist = get_dist(l_ray->crd, &hit_pt) - l_dist;
			if (check_shadow(obj_tmp, color, dist))
				return (1);
		}
		obj_tmp = obj_tmp->next;
	}
	return (0);
}

int			is_in_shadow(t_env *env, t_ray *light_ray, \
						t_color *color, t_light *light)
{
	t_color	color_tmp;
	double	light_dist;

	color_tmp.r = 0;
	color_tmp.g = 0;
	color_tmp.b = 0;
	light_dist = get_dist(light->crd, light_ray->crd);
	if (obj_shadow(light_ray, env->obj_lst, &color_tmp, light_dist))
		return (1);
	if (csg_shadow(light_ray, env->csg_lst, &color_tmp, light_dist))
		return (1);
	color->r += color_tmp.r;
	color->g += color_tmp.g;
	color->b += color_tmp.b;
	return (0);
}
