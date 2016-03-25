/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 14:07:55 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/25 15:16:47 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		rec_angle(double nbr, double *angle, int deg)
{
	if (!angle)
		return ;
	angle[0] = nbr;
	if (deg)
		angle[0] *= RADIAN;
	angle[1] = cos(angle[0]);
	angle[2] = sin(angle[0]);
}

int			xml_cmp(char *str, char *ref)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && ref[j] && str[i] != ref[j])
		i++;
	while (str[i] && ref[j] && str[i] == ref[j])
	{
		if (ref[j] == '\0')
			return (0);
		i++;
		j++;
	}
	if (ref[j] == '\0')
		return (0);
	return (1);
}

void		rec_cam(int fd, char *ret, t_env *e)
{
	if(!(e->cam = (t_cam *)malloc(sizeof(t_cam))))
		malloc_error();
	while (get_next_line(fd, &ret))
	{
		if (xml_cmp(ret, "<crd") == 0)
		{
			e->cam->crd = rec_vec(ret);
		}
		if (xml_cmp(ret, "<rotation") == 0)
		{
			e->cam->rx[0] = 0;
			e->cam->rx[1] = 0;
			e->cam->rx[2] = 0;
			e->cam->ry[0] = 0;
			e->cam->ry[1] = 0;
			e->cam->ry[2] = 0;
			e->cam->rz[0] = 0;
			e->cam->rz[1] = 0;
			e->cam->rz[2] = 0;
		}
		if (xml_cmp(ret, "</camera") == 0)
			break;
	}
}

t_mat		*rec_mat(char *str, t_mat *mat_lst)
{
	int		i;
	t_mat	*tmp_lst;

	i = rec_int_value(str);
	tmp_lst = mat_lst;
	while (tmp_lst)
	{
		if (tmp_lst->id == i)
			return (tmp_lst);
		tmp_lst = tmp_lst->next;
	}
	ft_putendl("Erreur: un materiau n'existe pas.");
	return (NULL);
}

int			rec_int_value(char *str)
{
	int	i;

	i = 0;
	while ((str[i] != '"') && (str[i] != '\0'))
		i++;
	if (str[i] == '\0')
		return (-1);
	i++;
	return (ft_atoi(&str[i]));
}

double		rec_double_value(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '"')
		i++;
	i++;
	return (ft_atoi(&str[i]));
}

t_color		*rec_color(char *str)
{
	int		i;
	char	s[3];
	t_color	*ret;

	i = 0;
	if (!(ret = (t_color *)malloc(sizeof(t_color))))
		malloc_error();
	while (str[i] != '"')
		i++;
	i++;
	s[2] = '\0';
	ret->r = ft_xtoi(ft_memcpy(s, &str[i], 2));
	ret->g = ft_xtoi(ft_memcpy(s, &str[i + 2], 2));
	ret->b = ft_xtoi(ft_memcpy(s, &str[i + 4], 2));
	ret->r /= 255;
	ret->g /= 255;
	ret->b /= 255;
	return (ret);
}

char		*rec_name(char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	while (str[i] != '"')
		i++;
	i++;
	j = i;
	while (str[i] != '"')
		i++;
	ret = ft_strdup(&str[j]);
	i = 0;
	while (ret[i] != '"')
		i++;
	ret[i] = '\0';
	return (ret);
}

t_vector3	*rec_vec(char *str)
{
	int			i;
	t_vector3	*res;

	i = 0;
	if (!(res = (t_vector3 *)malloc(sizeof(t_vector3))))
		malloc_error();
	while (str[i] != '"')
		i++;
	i++;
	res->x = ft_atoi(&str[i]);
	while (str[i] != '"')
		i++;
	i++;
	while (str[i] != '"')
		i++;
	i++;
	res->y = ft_atoi(&str[i]);
	while (str[i] != '"')
		i++;
	i++;
	while (str[i] != '"')
		i++;
	i++;
	res->z = ft_atoi(&str[i]);
	return (res);
}

void		rec_rot(char *str, t_obj *obj)
{
	int	i;

	i = 0;
	while (str[i] != '"')
		i++;
	i++;
	rec_angle(ft_atoi(&str[i]), obj->rx, 1);
	while (str[i] != '"')
		i++;
	i++;
	while (str[i] != '"')
		i++;
	i++;
	rec_angle(ft_atoi(&str[i]), obj->ry, 1);
	while (str[i] != '"')
		i++;
	i++;
	while (str[i] != '"')
		i++;
	i++;
	rec_angle(ft_atoi(&str[i]), obj->rz, 1);
}

int			rec_texture_type(char *ret)
{
	char	*name;

	name = rec_name(ret);
	if (ft_strcmp("img", name) == 0)
	{
		free(name);
		return (0);
	}
	else if (ft_strcmp("proc", name) == 0)
	{
		free(name);
		return (1);
	}
	else
	{
		free(name);
		return (1);
	}
}

t_tex		*rec_texture(char *str, t_tex *lst_tex)
{
	int		i;
	t_tex	*cpy;

	i = rec_int_value(str);
	cpy = lst_tex;
	while (cpy != NULL && cpy->id != i)
		cpy = cpy->next;
	if (cpy == NULL)
		return (NULL);
	return (cpy);
}

void		rec_texture_file(t_tex *tex, char *ret, void *mlx)
{
	char	*name;
	int		endian;
	int		bpp;
	int		sizeline;

	name = rec_name(ret);
	tex->type = 0;
	if ((tex->img = mlx_xpm_file_to_image(mlx, name, &tex->width,
		&tex->height)) == NULL)
	{
		tex->type = 1;
		tex->proc_type = 0;
	}
	else
		tex->data = mlx_get_data_addr(tex->img, &bpp, &sizeline, &endian);
	if (name != NULL)
		free(name);
}

void		rec_texture_proc(t_tex *tex, char *ret)
{
	char	*name;

	name = rec_name(ret);
	tex->type = 1;
	if (ft_strcmp(name, "checker") == 0)
		tex->proc_type = 0;
	else
		tex->proc_type = 0;
	if (name != NULL)
		free(name);
}
