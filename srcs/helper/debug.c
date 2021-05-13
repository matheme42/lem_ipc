/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheme <matheme@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 17:12:30 by matheme           #+#    #+#             */
/*   Updated: 2021/03/22 15:37:15 by matheme          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

				/* ********* *\
**************** **	PRIVÉE	**	****************
				\* ********* */


				/* ********* *\
**************** **	PUBLIC	**	****************
				\* ********* */

// AFFICHER L'ARENE
// cette fonction afficher l'arene de taille x y
void put_arena()
{
	int i = 0;
	int j = 0;
	while (i < ARENASIZE_X)
	{
		while (j < ARENASIZE_Y)
		{
			ft_putchar(' ');
			ft_putnbr(data.srv->arena[i][j]);
			ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
		j = 0;
		i++;
	}
}
