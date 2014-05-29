/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/29 18:55:19 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/29 20:08:52 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include "lemipc.h"

int		init_shm(t_share *shared)
{
	int	shm_id;

	if ((shm_id = shmget(KEY, sizeof(shared), 0644 | IPC_CREAT)) == -1)
		perror("shmget() error\n");
	return (shm_id);
}

int		main(void)
{
	t_share		shared;
	int			shm_id;

	shm_id = init_shm(&shared);
	printf("graph\n");
	eb_mlx(shm_id, &shared);
	return (0);
}
