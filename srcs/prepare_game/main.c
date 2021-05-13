#include "lem_ipc.h"

// Données global du projet
t_lem_ipc	data;



				/* ********* *\
**************** **	PRIVÉE	**	****************
				\* ********* */
// CTRL-C
static void intHandler(int dummy) {
		leavegame(getpid());
}

				/* ********* *\
**************** **	PUBLIC	**	****************
				\* ********* */

// LE MAIN
// 1 initialiser les données
// 2 parser les parametre
// 3 recuperer le signal CTRL-C
// 4 lancer le programme en tant que client
// 5 lancer le programme en tant que serveur
// 6 lancer la partie
// 7 supprimer les ressources si le processus est le serveur
int main(int ac, char **av)
{
	ft_bzero(&data, sizeof(data));

	if (parse(ac, av))
		return (FALSE);

	if (create_ressources())
		return (FALSE);

	signal(SIGINT, intHandler);

	// client
	if (!data.server && !joingame(getpid()))
		ft_printf("\ri'm the player %u/%-20d (%d-%d)\n", data.player_id, MAX_PLAYERS, data.posyx.x, data.posyx.y);

	// serveur
	if (data.server && !waitforuser(getpid())){
		game_started();
		ft_printf("\ri'm the player %u/%-30d (%d-%d)\n", data.player_id, MAX_PLAYERS, data.posyx.x, data.posyx.y);
	}

	game_loop();

	if (data.server)
	{
		ft_printf("supression des ressources...\n");
		usleep(500000);
		delete_ressources();
	}
	put_arena();
	return (TRUE);
}
