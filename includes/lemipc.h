/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemipc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/26 19:20:20 by gpetrov           #+#    #+#             */
/*   Updated: 2014/06/01 19:08:22 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIPC_H
# define LEMIPC_H

# define KEY_ESC	65307
# define TIME		10000
# include "libft.h"
# include "struct.h"

/*
**	Prototypes
*/

/*
**	main.c
*/

void	move(t_share *shared, t_player *player);
void	find_enemy(t_share *shared, t_player *player);
void	play(t_share *shared, t_player *player);

/*
**	tools.c
*/

int		check_nb_team(t_share *shared, t_player *player);
void	exit_error(char *msg);
t_data	*init_data(void);
void	put_player_on_map(t_share *shared, t_player *player);

/*
**	init.c
*/

char	**create_map(void);
void	fill_map(t_share *shared);
void	team_handle_init(t_share *shared);
void	create_player(t_share *shared, t_player *player);
void	register_team(t_share *shared, t_player *player);

/*
**	init_shm.c
*/
void	initshm(t_share *shared);
void	init_shm_sub(t_share *shared);

/*
**	check_if_dead.c
*/

int		check_if_dead(t_share *shared, t_player *player);
void	dead_case_1_to_4(t_share *shared, t_player *player, int *nb);
void	dead_case_5_to_8(t_share *shared, t_player *player, int *nb);

/*
**	semaphore.c
*/

void	create_sem(void);
void	lock(void);
void	unlock(void);
int		sem_init(void);
char	is_locked(void);

/*
**	msgq.c
*/
void	recv_pos(t_player *player);
void	send_pos(t_player *player);

/*
**	case.c
*/

void	case_1(t_share *shared, t_player *player);
void	case_2(t_share *shared, t_player *player);
void	case_3(t_share *shared, t_player *player);
void	case_4(t_share *shared, t_player *player);
/*
**	case2.c
*/
void	case_5(t_share *shared, t_player *player);
void	case_6(t_share *shared, t_player *player);
void	case_7(t_share *shared, t_player *player);
void	case_8(t_share *shared, t_player *player);

/*
**	graph/
*/

/*
**	draw_player.c
*/

void	draw_player_1(t_img *img, int	i, int j);
void	draw_player_2(t_img *img, int	i, int j);
void	draw_player_3(t_img *img, int	i, int j);
void	draw_player_4(t_img *img, int	i, int j);
void	draw_player_5(t_img *img, int	i, int j);

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
