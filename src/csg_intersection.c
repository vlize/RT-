/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 13:18:58 by vlize             #+#    #+#             */
/*   Updated: 2016/03/22 11:20:29 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	intersection_interval_new(t_interval **t)
{
	if (t[0])
	{
		t[3]->next = new_interval(NULL, NULL);
		t[3] = t[3]->next;
		return ;
	}
	t[0] = new_interval(NULL, NULL);
	t[3] = t[0];
}

static void	intersection_make(t_interval **t)
{
	intersection_interval_new(t);
	if (t[1]->min >= t[2]->min)
	{
		t[3]->min = t[1]->min;
		t[3]->obj_min = t[1]->obj_min;
	}
	else
	{
		t[3]->min = t[2]->min;
		t[3]->obj_min = t[2]->obj_min;
	}
	if (t[1]->max <= t[2]->max)
	{
		t[3]->max = t[1]->max;
		t[3]->obj_max = t[1]->obj_max;
		return ;
	}
	t[3]->max = t[2]->max;
	t[3]->obj_max = t[2]->obj_max;
}

t_interval	*intersection_interval(t_interval *i1, t_interval *i2)
{
	t_interval	*t[4];

	if (!i1)
		return (interval_null(i2));
	if (!i2)
		return (interval_null(i1));
	t[0] = NULL;
	t[1] = i1;
	while (t[1])
	{
		t[2] = i2;
		while (t[2])
		{
			if ((t[2]->max > t[1]->min) && (t[2]->min < t[1]->max))
				intersection_make(t);
			t[2] = t[2]->next;
		}
		t[1] = t[1]->next;
	}
	free_interval(i1);
	free_interval(i2);
	return (t[0]);
}
