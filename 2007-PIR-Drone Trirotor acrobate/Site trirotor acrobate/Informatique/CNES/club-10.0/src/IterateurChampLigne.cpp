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
//>       IterateurChampLigne.cpp
//$Resume
//       fichier d'implantation de la classe IterateurChampLigne
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class IterateurChampLigne
//>         IterateurChampLigne() 
//>         premier()
//>         dernier()
//>         allerSur()
//>         termine()              
//>         nombreIterations()
//>         nombreIterationsChamps()
//>         operator++()
//>         operator--()
//>         longueurElement()
//>         valeur()
//>         synchronize()
//>         actualiseEtat()        
//>         actualise()        
//>         rechercheChampLigne()
//>         debutDeChampLigne()    
//$Historique
//       $Log: IterateurChampLigne.cpp,v $
//       Revision 1.7  2003/02/03 13:41:22  club
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.6  2000/10/24 08:33:30  club
//       modification des include standard du C : utilisation de cNAME au lieu de
//       NAME.h (pour permettre la compilation avec le Sun Workshop 5.0)
//
//       Revision 1.5  2000/09/07 08:05:55  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//
//       Revision 1.4  2000/07/03 08:57:19  club
//       Ajout du copyright CNES
//
//       Revision 1.3.2.2  2000/04/04 07:15:50  club
//       déplacement du copyright
//
//       Revision 1.3.2.1  2000/03/30 14:46:48  club
//       ajout du copyright CNES
//
//       Revision 1.3  1999/07/07 07:55:16  club
//       Passage a une gestion d'erreurs par exceptions
//
//       Revision 1.2  1999/06/01 14:59:33  club
//       correction de l'include obsolete <strings.h> en "ClubConfig.h" et protection
//       pour les traitements sur un tampon nul
//
//       Revision 1.1  1999/03/15 13:23:23  club
//       version initiale
//
//$Version
//       $Id: IterateurChampLigne.cpp,v 1.7 2003/02/03 13:41:22 club Exp $
//$Auteur
//        P-A.Cros   CSSI
//        M. Julien  CSSI 
//        G. Lajon   CSSI
//        O. Queyrut CSSI
//        Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "club/IterateurChampLigne.h"
#include "club/TamponAscii.h"


IterateurChampLigne::IterateurChampLigne( const TamponAscii& tampon, 
                                          int compterChampsLignes )
  throw(ClubErreurs) :
  IterateurChamp( tampon,compterChampsLignes ),
  IterateurLigne( tampon,compterChampsLignes )
{

  // l'initialisation des attributs :
  //  , etat_ , nombreLignes_ , debutLigne_, numLigne_,
  // est faite par les constructeurs des classes de base.

  ptrTampon_ = &tampon;
  debutLigne_ = total();
  debutChamp_ = total();

  if (compterChampsLignes)
  {

    actualise();
  }
  premier();
}

IterateurChampLigne::IterateurChampLigne(const TamponAscii* tampon, 
                                         int compterChampsLignes )
  throw(ClubErreurs) :
  IterateurChamp( tampon,compterChampsLignes ),
  IterateurLigne( tampon,compterChampsLignes)
{
 
  ptrTampon_ = tampon;
  debutLigne_ = total();
  debutChamp_ = total();
  if (compterChampsLignes)
  {
    actualise();
  }

  premier();
}

void IterateurChampLigne::premier()
  throw(ClubErreurs)
{ 
  controleEtat();
  debutLigne_ = total();
  numLigne_   = 1;

  // mise a jour du nombre de champs :
  nombreChamps_ = compteChamps( debutLigne_ , 0 );
  
  // si ligne vide, on passe au prochain champ
  if (nombreChamps_ == 0 )
    (*this)++;
  else // on met a jour tous les parametres
    debutDeChampLigne( debutLigne_ );
}

void IterateurChampLigne::dernier()
  throw(ClubErreurs)
{
  controleEtat();
  rechercheLigne( nombreLignes_ );
  nombreChamps_ = compteChamps( debutLigne_ , 0 );
  
  // si ligne vide, on passe au champ precedent (non vide donc)
  if (nombreChamps_ == 0)
  {
    nombreChamps_ = 1;
    numChamp_= 1;
    (*this)--;
  }
  else
    // recherche du dernier champ de la ligne courante.
    rechercheChampLigne( nombreChamps_ );
    
}

