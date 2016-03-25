/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 11:53:52 by vlize             #+#    #+#             */
/*   Updated: 2016/03/25 16:16:49 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_interval	*interval_null(t_interval *i)
{
	free_interval(i);
	return (NULL);
}

int			free_shadow(t_interval *i, t_ray *ray)
{
	free_interval(i);
	if (!ray)
		return (1);
	if (ray->vec)
		free(ray->vec);
	if (ray->crd)
		free(ray->crd);
	ray->vec = NULL;
	ray->crd = NULL;
	return (1);
}

void		free_transparency(t_hit_pt *hit_pt, t_ray *ray)
{
	free_hit_pt(hit_pt);
	if (!ray)
		return ;
	if (ray->vec)
		free(ray->vec);
	if (ray->crd)
		free(ray->crd);
	ray->vec = NULL;
	ray->crd = NULL;
}
