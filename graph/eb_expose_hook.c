/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eb_expose_hook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/01 18:32:23 by gpetrov           #+#    #+#             */
/*   Updated: 2014/06/01 18:38:31 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "lemipc.h"

static void		draw(t_share *shared, t_img *img, int i, int j)
{
	if (shared->map[j][i] == shared->team[0])
		draw_player_1(img, i, j);
	else if ((shared->map[j][i] == shared->team[1]) && (shared->team[1] != '.'))
		draw_player_2(img, i, j);
	else if ((shared->map[j][i] == shared->team[2]) && (shared->team[2] != '.'))
		draw_player_4(img, i, j);
	else if ((shared->map[j][i] == shared->team[2]) && (shared->team[2] != '.'))
		draw_player_3(img, i, j);
}

int				eb_expose_hook(t_share *shared)
{
	t_win		*env;
	t_img		*img;
	int			i;
	int			j;

	i = 0;
	j = 0;
	img = img_init();
	env = env_init();
	while (j < HEIGHT)
	{
		while (i < WIDTH)
		{
			draw(shared, img, i, j);
			i++;
		}
		i = 0;
		j++;
	}
	mlx_put_image_to_window(env->mlx, env->win, img->img, 0, 0);
	if (shared->end == TRUE)
		mlx_string_put(env->mlx, env->win, WIDTH / 2,
				HEIGHT / 2, color_norm(0, 255, 255), "THE END");
	return (0);
}
