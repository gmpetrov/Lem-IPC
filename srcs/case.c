/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/29 16:29:01 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/29 16:45:50 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

void	case_1(t_share *shared, t_player *player)
{
	int		dx;
	int		dy;

	dx = player->x - player->ad_x;
	dy = player->y - player->ad_y;
	if (dx <= dy)
	{
		shared->map[player->y][player->x] = '.';
		player->x -= 1;
		shared->map[player->y][player->x] = player->team;
	}
	else
	{
		shared->map[player->y][player->x] = '.';
		player->y -= 1;
		shared->map[player->y][player->x] = player->team;
	}
}

void	case_2(t_share *shared, t_player *player)
{
		shared->map[player->y][player->x] = '.';
		player->y -= 1;
		shared->map[player->y][player->x] = player->team;
}

void	case_3(t_share *shared, t_player *player)
{
	int		dx;
	int		dy;

	dx = player->ad_x - player->x;
	dy = player->y - player->ad_y;
	if (dx <= dy)
	{
		shared->map[player->y][player->x] = '.';
		player->x += 1;
		shared->map[player->y][player->x] = player->team;
	}
	else
	{
		shared->map[player->y][player->x] = '.';
		player->y -= 1;
		shared->map[player->y][player->x] = player->team;
	}
}

void	case_4(t_share *shared, t_player *player)
{
		shared->map[player->y][player->x] = '.';
		player->x += 1;
		shared->map[player->y][player->x] = player->team;	
}

void	case_5(t_share *shared, t_player *player)
{
	int		dx;
	int		dy;

	dx = player->ad_x - player->x;
	dy = player->ad_y - player->y;
	if (dx <= dy)
	{
		shared->map[player->y][player->x] = '.';
		player->x += 1;
		shared->map[player->y][player->x] = player->team;
	}
	else
	{
		shared->map[player->y][player->x] = '.';
		player->y += 1;
		shared->map[player->y][player->x] = player->team;
	}
}

void	case_6(t_share *shared, t_player *player)
{
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
		shared->map[player->y][player->x] = '.';
		player->x -= 1;
		shared->map[player->y][player->x] = player->team;
	}
	else
	{
		shared->map[player->y][player->x] = '.';
		player->y += 1;
		shared->map[player->y][player->x] = player->team;
	}
}

void	case_8(t_share *shared, t_player *player)
{	
	shared->map[player->y][player->x] = '.';
	player->x -= 1;
	shared->map[player->y][player->x] = player->team;	
}
