/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 12:53:45 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/24 10:53:05 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parameters_init(int fd, char *ret, t_env *e)
{
	while (get_next_line(fd, &ret))
	{
		if (xml_cmp(ret, "</parameters>") == 0)
			break ;
		if (xml_cmp(ret, "<resolution") == 0)
		{
			e->width = rec_int_value(ret);
			e->height = rec_int_value(&ret[24]);
		}
		if (xml_cmp(ret, "<ambient") == 0)
			e->ambient = rec_double_value(ret) / 100;
		if (xml_cmp(ret, "<anti-aliasing") == 0)
			e->aa = rec_double_value(ret);
		if (xml_cmp(ret, "<background") == 0)
			e->background = rec_color(ret);
		if (xml_cmp(ret, "<camera>") == 0)
			rec_cam(fd, ret, e);
	}
}

static void	materials_init(int fd, char *ret, t_env *e)
{
	while (get_next_line(fd, &ret))
	{
		if (xml_cmp(ret, "</materials>") == 0)
			break ;
		if (xml_cmp(ret, "<item") == 0)
			e->mat_lst = add_mat(fd, ret, e->mat_lst, e->tex_lst);
	}
}

static void	lights_init(int fd, char *ret, t_env *e)
{
	int	in_comment;

	in_comment = 0;
	while (get_next_line(fd, &ret))
	{
		if (xml_cmp(ret, "<!--#") == 0)
			in_comment = 1;
		if (xml_cmp(ret, "</lights>") == 0)
			break ;
		if (in_comment == 0 && xml_cmp(ret, "<item") == 0)
			e->light_lst = add_light(fd, ret, e->light_lst);
		if (xml_cmp(ret, "#-->") == 0)
			in_comment = 0;
	}
}

static void	objects_init(int fd, char *ret, t_env *e)
{
	int	in_comment;

	in_comment = 0;
	while (get_next_line(fd, &ret))
	{
		if (xml_cmp(ret, "<!--#") == 0)
			in_comment = 1;
		if (xml_cmp(ret, "</objects>") == 0)
			break ;
		if (!in_comment && xml_cmp(ret, "<item") == 0)
			e->obj_lst = add_obj(fd, ret, e->obj_lst, e->mat_lst);
		if (!in_comment && xml_cmp(ret, "<csg") == 0)
			e->csg_lst = add_csg(fd, ret, e);
		if (xml_cmp(ret, "#-->") == 0)
			in_comment = 0;
	}
}

void		parsing(int fd, t_env *e)
{
	int		i;
	char	*ret;

	i = 0;
	while (get_next_line(fd, &ret))
	{
		if (xml_cmp(ret, "<scene") == 0)
			e->scene_name = rec_name(ret);
		if ((i == 0) && (i += 1))
			parameters_init(fd, ret, e);
		if ((i == 1) && (i += 1))
			materials_init(fd, ret, e);
		if ((i == 2) && (i += 1))
			lights_init(fd, ret, e);
		if ((i == 3) && (i += 1))
			objects_init(fd, ret, e);
	}
}
