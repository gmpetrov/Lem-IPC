/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/29 14:37:21 by gpetrov           #+#    #+#             */
/*   Updated: 2014/06/01 00:29:03 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/shm.h>
#include <stdio.h>
#include "lemipc.h"

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

void	team_handle_init(t_share *shared)
{
	int		i;

	i = 0;
	while (i < MAX_TEAM)
	{
		shared->team[i] = '.';
		i++;
	}
	shared->team[MAX_TEAM] = 0;
}

void	create_player(t_share *shared, t_player *player)
{
	int		i;
	t_data	*data;

	data = init_data();
	i = 0;
	shared = shmat(data->shm_id, (void *)0, 0);
	register_team(shared, player);
	put_player_on_map(shared, player);
	if (shmdt(shared) == -1)
		exit_error("shmdt() error\n");
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
