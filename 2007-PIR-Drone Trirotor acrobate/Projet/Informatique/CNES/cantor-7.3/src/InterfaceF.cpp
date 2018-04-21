///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Type
//       DEF
//
//$Projet
//       Marmottes
//
//$Application
//       Cantor
//
//$Nom
//>       InterfaceF.cpp
//
//$Resume
//       fichier d'implantation des fonctions d'interface avec le fortran
//
//$Description
//       Module de définition des fonctions d'interface
//
//$Contenu
//>       static int CopieMessageF()           
//>       static RotDBL::AxesRotation ConvertitOrdre()
//>       int rotaxeangle_()        
//>       int rotu1u2v1v2_()        
//>       int rotu1v1_()            
//>       int rotmatrice_()         
//>       int rottroisangles_()
//>       void rotinverse_()        
//>       void rotcomposee_()       
//>       void axerot_()            
//>       void anglerot_()          
//>       void axeanglerot_()       
//>       void matricerot_()        
//>       void troisanglesrot_()
//>       void appliquerot_()       
//>       void appliquerotinverse_()
//
//$Historique
//       $Log: InterfaceF.cpp,v $
//       Revision 1.12  2003/02/04 09:28:25  cantor
//       DM-ID 17 Mise à jour du nom du fichier dans le bandeau suite à la modification des extensions.
//
//       Revision 1.11  2001/06/05 15:45:22  cantor
//       ajout des fonctions rottroisangles_ et troisanglesrot_
//
//       Revision 1.10  2000/10/24 16:25:23  cantor
//       modification des includes pour permettre la compilation avec le
//       compilateur Sun Workshop 5.0
//
//       Revision 1.9  2000/08/09 14:36:42  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.8.4.1  2000/03/30 15:36:06  cantor
//       ajout du copyright CNES
//
//       Revision 1.8  1998/07/29 11:26:19  cantor
//       utilisation de CantorConfig.h
//
//       Revision 1.7  1998/06/24 10:09:48  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.6  1997/07/06 10:29:20  luc
//       ajout d'un en-tête de fichier
//       correction des signatures de longueurs de chaînes de caractères
//       (elles ne sont pas passées par référence)
//
//       Revision 1.5  1997/04/03 19:31:37  luc
//       inversion des codes de retour, 0 signifie désormais : pas d'erreur
//       
//       Revision 1.4  1997/03/26 06:54:31  luc
//       changement des conventions de nommage
//       
//       Revision 1.3  1997/03/24 09:32:41  luc
//       passage de SCCS à RCS
//       
//       Revision 1.2  1995/07/11 14:40:18  mercator
//       modification de la notation des vecteurs (et des fonctions)
//       pour la rendre compatible avec l'interface C++ et la documentation mathematique
//       
//       Revision 1.1  1995/01/19 07:06:55  mercator
//       Initial revision
//
//$Version
//       $Id: InterfaceF.cpp,v 1.12 2003/02/04 09:28:25 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <CantorConfigNoInstall.h>
#include "cantor/InterfaceF.h"


static int CopieMessageF (BaseErreurs *ptrErreur,
                          char *messageErreur, long int lDeclMessage)
{ // copie d'un message d'erreur dans des variables fortran
  int code = ptrErreur->code ();

  // vérification des dépassements de capacité
  int l = strlen (ptrErreur->why ());
  if (l > lDeclMessage)
    l = lDeclMessage;

  // transfert des caractères
  (void) strncpy (messageErreur, ptrErreur->why (), l);
  (void) memset  (messageErreur + l, ' ', lDeclMessage - l);

  // remise à zéro de l'instance d'erreur
  ptrErreur->correction ();

  // on retourne le code d'erreur
  return code;

}

