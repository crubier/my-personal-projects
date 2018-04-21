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
//>       IterateurChamp.cpp
//$Resume
//       fichier d'implantation de la classe IterateurChamp
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class IterateurChamp
//>         IterateurChamp()
//>         premier()
//>         dernier()
//>         allerSur()
//>         termine()         
//>         nombreIterations()         
//>         longueurElement()
//>         valeur()       
//>         synchronize()       
//>         actualise()       
//>         actualiseEtat()   
//>         analyseChamps()    
//>         compteChamps()    
//>         sauteChampAvant() 
//>         rechercheChamp()    
//>         debutDeChamp()    
//$Historique
//       $Log: IterateurChamp.cpp,v $
//       Revision 1.7  2003/02/03 13:40:48  club
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
//       Revision 1.3.2.2  2000/04/03 16:37:51  club
//       ajout de ClubErreurs dans la liste des exceptions déclenchées par les
//       constructeurs
//
//       Revision 1.3.2.1  2000/03/30 14:46:48  club
//       ajout du copyright CNES
//
//       Revision 1.3  1999/07/07 07:55:16  club
//       Passage a une gestion d'erreurs par exceptions
//
//       Revision 1.2  1999/06/01 14:58:46  club
//       correction de l'include obsolete <strings.h> en "ClubConfig.h" et protection
//       pour les traitements sur un tampon vide
//
//       Revision 1.1  1999/03/15 13:22:48  club
//       version initiale
//
//$Version
//       $Id: IterateurChamp.cpp,v 1.7 2003/02/03 13:40:48 club Exp $
//$Auteur
//        P-A.Cros   CSSI
//        M. Julien  CSSI 
//        G. Lajon   CSSI
//        O. Queyrut CSSI
//        Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "club/IterateurChamp.h"
#include "club/TamponAscii.h"

#include "club/AnalyseurLexical.h"

IterateurChamp::IterateurChamp( const TamponAscii& tampon, int compterChamps )
  throw(ClubErreurs) : debutChamp_ (0), numChamp_ (0), nombreChamps_ (0)
{
  ptrTampon_ = &tampon;
  etat_   = etat();
  if (compterChamps)
  {
    nombreChamps_ = compteChamps( total(), 1 );
    premier();
  }
}


IterateurChamp::IterateurChamp( const TamponAscii* tampon, int compterChamps)
  throw(ClubErreurs) : debutChamp_ (0), numChamp_ (0), nombreChamps_ (0)
{
  ptrTampon_ =  tampon;
  etat_   = etat();
  if (compterChamps)
  {
    nombreChamps_ = compteChamps( total(), 1 );
    premier();
  }
}

void IterateurChamp::premier()
  throw(ClubErreurs)
{ 
  controleEtat();
  debutDeChamp( total() , 1);
}

void IterateurChamp::dernier()
  throw(ClubErreurs)
{
  controleEtat();
  rechercheChamp( nombreChamps_ , 1); 
}

void IterateurChamp::allerSur(int index)
  throw(ClubErreurs)
{
  controleEtat();
  // positionne le pointeur sur le numero de ligne index
  //  de la valeur de index :
  if( index > nombreChamps_ )
  {
    throw ClubErreurs( ClubErreurs::champ_hors_domaine,
                   index,1,nombreChamps_,ptrTampon_->nom());
  }
  if( index < 1 )
  {
    throw ClubErreurs( ClubErreurs::champ_hors_domaine,
                    index,1,nombreChamps_,ptrTampon_->nom());
  }
  rechercheChamp( index, 1 );
}


int IterateurChamp::termine() const
{ 
  return( !debutChamp_ || (*debutChamp_ == 0 ) ); 
}


int IterateurChamp::nombreIterations() const
  throw(ClubErreurs)
{ 
  controleEtat();
  return nombreChamps_; 
}

int IterateurChamp::operator++(int)
  throw(ClubErreurs)
{
  controleEtat();
  if( termine() )
    return 0;
  if( numChamp_ < nombreChamps_ )
  {
    rechercheChamp( numChamp_ + 1 , 1);
  }
  else{
    // debutChamp_ pointe sur le dernier champ,
    // on positionne debutChamp_ sur le '\0'
    // ce qui provoquera l'etat termine de l'iterateur.
    while( debutChamp_ && *debutChamp_ ) 
      debutChamp_++;
    numChamp_++;
  }
  return( debutChamp_ <= total() + longueur() + 1 );
}

