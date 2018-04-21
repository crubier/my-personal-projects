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
//       Marmottes
//
//$Nom
//>       ModeleGeom.cpp
//
//$Resume
//       fichier d'implantation de la classe ModeleGeom
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class ModeleGeom          
//>         ModeleGeom()            
//>         operator =()            
//>         prendConsignesEnCompte()
//>         intersection()    
//>         attitude()              
//
//$Historique
//       $Log: ModeleGeom.cpp,v $
//       Revision 2.19  2003/02/04 16:31:01  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 2.18  2002/01/17 09:20:05  marmottes
//       (prendConsignesEnCompte): passage de l'axe du cône de consigne dans la construction des familles fixes (FA 0007)
//
//       Revision 2.17  2001/06/06 08:16:16  luc
//       remontée des exceptions Cantor
//       prise en compte du déplacement de Secteurs vers cantor
//
//       Revision 2.16  2000/09/13 11:01:17  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 2.15  2000/03/30 17:01:19  luc
//       ajout du copyright CNES
//
//       Revision 2.14  1999/10/15 13:04:35  filaire
//       modification du calcul de cosGamma pour s'affranchir de cos > 1
//
//       Revision 2.13  1999/10/15 11:55:49  luc
//       transfert de la responsabilité de la désallocation mémoire des
//       familles à la classe d'encapsulation Famille (pour corriger un bug de
//       fuite mémoire)
//
//       Revision 2.12  1999/09/14 07:56:38  filaire
//       ajout de marges sur le domaine de validité de théta (précision machine)
//
//       Revision 2.11  1999/08/25 09:42:05  filaire
//       Suppression des marges prises sur le domaine de validité de théta dans
//       le cas particulier (Mu1=Gamma=Pi/2)
//
//       Revision 2.10  1999/07/29 12:17:18  filaire
//       Restructuration de la classe en accord avec le nouveau modele
//       mathematique (utilisation des Familles de solutions)
//
//       Revision 2.9  1998/09/14 11:48:15  luc
//       simplification d'un test
//
//       Revision 2.8  1998/08/04 06:57:25  luc
//       élimination des recollements de familles dans les modèles
//
//       Revision 2.7  1998/07/22 06:32:40  luc
//       génération d'une erreur pour les consignes incompatibles
//
//       Revision 2.6  1998/06/24 19:59:06  luc
//       élimination des variables statiques RCS
//       modification du format des en-têtes
//
//       Revision 2.5  1998/06/08 15:56:13  luc
//       élimination d'attributs inutilisés
//
//       Revision 2.4  1998/04/26 18:25:11  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 2.3  1998/02/19 16:20:04  luc
//       déplacement d'un constructeur inline dans le .cc
//       pour contourner un problème d'optimiseur avec g++ 2.8.0
//
//       Revision 2.2  1997/11/27 06:54:17  luc
//       correction d'un commentaire
//
//       Revision 2.1  1997/09/14 19:59:53  luc
//       remplacement de ModeleGeomMono et de ModeleGeomAlig
//       par la nouvelle classe ModeleGeomV1Fixe
//
//       Revision 1.10  1997/08/20 08:31:08  luc
//       ajout d'un en-tête de fichier
//       réorganisation du code à raison d'une seule classe par fichier
//
//       Revision 1.9  1997/04/27 19:35:57  luc
//       inversion des codes de retour
//       changement des règles de nommage
//       passage de SCCS à RCS
//       
//       Revision 1.8  1996/10/18 07:50:40  luc
//       ajout d'une protection contre des divisions par zéro
//       
//       Revision 1.7  1996/10/03 14:40:29  luc
//       correction de la gestion du prolongement par continuité
//       
//       Revision 1.6  1996/06/03 10:24:00  luc
//       élimination d'une constante calculée avant exécution du programme principal
//       (le compilateur fortran semble incapable de l'initialiser correctement)
//       la constante est désormais recalculée à chaque modélisation
//       
//       Revision 1.5  1995/09/12 06:44:48  mercator
//       correction du sens d'application de la rotation entre le repere
//       canonique de resolution et le repere satellite
//       
//       Revision 1.4  1995/02/10 12:10:07  mercator
//       correction de l'oubli de desactivation des modeles particuliers
//       (cas de vecteurs cibles alignes, cas d'axes alignes)
//       
//       Revision 1.3  1995/02/06 08:07:53  mercator
//       prise en compte du spin precedent pour estimer le spin courant
//       incorporation de l'extrapolation de spin dans la classe Etat
//       
//       Revision 1.2  1995/01/27 16:59:40  mercator
//       propagation du spin dans tous les calculs depuis la modelisation
//       jusqu'a la sauvegarde de la solution finale dans l'etat
//       
//       Revision 1.1  1994/12/23 11:00:07  luc
//       Initial revision
//
//$Version
//       $Id: ModeleGeom.cpp,v 2.19 2003/02/04 16:31:01 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES et G. Filaire CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "cantor/Secteurs.h"