void IterateurChampLigne::allerSur(int champ, int ligne )
  throw(ClubErreurs)
{
  //
  // positionne le pointeur sur le champ numero champ 
  // de la ligne numero ligne.
  // le numero de champ peut etre nul, dans ce cas, il n'y a pas
  // d'exception de levee, mais au final, on ne pointe pas sur un
  // champ.(Utile pour inserer un champ entre 2 lignes vides)
  controleEtat();

  // ajustement de la valeur de ligne :
  if( ligne < 1 )
    throw ClubErreurs( ClubErreurs::ligne_hors_domaine,
                       ligne,1,nombreLignes_,ptrTampon_->nom());
  if( ligne > nombreLignes_ )
    throw ClubErreurs( ClubErreurs::ligne_hors_domaine,
                       ligne,1,nombreLignes_,ptrTampon_->nom());

  // positionner debutLigne_ sur la ligne 'ligne'.
  IterateurLigne::allerSur( ligne );

  // mise a jour du comteur nombreChamps_ :
 
  nombreChamps_ = compteChamps( debutLigne_, 0 );

  // ajustement de la valeur de champ :
  if( champ < 0 )
    throw ClubErreurs( ClubErreurs::champ_ligne_hors_domaine,
                       champ,1,nombreChamps_,ligne,ptrTampon_->nom());
  if( nombreChamps_ && (champ > nombreChamps_ ) )
    throw ClubErreurs( ClubErreurs::champ_ligne_hors_domaine,
                       champ,1,nombreChamps_,ligne,ptrTampon_->nom());

  if(champ != 0) // on recherche le champ
    rechercheChampLigne( champ );
  else // on n'essaye meme pas, on se place sur un champ fictif 0
    numChamp_=0;
}

void IterateurChampLigne::allerSur(int index)
  throw(ClubErreurs)
{
  //
  // positionne le pointeur sur le numero de champ index
  // de la ligne courante.
  //
  controleEtat();
  // Ajustement de la valeur de index :
  if( index > nombreChamps_ )
  {
    throw ClubErreurs( ClubErreurs::champ_hors_domaine,
                       index,1,nombreChamps_,ptrTampon_->nom());
    //                   index,1,nombreChamps_,numLigne_,ptrTampon_->nom());
  }
  if( index < 1 )
  {
    throw ClubErreurs( ClubErreurs::champ_hors_domaine,
                       index,1,nombreChamps_,ptrTampon_->nom());
    //                   index,1,nombreChamps_,numLigne_,ptrTampon_->nom());
  }
  rechercheChampLigne( index );
  
}

int IterateurChampLigne::termine() const
{ 
  return( !debutLigne_ || (*debutLigne_ == 0 ) ); 
}
  

int IterateurChampLigne::nombreIterations() const
  throw(ClubErreurs)
{ 
  //
  // retourne le nombre de lignes 
  //
  IterateurChampLigne *nonConstThis = (IterateurChampLigne *) this;
  nonConstThis->controleEtat(); 
  return nombreLignes_; 
}

int IterateurChampLigne::nombreIterationsChamps(int l)
  throw(ClubErreurs)
{
  //
  // retourne le nombre de champs de la ligne l
  // si l = 0 , retourne le nombre de champs de la ligne courante
  //
  controleEtat();
  if( l == 0 )
    return nombreChamps_;

  char *sauveDebutLigne = debutLigne_;
  int  sauveNumLigne = numLigne_;
  int nbchamps;
  rechercheLigne( l );
  nbchamps = compteChamps( debutLigne_ , 0 );
  // restaure les valeurs :
  numLigne_ = sauveNumLigne;
  debutLigne_ = sauveDebutLigne;
  return nbchamps;
}
 
