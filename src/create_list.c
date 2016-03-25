/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 16:58:39 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/21 18:02:06 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_mat	*add_mat(int fd, char *ret, t_mat *mat, t_tex *lst_tex)
{
	t_mat	*new;

	new = (t_mat *)malloc(sizeof(t_mat));
	new->next = NULL;
	new->tex = NULL;
	new->id = rec_int_value(ret);
	while (get_next_line(fd, &ret))
	{
		if (xml_cmp(ret, "<specular") == 0)
			new->spec = rec_int_value(ret);
		if (xml_cmp(ret, "<reflection") == 0)
			new->refl = rec_int_value(ret);
		if (xml_cmp(ret, "<transparency") == 0)
			new->trans = rec_int_value(ret);
		if (xml_cmp(ret, "<refraction") == 0)
			new->ind_trans = rec_int_value(ret) / 100.0;
		if (xml_cmp(ret, "<color") == 0)
			new->color = rec_color(ret);
		if (xml_cmp(ret, "<texture") == 0)
			new->tex = rec_texture(ret, lst_tex);
		if (xml_cmp(ret, "</item>") == 0)
			break ;
	}
	if (!mat)
		return (new);
	new->next = mat;
	return (new);
}

t_tex	*add_tex(int fd, char *ret, t_tex *tex, void *mlx)
{
	t_tex	*new;

	new = (t_tex *)malloc(sizeof(t_tex));
	new->next = NULL;
	new->id = rec_int_value(ret);
	new->img = NULL;
	new->data = NULL;
	while (get_next_line(fd, &ret))
	{
		if (xml_cmp(ret, "<type") == 0)
		new->type = rec_texture_type(ret);
		if (xml_cmp(ret, "<file") == 0)
		rec_texture_file(new, ret, mlx);
		if (xml_cmp(ret, "<name") == 0)
		rec_texture_proc(new, ret);
		if (xml_cmp(ret, "</item>") == 0)
			break ;
	}
	if (!tex)
		return (new);
	new->next = tex;
	return (new);
}

t_light	*add_light(int fd, char *ret, t_light *light)
{
	t_light	*new;

	new = (t_light *)malloc(sizeof(t_light));
	new->next = NULL;
	new->id = rec_int_value(ret);
	while (get_next_line(fd, &ret))
	{
		if (xml_cmp(ret, "<type") == 0)
			new->type = rec_int_value(ret);
		if (xml_cmp(ret, "<crd") == 0)
			new->crd = rec_vec(ret);
		if (xml_cmp(ret, "<intensity") == 0)
			new->intensity = rec_int_value(ret);
		if (xml_cmp(ret, "</item>") == 0)
			break ;
	}
	if (!light)
		return (new);
	new->next = light;
	return (new);
}

t_obj	*add_obj(int fd, char *ret, t_obj *obj, t_mat *mat)
{
	t_obj	*new;

	new = (t_obj *)malloc(sizeof(t_obj));
	new->next = NULL;
	new->id = rec_int_value(ret);
	while (get_next_line(fd, &ret))
	{
		if (xml_cmp(ret, "<type") == 0)
			new->type = rec_int_value(ret);
		if (xml_cmp(ret, "<crd") == 0)
			new->crd = rec_vec(ret);
		if (xml_cmp(ret, "<rotation") == 0)
			rec_rot(ret, new);
		if (xml_cmp(ret, "<radius") == 0)
			new->r = rec_int_value(ret);
		if (xml_cmp(ret, "<material") == 0)
			new->mat = rec_mat(ret, mat);
		if (xml_cmp(ret, "</item>") == 0)
			break ;
	}
	if (!obj)
		return (new);
	new->next = obj;
	return (new);
}
