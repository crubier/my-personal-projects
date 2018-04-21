#include "supanoid.h"

/*=======================================================*/
/*                       Physique.c                      */
/*=======================================================*/
/* Ce fichier contient le moteur physique du jeu, cad    */
/* la gestion des collisions, des différentes couches,   */
/* de l'attraction entre les objets, les rebonds etc...  */
/*=======================================================*/

void mouvement(PTROBJET objet)
{
    (*objet)=positionsuivante((*objet));
    (*objet).acceleration=vecteur(0,0);
}

void mouvements(void)
{
    PTRCELLULE pcellule;
    pcellule=premierecellule();

    while(pcellule!=NULL)		//On parcourt la liste des objets
    {
		if( (*(*pcellule).element).couche !=0 )	// seuls les objets presents a un etages sont calcules
		{
        	mouvement((*pcellule).element);
		}
        pcellule=(*pcellule).suivant;
    }
}


OBJET positionsuivante(OBJET objet)
{
    OBJET res;
    res=objet;												//On integre les vitesses et les accelerations
 	res.vitesse=somme(res.vitesse,res.acceleration);
 	res.position=somme(res.position,res.vitesse);
 	return res;
}

void rebond(PTRCELLULE pcellulea, PTRCELLULE pcelluleb)
{
    
    COORD normale;
    PTROBJET objeta;
    PTROBJET objetb;
    objeta=(*pcellulea).element;
    objetb=(*pcelluleb).element;
    
    normale=normalecontact(*objeta,*objetb);
    
  
    if(norme(normale)!=0)
 	{
        float coef;

		char temp[LONGCHAINE];
		sprintf(temp,"evenements/collision[%s,%s];",ecrireIDENTIFIANT(*(*pcellulea).identifiant),ecrireIDENTIFIANT(*(*pcelluleb).identifiant));
		executercommande(temp,VIDE);

        coef=((*objeta).rebondissement*(*objetb).rebondissement)/(((*objeta).masse+(*objetb).masse)*norme(normale)*norme(normale));      
  
        //printf("Rebond %s - %s valeur %g\n",(*objeta).nom,(*objetb).nom,coef);

        (*objeta).acceleration=somme((*objeta).acceleration,
            multiplicationscalaire
            (    
                normale,
                -2*coef*((*objetb).masse)*produitscalaire(difference((*objeta).acceleration,(*objetb).acceleration),normale)
            ));
            
        (*objetb).acceleration=somme((*objetb).acceleration,
            multiplicationscalaire
            (    
                normale,
                -2*coef*((*objeta).masse)*produitscalaire(difference((*objetb).acceleration,(*objeta).acceleration),normale)
            ));


        
        (*objeta).acceleration=somme((*objeta).acceleration,
            multiplicationscalaire
            (    
                normale,
                -2*coef*((*objetb).masse)*produitscalaire(difference((*objeta).vitesse,(*objetb).vitesse),normale)
            ));

        
        (*objetb).acceleration=somme((*objetb).acceleration,
            multiplicationscalaire
            (    
                normale,
                -2*coef*((*objeta).masse)*produitscalaire(difference((*objetb).vitesse,(*objeta).vitesse),normale)
            ));
            
        (*objeta).solidite-=(*objetb).agressivite;
        (*objetb).solidite-=(*objeta).agressivite; 
	
		if(norme(normalecontact(*objeta,*objetb))!=0)
		{
			supprimercellule(pcelluleb);
		}      
       
    }     
  
}

void gravitation(PTRCELLULE pcellulea, PTRCELLULE pcelluleb)
{
    PTROBJET objeta;
    PTROBJET objetb;
    objeta=(*pcellulea).element;
    objetb=(*pcelluleb).element;
    COORD posrel;
    float coef;
    COORD vitessea,vitesseb;
    
    posrel=positionrelative(*objeta,*objetb);
    coef= ATTRACTION * ((*objeta).attraction) * ((*objetb).attraction)  * pow(norme(posrel),-2);
    
    //F=GmM/r^2
    
    //printf("Attraction %s - %s valeur %g\n",(*objeta).nom,(*objetb).nom,coef);
    
    (*objeta).acceleration=somme((*objeta).acceleration,
    multiplicationscalaire(posrel,-1*coef/(*objeta).masse));
    
    (*objetb).acceleration=somme((*objetb).acceleration,
    multiplicationscalaire(posrel,1*coef/(*objetb).masse));     
  
}