static RotDBL::AxesRotation ConvertitOrdre (int ordre)
  throw (CantorErreurs)
{
    switch (ordre)
    {
       case  1 : // PARAMETER CtrXYZ dans cantdefs.f
         return RotDBL::XYZ;
         break;
       case  2 : // PARAMETER CtrXZY dans cantdefs.f
         return RotDBL::XZY;
         break;
       case  3 : // PARAMETER CtrYXZ dans cantdefs.f
         return RotDBL::YXZ;
         break;
       case  4 : // PARAMETER CtrYZX dans cantdefs.f
         return RotDBL::YZX;
         break;
       case  5 : // PARAMETER CtrZXY dans cantdefs.f
         return RotDBL::ZXY;
         break;
       case  6 : // PARAMETER CtrZYX dans cantdefs.f
         return RotDBL::ZYX;
         break;
       case  7 : // PARAMETER CtrXYX dans cantdefs.f
         return RotDBL::XYX;
         break;
       case  8 : // PARAMETER CtrXZX dans cantdefs.f
         return RotDBL::XZX;
         break;
       case  9 : // PARAMETER CtrYXY dans cantdefs.f
         return RotDBL::YXY;
         break;
       case 10 : // PARAMETER CtrYZY dans cantdefs.f
         return RotDBL::YZY;
         break;
       case 11 : // PARAMETER CtrZXZ dans cantdefs.f
         return RotDBL::ZXZ;
         break;
       case 12 : // PARAMETER CtrZYZ dans cantdefs.f
         return RotDBL::ZYZ;
         break;
       default :
         throw CantorErreurs (CantorErreurs::ordre_inconnu, ordre,
                              "CtrXYZ", "CtrXZY", "CtrYXZ",
                              "CtrYZX", "CtrZXY", "CtrZYX",
                              "CtrXYX", "CtrXZX", "CtrYXY",
                              "CtrYZY", "CtrZXZ", "CtrZYZ",
                              (char *) 0);
         break;
    }
}

int rotaxeangle_ (double q [4], double axe [3], double& angle,
                  char* message, long int lDeclMessage)
{
  try
  {
    VecDBL a (axe [0], axe [1], axe [2]);
    RotDBL r (a, angle);

    // remplissage du tableau des composantes "C" du quaternion
    q [0] = r.q0 ();
    q [1] = r.q1 ();
    q [2] = r.q2 ();
    q [3] = r.q3 ();

    return 0;
  }
  catch (CantorErreurs erreur)
  {
    return CopieMessageF (&erreur, message, lDeclMessage);
  }

}

int rotu1u2v1v2_ (double q  [4],
                  double u1 [3], double u2 [3], double v1 [3], double v2 [3],
                  char* message, long int lDeclMessage)
{

  try
  {
    // vecteurs avant rotation
    VecDBL vecU1 (u1 [0], u1 [1], u1 [2]);
    VecDBL vecU2 (u2 [0], u2 [1], u2 [2]);

    // vecteurs apres rotation
    VecDBL vecV1 (v1 [0], v1 [1], v1 [2]);
    VecDBL vecV2 (v2 [0], v2 [1], v2 [2]);

    RotDBL r (vecU1, vecU2, vecV1, vecV2);

    // remplissage du tableau des composantes "C" du quaternion
    q [0] = r.q0 ();
    q [1] = r.q1 ();
    q [2] = r.q2 ();
    q [3] = r.q3 ();

    return 0;
  }
  catch (CantorErreurs erreur)
  {
    return CopieMessageF (&erreur, message, lDeclMessage);
  }

}

int rotu1v1_ (double q  [4], double u1 [3], double v1 [3],
              char* message, long int lDeclMessage)
{
  try
  {
    VecDBL vecU1 (u1 [0], u1 [1], u1 [2]);
    VecDBL vecV1 (v1 [0], v1 [1], v1 [2]);
    RotDBL r (vecU1, vecV1);

    // remplissage du tableau des composantes "C" du quaternion
    q [0] = r.q0 ();
    q [1] = r.q1 ();
    q [2] = r.q2 ();
    q [3] = r.q3 ();

    return 0;
  }
  catch (CantorErreurs erreur)
  {
    return CopieMessageF (&erreur, message, lDeclMessage);
  }

}

int rotmatrice_ (double q  [4], double matrice [3][3], double& seuil,
                 char* message, long int lDeclMessage)
{

  try
  {
    // transposition de la matrice (entre fortran et C)
    double mTransp [3] [3];
    for (int i = 0; i < 3; i++)
    {
      mTransp [i][i] = matrice [i] [i];
      for (int j = 0; j < i; j++)
      {
        mTransp [j][i] = matrice [i][j];
        mTransp [i][j] = matrice [j][i];
      }
    }

    RotDBL r (mTransp, seuil);

    // remplissage du tableau des composantes "C" du quaternion
    q [0] = r.q0 ();
    q [1] = r.q1 ();
    q [2] = r.q2 ();
    q [3] = r.q3 ();

    return 0;
  }
  catch (CantorErreurs erreur)
  {
    return CopieMessageF (&erreur, message, lDeclMessage);
  }

}

