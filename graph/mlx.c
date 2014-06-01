/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/29 19:31:37 by gpetrov           #+#    #+#             */
/*   Updated: 2014/06/01 18:35:09 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/shm.h>
#include <mlx.h>
#include <stdio.h>
#include "lemipc.h"

void	*eb_mlx(int	shm_id, t_share *shared)
{
	t_win		*env;
	t_img		*img;

	shared = shmat(shm_id, (void *)0, 0);
	env = env_init();
	img = img_init();
	mlx_key_hook(env->win, eb_mlx_key_hook, NULL);
	mlx_expose_hook(env->win, eb_expose_hook, shared);
	mlx_loop_hook(env->mlx, eb_loop_hook, shared);
	mlx_loop(env->mlx);
	return (NULL);
}

int		eb_mlx_key_hook(int keycode)
{
	t_win	*env;
	t_img	*img;

	if (keycode == KEY_ESC)
	{
		img = img_init();
		env = env_init();
		if (img->img)
			mlx_destroy_image(env->mlx, img->img);
		free(img);
		free(env);
		exit(0);
	}
	return (0);
}

int		eb_loop_hook(t_share *shared)
{
	eb_expose_hook(shared);
	return (0);
}

void	eb_clean_map(t_img *img)
{
	int		x;
	int		y;

	x = 0;
	while (x <= WIDTH)
	{
		y = 0;
		while (y <= HEIGHT)
		{
			eb_put_pixel_to_img(img, x, y, 0x000000);
			y++;
		}
		x++;
	}
}