#include "marmottes/ModeleGeom.h"
#include "marmottes/SenseurGeometrique.h"

const double sinUneSec = 4.8e-6;

// limite d'alignement: eps = sin (1") * sin (1")
const double epsAligne = sinUneSec * sinUneSec;

//constructeur par défaut
ModeleGeom::ModeleGeom ()
  : nombreFamilles_ (0), table_ (0)
{}

// constructeur par copie
ModeleGeom::ModeleGeom (const ModeleGeom& m)
  : Modele (m), nombreFamilles_ (m.nombreFamilles_), 
    table_ (m.table_), canSat_ (m.canSat_)
{}

//opérateur d'affectation
ModeleGeom& ModeleGeom::operator = (const ModeleGeom& m)
{ 
  if (&m != this)   // protection contre x = x
 { 
   Modele::operator  = (m);
   nombreFamilles_   = m.nombreFamilles_;
   table_            = m.table_;
   canSat_           = m.canSat_;
 }
 return *this;
}

void ModeleGeom::prendConsignesEnCompte () throw (MarmottesErreurs)
{ // mise à jour du modèle géométrique selon les nouvelles consignes
  nombreFamilles_ = 0;
  table_.clear();

  // récupération des senseurs géométriques
  SenseurGeometrique* s1 = (SenseurGeometrique *) (senseur1 ());
  SenseurGeometrique* s2 = (SenseurGeometrique *) (senseur2 ());

  // données constantes du modèle
  VecVD1 u1           = VecDBLVD1 (s1->cible ());
  VecVD1 u2           = VecDBLVD1 (s2->cible ());
  double cosMu_1      = s1->secteursConsigne ().cone ().cosinus ();
  double cosMu_2      = s2->secteursConsigne ().cone ().cosinus ();
  double sinMu_1      = s1->secteursConsigne ().cone ().sinus ();
  double sinMu_2      = s2->secteursConsigne ().cone ().sinus ();
  double sinAlpha_1_2 = (s1->cible () ^ s2->cible ()).norme ();
  double cosAlpha_1_2 = s1->cible () | s2->cible ();

  // calculs intermédiaires servant à tous les modèles
  double cosPlus      = cosAlpha_1_2  * cosMu_2 - sinAlpha_1_2 * sinMu_2;
  double cosMoins     = cosAlpha_1_2  * cosMu_2 + sinAlpha_1_2 * sinMu_2;

  VecDBL a1Sat        = s1->secteursConsigne ().cone ().axe ();
  VecDBL a2Sat        = s2->secteursConsigne ().cone ().axe ();
  double gamma        = angle (a1Sat, a2Sat);
  double cosGamma     = cos (gamma);
  double sinGamma     = sin (gamma);
  double sinPlus      = sinGamma  * cosMu_1 + cosGamma * sinMu_1;
  double sinMoins     = sinGamma  * cosMu_1 - cosGamma * sinMu_1;
  
  VecVD1 a2Can        = VecVD1 (0.0, 0.0, 1.0);
  VecVD1 a1Can        = VecVD1 (sinGamma, 0.0, cosGamma);
  VecVD1 moinsA1Can   = - a1Can;
  VecVD1 moinsA2Can   = - a2Can;

  double cosCos       = cosMu_1  * cosGamma;
  double sinSin       = sinMu_1  * sinGamma;

  double cosMin;
  double cosMax;

  if ((sinSin >= -epsAligne) && (sinSin < epsAligne))
  { // on est dans le cas d'alignement des deux axes de consignes a1 et a2
    // Il faut redéfinir la rotation canSat_ qui est indéfinie
    // on prend n'importe quelle rotation qui amène a2 en k
    canSat_ = RotDBLVD1 (RotDBL (VecDBL (0.0, 0.0, 1.0), a2Sat));
    if ((cosPlus <= cosCos) && (cosCos <= cosMoins))
    { // tous les theta sont valides
      cosMin = -2.0;
      cosMax =  2.0;
      //VecVD1 moinsISat = canSat_ (VecDBLVD1 (VecDBL (-1.0, 0.0, 0.0)));
      VecVD1 moinsISat = canSat_ (VecVD1 (-1.0, 0.0, 0.0));
      VecDBL ref = VecVD1DBL (moinsISat);
      s1->nouvelleReferenceSecteurs (ref);
    }
    else
    { // aucun theta n'est valide
      cosMin = -3.0;
      cosMax = -2.0;
    }
  }
  else
  { 
    canSat_             = RotDBLVD1 (RotDBL (VecDBL (0.0, 0.0, 1.0),
                                             VecDBL (1.0, 0.0, 0.0),
                                             a2Sat, a1Sat));
    s1->nouvelleReferenceSecteurs (a2Sat);
    cosMin = (cosPlus  - cosCos) / sinSin;
    cosMax = (cosMoins - cosCos) / sinSin;
  }

  if (sinAlpha_1_2 <= sinUneSec)
  { // les vecteurs v1 et v2 sont alignés
    Cone consigne_2_prime (s2->secteursConsigne ().cone ());
    if (cosAlpha_1_2 < 0.0)
    { // cas TRÈS RARE: deux cibles différentes sont opposées !...
      consigne_2_prime = Cone (-s2->secteursConsigne ().cone ().axe   (),
                                s2->secteursConsigne ().cone ().angle ());
    }

    try
    {
      // v1 est figé à l'intersection des deux cônes de consigne
      VecDBL v1a;
      VecDBL v1b;
      s1->secteursConsigne ().cone ().intersection (consigne_2_prime,
                                                    &v1a, &v1b);

      // mise en place des modèles fixes
      Intervalle i  = Intervalle (-M_PI , M_PI);
      VecVD1 v1aCan = (-canSat_) (VecDBLVD1 (v1a));
      VecVD1 v1bCan = (-canSat_) (VecDBLVD1 (v1b));
      table_.push_back (Famille (new FamilleFixe (i, u1, u2, v1aCan, v1bCan,
                                                  v1aCan),
                                 false));
      nombreFamilles_++;
      table_.push_back (Famille (new FamilleFixe (i, u1, u2, v1bCan, v1aCan,
                                                  v1bCan),
                                 false));
      nombreFamilles_++;

      // il est inutile de continuer, il n'y aura pas d'autres familles
      return;
    }
    catch (CantorErreurs ce)
    { // on ne peut pas faire de modèle analytique !
      ce.correction ();
      throw MarmottesErreurs (MarmottesErreurs::consignes_incompatibles,
                              s1->nom ().c_str (),
                              s2->nom ().c_str ());
    }

  }
 
  // conversion de l'intervalle de cos (theta) en créneau de consigne et de validité
  // modification de la référence du secteur 1 pour être homogène avec theta
  Creneau creneauConsigne1 = s1->creneauConsigne ();
  s2->nouvelleReferenceSecteurs (a1Sat);
  Creneau creneauConsigne2 = s2->creneauConsigne ();
  Creneau creneauInter;

  // création des tables de familles
  int nombreIntervallesSecteur1 = creneauConsigne1.nombre ();
  int nombreIntervallesSecteur2 = creneauConsigne2.nombre ();

  // l'algorithme suivant fait référence à la doc mathématique
  if ((fabs (cosMu_1) <= sinUneSec) && 
      (fabs (cosGamma) <= sinUneSec))
  { // Mu_1 = Gamma = pi/2
    if ((fabs (cosMu_2) <= sinUneSec) && 
        (fabs (cosAlpha_1_2) <= sinUneSec))
    { 
      // Dans ce cas particulier, tous les théta sont valides
      // Mu_2 = Alpha12 = pi/2
      if (creneauConsigne1.rencontre (Intervalle (-sinUneSec, sinUneSec)))
      { // a2 est sur le secteur 1
        for (int i = 0 ; i < nombreIntervallesSecteur2 ; i++)
        {
          // Famille à v1 = a2 fixe
          table_.push_back (Famille (new FamilleFixe (creneauConsigne2 [i], u1, u2,
                                                      a2Can, a1Can, a2Can),
                                     false));
          nombreFamilles_++; 
        }
      }
      if (creneauConsigne1.rencontre (Intervalle (M_PI-sinUneSec, M_PI+sinUneSec)))
      { // -a2 est sur le secteur 1
        for (int i = 0 ; i < nombreIntervallesSecteur2 ; i++)
        {
          // Famille à v1 = -a2 fixe
          table_.push_back (Famille (new FamilleFixe (creneauConsigne2 [i], u1, u2,
                                                      moinsA2Can, a1Can, a2Can),
                                     false));
          nombreFamilles_++; 
        }
      }
      if (creneauConsigne2.rencontre (Intervalle (-sinUneSec, sinUneSec)))
      { // a1 est sur le secteur 2
        for (int i = 0 ; i < nombreIntervallesSecteur1 ; i++)
        {
          // Famille à v2 = a1 fixe
          table_.push_back (Famille (new FamilleFixe (creneauConsigne1 [i], u2, u1,
                                                      a1Can, a2Can, a1Can),
                                     false));
          nombreFamilles_++; 
        }
      }
      if (creneauConsigne2.rencontre (Intervalle (M_PI-sinUneSec, M_PI+sinUneSec)))
      { // -a1 est sur le secteur 2
        for (int i = 0 ; i < nombreIntervallesSecteur1 ; i++)
        {
          // Famille à v2 = -a1 fixe
          table_.push_back (Famille (new FamilleFixe (creneauConsigne1 [i], u2, u1,
                                                      moinsA1Can, a2Can, a1Can),
                                     false));
          nombreFamilles_++; 
        }
      }
    }
    else
    {
      // Mu_1 = Gamma = pi/2 
      // mais Mu2 différent de Pi/2 ou Alpha12 différent de Pi/2
      // cMin et cMax ont des valeurs particulières
      double aMin = acos (cosPlus);
      double aMax = acos (cosMoins);
      Creneau creneauTheta = Intervalle (-aMin - marmottesPrecision,
                                         -aMax + marmottesPrecision);
      creneauTheta += Creneau (aMax - marmottesPrecision, aMin + marmottesPrecision);
      creneauInter = creneauTheta * creneauConsigne1;
      nombreIntervallesSecteur1 = creneauInter.nombre ();
      // algorithme
      for (int i = 0 ; i < nombreIntervallesSecteur1 ; i++)
      {
        if (creneauInter.rencontre (Intervalle (-sinUneSec, sinUneSec)))
        {
          // Theta = 0 est rencontré
          for (int j = 0 ; j < nombreIntervallesSecteur2 ; j++)
          {
            table_.push_back (Famille (new FamilleFixe (creneauConsigne2 [j],
                                                        u1, u2, a2Can, a1Can,
                                                        a2Can),
                                       false));
            nombreFamilles_++; 
          }
          table_.push_back (Famille (new FamilleProlongementZero (creneauInter [i],
                                                                  u1, u2, 1.0,
                                                                  sinMu_2, cosMu_2),
                                     false));
          nombreFamilles_++; 
          table_.push_back (Famille (new FamilleProlongementZero (creneauInter [i],
                                                                  u1, u2, -1.0,
                                                                  sinMu_2, cosMu_2),
                                     false));
          nombreFamilles_++; 
        }
        else
        {
          if (creneauInter.rencontre (Intervalle (M_PI-sinUneSec, M_PI+sinUneSec)))
          { 
            // Theta = Pi est rencontré
            for (int j = 0 ; j < nombreIntervallesSecteur2 ; j++)
            {
              table_.push_back (Famille (new FamilleFixe (creneauConsigne2 [j],
                                                          u1, u2,
                                                          moinsA2Can, a1Can,
                                                          a2Can),
                                         false));
              nombreFamilles_++;
            } 
            table_.push_back (Famille (new FamilleProlongementPi (creneauInter [i],
                                                                  u1, u2, 1.0,
                                                                  sinMu_2, cosMu_2),
                                       false));
            nombreFamilles_++; 
            table_.push_back (Famille (new FamilleProlongementPi (creneauInter [i],
                                                                  u1, u2, -1.0,
                                                                  sinMu_2, cosMu_2),
                                       false));
            nombreFamilles_++; 
          }
          else
          {
            // Ni Theta = 0, ni Theta = Pi ne sont rencontrés
            // On a sinMu_1 = sinGamma = 1 et cosMu_1 = cosGamma = 0
            table_.push_back (Famille (new FamilleGenerale (creneauInter [i],
                                                            u1, u2, -1.0,
                                                            1, 0, sinMu_2, cosMu_2,
                                                            1, 0, cosAlpha_1_2),
                                       false));
            nombreFamilles_++;
            table_.push_back (Famille (new FamilleGenerale (creneauInter [i],
                                                            u1, u2, 1.0,
                                                            1, 0, sinMu_2, cosMu_2,
                                                            1, 0, cosAlpha_1_2),
                                       false));
            nombreFamilles_++;
          }
        }
      }
    }
  }
  else
  {
    // Mu_1 different Gamma ou different de Pi/2
    // On est dans le cas le plus général
    creneauInter = intersection (cosMin, cosMax, creneauConsigne1);
    nombreIntervallesSecteur1 = creneauInter.nombre ();
    for (int i = 0 ; i < nombreIntervallesSecteur1 ; i++)
    {
      if ((creneauInter.rencontre (Intervalle (-sinUneSec, sinUneSec))) 
           && (fabs (sinMoins) <= sinUneSec))
      {
        // Theta = 0 est rencontré
        for (int j = 0 ; j < nombreIntervallesSecteur2 ;j++)
        {
          table_.push_back (Famille (new FamilleFixe (creneauConsigne2 [j],
                                                      u1, u2, a2Can, a1Can,
                                                      a2Can),
                                     false));
          nombreFamilles_++;
        }
        table_.push_back (Famille (new FamilleAlignementPlus (creneauInter [i],
                                                              u1, u2, -1.0,
                                                              sinMu_1, cosMu_1,
                                                              sinMu_2, cosMu_2),
                                   false));
        nombreFamilles_++;
        table_.push_back (Famille (new FamilleAlignementPlus (creneauInter [i],
                                                              u1, u2, 1.0,
                                                              sinMu_1, cosMu_1,
                                                              sinMu_2, cosMu_2),
                                   false));
        nombreFamilles_++;
      }
      else
      {
        if ((creneauInter.rencontre (Intervalle (M_PI-sinUneSec, M_PI+sinUneSec))) &&
             (fabs (sinPlus) <= sinUneSec))
        {
          // Theta = Pi est rencontré
          for (int j = 0 ; j < nombreIntervallesSecteur2 ; j++)
          {
            table_.push_back (Famille (new FamilleFixe (creneauConsigne2 [j],
                                                        u1, u2,
                                                        moinsA2Can, a1Can,
                                                        a2Can),
                                       false));
            nombreFamilles_++;
          }
          table_.push_back (Famille (new FamilleAlignementMoins (creneauInter [i],
                                                                 u1, u2, -1.0,
                                                                 sinMu_1, cosMu_1,
                                                                 sinMu_2, cosMu_2),
                                     false));
          nombreFamilles_++;
          table_.push_back (Famille (new FamilleAlignementMoins (creneauInter [i],
                                                                 u1, u2, 1.0,
                                                                 sinMu_1, cosMu_1,
                                                                 sinMu_2, cosMu_2),
                                     false));
          nombreFamilles_++;
        }
        else
        {
          // Ni Theta = 0, ni Theta = Pi ne sont rencontrés
          table_.push_back (Famille (new FamilleGenerale (creneauInter [i],
                                                          u1, u2, -1.0,
                                                          sinMu_1, cosMu_1,
                                                          sinMu_2, cosMu_2,
                                                          sinGamma, cosGamma,
                                                          cosAlpha_1_2),
                                     false));
          nombreFamilles_++;
          table_.push_back (Famille (new FamilleGenerale (creneauInter [i],
                                                          u1, u2, 1.0,
                                                          sinMu_1, cosMu_1,
                                                          sinMu_2, cosMu_2,
                                                          sinGamma, cosGamma,
                                                          cosAlpha_1_2),
                                     false));
          nombreFamilles_++;
        }
      }
    }
  }
}

