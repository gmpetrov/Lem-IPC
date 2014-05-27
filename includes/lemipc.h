/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemipc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/26 19:20:20 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/27 19:36:15 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIPC_H
# define LEMIPC_H

# define WIDTH	20
# define HEIGHT	10
# define KEY	424242

# include "libft.h"
# include "struct.h"

/*
**	Prototypes
*/

void	fill_map(t_share *shared);
void	print_map(char **map);
char	**create_map(void);

#endif
