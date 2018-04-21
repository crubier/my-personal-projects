/* 
 * File:   Mesure.h
 * Author: auge
 *
 * Created on 28 décembre 2009, 11:42
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>

// Structure chrono contenant 6 itimerval, ainsi on peut mesurer
// trois temporisations différentes
struct chrono {
    struct itimerval rttimer;
    struct itimerval old_rttimer;
    struct itimerval rttimerbis;
    struct itimerval old_rttimerbis;
};

//initilise un chrono
struct chrono initialiser(int ,int );

//met à jour un chrono
void mesuretemps(struct itimerval *,struct itimerval *);

//ecrit dans un fichier les valeurs contenues dans le chrono
int ecrirefichier(struct chrono ,FILE *,int);

//retourne un pointeur vers un fichier avec le nom qui va bien
FILE * creerfichier();
