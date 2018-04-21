//============================================================================
// Name        : BE_OS_Lecrubier.cpp
// Author      : Vincent Lecrubier
//============================================================================

#include "BE_OS_Lecrubier.h"

int main() {

	//Toutes les fonctions integrent des chronometres (itimers) sur les processus, ce qui permet de faire des mesures.
	//Les différents resultats sont stockés dans des fichiers textes dans le repertoire de l'executable.

	//A cause des limitation sur les nombres en virgule flottante, le resultat peut etre invalide si les differents processus ne s'effectuent pas dans l'ordre
	//Il faut donc mettre l'option WUNTRACED.
	//
	//La fonction retourne la fonction de bessel de la premiere espece, d'ordre 2, evaluee au point 5.261, a l'aide d'un developpement limite a l'ordre 50,
	// dont chaque terme (il y en a donc 50) est calculé dans un processus separé.
	//
	//Verification possible du resultat a l'aide du site suivant
	//http://www.wolframalpha.com/input/?i=BesselJ[2%2C5.2561]
	//
	cout << "RESULTAT DE DEVLIM : " << devlim(2, 5.2561, WUNTRACED, 50, 1) << endl;

	//Fonctionne quelque soit l ordonancement des processus, on peut donc mettre l'option WNOHANG.
	//La fonction retourne la somme des racines carré des entiers compris entre 1 et 50, chaque racine carree est calculee avec la methode de newton, en 100000 iterations
	//
	//Verification possible du resultat a l'aide du site suivant
	//http://www.wolframalpha.com/input/?i=Sum[Sqrt[i]%2C{i%2C1%2C50}]
	//
	cout << "RESULTAT DE RACINES : " << racines(100000, WNOHANG, 50, 1) << endl;

	//Lance 2^7 processus fils en cascade selon un arbre binaire.
	//Si l'on choisi l'option WUNTRACED, alors lee dernier processus se terminera en premier, et ainsi de suite jusqu'au premier processus qui se terminera en dernier.
	//La numerotation de chaque processus est lié a sa "genealogie", et chaque processus affiche une représentation binaire de son numero,
	//On observe alors en sortie, grace a l'ordonnancement des processus, un tableau représentant tous les nombres binaires a 7 bits, dans l'ordre du code GRAY
	//La sortie est visible dans
	//
	//Si on choisi l'option WNOHANG, on constate bien l'ordre des processus en sortie est désordonné.
	//
	paralel(WUNTRACED, 7, 1);

	//Lance un nombre arbitraire de processus executant gnome-terminal de maniere groupée.
	//Toutes les feneters du premier groupe doivent etre fermees pour que le deuxieme groupe de fenetres apparaisse, et ainsi de suite.
	//
	//Demonstration du fork et exec.
	//
	lancefenetres();

}
