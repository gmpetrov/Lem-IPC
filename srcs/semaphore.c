/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/01 00:01:01 by gpetrov           #+#    #+#             */
/*   Updated: 2014/06/01 00:03:17 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/sem.h>
#include "lemipc.h"

char			is_locked(void)
{
	int			val;

	val = semctl(sem_init(), 0, GETVAL);
	if (val == -1)
		exit_error("semctl() error\n");
	return (val);
}

int			sem_init(void)
{
	static int		semid = 0;
	t_data			*data;

	data = init_data();
	if (semid == 0)
	{
		if ((semid = semget(data->key, 1, IPC_CREAT | 0666)) == -1)
			exit_error("semget() error\n");
		if (semctl(semid, 0, SETVAL, 1) == -1)
			exit_error("semctl() error\n");
	}
	return (semid);
}

void	lock(void)
{
	int		val;

	if (is_locked())
		return ;
	val = semctl(sem_init(), 0, SETVAL, 1);
	if (val == -1)
		exit_error("semctl() error\n");
}

void	unlock(void)
{
	int		val;

	if (!is_locked())
		return ;
	val = semctl(sem_init(), 0, SETVAL, 0);
	if (val == -1)
		exit_error("semctl() error\n");
}

void		create_sem(void)
{
	t_data	*data;

	data = init_data();
	if ((data->sem_id = semget(data->key, HEIGHT * WIDTH,
					0666 | IPC_CREAT | IPC_EXCL)) == -1)
		exit_error("semget() error\n");
	if (semctl(data->sem_id, 1, SETALL, data->array) == -1)
		exit_error("semctl() error\n");
	printf("Semaphores Created\n");
}
