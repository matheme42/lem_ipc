/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheme <matheme@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 14:10:07 by matheme           #+#    #+#             */
/*   Updated: 2021/03/18 16:13:35 by matheme          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

				/* ********* *\
**************** **	PRVÉE	**	****************
				\* ********* */


// CREER LA DATA DU MESSAGE A PARTIR D'ARGUMENT (PRIVÉE)
// ** A NE PAS APPELER **
// cette fonction construit un message pret a etre decompilé.
static char	*create_shdmsg(const char args[4][10], const int values[4], int len)
{
	char *msg;
	char *value;

	msg = ft_strnew(0);
	while (len--) {
		value = ft_itoa(values[len]);
		ft_strjoin_free(&msg, args[len]);
		ft_strjoin_free(&msg , "=");
		ft_strjoin_free(&msg,value);
		free(value);
		if (len > 0)
			ft_strjoin_free(&msg, "&");
	}
	return (msg);
}


				/* ********* *\
**************** **	PUBLIC	**	****************
				\* ********* */


// RECUPERER UN ARGUMENT DE MESSAGE
// cette fonction decrypte le contenu du message pour recuperer la valeur de
// l'argument en parametre
// str		: message a decrypter
// trc		: valeur a recuperer
// return	: la valeur de l'argument
// erreur	: -1 (argument introuvable)
int		arg(char *str, char *trc)
{
	char *find;
	trc = ft_strjoin(trc, "=");
	find = ft_strstr(str, trc);
	if (find != NULL) 
	{
		find = &find[ft_strlen(trc)];
		return (ft_atoi(find));
	}
	ft_printf("%args not found (%s) %s\n", trc, str);
	free(trc);
	return (-1);
}

// ENVOIE UN MESSAGE
// Cette fonction permet d'envoyer un message autre autre processus
// type		: le type du message
// args		: le nom des arguments a envoyer
// values	: la valeur des arguments
// len		: la longueur des arguments
// return	: TRUE (0)
// erreur	: FALSE (impossible d'envoyer le message)
int		send_msg(int type, const char args[4][10], const int values[4], int len)
{
	t_msgbuf	msg;
	char		*msgstr;

	ft_bzero(&msg, sizeof(msg));
	msg.mtype = type;
	msgstr = create_shdmsg(args, values, len);
	ft_strcpy(msg.mtext, msgstr);
	free(msgstr);
	if((msgsnd(data.msqid, &msg, ft_strlen(msg.mtext) + 1, IPC_NOWAIT)) < 0){
		return (FALSE);
	}
	return (TRUE);	
}

// RECOIE UN MESSAGE
// cette fonction receptionne les messages de type `type`
// msg		: buffer de taille MSGSZ
// type		: le type de message à écouter
// flag 	: flag d'ecoute [IPC_NOWAIT , 0]
// return	: le nombre d'octect reçu
// erreur	: -1 (impossible de lire les messages)
long	rcv_msg(char msg[MSGSZ], int type, int flag)
{
	t_msgbuf	rcv;
	long		ret;

	ft_bzero(&rcv, sizeof(rcv));
	if ((ret = msgrcv(data.msqid, &rcv, MSGSZ, type, flag)) > 0)
			ft_strcpy(msg, rcv.mtext);
	return (ret);
}