/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/26 19:21:18 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/28 16:36:14 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include "lemipc.h"

void	exit_error(char *msg)
{
	printf("\033[31m%s\033[0m", msg);
	exit(0);
}

char	**create_map(void)
{
	char	**map;
	int		i;

	i = 0;
	map = (char **)malloc(sizeof(char *) * (HEIGHT + 1));
	while (i < HEIGHT)
	{
		map[i] = (char *)malloc(sizeof(char) * (WIDTH + 1));
		map[i][WIDTH] = 0;
		i++;
	}
	map[HEIGHT] = NULL;
	return (map);
}

void	print_map(char map[HEIGHT][WIDTH])
{
	int		i;
	int		j;

	i = 0;
	j = 0;
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
			else if (map[i][j] == '1')
			{		
				ft_putstr("\033[32m\u25CD\033[0m");
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

void	fill_map(t_share *shared)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < HEIGHT)
	{
		while (j < WIDTH)
		{
			shared->map[i][j] = '.';
			j++;
		}
		i++;
		j = 0;
	}

}

void	init_shm(t_share *shared)
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
		printf("%d\n", shared->fuck);
		create_player(shared);
		print_map(shared->map);
	}
	else
	{
		printf("Creating MAP\n");
//		shared->map = create_map();
		fill_map(shared);
		create_player(shared);
		print_map(shared->map);
		shared->fuck = 42;
		shared->first = TRUE;
	}
	if (shmdt(shared) == -1)
		exit_error("shmdt() error\n");
}

void	create_player(t_share *shared)
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
				shared->map[j][i] = '1';
				return ;
			}
			i++;
		}
		i = 0;
		j++;
	}
}

int		main(int ac, char **av)
{
//	char		cross = ❌;
//	 printf("%d", cross);
//	ft_putstr("\u05D4\n");
//	ft_putstr("\u272C\n");
//	ft_putstr("\033[32mlemipc \033[0m\n");
	t_share		shared;

	(void)av;
	if (ac != 2)
		exit_error("[USAGE] - ./lemipc <team>\n");
	init_shm(&shared);
	create_player(&shared);
	return (0);
}
