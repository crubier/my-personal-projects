//============================================================================
// Name        : Paralel.cpp
// Author      : Vincent Lecrubier
//============================================================================

#include "BE_OS_Lecrubier.h"

using namespace std;

int paralel(int mode, int nbProcessus, int nbTests) {
	filebuf fb;
	fb.open ("parallel.txt",ios::out);
	ostream fluxsortie(&fb);


	int nbiterations = nbProcessus;

	int childExitStatus;

	int numero = 0;
	int offset = 1;

	Chronometre chronoreel(ITIMER_REAL);
	chronoreel.start();

	for (int i = nbiterations; i > 0; i--) {
		pid_t pID = fork();

		if (pID == 0) {
			numero = numero + offset;
		} else {
			waitpid(pID, &childExitStatus, mode);
		}

		offset = 2 * offset;

	}

	fluxsortie << getpid() << "		";

			int coef = 1;
			for (int i = nbiterations; i > 0; i--) {
				if (((numero % (2 * coef)) - (numero % (coef))) / coef == 0) {
					fluxsortie << "1 ";
				} else {
					fluxsortie << "0 ";
				}
				coef = coef * 2;
			}

	//fluxsortie << getpid() << ","<<numero<<"";
	fluxsortie << endl;

	if (numero == 0) { //Seulement sur le pere originel
		chronoreel.stop();
		fluxsortie << "T = " << chronoreel.getDouble() <<"s"<< endl;
		return 0;
	}
	else {
		exit(EXIT_SUCCESS);
	}
}
