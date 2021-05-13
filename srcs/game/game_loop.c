/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheme <matheme@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 17:00:02 by matheme           #+#    #+#             */
/*   Updated: 2021/05/13 13:56:20 by matheme          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

static void game_loop_client()
{

}

static void game_loop_server()
{
    data.srv->team_list
}

void game_loop()
{
    while (data.srv->nb_team > 1)
    {
        data.server ? game_loop_server() : game_loop_client();
        usleep(100000);
    }
}