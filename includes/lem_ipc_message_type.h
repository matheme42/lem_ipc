/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_ipc_message_type.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheme <matheme@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:39:07 by matheme           #+#    #+#             */
/*   Updated: 2021/03/19 11:53:55 by matheme          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IPC_MESSAGE_TYPE_H
# define LEM_IPC_MESSAGE_TYPE_H

#define MSGSZ 128

// Declare the message structure.
typedef struct	msgbuf {
	long		mtype;
	char		mtext[MSGSZ];
}				t_msgbuf;

// the message 1 TO 99 is RESERVED FOR THE PLAYER

# define MSG_TYPE_CL_JOIN_GAME	101
# define MSG_TYPE_CL_LEAVE_GAME 102
# define MSG_TYPE_CL_SWITCH_SERVEUR 103

#endif