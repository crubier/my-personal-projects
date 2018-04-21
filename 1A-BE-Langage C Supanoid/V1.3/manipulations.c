#include "supanoid.h"

/*=======================================================*/
/*                   Manipulations.c                     */
/*=======================================================*/
/* Ce fichier contient toutes les fonction concernant    */
/* la gestion des listes, des cellules, de leur contenu  */
/* (objets et identifiant), la modification des          */
/* parametres , la recherhce d'elements etc...           */
/*=======================================================*/


// Manipulation du TDA OBJET 

PTROBJET creerobjet
(
        COORD position,
 		COORD vitesse,
 		COORD acceleration,
 		int couche,

 		FORME forme,
 		COORD dimensions,
 		float masse,
 		float frottement,
 		float rebondissement,
 		float attraction,
 		float solidite,
 		float agressivite,

 		char* graphique,
        char* texte,
        COULEUR couleur,
		float chronometre
)

{
    PTROBJET pobjet;
    char* temp;
    
    pobjet=malloc(sizeof(OBJET));

	if(pobjet==NULL)return NULL;
    
    (*pobjet).position=position;
    (*pobjet).vitesse=vitesse;
    (*pobjet).acceleration=acceleration;
    (*pobjet).couche=couche;
    
    (*pobjet).forme=forme;
    (*pobjet).dimensions=dimensions;
    (*pobjet).masse=masse;
    (*pobjet).frottement=frottement;
    (*pobjet).rebondissement=rebondissement;
    (*pobjet).solidite=solidite;
    (*pobjet).attraction=attraction;
    (*pobjet).agressivite=agressivite;

    (*pobjet).graphique=creerchaine(graphique);
    (*pobjet).texte=creerchaine(texte);
    (*pobjet).couleur=couleur;
	(*pobjet).chronometre=chronometre;
    
    return pobjet;
}

PTROBJET copierobjet(PTROBJET pobjet)
{
	if(pobjet==NULL)return NULL;
    return creerobjet
    (
        (*pobjet).position,
 		(*pobjet).vitesse,
 		(*pobjet).acceleration,
 		(*pobjet).couche,

 		(*pobjet).forme,
 		(*pobjet).dimensions,
 		(*pobjet).masse,
 		(*pobjet).frottement,
 		(*pobjet).rebondissement,
 		(*pobjet).attraction,
 		(*pobjet).solidite,
 		(*pobjet).agressivite,

 		(*pobjet).graphique,
        (*pobjet).texte,
        (*pobjet).couleur,
		(*pobjet).chronometre
    
    );
}

PTROBJET nouvelobjet(void)
{
    return creerobjet
    (
        vecteur(0,0),
 		vecteur(0,0),
 		vecteur(0,0),
 		1,

 		INCONNUE,
 		vecteur(0,0),
 		1,
 		0,
 		1,
 		0,
 		1000000,
 		0,

 		"INCONNU",
        "INCONNU",
        NOIR,
		0
    );
}

void supprimerobjet(PTROBJET pobjet)
{
    if(pobjet==NULL)return;
	free((*pobjet).graphique);
	free((*pobjet).texte);
	free(pobjet);
}

// Manipulation du TDA IDENTIFIANT 

PTRIDENTIFIANT creeridentifiant
(
 		char* type,
        char* nom,
        int numero
)

{
    PTRIDENTIFIANT pidentifiant;
      
    pidentifiant=malloc(sizeof(IDENTIFIANT));
    
	if(pidentifiant==NULL)return NULL;

    (*pidentifiant).type=creerchaine(type);
    
    (*pidentifiant).nom=creerchaine(nom);

    (*pidentifiant).numero=numero;
    
    return pidentifiant;
}

PTRIDENTIFIANT copieridentifiant(PTRIDENTIFIANT pidentifiant)
{
	if(pidentifiant==NULL)return NULL;
    return creeridentifiant
    (
 		(*pidentifiant).type,
        (*pidentifiant).nom,
        (*pidentifiant).numero
    );
}

