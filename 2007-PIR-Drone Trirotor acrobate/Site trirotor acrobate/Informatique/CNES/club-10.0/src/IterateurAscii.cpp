////////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Type
//       DEF
//
//$Projet
//        Bibam
//$Application
//        Club
//$Nom
//>       IterateurAscii.cpp
//$Resume
//       fichier d'implantation de la classe IterateurAscii
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class IterateurAscii 
//>         total()
//>         courant()
//>         affecteCourant()
//>         tailleAllouee()
//>         etat()
//>         longueur()
//>         estCarGuillemet()  
//>         estCarCommentaire()
//>         estSeparateur()  
//>         sauteChaine()
//>         controleEtat()    
//$Historique
//       $Log: IterateurAscii.cpp,v $
//       Revision 1.5  2003/02/03 13:38:57  club
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.4  2000/10/24 08:33:30  club
//       modification des include standard du C : utilisation de cNAME au lieu de
//       NAME.h (pour permettre la compilation avec le Sun Workshop 5.0)
//
//       Revision 1.3  2000/07/03 08:57:19  club
//       Ajout du copyright CNES
//
//       Revision 1.2.2.2  2000/04/04 07:15:50  club
//       déplacement du copyright
//
//       Revision 1.2.2.1  2000/03/30 14:46:47  club
//       ajout du copyright CNES
//
//       Revision 1.2  1999/06/01 14:58:14  club
//       correction de l'include obsolete <strings.h>
//       en "ClubConfig.h"
//
//       Revision 1.1  1999/03/15 13:21:48  club
//       version initiale
//
//$Version
//       $Id: IterateurAscii.cpp,v 1.5 2003/02/03 13:38:57 club Exp $
//$Auteur
//        P-A.Cros  CSSI
//        M. Julien CSSI 
//        Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "club/IterateurAscii.h"
#include "club/TamponAscii.h"
#include "club/AnalyseurLexical.h"

char* IterateurAscii::total()
{
  //
  // acces a l'attribut protected TamponAscii::total_ .
  //  
  if( ptrTampon_ )
  {
    return ptrTampon_->total();
  }
  else
    return 0;
}


char* IterateurAscii::courant()
{ 
  //
  // acces a l'attribut protected TamponAscii::courant_ .
  //
  if( ptrTampon_ )
    return ptrTampon_->courant_;
  else 
    return 0;
}

void IterateurAscii::affecteCourant(char* valeur)
  throw(ClubErreurs)
{
  //
  // affecte a l'attribut TamponAscii::courant_ le parametre valeur.
  // si l'etat du tampon et celui de l'iterateur ne sont pas compatibles
  // on leve une exception ( appel a controleEtat ).
  //
  controleEtat();
  TamponAscii *nonConstThis = (TamponAscii *) ptrTampon_;
  if( ptrTampon_ )
    nonConstThis->courant_ = valeur;
}


int IterateurAscii::tailleAllouee()
{ 
  //
  // acces a l'attribut TamponAscii::tailleTampon_
  //
  if ( ptrTampon_ )
    return ptrTampon_->tailleTampon_;
  else
    return 0;
}


unsigned long IterateurAscii::etat()
{
  //
  // acces a l'attribut protected TamponAscii::etat_ .
  //
  if(ptrTampon_) 
    return ptrTampon_->etat_ ;
  else 
    return 0L;
}


int IterateurAscii::longueur() const
{
  //
  // acces a l'attribut TamponAscii::longueur_
  //
  if ( ptrTampon_ ) 
    return ptrTampon_->longueur_;
  else 
    return 0;
}

int IterateurAscii::estCarGuillemet (char c) const
{ 
  return ptrTampon_->estCarGuillemet(c); 
}


int IterateurAscii::estCarCommentaire (char c) const
{
  return ptrTampon_->estCarCommentaire(c);
}

int IterateurAscii::estSeparateur (char c) const
{
  return ptrTampon_->estSeparateur(c);
}


const char* IterateurAscii::sauteChaine (char* mobile) const
  throw(ClubErreurs)
{
  if (ptrTampon_->interprete_ && estCarCommentaire (*mobile))
  { // il faut sauter un commentaire
    while (*mobile && (*mobile != '\n'))
      mobile++;
    return mobile;
  }
  // boucle sur les tronçons entre et hors '"'

  while (1)
  { // boucle sur les tronçons entre et hors '"'

    if ((*mobile == '\0')
     || estSeparateur (*mobile)
     || (ptrTampon_->interprete_ && estCarCommentaire (*mobile)))
    { // on est arrivé à la fin de chaîne
      return mobile;
    }

    if ((! estCarGuillemet (*mobile))
     && (! (ptrTampon_->interprete_ && estCarCommentaire (*mobile))))
    { // il faut sauter une série de caractères non blancs
      while (*mobile
         && (! estSeparateur   (*mobile))
         && (! estCarGuillemet (*mobile))
         && (! (ptrTampon_->interprete_ && estCarCommentaire (*mobile))))
        mobile++;
    }

    if (estCarGuillemet (*mobile))
    { // il faut sauter une chaîne C ou fortran
      const char *fin = strchr (mobile, '\n');
      int lg = fin ? (fin - mobile) : strlen (mobile);
      AnalyseurLexical al (mobile, lg);
      al.autoriseChainesC       ();
      al.autoriseChainesFortran ();

      int code = al.suivant ();
      if ((code == AnalyseurLexical::codeChaineC)
          ||
          (code == AnalyseurLexical::codeChaineFortran))
      { // on a bien reconnu une chaîne
        mobile += al.apresLexeme ();
      }
      else
      { // erreur de syntaxe dans le tampon: il faut générer un message
        throw ClubErreurs( ClubErreurs::manque_guillemet    ,
                           ptrTampon_->nom()                   );
      }

    }
  }
  
}




void IterateurAscii::controleEtat() const
  throw(ClubErreurs)
{
  if( ptrTampon_ && ( etat_ != ptrTampon_->etat_ ) ){
    // erreur de synchronisation dans le tampon: il faut générer un message
    throw ClubErreurs( ClubErreurs::iterateur_invalide ,
                       ptrTampon_->nom()                  );  
  }
}
