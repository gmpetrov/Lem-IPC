/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/29 19:35:49 by gpetrov           #+#    #+#             */
/*   Updated: 2014/06/01 01:21:33 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include "lemipc.h"

t_win		*env_init(void)
{
	static t_win	*win = NULL;

	if (win == NULL)
	{
		if (!(win = (t_win *)malloc(sizeof(t_win))))
			perror("erreur malloc\n");
		win->mlx = mlx_init();
		win->win = mlx_new_window(win->mlx, WIDTH, HEIGHT
			, "Lem-ipc");
		win->img = img_init();
	}
	return (win);
}

t_img		*img_init(void)
{
	t_win	*win;
	t_img	*img;

	win = env_init();
	img = (t_img *)malloc(sizeof(t_img));
	img->img = mlx_new_image(win->mlx, WIDTH, HEIGHT);
	img->data = mlx_get_data_addr(img->img, &img->bpp, &img->size_line
		, &img->endian);
	return (img);
}