PTRIDENTIFIANT nouvelidentifiant(void)
{
    return creeridentifiant
    (
 		"INCONNU",
        "INCONNU",
        0
    );
}

void supprimeridentifiant(PTRIDENTIFIANT pidentifiant)
{
    if(pidentifiant==NULL)return;
	free((*pidentifiant).type);
	free((*pidentifiant).nom);
	free(pidentifiant);
}


// Manipulation du TDA CHAINELISTE

PTRCHAINELISTE creerchaineliste
(
	char* nom,
	char* chaine,
	PTRCHAINELISTE suivant
)
{
	PTRCHAINELISTE pchaineliste;
	pchaineliste=malloc(sizeof(CHAINELISTE));
	(*pchaineliste).nom=creerchaine(VIDE);
	(*pchaineliste).chaine=creerchaine(VIDE);
	(*pchaineliste).suivant=suivant;
	return pchaineliste;
}

void lierchaineliste(PTRCHAINELISTE originechaineliste,	PTRCHAINELISTE element)
{
	(*chainelistedernierelement(originechaineliste)).suivant=element;
}

PTRCHAINELISTE longueurchaineliste(PTRCHAINELISTE originechaineliste)
{
	PTRCHAINELISTE pchaineliste;
	int i;
	i=0;
	if(pchaineliste==NULL)return 0;
	while((*pchaineliste).suivant!=NULL)
	{
		i++;
		pchaineliste=(*pchaineliste).suivant;
	}
	return i;
}

PTRCHAINELISTE chainelisteelementnumero(PTRCHAINELISTE originechaineliste, int i)
{
	PTRCHAINELISTE pchaineliste;
	int j;
	if(pchaineliste==NULL)return NULL;
	for(j=0;j<i;j++)
	{
		if((*pchaineliste).suivant!=NULL)
		{
			pchaineliste=(*pchaineliste).suivant;
		}
		if(pchaineliste==NULL) return NULL;
	}
	return pchaineliste;
}

PTRCHAINELISTE chainelistepremierelement(PTRCHAINELISTE originechaineliste)
{
	return chainelisteelementnumero(originechaineliste,0);
}

PTRCHAINELISTE chainelistedernierelement(PTRCHAINELISTE originechaineliste)
{
	return chainelisteelementnumero(originechaineliste,longueurchaineliste(originechaineliste));
}

PTRCHAINELISTE nouvellechaineliste(void)
{
	return creerchaineliste
	(
		VIDE,
		VIDE,
		NULL
	);
}

void supprimerchaineliste(PTRCHAINELISTE pchaineliste)
{
    if(pchaineliste==NULL)return;
	supprimerchaineliste((*pchaineliste).suivant);
	free((*pchaineliste).nom);
	free((*pchaineliste).chaine);
	free(pchaineliste);
}

// Manipulation du TDA CELLULE

PTRCELLULE creercellule
(
    PTROBJET element, 
 	PTRIDENTIFIANT identifiant,
	PTRCELLULE suivant,
	PTRCELLULE precedent
)
{
    PTRCELLULE pcellule;
    pcellule=malloc(sizeof(CELLULE));
    
	if(pcellule==NULL)return NULL;

    (*pcellule).element=element;
    (*pcellule).identifiant=identifiant;
    (*pcellule).suivant=suivant;
    (*pcellule).precedent=precedent;
    
    if(origineliste==NULL)
    {
        origineliste=pcellule;
    }
    else
    {
        liercellules(dernierecellule(),pcellule);
    }
    return pcellule;
}

PTRCELLULE copiercellule(PTRCELLULE pcellule)
{
	if(pcellule==NULL)return NULL;
    return creercellule
    (
 		copierobjet((*pcellule).element),
        copieridentifiant((*pcellule).identifiant),
        NULL,
        NULL
    );
}

