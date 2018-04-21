//============================================================================
// Name        : LanceFenetres.cpp
// Author      : Vincent Lecrubier
//============================================================================


#include "BE_OS_Lecrubier.h"
using namespace std;

int lancefenetres () {


	int childExitStatus;
	int nbFenetres=-1;
	int taillegroupe=-1;

	while(nbFenetres<0 || nbFenetres>20) {
		cout << "Combien de fenetres voulez vous en tout ? (0-20) " << endl;
		cin >> nbFenetres;
	}

	while(taillegroupe<1) {
		cout << "Combien de fenetres voulez vous par groupe ? (>0)" << endl;
		cin >> taillegroupe;
	}

	pid_t listePID[taillegroupe];
	for (int i = 0; i < nbFenetres; i++) {
		pid_t pID = fork();
		if (pID == 0) {
			// Le processus fils ouvre une fenetre de terminal
			execlp("gnome-terminal", "--hide-menubar", '\0');
		} else {
			//Le pere enregistre le pID de son fils afin de l'attendre par la suite
			listePID[i%taillegroupe]=pID;
			cout << "Fenetre " << i << endl;
		}

		// Lorsqu'on a lancé un nombre de fenetre correspondant a la taille du groupe, on attend la cloture de toutes les fenetres du groupe
		// Avant de recreer les fenetres du groupe suivant
		if(i%taillegroupe==taillegroupe-1) {
			for(int j=0;j<taillegroupe;j++) {
				waitpid(listePID[j], &childExitStatus, WUNTRACED);
			}
		}
	}
	cout << "Terminé" << endl;

	return 0;

}

