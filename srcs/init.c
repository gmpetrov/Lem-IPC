/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/29 14:37:21 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/29 16:04:07 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