PTRCELLULE nouvellecellule(void)
{
    return creercellule
    (
 		nouvelobjet(),
        nouvelidentifiant(),
        NULL,
        NULL
    );
}


void supprimercellule(PTRCELLULE pcellule)
{
	if(pcellule==NULL)return;

	char temp[LONGCHAINE];
	sprintf(temp,"evenements/mort[%s];",ecrireIDENTIFIANT(*(*pcellule).identifiant));
	executercommande(temp,VIDE);

	if((*pcellule).suivant!=NULL && (*pcellule).precedent!=NULL)
	{
		(*(*pcellule).suivant).precedent=(*pcellule).precedent;
		(*(*pcellule).precedent).suivant=(*pcellule).suivant;
	}
	else
	{
		if((*pcellule).precedent==NULL)
		{
			(*(*pcellule).suivant).precedent=NULL;
		}
		if((*pcellule).suivant==NULL)
		{
			(*(*pcellule).precedent).suivant=NULL;
		}
	}

	if(pcellule==origineliste)
	{
		if((*pcellule).suivant!=NULL || (*pcellule).precedent!=NULL)	
		{
			if((*pcellule).precedent!=NULL)
			{
				origineliste=(*pcellule).precedent;
			}
			else
			{
				origineliste=(*pcellule).suivant;
			}
		}
		else
		{
			origineliste=NULL;
		}
	}
	
	(*pcellule).precedent=NULL;
	(*pcellule).suivant=NULL;

	supprimerobjet((*pcellule).element);
	supprimeridentifiant((*pcellule).identifiant);
	free(pcellule);

}

void liercellules(PTRCELLULE pcellulea, PTRCELLULE pcelluleb)
{
    (*pcellulea).suivant=pcelluleb;
    (*pcelluleb).precedent=pcellulea;
	verifiercellules(pcellulea,pcelluleb);
}

void verifiercellules(PTRCELLULE pcellulea, PTRCELLULE pcelluleb)
{
    if(
    ((*pcellulea).suivant==pcelluleb) && ((*pcelluleb).precedent==pcellulea) ||
    ((*pcellulea).precedent==pcelluleb) && ((*pcelluleb).suivant==pcellulea) ||    
    ((*pcellulea).suivant!=pcelluleb) && ((*pcelluleb).precedent!=pcellulea) ||
    ((*pcellulea).precedent!=pcelluleb) && ((*pcelluleb).suivant!=pcellulea)  
    )return;
    fprintf(journal,"Probleme de liaison de la liste au niveau des cellules %s et %s",(*(*pcellulea).identifiant).nom,(*(*pcelluleb).identifiant).nom);
}

void verifierpointeur(char* p)
{
    if(p == NULL)
    {
        exit (1);
    }
}




// fonctions de recherche et reperage

PTRCELLULE rechercher(PTRIDENTIFIANT pidentifiant)
{
    return recherchertypenomnumero(pidentifiant, cellulenumero(1),1);
}

PTRCELLULE cellulenumero(int i)
{
    PTRCELLULE pcellule;
    int j;

	if(origineliste!=NULL)
	{
		pcellule=origineliste;
	}
	else
	{
		return NULL;
	}
	
	if(i>nombrecellules() || i<1)
	{
		return NULL;
	}

	while((*pcellule).precedent!=NULL)
	{
		pcellule=(*pcellule).precedent;
	}

	j=0;
    while(j<i-1 && (*pcellule).suivant!=NULL)
	{
		pcellule=(*pcellule).suivant;
		j++;
	}

    return pcellule;
}

int nombrecellules(void)
{
	PTRCELLULE pcellule;
    int i;

	i=0;

	if(origineliste!=NULL)
	{
		pcellule=origineliste;
	}
	else
	{
		return 0;
	}
	
	while((*pcellule).precedent!=NULL)
	{
		pcellule=(*pcellule).precedent;
	}


	while(pcellule!=NULL)
	{
		i++;
		pcellule=(*pcellule).suivant;

	}
    return i;
}

