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
//>       IterateurLigne.cpp
//$Resume
//       fichier d'implantation de la classe IterateurLigne
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class IterateurLigne
//>         IterateurLigne()
//>         premier()
//>         dernier()
//>         allerSur()
//>         termine()         
//>         nombreIterations()
//>         operator++()
//>         operator--()
//>         longueurElement()
//>         valeur ()
//>         synchronize()
//>         actualise()       
//>         actualiseEtat()       
//>         rechercheLigne()
//>         compteLignes()    
//$Historique
//       $Log: IterateurLigne.cpp,v $
//       Revision 1.6  2003/02/03 13:41:49  club
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
//       Revision 1.1  1999/03/15 13:23:56  club
//       version initiale
//
//$Version
//       $Id: IterateurLigne.cpp,v 1.6 2003/02/03 13:41:49 club Exp $
//$Auteur
//        P-A.Cros   CSSI
//        M. Julien  CSSI 
//        G. Lajon   CSSI
//        O. Queyrut CSSI
//        Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "club/IterateurLigne.h"
#include "club/TamponAscii.h"


IterateurLigne::IterateurLigne( const TamponAscii& tampon, int compterLignes )
  throw(ClubErreurs) : debutLigne_ (0), numLigne_ (0), nombreLignes_(0)
{
  ptrTampon_ = &tampon;
  char *s = total();
  etat_ = etat();
  if (compterLignes)
  {
    nombreLignes_ = compteLignes(s);
    premier();
  }
}

IterateurLigne::IterateurLigne(TamponAscii* tampon, int compterLignes )
  throw(ClubErreurs) : debutLigne_ (0), numLigne_ (0), nombreLignes_(0)
{
  ptrTampon_ = tampon;
  char *s = total();
  etat_ = etat();
  if (compterLignes)
  {
    nombreLignes_ = compteLignes(s);
    premier();
  } 
}

void IterateurLigne::premier()
  throw(ClubErreurs)
{ 
  controleEtat();
  debutLigne_ = total();
  numLigne_   = 1;  
}

void IterateurLigne::dernier()
  throw(ClubErreurs)
{
  controleEtat();
  rechercheLigne( nombreLignes_ );
}

void IterateurLigne::allerSur(int index)
  throw(ClubErreurs)
{
  controleEtat();
  // positionne le pointeur sur le numero de ligne index
  // Verification de la valeur de index :
  if( index > nombreLignes_ )
  {
    throw ClubErreurs( ClubErreurs::ligne_hors_domaine,
                       index,1,nombreLignes_,ptrTampon_->nom());
  }
  if( index < 1 )
  {
    throw ClubErreurs( ClubErreurs::ligne_hors_domaine,
                       index,1,nombreLignes_,ptrTampon_->nom());
  }
  rechercheLigne( index );
}


int IterateurLigne::termine() const
{ 
  return( !debutLigne_ || (*debutLigne_ == 0 ) ); 
}
  
int IterateurLigne::nombreIterations() const 
  throw(ClubErreurs)
{
  controleEtat();
  return nombreLignes_; 
}
 

int IterateurLigne::operator++(int)
  throw(ClubErreurs)
{
  controleEtat();

  if( termine() )
    return 0;

  if( numLigne_ < nombreLignes_ )
  {
    rechercheLigne( numLigne_ + 1 );
  }
  else
  {
    // debutLigne_ pointe sur la derniere ligne,
    // on positionne debutLigne_ sur le '\0'
    // ce qui provoquera l'etat termine de l'iterateur.
    while( debutLigne_ && *debutLigne_ ) debutLigne_++;
    numLigne_++;
  }
  return( debutLigne_ <= total() + longueur() + 1 );
}

int IterateurLigne::operator--(int)
  throw(ClubErreurs)
{
  controleEtat();
  if( debutLigne_ > total() )
  {
    rechercheLigne( numLigne_ - 1 );
    return( debutLigne_ >= total() );
  }
  else
  { // on ne peut pas decrementer
    return 0;
  }
}

