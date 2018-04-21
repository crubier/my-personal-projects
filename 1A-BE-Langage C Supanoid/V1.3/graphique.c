#include "supanoid.h"

/*=======================================================*/
/*                   Graphique.c                         */
/*=======================================================*/
/* Ce fichier contient les fonctions liees a l'interface */
/* utilisateur,n s'appuyant principalement sur           */
/* le TDA 'COORD' et les reels                           */
/* Ces fonctions sont principalement utilisees par       */
/* le moteur physique, mais peuvent aussi etre appelees  */
/* par l'utilisateur                                     */
/*=======================================================*/

void clavier(void)
{
	char temp[LONGCHAINE];
	switch (getLastKeyPressed())
        { 
            case -1:
                break;
            case VK_LEFT:
                (*(*raquette).element).acceleration.x=-SENSIBILITE;
                break;
            case VK_RIGHT:
                (*(*raquette).element).acceleration.x=SENSIBILITE;
                break;
            case VK_UP:
                (*(*raquette).element).acceleration.y=SENSIBILITE;
                break;
            case VK_DOWN:   
                (*(*raquette).element).acceleration.y=-SENSIBILITE;
                break;
            case VK_Q:
                (*(*fenetre).element).acceleration.x=-SENSIBILITE;
                break;
            case VK_D:
                (*(*fenetre).element).acceleration.x=SENSIBILITE;
                break;
            case VK_Z:
                (*(*fenetre).element).acceleration.y=SENSIBILITE;
                break;
            case VK_S:
                (*(*fenetre).element).acceleration.y=-SENSIBILITE;
                break;
            case VK_ESCAPE:
                fini = 1;      
                break;
			case VK_A:
				executercommande("modifierparametre[focus,(fenetre:fenetre:1)];",VIDE);
				(*(*fenetre).element).position=lireCOORD("(0:0)");
				(*(*fenetre).element).vitesse=lireCOORD("(0:0)");
				(*(*fenetre).element).acceleration=lireCOORD("(0:0)");
				break;
			case VK_T:
				if(recherchertypenom(creeridentifiant("trounoir","trounoir",0),premierecellule(),1)==NULL)
			    executercommande("actions/creertrounoir[];",VIDE);
				break;
			case VK_Y:
			    executercommande("actions/tuertrounoir[];",VIDE);
				break;
            case VK_F1:
                decrireLISTEdetail();
                break;
            case VK_F2:
                executercommande("initialiser[];",VIDE);
                break;
            case VK_F3:
                DT*=2;
                break;
            case VK_F4:
                DT/=2;
                break;
			case VK_F6:
				SENSIBILITE/=1.05;
				break;
			case VK_F7:
				SENSIBILITE*=1.05;
				break;
			case VK_F8:
				executercommande("affichernoms[255];",VIDE);
				break;
			case VK_F9:
				executercommande("cachernoms[255];",VIDE);
				break;
            case VK_P:
                pause();
                break;
            case VK_ENTER:
                scanf("%s",temp);
				executercommande(temp,VIDE);
                break;
            case VK_SPACE:
				executercommande("actions/balles/creerballes[vecteur_somme[propriete[(raquette:raquette:1),position],(0:40)]];",VIDE);
                break;
            case VK_X:
				executercommande("actions/balles/explosionballes[(0:0),(0:0)];",VIDE);
                break;
            case VK_W:
				executercommande("modifierparametre[focus,(raquette:raquette:1)];",VIDE);
                break;
            case VK_B:
				executercommande("actions/raquette/raquette+[];",VIDE);
                break;
            case VK_N:
				executercommande("actions/raquette/raquette-[];",VIDE);
                break;

        }
}

void dessin(void)
{
    PTRCELLULE pcellule;
    int i;
    pcellule=premierecellule();

	setForegroundColor((*(*fenetre).element).couleur);
	clearRect(0, 0, (*(*fenetre).element).dimensions.x,(*(*fenetre).element).dimensions.y);
    for(i=1;i<=COUCHES;i*=2)
    {
        while(pcellule!=NULL)
        {
            if( i & (*(*pcellule).element).couche != 0 )     //Comparaison des couches
            {
                dessiner(pcellule);
            }
            pcellule=(*pcellule).suivant;
        }
    }
    paint(); 
}

void dessiner(PTRCELLULE pcellule)
{
    FILE* fichier;
   	char nom[LONGCHAINE];
    float x,y;
    x=((*(*pcellule).element).position.x-0.5*(*(*pcellule).element).dimensions.x)-((*(*focus).element).position.x-0.5*(*(*fenetre).element).dimensions.x);
    y=(-(*(*pcellule).element).position.y-0.5*(*(*pcellule).element).dimensions.y)-(-(*(*focus).element).position.y-0.5*(*(*fenetre).element).dimensions.y);


    setForegroundColor((*(*pcellule).element).couleur);

    if(strcmp((*(*pcellule).element).graphique,"INCONNU")!=0)/*si le fichier n'existe pas, rien ne sera affiché, les formes seront affichée sulement si graphique = INCONNU*/
    {
        sprintf(nom,"mondes/%s/images/%s.png",repertoire,(*(*pcellule).element).graphique);
        drawImage(nom, x,y);
    }
    else
    {
        if((*(*pcellule).element).forme==CERCLE) 
        {
            fillOval(x,y, (*(*pcellule).element).dimensions.x, (*(*pcellule).element).dimensions.y);
        }
        else
        {
            fillRect(x,y, (*(*pcellule).element).dimensions.x, (*(*pcellule).element).dimensions.y);
        }
    }

	if(strcmp((*(*pcellule).element).texte,"INCONNU")!=0)
    {
		strcpy(nom,(*(*pcellule).element).texte);
		
        drawText(nom, x,y);
    }

}

