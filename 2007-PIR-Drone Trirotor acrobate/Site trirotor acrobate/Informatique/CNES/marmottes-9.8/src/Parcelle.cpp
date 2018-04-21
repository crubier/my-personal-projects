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
//>       Parcelle.cpp
//
//$Resume
//       fichier d'implantation de la classe Parcelle
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class Parcelle    
//>         champSuivant()  
//>         initParcours()  
//>         pointSuivant()  
//>         arreteParcours()
//
//$Historique
//       $Log: Parcelle.cpp,v $
//       Revision 2.8  2003/02/04 16:31:53  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 2.7  2000/11/13 10:02:35  luc
//       remplacement de la classe Champ par la classe Field
//       modification de la signature de la méthode pointSuivant
//
//       Revision 2.6  2000/03/30 17:01:19  luc
//       ajout du copyright CNES
//
//       Revision 2.5  1998/06/24 20:00:22  luc
//       élimination des variables statiques RCS
//       modification du format des en-têtes
//
//       Revision 2.4  1998/04/26 18:25:15  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 2.3  1997/08/20 08:33:32  luc
//       ajout d'un en-tête de fichier
//       réorganisation du code à raison d'une seule classe par fichier
//
//       Revision 2.2  1997/04/27 19:36:21  luc
//       inversion des codes de retour
//       changement des règles de nommage
//       passage de SCCS à RCS
//       
//       Revision 2.1  1996/07/31 17:17:41  luc
//       refonte complète pour remplacer les Connexes par des Mosaïques
//       
//       Revision 1.2  1995/08/21 14:14:13  mercator
//       correction d'un probleme de parcours des parcelles comprenant des connexes vides
//       
//       Revision 1.1  1994/12/23 11:00:08  luc
//       Initial revision
//
//$Version
//       $Id: Parcelle.cpp,v 2.8 2003/02/04 16:31:53 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/Parcelle.h"

bool Parcelle::champSuivant ()
{ VecDBL point;
  bool dernier;
  do
  { // recherche du prochain champ à parcourir
    rechercheChamp (&courant_);
    if (courant_ == 0)
      return false;

    // préparation du parcours
    courant_->initWalk (tolerance_);

  } while (! courant_->nextPoint (&point, &dernier));

  // retour normal à la fonction appelante
  return true;

}

void Parcelle::initParcours (double tolerance)
{ arreteParcours ();

  tolerance_ = tolerance;

  (void) champSuivant ();

}

bool Parcelle::pointSuivant (VecDBL* u, bool* dernier)
{
  if (courant_ == 0)
    return 0;

  // lecture du prochain point
  if (courant_->nextPoint (u, dernier))
    return 1;

  // il faut passer au champ suivant
  if (! champSuivant ())
    return 0;

  // retour du premier point du champ suivant
  return courant_->nextPoint (u, dernier);
    
}

void Parcelle::arreteParcours ()
{ if (courant_)
  { courant_->stopWalk ();
    courant_ = 0;
  }
}