PTRCELLULE premierecellule(void)
{
    return cellulenumero(1);
}

PTRCELLULE dernierecellule(void)
{
    return cellulenumero(nombrecellules());
}

PTRIDENTIFIANT prochainidentifiant(PTRIDENTIFIANT pidentifiantdepart)
{
	PTRCELLULE pcellule;
	PTRIDENTIFIANT pidentifiant;
	if(pidentifiantdepart==NULL ) return NULL;
	pcellule=premierecellule();
	pidentifiant=copieridentifiant(pidentifiantdepart);

	while(pcellule!=NULL)
	{
		if((*pcellule).suivant==NULL)break;
		pcellule=recherchertypenom(pidentifiant,(*pcellule).suivant,1);
		if(pcellule==NULL)
		{
			break;
		}
		else
		{
			if((*(*pcellule).identifiant).numero > (*pidentifiant).numero)
			{
				(*pidentifiant).numero=(*(*pcellule).identifiant).numero;
			}
		}
	}

	(*pidentifiant).numero++;
	return copieridentifiant(pidentifiant);
}	

int nombretype(PTRIDENTIFIANT pidentifiant)
{
	int res;
	PTRCELLULE pcellule;
	if(pidentifiant==NULL ) return -1;
	pcellule=premierecellule();
	res=0;
	while(pcellule!=NULL)
	{
		if(compareridentifiantstype(pidentifiant,(*pcellule).identifiant)==0)
		{
			res++;
		}
		pcellule=(*pcellule).suivant;
	}
	return res;
}

int nombretypenom(PTRIDENTIFIANT pidentifiant)
{
	int res;
	PTRCELLULE pcellule;
	if(pidentifiant==NULL ) return -1;
	pcellule=premierecellule();
	res=0;
	while(pcellule!=NULL)
	{
		if(compareridentifiantstypenom(pidentifiant,(*pcellule).identifiant)==0)
		{
			res++;
		}
		pcellule=(*pcellule).suivant;
	}
	return res;
}

int nombretypenomnumero(PTRIDENTIFIANT pidentifiant)
{
	int res;
	PTRCELLULE pcellule;
	if(pidentifiant==NULL ) return -1;
	pcellule=premierecellule();
	res=0;
	while(pcellule!=NULL)
	{
		if(compareridentifiantstypenomnumero(pidentifiant,(*pcellule).identifiant)==0)
		{
			res++;
		}
		pcellule=(*pcellule).suivant;
	}
	return res;
}

PTRCELLULE recherchertype(PTRIDENTIFIANT pidentifiant, PTRCELLULE pi, int sens)
{
    PTRCELLULE pcellule;
    pcellule=pi;

	if(pcellule==NULL)return NULL;

    while(pcellule!=NULL)
    {
        if(compareridentifiantstype(pidentifiant,(*pcellule).identifiant)==0)
        {
            return pcellule;
        }
        if(sens>=0)
		{
			pcellule=(*pcellule).suivant;
		}
		else
		{
			pcellule=(*pcellule).precedent;
		}
    }

    return NULL;
}

PTRCELLULE recherchertypenom(PTRIDENTIFIANT pidentifiant, PTRCELLULE pi, int sens)
{
    PTRCELLULE pcellule;
    pcellule=pi;

	if(pcellule==NULL)return NULL;

    while(pcellule!=NULL)
    {
        if(compareridentifiantstypenom(pidentifiant,(*pcellule).identifiant)==0)
        {
            return pcellule;
        }
        if(sens>=0)
		{
			pcellule=(*pcellule).suivant;
		}
		else
		{
			pcellule=(*pcellule).precedent;
		}
    }

    return NULL;
}


