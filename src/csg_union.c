/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg_union.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 10:19:04 by vlize             #+#    #+#             */
/*   Updated: 2016/03/24 14:32:00 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	union_merge(t_interval **i1, t_interval *i2)
{
	t_interval	*t[3];

	t[1] = NULL;
	t[0] = i1[0];
	while (t[0] && i2)
	{
		if (i2->min < t[0]->min)
		{
			if (t[1])
				t[1]->next = i2;
			else
				i1[0] = i2;
			while (i2->next && (i2->next->min <= t[0]->min))
				i2 = i2->next;
			t[2] = i2->next;
			i2->next = t[0];
			i2 = t[2];
		}
		if (!t[0]->next && (t[0]->next = i2))
			break ;
		t[0] = t[0]->next;
	}
}

t_interval	*union_interval(t_interval *i1, t_interval *i2)
{
	t_interval	*t[2];

	if (!i2)
		return (i1);
	if (!i1)
		return (i2);
	union_merge(&i1, i2);
	t[0] = i1;
	while (t[0])
	{
		t[1] = t[0]->next;
		if (t[1] && (t[0]->max >= t[1]->min))
		{
			if (t[0]->max < t[1]->max)
			{
				t[0]->max = t[1]->max;
				t[0]->obj_max = t[1]->obj_max;
			}
			t[0]->next = t[1]->next;
			free(t[1]);
		}
		else
			t[0] = t[0]->next;
	}
	return (i1);
}