void decrireLISTE(void)
{
	fprintf(journal,"Liste : %s\n",ecrireLISTE());
}

void decrireLISTEdetail(void)
{
	char res[LONGCHAINE];
	char temp[LONGCHAINE];
	int i;
	
		fprintf(journal,"\n==================================================\n");
		fprintf(journal,"Description détaillée de la liste\n");
		fprintf(journal,"==================================================\n\n");

	strcpy(temp,VIDE);
	for(i=1;i<=nombrecellules();i++)
	{
		fprintf(journal,"--------------------------------------------------\n");
		fprintf(journal,"Objet : %s \n\n",ecrireIDENTIFIANT(*(*cellulenumero(i)).identifiant));
		fprintf(journal,"%s\n",ecrireOBJET(*(*cellulenumero(i)).element));
		fprintf(journal,"--------------------------------------------------\n");
	}

		fprintf(journal,"==================================================\n");
		fprintf(journal,"Fin de la description détaillée de la liste\n");
		fprintf(journal,"==================================================\n\n");

}

void decrireCELLULE(PTRCELLULE pcellule)
{
	if(pcellule==NULL)
	{
		fprintf(journal,"NULL\n");
	}
	else
	{
		fprintf(journal,"%s\n",ecrireIDENTIFIANT(*(*pcellule).identifiant));
	}
}

void initialisation(void)
{

	fprintf(journal,"Initialisation ");
    fenetre=recherchertype(creeridentifiant("fenetre","fenetre",1),premierecellule(),1);
    raquette=recherchertype(creeridentifiant("raquette","raquette",1),premierecellule(),1);
    focus=fenetre;
	fprintf(journal,"fenetre : %s ",ecrireIDENTIFIANT(*(*fenetre).identifiant));

	SENSIBILITE=0.5;
    DT=0.002;
    ATTRACTION=0.1;
	fini = 0;

	fprintf(journal,": OK\n");   
}

void initialisationgraphique()
{
    start((int)(*(*fenetre).element).dimensions.x,(int)(*(*fenetre).element).dimensions.y);

    setBackgroundColor(BLACK);
    setForegroundColor(RED);

	setFontSize(12);
	setFontStyle(PLAIN);

    registerKeyPressed(VK_ENTER);   
    registerKeyPressed(VK_SPACE);   
    registerKeyPressed(VK_LEFT);       
    registerKeyPressed(VK_RIGHT);     
    registerKeyPressed(VK_UP);       
    registerKeyPressed(VK_DOWN); 
    registerKeyPressed(VK_F1); 
    registerKeyPressed(VK_F2); 
    registerKeyPressed(VK_F3); 
    registerKeyPressed(VK_F4);
    registerKeyPressed(VK_F5); 
    registerKeyPressed(VK_F6); 
    registerKeyPressed(VK_F7); 
    registerKeyPressed(VK_F8); 
    registerKeyPressed(VK_F9); 
    registerKeyPressed(VK_F10); 
    registerKeyPressed(VK_F11); 
    registerKeyPressed(VK_F12); 
    registerKeyPressed(VK_A);
    registerKeyPressed(VK_B);
    registerKeyPressed(VK_C);
    registerKeyPressed(VK_D);
    registerKeyPressed(VK_E);
    registerKeyPressed(VK_F);
    registerKeyPressed(VK_G);
    registerKeyPressed(VK_H);
    registerKeyPressed(VK_I);
    registerKeyPressed(VK_J);
    registerKeyPressed(VK_K);
    registerKeyPressed(VK_L);
    registerKeyPressed(VK_M);
    registerKeyPressed(VK_N);
    registerKeyPressed(VK_O);
    registerKeyPressed(VK_P);
    registerKeyPressed(VK_Q);
    registerKeyPressed(VK_R);
    registerKeyPressed(VK_S);
    registerKeyPressed(VK_T);
    registerKeyPressed(VK_U);
    registerKeyPressed(VK_V);
    registerKeyPressed(VK_W);
    registerKeyPressed(VK_X);
    registerKeyPressed(VK_Y);
    registerKeyPressed(VK_Z);

    setBackgroundColor((*(*fenetre).element).couleur);        
    clearRect(0, 0, (int)(*(*fenetre).element).dimensions.x, (int)(*(*fenetre).element).dimensions.y); 
}
void cloture(void)
{ 
}

void cloturegraphique(void)
{
    finish(); 
}

