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
//>       IterateurCaractere.cpp
//$Resume
//       fichier d'implantation de la classe IterateurCaractere
//
//$Description
//   - synchronisation Tampon / Iterateur :
//       De par la nature particuliere de cet iterateur, la synchronisation
//       entre l'iterateur et le tampon est immediate ( le nombre d'elements
//       etant egal au nombre d'octets du tampon). Il n'est donc pas
//       necesaire de faire appel a controleEtat() pour verifier la coherence
//       Tampon/Iterateur lors d'appel aux methodes :
//          - premier
//          - dernier
//          - allerSur
//          - nombreIterations
//          - termine.
//       Les trois premieres methodes permettent egalement de mettre a jour
//       la coherence Tampon/Iterateur, on peut donc ajouter a ces methodes
//       la ligne de code :
//           etat_ = etat();
//
//$Contenu
//>       class IterateurCaractere
//>         IterateurCaractere()
//>         premier()
//>         dernier()
//>         termine()             
//>         nombreIterations()
//>         operator++()
//>         operator--()
//>         allerSur()
//>         valeur ()
//>         synchronize ()
//$Historique
//       $Log: IterateurCaractere.cpp,v $
//       Revision 1.6  2003/02/03 13:39:41  club
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.5  2000/10/24 08:33:30  club
//       modification des include standard du C : utilisation de cNAME au lieu de
//       NAME.h (pour permettre la compilation avec le Sun Workshop 5.0)
//
//       Revision 1.4  2000/09/07 08:05:55  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//
//       Revision 1.3  2000/07/03 08:57:19  club
//       Ajout du copyright CNES
//
//       Revision 1.2.2.2  2000/04/04 07:15:50  club
//       déplacement du copyright
//
//       Revision 1.2.2.1  2000/03/30 14:46:48  club
//       ajout du copyright CNES
//
//       Revision 1.2  1999/07/07 07:55:16  club
//       Passage a une gestion d'erreurs par exceptions
//
//       Revision 1.1  1999/03/15 13:22:20  club
//       version initiale
//
//$Version
//       $Id: IterateurCaractere.cpp,v 1.6 2003/02/03 13:39:41 club Exp $
//$Auteur
//        P-A.Cros  CSSI
//        M. Julien CSSI 
//        G. Lajon  CSSI
//        Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "club/IterateurCaractere.h"
#include "club/TamponAscii.h"



IterateurCaractere::IterateurCaractere( const TamponAscii& tampon )
  throw(ClubErreurs) // ne leve pas d'exceptions , mais appel a premier()
{
  ptrTampon_ = &tampon;
  etat_   = etat();
  premier();

}

IterateurCaractere::IterateurCaractere( TamponAscii* tampon )
  throw(ClubErreurs) // ne leve pas d'exceptions , mais appel a premier()
{
  ptrTampon_ = tampon;
  etat_   = etat();
  premier();

}

void IterateurCaractere::premier()
  throw(ClubErreurs) // ne leve pas d'exceptions en fait
{
  caractereCourant_ = total();
  etat_    = etat();
}

void IterateurCaractere::dernier()
  throw(ClubErreurs) // ne leve pas d'exceptions en fait
{
  caractereCourant_ = total() + longueur() - 1; 
  etat_    = etat();
}

void IterateurCaractere::allerSur(int index)
  throw(ClubErreurs)
{
  //la position de l'index commence a 1 jusqu'a nbcaracteres
  // les index reels vont de 0 a nbcaracteres -1 ( en comptant '\0').
  if( index < 1 ) 
    throw ClubErreurs( ClubErreurs::caractere_hors_domaine,
                   index,1,ptrTampon_->longueur(),ptrTampon_->nom());
  if( index > longueur() )
    throw ClubErreurs( ClubErreurs::caractere_hors_domaine,
                   index,1,longueur(),ptrTampon_->nom()); 

  caractereCourant_ = total() + index - 1;

  etat_ = etat();
}

int IterateurCaractere::termine() const
{ 
  return( !caractereCourant_ || (*caractereCourant_ == 0 ) ); 
}
  
int IterateurCaractere::nombreIterations() const
  throw(ClubErreurs)
{ 
  return longueur();
}
 
int IterateurCaractere::operator++(int)
  throw(ClubErreurs)
{
  controleEtat();
  if( caractereCourant_ < total() + longueur() )
  {
    caractereCourant_++;
    return( caractereCourant_ <= total() + longueur()  );
  }
  else
  { // on ne peut pas incrementer
    return 0;
  }
}

int IterateurCaractere::operator--(int)
  throw(ClubErreurs)
{
  controleEtat();
  if( caractereCourant_ > total() )
  {
    caractereCourant_--;
    return( caractereCourant_ >= total() );
  }
  else
  { // on ne peut pas decrementer
    return 0;
  }
}

const char* IterateurCaractere::valeur () const
  throw(ClubErreurs)
{
  IterateurCaractere *nonConstThis = (IterateurCaractere *) this;
  nonConstThis->controleEtat();
  string *ptrNonConstSortie = &(((IterateurCaractere *) this)->sortie_);
  *ptrNonConstSortie = "";
  if( caractereCourant_ )
    *ptrNonConstSortie += string (1, *caractereCourant_);
  return sortie_.c_str ();
}



void IterateurCaractere::synchronize (int direction)
  throw(ClubErreurs)
{
  //
  // synchronisation du tampon sur la position courante de l'iterateur
  // ou de l'iterateur sur la position courante du tampon (selon la
  // valeur de direction : resp. 0 et 1
  //
  if( ptrTampon_ ){
    if( direction )
      actualiseEtat();      
    else
      affecteCourant(caractereCourant_);
  }

}
