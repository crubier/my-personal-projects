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
//>       InterfaceC.cpp
//
//$Resume
//       fichier d'implantation des fonctions d'interface avec le C
//
//$Description
//       Module de définition des fonctions d'interface
//
//$Contenu
//>       static int CopieMessageC()          
//>       static RotDBL::AxesRotation ConvertitOrdre()
//>       int RotAxeAngle()        
//>       int RotU1U2V1V2()        
//>       int RotU1V1()            
//>       int RotMatrice()         
//>       int RotTroisAngles()
//>       void RotInverse()        
//>       void RotComposee()       
//>       void AxeRot()            
//>       void AngleRot()          
//>       void AxeAngleRot()       
//>       void MatriceRot()        
//>       int TroisAnglesRot()
//>       void AppliqueRot()       
//>       void AppliqueRotInverse()
//
//$Historique
//       $Log: InterfaceC.cpp,v $
//       Revision 1.12  2003/02/04 09:28:08  cantor
//       DM-ID 17 Mise à jour du nom du fichier dans le bandeau suite à la modification des extensions.
//
//       Revision 1.11  2001/06/05 15:44:40  cantor
//       ajout des fonctions RotTroisAngles et TroisAnglesRot
//       ajout de lgMaxMessage dans la signature des fonctions
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
//       Revision 1.8  1998/10/05 13:07:59  cantor
//       inclusion de CantorConfig.h pour avoir le prototype de strcpy
//
//       Revision 1.7  1998/06/24 10:09:33  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.6  1997/07/06 10:38:48  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.5  1997/04/03 19:31:24  luc
//       inversion des codes de retour, 0 signifie désormais : pas d'erreur
//       
//       Revision 1.4  1997/03/26 06:54:30  luc
//       changement des conventions de nommage
//       
//       Revision 1.3  1997/03/24 09:32:41  luc
//       passage de SCCS à RCS
//       
//       Revision 1.2  1995/07/11 14:40:15  mercator
//       modification de la notation des vecteurs (et des fonctions)
//       pour la rendre compatible avec l'interface C++ et la documentation mathematique
//       
//       Revision 1.1  1995/01/19 06:35:14  mercator
//       Initial revision
//
//$Version
//       $Id: InterfaceC.cpp,v 1.12 2003/02/04 09:28:08 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <CantorConfigNoInstall.h>
#include "cantor/InterfaceC.h"


static int CopieMessageC (BaseErreurs *ptrErreur,
                          char *messageErreur, long int lgMaxMessage)
{ // copie d'un message d'erreur dans une chaîne C
  int code = ptrErreur->code ();

  // vérification des dépassements de capacité
  int lg = strlen (ptrErreur->why ());
  if (lg >= lgMaxMessage)
    lg = lgMaxMessage - 1;

  // transfert des caractères
  (void) strncpy (messageErreur, ptrErreur->why (), lg);
  messageErreur [lg] = '\0';

  // remise à zéro de l'instance d'erreur
  ptrErreur->correction ();

  // on retourne le code d'erreur
  return code;

}

static RotDBL::AxesRotation ConvertitOrdre (CantorAxesRotation ordre)
  throw (CantorAxesRotation)
{
    switch (ordre)
    {
      case CtrXYZ :
        return RotDBL::XYZ;
        break;
      case CtrXZY :
        return RotDBL::XZY;
        break;
      case CtrYXZ :
        return RotDBL::YXZ;
        break;
      case CtrYZX :
        return RotDBL::YZX;
        break;
      case CtrZXY :
        return RotDBL::ZXY;
        break;
      case CtrZYX :
        return RotDBL::ZYX;
        break;
      case CtrXYX :
        return RotDBL::XYX;
        break;
      case CtrXZX :
        return RotDBL::XZX;
        break;
      case CtrYXY :
        return RotDBL::YXY;
        break;
      case CtrYZY :
        return RotDBL::YZY;
        break;
      case CtrZXZ :
        return RotDBL::ZXZ;
        break;
      case CtrZYZ :
        return RotDBL::ZYZ;
        break;
      default :
        throw CantorErreurs (CantorErreurs::erreur_interne,
                             __LINE__, __FILE__);
        break;
    }
}