int IterateurChampLigne::operator++(int)
  throw(ClubErreurs)
{
  //
  // avance au champ suivant ou si fin de ligne
  // passe a ligne suivante puis au champ suivant.
  controleEtat();
  if( numChamp_ < nombreChamps_ )
  {
    rechercheChampLigne( numChamp_ + 1 );
  }
  else
  {
    do
    {
      if( numLigne_ < nombreLignes_ )
      {
        // il faut d'abord passer a ligne suivante :
        rechercheLigne( numLigne_ + 1 );
        // mise a jour du nombre de champs de la ligne :
        nombreChamps_ = compteChamps( debutLigne_ , 0 );
        if (nombreChamps_>0)
          rechercheChampLigne( 1 );
      }
      else
      {
        // debutLigne_ pointe sur la derniere ligne,
        // on positionne debutLigne_ et debutChamp_ sur le '\0'
        // ce qui provoquera l'etat termine de l'iterateur.
        while( debutLigne_ && *debutLigne_ ) debutLigne_++;
        debutChamp_ = debutLigne_;
        numChamp_++;
        numLigne_++;
        return 0;
      }
    } while (nombreChamps_ ==0 && numLigne_ <= nombreLignes_);
  }
  return( debutLigne_ <= total() 
          + longueur() + 1 );
}

int IterateurChampLigne::operator--(int)
  throw(ClubErreurs)
{
  // si le numero du champ est superieur a 1
  // on passe au champ precedent.
  // sinon on passe a la ligne precedente
  // puis au premier champ de cette ligne.
  controleEtat();
  
  if( numChamp_ > 1 )
  {
    rechercheChampLigne( numChamp_ - 1 );
  }
  else
  {
    do
    {
      if( numLigne_ > 1 )
      {
        rechercheLigne( numLigne_ - 1 );
        nombreChamps_ = compteChamps( debutLigne_ , 0 );
        if (nombreChamps_ >0)
          rechercheChampLigne( nombreChamps_ );
      }
      else
      {
        // on est deja sur la premiere ligne et il n'y a plus rien
        (*this).premier();
        return 0;
      }  
    } while ( nombreChamps_== 0 && numLigne_ >1);
  }
  if (numLigne_ == 1 && nombreChamps_ == 0 ) 
  {// on etait au debut du tampon , on s'y remet
    (*this).premier();
    return 0;
  }  
  return( debutLigne_ >= total() );
}



int IterateurChampLigne::longueurElement(int avecFin) const
  throw(ClubErreurs)
{
  // retourne la longueur de l'element courant
  // i.e. : le nombre d'octets renvoyes par valeur();
  // dans ce cas on peut faire appel a IterateurChamp::longueurElement()
  return IterateurChamp::longueurElement(avecFin);
}


const char* IterateurChampLigne::valeur () const
  throw(ClubErreurs)
{
  IterateurChampLigne *nonConstThis = (IterateurChampLigne *) this;
  nonConstThis->controleEtat();
  // l'attribut sortie_ est destiné à optimiser l'implantation de la classe
  // il est licite de le modifier au sein de cette méthode const
  string *ptrNonConstSortie = &(((IterateurChampLigne *) this)->sortie_);
  *ptrNonConstSortie = "";
  // prise en compte de lignes/champs vides
  if( nombreChamps_ == 0 || numChamp_ == 0)
    return "";
  if( debutChamp_ )
  {
    if( analyseChamp( debutChamp_ , 0) )
      return "";
  }
  return sortie_.c_str ();
}


void IterateurChampLigne::synchronize(int direction)
  throw(ClubErreurs)
{
  if( ptrTampon_ )
  {
    if( direction )
      // mise a jour a partir du tampon
      actualiseEtat();
    else
      affecteCourant( debutChamp_ );
  }
}

void IterateurChampLigne::actualiseEtat()
{
  //
  // met a jour les differents compteurs ainsi que
  // le pointeur courant_
  //
  etat_ = etat();
  
  // repositionner la ligne :
  debutLigne_ = courant();
  while( (debutLigne_ > total())&&(*(debutLigne_ - 1) != '\n')) 
    debutLigne_--;
  // on est oblige de reparcourir tout le tampon !
  char *s         = total();
  nombreLignes_   = 0;
  numLigne_       = 0;
  while( s && *s )
  {
    nombreLignes_++;
    
    // recherche du numero de ligne.
    if( s == debutLigne_ ) numLigne_ = nombreLignes_;
    
    // recherche de la fin de la ligne.
    while( *s && (*s != '\n') ) s++;
    
    // saut de la fin de ligne :
    if( *s ) s++;
  }
  // mise a jour du nombre de champs :
  nombreChamps_ = compteChamps( debutLigne_ , 0 );
  
  // mise a jour de informations relatives au champ courant :
  // repositionner debutChamp_ sur le debut du champ :
  // si le nombre de champ existe
  // L'appel suivant ne semble pas utile, il pose probleme pour
  // passer au champ qui suit un commentaire place en fin de ligne
  // debutDeChampLigne( courant() );
}