int IterateurLigne::longueurElement(int avecFin) const
  throw(ClubErreurs)
{
  controleEtat();
  char *s = debutLigne_;
  int longueur = 0;
  while( s && *s && (*s != '\n' ))
  {
    longueur++;
    s++;
  }
  if( avecFin && (*s == '\n'))
    longueur++;
  return longueur;
}

const char* IterateurLigne::valeur () const
  throw(ClubErreurs)
{
  IterateurLigne *nonConstThis = (IterateurLigne *) this;
  nonConstThis->controleEtat();
  // l'attribut sortie_ est destiné à optimiser l'implantation de la classe
  // il est licite de le modifier au sein de cette méthode const
  string *ptrNonConstSortie = &(((IterateurLigne *) this)->sortie_);
  *ptrNonConstSortie = "";
  if( debutLigne_ )
  {
    char *s = debutLigne_;
    while( *s && (*s != '\n') )
      (*ptrNonConstSortie) += *s++;
  }
  return sortie_.c_str ();
}



void IterateurLigne::synchronize(int direction)
  throw(ClubErreurs)
{
  if( ptrTampon_ )
  {
    if( direction )
      // mise a jour a partir du tampon
      actualiseEtat();
    else
      affecteCourant( debutLigne_ );
  }
}

void IterateurLigne::actualise()
{
  etat_ = etat();
  // mise a jour du nombre de lignes :
  nombreLignes_ = compteLignes( total());
  // met a jour les differents compteurs ainsi que
  // le pointeur courant_
  // on est oblige de reparcourir tout le tampon !
  premier();
}

void IterateurLigne::actualiseEtat()
  //
  // met a jour les differents compteurs ainsi que le pointeur courant_
  // on est oblige de reparcourir tout le tampon !
  // il faut mettre a jour etat_.
  //
{
  etat_ = etat();
  debutLigne_     = courant();
  // repositionner debutLigne_ en debut de ligne :
  while( (debutLigne_ > total())&&(*(debutLigne_ - 1) != '\n')) debutLigne_--;

  char *s         = total();
  nombreLignes_   = 0;
  numLigne_       = 0;
  while( s && *s )
  {
    nombreLignes_++;

    // recherche du numero de ligne.
    if( s == debutLigne_ )
      numLigne_ = nombreLignes_;

    // recherche de la fin de la ligne.
    while( *s && (*s != '\n') ) 
      s++;
    
    // saut de la fin de ligne :
    if( *s ) 
      s++;
  }

  // numLigne_ == 0 indique que l'iterateur est dans l'etat termine,
  // numLigne_ vaut alors nombreLignes_+1.
  if( !numLigne_  )
    numLigne_ = nombreLignes_ + 1;
}

void IterateurLigne::rechercheLigne( int l )
  throw(ClubErreurs)
{
  // test de validité de la demande
  if ((l < 1) || (l > nombreLignes_))
    throw ClubErreurs( ClubErreurs::ligne_hors_domaine   ,
                       l                                 ,
                       1                                 ,
                       nombreLignes_                     ,
                       ( ptrTampon_ ) ? ptrTampon_->nom() : "" );

 if ( numLigne_ < l)
  { // il faut avancer dans le tampon

    while ( numLigne_ < l)
    { // recherche de la fin de ligne courante
      while (*debutLigne_ != '\n')
        debutLigne_++;

      // passage à la ligne suivante
      debutLigne_++;
      numLigne_++;
    }
  }
  else if ( numLigne_ > l)
  { // il faut reculer dans le tampon

    if (l == 1)
    { // le début de la ligne 1 est au début du tampon
      debutLigne_ = total();
      numLigne_   = 1;
    }
    else
    { // le début de la ligne l est après le '\n' de la ligne l-1

      while ( numLigne_ > l)
      { // passage à la ligne précédente
        debutLigne_--;
        numLigne_--;

        // recherche du début de la ligne précédente
        while (*(debutLigne_ - 1) != '\n')
          debutLigne_--;
      }
    }
  }
}


int IterateurLigne::compteLignes(const char*   mobile) const
{
  int nombre = 0;

  while( mobile && *mobile )
  {
    nombre++;
    while( *mobile && (*mobile != '\n') ) 
      mobile++;
    if( *mobile )
      mobile++;
  }
  return nombre;
}
