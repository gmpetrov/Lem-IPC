/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/27 14:51:19 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/31 19:27:39 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUC_H
# define TRUE	1
# define FALSE	-1
# define WIDTH	1000
# define HEIGHT	800
# define MAX_TEAM 100
# define MAX_SIZE 1024
# include "lemipc.h"

typedef struct		s_share
{
	char			map[HEIGHT][WIDTH];
	int				first;
	char			team[MAX_TEAM + 1];
	int				nb_team;
	int				nb_player;
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

typedef struct		s_win
{
	void			*mlx;
	void			*win;
	struct s_img	*img;
}					t_win;

typedef struct		s_img
{
	void			*img;
	void			*load_ptr;
	char			*data;
	int				bpp;
	int				size_line;
	int				endian;
	int				x;
	int				y;
}					t_img;

typedef struct		s_data
{
	int				key;
	int				shm_id;
	int				sem_id;
	int				array[WIDTH * HEIGHT];
}					t_data;

#endif
