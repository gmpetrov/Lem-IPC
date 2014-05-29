/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemipc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/26 19:20:20 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/29 16:45:48 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIPC_H
# define LEMIPC_H


# define KEY	424242

# include "libft.h"
# include "struct.h"

/*
**	Prototypes
*/

void	print_map(char map[HEIGHT][WIDTH], t_share *shared);
void	create_player(t_share *shared, int shm_id, t_player *player);

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

#endif
