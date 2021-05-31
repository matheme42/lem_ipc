/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ressources.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheme <matheme@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:33:35 by matheme           #+#    #+#             */
/*   Updated: 2021/05/13 14:04:29 by matheme          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

				/* ********* *\
**************** **	PRIVÉE	**	****************
				\* ********* */


// INITIALISER LES RESSOURCES
// appel implicite dans la recuperation des ressources
static void initialize_ressources()
{
	if (msgget(data.game_id, IPC_EXCL) == -1) {
		ft_bzero(data.srv, sizeof(data.srv));
		data.srv->time = 50;
		data.server = 1;
	}
}

				/* ********* *\
**************** **	PUBLIC	**	****************
				\* ********* */

// RECUPERER LES RESSOURCES
// cette fonction initialiser les ressources necessaire au fonctionnement de lem_ipc
// si celle-ci ne sont pas creer, elle les creer.
// return	: TRUE (0)
// error	: FALSE (1)
int	create_ressources()
{
	// create / get shared memory
	if ((data.shmid = shmget(data.game_id, sizeof(data.srv),  0666 | IPC_CREAT)) == -1)
		return (FALSE);
	data.srv = shmat(data.shmid, NULL, 0);

	initialize_ressources();

	// create / get message queues
	if ((data.msqid = msgget(data.game_id, 0666 | IPC_CREAT)) == -1)
		return (FALSE);

	// create / get semaphore
	if ((data.semid = semget(data.game_id, 1, 0666 | IPC_CREAT)) == -1)
		return (FALSE);

	return (TRUE);
}

// SUPPRIMER LES RESSOURCES
// supprime les ressources. A utiliser en fin de programme
// return	: TRUE (0)
// error	: FALSE (1)
int delete_ressources()
{
	// delete the message queues
	if (msgctl(data.msqid, IPC_RMID, NULL) == -1) {
		return (FALSE);
   }

	// delete share memory
    if (shmctl(data.shmid, IPC_RMID, 0) == -1) {
      return (FALSE);
   }

   	// delete semaphore
    if (semctl(data.semid, IPC_RMID, 0) == -1) {
      return (FALSE);
   }
   return (TRUE);
}