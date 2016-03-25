/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 11:31:07 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/24 10:53:33 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			cap_color(t_color *color)
{
	if (color->r > 1)
		color->r = 1;
	if (color->g > 1)
		color->g = 1;
	if (color->b > 1)
		color->b = 1;
}

static void		calc_cam_ray(double x, double y, t_ray *cam_ray, t_env *e)
{
	double	depth;

	depth = (e->height / 2) / FOV;
	cam_ray->vec->x = depth;
	cam_ray->vec->y = e->width / 2 - x;
	cam_ray->vec->z = e->height / 2 - y;
	normalise(cam_ray->vec);
}

static void		average_color(t_color *dst, int divi)
{
	dst->r /= divi;
	dst->g /= divi;
	dst->b /= divi;
}

static void		add_color(t_color *dst, t_color *col)
{
	dst->r += col->r;
	dst->g += col->g;
	dst->b += col->b;
}

static int		color_cmp(t_color *col1, t_color *col2, \
							t_color *col3, t_color *col4)
{
	double	d1;
	double	d2;
	double	d3;

	d1 = pow((col2->r - col1->r), 2) + pow((col2->g - col1->g), 2) \
		+ pow((col2->b - col1->b), 2);
	d2 = pow((col3->r - col1->r), 2) + pow((col3->g - col1->g), 2) \
		+ pow((col3->b - col1->b), 2);
	d3 = pow((col4->r - col1->r), 2) + pow((col4->g - col1->g), 2) \
		+ pow((col4->b - col1->b), 2);
	if (d1 != 0 || d2 != 0 || d3 != 0 )
		return(1);
	return (0);
}

static t_color	*anti_aliasing(double x, double y, t_ray *cam_ray, t_env *e)
{
	t_hit_pt	*hit_pt1;
	t_hit_pt	*hit_pt2;
	t_hit_pt	*hit_pt3;
	t_hit_pt	*hit_pt4;
	t_color		*color;
	static int	i = 0;
	static int	j = 0;

	color = (t_color *)malloc(sizeof(t_color));
	color->r = 0;
	color->g = 0;
	color->b = 0;
	calc_cam_ray(x, y, cam_ray, e);
	hit_pt1 = get_color(cam_ray, e);
	calc_cam_ray(x + 1, y + 1, cam_ray, e);
	hit_pt2 = get_color(cam_ray, e);
	calc_cam_ray(x + 1, y, cam_ray, e);
	hit_pt3 = get_color(cam_ray, e);
	calc_cam_ray(x, y + 1, cam_ray, e);
	hit_pt4 = get_color(cam_ray, e);
	add_color(color, hit_pt1->color);
	add_color(color, hit_pt2->color);
	add_color(color, hit_pt3->color);
	add_color(color, hit_pt4->color);
	if (!color_cmp(hit_pt1->color, hit_pt2->color, \
					hit_pt3->color, hit_pt4->color))
	{
		i++;
		// printf("SIMPLE %d, COMPLEXE %d\n", i, j);
		average_color(color, 4);
		return (color);
	}
	calc_cam_ray(x + 0.5, y, cam_ray, e);
	hit_pt1 = get_color(cam_ray, e);
	add_color(color, hit_pt1->color);

	calc_cam_ray(x , y + 0.5, cam_ray, e);
	hit_pt1 = get_color(cam_ray, e);
	add_color(color, hit_pt1->color);

	calc_cam_ray(x + 0.5, y + 0.5, cam_ray, e);
	hit_pt1 = get_color(cam_ray, e);
	add_color(color, hit_pt1->color);

	calc_cam_ray(x + 1, y + 0.5, cam_ray, e);
	hit_pt1 = get_color(cam_ray, e);
	add_color(color, hit_pt1->color);

	calc_cam_ray(x + 0.5, y + 1, cam_ray, e);
	hit_pt1 = get_color(cam_ray, e);
	add_color(color, hit_pt1->color);

	average_color(color, 9);
	j++;
	// printf("SIMPLE %d, COMPLEXE %d\n", i, j);
	return (color);
}

void			raytracer(t_env *e, char *addr)
{
	int			x;
	int			y;
	t_ray		*cam_ray;
	t_hit_pt	*hit_pt;

	x = 0;
	cam_ray = (t_ray *)malloc(sizeof(t_ray));
	cam_ray->vec = (t_vector3 *)malloc(sizeof(t_vector3));
	cam_ray->crd = e->cam->crd;
	while (x < e->width)
	{
		y = 0;
		while (y < e->height)
		{
			if ((x * e->width + y) % (e->width * e->height / 10) == 0 \
				|| x * y == (e->width - 1) * (e->height - 1))
			{
				mlx_put_image_to_window(e->mlx, e->win, e->img, 200, 0);
				print_loading(e);
				mlx_do_sync(e->mlx);
			}
			e->nb_refle = 0;
			if (e->aa == 0)
			{
				calc_cam_ray(x, y, cam_ray, e);
				hit_pt = get_color(cam_ray, e);
			}
			else
			{
				hit_pt = (t_hit_pt*)malloc(sizeof(t_hit_pt));
				hit_pt->color = anti_aliasing(x, y, cam_ray, e);
			}
			cap_color(hit_pt->color);
			addr[y * e->size + x * e->bit / 8] = hit_pt->color->b * 255;
			addr[y * e->size + x * e->bit / 8 + 1] = hit_pt->color->g * 255;
			addr[y * e->size + x * e->bit / 8 + 2] = hit_pt->color->r * 255;
			free_hit_pt(hit_pt);
			y++;
		}
		x++;
	}
	free(cam_ray->vec);
	free(cam_ray);
}
