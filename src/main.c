/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 09:18:42 by thibautp          #+#    #+#             */
/*   Updated: 2016/03/23 09:07:18 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rt.h"

static int	ft_expose_hook(t_env *env)
{
	mlx_put_image_to_window(env->mlx, env->win, env->img, 200, 0);
	return (0);
}

static int	ft_key_hook(int keycode, t_env *env)
{
	if (keycode == 53 && env)
		// exit(ft_free_env(env));
		exit(0);
	return (0);
}

static int mouse_press(int button, int x, int y, t_env *e)
{
	if (x >= 21 && x <= 90 && y >= 362 && y<= 391 && e && button == 1)
	{
		e->menu->filter_button = 1;
		black_and_white(e);
	}
	if (x >= 111 && x <= 180 && y >= 362 && y<= 391 && e && button == 1)
	{
		e->menu->filter_button = 2;
		sepia(e);
	}
	if (x >= 61 && x <= 130 && y >= 403 && y<= 432 && e && button == 1)
	{
		e->menu->filter_button = 0;
		mlx_put_image_to_window(e->mlx, e->win, e->img, 200, 0);
	}
	if (x >= 21 && x <= 90 && y >= 483 && y<= 512 && e && button == 1)
	{
		e->menu->aa_button = 1;
		e->aa = 1;
		raytracer(e, e->addr_aa);
		mlx_put_image_to_window(e->mlx, e->win, e->img_aa, 200, 0);
		// mlx_do_sync(e->mlx);
	}
	print_menu(e);
	return (0);
}

int			main(int ac, char **av)
{
	t_env	*env;

	if (ac != 2)
		arg_error(ac);
	if (!(env = (t_env *)malloc(sizeof(t_env))))
		malloc_error();
	init(av[1], env);
	print_menu(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 200, 0);
	raytracer(env, env->addr);
	print_menu(env);
	// debug(env);
	mlx_key_hook(env->win, ft_key_hook, env);
	mlx_expose_hook(env->win, ft_expose_hook, env);
	mlx_hook(env->win, 4, (1L << 0), &mouse_press, env);
	mlx_loop(env->mlx);
	return (0);
}
