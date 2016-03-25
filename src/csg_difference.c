/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg_difference.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 14:08:44 by vlize             #+#    #+#             */
/*   Updated: 2016/03/22 10:59:47 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int			difference_nothing_remains(t_interval **i, t_interval **t)
{
	if ((t[1]->min < t[2]->min) || (t[1]->max > t[2]->max))
		return (1);
	if (t[0])
	{
		t[0]->next = t[1]->next;
		free(t[1]);
		t[1] = t[0]->next;
		return (0);
	}
	*i = t[1]->next;
	free(t[1]);
	t[1] = *i;
	return (0);
}

static void			difference_remaining_portion(t_interval **t)
{
	t_interval	*tmp;

	if ((t[1]->min >= t[2]->max) || (t[1]->max <= t[2]->min))
		return ;
	if ((t[1]->min < t[2]->min) && (t[1]->max <= t[2]->max))
	{
		t[1]->max = t[2]->min;
		t[1]->obj_max = t[2]->obj_min;
		return ;
	}
	if ((t[1]->min >= t[2]->min) && (t[1]->max > t[2]->max))
	{
		t[1]->min = t[2]->max;
		t[1]->obj_min = t[2]->obj_max;
		return ;
	}
	tmp = (t_interval *)malloc(sizeof(t_interval));
	tmp->min = t[2]->max;
	tmp->max = t[1]->max;
	tmp->obj_min = t[2]->obj_min;
	tmp->obj_max = t[1]->obj_max;
	tmp->next = t[1]->next;
	t[1]->max = t[2]->min;
	t[1]->obj_max = t[2]->obj_min;
}

t_interval			*difference_interval(t_interval *i1, t_interval *i2)
{
	t_interval	*t[3];
	int			n;

	if (!i1)
		return (interval_null(i2));
	if (!i2)
		return (i1);
	t[0] = NULL;
	t[1] = i1;
	n = 1;
	while (t[1])
	{
		t[2] = i2;
		while (t[2])
		{
			if (!(n = difference_nothing_remains(&i1, t)))
				break ;
			else
				difference_remaining_portion(t);
			t[2] = t[2]->next;
		}
		if (n && (t[0] = t[1]))
			t[1] = t[1]->next;
	}
	return (i1);
}
