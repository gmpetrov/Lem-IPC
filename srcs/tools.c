/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/29 14:33:11 by gpetrov           #+#    #+#             */
/*   Updated: 2014/06/01 00:22:58 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdio.h>
#include "lemipc.h"

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