void frottement(PTRCELLULE pcellule)
{
    PTROBJET objet;
    objet=(*pcellule).element;
    (*objet).acceleration=somme((*objet).acceleration,multiplicationscalaire(positionsuivante(*objet).vitesse,-1*(*objet).frottement));
}

void degradation(PTRCELLULE pcellule)
{
	if(pcellule==NULL)return;
	if((*pcellule).element==NULL)return;
    if((*(*pcellule).element).solidite<=0)
	{
		supprimercellule(pcellule);
	}
	return;
}

void chronometrer(PTRCELLULE pcellule)
{
	float chronoinitial;
	float chronofinal;

	if(pcellule==NULL)return;
	if((*pcellule).element==NULL)return;

	chronoinitial=(*(*pcellule).element).chronometre;
	chronofinal=(*(*pcellule).element).chronometre;

	if(chronoinitial!=0)
	{
		if(chronoinitial>0)
		{
			chronofinal=chronofinal-DT;
		}
		else
		{
			chronofinal=chronofinal+DT;
		}
		if((chronoinitial>=0 && chronofinal<=0) || (chronoinitial<=0 && chronofinal>=0))
		{
			(*(*pcellule).element).chronometre=0;
			char temp[LONGCHAINE];
			sprintf(temp,"evenements/chronometre[%s];",ecrireIDENTIFIANT(*(*pcellule).identifiant));
			executercommande(temp,VIDE);
		}
		else
		{
			(*(*pcellule).element).chronometre=chronofinal;
		}
	}
	return;
}

