/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msgq.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/01 00:05:49 by gpetrov           #+#    #+#             */
/*   Updated: 2014/06/01 00:09:09 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/msg.h>
#include <stdio.h>
#include "lemipc.h"

void	send_pos(t_player *player)
{
	t_msgbuf	buf;
	int			msg_id;
	t_data		*data;

	data = init_data();
	(void)player;
	if ((msg_id = msgget(data->key, 0666 | IPC_CREAT)) < 0)
		exit_error("msgget() error\n");
	buf.mtype = player->team;
	ft_strncpy(buf.mtext, "salut", 5);
	if (msgsnd(msg_id, &buf, 5, IPC_NOWAIT) < 0)
		exit_error("msgsnd() error\n");
}

void	recv_pos(t_player *player)
{
	int			msg_id;
	t_msgbuf	buf;
	t_data		*data;
	int			r;

	data = init_data();
	if ((msg_id = msgget(data->key, 0666)) < 0)
	{
		return ;
	}
	if ((r = msgrcv(msg_id, &buf, MAX_SIZE, player->team, IPC_NOWAIT)) < 0)
	{
		return ;
	}
	if (r > 0)
	{
		printf("r = %d\n", r);
		printf("\n recv BUF : %s\n", buf.mtext);
	}
}
