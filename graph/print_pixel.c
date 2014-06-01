/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pixel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/29 19:38:46 by gpetrov           #+#    #+#             */
/*   Updated: 2014/06/01 18:39:05 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "lemipc.h"

int		color_norm(int red, int green, int blue)
{
	int		color;

	red = (red > 0xFF ? 0xFF : red);
	green = (green > 0xFF ? 0xFF : green);
	blue = (blue > 0xFF ? 0xFF : blue);
	red = (red < 0x00 ? 0x00 : red);
	green = (green < 0x00 ? 0x00 : green);
	blue = (blue < 0x00 ? 0x00 : blue);
	color = (red << 16) + (green << 8) + blue;
	return (color);
}

void	eb_put_pixel_to_img(t_img *img, int x, int y, int color)
{
	unsigned int	mgcv;
	int				i;
	t_win			*env;

	env = env_init();
	mgcv = mlx_get_color_value(env->mlx, color);
	i = x * 4 + y * img->size_line;
	img->data[i] = (mgcv & 0xFF);
	img->data[i + 1] = (mgcv & 0xFF00) >> 8;
	img->data[i + 2] = (mgcv & 0xFF0000) >> 16;
}