PTRCELLULE recherchertypenomnumero(PTRIDENTIFIANT pidentifiant, PTRCELLULE pi, int sens)
{
    PTRCELLULE pcellule;
    pcellule=pi;

	if(pcellule==NULL)return NULL;

    while(pcellule!=NULL)
    {
        if(compareridentifiantstypenomnumero(pidentifiant,(*pcellule).identifiant)==0)
        {
            return pcellule;
        }
        if(sens>=0)
		{
			pcellule=(*pcellule).suivant;
		}
		else
		{
			pcellule=(*pcellule).precedent;
		}
    }
    return NULL;
}

int compareridentifiantstype(PTRIDENTIFIANT pidentifianta,PTRIDENTIFIANT pidentifiantb)
{
	if(pidentifianta==NULL || pidentifiantb==NULL) return -1;
	return strcmp((*pidentifianta).type,(*pidentifiantb).type);
}

int compareridentifiantstypenom(PTRIDENTIFIANT pidentifianta,PTRIDENTIFIANT pidentifiantb)
{
	if(pidentifianta==NULL || pidentifiantb==NULL) return -1;
	if(strcmp((*pidentifianta).nom,(*pidentifiantb).nom)==0)
        {
            return strcmp((*pidentifianta).type,(*pidentifiantb).type);
        }
        else
        {
            return strcmp((*pidentifianta).nom,(*pidentifiantb).nom);
        } 
}

int compareridentifiantstypenomnumero(PTRIDENTIFIANT pidentifianta,PTRIDENTIFIANT pidentifiantb)
{
	if(pidentifianta==NULL || pidentifiantb==NULL) return -1;
    if(((*pidentifianta).numero-(*pidentifiantb).numero)==0)
    {
        if(strcmp((*pidentifianta).nom,(*pidentifiantb).nom)==0)
        {
            return strcmp((*pidentifianta).type,(*pidentifiantb).type);
        }
        else
        {
            return strcmp((*pidentifianta).nom,(*pidentifiantb).nom);
        } 
    }
    else
    {        
        return((*pidentifianta).numero - (*pidentifiantb).numero);
    }
}

// creation de chaines de caractere

char* creerchaine(char* chaine)
{
    char* res;
	if(chaine==NULL)return NULL;
    res=malloc((strlen(chaine)+2)*sizeof(char));
    strcpy(res,chaine);
    return res;
}

void supprimerchaine(char* chaine)
{
    free(chaine);
}

char* modifierchaine(char* anciennechaine,char* nouvellechaine)
{
    supprimerchaine(anciennechaine);
	return(creerchaine(nouvellechaine));
}

// lecture et ecriture des differents types de donnes a partir de chaines

int lireint(char* chaine)
{
	int res;
	res=0;
	if(sscanf(chaine,"%d",&res)!=1)fprintf(journal,"Erreur de lireint\n");
	return res;
}

char* ecrireint(int a)
{
	char res[LONGCHAINE];
	strcpy(res,"0");
	sprintf(res,"%d",a);	
	return creerchaine(res);
}

float lirefloat(char* chaine)
{
	float res;
	res=0;
	if(sscanf(chaine,"%f",&res)!=1)fprintf(journal,"Erreur de lirefloat\n");
	return res;
}

char* ecrirefloat(float a)
{
	char res[LONGCHAINE];
	strcpy(res,"0.");
	sprintf(res,"%g",a);	
	return creerchaine(res);
}

COORD lireCOORD(char* chaine)
{
	COORD res;
	int conv;
	res.x=0;
	res.y=0;
	conv=sscanf(chaine,"(%f:%f)",&(res.x),&(res.y));
	if(conv!=2)
	{
		res.x=0;
		res.y=0;
		fprintf(journal ,"erreur de lirecoord\n");
	}
	return res;
}

char* ecrireCOORD(COORD a)
{
	char res[LONGCHAINE];
	strcpy(res,"(0:0)");
	sprintf(res,"(%g:%g)",a.x,a.y);	
	return creerchaine(res);
}

