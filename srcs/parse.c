/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheme <matheme@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:56:30 by matheme           #+#    #+#             */
/*   Updated: 2021/03/19 11:49:04 by matheme          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

				/* ********* *\
**************** **	PRIVÉE	**	****************
				\* ********* */


// L'USAGE
// affiche l'usage de lem_ipc
static void usage()
{
	ft_printf("usage: ./lem_ipc game[0x0001 - 0x9999]  equipe[0x0001 - 0x9999]\n");
}

				/* ********* *\
**************** **	PUBLIC	**	****************
				\* ********* */

// PARCOURS LES ARGUMENTS PASSER EN PARAMETRE
// s'occupe de separere les argument de remplir le numero d'equipe et le numero de partie
// des données joueur.
// ac		: le nombre d'argument
// av		: tableau argument
// return	: TRUE (0)
// error	: FALSE (affiche l'erreur obtenu)
int parse(int ac, char **av)
{
	if (ac != 3) {
		usage();
		return (FALSE);
	}

	if ((data.game_id = ft_atoi(av[1])) <= 0) {
		usage();
		ft_printf("error: numero de partie invalide\n");
		return (FALSE);
	}

	if ((data.team_id = ft_atoi(av[2])) <= 0) {
		usage();
		ft_printf("error: numero d'equipe invalide\n");
		return (FALSE);
	}

	return (TRUE);
}