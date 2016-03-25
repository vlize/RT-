/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 10:53:38 by vlize             #+#    #+#             */
/*   Updated: 2016/03/25 17:06:10 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	transparency_init(t_ray *ray_refr, t_obj *hit_obj, t_hit_pt *hit_pt)
{
	hit_pt->color->r *= (100.0 - hit_obj->mat->trans) / 100.0;
	hit_pt->color->g *= (100.0 - hit_obj->mat->trans) / 100.0;
	hit_pt->color->b *= (100.0 - hit_obj->mat->trans) / 100.0;
	if (!(ray_refr->crd = (t_vector3 *)malloc(sizeof(t_vector3))))
		malloc_error();
	vec_cpy(ray_refr->crd, hit_pt->crd);
	ray_refr->crd->x += hit_pt->root_ray->vec->x;
	ray_refr->crd->y += hit_pt->root_ray->vec->y;
	ray_refr->crd->z += hit_pt->root_ray->vec->z;
	ray_refr->vec = refre_vec(hit_pt->normal, hit_pt->root_ray->vec, 1, \
								hit_obj->mat->ind_trans);
}

static int	transparency_check(t_env *env, t_obj **obj, t_ray *ray, double *k)
{
	t_csg		*csg_tmp;
	t_interval	*i[2];

	csg_tmp = env->csg_lst;
	while (csg_tmp)
	{
		if (csg_tmp->id == (*obj)->id)
		{
			if (!(i[0] = get_interval(csg_tmp->tree, ray)))
				return (0);
			i[1] = i[0];
			while (i[1]->next && (i[1]->next->min < EPSILON))
				i[1] = i[1]->next;
			k[0] = i[1]->max;
			*obj = i[1]->obj_max;
			return (free_interval(i[0]));
		}
		csg_tmp = csg_tmp->next;
	}
	if (!smallest_k(*obj, ray, k))
		return (0);
	return (1);
}

void		transparency(t_env *env, t_obj *hit_obj, t_hit_pt *hit_pt)
{
	t_hit_pt	*hit_pt_refr;
	t_ray		ray_refr;
	t_vector3	normal;
	t_vector3	tmp;
	double		k[4];

	transparency_init(&ray_refr, hit_obj, hit_pt);
	if (!transparency_check(env, &hit_obj, &ray_refr, k))
		return (free_transparency(NULL, &ray_refr));
	vec_cpy(&tmp, ray_refr.vec);
	new_point(ray_refr.crd, ray_refr.vec, ray_refr.crd, k[0]);
	get_normal(&normal, hit_obj, ray_refr.crd);
	normal.x *= -1;
	normal.y *= -1;
	normal.z *= -1;
	ray_refr.vec = refre_vec(&normal, &tmp, hit_obj->mat->ind_trans, 1);
	hit_pt_refr = get_color(&ray_refr, env);
	cap_color(hit_pt_refr->color);
	hit_pt->color->r += hit_obj->mat->trans / 100.0 * hit_pt_refr->color->r;
	hit_pt->color->g += hit_obj->mat->trans / 100.0 * hit_pt_refr->color->g;
	hit_pt->color->b += hit_obj->mat->trans / 100.0 * hit_pt_refr->color->b;
	free_transparency(hit_pt_refr, &ray_refr);
}

void		reflection(t_env *env, t_obj *hit_obj, t_hit_pt *hit_pt)
{
	t_hit_pt	*hit_pt_refl;
	t_ray		ray_refl;

	env->nb_refle++;
	hit_pt->color->r *= (100.0 - hit_obj->mat->refl) / 100.0;
	hit_pt->color->g *= (100.0 - hit_obj->mat->refl) / 100.0;
	hit_pt->color->b *= (100.0 - hit_obj->mat->refl) / 100.0;
	ray_refl.vec = refle_vec(hit_pt->normal, hit_pt->root_ray->vec);
	ray_refl.crd = hit_pt->crd;
	hit_pt_refl = get_color(&ray_refl, env);
	cap_color(hit_pt_refl->color);
	hit_pt->color->r += hit_obj->mat->refl / 100.0 * hit_pt_refl->color->r;
	hit_pt->color->g += hit_obj->mat->refl / 100.0 * hit_pt_refl->color->g;
	hit_pt->color->b += hit_obj->mat->refl / 100.0 * hit_pt_refl->color->b;
	free(ray_refl.crd);
	free(ray_refl.vec);
	free_hit_pt(hit_pt_refl);
}
