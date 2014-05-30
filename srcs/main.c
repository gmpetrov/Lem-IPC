/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/26 19:21:18 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/31 00:03:41 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include "lemipc.h"

t_data			*init_data(void)
{
	static t_data		*data = NULL;

	if (data == NULL)
		data = (t_data *)malloc(sizeof(t_data));
	return (data);
}

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

void		create_sem(void)
{
	t_data	*data;

	data = init_data();
	if ((data->sem_id = semget(data->key, HEIGHT * WIDTH, 0666 | IPC_CREAT | IPC_EXCL)) == -1)
		exit_error("semget() error\n");
	if (semctl(data->sem_id, 1, SETALL, data->array) == -1)
		exit_error("semctl() error\n");
	printf("Semaphores Created\n");
}

void		init_shm(t_share *shared)
{
	char		*pwd;
	t_data		*data;

	data = init_data();
	pwd = getwd(NULL);
	data->key = ftok(pwd, 0);
	printf("KEY = %d\n", data->key);
	size_t size = sizeof(t_share);
	ft_putnbr(size);
	if ((data->shm_id = shmget(data->key, sizeof(struct s_share), 0666)) == -1)
	{
		if ((data->shm_id = shmget(data->key, sizeof(t_share), 0666 | IPC_CREAT)))
		{
			ft_putnbr(data->shm_id);
			ft_putstr("\n\t");
			shared = shmat(data->shm_id, (void *)0, 0);
			if (shared == (t_share *)-1)
				exit_error("shmat error1\n");
			printf("Creating GameP\n");
			team_handle_init(shared);
			shared->nb_team = 0;
			fill_map(shared);
			//		print_map(shared->map, shared);
			shared->end = FALSE;
			shared->first = TRUE;
			//create_sem();
			if (shmdt(shared) == -1)
				exit_error("shmdt() error\n");
		}
		else
			exit_error("FUCK YOU BITCH I WANT TO EAT JAPANESE\n");
	}
	else
		printf("OK\n");
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
	/*
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
	*/
}

void	create_player(t_share *shared, t_player *player)
{
	int		i;
	t_data	*data;

	data = init_data();
	i = 0;
//	lock();
	shared = shmat(data->shm_id, (void *)0, 0);
	register_team(shared, player);
	put_player_on_map(shared, player);
	if (shmdt(shared) == -1)
		exit_error("shmdt() error\n");
//	unlock();
}

void	test(t_share *shared, int shm_id)
{
	shared = shmat(shm_id, (void *)0, 0);

	shared->map[5][5] = '1';
	print_map(shared->map, shared);

	if (shmdt(shared) == -1)
		exit_error("shmdt() error\n");
}

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

void	send_pos(t_player *player)
{
	/* TEST msgq */

	t_msgbuf	buf;
	int			msg_id;
	t_data		*data;

	data = init_data();
	(void)player;
	if ((msg_id = msgget(data->key, 0666 | IPC_CREAT)) < 0)
		exit_error("msgget() error\n");
	buf.mtype = player->team;
	ft_strncpy(buf.mtext, "salut", 5);
	if (msgsnd(msg_id, &buf, 5, IPC_NOWAIT) < 0)
		exit_error("msgsnd() error\n");

}

