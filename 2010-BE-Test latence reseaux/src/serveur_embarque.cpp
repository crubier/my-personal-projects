

//////////////////////////////////////////////////////////////////////
/*! \file serveur_embarque.cpp
 *  \brief main (gestion des sockets clients)
 *
 *  \mainpage Projet serveur_Embarque_NouveauProtocole
 *
 *  \version V0.1
 *
 *  \date  18 mars 2009
 *
 * \section intro_sec Introduction
 *
 * Logiciel de base de l'interface TM/TC (voir document "description interface TMTC.doc" )
 *
 * \section Evol_sec Evolution du logiciel
 *
 * \subsection vers_anterieure version anterieure :
 *   Aucune  (version de base)
 *
 * \subsection modifs modifications :
 *    version de base
 *
 *
 */

#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <iostream>
#include <string>
#include <strings.h>
#include <pthread.h>
#include <vector>
#include <errno.h>
#include <asm/socket.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <native/task.h>
#include <native/timer.h>
#include <native/sem.h>
#include <sys/mman.h>
#include <mqueue.h>
#include <math.h>
#include "Mesure.h"
#include "ConnexionUDP.h"

#define MAX_LINE 100
// 3 caractères pour les codes ASCII 'cr', 'lf' et '\0'
#define LINE_ARRAY_SIZE (MAX_LINE+3)

using namespace std;


void cleanup_upon_sig(int sig __attribute__((unused)))
{
  exit(0);
}