int  rottroisangles_ (double q [4],
                      int& ordre,
                      double& alpha1, double& alpha2, double& alpha3,
                      char* message, long int lDeclMessage)
{

  try
  {

    RotDBL r (ConvertitOrdre (ordre), alpha1, alpha2, alpha3);

    // remplissage du tableau des composantes "C" du quaternion
    q [0] = r.q0 ();
    q [1] = r.q1 ();
    q [2] = r.q2 ();
    q [3] = r.q3 ();

    return 0;
  }
  catch (CantorErreurs erreur)
  {
    return CopieMessageF (&erreur, message, lDeclMessage);
  }

}

void rotinverse_ (double q [4], double qInitiale [4])
{ // pour des raisons de performances, on ne passe pas par RotDBL ici ...
  // (on evite ainsi les appels constructeur/destructeur)

  q [0] = -qInitiale [0];
  q [1] =  qInitiale [1];
  q [2] =  qInitiale [2];
  q [3] =  qInitiale [3];

}

void rotcomposee_ (double q  [4], double q1 [4], double q2 [4])
{
  RotDBL r1 (q1 [0], q1 [1], q1 [2], q1 [3]);
  RotDBL r2 (q2 [0], q2 [1], q2 [2], q2 [3]);
  RotDBL r = r2 (r1);

  // remplissage du tableau des composantes "C" du quaternion
  q [0] = r.q0 ();
  q [1] = r.q1 ();
  q [2] = r.q2 ();
  q [3] = r.q3 ();

}

void axerot_ (double q [4], double axe [3])
{
  RotDBL r (q [0], q [1], q [2], q [3]);
  VecDBL v = r.axe ();

  // remplissage du tableau des composantes "C" du vecteur
  axe [0] = v.x ();
  axe [1] = v.y ();
  axe [2] = v.z ();

}

void anglerot_ (double q [4], double& angle)
{
  RotDBL r (q [0], q [1], q [2], q [3]);
  angle = r.angle ();
}

void axeanglerot_ (double q [4], double axe [3], double& angle)
{
  RotDBL r (q [0], q [1], q [2], q [3]);
  VecDBL v = r.axe   ();
  angle    = r.angle ();

  // remplissage du tableau des composantes "C" du vecteur
  axe [0] = v.x ();
  axe [1] = v.y ();
  axe [2] = v.z ();

}

void matricerot_ (double q [4], double m [3][3])
{
  double mTransp [3][3];
  RotDBL r (q [0], q [1], q [2], q [3]);
  r.initMatrice (mTransp);

  // transposition de la matrice (entre fortran et C)
  for (int i = 0; i < 3; i++)
  { m [i][i] = mTransp [i] [i];
    for (int j = 0; j < i; j++)
    { m [j][i] = mTransp [i][j];
      m [i][j] = mTransp [j][i];
    }
  }

}

int troisanglesrot_ (double q [4], int& ordre,
                     double& alpha1, double& alpha2, double& alpha3,
                     char *message, long int lDeclMessage)
{

  try
  {
    RotDBL r (q [0], q [1], q [2], q [3]);
    r.initAngles (ConvertitOrdre (ordre), &alpha1, &alpha2, &alpha3);
    return 0;
  }
  catch (CantorErreurs erreur)
  {
    return CopieMessageF (&erreur, message, lDeclMessage);
  }

}

void appliquerot_ (double q [4], double u [3], double uPrime [3])
{
  RotDBL r (q [0], q [1], q [2], q [3]);
  VecDBL v (u [0], u [1], u [2]);
  VecDBL vPrime = r (v);

  // remplissage du tableau des composantes "C" du vecteur
  uPrime [0] = vPrime.x ();
  uPrime [1] = vPrime.y ();
  uPrime [2] = vPrime.z ();

}

void appliquerotinverse_ (double q [4], double uPrime [3], double u [3])
{
  RotDBL r (-q [0], q [1], q [2], q [3]);
  VecDBL vPrime (uPrime [0], uPrime [1], uPrime [2]);
  VecDBL v = r (vPrime);

  // remplissage du tableau des composantes "C" du vecteur
  u [0] = v.x ();
  u [1] = v.y ();
  u [2] = v.z ();

}
