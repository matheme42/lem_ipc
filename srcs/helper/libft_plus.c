/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_plus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheme <matheme@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:00:30 by matheme           #+#    #+#             */
/*   Updated: 2021/05/12 17:06:51 by matheme          ###   ########lyon.fr   */
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
