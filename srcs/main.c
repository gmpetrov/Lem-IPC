/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/26 19:21:18 by gpetrov           #+#    #+#             */
/*   Updated: 2014/06/01 23:35:52 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/stat.h>
#include "lemipc.h"

void	move(t_share *shared, t_player *player)
{
	if (player->ad_x < player->x && player->ad_y < player->y)
		case_1(shared, player);
	else if (player->ad_x == player->x && player->ad_y < player->y)
		case_2(shared, player);
	else if (player->ad_x > player->x && player->ad_y < player->y)
		case_3(shared, player);
	else if (player->ad_x > player->x && player->ad_y == player->y)
		case_4(shared, player);
	else if (player->ad_x > player->x && player->ad_y > player->y)
		case_5(shared, player);
	else if (player->ad_x == player->x && player->ad_y > player->y)
		case_6(shared, player);
	else if (player->ad_x < player->x && player->ad_y > player->y)
		case_7(shared, player);
	else if (player->ad_x < player->x && player->ad_y == player->y)
		case_8(shared, player);
}

void	find_enemy(t_share *shared, t_player *player)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < HEIGHT)
	{
		while (i < WIDTH)
		{
			if (shared->map[j][i] != player->team && shared->map[j][i] != '.')
			{
				player->ad_x = i;
				player->ad_y = j;
				player->attack = TRUE;
				return ;
			}
			i++;
		}
		i = 0;
		j++;
	}
}

void	play(t_share *shared, t_player *player)
{
	t_data	*data;

	data = init_data();
	shared = shmat(data->shm_id, (void *)0, 0);
	init_play(shared, player);
	data = init_data();
	while (shared->end == FALSE)
		play_loop(shared, player);
	end(shared, player);
}

int		main(int ac, char **av)
{
	t_share		shared;
	t_player	player;

	if (ac != 2)
		exit_error("[USAGE] - ./lemipc <team>\n");
	player.team = av[1][0];
	printf("%c\n", player.team);
	initshm(&shared);
	create_player(&shared, &player);
	play(&shared, &player);
	return (0);
}
