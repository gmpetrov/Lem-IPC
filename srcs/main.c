/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/26 19:21:18 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/29 14:44:33 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include "lemipc.h"

void	lock(void)
{
	int				sem_id;
	struct	sembuf	buf;

	sem_id = semget(KEY, 1, 0666);
	if (sem_id == -1)
	{
		sem_id = semget(KEY, 1, 0666 | IPC_CREAT);
		semctl(sem_id, SETVAL, 1);
	}
	buf.sem_num = 0;
	buf.sem_op = -1;
	buf.sem_flg = 0;
	semop(sem_id, &buf, 0);
}

void	unlock(void)
{
	struct sembuf	buf;
	int				sem_id;

	sem_id = semget(KEY, 1, 0666);
	buf.sem_num = 0;
	buf.sem_op = 1;
	buf.sem_flg = 0;
	semop(sem_id, &buf, 0);
}
void	print_map(char map[HEIGHT][WIDTH], t_share *shared)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	usleep(1000000);
	system("clear");
	while (i < HEIGHT)
	{
		while (j < WIDTH)
		{
			if (map[i][j] == '.')
			{
				ft_putstr("\033[33m\u25CE\033[0m");
				write(1, " ", 1);
			}
			else if (map[i][j] == shared->team[0])
			{		
				ft_putstr("\033[32m\u25CD\033[0m");
				write(1, " ", 1);
			}
			else if (map[i][j] == shared->team[1])
			{
				ft_putstr("\033[31m\u25CD\033[0m");
				write(1, " ", 1);
			}
			write(1, " ", 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
		j = 0;
	}
}

int		init_shm(t_share *shared)
{
	int			shm_id;

	if ((shm_id = shmget(KEY, sizeof(shared), 0644 | IPC_CREAT)) == -1)
		exit_error("shmget() error\n");
	shared = shmat(shm_id, (void *)0, 0);
	if (shared == (t_share *)-1)
		exit_error("shmat error\n");
	if (shared->first == TRUE)
	{
		printf("OK\n");
		lock();
		print_map(shared->map, shared);
		unlock();
	}
	else
	{
		printf("Creating GameP\n");
		team_handle_init(shared);
		shared->nb_team = 0;
		fill_map(shared);
		print_map(shared->map, shared);
		shared->end = FALSE;
		shared->first = TRUE;
	}
	if (shmdt(shared) == -1)
		exit_error("shmdt() error\n");
	return (shm_id);
}

void	register_team(t_share *shared, t_player *player)
{
	int		i;

	i = 0;
	while (i < MAX_TEAM)
	{
		if (shared->team[i] == player->team)
		{
			printf("%s\n", shared->team);
			return ;
		}
		else if (shared->team[i] == '.')
		{
			shared->team[i] = player->team;
			shared->nb_team++;
			printf("nb of team : %d %s\n", shared->nb_team, shared->team);
			return ;
		}
		i++;
	}
	printf("%s\n", shared->team);
}

void	put_player_on_map(t_share *shared, t_player *player)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < HEIGHT)
	{
		while (i < WIDTH)
		{
			if (shared->map[j][i] == '.')
			{
				shared->map[j][i] = player->team;
				player->x = i;
				player->y = j;
				return ;
			}
			i++;
		}
		i = 0;
		j++;
	}
}

void	create_player(t_share *shared, int shm_id, t_player *player)
{
	int		i;

	i = 0;
	lock();
	shared = shmat(shm_id, (void *)0, 0);
	register_team(shared, player);
	put_player_on_map(shared, player);
	if (shmdt(shared) == -1)
		exit_error("shmdt() error\n");
	unlock();
}

void	test(t_share *shared, int shm_id)
{
	shared = shmat(shm_id, (void *)0, 0);

	shared->map[5][5] = '1';
	print_map(shared->map, shared);

	if (shmdt(shared) == -1)
		exit_error("shmdt() error\n");
}
/*
void	analyze(t_share *shared, t_player *player)
{
	check_if_dead(shared, player);
}
*/

void	move(t_share *shared, t_player *player)
{
	if ((player->x + 1 < WIDTH) && shared->map[player->y][player->x + 1] == '.')
	{
		shared->map[player->y][player->x] = '.';
		player->x++;
		shared->map[player->y][player->x] = player->team;
	}
	else if (player->x + 1 == WIDTH && (player->y + 1 < HEIGHT))
	{	
		shared->map[player->y][player->x] = '.';
		player->x = 0;
		player->y++;
		shared->map[player->y][player->x] = player->team;
	}
	else
		shared->end = TRUE;
}

void	send_pos(t_player *player)
{
	/* TEST msgq */

	t_msgbuf	buf;
	int			msg_id;

	(void)player;
	if ((msg_id = msgget(KEY, 0666 | IPC_CREAT)) < 0)
		exit_error("msgget() error\n");
	buf.mtype = (int)player->team;
	ft_strncpy(buf.mtext, "salut", 5);
	if (msgsnd(msg_id, &buf, 5, IPC_NOWAIT) < 0)
		exit_error("msgsnd() error\n");

}

void	recv_pos(t_player *player)
{
	int			msg_id;
	t_msgbuf	buf;

	if ((msg_id = msgget(KEY, 0666)) < 0)
		exit_error("msgget() error\n");
	if (msgrcv(msg_id, &buf, MAX_SIZE, (int)player->team, 0) < 0)
		exit_error("msgrcv() error\n");	
	printf("\n recv BUF : %s\n", buf.mtext);
}

void	play(t_share *shared, int shm_id, t_player *player)
{
	lock();
	player->danger = FALSE;
	player->attack = FALSE;
	shared = shmat(shm_id, (void *)0, 0);
	while (shared->end == FALSE)
	{
		move(shared, player);
		print_map(shared->map, shared);
	}
	if (shmdt(shared) == -1)
		exit_error("shmdt() error\n");
	unlock();
}

int		main(int ac, char **av)
{
//	char		cross = ❌;
//	 printf("%d", cross);
//	ft_putstr("\u05D4\n");
//	ft_putstr("\u272C\n");
//	ft_putstr("\033[32mlemipc \033[0m\n");
	t_share		shared;
	t_player	player;
	int			shm_id;

	if (ac != 2)
		exit_error("[USAGE] - ./lemipc <team>\n");
	player.team = av[1][0];
	printf("%c\n", player.team);
	shm_id = init_shm(&shared);
	create_player(&shared, shm_id, &player);
	play(&shared, shm_id, &player);
	return (0);
}
