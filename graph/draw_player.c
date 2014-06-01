/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/01 18:29:03 by gpetrov           #+#    #+#             */
/*   Updated: 2014/06/01 18:37:48 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

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
