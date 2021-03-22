/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_ipc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheme <matheme@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 15:42:13 by matheme           #+#    #+#             */
/*   Updated: 2021/03/22 15:07:29 by matheme          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


/* source to help me

for remove shareddata
	https://knowledgebase.progress.com/articles/Article/ipcrm-m-not-removing-shared-memory-id-on-linux

for message queues
	https://gist.github.com/Mark-htmlgogogo/e024c36541646373581472348657304d
	https://www.tutorialspoint.com/inter_process_communication/inter_process_communication_message_queues.htm
for semaphore
	https://www.i3s.unice.fr/~tettaman/Classes/L2I/ProgSys/9_ProgSysLinuxSem.pdf
for shared_memory
	https://www.tutorialspoint.com/inter_process_communication/inter_process_communication_shared_memory.htm
*/

#ifndef LEM_IPC_H
# define LEM_IPC_H

//libft_include
#include "ft_int.h"
#include "ft_str.h"
#include "ft_printf.h"
#include "ft_printf_err.h"
#include "ft_mem.h"

#include "lem_ipc_message_type.h" // message d'envoie possible

#include <sys/ipc.h> // include ipc
#include <sys/shm.h> // shared memory
#include <sys/msg.h> // message
#include <sys/sem.h> // semaphore


#include <signal.h> // une to catch signal ctrl-c

# define TRUE	0
# define FALSE	1

// the sie of the arena
# define ARENASIZE_X	10 // MAX 255
# define ARENASIZE_Y	10 // MAX 255

# define MAX_PLAYERS	(ARENASIZE_X * ARENASIZE_Y) / 5
# define MAX_TEAMS		(ARENASIZE_X * ARENASIZE_Y) / 25


// STRUCTURE DES DONNEES DE JEUX
typedef struct	player_list
{
				unsigned int team_id;
				unsigned int player_id;
}				t_player_list;

typedef struct	arena_data
{
				unsigned char	size_x;
				unsigned char	size_y;
				char			arena[ARENASIZE_X][ARENASIZE_Y];
				int				nb_player;							// the number of player inside the game
				int				nb_team;
				int				time;								// temps avant le debut de la partie
				t_player_list	player_list[MAX_PLAYERS];			// list of association between team_id & player_id
				int				team_list[MAX_TEAMS];				// team list
}				t_arena_data;


// STRUCTURE DES DONNEES DE JOUEUR
typedef struct	player_posyx
{
				unsigned char x; // position x of the player
				unsigned char y; // position y of the player
}				t_player_posyx;

typedef struct	lem_ipc
{
	int				server;		// 1 if the current process is the server
	t_arena_data	*srv;		// share memory ptr
	int				msqid;		// msg queue id
	int				semid;		// semaphore id
	int				shmid;		// share memory id

	unsigned int	player_id;	// the process id
	unsigned int	team_id;	// the team id
	unsigned int	game_id;	// the game id
	t_player_posyx	posyx;		// position x and y of the player on the map
}				t_lem_ipc;

// global
extern			t_lem_ipc		data;


// FONCTIONS DE GESTION DE RESSOURCES
int				create_ressources();
int				delete_ressources();

// FONCTIONS DE PREPARATION DE LA PARTIE
int				waitforuser(int pid);
void			game_started();
int				joingame(int pid);
int				leavegame(int pid);


// FONCTIONS DE COMMUNICATION INTER-PROCESSUS
int				send_msg(int type, const char args[4][10], const int values[4], int len);
long			rcv_msg(char msg[MSGSZ], int type, int flag);
int				arg(char *str, char *trc);

// FONCTIONS D'AFFICHAGES
void			message_printer(char *msg, int replace);

// FONCTIONS DE DEBUG
void			put_arena();

// AUTRES FONCTIONS
int				parse(int ac, char **av);


// LIBFT PLUS
int				isin(int nb, int *tab, int len);
void			update_team_list();
#endif