int IterateurChamp::operator--(int)
  throw(ClubErreurs)
{
  if( numChamp_ > 1 )
  {    
    rechercheChamp( numChamp_ - 1 , 1);
    return( debutChamp_ >= total() );
  }
  else
  { // on ne peut pas decrementer
    return 0;
  }
}


int IterateurChamp::longueurElement(int avecFin) const
  throw(ClubErreurs)
  //
  // retourne la longueur de l'element.
  // i.e. : le nombre d'octets renvoyes par valeur.
  //
{
  controleEtat();
  char *mobile = debutChamp_;

  // on n'utilise pas les expressions rationnelles ici
  // car le traitement des caractères '\\' et '"' ne le permet pas,
  // d'autre part l'analyse directe en C est très simple...
  char* debut = mobile;

  // élimination des blancs initiaux
  while (( estSeparateur(*mobile) || (*mobile == '\n' ))
	 && ((*mobile != '\n') || avecFin))
    mobile++;

  if ((*mobile == '\0') || (*mobile == '\n'))
    return (mobile - debut); // la boucle s'est arrêtée en fin de ligne

  if ( ptrTampon_->interprete() && estCarCommentaire (*mobile))
  { // il faut analyser un commentaire
    while (*mobile && (*mobile != '\n'))
      mobile++;
     return (mobile - debut);
  }

  while (1)
  { // boucle sur les tronçons de champ entre et hors '"' et "'"

    if (estSeparateur(*mobile)
     || (*mobile == '\0') 
     || (*mobile == '\n')
     || (ptrTampon_->interprete() && estCarCommentaire(*mobile)))
      return (mobile - debut); // le caractère courant n'est pas dans le champ

    if (! estCarGuillemet (*mobile))
    { // le tronçon est une simple suite de caractères non blancs
      // et non commentaire si interprete_ est vrai,
      // et non fin de ligne si sauteFinLigne est faux.
      while ( *mobile
          && (*mobile != '\n' || avecFin )
          && (! estSeparateur   (*mobile)      )
          && (! estCarGuillemet (*mobile)      )
          && (! ptrTampon_->interprete() 
           || ! estCarCommentaire(*mobile)     ))
        mobile++;

    }

    if (estCarGuillemet (*mobile))
    { // analyse d'une chaîne de caractères au format C ou fortran
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
      { // il y a une erreur de syntaxe
        throw ClubErreurs( ClubErreurs::manque_guillemet     ,
                           (ptrTampon_) ? ptrTampon_->nom() : ""   );
      }
    }
  }
  return (mobile - debut);
}


const char* IterateurChamp::valeur () const
  throw(ClubErreurs)
{
  IterateurChamp *nonConstThis = (IterateurChamp *) this;
  nonConstThis->controleEtat();
  // l'attribut sortie_ est destiné à optimiser l'implantation de la classe
  // il est licite de le modifier au sein de cette méthode const
  string *ptrNonConstSortie = &(((IterateurChamp *) this)->sortie_);
  *ptrNonConstSortie = "";

  //prise en compte de lignes vides (ou commentaire)
  if( nombreChamps_ == 0 )
    return "";

  if( debutChamp_ ){
    if ( analyseChamp( debutChamp_ , 1) )
        return "";
  }
  return sortie_.c_str ();
}


void IterateurChamp::synchronize(int direction)
  throw(ClubErreurs)
{
  if( ptrTampon_ ){
    if( direction )
      // mise a jour a partir du tampon
      actualiseEtat();
    else
      affecteCourant( debutChamp_ );
  }
}


void IterateurChamp::actualise()
{
  etat_ = etat();
 // mise a jour du nombre de champs :
  nombreChamps_ = compteChamps( total(), 1 );
  // met a jour les differents compteurs ainsi que
  // le pointeur courant_
  // on est oblige de reparcourir tout le tampon !
  premier();
}