FORME lireFORME(char* chaine)
{
    if(strcmp(chaine,"CERCLE")==0)return CERCLE;
    if(strcmp(chaine,"RECTANGLE")==0)return RECTANGLE;
    if(strcmp(chaine,"RAQUETTE")==0)return RAQUETTE;
	fprintf(journal,"Erreur de lireforme\n");
    return INCONNUE;
}

char* ecrireFORME(FORME a)
{
	char res[LONGCHAINE];
	strcpy(res,"INCONNUE");
    if(a==CERCLE)strcpy(res,"CERCLE");
    if(a==RECTANGLE)strcpy(res,"RECTANGLE");
    if(a==RAQUETTE)strcpy(res,"RAQUETTE");
    return creerchaine(res);
}

COULEUR lireCOULEUR(char* chaine)
{
    if(strcmp(chaine,"BLANC")==0)return BLANC;
    if(strcmp(chaine,"NOIR")==0)return NOIR;
    if(strcmp(chaine,"ROUGE")==0)return ROUGE;
    if(strcmp(chaine,"BLEU")==0)return BLEU;
    if(strcmp(chaine,"VERT")==0)return VERT;
    if(strcmp(chaine,"JAUNE")==0)return JAUNE;
    if(strcmp(chaine,"CYAN")==0)return CYAN;
    if(strcmp(chaine,"GRIS")==0)return GRIS;
    if(strcmp(chaine,"MAGENTA")==0)return MAGENTA;
    if(strcmp(chaine,"ORANGE")==0)return ORANGE;
    if(strcmp(chaine,"ROSE")==0)return ROSE;
	fprintf(journal,"Erreur de lirecouleur\n");
    return NOIR;
}

char* ecrireCOULEUR(COULEUR a)
{
	char res[LONGCHAINE];
	strcpy(res,"NOIR");
    if(a==BLANC)strcpy(res,"BLANC");
    if(a==NOIR)strcpy(res,"NOIR");
    if(a==ROUGE)strcpy(res,"ROUGE");
    if(a==BLEU)strcpy(res,"BLEU");
    if(a==VERT)strcpy(res,"VERT");
    if(a==JAUNE)strcpy(res,"JAUNE");
    if(a==CYAN)strcpy(res,"CYAN");
    if(a==GRIS)strcpy(res,"GRIS");
    if(a==MAGENTA)strcpy(res,"MAGENTA");
    if(a==ORANGE)strcpy(res,"ORANGE");
    if(a==ROSE)strcpy(res,"ROSE");
    return creerchaine(res);
}

IDENTIFIANT lireIDENTIFIANT(char* chaine)
{
	PTRIDENTIFIANT pres;
	char type[LONGCHAINE];
	char nom[LONGCHAINE];
	int numero;
	int conv;

	conv=sscanf(chaine," ( %[a-zA-Z0-9 ]: %[a-zA-Z0-9 ] : %d ) ",type,nom,&numero);

	if(conv==3)
	{
		pres=creeridentifiant(type,nom,numero);
	}
	else
	{
		pres=nouvelidentifiant();
		fprintf(journal,"Erreur de lireidentifiant\n");
	}

	return *pres;
}

char* ecrireIDENTIFIANT(IDENTIFIANT a)
{
	char res[LONGCHAINE];
	strcpy(res,VIDE);
	sprintf(res,"(%s:%s:%d)",a.type,a.nom,a.numero);
	return creerchaine(res); 
}

