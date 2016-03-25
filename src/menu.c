/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 14:15:21 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/23 09:13:30 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		print_loading(t_env *e)
{
	static int	nb = 0;
	int			i;
	int			j;

	j = 0;
	while (j < 20)
	{
		i = 0;
		while (i < 20)
		{
			e->addr_load[i * e->size_load + (nb * 20 + j) \
							* e->bit_load / 8] = 255;
			e->addr_load[i * e->size_load + (nb * 20 + j) \
							* e->bit_load / 8 + 1] = 255;
			e->addr_load[i * e->size_load + (nb * 20 + j) \
							* e->bit_load / 8 + 2] = 255;
			i++;
		}
		j++;
	}
	nb++;
	mlx_put_image_to_window(e->mlx, e->win, e->img_load, 0, e->height - 110);
}

static int	*fill_params(int x, int y, int width, int heigth)
{
	int	*ret;

	ret = (int *)malloc(sizeof(int) * 4);
	ret[0] = x;
	ret[1] = y;
	ret[2] = width;
	ret[3] = heigth;
	return (ret);
}

static void	print_button(t_env *e, int *prm, char *text, int boo)
{
	int	i;
	int	j;
	int	color;

	color = (boo == 1) ? 0xFF0000 : 0xFFFFFF;
	i = 0;
	while (i < prm[2])
	{
		mlx_pixel_put(e->mlx, e->win, prm[0] + i, prm[1], color);
		if (i == 0 || i == prm[2] - 1)
		{
			j = 1;
			while (j < prm[3])
			{
				mlx_pixel_put(e->mlx, e->win, prm[0] + i, prm[1] + j, color);
				j++;
			}
		}
		mlx_pixel_put(e->mlx, e->win, prm[0] + i, prm[1] + prm[3] - 1, color);
		i++;
	}
	mlx_string_put(e->mlx, e->win, prm[0] + prm[2] / 10, \
					prm[1] + prm[3] / 10, 0xFFFFFF, text);
	free(prm);
}

int			print_elements(int nbl, int l, t_env *e)
{
	print_button(e, fill_params(10, nbl * l, 25, 25), "<", 0);
	print_button(e, fill_params(160, nbl * l, 25, 25), " >", 0);
	nbl += 2;
	mlx_string_put(e->mlx, e->win, 0, nbl++ * l, 0xFFFFFF, "Position");
	mlx_string_put(e->mlx, e->win, 10, nbl * l, 0xFFFFFF, "X :");
	mlx_string_put(e->mlx, e->win, 50, nbl++ * l, 0xFFFFFF, \
					ft_itoa(e->cam->crd->x));
	mlx_string_put(e->mlx, e->win, 10, nbl * l, 0xFFFFFF, "Y :");
	mlx_string_put(e->mlx, e->win, 50, nbl++ * l, 0xFFFFFF, \
					ft_itoa(e->cam->crd->y));
	mlx_string_put(e->mlx, e->win, 10, nbl * l, 0xFFFFFF, "Z :");
	mlx_string_put(e->mlx, e->win, 50, nbl++ * l, 0xFFFFFF, \
					ft_itoa(e->cam->crd->z));
	nbl++;
	mlx_string_put(e->mlx, e->win, 0, nbl++ * l, 0xFFFFFF, "Rotation");
	mlx_string_put(e->mlx, e->win, 10, nbl * l, 0xFFFFFF, "X :");
	mlx_string_put(e->mlx, e->win, 50, nbl++ * l, 0xFFFFFF, \
					ft_itoa(e->cam->rx[0]));
	mlx_string_put(e->mlx, e->win, 10, nbl * l, 0xFFFFFF, "Y :");
	mlx_string_put(e->mlx, e->win, 50, nbl++ * l, 0xFFFFFF, \
					ft_itoa(e->cam->ry[0]));
	mlx_string_put(e->mlx, e->win, 10, nbl * l, 0xFFFFFF, "Z :");
	mlx_string_put(e->mlx, e->win, 50, nbl++ * l, 0xFFFFFF, \
					ft_itoa(e->cam->rz[0]));
	nbl++;
	print_button(e, fill_params(60, nbl * l, 70, 30), "Reload", 0);
	return (13);
}

int			print_effects(int nbl, int l, t_env *e)
{
	int	sepia;
	int	none;
	int	b_w;

	sepia = (e->menu->filter_button == 2) ? 1 : 0;
	b_w = (e->menu->filter_button == 1) ? 1 : 0;
	none = (e->menu->filter_button == 0) ? 1 : 0;
	mlx_string_put(e->mlx, e->win, 0, nbl++ * l, 0xFFFFFF, "Filters:");
	nbl++;
	print_button(e, fill_params(20, nbl * l, 70, 30), "B & W", b_w);
	print_button(e, fill_params(110, nbl * l, 70, 30), "Sepia", sepia);
	nbl += 2;
	print_button(e, fill_params(60, nbl * l, 70, 30), " None", none);
	nbl += 2;
	mlx_string_put(e->mlx, e->win, 0, nbl * l, 0xFFFFFF, "AA:");
	nbl += 2;
	print_button(e, fill_params(20, nbl * l, 70, 30), "  On", \
				e->menu->aa_button);
	print_button(e, fill_params(110, nbl * l, 70, 30), " Off", \
				(e->menu->aa_button + 1) % 2);
	return (12);
}

void		clear_menu(t_env *e)
{
	int	i;
	int	j;

	j = 0;
	while (j < 200)
	{
		i = 0;
		while (i < e->height)
		{
			mlx_pixel_put(e->mlx, e->win, j, i, 0x000000);
			i++;
		}
		j++;
	}
}

void		print_menu(t_env *e)
{
	int	l;
	int	nbl;

	l = 20;
	nbl = 0;
	clear_menu(e);
	mlx_string_put(e->mlx, e->win, 0 , nbl++ * l, 0xFFFFFF, e->scene_name);
	nbl++;
	nbl += print_elements(nbl, l, e);
	nbl++;
	nbl += print_effects(nbl, l, e);
	print_button(e, fill_params(25, nbl * l, 150, 30), "Save Picture", 0);
	mlx_string_put(e->mlx, e->win, 0, e->height - 135, 0xFFFFFF, "Loading");
	mlx_string_put(e->mlx, e->win, 0, e->height - 70, \
					0xFFFFFF, "Nbr of rays :");
	if (e->nb_rays > 0)
		mlx_string_put(e->mlx, e->win, 0, e->height - 50, \
						0xFFFFFF, ft_itoa(e->nb_rays));
	int i = 0;
	while (i < e->height)
	{
		mlx_pixel_put(e->mlx, e->win, 199, i, 0xFFFFFF);
		i++;
	}
	//print_loading(e, 50);
}
