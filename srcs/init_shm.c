/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/01 00:32:15 by gpetrov           #+#    #+#             */
/*   Updated: 2014/06/01 00:42:36 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/shm.h>
#include <stdio.h>
#include "lemipc.h"

void		init_shm_sub(t_share *shared)
{
	t_data	*data;

	data = init_data();
	shared = shmat(data->shm_id, (void *)0, 0);
	if (shared == (t_share *)-1)
		exit_error("shmat error1\n");
	printf("Creating GameP\n");
	team_handle_init(shared);
	shared->nb_team = 0;
	fill_map(shared);
	shared->end = FALSE;
	shared->nb_player = 0;
	shared->kill = 0;
	//create_sem();
	if (shmdt(shared) == -1)
		exit_error("shmdt() error\n");
}

void		initshm(t_share *shared)
{
	char		*pwd;
	t_data		*data;

	data = init_data();
	pwd = getwd(NULL);
	data->key = ftok(pwd, 0);
	if ((data->shm_id = shmget(data->key, sizeof(struct s_share), 0666)) == -1)
	{
		if ((data->shm_id = shmget(data->key,
						sizeof(t_share), 0666 | IPC_CREAT)))
			init_shm_sub(shared);
		else
			exit_error("FUCK YOU BITCH I WANT TO EAT JAPANESE\n");
	}
	else
		printf("OK\n");
}
