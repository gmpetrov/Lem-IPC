/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/01 23:06:05 by gpetrov           #+#    #+#             */
/*   Updated: 2014/06/01 23:31:01 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "lemipc.h"

void	end(t_share *shared, t_player *player)
{
	t_data	*data;

	data = init_data();
	lock();
	if (shared->end == TRUE && shared->nb_player == 0)
	{
		shared->winner = player->team;
		unlock();
		if (shmdt(shared) == -1)
			exit_error("shmdt() error\n");
		shmctl (data->shm_id, IPC_RMID, 0);
		semctl(data->sem_id, 0, IPC_RMID, NULL);
	}
	else
	{
		if (shmdt(shared) == -1)
			exit_error("shmdt() error FUCK\n");
	}
}

void	play_loop(t_share *shared, t_player *player)
{
	usleep(TIME);
	lock();
	if (shared->kill == TRUE)
	{
		if (shared->nb_team == 1)
		{
			unlock();
			shared->end = TRUE;
		}
	}
	if (check_if_dead(shared, player) == -1)
	{
		shared->kill = TRUE;
		unlock();
		return ;
	}
	find_enemy(shared, player);
	move(shared, player);
	unlock();
}
