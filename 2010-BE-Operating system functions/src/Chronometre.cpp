/*
 * Chronometre.cpp
 *
 *  Created on: 1 mai 2010
 *      Author: lecrubier
 */

#include "Chronometre.h"


void Chronometre::reglerValeur (struct itimerval &tv, int valeurS, int valeurUS, int intervalleS, int intervalleUS) {
	tv.it_value.tv_sec = valeurS;
	tv.it_value.tv_usec = valeurUS;
	tv.it_interval.tv_sec = intervalleS;
	tv.it_interval.tv_usec = intervalleUS;
}

Chronometre::Chronometre() {
	type = ITIMER_REAL;
	init();
}

Chronometre::Chronometre(int letype) {
	type = letype;
	init();
}


Chronometre::~Chronometre() {
}

void Chronometre::init() {

	reglerValeur(initialiseur,0,0,0,0);
	setitimer(type, &initialiseur, NULL);

	reglerValeur(valeur,0,0,0,0);

	etat = 0;
	return;
}

void Chronometre::start() {
	if (etat == 0) {

		reglerValeur(initialiseur,DUREE_SECONDES,0,DUREE_SECONDES,0);
		setitimer(type, &initialiseur, NULL);

		etat = 1;
		return;

	} else {
		return;
	}
}

void Chronometre::stop() {
	if (etat == 1) {

		struct itimerval recu;
		getitimer(type, &recu);

		reglerValeur(initialiseur,0,0,0,0);
		setitimer(type, &initialiseur, NULL);

		reglerValeur(temp,0,0,0,0);
		temp.it_value.tv_sec = DUREE_SECONDES - recu.it_value.tv_sec - 1;
		temp.it_value.tv_usec = 1000000 - recu.it_value.tv_usec - 1;

		if (valeur.it_value.tv_usec + temp.it_value.tv_usec >= 1000000) {
			valeur.it_value.tv_sec = valeur.it_value.tv_sec + temp.it_value.tv_sec + 1;
			valeur.it_value.tv_usec = valeur.it_value.tv_usec + temp.it_value.tv_usec - 1000000;

		} else {
			valeur.it_value.tv_sec = valeur.it_value.tv_sec + temp.it_value.tv_sec;
			valeur.it_value.tv_usec = valeur.it_value.tv_usec + temp.it_value.tv_usec;
		}
		etat =0;
		return;

	} else {
		return;

	}
}

void Chronometre::lap() {
	if (etat == 1) {

		stop();
		start();
		return;

	} else {
		return;
	}
}

int Chronometre::getSecondes() {
	return valeur.it_value.tv_sec;
}

int Chronometre::getUSecondes() {
	return valeur.it_value.tv_usec;
}

double Chronometre::getDouble() {
	return  0.000001 * valeur.it_value.tv_usec + 1.* valeur.it_value.tv_sec;
}
