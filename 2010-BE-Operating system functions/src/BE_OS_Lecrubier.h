
#include <iostream>
#include<fstream>
#include <string>
#include <cstdlib>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>


#include "Chronometre.h"

using namespace std;

//#define NBPROC 50
//#define NBTESTS 1
//#define MODE WUNTRACED
//Differents mode : WNOHANG, WUNTRACED


//////////////////////////////////////////////////////////////////


// fonction de bessel de la premiere espece d'ordre n au point x
// n = ordre de la fonction de bessel
// x = point d'evaluation
double devlim(int n, double x, int, int, int) ;

// Test simple
int paralel(int, int, int);

// Somme des racines carrees des entiers compris entre zero et nbProcessus
double racines(int iterations, int nbProcessus, int, int);


// Lancer des groupes fenetres de maniere groupee;
int lancefenetres();

//////////////////////////////////////////////////////////////////


