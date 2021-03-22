/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_user.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheme <matheme@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 14:03:01 by matheme           #+#    #+#             */
/*   Updated: 2021/03/22 15:42:30 by matheme          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"


				/* ********* *\
**************** **	PRIVÉE	**	****************
				\* ********* */


// ACCEPTER / REFUSER UN PROCESSUS
// Cette fonction verifie si le nombre maximale de joueur (MAX_PLAYERS) A été atteins
// ou non, et refuse le processus si c'es le cas
// A NE PAS APPELER DIRECTEMENT
// rcvstr	: chaine de caractere reçu du processus client 
// return	: TRUE (message bien envoyé)
// error	: FALSE (message non envoyé)
// **************** PLUS ****************
// Structure du message reçu	: "id_team=?, id=?"
// Structure du message envoyé	: "id=0"
static int accept_decline_process(char *rcvstr)
{
	int pid;
	int team_id;

	pid = arg(rcvstr, "id");
	team_id = arg(rcvstr, "id_team");
	if (data.srv->nb_player < MAX_PLAYERS)
	{
		if (data.srv->nb_team == MAX_TEAMS && isin(team_id, data.srv->team_list, data.srv->nb_team))
		{
			if (send_msg(pid, (char[4][10]){"id"}, (int[4]){-2}, 1))
				return (FALSE);
			return (TRUE);
		}
		
		data.srv->player_list[data.srv->nb_player].player_id = pid;
		data.srv->player_list[data.srv->nb_player].team_id = team_id;
		data.srv->nb_player++;
		update_team_list();
		return (TRUE);
	}
	if (send_msg(pid, (char[4][10]){"id"}, (int[4]){0}, 1))
		return (FALSE);
	return (TRUE);
}

// SUPPRIME UN PROCESSUS DE LA LISTE DES JOUEURS
// cette fonction supprime un joueur de la liste des joueurs en fonction de son id
// et change la position des autre joueurs dans la liste (CHANGE L'ID DES AUTRES JOUEURS)
// A NE PAS APPELER DIRECTEMENT
// pid	: pid du processus du joueur a supprimer
static void remove_process_from_list(int pid)
{
	int i;
	int find;
	int team_id;

	i = 0;
	find = 0;
	while (i < data.srv->nb_player)
	{
		if (find == 1) {
			data.srv->player_list[i - 1].player_id = data.srv->player_list[i].player_id;
			data.srv->player_list[i - 1].team_id = data.srv->player_list[i].team_id;
		}
		if (data.srv->player_list[i].player_id == pid)
			find = 1;
		i++;
	}
	ft_bzero(&data.srv->player_list[i - 1], sizeof(data.srv->player_list[i - 1]));
	data.srv->nb_player--;
}

// SUPPRIMER UN PROCESSUS DU JEU
// supprime un processus de la liste des joueurs. Et envoie un message de refus au processus client
// A NE PAS APPELER DIRECTEMENT
// rcvstr	: message reçu du processus pour quitter
// return	: TRUE (message bien envoyé)
// erreur	: FALSE (impossible d'envoyé le message)
//	************* PLUS *************
// Structure du message reçu	: "id_team=?, id=?"
// Structure du message envoyé	: "id=-1"
static int remove_process(char *rcvstr)
{
	int id;

	id = arg(rcvstr, "id");
	remove_process_from_list(id);
	update_team_list();
	if (send_msg(id, (char[4][10]){"id"}, (int[4]){-1}, 1))
		return (FALSE);
	return (TRUE);
}

// PERMET DE CHANGER LE PROCESSUS SERVEUR
// envoie un message au prochain processus de la liste pour qu'il devienne un processus serveur
// A NE PAS APPELER DIRECTEMENT
static void switch_serveur()
{
	char	msg[MSGSZ];
	
	while (send_msg(data.srv->player_list[0].player_id, (char[4][10]){"id"}, (int[4]){1}, 1));
	data.server = 0;
}


				/* ********* *\
**************** **	PUBLIC	**	****************
				\* ********* */

// HUB SERVEUR D'ATTENTE DES PROCESSUS
// s'occupe d'attendre et de receptionner les messages des autre processus
// pid		: correspond au pid du serveur
// return	: TRUE (Compte a rebourd atteint)
// error	: CTRL-C demandé changement de serveur
int waitforuser(int pid)
{
	char	msg[MSGSZ];

	data.player_id = pid;
	data.srv->nb_player++;
	data.srv->player_list[0].player_id = data.player_id;
	data.srv->player_list[0].team_id = data.team_id;
	update_team_list();
	while (data.srv->time > 0)
	{
		usleep(98000);
		data.srv->time--;
		ft_printf("\rthe game will start in: %2d.%ds (%d/%d) (%d)", data.srv->time / 10, data.srv->time % 10, data.srv->nb_player, MAX_PLAYERS, data.srv->nb_team);

		if (rcv_msg(msg, MSG_TYPE_CL_JOIN_GAME, IPC_NOWAIT) > 0) {
			while (accept_decline_process(msg));
		}
		if (rcv_msg(msg, MSG_TYPE_CL_LEAVE_GAME, IPC_NOWAIT) > 0) {
			while (remove_process(msg));
		}
		if (rcv_msg(msg, pid, IPC_NOWAIT) > 0) {
			ft_printf("\ryou leave this game ($%d)                            \n", data.game_id);
			if (data.srv->nb_player > 0)
			 	switch_serveur();
			return (FALSE);
		}

		if (data.srv->nb_player == MAX_PLAYERS && data.srv->time > 100) {
			data.srv->time = 100;
		}
	}
	return (TRUE);
}