void IterateurChamp::actualiseEtat()
{
  etat_ = etat();
  // met a jour les differents compteurs ainsi que
  // le pointeur courant_
  // on est oblige de reparcourir tout le tampon !
  debutDeChamp( courant() , 1);
  // mise a jour du nombre de champs :
  nombreChamps_ = compteChamps( debutChamp_ , 1 );
  // on a compte le nombre de champs a partir de debutChamp_
  // pour avoir le nombre total il faut y rajouter le numero du champ
  // moins un ( puisque le champ courant a deja ete compte dans compteChamps)
  nombreChamps_ = nombreChamps_ + numChamp_ - 1;
}


int IterateurChamp::analyseChamp (const char* mobile, int sauteFinLigne ) const
  throw(ClubErreurs)
{ 
  // on n'utilise pas les expressions rationnelles ici
  // car le traitement des caractères '\\' et '"' ne le permet pas,
  // d'autre part l'analyse directe en C est très simple...

  // l'attribut sortie_ est destiné à optimiser l'implantation de la classe
  // il est licite de le modifier au sein de cette méthode const
  string *ptrNonConstSortie = &(((IterateurChamp *) this)->sortie_);
  *ptrNonConstSortie              = "";

  // élimination des blancs initiaux
  while (( (*mobile == '\n' ) || estSeparateur(*mobile))
	 && ((*mobile != '\n') || sauteFinLigne))
    mobile++;

  if ((*mobile == '\0') || (*mobile == '\n'))
    return CodeInconnu; // la boucle s'est arrêtée en fin de ligne

  if ( ptrTampon_->interprete() && estCarCommentaire (*mobile))
  { // il faut analyser un commentaire
    const char *debut = mobile;
    while (*mobile && (*mobile != '\n'))
      mobile++;
    *ptrNonConstSortie = string (debut, mobile - debut);
    return 0;
  }

  while (1)
  { // boucle sur les tronçons de champ entre et hors '"' et "'"

    if (estSeparateur(*mobile)
     || (*mobile == '\0') 
     || (*mobile == '\n')
     || (ptrTampon_->interprete() && estCarCommentaire(*mobile)))
      return 0; // le caractère courant n'est pas dans le champ

    if (! estCarGuillemet (*mobile))
    { // le tronçon est une simple suite de caractères non blancs
      // et non commentaire si interprete_ est vrai,
      // et non fin de ligne si sauteFinLigne est faux.
      while ( *mobile
          && (*mobile != '\n' || sauteFinLigne )
          && (! estSeparateur   (*mobile)      )
          && (! estCarGuillemet (*mobile)      )
          && (! ptrTampon_->interprete() 
           || ! estCarCommentaire(*mobile)     ))
        *ptrNonConstSortie += *mobile++;

    }

    if (estCarGuillemet (*mobile))
    { 
      // analyse d'une chaîne de caractères au format C ou fortran

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
        *ptrNonConstSortie += al.lexeme ();

        mobile += al.apresLexeme ();
      }
      else
      { // il y a une erreur de syntaxe
        throw ClubErreurs( ClubErreurs::manque_guillemet     ,
                           (ptrTampon_) ? ptrTampon_->nom() : ""   );
      }
    }
  }
}


int IterateurChamp::compteChamps (char* mobile, int sauteFinLigne ) const
{ 
//
// Calcul du nombre de Champ a partir d'une position donnee
//
  int nombre = 0;
 

  while (mobile && *mobile)
  { 
    // boucle sur les champs
    if (sauteFinLigne)
    {
      if (ptrTampon_->interprete() && estCarCommentaire(*mobile))
      {
        mobile = (char *)sauteChaine( mobile );
        nombre++; // Un commentaire est considere comme un champ
      }
      else 
        if ( (*mobile == '\n') || estSeparateur(*mobile))
        {
          mobile++;
        }
        else
        {
          mobile = (char *)sauteChaine (mobile );
          nombre++;
          if (mobile == 0)
          {
            return -1;
          }  
        }
    }
    else // not sauteFinLigne
    {
      if (*mobile == '\n')
      {
        return nombre;
      }
      
      if (ptrTampon_->interprete() && estCarCommentaire(*mobile))
      {
        mobile = (char *)sauteChaine( mobile );
        nombre++; // Un commentaire est considere comme un champ
        
        return nombre;
      }
      if (estSeparateur(*mobile))
      {
        mobile ++;
      }
      else
      {
        mobile = (char *)sauteChaine (mobile );
        nombre++;
        if (mobile == 0)
        {
          return -1;
        }  
      }
    }
  }
  return nombre;
}


