/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/01 18:44:51 by gpetrov           #+#    #+#             */
/*   Updated: 2014/06/01 18:45:02 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

void	case_5(t_share *shared, t_player *player)
{
	int		dx;
	int		dy;

	dx = player->ad_x - player->x;
	dy = player->ad_y - player->y;
	if (dx <= dy)
	{
		if (shared->map[player->y][player->x + 1] != '.')
			return ;
		shared->map[player->y][player->x] = '.';
		player->x += 1;
		shared->map[player->y][player->x] = player->team;
	}
	else
	{
		if (shared->map[player->y + 1][player->x] != '.')
			return ;
		shared->map[player->y][player->x] = '.';
		player->y += 1;
		shared->map[player->y][player->x] = player->team;
	}
}

void	case_6(t_share *shared, t_player *player)
{
	if (shared->map[player->y][player->x - 1] != '.')
	{
		if (player->y - 1 >= 0 && shared->map[player->y - 1][player->x] == '.')
		{
			shared->map[player->y][player->x] = '.';
			player->y -= 1;
			shared->map[player->y][player->x] = player->team;
		}
		else if (player->y + 1 < HEIGHT &&
			shared->map[player->y + 1][player->x] == '.')
		{
			shared->map[player->y][player->x] = '.';
			player->y += 1;
			shared->map[player->y][player->x] = player->team;
		}
		return ;
	}
	shared->map[player->y][player->x] = '.';
	player->x -= 1;
	shared->map[player->y][player->x] = player->team;
}

void	case_7(t_share *shared, t_player *player)
{
	int		dx;
	int		dy;

	dx = player->x - player->ad_x;
	dy = player->ad_y - player->y;
	if (dx <= dy)
	{
		if (shared->map[player->y][player->x - 1] != '.')
			return ;
		shared->map[player->y][player->x] = '.';
		player->x -= 1;
		shared->map[player->y][player->x] = player->team;
	}
	else
	{
		if (shared->map[player->y + 1][player->x] != '.')
			return ;
		shared->map[player->y][player->x] = '.';
		player->y += 1;
		shared->map[player->y][player->x] = player->team;
	}
}

void	case_8(t_share *shared, t_player *player)
{
	if (shared->map[player->y][player->x - 1] != '.')
	{
		if (player->y - 1 >= 0 && shared->map[player->y - 1][player->x] == '.')
		{
			shared->map[player->y][player->x] = '.';
			player->y -= 1;
			shared->map[player->y][player->x] = player->team;
		}
		else if (player->y + 1 < HEIGHT &&
			shared->map[player->y + 1][player->x] == '.')
		{
			shared->map[player->y][player->x] = '.';
			player->y += 1;
			shared->map[player->y][player->x] = player->team;
		}
		return ;
	}
	shared->map[player->y][player->x] = '.';
	player->x -= 1;
	shared->map[player->y][player->x] = player->team;
}
