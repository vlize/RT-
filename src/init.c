/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 09:36:58 by vlize             #+#    #+#             */
/*   Updated: 2016/03/23 09:00:11 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_mlx(t_env *e)
{
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, e->width + 200, e->height, e->scene_name);
	e->img = mlx_new_image(e->mlx, e->width , e->height);
	e->img_cpy = mlx_new_image(e->mlx, e->width , e->height);
	e->addr = mlx_get_data_addr(e->img, &e->bit, &e->size, &e->end);
	e->addr_cpy = mlx_get_data_addr(e->img_cpy, &e->bit, &e->size, &e->end);
	e->img_load = mlx_new_image(e->mlx, 199 , 20);
	e->addr_load = mlx_get_data_addr(e->img_load, &e->bit_load, \
									&e->size_load, &e->end_load);
	e->img_aa = mlx_new_image(e->mlx, e->width , e->height);
	e->addr_aa = mlx_get_data_addr(e->img_aa, &e->bit, &e->size, &e->end);
}

int		nb_lights(t_env *e)
{
	t_light *tmp_light;
	int nb;

	nb = 0;
	tmp_light = e->light_lst;
	while (tmp_light)
	{
		nb++;
		tmp_light = tmp_light->next;
	}
	return (nb);
}

void	init(char *arg, t_env *env)
{
	int fd;
	t_menu *menu;

	env->mat_lst = NULL;
	env->obj_lst = NULL;
	env->csg_lst = NULL;
	env->light_lst = NULL;
	if ((fd = open(arg, O_RDONLY)) < 0)
		exit(write(1, "scene name error",2));
	parsing(fd, env);
	env->nb_rays = 0;
	env->nb_lights = nb_lights(env);
	menu = (t_menu *)malloc(sizeof(t_menu));
	menu->filter_button = 0;
	menu->aa_button = 0;
	env->menu = menu;
	init_mlx(env);
	close(fd);
}