const char* IterateurChamp::sauteChampAvant (char* mobile, int n,
                                             int sauteFinLigne) const
{ 
//
// sauter plusieurs champs a partir d'une position donnee
//
  if (n < 0)
    return 0;

  while (n--)
  { // boucle sur les champs à sauter

    // saut des blancs initiaux et des commentaires si interprete est vrai
    while ((  ((*mobile == '\n') || estSeparateur(*mobile))
              && ((*mobile != '\n') || sauteFinLigne)))
    {
        mobile++;
    }

    if ((*mobile == '\0') || (*mobile == '\n'))
    { // la boucle s'est arrêtée pour cause de fin de ligne prématurée
      // on retourne 0 pour indiquer l'inexistance du champ demandé
      return 0;
    }
    else
    { 
      mobile = (char *)sauteChaine (mobile);
      if (mobile == 0)
        return 0;
    }
  }
  // retour normal à la fonction appelante
  return mobile;
}


void IterateurChamp::rechercheChamp(int c, int sauteFinLigne ) 
  throw(ClubErreurs)
{
  if (total() == 0)
    throw ClubErreurs( ClubErreurs::tampon_vide          ,
                       (ptrTampon_) ? ptrTampon_->nom() : ""   );

  // test de validité de la demande
  if ((c < 1) || (c > nombreChamps_))
    throw ClubErreurs( ClubErreurs::champ_hors_domaine   ,
                       c                                 ,
                       1                                 ,
                       nombreChamps_                     ,
                       ( ptrTampon_ ) ? ptrTampon_->nom() : "" );

 if ( numChamp_ < c)
   { // il faut avancer dans le tampon

     debutChamp_ = (char *) sauteChampAvant( debutChamp_,
					    c - numChamp_, 
					    sauteFinLigne );
   }
 else if( numChamp_ > c )
   {
     debutChamp_ = (char *) sauteChampAvant( total(),
					     c-1     ,
					     sauteFinLigne  );
   }

 if( debutChamp_ == 0 ){
   debutChamp_ = total();
   numChamp_   = 1;
 }
 else
 {
   numChamp_ = c;
 }
 // positionner sur le debut du champ :
 while( ( (estSeparateur( *debutChamp_ ) || (*debutChamp_ == '\n') )
          && ((*debutChamp_ != '\n') || sauteFinLigne)))
 {
     debutChamp_++;
 }
}

void IterateurChamp::debutDeChamp( const char *mobile, int sauteFinLigne)
{
  //
  // Recherche du debut d'un champ.
  // repositionne debutChamp_ sur le debut du champ qui contient
  // le pointeur mobile.
  // met a jour le compteur numChamp_
  //
  if (mobile && *mobile)
  {
    numChamp_ = 0;
    debutChamp_ = total();
    while( debutChamp_ && *debutChamp_ && (debutChamp_ < mobile ) ){
      // saut des blanc initiaux :
      // et des commentaires si interprete est vrai.
      while( (((*debutChamp_ == '\n') || estSeparateur(*debutChamp_))
              &&((*debutChamp_ != '\n')||sauteFinLigne))           )
      {
          debutChamp_++;
      }
      if ((*debutChamp_ != '\0') && (*debutChamp_ != '\n'))
      { 
        // on passe le champ , et si on se retrouve apres mobile
        // on etait sur le bon champ.
        char *s = debutChamp_;
        debutChamp_ = (char *)sauteChaine (debutChamp_);
        // 
        if( debutChamp_ )
        {
          numChamp_++;
        }
        if( debutChamp_ > mobile )
        {
          debutChamp_ = s;
          mobile = debutChamp_; // pour sortir de la boucle
        }
      }
    }
    // on elimine les blancs initiaux  et les commentaires: 
    if( numChamp_ == 0 ) numChamp_ = 1;
    while( ((*debutChamp_ == '\n') || (estSeparateur(*debutChamp_))
            &&((*debutChamp_ != '\n')||sauteFinLigne)))
    {
        debutChamp_++;
    }
  }
}
