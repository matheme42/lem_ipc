/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheme <matheme@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:00:26 by matheme           #+#    #+#             */
/*   Updated: 2021/03/22 16:07:32 by matheme          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

				/* ********* *\
**************** **	PRIVÉE	**	****************
				\* ********* */

// POSITIONNEMENTS DES JOUEURS AU DEBUT
// Cette fonction permet de positionner les joueurs en debut de partie
// map point de spawn
// * * * * * + + + + +
// * A * A * + B + B +
// * * A * * + + B + +
// * A * A * + B + B +
// * * * * * + + + + +
// . . . . . - - - - -
// . C . C . - D - D -
// . . C . . - - D - -
// . C . C . - D - D -
// . . . . . - - - - -

static void get_start_position()
{
	 
}

				/* ********* *\
**************** **	PUBLIC	**	****************
				\* ********* */

// DEMMARE LA PARTIE
// Cette fonction envoie l'ID et la position du joueur au joueur
void game_started()
{
	int	i;

	i = 0;
	data.player_id = 1;
	data.srv->player_list[0].player_id = 1;
	while (++i < data.srv->nb_player)
	{
		while (send_msg(data.srv->player_list[i].player_id, (char[4][10]){"id"}, (int[4]){i + 1}, 1));
		data.srv->player_list[i].player_id = i + 1;
	}
}