void IterateurChampLigne::actualise()
  throw(ClubErreurs)
{

  etat_ = etat();
  char *s = total();
  nombreChamps_ = compteChamps( s, 1 );
  // mise a jour du nombre de lignes :
  s = total();
  nombreLignes_ = compteLignes( s);
  debutLigne_ = total();
  IterateurLigne::synchronize();
  premier();  
}

void IterateurChampLigne::rechercheChampLigne( int c )
  throw(ClubErreurs)
{
  //
  // recherche du champ c, dans la ligne courante
  //
  if (total() == 0)
    throw ClubErreurs( ClubErreurs::tampon_vide          ,
                       (ptrTampon_) ? ptrTampon_->nom() : ""   );

  // prise en compte de champ vide ( si la ligne est vide )
  if( nombreChamps_ == 0 )
  {
    debutChamp_ = debutLigne_;
    numChamp_   = 1;

  }
    

  // test de validité de la demande
  if ((c < 1) || (c > nombreChamps_))
    throw ClubErreurs( ClubErreurs::champ_hors_domaine   ,
                       c                                 ,
                       1                                 ,
                       nombreChamps_                     ,
                       ( ptrTampon_ ) ? ptrTampon_->nom() : "" );

  // parce que l'on ne sait pas toujours si numChamp_ est a jour
  // on repart systematiquement de debutLigne_
  debutChamp_ = (char *) sauteChampAvant( debutLigne_,
					  c-1,
					  0);
  if( debutChamp_ == 0 )
  {
    debutChamp_ = debutLigne_;
    numChamp_   = 1;
  }
  else
  {
    numChamp_ = c;
  }
  // positionner sur le debut du champ :
  while( estSeparateur( *debutChamp_ ) && (*debutChamp_ != '\n'))
    debutChamp_++;
}


void IterateurChampLigne::debutDeChampLigne( const char* mobile )
{

  //
  // repositionne sur le debut du champ qui contient mobile
  // pour la ligne courante.
  // si la ligne est vide,
  // debutChamp_ pointe sur debutLigne_ et numChamp_ vaut 1.

  numChamp_ = 0;
  //protection contre un tampon vide
  if (mobile && *mobile)
  { 
    debutChamp_ = debutLigne_;
    
    // traite le cas des lignes vides et des lignes
    // ne contenant que des commentaires.
    if( !nombreChamps_ )
    {
      numChamp_++;
      return;
    }
    char *champPrecedent = debutChamp_;
    // recherche du champ contenant mobile, si mobile fait partie
    // d'un commentaire on pointe sur le champ juste avant.
    //
    while( debutChamp_ && *debutChamp_ && (debutChamp_ < mobile ) )
    {
      // saut des blancs initiaux .
      while( estSeparateur(*debutChamp_)&&(*debutChamp_ != '\n'))
        debutChamp_++;
      if ((*debutChamp_ == '\0') || (*debutChamp_ == '\n'))
      { // la boucle s'est arrêtée pour cause de fin de ligne prématurée
        // on met debutChamp_ a 0 pour indiquer l'inexistance du champ demandé
        // i.e. : mobile n'appartient pas a la ligne debutLigne_.
        debutChamp_ = 0;
      }
      else
      { 
        champPrecedent = debutChamp_;
        // on passe le champ , et si on se retrouve apres mobile
        // on etait sur le bon champ.
        debutChamp_ = (char *)sauteChaine (debutChamp_);
        if( debutChamp_ )
        {
          numChamp_++;
        }
        if( debutChamp_ >= mobile )
        {
          debutChamp_ = champPrecedent;
          mobile = debutChamp_; // pour sortir de la boucle
        }
        
      }
      
    }
    // on elimine les blancs initiaux :
    if( numChamp_ == 0 ) numChamp_ = 1;
    while( estSeparateur(*debutChamp_)&&(*debutChamp_ != '\n'))
      debutChamp_++;
  }
}
