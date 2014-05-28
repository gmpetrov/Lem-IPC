/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/27 14:51:19 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/28 17:59:37 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUC_H
# define TRUE	1
# define FALSE	-1
# define WIDTH	20
# define HEIGHT	10
# define MAX_TEAM 100
# include "lemipc.h"

typedef struct		s_share
{
	char			map[HEIGHT][WIDTH];
	int				first;
	char			team[MAX_TEAM + 1];
	int				nb_team;
}					t_share;

typedef struct		s_player
{
	char			team;			
}					t_player;

#endif
