/*
 * Chronometre.h
 *
 *  Created on: 1 mai 2010
 *      Author: lecrubier
 */
#include <time.h>
#include <sys/time.h>
#include <signal.h>

#ifndef CHRONOMETRE_H_
#define CHRONOMETRE_H_
#define DUREE_SECONDES 100000

class Chronometre {
private:
	struct itimerval temp;			// valeur temporaire

	struct itimerval initialiseur;	// valeur pour initialiser l'itimer a differents endroits du code, pourrait etre eventuellement fusionnee avec temp
									// mais je ne suis pas sur du resultat

	struct itimerval valeur;		// valeur du chronometre qui sera retournee a l'utilisateur

	int type;	// le type du itimer
				//	ITIMER_REAL
				//		décroît en temps réel et un signal SIGALRM est émis à l'expiration du délai.
				//	ITIMER_VIRTUAL
				//		décroît uniquement quand le processus s'exécute, et un signal SIGVTALRM est émis à l'expiration du délai.
				//	ITIMER_PROF
				//		décroît à la fois quand le processus s'exécute, et quand le processeur exécute des fonctions systèmes à la demande du processus.
				//		Ce timer, utilisé conjointement avec ITIMER_VIRTUAL, est généralement utilisé pour obtenir le profil d'exécution du processus
				//		entre les fonctionnalités utilisateur et le noyau. SIGPROF est émis à l'expiration du délai.

	int etat;	// 0 = stop
				// 1 = en marche

	// Methode privee utilisee pour racourcir le code
	void reglerValeur(struct itimerval&, int, int, int, int);

public:
	// Constructeur avec type = ITIMER_REAL
	Chronometre();

	// Constructeur avec specification du type
	Chronometre(int letype);

	// Destructeur
	virtual ~Chronometre();


	// Initialiser le chronometre a zero, et le mettre en mode stop, methode appelle par le constructeur
	void init();

	// Demarrer le chronometre s'il est a l'arret, sans le remettre a zero
	void start();

	// Arreter le chronometre, sans le remettre a zero, et en enregistrant sa valeur pour qu'elle soit accessible a l'utilisateur via les getters
	void stop();

	// Enregistrer la valeur du chronometre pour qu'elle soit accessible a l'utilisateur via les getters, sans arreter le chronometre
	void lap();

	// Getters
	int getSecondes();		// Valeur du compteur des secondes du chronometre
	int getUSecondes();		// Valeur du compteur des microsecondes du chronometre
	double getDouble();		// Valeur du chronometre en secondes

};

#endif /* CHRONOMETRE_H_ */