Creneau ModeleGeom::intersection (double cosMin, double cosMax, 
                                  const Creneau& creneauConsigne) const
{
  // conversion de l'intervalle de cos (theta) en domaine sur theta
  // les numéros mentionnés correspondent à la doc mathématique
  if (cosMax <= -1.0)
  { // cas numéro 1 : aucun theta n'est valide
    // construire un créneau vide
    return Creneau();
  }
  else if (cosMax <= 1.0)
  { if (cosMin <= -1.0)
    { // cas numéro 2 
      double aMax     = acos (cosMax);
      Creneau creneauTheta = Intervalle (-M_PI, -aMax + marmottesPrecision);
      creneauTheta += Creneau (aMax - marmottesPrecision, M_PI);
      return creneauTheta * creneauConsigne;
    }
    else
    { // cas numéro 4
      double aMax     = acos (cosMax);
      double aMin     = acos (cosMin);
      Creneau creneauTheta = Intervalle (-aMin - marmottesPrecision, -aMax + marmottesPrecision);
      creneauTheta += Creneau (aMax - marmottesPrecision, aMin + marmottesPrecision);
      return creneauTheta * creneauConsigne;  
    }
  }
  else
  { if (cosMin <= -1.0)
    { // cas numéro 3
      return Intervalle (-M_PI, M_PI) * creneauConsigne;
    }
    else if (cosMin <= 1.0)
    { // cas numéro 5
      double aMin     = acos (cosMin);
      return Intervalle (-aMin - marmottesPrecision, aMin + marmottesPrecision) * creneauConsigne;
    }
    else
    { // cas numéro 6 : aucun theta n'est valide
      // construire un créneau vide
      return Creneau();
    }
  }
}

void ModeleGeom::attitude (const Etat& etatPrecedent, double date,
                           const ValeurDerivee1& t, int famille,
                           RotVD1* ptrAtt, VecVD1* ptrSpin) const
{ // calcul à partir du modèle de l'attitude respectant deux consignes

  // *ptrAtt transforme des vecteurs inertiels en vecteurs satellite
  *ptrAtt  = canSat_ (table_ [famille].inertielCanonique (t) );
  *ptrSpin = etatPrecedent.spinExtrapole (date, *ptrAtt);
}
