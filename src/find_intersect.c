/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_intersect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 15:19:13 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/25 15:06:20 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			make_csg_ray(t_ray *ray1, t_ray *ray2, t_csg *csg)
{
	if (!ray1 || !ray2 || !csg)
		seg_fault();
	if (!(ray1->vec = (t_vector3 *)malloc(sizeof(t_vector3))))
		malloc_error();
	if (!(ray1->crd = (t_vector3 *)malloc(sizeof(t_vector3))))
		malloc_error();
	vec_cpy(ray1->vec, ray2->vec);
	csg_rotation(ray1->vec, csg, 1);
	set_vec(ray1->crd, csg->crd, ray2->crd);
	csg_rotation(ray1->crd, csg, 1);
}

static double	find_intersect_csg(t_ray *ray, t_csg *csg_lst, t_obj **hit_csg)
{
	double	k;
	double	tmp;
	t_ray	tmp_ray;
	t_obj	*tmp_obj;
	t_csg	*tmp_lst;

	k = DBL_MAX;
	*hit_csg = NULL;
	tmp_lst = csg_lst;
	while (tmp_lst)
	{
		make_csg_ray(&tmp_ray, ray, tmp_lst);
		tmp_obj = ray_collision_csg(tmp_lst, &tmp_ray, &tmp);
		if (tmp_obj && (tmp > EPSILON) && (tmp < k))
		{
			k = tmp;
			*hit_csg = tmp_obj;
		}
		free(tmp_ray.vec);
		free(tmp_ray.crd);
		tmp_lst = tmp_lst->next;
	}
	return (k);
}

static double	find_intersect_obj(t_ray *ray, t_obj *obj_lst, t_obj **hit_obj)
{
	double	k0;
	double	k[4];
	t_obj	*tmp_lst;

	k0 = DBL_MAX;
	*hit_obj = NULL;
	tmp_lst = obj_lst;
	while (tmp_lst)
	{
		if (smallest_k(tmp_lst, ray, k) && (k[0] > EPSILON) && (k[0] < k0))
		{
			k0 = k[0];
			*hit_obj = tmp_lst;
		}
		tmp_lst = tmp_lst->next;
	}
	return (k0);
}

t_vector3		*find_intersect(t_ray *ray, t_env *e, t_obj **hit_obj)
{
	double		k[3];
	t_obj		*hit_csg;

	*hit_obj = NULL;
	k[0] = DBL_MAX;
	k[1] = find_intersect_obj(ray, e->obj_lst, hit_obj);
	k[2] = find_intersect_csg(ray, e->csg_lst, &hit_csg);
	if ((k[1] < k[0]) && (k[1] > EPSILON))
		k[0] = k[1];
	if ((k[2] < k[0]) && (k[2] > EPSILON))
	{
		k[0] = k[2];
		*hit_obj = hit_csg;
	}
	if (k[0] < EPSILON || k[0] >= DBL_MAX || !*hit_obj)
		return (NULL);
	return (new_point(NULL, ray->vec, ray->crd, k[0]));
}
