/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_plus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheme <matheme@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:00:30 by matheme           #+#    #+#             */
/*   Updated: 2021/03/22 15:07:18 by matheme          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

// ISIN
// Cette fonction regarde si le nombre passé en premier parametre est présent
// dans le tableau de longueur len
int isin(int nb, int *tab, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (nb == tab[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
}


void update_team_list()
{
	int i;

	i = -1;
	ft_bzero(data.srv->team_list, MAX_TEAMS);
	data.srv->nb_team = 0;
	while (++i < data.srv->nb_player)
	{
		if (isin(data.srv->player_list[i].team_id, data.srv->team_list, data.srv->nb_team))
			data.srv->team_list[data.srv->nb_team++] = data.srv->player_list[i].team_id;
	}
}