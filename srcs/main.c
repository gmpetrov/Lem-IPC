/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/26 19:21:18 by gpetrov           #+#    #+#             */
/*   Updated: 2014/06/01 01:06:10 by gpetrov          ###   ########.fr       */
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
			//	send_pos(player);
				player->attack = TRUE;
				return ;
			}
			i++;
		}
		i = 0;
		j++;
	}
}

void	play(t_share *shared,  t_player *player)
{
	t_data	*data;

	data = init_data();
	player->danger = FALSE;
	player->attack = FALSE;
	player->ad_x = 200;
	player->ad_y = 200;
	shared = shmat(data->shm_id, (void *)0, 0);
	shared->nb_player++;
	sleep(2);
	while (shared->end == FALSE)
	{
		usleep(TIME);
		if (shared->kill == TRUE)
		{
			if (shared->nb_team == 1)
				shared->end = TRUE;
		}
		if (check_if_dead(shared, player) == -1)
		{
			shared->kill = TRUE;
			break ;
		}
//		send_pos(player);
//		recv_pos(player);
		find_enemy(shared, player);
		move(shared, player);
	}
	shared->nb_player--;
	if (shared->end == TRUE && shared->nb_player == 0)
	{
		shared->winner = player->team;
		if (shmdt(shared) == -1)
			exit_error("shmdt() error\n");
		shmctl (data->shm_id, IPC_RMID, 0);
	}
	else 
	{	
		if (shmdt(shared) == -1)
		exit_error("shmdt() error\n");
	}
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
