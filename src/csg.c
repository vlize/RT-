/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 10:11:34 by vlize             #+#    #+#             */
/*   Updated: 2016/03/25 11:54:45 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_interval	*obj_interval(t_obj *obj, t_ray *ray)
{
	t_interval	*i;
	double		k[4];

	if (!ray_collision(obj, ray, k))
		return (NULL);
	i = (t_interval *)malloc(sizeof(t_interval));
	i->next = NULL;
	i->obj_min = obj;
	i->obj_max = obj;
	i->min = k[0];
	i->max = k[1];
	if (k[2] > -DBL_MAX)
	{
		i->next = (t_interval *)malloc(sizeof(t_interval));
		i->next->next = NULL;
		i->next->obj_min = obj;
		i->next->obj_max = obj;
		i->next->min = k[2];
		i->next->max = k[3];
	}
	return (i);
}

t_interval			*get_interval(t_node *node, t_ray *ray)
{
	t_interval	*i1;
	t_interval	*i2;

	if (!node || !ray)
		return (NULL);
	if (!node->type && node->obj)
		return (obj_interval(node->obj, ray));
	i1 = get_interval(node->fork1, ray);
	i2 = get_interval(node->fork2, ray);
	if (node->type == INTERSECTION)
		return (intersection_interval(i1, i2));
	if (node->type == DIFFERENCE)
		return (difference_interval(i1, i2));
	if (node->type == UNION)
		return (union_interval(i1, i2));
	return (i1);
}

t_obj				*ray_collision_csg(t_csg *csg, t_ray *ray, double *k)
{
	t_interval	*i;
	t_interval	*t;
	t_obj		*obj;

	k[0] = DBL_MAX;
	if (!(i = get_interval(csg->tree, ray)))
		return (NULL);
	obj = NULL;
	t = i;
	while (t)
	{
		if ((t->min >= EPSILON) && (t->min < k[0]))
		{
			k[0] = t->min;
			obj = t->obj_min;
		}
		if ((t->max >= EPSILON) && (t->max < k[0]))
		{
			k[0] = t->max;
			obj = t->obj_max;
		}
		t = t->next;
	}
	free_interval(i);
	return (obj);
}
