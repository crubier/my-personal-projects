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
//       Club
//
//$Nom
//>       TamponPartage.cpp
//
//$Resume
//       fichier d'implantation de la classe TamponPartage
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class TamponPartage
//>         TamponPartage()  
//>         operator =()     
//>         ~TamponPartage() 
//
//$Historique
//       $Log: TamponPartage.cpp,v $
//       Revision 3.10  2003/02/03 13:49:38  club
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 3.9  2000/07/03 08:56:46  club
//       ajout du copyright CNES
//       élimination du delete[] lorsque l'utilisateur ne donne
//       pas de pointeur de fonction valide
//
//       Revision 3.8.2.2  2000/03/30 14:46:52  club
//       ajout du copyright CNES
//
//       Revision 3.8.2.1  2000/03/30 10:06:01  club
//       élimination du delete[] lorsque l'utilisateur ne donne
//       pas de pointeur de fonction valide
//
//       Revision 3.8  1999/10/18 07:14:51  club
//       correction d'un bug sur la fuite mémoire qui survient lors de
//       l'opérateur d'affectation : on teste désormais si l'indicateur
//       de référence est négatif au lieu du test de nullité.
//
//       Revision 3.7  1999/04/12 15:21:19  club
//       utilisation de la fonction utilisateur pour libérer la mémoire allouée
//
//       Revision 3.6  1998/07/07 15:06:52  luc
//       correction du cas des instances réaffectées
//       sans jamais avoir été initialisées
//
//       Revision 3.5  1998/06/21 15:55:23  luc
//       modification du format de l'en-tête
//       transformation de TamponPartage::Acces de "struct" en "class"
//       élimination de la chaîne statique RCS
//
//       Revision 3.4  1998/04/26 13:02:45  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 3.3  1997/08/21 16:44:07  luc
//       ajout d'un en-tête de fichier
//
//       Revision 3.2  1997/03/25 15:04:08  luc
//       changement des règles de nommage
//       
//       Revision 3.1  1997/03/19 15:20:37  luc
//       renommage de la bibliothèque util_c++ en club
//       passage de SCCS à RCS
//       
//       Revision 2.1  1996/07/15 17:29:37  luc
//       élimination de la dépendance au tools.h++ (Rogue Wave)
//       prise en compte du renommage de erreurs.h en util_erreurs.h
//       
//       Revision 1.2  1994/11/09 15:02:53  mercator
//       elimination des directives #pragma
//       
//       Revision 1.1  1994/07/27 12:06:03  luc
//       Initial revision
//
//$Version
//       $Id: TamponPartage.cpp,v 3.10 2003/02/03 13:49:38 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "club/ClubErreurs.h"
#include "club/TamponPartage.h"

TamponPartage::TamponPartage ()
 : fonctionLiberation_ (0), arg_ (0)
{ // allocation d'une nouvelle structure d'accès
  acces_ = new Acces;
}

TamponPartage::TamponPartage (void* memoire,
                              void  (*f) (void *, void *), void *arg)
 : fonctionLiberation_ (f), arg_ (arg)
{ // allocation d'une nouvelle structure d'accès
  acces_ = new Acces;

  if (memoire)
  { // indirection de la mémoire
    acces_->initMemoire (memoire);
  }

}

TamponPartage::TamponPartage (const TamponPartage& t)
{ // copie du pointeur sur la structure d'accès
  acces_              = t.acces_;
  fonctionLiberation_ = t.fonctionLiberation_;
  arg_                = t.arg_;

  // incrémentation du compteur des références à la mémoire
  (*acces_)++;

  
}

TamponPartage& TamponPartage::operator = (const TamponPartage& t)
{ // prise en compte de la nouvelle référence à la ressource mémoire
  if (this != &t)          // protection contre x = x
  { (*(t.acces_))++;

    // déconnexion de la mémoire précédente
    (*acces_)--;
    if (acces_->compteur () <= 0)
    { // cette instance était la dernière à utiliser cette mémoire
      if ((acces_->memoire () != 0) && (fonctionLiberation_ != 0))
        fonctionLiberation_ (acces_->memoire (), arg_);
      delete acces_;
    }

    // partage de la ressource mémoire
    acces_ = t.acces_;

    // enregistrement de la nouvelle fonction de libération
    fonctionLiberation_ = t.fonctionLiberation_;
    arg_                = t.arg_;

  }

  return *this;
  
}

TamponPartage::~TamponPartage ()
{ (*acces_)--;
  if (acces_->compteur () <= 0)
  { // cette instance était la dernière à utiliser cette mémoire
    if ((acces_->memoire () != 0) && (fonctionLiberation_ != 0))
      fonctionLiberation_ (acces_->memoire (), arg_);
    delete acces_;
  }
}
