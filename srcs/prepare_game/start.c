/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheme <matheme@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:00:26 by matheme           #+#    #+#             */
/*   Updated: 2021/05/13 14:04:56 by matheme          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

				/* ********* *\
**************** **	PRIVÉE	**	****************
				\* ********* */

// VERIFIE LE POSITIONNEMENT DES JOUEURS EN DEBUT DE PARTIE
// cette fonction verifie si le joueur x est entourner par des joueurs adverse
// si c'est le cette fonction reverra FALSE sinon TRUE
// x		: posX du joueur
// y		: posY du joueur
// team_id  : id de l'equipe du joueur
// return	: TRUE (0) or FALSE (1)

static int check_start_position(int x, int y, int team_id)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	x -= 1;
	y -= 1;
	while (i <= 2)
	{
		j = 0;
		while (j <= 2)
		{
			if (x + j >= 0 && y + i >= 0 && x + j < ARENASIZE_X && y + i < ARENASIZE_Y)
			{
				c = data.srv->arena[x + j][y + i];
				if (c != 0 && c != team_id)
					return (FALSE);
			}
			j++;
		}
		i++;
	}
	return (TRUE);
}

// POSITIONNEMENTS DES JOUEURS AU DEBUT
// Cette fonction permet de positionner les joueurs en debut de partie

static t_player_posyx get_start_position(int teamid)
{
	t_player_posyx	player;

	srand(time(NULL));

	do
	{
		player.x = rand() % ARENASIZE_X;
		player.y = rand() % ARENASIZE_Y;
	} while (data.srv->arena[player.x][player.y] != 0 || check_start_position(player.x, player.y, teamid));
	data.srv->arena[player.x][player.y] = teamid;
	return (player);
}

				/* ********* *\
**************** **	PUBLIC	**	****************
				\* ********* */

// DEMMARE LA PARTIE
// Cette fonction envoie l'ID et la position du joueur au joueur
void game_started()
{
	// int	i;
	// t_player_posyx	player;

	// i = 0;
	// data.player_id = 1;
	// data.srv->player_list[0].player_id = 1;
	// player = get_start_position(data.srv->player_list[0].team_id);
	// data.posyx.x = player.x;
	// data.posyx.y = player.y;
	// while (++i < data.srv->nb_player)
	// {
	// 	player = get_start_position(data.srv->player_list[i].team_id);
	// 	while (send_msg(data.srv->player_list[i].player_id, (char[4][10]){"id", "x", "y"}, (int[4]){i + 1, player.x, player.y}, 3));
	// 	data.srv->player_list[i].player_id = i + 1;
	// }
}
