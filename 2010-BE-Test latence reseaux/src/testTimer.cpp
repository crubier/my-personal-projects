/*
 * Mesure du temps et on l'ecrit dans un fichier
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include "Mesure.h"

struct chrono initialiser(int s,int us){
    struct chrono test;
    test.rttimer.it_value.tv_sec = s;
    test.rttimer.it_value.tv_usec = us;
    test.rttimer.it_interval.tv_sec = s;
    test.rttimer.it_interval.tv_usec = us;

    test.rttimerbis.it_value.tv_sec = s;
    test.rttimerbis.it_value.tv_usec = us;
    test.rttimerbis.it_interval.tv_sec = s;
    test.rttimerbis.it_interval.tv_usec = us;
    return test;
}

void mesuretemps(struct itimerval *rttimer,struct itimerval *rttimerbis){
    getitimer(ITIMER_REAL, rttimer);
    getitimer(ITIMER_VIRTUAL, rttimerbis);
}

int ecrirefichier(struct chrono test,FILE *fp,int s){
    int sec=s-test.rttimer.it_value.tv_sec-1;
    fprintf(fp,"TEMPS REEL (secondes)=      %d \n",sec);
    int usec=999999-test.rttimer.it_value.tv_usec;
    fprintf(fp,"TEMPS REEL (microsecondes)= %d \n",usec );
    return usec;
//    int secbis=s-test.rttimerbis.it_value.tv_sec;
//    fprintf(fp,"TEMPS VIRTUEL (secondes)= %d \n",secbis);
//    int usecbis=999999-test.rttimerbis.it_value.tv_usec;
//    fprintf(fp,"TEMPS VIRTUEL (microsecondes)= %d \n",usecbis);
}

FILE * creerfichier(){
    time_t timestamp;
    struct tm * t;
    timestamp = time(NULL);
    t = localtime(&timestamp);
    FILE *fp;
    fp=fopen("\resultat_forkseq","a");
    int mois=t->tm_mon++;
    int year=t->tm_year+1900;
    fprintf(fp,"\n");
    fprintf(fp,"Essai du %d/%d/%d à %d:%d:%d \n",t->tm_mday,mois,year,t->tm_hour,t->tm_min,t->tm_sec);
    fflush(fp);
    return fp;
}

FILE * ouvrirfichier(){
    FILE *fp;
    fp=fopen("\resultat_forkseq","a");
    return fp;
}
