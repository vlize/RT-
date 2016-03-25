/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 13:35:48 by vlize             #+#    #+#             */
/*   Updated: 2016/03/25 15:16:54 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"


static void		rec_rot_csg(char *str, t_csg *csg)
{
	int i;

	i = 0;
	while (str[i] != '"')
		i++;
	i++;
	rec_angle(ft_atoi(&str[i]), csg->rx, 1);
	while (str[i] != '"')
		i++;
	i++;
	while (str[i] != '"')
		i++;
	i++;
	rec_angle(ft_atoi(&str[i]), csg->ry, 1);
	while (str[i] != '"')
		i++;
	i++;
	while (str[i] != '"')
		i++;
	i++;
	rec_angle(ft_atoi(&str[i]), csg->rz, 1);
}

static t_obj	*add_obj_csg(int fd, char *ret, t_csg *csg, t_mat *mat)
{
	t_obj	*obj;

	obj = add_obj(fd, ret, NULL, mat);
	obj->id = csg->id;
	return (obj);
}

static t_node	*add_node(int fd, char *ret, t_csg *csg, t_mat *mat)
{
	static int	in_comment;
	t_node		*new;

	new = new_node(rec_int_value(ret));
	while (get_next_line(fd, &ret))
	{
		if (xml_cmp(ret, "<!--#") == 0)
			in_comment = 1;
		if (!in_comment && xml_cmp(ret, "<item") == 0)
			new->obj = add_obj_csg(fd, ret, csg, mat);
		else if (!in_comment && xml_cmp(ret, "<fork1") == 0)
			new->fork1 = add_node(fd, ret, csg, mat);
		else if (!in_comment && xml_cmp(ret, "<fork2") == 0)
			new->fork2 = add_node(fd, ret, csg, mat);
		else if (!in_comment && xml_cmp(ret, "</tree>") == 0)
			break ;
		else if (!in_comment && xml_cmp(ret, "</fork2>") == 0)
			break ;
		else if (!in_comment && xml_cmp(ret, "</fork1>") == 0)
			break ;
		if (xml_cmp(ret, "#-->") == 0)
			in_comment = 0;
	}
	return (new);
}

t_csg			*add_csg(int fd, char *ret, t_env *env)
{
	t_csg	*new;

	new = new_csg(rec_int_value(ret));
	while (get_next_line(fd, &ret))
	{
		if (xml_cmp(ret, "<scale") == 0)
			new->scale = rec_int_value(ret) / 100;
		if (xml_cmp(ret, "<crd") == 0)
			new->crd = rec_vec(ret);
		if (xml_cmp(ret, "<rotation") == 0)
			rec_rot_csg(ret, new);
		if (xml_cmp(ret, "<tree") == 0)
			new->tree = add_node(fd, ret, new, env->mat_lst);
		if (xml_cmp(ret, "</csg>") == 0)
			break ;
	}
	new->next = env->csg_lst;
	return (new);
}
