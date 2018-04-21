//============================================================================
// Name        : Racines.cpp
// Author      : Vincent Lecrubier
//============================================================================


#include "BE_OS_Lecrubier.h"
using namespace std;


double racines(int iterations, int mode, int nbProcessus, int nbTests) {
	filebuf fb;
	fb.open ("racines.csv",ios::out);
	ostream fluxsortie(&fb);

	// L'intitule du tableau, pratique en cas d'import des resultat dans un tableur
	fluxsortie<<"texte	numero	temps		resultat" <<endl;

	// Boucle d'iteration pour faire plusieurs tests a la suite
	for(int ff=0; ff< nbTests;ff++) {

		//
		//

		int nbproc = nbProcessus+1; 	// le nombre de processus
		int numero = 0;			// le numero du premier processus (pere)
		int childExitStatus;	// le statut de retour de l'enfant
		pid_t pID = 0;			// le pID de l'enfant

		double res = -1;		// le resultat du calcul effectue par le processus

		//
		//

		// On cree un tableau de pipes, le lecteur de chaque pipe sera le processus pere de tous les autres, avec le numero 0
		// Le processus numero N sera celui qui ecrira dans le pipe N
		int pfd[2][nbProcessus+1];

		// Tableau temporaire
		int pfdtemp[2];

		// Boucle de remplissage du tableau de pipes
		for (int i = 0; i < nbproc; i++) {

			// On cree un pipe dont on stocke les coordonnees dans le tableau temporaire
			if (pipe(pfdtemp) == -1) {

				// Erreur
				fluxsortie << "Erreur a la creation de pipe" << endl;
				return 0;

			} else {

				// Pas d'erreur, on peut donc stocker les coordonnes du pipe cree dans le tableau de pipes
				pfd[0][i] = pfdtemp[0];
				pfd[1][i] = pfdtemp[1];
			}
		}

		//
		//

		// On lance le chrono, qui ne rester fonctionnel que sur le processus numero 0
		Chronometre chronoreel(ITIMER_REAL);
		chronoreel.start();

		//
		//


		// On lance les processus
		do {

			pID = fork();

			if (pID == 0) {

				// le processus est le fils donc on incremente son numero par rapport a celui de son pere
				numero = numero + 1;

			}
			else {

				//le processus est le pere donc on garde le numero et on attend (ou pas) la fin de l execution du fils
				waitpid(pID, &childExitStatus, mode);

			}

		//le fils dont le numero est egal au nombre de processus desiré ne doit pas faire de fork, il est en bout de chaine
		} while (numero < nbproc -1 && pID == 0);


		//
		//


		// Le code qui sera execute par les processus, on fera une difference entre le pere (numero 0) et les fils


		if (numero == 0) {
			//
			// Code du pere

			double resultats[nbProcessus];
			double resultat =0;

			// Boucle de gestion des pipes
			for (int i = 1; i < nbproc; i++) {

				//On ferme le cote d ecriture
				close(pfd[1][i]);

				//On rend le read non bloquant
				fcntl(pfd[0][i],F_SETFL,O_NONBLOCK);
			}

			double buffer; 	// Un buffer pour recevoir le resultat des fils
			int recus =0; 	// Le nombre de resultats recus
			int loops =0;	// Le nombre de boucles de reception effectuees

			// Boucle de reception des resultats des fils, qui tourne tant qu'il manque des resultats
			while(recus < nbProcessus) {

				// On extrait le temps actuel du chrono et on affiche le resultat en meme temps que le nombre de boucles effectuees
				chronoreel.lap();
				fluxsortie << "Loop	"<< loops<<"	"<< chronoreel.getDouble() << "	"<<recus<<endl;

				// On passe en revue tous les pipes pour voir si des resultats sont arrives
				for (int i = 1; i <nbproc; i++) {

					// Le read est non bloquant, donc si pas de resultat, on passe
					if(read(pfd[0][i], &buffer, sizeof(buffer))==sizeof(buffer)){

						// Si il y a un resultat, on l'affiche, ainsi que le temps ecoulé et le numéro du pipe d'ou provient le resultat,
						// ie le numero du processus ayant effectué le calcul
						chronoreel.lap();
						fluxsortie << "recu	"<<i << "	" << chronoreel.getDouble() <<"	"<<buffer<< endl;

						// On enregistre le resultat dans la table des resultats
						resultats [i] = buffer;
						resultat = resultat + buffer;

						// Puis on incrémente le compteur du nombre de resultats recus
						recus = recus+1;
					}
				}

				// Quand on a passe en revue tout les pipes, on affiche le temps total ecoulé, puis on boucle si il manque des resultats
				chronoreel.lap();
				fluxsortie << "/Loop	"<< loops<<"	"<< chronoreel.getDouble() << "	"<<recus<<endl;

				usleep(1000);
			}

			// Quand tout les resultats sont arrives, le programme est termine, on affiche le temps total,
			// et eventuellement on refait un essai en fonction de NBTESTS
			chronoreel.stop();
			fluxsortie  <<"Essai	"<< ff << "	"<< chronoreel.getDouble() << "	" << resultat<< endl;
			fb.close();
			return resultat;

		}

		else {

			//
			// Code des fils

			// On lance un chronometre car les itimer ne restent valables que pour le pere lors d'un fork
			Chronometre chronoreel2(ITIMER_REAL);
			chronoreel2.start();


			// Boucle de gestion des pipes
			for (int i = 1; i < nbproc; i++) {

				//On ferme le cote de lecture de tous les pipes
				close(pfd[0][i]);

				//On ferme le cote d'ecriture de tous les pipes sauf celui utilise par le processus
				if(i!=numero) close(pfd[1][i]);

			}

			//On rend le write non bloquant sur le pipe utilise
			fcntl(pfd[1][numero],F_SETFL,O_NONBLOCK);


			res = (double) numero;	// Le resultat retourne par le processus (initialise a son numero)

			// On affiche le temps reel ecoule entre le demarage du processus et le demarrage effectif du calcul
			chronoreel2.lap();
			fluxsortie << "Calc	" << numero << "	" << chronoreel2.getDouble() << endl;

			// Boucle de calcul du resultat (racine carree);
			for(int i = 0; i < iterations;i++) {
				res = 0.5* (res + ((double) numero)/res);
			}

			// Ecriture du resultat dans le pipe afin de l'envoyer au pere (numero 0)
			write(pfd[1][numero], &res, sizeof(res));


			// On stope le chronometre du processus et on affiche le temps total ecoule pour le calcul du processus
			chronoreel2.stop();
			fluxsortie << "/Calc	" << numero << "	" << chronoreel2.getDouble() <<"	"<<res<< endl;

			//On arrete le processus fils.
			exit(EXIT_SUCCESS);
		}
	}
}