char* ecrireOBJET(OBJET a)
{
	char res[20*LONGCHAINE];
	char temp[LONGCHAINE];

	strcpy(res,VIDE);

    sprintf(temp,"Position         : %s \n",ecrireCOORD(a.position));
	strcat(res,temp);
 	sprintf(temp,"Vitesse          : %s \n",ecrireCOORD(a.vitesse));
	strcat(res,temp);
 	sprintf(temp,"Acceleration     : %s \n",ecrireCOORD(a.acceleration));
	strcat(res,temp);
 	sprintf(temp,"Couche           : %s \n",ecrireint(a.couche));
	strcat(res,temp);
	sprintf(temp,"Forme            : %s \n",ecrireFORME(a.forme));
	strcat(res,temp);
	sprintf(temp,"Dimensions       : %s \n",ecrireCOORD(a.dimensions));
	strcat(res,temp);
	sprintf(temp,"Masse            : %s \n",ecrirefloat(a.masse));
	strcat(res,temp);
	sprintf(temp,"Frottement       : %s \n",ecrirefloat(a.frottement));
	strcat(res,temp);
	sprintf(temp,"Rebondissement   : %s \n",ecrirefloat(a.rebondissement));
	strcat(res,temp);
	sprintf(temp,"Solidite         : %s \n",ecrirefloat(a.solidite));
	strcat(res,temp);
	sprintf(temp,"Attraction       : %s \n",ecrirefloat(a.attraction));
	strcat(res,temp);
	sprintf(temp,"Agressivite      : %s \n",ecrirefloat(a.agressivite));
	strcat(res,temp);
	sprintf(temp,"Graphique        : %s \n",(a.graphique));
	strcat(res,temp);
    sprintf(temp,"Texte            : %s \n",(a.texte));
	strcat(res,temp);
    sprintf(temp,"Couleur          : %s \n",ecrireCOULEUR(a.couleur));
	strcat(res,temp);
    sprintf(temp,"Chronometre      : %s \n",ecrirefloat(a.chronometre));
	strcat(res,temp);

	return creerchaine(res); 
}

char* ecrireLISTE(void)
{
	char res[10*LONGCHAINE];
	char temp[10*LONGCHAINE];
	int i;
	
	strcpy(temp,VIDE);
	for(i=1;i<nombrecellules();i++)
	{
		strcat(temp,ecrireIDENTIFIANT(*(*cellulenumero(i)).identifiant));
		strcat(temp,",");
	}
	strcat(temp,ecrireIDENTIFIANT(*(*dernierecellule()).identifiant));
	sprintf(res,"{%s}",temp);
	return creerchaine(res);
}

PTRCELLULE lireOBJET(char* chaine)
{
	IDENTIFIANT identifiant;

	identifiant=lireIDENTIFIANT(chaine);

	return rechercher(&identifiant);
}


// Lecture et ecriture des proprietes et parametres des objets.

void entrerpropriete(PTRCELLULE pcellule, char* propriete, char* valeur)
{
    PTROBJET pobjet;

	if(pcellule==NULL)return ;
    pobjet = (*pcellule).element;
	if(pobjet==NULL)return ;

    if(strcmp(propriete,"position")==0)
    {
        (*pobjet).position=lireCOORD(valeur);
    }
    
    if(strcmp(propriete,"vitesse")==0)
    {
        (*pobjet).vitesse=lireCOORD(valeur);
    }
    
    if(strcmp(propriete,"acceleration")==0)
    {
        (*pobjet).acceleration=lireCOORD(valeur);
    }
    
    if(strcmp(propriete,"couche")==0)
    {
        (*pobjet).couche=lireint(valeur);
    }
    
    if(strcmp(propriete,"forme")==0)
    {
        (*pobjet).forme=lireFORME(valeur);
    }
    
    if(strcmp(propriete,"dimensions")==0)
    {
        (*pobjet).dimensions=lireCOORD(valeur);
    }
       
    if(strcmp(propriete,"masse")==0)
    {
        (*pobjet).masse=lirefloat(valeur);
    }
    
    if(strcmp(propriete,"frottement")==0)
    {
        (*pobjet).frottement=lirefloat(valeur);
    }
    
    if(strcmp(propriete,"rebondissement")==0)
    {
        (*pobjet).rebondissement=lirefloat(valeur);
    }
    
    if(strcmp(propriete,"solidite")==0)
    {
        (*pobjet).solidite=lirefloat(valeur);
    }
    
    if(strcmp(propriete,"attraction")==0)
    {
        (*pobjet).attraction=lirefloat(valeur);
    }
    
    if(strcmp(propriete,"agressivite")==0)
    {
        (*pobjet).agressivite=lirefloat(valeur);
    }
      
    if(strcmp(propriete,"graphique")==0)
    {
        (*pobjet).graphique=creerchaine(valeur);
    }
     
  	if(strcmp(propriete,"texte")==0)
    {
        (*pobjet).texte=creerchaine(valeur);
    }

    if(strcmp(propriete,"couleur")==0)
    {
        (*pobjet).couleur=lireCOULEUR(valeur);
    }

    if(strcmp(propriete,"chronometre")==0)
    {
        (*pobjet).chronometre=lirefloat(valeur);
    }
        
    return ;
}


