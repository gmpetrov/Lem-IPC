/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/29 19:31:37 by gpetrov           #+#    #+#             */
/*   Updated: 2014/06/01 01:23:31 by gpetrov          ###   ########.fr       */
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

void	draw_player_1(t_img *img, int	i, int j)
{
	eb_put_pixel_to_img(img, i, j, color_norm(255, 0, 0));
	eb_put_pixel_to_img(img, i + 1, j, color_norm(255, 0, 0));
	eb_put_pixel_to_img(img, i, j + 1, color_norm(255, 0, 0));
	eb_put_pixel_to_img(img, i + 1, j + 1, color_norm(255, 0, 0));
}

void	draw_player_2(t_img *img, int i, int j)
{
	eb_put_pixel_to_img(img, i, j, color_norm(0, 255, 0));
	eb_put_pixel_to_img(img, i + 1, j, color_norm(0, 255, 0));	
	eb_put_pixel_to_img(img, i, j + 1, color_norm(0, 255, 0));
	eb_put_pixel_to_img(img, i + 1, j + 1, color_norm(0, 255, 0));
}

void	draw_player_3(t_img *img, int i, int j)
{
	eb_put_pixel_to_img(img, i, j, color_norm(0, 0, 255));
	eb_put_pixel_to_img(img, i + 1, j, color_norm(0, 0, 255));
	eb_put_pixel_to_img(img, i, j + 1, color_norm(0, 0, 255));
	eb_put_pixel_to_img(img, i + 1, j + 1, color_norm(0, 0, 255));
}

void	draw_player_4(t_img *img, int i, int j)
{
	eb_put_pixel_to_img(img, i, j, color_norm(255, 255, 0));
	eb_put_pixel_to_img(img, i + 1, j, color_norm(255, 255, 0));
	eb_put_pixel_to_img(img, i, j + 1, color_norm(255, 255, 0));
	eb_put_pixel_to_img(img, i + 1, j + 1, color_norm(255, 255, 0));
}

void	draw_player_5(t_img *img, int i, int j)
{
	eb_put_pixel_to_img(img, i, j, color_norm(0, 255, 255));
	eb_put_pixel_to_img(img, i + 1, j, color_norm(0, 255, 255));
	eb_put_pixel_to_img(img, i, j + 1, color_norm(0, 255, 255));
	eb_put_pixel_to_img(img, i + 1, j + 1, color_norm(0, 255, 255));
}

int		eb_expose_hook(t_share *shared)
{
	t_win		*env;
	t_img		*img;
	int		i;
	int		j;

	(void)shared;
	img = img_init();
	env = env_init();
	i = 0;
	j = 0;
	while (j < HEIGHT)
	{
		while (i < WIDTH)
		{
			if (shared->map[j][i] == shared->team[0])
				draw_player_1(img, i, j);
			else if ((shared->map[j][i] == shared->team[1]) && (shared->team[1] != '.'))
				draw_player_2(img, i, j);
			else if ((shared->map[j][i] == shared->team[2]) && (shared->team[2] != '.'))
				draw_player_4(img, i, j);
			else if ((shared->map[j][i] == shared->team[2]) && (shared->team[2] != '.'))
				draw_player_3(img, i, j);
//			else if ((shared->map[j][i] != '.'))
//				draw_player_5(img, i, j);
			i++;
		}
		i = 0;
		j++;
	}
	mlx_put_image_to_window(env->mlx, env->win, img->img, 0, 0);
	if (shared->end == TRUE)
		mlx_string_put(env->mlx, env->win, WIDTH / 2, HEIGHT / 2, color_norm(0, 255, 255),
						"THE END");
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
