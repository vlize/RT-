/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 14:18:18 by vlize             #+#    #+#             */
/*   Updated: 2016/03/25 15:19:59 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	dot_product(t_vector3 *v1, t_vector3 *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vector3		*refle_vec(t_vector3 *normal, t_vector3 *src_vec)
{
	t_vector3	*refle;
	double		dot_produc;

	if (!(refle = (t_vector3*)malloc(sizeof(t_vector3))))
		malloc_error();
	dot_produc = dot_product(src_vec, normal);
	refle->x = src_vec->x - 2 * dot_produc * normal->x;
	refle->y = src_vec->y - 2 * dot_produc * normal->y;
	refle->z = src_vec->z - 2 * dot_produc * normal->z;
	normalise(refle);
	return (refle);
}

t_vector3		*refre_vec(t_vector3 *normal, t_vector3 *incident, \
							double ind_prev, double ind_next)
{
	t_vector3 *refre;
	double	dot_produc;
	double n;
	double sint2;

	n = ind_prev / ind_next;
	if (n == 1)
		return (incident);
	dot_produc = dot_product(normal, incident);
	sint2 = n * n * (1.0 - dot_produc * dot_produc);
	if (sint2 > 1.0)
		return (NULL);
	if (!(refre = (t_vector3*)malloc(sizeof(t_vector3))))
		malloc_error();
	refre->x = n * incident->x - (n + sqrt(1.0 - sint2)) * normal->x;
	refre->y = n * incident->y - (n + sqrt(1.0 - sint2)) * normal->y;
	refre->z = n * incident->z - (n + sqrt(1.0 - sint2)) * normal->z;
	normalise(refre);
	return (refre);
}

void			vec_cpy(t_vector3 *dst, t_vector3 *src)
{
	if (!dst || !src)
		seg_fault();
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
}

double			get_dist(t_vector3 *p1, t_vector3 *p2)
{
	return (sqrt(powf(p1->x - p2->x, 2) + powf(p1->y - p2->y, 2) \
										+ powf(p1->z - p2->z, 2)));
}

void			set_vec(t_vector3 *vec, t_vector3 *p1, t_vector3 *p2)
{
	vec->x = p2->x - p1->x;
	vec->y = p2->y - p1->y;
	vec->z = p2->z - p1->z;
}

t_vector3		*rot_pt1(t_vector3 *pt1, t_obj *obj)
{
	if (!pt1 || !obj)
		seg_fault();
	vector_rotation(pt1, obj, 0);
	pt1->x += obj->crd->x;
	pt1->y += obj->crd->y;
	pt1->z += obj->crd->z;
	return (pt1);
}