int main (int nbParam, char *params[])
{
	
	//	verrouillage de la pagination mémoire pour cette application
	//	mlockall(MCL_CURRENT | MCL_FUTURE);
	//	instanciation signal pour ctrl-C	
	//	signal(SIGINT, cleanup_upon_sig);
	//	signal(SIGTERM, cleanup_upon_sig);
	
    int s = 1;
    int us = 0;
    FILE *fp;
    fp = stdout;
	//socklen_t clientAddressLength;
	int k=0;
	int delai=0;
	
//	const char* IPMatlab = "10.255.100.106";
//	const char* IPGumstix = "10.255.100.101";
//	
//	
//	struct sockaddr_in adresseMatlabEmission = 	creerAdresse(IPMatlab,9000);
//	struct sockaddr_in adresseGumstixReception=	creerAdresse(IPGumstix,9010);
//	struct sockaddr_in adresseMatlabReception= 	creerAdresse(IPMatlab,9010);
//	struct sockaddr_in adresseGumstixEmission = creerAdresse(IPGumstix,9000);
//
//	int socketReception = creerSocket() ;
//	int socketEmission = creerSocket() ;
//
//	binderSocket(socketReception,	&adresseGumstixReception);
//	binderSocket(socketEmission,	&adresseGumstixEmission);
	
	int socketReception,socketEmission ;
	struct sockaddr_in adresseMatlabEmission, adresseGumstixReception, adresseMatlabReception,adresseGumstixEmission;
	
	socketReception = socket(AF_INET, SOCK_DGRAM, 0);
	if (socketReception < 0) {
		std::cerr << "cannot create socket Reception";
		exit(1);
	}
		
	socketEmission = socket(AF_INET, SOCK_DGRAM, 0);
	if (socketEmission < 0) {
		std::cerr << "cannot create socket Emission";
		exit(1);
	}
	
	adresseGumstixReception.sin_family = AF_INET;
	adresseGumstixReception.sin_addr.s_addr = inet_addr("10.255.100.101");
	adresseGumstixReception.sin_port = htons(9010);
	if (bind(socketReception,(struct sockaddr *) &adresseGumstixReception,
			sizeof(adresseGumstixReception)) < 0) {
		cout << "cannot bind listen socket";
		exit(1);
	}
	
	adresseGumstixEmission.sin_family = AF_INET;
	adresseGumstixEmission.sin_addr.s_addr = inet_addr("10.255.100.101");
	adresseGumstixEmission.sin_port = htons(9000);
	if (bind(socketEmission,(struct sockaddr *) &adresseGumstixEmission,
			sizeof(adresseGumstixEmission)) < 0) {
		cout << "cannot bind emission socket";
		exit(1);
	}
	
	adresseMatlabEmission.sin_family = AF_INET;
	adresseMatlabEmission.sin_addr.s_addr = inet_addr("10.255.100.106");
	adresseMatlabEmission.sin_port = htons(9000);	
	
	adresseMatlabReception.sin_family = AF_INET;
	adresseMatlabReception.sin_addr.s_addr = inet_addr("10.255.100.106");
	adresseMatlabReception.sin_port = htons(9010);
	
//	float recu [25]; // Entiers63 Reels25 Octets15
//	float envoi [25];
	
	char paquetRecu [241];
	char paquetEnvoi [241];
	
	float recuFloat [25];
	float envoiFloat [25];
	char* recuFloatC ; //25*4
	char* envoiFloatC ;
	
	int recuInt [63];
	int envoiInt [63];
	char* recuIntC ; //63*2
	char* envoiIntC ;
	
	char recuChar [15];
	char envoiChar [15];
	char* recuCharC ; //15*1
	char* envoiCharC ;
	
//	for(k=0;k<25;k++){
//		envoi[k]= (float)k;
//		recu[k]=(float)0;
//	}
	
	for(k=0;k<241;k++){
		paquetRecu[k]= 0;
		paquetEnvoi[k]=0;
	}
	
	// Attente des requêtes clients.
	// C'est un appel non-bloquant ; c'est-à-dire qu'il enregistre ce programme
	// auprès du système comme devant attendre des connexions sur ce socket avec
	// cette tâche. Puis, l'exécution se poursuit.
	listen(socketReception, 5);
	cout << "Waiting for request " << endl;
	
	//clientAddressLength = sizeof(adresseMatlabEmission);
	
	while (1) {
		cout << "Boucle" << endl;
		
       struct chrono chr = initialiser(s, us);
        setitimer(ITIMER_REAL, &chr.rttimer, &chr.old_rttimer);
       // setitimer(ITIMER_VIRTUAL, &chr.rttimerbis, &chr.old_rttimerbis);
		
		// Mise à zéro du tampon de façon à connaître le délimiteur
		// de fin de chaîne.
		//memset(line, 0x0, LINE_ARRAY_SIZE);
		
        envoiFloat[1] = (float)delai; 

		envoiFloatC = (char*)envoiFloat;
		envoiIntC = (char*)envoiInt;
		envoiCharC = (char*)envoiChar;
		for(k=0;k<(25*4);k++){
			paquetEnvoi[k] = envoiFloatC[k];
		}
		for(k=0;k<(63*2);k++){
			paquetEnvoi[k+(25*4)] = envoiIntC[k];
		}
		for(k=0;k<(15*1);k++){
			paquetEnvoi[k+(25*4)+(63*2)] = envoiCharC[k];
		}
		
		// Envoi des donnees
		if (sendto(socketEmission, &paquetEnvoi, sizeof(paquetEnvoi), 0,
				(struct sockaddr *) &adresseMatlabReception,
				sizeof(adresseMatlabReception)) < 0) {
			cout << "Not sent" << endl;
		}
		else {
//			for(k=0;k<25;k++){
//				//cout << "Sent     : " << envoi[k] << endl;
//				//fprintf(stdout,"Sent     PF : %4.3f \n", envoi[k]);
//			}
			cout << "Envoye" << endl;
		}
		
		// Reception des donnees
		if (recvfrom(socketReception, &paquetRecu, sizeof(paquetRecu), 0,
				NULL,
				NULL) < 0) {
			cout << "Not received" << endl;
		}
		else {
//			for(k=0;k<25;k++){
//				//cout << "Received : " << recu[k] << endl;
//				//fprintf(stdout,"Received PF : %4.3f \n", recu[k]);
//				//envoi[k]= (float)delai;
//				//envoi[k]=recu[k];
//			}
			cout << "Recu" << endl;
		}
		
		recuFloatC = (char*)recuFloat;
		recuIntC = (char*)recuInt;
		recuCharC = (char*)recuChar;
		for(k=0;k<(25*4);k++){
			recuFloatC[k] = paquetRecu[k] ;
		}
		for(k=0;k<(63*2);k++){
			recuIntC[k] = paquetRecu[k+(25*4)]; 
		}
		for(k=0;k<(15*1);k++){
			recuCharC[k] = paquetRecu[k+(25*4)+(63*2)];
		}
		
       mesuretemps(&chr.rttimer, &chr.rttimerbis);
       delai = ecrirefichier(chr, fp, s);
		usleep(100000);
	}
    fprintf(fp,"\n");
    //fclose(fp);
}