void	recv_pos(t_player *player)
{
	int			msg_id;
	t_msgbuf	buf;
	t_data		*data;
	int			r;

	data = init_data();
	if ((msg_id = msgget(data->key, 0666)) < 0)
	{
		return ;
	//		exit_error("msgget() error\n");
	}
	if ((r = msgrcv(msg_id, &buf, MAX_SIZE, player->team, IPC_NOWAIT)) < 0)
		exit_error("msgrcv() error\n");
	if (r > 0)
	{
		printf("r = %d\n", r);
		printf("\n recv BUF : %s\n", buf.mtext);
	}
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

int		check_if_dead(t_share *shared, t_player *player)
{
	int		nb;

	nb = 0;
	if (((player->x - 1 >= 0) && (player->y - 1 >= 0)) &&
			(shared->map[player->y - 1][player->x - 1] != '.' &&
			 shared->map[player->y - 1][player->x - 1] != player->team))
		nb++;
	if ((player->y - 1 >= 0) && (shared->map[player->y - 1][player->x] != '.' &&
			shared->map[player->y - 1][player->x] != player->team))
		nb++;
	if (((player->x + 1 < WIDTH) && (player->y - 1 >= 0)) &&
			(shared->map[player->y - 1][player->x - 1] != '.' &&
			 shared->map[player->y - 1][player->x - 1] != player->team))
		nb++;
	if ((player->x + 1 < WIDTH) && (shared->map[player->y][player->x + 1] != '.' &&
				shared->map[player->y][player->x + 1] != player->team))
		nb++;
	if ((player->x + 1 < WIDTH && player->y + 1 < HEIGHT) &&
			(shared->map[player->y + 1][player->x + 1] != '.' &&
			 shared->map[player->y + 1][player->x + 1] != player->team))
		nb++;
	if ((player->y + 1 < HEIGHT) && (shared->map[player->y + 1][player->x] != '.' &&
				shared->map[player->y + 1][player->x] != player->team))
		nb++;
	if (((player->y + 1 < HEIGHT) && (player->x - 1 >= 0)) &&
			(shared->map[player->y + 1][player->x - 1] != '.' &&
			shared->map[player->y + 1][player->x - 1] != player->team))
		nb++;
	if ((player->x - 1 >= 0) && (shared->map[player->y][player->x - 1] != '.' &&
				shared->map[player->y][player->x - 1] != player->team))
		nb++;
	if (nb >= 2)
	{
		shared->map[player->y][player->x] = '.';
		return (-1);
	}
	return (0);
}

void	find_closest_enemy(t_share *shared, t_player *player )
{
	int		i;

	i = 1;
	while (i < WIDTH)
	{
		if (((player->x - i >= 0) && (player->y - i >= 0)) &&
				(shared->map[player->y - i][player->x - i] != '.' &&
				 shared->map[player->y - i][player->x - i] != player->team))
		{
			player->ad_x = player->x - i;
			player->ad_y = player->y - i;
			return ;
		}
		if ((player->y - i >= 0) && (shared->map[player->y - i][player->x] != '.' &&
					shared->map[player->y - i][player->x] != player->team))	
		{
			player->ad_x = player->x;
			player->ad_y = player->y - i;
			return ;
		}
		if (((player->x + i < WIDTH) && (player->y - i >= 0)) &&
				(shared->map[player->y - i][player->x - i] != '.' &&
				 shared->map[player->y - i][player->x - i] != player->team))	
		{
			player->ad_x = player->x + i;
			player->ad_y = player->y - i;
			return ;
		}
		if ((player->x + i < WIDTH) && (shared->map[player->y][player->x + i] != '.' &&
					shared->map[player->y][player->x + i] != player->team))	
		{
			player->ad_x = player->x + i;
			player->ad_y = player->y;
			return ;
		}
		if ((player->x + i < WIDTH && player->y + i < HEIGHT) &&
				(shared->map[player->y + i][player->x + i] != '.' &&
				 shared->map[player->y + i][player->x + i] != player->team))	
		{
			player->ad_x = player->x + i;
			player->ad_y = player->y + i;
			return ;
		}
		if ((player->y + i < HEIGHT) && (shared->map[player->y + i][player->x] != '.' &&
					shared->map[player->y + i][player->x] != player->team))	
		{
			player->ad_x = player->x;
			player->ad_y = player->y + i;
			return ;
		}
		if (((player->y + i < HEIGHT) && (player->x - i >= 0)) &&
				(shared->map[player->y + i][player->x - i] != '.' &&
				 shared->map[player->y + i][player->x - i] != player->team))	
		{
			player->ad_x = player->x - i;
			player->ad_y = player->y + i;
			return ;
		}
		if ((player->x - i >= 0) && (shared->map[player->y][player->x - i] != '.' &&
					shared->map[player->y][player->x - i] != player->team))	
		{
			player->ad_x = player->x - i;
			player->ad_y = player->y;
			return ;
		}
		i++;
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
	while (shared->end == FALSE)
	{
		if (check_if_dead(shared, player) == -1)
		{
			break ;
		}
		send_pos(player);
		recv_pos(player);
		find_enemy(shared, player);
		move(shared, player);
	}
	if (shmdt(shared) == -1)
		exit_error("shmdt() error\n");
//	shmctl (data->shm_id, IPC_RMID, 0);
}

int		main(int ac, char **av)
{
	t_share		shared;
	t_player	player;

	if (ac != 2)
		exit_error("[USAGE] - ./lemipc <team>\n");
	player.team = av[1][0];
	printf("%c\n", player.team);
	init_shm(&shared);
	create_player(&shared, &player);
	play(&shared, &player);
	return (0);
}