int RotAxeAngle (double q [4], double axe [3], double angle,
                 char* message, int lgMaxMessage)
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
    return CopieMessageC (&erreur, message, lgMaxMessage);
  }

}

int RotU1U2V1V2 (double q  [4],
                 double u1 [3], double u2 [3], double v1 [3], double v2 [3],
                 char* message, int lgMaxMessage)
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
    return CopieMessageC (&erreur, message, lgMaxMessage);
  }

}

int RotU1V1 (double q  [4], double u1 [3], double v1 [3],
             char* message, int lgMaxMessage)
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
    return CopieMessageC (&erreur, message, lgMaxMessage);
  }

}

int RotMatrice (double q  [4], double matrice [3][3], double seuil,
                char* message, int lgMaxMessage)
{
  try
  {
    RotDBL r (matrice, seuil);

    // remplissage du tableau des composantes "C" du quaternion
    q [0] = r.q0 ();
    q [1] = r.q1 ();
    q [2] = r.q2 ();
    q [3] = r.q3 ();

    return 0;
  }
  catch (CantorErreurs erreur)
  {
    return CopieMessageC (&erreur, message, lgMaxMessage);
  }

}

int  RotTroisAngles (double q [4],
                     CantorAxesRotation ordre,
                     double alpha1, double alpha2, double alpha3,
                     char* message, int lgMaxMessage)
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
    return CopieMessageC (&erreur, message, lgMaxMessage);
  }

}

void RotInverse (double q [4], double qInitiale [4])
{ // pour des raisons de performances, on ne passe pas par RotDBL ici ...
  // (on evite ainsi les appels constructeur/destructeur)

  q [0] = -qInitiale [0];
  q [1] =  qInitiale [1];
  q [2] =  qInitiale [2];
  q [3] =  qInitiale [3];

}

void RotComposee (double q  [4], double q1 [4], double q2 [4])
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

void AxeRot (double q [4], double axe [3])
{
  RotDBL r (q [0], q [1], q [2], q [3]);
  VecDBL v = r.axe ();

  // remplissage du tableau des composantes "C" du vecteur
  axe [0] = v.x ();
  axe [1] = v.y ();
  axe [2] = v.z ();

}

void AngleRot (double q [4], double* pAngle)
{
  RotDBL r (q [0], q [1], q [2], q [3]);
  *pAngle = r.angle ();
}

void AxeAngleRot (double q [4], double axe [3], double* pAngle)
{
  RotDBL r (q [0], q [1], q [2], q [3]);
  VecDBL v = r.axe   ();
  *pAngle  = r.angle ();

  // remplissage du tableau des composantes "C" du vecteur
  axe [0] = v.x ();
  axe [1] = v.y ();
  axe [2] = v.z ();

}

void MatriceRot (double q [4], double m [3][3])
{
  RotDBL r (q [0], q [1], q [2], q [3]);
  r.initMatrice (m);
}

int  TroisAnglesRot (double q [4], CantorAxesRotation ordre,
                     double *pAlpha1, double *pAlpha2, double *pAlpha3,
                     char* message, int lgMaxMessage)
{

  try
  {
    RotDBL r (q [0], q [1], q [2], q [3]);
    r.initAngles (ConvertitOrdre (ordre), pAlpha1, pAlpha2, pAlpha3);
    return 0;
  }
  catch (CantorErreurs erreur)
  {
    return CopieMessageC (&erreur, message, lgMaxMessage);
  }

}

void AppliqueRot (double q [4], double u [3], double uPrime [3])
{
  RotDBL r (q [0], q [1], q [2], q [3]);
  VecDBL v (u [0], u [1], u [2]);
  VecDBL vPrime = r (v);

  // remplissage du tableau des composantes "C" du vecteur
  uPrime [0] = vPrime.x ();
  uPrime [1] = vPrime.y ();
  uPrime [2] = vPrime.z ();

}

void AppliqueRotInverse (double q [4], double uPrime [3], double u [3])
{
  RotDBL r (-q [0], q [1], q [2], q [3]);
  VecDBL vPrime (uPrime [0], uPrime [1], uPrime [2]);
  VecDBL v = r (vPrime);

  // remplissage du tableau des composantes "C" du vecteur
  u [0] = v.x ();
  u [1] = v.y ();
  u [2] = v.z ();

}
