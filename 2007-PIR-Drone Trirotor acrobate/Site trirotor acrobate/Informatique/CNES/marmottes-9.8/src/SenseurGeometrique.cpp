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
//>       SenseurGeometrique.cpp
//
//$Resume
//       fichier d'implantation de la classe SenseurGeometrique
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class SenseurGeometrique
//>         operator =()          
//>         nouveauRepere()       
//>         foncEcart()           
//
//$Historique
//       $Log: SenseurGeometrique.cpp,v $
//       Revision 2.17  2003/10/08 09:39:41  marmottes
//       FA 0029, 0030, 0031
//       DM 0025, 0026, 0028
//
//       Revision 2.16  2003/02/04 16:41:11  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 2.15  2002/01/17 09:24:35  marmottes
//       (verifieConsigne): rejet des cônes de consigne de demi ouverture PI/2 en plus des cônes de demi ouverture nulle (FA 0003)
//
//       Revision 2.14  2000/09/13 10:40:16  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 2.13  2000/03/30 17:01:20  luc
//       ajout du copyright CNES
//
//       Revision 2.12  1999/08/06 13:32:16  filaire
//       Passage à la gestion des erreurs par les exceptions
//
//       Revision 2.11  1998/09/14 11:52:05  luc
//       ajout de la méthode verifieConsigne
//
//       Revision 2.10  1998/06/24 20:05:20  luc
//       élimination des variables statiques RCS
//       modification du format des en-têtes
//
//       Revision 2.9  1998/04/26 18:25:37  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 2.8  1997/08/20 09:25:38  luc
//       ajout d'un en-tête de fichier
//       réorganisation du code à raison d'une seule classe par fichier
//       remplacement du cône de consigne par un secteur de consigne
//
//       Revision 2.7  1997/04/27 19:36:44  luc
//       inversion des codes de retour
//       changement des règles de nommage
//       passage de SCCS à RCS
//       
//       Revision 2.6  1997/04/15 16:08:41  luc
//       correction d'une inversion dans le calcul du moment de l'orbite
//       
//       Revision 2.5  1997/02/13 09:59:23  luc
//       ajout du moment comme cible observable
//       
//       Revision 2.4  1997/02/12 11:09:12  luc
//       ajout de la cible pseudo-soleil pour les senseurs optiques
//       prise en compte des éclipses par la lune
//       
//       Revision 2.3  1997/02/10 11:22:11  luc
//       ajout de la vitesse en tant que cible observable par un senseur
//       prise en compte des éclipses de soleil et de lune pour la contrôlabilité
//       
//       Revision 2.2  1996/09/11 17:45:19  luc
//       ajout du nom du senseur dans l'instance
//       
//       Revision 2.1  1996/07/31 17:24:09  luc
//       ajout d'une possibilité de modifier le repère senseur à l'exécution
//       report au niveau du senseur terre de base de la séparation des inhibitions soleil/lune
//       élimination du senseur std15
//       
//       Revision 1.7  1996/05/22 17:02:52  luc
//       correction d'une erreur de non initialisation de l'attribut axeVD1_
//       dans SenseurVecteur::modeliseConsigne
//       
//       Revision 1.6  1996/03/21 17:30:38  luc
//       ajout du senseur STD15
//       
//       Revision 1.5  1995/09/12 06:25:11  mercator
//       ajout des pseudo-senseurs d'ascension droite et de declinaison
//       
//       Revision 1.4  1995/07/12 12:02:45  mercator
//       limitation de la portee de variables locales de switch
//       
//       Revision 1.3  1995/01/30 09:43:30  mercator
//       ajout de l'initialisation de pointeurs d'erreur en sortie
//       ajout d'initialisations des cibles de senseurs geometriques
//       
//       Revision 1.2  1995/01/27 16:59:51  mercator
//       propagation du spin dans tous les calculs depuis la modelisation
//       jusqu'a la sauvegarde de la solution finale dans l'etat
//       
//       Revision 1.1  1994/12/23 11:00:15  luc
//       Initial revision
//
//$Version
//       $Id: SenseurGeometrique.cpp,v 2.17 2003/10/08 09:39:41 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/SenseurGeometrique.h"

SenseurGeometrique& SenseurGeometrique::operator =
                                                 (const SenseurGeometrique& s)
{ if (&s != this)    // protection contre x = x
  { Senseur::operator = (s);
    secteursConsigne_ = s.secteursConsigne_;
    axeVD1_           = s.axeVD1_;
    cible_            = s.cible_;
    cibleVD1_         = s.cibleVD1_;

  }

  return *this;

}

void SenseurGeometrique::verifieConsigne () const
  throw (MarmottesErreurs)
{ // vérifie si le cône de consigne n'est pas dégénéré
  if (secteursConsigne_.cone ().sinus () < 4.8e-6)
    throw MarmottesErreurs (MarmottesErreurs::consigne_degeneree,
                            nom ().c_str ());
}

void SenseurGeometrique::nouveauRepere (const RotDBL& nouveau)
{ // réorientation du senseur
  RotDBL decalage ((-nouveau) (repere ()));
  secteursConsigne_.tourne (decalage);
  axeVD1_ = VecDBLVD1 (secteursConsigne_.cone ().axe ());

  // appel de la fonction de la classe de base
  Senseur::nouveauRepere (nouveau);

}

ValeurDerivee1 SenseurGeometrique::foncEcart (const Etat& etatPrecedent,
                                              const Etat& etatResolution,
                                              const RotVD1& attitude,
                                              const VecVD1& spin)
{
  VecVD1 v = attitude (cibleVD1_);
  return angle (v, axeVD1_) - secteursConsigne_.cone ().angle ();
}
