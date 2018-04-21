#include "supanoid.h"

/*=======================================================*/
/*                   Geometrie.c                         */
/*=======================================================*/
/* Ce fichier contient les fonctions de base de la       */
/* géometrie, en s'appuyant principalement sur           */
/* le TDA 'COORD' et les reels                           */
/* Ces fonctions sont principalement utilisees par       */
/* le moteur physique, mais peuvent aussi etre appelees  */
/* par l'utilisateur                                     */
/*=======================================================*/

COORD vecteur(float x, float y)
{
    COORD res;
    res.x=x;
    res.y=y;
    return res;
}

COORD polaire2cartesien(COORD a)
{
    COORD res;
    res.x=(a.x)*cos(a.y);
    res.y=(a.x)*sin(a.y);
    return res;
}

COORD cartesien2polaire(COORD a)
{
    COORD res;
    res.y=atan2((a.y),(a.x));
    res.x=sqrt((a.x)*(a.x)+(a.y)*(a.y));
    return res;
}
    
COORD somme(COORD a, COORD b)
{
    COORD res;
    res.x=a.x+b.x;
    res.y=a.y+b.y;
    return res;
}

COORD oppose(COORD a)
{
    COORD res;
    res.x=-a.x;
    res.y=-a.y;
    return res;
}

COORD difference(COORD a, COORD b)
{
    return somme(a,oppose(b));
}

COORD inverse(COORD a)
{
    COORD res;
    if(a.x==0 || a.y==0) return a;
    res.x=1/a.x;
    res.y=1/a.y;
    return res;
}

COORD multiplication(COORD a, COORD b)
{
    COORD res;
    res.x=a.x*b.x;
    res.y=a.y*b.y;
    return res;
}

COORD multiplicationscalaire(COORD a, float k)
{
    return multiplication(a,vecteur(k,k));
}

float produitscalaire(COORD a, COORD b)
{
    return total(multiplication(a,b));
}

COORD normalisation(COORD a)
{
    if(norme(a)==0)return a;
    return multiplicationscalaire(a,1/norme(a));
}

float distance(COORD a, COORD b)
{
    return norme(difference(a,b));
}

float norme(COORD a)
{
    return sqrt(produitscalaire(a,a));
}

float total(COORD a)
{
    return a.x+a.y;
}

COORD arrondi(COORD a)
{
    return vecteur(round(a.x),round(a.y));
}
