/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_treatment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 09:11:12 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/22 14:17:06 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	black_and_white(t_env *e)
{
	int				x;
	int				y;
	unsigned char	tmp;

	x = 0;
	while (x < e->width)
	{
		y = 0;
		while (y < e->height)
		{
			tmp = ((unsigned char)e->addr[y * e->size + x * e->bit / 8] \
				+ (unsigned char)e->addr[y * e->size + x * e->bit / 8 + 1] \
				+ (unsigned char)e->addr[y * e->size + x * e->bit / 8 + 2]) / 3;
			e->addr_cpy[y * e->size + x * e->bit / 8] = tmp;
			e->addr_cpy[y * e->size + x * e->bit / 8 + 1] = tmp;
			e->addr_cpy[y * e->size + x * e->bit / 8 + 2] = tmp;
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img_cpy, 200, 0);
}

void	sepia(t_env *e)
{
	int	x;
	int	y;
	int	tmp_b;
	int	tmp_g;
	int	tmp_r;

	x = 0;
	while (x < e->width)
	{
		y = 0;
		while (y < e->height)
		{
			tmp_b = ((unsigned char)e->addr[y * e->size + x * e->bit / 8] * \
			0.131 + (unsigned char)e->addr[y * e->size + x * e->bit / 8 + 1] * \
			0.534 + (unsigned char)e->addr[y * e->size + x * e->bit / 8 + 2] * \
			0.272);
			tmp_g = ((unsigned char)e->addr[y * e->size + x * e->bit / 8] * \
			0.168 + (unsigned char)e->addr[y * e->size + x * e->bit / 8 + 1] * \
			0.686 + (unsigned char)e->addr[y * e->size + x * e->bit / 8 + 2] * \
			0.349);
			tmp_r = ((unsigned char)e->addr[y * e->size + x * e->bit / 8] * \
			0.189 + (unsigned char)e->addr[y * e->size + x * e->bit / 8 + 1] * \
			0.769 + (unsigned char)e->addr[y * e->size + x * e->bit / 8 + 2] * \
			0.393);
			tmp_b = (tmp_b > 255) ? 255 : tmp_b;
			tmp_g = (tmp_g > 255) ? 255 : tmp_g;
			tmp_r = (tmp_r > 255) ? 255 : tmp_r;
			e->addr_cpy[y * e->size + x * e->bit / 8] = tmp_b;
			e->addr_cpy[y * e->size + x * e->bit / 8 + 1] = tmp_g;
			e->addr_cpy[y * e->size + x * e->bit / 8 + 2] = tmp_r;
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img_cpy, 200, 0);
	mlx_do_sync(e->mlx);
}
