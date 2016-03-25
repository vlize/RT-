/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 17:18:28 by vlize             #+#    #+#             */
/*   Updated: 2016/03/25 16:24:42 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	free_ray(t_ray *ray)
{
	if (!ray)
		return ;
	if (ray->vec)
		free(ray->vec);
	if (ray->crd)
		free(ray->crd);
	free(ray);
}

void	free_hit_pt(t_hit_pt *hit_pt)
{
	if (!hit_pt)
		return ;
	if (hit_pt->color)
		free(hit_pt->color);
	if (hit_pt->normal)
		free(hit_pt->normal);
	free_ray(hit_pt->root_ray);
	free(hit_pt);
}

int		free_interval(t_interval *i)
{
	t_interval	*tmp;

	while (i)
	{
		tmp = i->next;
		free(i);
		i = tmp;
	}
	return (1);
}

void	free_tree(t_node *tree)
{
	t_node	*tmp;

	if (!tree)
		return ;
	if (tree->fork1)
		free_tree(tree->fork1);
	tmp = tree->fork2;
	free(tree);
	return (free_tree(tmp));
}

void	free_csg(t_csg *csg)
{
	if (csg->crd)
		free(csg->crd);
	if (csg->tree)
		free_tree(csg->tree);
	free(csg);
}
