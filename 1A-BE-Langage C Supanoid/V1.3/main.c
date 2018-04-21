#include "supanoid.h"

/*=======================================================*/
/*                       Main.c                          */
/*=======================================================*/
/* Le fichier main est simplifie au maximum afin de      */
/* laisser apparaitre la structure globale du programme. */
/*=======================================================*/

int main(int argc, char *argv[])
{
	
	origineliste=NULL;								// On initialise d'abord les variables						
	raquette=NULL;
	fenetre=NULL;
	modefonctionnement=0;

	demanderparametres(argc,argv);					// On va chercher les parametres dans les arguments donnes au programme, sinon on les demande
    executercommande("monde[]",VIDE);						// On execute le fichier 'monde' dans le repertoire actuel
    initialisation();								// On initialise les variables
	initialisationgraphique();						// On initialise le moteur graphique
    executercommande("initialisation[]",VIDE);				// On execute le fichier 'initialisation' lorsque tout est prêt

    while (!fini) 									// Tant que 'fini' est nul
    {        
        clavier();									// On recherche les touches appuyees et on execute les actions associees
        interactions();								// On calcule les interactions entre les objets
        mouvements();								// On en deduit les mouvements des objets
        dessin();                     				// On dessine les objets
        sleepAWhile((int)(1000*DT));				// On attend pendant le pas de temps
    }

    cloture();										// A la fin, on ferme les variables
	cloturegraphique();								// Et on ferme la fenetre
    return 1;
}
