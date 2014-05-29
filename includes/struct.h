/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/27 14:51:19 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/29 15:56:19 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUC_H
# define TRUE	1
# define FALSE	-1
# define WIDTH	20
# define HEIGHT	10
# define MAX_TEAM 100
# define MAX_SIZE 1024
# include "lemipc.h"

typedef struct		s_share
{
	char			map[HEIGHT][WIDTH];
	int				first;
	char			team[MAX_TEAM + 1];
	int				nb_team;
	int				end;
}					t_share;

typedef struct		s_player
{
	char			team;
	int				x;
	int				y;
	int				danger;
	int				attack;
	int				ad_x;
	int				ad_y;
}					t_player;

typedef struct		s_msgbuf
{
    long			mtype;
    char			mtext[MAX_SIZE];
}					t_msgbuf;

#endif
