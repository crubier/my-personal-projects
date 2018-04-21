#include "supanoid.h"

/*=======================================================*/
/*                   Interface.c                         */
/*=======================================================*/
/* Ce fichier contient les fonctions liees a l'interface */
/* utilisateur, c'est a dire les fonctions d'affichage   */
/* et de verification des touches activees               */
/*=======================================================*/

void pause(void)
{
	//On met le programme en pause
	system("pause");
	return;
}

void clavier(void)
{
	char temp[LONGCHAINE];

	//On teste simplement les touches
	switch (getLastKeyPressed())
        { 
            case -1:
                break;
            case VK_RIGHT:
                (*(*raquette).element).acceleration=vecteur(SENSIBILITE,0);
                break;
            case VK_LEFT:
                (*(*raquette).element).acceleration=vecteur(-SENSIBILITE,0);
                break;
            case VK_UP:
                (*(*raquette).element).acceleration=vecteur(0,SENSIBILITE);
                break;
            case VK_DOWN:   
                (*(*raquette).element).acceleration=vecteur(0,-SENSIBILITE);
                break;
            case VK_NUMPAD0:
                break;
            case VK_NUMPAD1:
                (*(*fenetre).element).acceleration=vecteur(-SENSIBILITE,-SENSIBILITE);
                break;
            case VK_NUMPAD2:
                (*(*fenetre).element).acceleration=vecteur(0,-SENSIBILITE);
                break;
            case VK_NUMPAD3:
                (*(*fenetre).element).acceleration=vecteur(SENSIBILITE,-SENSIBILITE);
                break;
            case VK_NUMPAD4:
                (*(*fenetre).element).acceleration=vecteur(-SENSIBILITE,0);
                break;
            case VK_NUMPAD5:
                (*(*fenetre).element).position=vecteur(0,0);
                (*(*fenetre).element).vitesse=vecteur(0,0);
                (*(*fenetre).element).acceleration=vecteur(0,0);
                break;
            case VK_NUMPAD6:
                (*(*fenetre).element).acceleration=vecteur(SENSIBILITE,0);
                break;
            case VK_NUMPAD7:
                (*(*fenetre).element).acceleration=vecteur(-SENSIBILITE,SENSIBILITE);
                break;
            case VK_NUMPAD8:
                (*(*fenetre).element).acceleration=vecteur(0,SENSIBILITE);
                break;
            case VK_NUMPAD9:
                (*(*fenetre).element).acceleration=vecteur(SENSIBILITE,SENSIBILITE);
                break;
            case VK_ESCAPE:
                fini = 1;      
                break;
   			case VK_ENTER:
                scanf("%s",temp);
				executercommande(temp,VIDE);
                break;
            case VK_F1:
				executerfichier("evenements/touches/F1");
                break;
            case VK_F2:
				executerfichier("evenements/touches/F2");
                break;
            case VK_F3:
				executerfichier("evenements/touches/F3");
                break;
            case VK_F4:
				executerfichier("evenements/touches/F4");
                break;
			case VK_F5:
				executerfichier("evenements/touches/F5");
				break;
			case VK_F6:
				executerfichier("evenements/touches/F6");
				break;
			case VK_F7:
				executerfichier("evenements/touches/F7");
				break;
			case VK_F8:
				executerfichier("evenements/touches/F8");
				break;
			case VK_F9:
				executerfichier("evenements/touches/F9");
				break;
			case VK_F10:
				executerfichier("evenements/touches/F10");
				break;
			case VK_F11:
				executerfichier("evenements/touches/F11");
				break;
			case VK_F12:
				executerfichier("evenements/touches/F12");
				break; 
            case VK_SPACE:
				executerfichier("evenements/touches/ESPACE");
                break;
            case VK_A:
				executerfichier("evenements/touches/A");
                break;
            case VK_B:
				executerfichier("evenements/touches/B");
                break;
            case VK_C:
				executerfichier("evenements/touches/C");
                break;
            case VK_D:
				executerfichier("evenements/touches/D");
                break;
            case VK_E:
				executerfichier("evenements/touches/E");
                break;
            case VK_F:
				executerfichier("evenements/touches/F");
                break;
            case VK_G:
				executerfichier("evenements/touches/G");
                break;
            case VK_H:
				executerfichier("evenements/touches/H");
                break;
            case VK_I:
				executerfichier("evenements/touches/I");
                break;
            case VK_J:
				executerfichier("evenements/touches/J");
                break;
            case VK_K:
				executerfichier("evenements/touches/K");
                break;
            case VK_L:
				executerfichier("evenements/touches/L");
                break;
            case VK_M:
				executerfichier("evenements/touches/M");
                break;
            case VK_N:
				executerfichier("evenements/touches/N");
                break;
            case VK_O:
				executerfichier("evenements/touches/O");
                break;
            case VK_P:
				executerfichier("evenements/touches/P");
                break;
            case VK_Q:
				executerfichier("evenements/touches/Q");
                break;
            case VK_R:
				executerfichier("evenements/touches/R");
                break;
            case VK_S:
				executerfichier("evenements/touches/S");
                break;
            case VK_T:
				executerfichier("evenements/touches/T");
                break;
            case VK_U:
				executerfichier("evenements/touches/U");
                break;
            case VK_V:
				executerfichier("evenements/touches/V");
                break;
            case VK_W:
				executerfichier("evenements/touches/W");
                break;
            case VK_X:
				executerfichier("evenements/touches/X");
                break;
            case VK_Y:
				executerfichier("evenements/touches/Y");
                break;
            case VK_Z:
				executerfichier("evenements/touches/Z");
                break;
            case VK_1:
				executerfichier("evenements/touches/1");
                break;
            case VK_2:
				executerfichier("evenements/touches/2");
                break;
            case VK_3:
				executerfichier("evenements/touches/3");
                break;
            case VK_4:
				executerfichier("evenements/touches/4");
                break;
            case VK_5:
				executerfichier("evenements/touches/5");
                break;
            case VK_6:
				executerfichier("evenements/touches/6");
                break;
            case VK_7:
				executerfichier("evenements/touches/7");
                break;
            case VK_8:
				executerfichier("evenements/touches/8.");
                break;
            case VK_9:
				executerfichier("evenements/touches/9");
                break;
            case VK_0:
				executerfichier("evenements/touches/0");
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
    for(i=1;i<=COUCHES;i*=2)								// On parcourt les couches
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

	if(pcellule==NULL)
	{
		fprintf(journal,"Erreur dessin\n");
		return;
	}
	else
	{
		if((*pcellule).element==NULL)
		{
			fprintf(journal,"Erreur dessin\n");
			return;
		}
		else
		{
			if((*(*pcellule).element).graphique==NULL || (*(*pcellule).element).texte==NULL)
			{
				fprintf(journal,"Erreur dessin\n");
				return;
			}
			else
			{

			    setForegroundColor((*(*pcellule).element).couleur);
			
			    if(strcmp((*(*pcellule).element).graphique,"INCONNU")!=0)//si le fichier n'existe pas, rien ne sera affiché, les formes seront affichée seulement si graphique = INCONNU
			    {
			        sprintf(nom,"mondes/%s/images/%s.png",repertoire,(*(*pcellule).element).graphique);
			        drawImage(nom, x,y);
			    }
			    else
			    {
				//affichage de la forme de l'objet
			        if((*(*pcellule).element).forme==CERCLE) 
			        {
			            fillOval(x,y, (*(*pcellule).element).dimensions.x, (*(*pcellule).element).dimensions.y);
			        }
			        else
			        {
			            fillRect(x,y, (*(*pcellule).element).dimensions.x, (*(*pcellule).element).dimensions.y);
			        }
			    }
				
				//affichage du texte
				if(strcmp((*(*pcellule).element).texte,"INCONNU")!=0)
			    {
					strcpy(nom,(*(*pcellule).element).texte);
					
			        drawText(nom, x,y);
			    }
			}
		}
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

	//initialisation des variables globales
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
    registerKeyPressed(VK_0);
    registerKeyPressed(VK_1);
    registerKeyPressed(VK_2);
    registerKeyPressed(VK_3);
    registerKeyPressed(VK_4);
    registerKeyPressed(VK_5);
    registerKeyPressed(VK_6);
    registerKeyPressed(VK_7);
    registerKeyPressed(VK_8);
    registerKeyPressed(VK_9);
    registerKeyPressed(VK_NUMPAD0);
    registerKeyPressed(VK_NUMPAD1);
    registerKeyPressed(VK_NUMPAD2);
    registerKeyPressed(VK_NUMPAD3);
    registerKeyPressed(VK_NUMPAD4);
    registerKeyPressed(VK_NUMPAD5);
    registerKeyPressed(VK_NUMPAD6);
    registerKeyPressed(VK_NUMPAD7);
    registerKeyPressed(VK_NUMPAD8);
    registerKeyPressed(VK_NUMPAD9);

    setBackgroundColor((*(*fenetre).element).couleur);        
    clearRect(0, 0, (int)(*(*fenetre).element).dimensions.x, (int)(*(*fenetre).element).dimensions.y); 
}
void cloture(void)
{ 
	PTRCELLULE pcellule;
	PTRCELLULE pcellulesuivant;
	pcellule=premierecellule();


//Ca fait planter le programme dans certaines conditions lorsque l'on met ça... bizarre

/*	while(pcellule!=NULL)
	{
		pcellulesuivant=(*pcellule).suivant;
		supprimerobjet((*pcellule).element);
		supprimeridentifiant((*pcellule).identifiant);
		free(pcellule);
		pcellule=pcellulesuivant;
	}*/

	origineliste=NULL;
	raquette=NULL;
	fenetre=NULL;
}

void cloturegraphique(void)
{
    finish(); 
}

