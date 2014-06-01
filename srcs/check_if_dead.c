/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_dead.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/01 00:19:16 by gpetrov           #+#    #+#             */
/*   Updated: 2014/06/01 22:21:13 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

void	dead_case_1_to_4(t_share *shared, t_player *player, int *nb)
{
	if (((player->x - 1 >= 0) && (player->y - 1 >= 0)) &&
			(shared->map[player->y - 1][player->x - 1] != '.' &&
			shared->map[player->y - 1][player->x - 1] != player->team))
		*nb += 1;
	if ((player->y - 1 >= 0) && (shared->map[player->y - 1][player->x]
		!= '.' && shared->map[player->y - 1][player->x] != player->team))
		*nb += 1;
	if (((player->x + 1 < WIDTH) && (player->y - 1 >= 0)) &&
			(shared->map[player->y - 1][player->x + 1] != '.' &&
			shared->map[player->y - 1][player->x + 1] != player->team))
		*nb += 1;
	if ((player->x + 1 < WIDTH) && (shared->map[player->y][player->x + 1]
		!= '.' && shared->map[player->y][player->x + 1] != player->team))
		*nb += 1;
}

void	dead_case_5_to_8(t_share *shared, t_player *player, int *nb)
{
	if ((player->x + 1 < WIDTH && player->y + 1 < HEIGHT) &&
			(shared->map[player->y + 1][player->x + 1] != '.' &&
			shared->map[player->y + 1][player->x + 1] != player->team))
		*nb += 1;
	if ((player->y + 1 < HEIGHT) && (shared->map[player->y + 1][player->x]
		!= '.' && shared->map[player->y + 1][player->x] != player->team))
		*nb += 1;
	if (((player->y + 1 < HEIGHT) && (player->x - 1 >= 0)) &&
			(shared->map[player->y + 1][player->x - 1] != '.' &&
			shared->map[player->y + 1][player->x - 1] != player->team))
		*nb += 1;
	if ((player->x - 1 >= 0) && (shared->map[player->y][player->x - 1]
		!= '.' && shared->map[player->y][player->x - 1] != player->team))
		*nb += 1;
}

int		check_if_dead(t_share *shared, t_player *player)
{
	int		nb;

	nb = 0;
	dead_case_1_to_4(shared, player, &nb);
	dead_case_5_to_8(shared, player, &nb);
	if (nb >= 2)
	{
		shared->nb_player--;
		shared->map[player->y][player->x] = '.';
		if (check_nb_team(shared, player) == TRUE)
			shared->nb_team--;
		return (-1);
	}
	return (0);
}
