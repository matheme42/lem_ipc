/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_leave.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheme <matheme@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:06:01 by matheme           #+#    #+#             */
/*   Updated: 2021/05/12 16:50:02 by matheme          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "lem_ipc.h"

				/* ********* *\
**************** **	PRIVÉE	**	****************
				\* ********* */

				/* ********* *\
**************** **	PUBLIC	**	****************
				\* ********* */

// SE JOINDRE A LA PARTIE
// parmet de rejoindre une partie et de recuperer les informations de depart
// pid		: pid du processus
// return	: TRUE (est bien connecté à la partie)
// erreur	: FALSE (connection refusé / interompu / deviens le serveur)
int joingame(int pid)
{
	char	msg[MSGSZ];
	int		id;

	if (send_msg(MSG_TYPE_CL_JOIN_GAME, (char[4][10]){"id", "id_team"}, (int[4]){pid, data.team_id}, 2)){
		return (FALSE);
	}

	ft_printf("waiting for the serveur...");

	while (rcv_msg(msg, pid, 0) < 0);
	id = arg(msg, "id");
	if (id == -2)
	{
		ft_printf("\rnumber of team reached               \n");
		return (FALSE);
	}
	if (id == -1)
	{
		ft_printf("\ryou leave this game ($%d)                            \n", data.game_id);
		return (FALSE);
	} else if (id == 0)
	{
		ft_printf("\rthis game is full                   \n");
		return (FALSE);
	} else if (id == 1) // deviens le serveur
	{
		data.srv->nb_player--;
		data.server = 1;
		return (FALSE);
	}
	data.player_id = id; // the id of the process is set
	data.posyx.x = arg(msg, "x");
	data.posyx.y = arg(msg, "y");
	return (TRUE);
}

// QUITTER LA PARTIE
int leavegame(int pid)
{
	return (send_msg(MSG_TYPE_CL_LEAVE_GAME, (char[4][10]){"id"}, (int[4]){pid}, 1));
}