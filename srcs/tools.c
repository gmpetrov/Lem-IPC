/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/29 14:33:11 by gpetrov           #+#    #+#             */
/*   Updated: 2014/06/01 23:05:08 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <stdio.h>
#include "lemipc.h"

void		init_play(t_share *shared, t_player *player)
{
	t_data	*data;

	data = init_data();
	player->danger = FALSE;
	player->attack = FALSE;
	player->ad_x = WIDTH / 2;
	player->ad_y = HEIGHT / 2;
	shared = shmat(data->shm_id, (void *)0, 0);
	shared->nb_player++;
	data->sem_id = shared->sem_id;
	sleep(2);
}

void		exit_error(char *msg)
{
	printf("\033[31m%s\033[0m", msg);
	exit(0);
}

t_data		*init_data(void)
{
	static t_data		*data = NULL;

	if (data == NULL)
		data = (t_data *)malloc(sizeof(t_data));
	return (data);
}

void		put_player_on_map(t_share *shared, t_player *player)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	srand(time(NULL));
	while (42)
	{
		i = rand() % WIDTH;
		j = rand() % HEIGHT;
		if (shared->map[j][i] == '.')
		{
			player->x = i;
			player->y = j;
			shared->map[j][i] = player->team;
			return ;
		}
	}
}

int			check_nb_team(t_share *shared, t_player *player)
{
	int		i;
	int		j;
	int		counter;

	i = 0;
	j = 0;
	counter = 0;
	while (j < HEIGHT)
	{
		while (i < WIDTH)
		{
			if (shared->map[j][i] == player->team)
			{
				counter++;
				return (FALSE);
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (TRUE);
}
