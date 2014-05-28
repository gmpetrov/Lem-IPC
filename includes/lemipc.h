/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemipc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/26 19:20:20 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/28 18:00:56 by gpetrov          ###   ########.fr       */
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

void	fill_map(t_share *shared);
void	print_map(char map[HEIGHT][WIDTH]);
char	**create_map(void);
void	create_player(t_share *shared, int shm_id, t_player *player);

#endif