char* afficherpropriete(PTRCELLULE pcellule, char* propriete)
{
    PTROBJET pobjet;

	if(pcellule==NULL)
	{
		fprintf(journal,"Impossible d afficherpropriete pcellule=null");
		return VIDE;
	}

    pobjet = (*pcellule).element;

	if(pobjet==NULL)
	{
		fprintf(journal,"Impossible d afficherpropriete pobjet=null");
		return VIDE;
	}

    if(strcmp(propriete,"position")==0)
    {
        return ecrireCOORD((*pobjet).position);
    }
    
    if(strcmp(propriete,"vitesse")==0)
    {
        return ecrireCOORD((*pobjet).vitesse);
    }
    
    if(strcmp(propriete,"acceleration")==0)
    {
		return ecrireCOORD((*pobjet).acceleration);
    }
    
    if(strcmp(propriete,"couche")==0)
    {
        return ecrireint((*pobjet).couche);
    }
    
    if(strcmp(propriete,"forme")==0)
    {
        return ecrireFORME((*pobjet).forme);
    }
    
    if(strcmp(propriete,"dimensions")==0)
    {
        return ecrireCOORD((*pobjet).dimensions);
    }
       
    if(strcmp(propriete,"masse")==0)
    {
        return ecrirefloat((*pobjet).masse);
    }
    
    if(strcmp(propriete,"frottement")==0)
    {
        return ecrirefloat((*pobjet).frottement);
    }
    
    if(strcmp(propriete,"rebondissement")==0)
    {
        return ecrirefloat((*pobjet).rebondissement);
    }
    
    if(strcmp(propriete,"solidite")==0)
    {
        return ecrirefloat((*pobjet).solidite);
    }
    
    if(strcmp(propriete,"attraction")==0)
    {
        return ecrirefloat((*pobjet).attraction);
    }
    
    if(strcmp(propriete,"agressivite")==0)
    {
        return ecrirefloat((*pobjet).agressivite);
    }
      
    if(strcmp(propriete,"graphique")==0)
    {
        return creerchaine((*pobjet).graphique);
    }
     
  	if(strcmp(propriete,"texte")==0)
    {
        return creerchaine((*pobjet).texte);
    }

    if(strcmp(propriete,"couleur")==0)
    {
        return ecrireCOULEUR((*pobjet).couleur);
    }
        
    if(strcmp(propriete,"chronometre")==0)
    {
        return ecrirefloat((*pobjet).chronometre);
    }

    return ;
}


char* afficherparametre(char* chaine)
{
	if(strcmp(chaine+1*LONGCHAINE*sizeof(char),"dt")==0)
	{
		return ecrirefloat(DT);
	}

	if(strcmp(chaine+1*LONGCHAINE*sizeof(char),"sensibilite")==0)
	{
		return ecrirefloat(SENSIBILITE);
	}

	if(strcmp(chaine+1*LONGCHAINE*sizeof(char),"attraction")==0)
	{
		return ecrirefloat(ATTRACTION);
	}

	if(strcmp(chaine+1*LONGCHAINE*sizeof(char),"focus")==0)
	{
		return ecrireIDENTIFIANT(*(*focus).identifiant);
	}

	return VIDE;
}
