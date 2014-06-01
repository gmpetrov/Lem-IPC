/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/01 00:01:01 by gpetrov           #+#    #+#             */
/*   Updated: 2014/06/01 23:00:43 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/sem.h>
#include "lemipc.h"

void	lock(void)
{
	struct sembuf	actions[2];
	t_data			*data;

	data = init_data();
	actions[0].sem_num = 0;
	actions[0].sem_flg = SEM_UNDO;
	actions[0].sem_op = 0;
	actions[1].sem_num = 1;
	actions[1].sem_flg = SEM_UNDO;
	actions[1].sem_op = +1;
	if (semop(data->sem_id, actions, 2) == -1)
		exit_error("semop() error\n");
}

void	unlock(void)
{
	struct sembuf	actions[1];
	t_data			*data;

	data = init_data();
	actions[0].sem_num = 1;
	actions[0].sem_flg = SEM_UNDO;
	actions[0].sem_op = -1;
	if (semop(data->sem_id, actions, 1) == -1)
		exit_error("semop() error\n");
}

void	set_sem_value(void)
{
	union semun		init_val;
	t_data			*data;

	data = init_data();
	init_val.val = 0;
	if (semctl(data->sem_id, 0, SETVAL, init_val) == -1)
		exit_error("semctl() error\n");
	if (semctl(data->sem_id, 1, SETVAL, init_val) == -1)
		exit_error("semctl() error\n");
}

void	create_sem(void)
{
	t_data	*data;

	data = init_data();
	if ((data->sem_id = semget(data->key, 2,
					0666 | IPC_CREAT | IPC_EXCL)) == -1)
		exit_error("semget() error\n");
	set_sem_value();
	printf("Semaphores Created\n");
}