COORD normalecontact(OBJET objeta, OBJET objetb)
{
 	COORD res;
    COORD dir;

	res=vecteur(0,0);

	if((objeta.couche & objetb.couche) == 0)
	{
		return res;
	}

	if((objeta.forme==RAQUETTE && objetb.forme==CERCLE))
    {
        if(abs(produitscalaire(difference(positionsuivante(objeta).position, positionsuivante(objetb).position),vecteur(1,0)))<abs(produitscalaire(somme(objeta.dimensions,objetb.dimensions),vecteur(0.5,0))) && abs(produitscalaire(difference(positionsuivante(objeta).position, positionsuivante(objetb).position),vecteur(0,1)))<abs(produitscalaire(somme(objeta.dimensions,objetb.dimensions),vecteur(0,0.5))))
        {
            dir=inverse(somme(objeta.dimensions,objetb.dimensions));
            
            res=arrondi(multiplicationscalaire(normalisation(multiplication(difference(objeta.position, objetb.position),dir)),sqrt(0.5)));

            res=normalisation(res);

			res=somme(res,multiplicationscalaire(vecteur(1/objeta.dimensions.x,0),produitscalaire(vecteur(1,0),difference(objeta.position,objetb.position))));
        
            res=normalisation(res);

		}
        else
        {
            res=vecteur(0,0);
        }
	 	return res;
    }

	if((objetb.forme==RAQUETTE && objeta.forme==CERCLE))
    {
        if(abs(produitscalaire(difference(positionsuivante(objeta).position, positionsuivante(objetb).position),vecteur(1,0)))<abs(produitscalaire(somme(objeta.dimensions,objetb.dimensions),vecteur(0.5,0))) && abs(produitscalaire(difference(positionsuivante(objeta).position, positionsuivante(objetb).position),vecteur(0,1)))<abs(produitscalaire(somme(objeta.dimensions,objetb.dimensions),vecteur(0,0.5))))
        {
            dir=inverse(somme(objeta.dimensions,objetb.dimensions));
            
            res=arrondi(multiplicationscalaire(normalisation(multiplication(difference(objeta.position, objetb.position),dir)),sqrt(0.5)));

            res=normalisation(res);

			res=somme(res,multiplicationscalaire(vecteur(-1/objetb.dimensions.x,0),produitscalaire(vecteur(1,0),difference(objeta.position,objetb.position))));

            res=normalisation(res);

		}
        else
        {
            res=vecteur(0,0);
        }
	 	return res;
    }

	if((objeta.forme==RAQUETTE && objetb.forme==RECTANGLE)||(objeta.forme==RECTANGLE && objetb.forme==RAQUETTE))
    {
        if(abs(produitscalaire(difference(positionsuivante(objeta).position, positionsuivante(objetb).position),vecteur(1,0)))<abs(produitscalaire(somme(objeta.dimensions,objetb.dimensions),vecteur(0.5,0))) && abs(produitscalaire(difference(positionsuivante(objeta).position, positionsuivante(objetb).position),vecteur(0,1)))<abs(produitscalaire(somme(objeta.dimensions,objetb.dimensions),vecteur(0,0.5))))
        {
            dir=inverse(somme(objeta.dimensions,objetb.dimensions));
            
            res=arrondi(multiplicationscalaire(normalisation(multiplication(difference(objeta.position, objetb.position),dir)),sqrt(0.5)));

            res=normalisation(res);

        }
        else
        {
            res=vecteur(0,0);
        }
	 	return res;
    }
 
    if(objeta.forme==RECTANGLE || objetb.forme==RECTANGLE)
    {

        if(abs(produitscalaire(difference(positionsuivante(objeta).position, positionsuivante(objetb).position),vecteur(1,0)))<abs(produitscalaire(somme(objeta.dimensions,objetb.dimensions),vecteur(0.5,0))) && abs(produitscalaire(difference(positionsuivante(objeta).position, positionsuivante(objetb).position),vecteur(0,1)))<abs(produitscalaire(somme(objeta.dimensions,objetb.dimensions),vecteur(0,0.5))))
        {
            dir=inverse(somme(objeta.dimensions,objetb.dimensions));
            
            res=arrondi(multiplicationscalaire(normalisation(multiplication(difference(objeta.position, objetb.position),dir)),sqrt(0.5)));

            res=normalisation(res);

        }
        else
        {
            res=vecteur(0,0);
        }
 		return res;
    }

    if(objeta.forme==CERCLE || objetb.forme==CERCLE)
    {
        if(sqrt(8.)*distance(positionsuivante(objeta).position,positionsuivante(objetb).position)<(norme(objeta.dimensions)+norme(objetb.dimensions)))
        {
            res=difference(positionsuivante(objeta).position,positionsuivante(objetb).position);
          
            res=normalisation(res);

        }
        else
        {
            res=vecteur(0,0);
        }
	 	return res;
    }

   /* if(norme(res)!=0)
    {printf("Normale : ");indiquer(res);printf(" Norme : %g \n",norme(res));}*/
    
 	return res;
}

COORD positionrelative(OBJET objeta, OBJET objetb)
{
    COORD res;
    res=difference(positionsuivante(objeta).position,positionsuivante(objetb).position);
    //printf("Position relative : ");indiquer(res);printf("\n");
    return res;
}

void interactions(void)
{
    PTRCELLULE pcellulea;
    PTRCELLULE pcelluleb;
    
    pcellulea=premierecellule();
    while(pcellulea!=NULL)
    {
        pcelluleb=(*pcellulea).suivant;

        while(pcelluleb!=NULL)
        {
            if( ((int)(*(*pcellulea).element).couche & (int)(*(*pcelluleb).element).couche) != 0)  //Comparaison des couches
            {
                gravitation(pcellulea,pcelluleb);
                rebond(pcellulea,pcelluleb);
            }
            pcelluleb=(*pcelluleb).suivant;
        }
        
        if( (*(*pcellulea).element).couche !=0 ) // La couche 0 est inactive
        {
            frottement(pcellulea);
			chronometrer(pcellulea);
            degradation(pcellulea);
        }
        
        pcellulea=(*pcellulea).suivant;
    }
    
}
