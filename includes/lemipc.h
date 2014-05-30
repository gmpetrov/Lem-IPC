/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemipc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/26 19:20:20 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/30 18:15:26 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIPC_H
# define LEMIPC_H

# define KEY_ESC	65307
# include "libft.h"
# include "struct.h"


t_data	*init_data(void);

/*
**	Prototypes
*/

void	print_map(char map[HEIGHT][WIDTH], t_share *shared);
void	create_player(t_share *shared, t_player *player);

/*
**	tools.c
*/

void	exit_error(char *msg);

/*
**	init.c
*/

char	**create_map(void);
void	fill_map(t_share *shared);
void	team_handle_init(t_share *shared);
int		sem_init(void);
char	is_locked(void);

/*
**	case.c
*/

void	case_1(t_share *shared, t_player *player);
void	case_2(t_share *shared, t_player *player);
void	case_3(t_share *shared, t_player *player);
void	case_4(t_share *shared, t_player *player);
void	case_5(t_share *shared, t_player *player);
void	case_6(t_share *shared, t_player *player);
void	case_7(t_share *shared, t_player *player);
void	case_8(t_share *shared, t_player *player);


void	*eb_mlx(int shm_id, t_share *shared);
int		eb_mlx_key_hook(int keycode);
int		eb_expose_hook(t_share *shared);
void	eb_clean_map(t_img *img);
t_win	*env_init(void);
t_img	*img_init(void);
int		color_norm(int red, int green, int blue);
int		color_life(int life);
void	eb_put_pixel_to_img(t_img *img, int x, int y, int color);
int		eb_loop_hook(t_share *shared);

#endif
