////////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Type
//       DEF
//
//$Projet
//        Marmottes
//$Application
//        Club
//$Nom
//>       TamponAscii.cpp
//$Resume
//        Fichier d'implantation de la classe TamponAscii
//
//$Description
//        Module de definition de la classe 
//
//$Contenu
//>       class TamponAscii        
//>         TamponAscii()          
//>         operator =()           
//>         estCarGuillemet()      
//>         estCarCommentaire()    
//>         estSeparateur()        
//>         initCarCommentaires()  
//>         ajouteCarCommentaires()
//>         initSeparateurs()      
//>         ajouteSeparateurs()    
//>         insereZone()           
//>         insereAvant()          
//>         insereApres()          
//>         supprime()             
//>         remplace()             
//$Historique
//       $Log: TamponAscii.cpp,v $
//       Revision 1.6  2003/02/03 13:48:42  club
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.5  2000/10/24 08:33:31  club
//       modification des include standard du C : utilisation de cNAME au lieu de
//       NAME.h (pour permettre la compilation avec le Sun Workshop 5.0)
//
//       Revision 1.4  2000/09/07 08:06:52  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//
//       Revision 1.3  2000/07/03 08:57:21  club
//       Ajout du copyright CNES
//
//       Revision 1.2.2.2  2000/04/04 07:15:50  club
//       déplacement du copyright
//
//       Revision 1.2.2.1  2000/03/30 14:46:52  club
//       ajout du copyright CNES
//
//       Revision 1.2  1999/07/07 07:55:17  club
//       Passage a une gestion d'erreurs par exceptions
//
//       Revision 1.1  1999/03/15 13:26:08  club
//       version initiale
//
//$Version
//       $Id: TamponAscii.cpp,v 1.6 2003/02/03 13:48:42 club Exp $
//$Auteur
//        P-A.Cros    CSSI
//        O. Queyrut  CSSI
//        Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "club/TamponAscii.h"
#include "club/AnalyseurLexical.h"

TamponAscii::TamponAscii (FILE* ptrFic, int interprete)
  throw(ClubErreurs)  :
  interprete_ ( interprete )
{ 
  initCarCommentaires (NULL);
  initSeparateurs     (NULL);

  lit (ptrFic);

}

TamponAscii::TamponAscii (const char* nom, 
                          int interprete)
  throw(ClubErreurs) : interprete_ ( interprete )
{ 
  initCarCommentaires (NULL);
  initSeparateurs     (NULL);

   lit (nom);

}


TamponAscii::TamponAscii (const TamponAscii& t)
  : interprete_ ( t.interprete_ )
{ 
  etat_ = t.etat_;
  nom_ = t.nom_;
  carCommentaires_ = t.carCommentaires_;
  separateurs_     = t.separateurs_;
  tailleTampon_ = t.longueur_ + 1; 
  longueur_ = t.longueur_; 
  // tampon total
  total_ = new char [tailleTampon_];
  (void) strncpy (total_, t.total_, longueur_);
  total_ [longueur_] = '\0';

  // positionner le pointeur courant :
  int deplacement = t.courant_ - t.total_;
  courant_ = total_ + deplacement;

}

TamponAscii::TamponAscii (const TamponAscii* t)
  : interprete_ ( t->interprete_ )
{ 
  etat_ = t->etat_;
  nom_ = t->nom_;
  carCommentaires_ = t->carCommentaires_;
  separateurs_     = t->separateurs_;
  tailleTampon_ = t->longueur_ + 1; 
  longueur_ = t->longueur_; 
  //tampon total
  total_ = new char [tailleTampon_];
  (void) strncpy (total_, t->total_, longueur_);
  total_ [longueur_] = '\0';

  //positionner le pointeur courant :
  int deplacement = t->courant_ - t->total_;
  courant_ = total_ + deplacement;

}

TamponAscii& TamponAscii::operator = (const TamponAscii& t)
{ 
  if (this != &t)       // protection contre x = x
  { if (t.longueur_ + 1 > tailleTampon_)
    { // il faut allouer un nouveau tampon, l'ancien est trop petit
      if (total_ != NULL)
      delete [] total_;
      tailleTampon_ = t.longueur_ + 1;
      total_        = new char [tailleTampon_];
    }

    // copie des attributs
    nom_                   = t.nom_;
    carCommentaires_       = t.carCommentaires_;
    separateurs_           = t.separateurs_;
    longueur_              = t.longueur_;
    (void) strncpy (total_, t.total_, longueur_);
    total_ [longueur_]     = '\0';
    interprete_            = t.interprete_;
    etat_                  = t.etat_;
    //positionnement du pointeur courant :
    int deplacement = t.courant_ - t.total_;
    courant_ = total_ + deplacement; 

  }

  return *this;

}

void TamponAscii::initCarCommentaires (const char* chaine)
{ // changement des marqueurs de commentaires
 
  if ((chaine == NULL) || (*chaine == '\0'))
    carCommentaires_ = "#";  // réinitialisation à la valeur par défaut
  else
  { // l'appelant a fourni une chaîne explicite

    if (interprete_)
    { // extraction des caractères '"' et '\'' éventuels de la chaîne
      char *dst    = new char [1 + strlen (chaine)];
      char *mobile = dst;
      for (const char *src = chaine; *src; src++)
        if ((*src != '"') && (*src != '\''))
          *mobile++ = *src;
      *mobile = '\0';

      // sauvegarde de la chaîne nettoyée
      carCommentaires_ = dst;

      delete [] dst;

    }
    else
      carCommentaires_ = chaine;

  }

}

void TamponAscii::ajouteCarCommentaires (const char* chaine)
{ // changement des marqueurs de commentaires
  if ((chaine == NULL) || (*chaine == '\0'))
    return;

  if (interprete_)
  { // extraction des caractères '"' et '\'' éventuels de la chaîne
    char *dst    = new char [1 + strlen (chaine)];
    char *mobile = dst;
    for (const char *src = chaine; *src; src++)
      if ((*src != '"') && (*src != '\''))
        *mobile++ = *src;
    *mobile = '\0';

    // sauvegarde de la chaîne nettoyée
    carCommentaires_ += dst;

    delete [] dst;
  }
  else
    carCommentaires_ += chaine;

}

void TamponAscii::elimineCommentaires ()
  throw(ClubErreurs)
{ 
  //
  // elimine les commentaires reconnus dans le tampon.
  // operation inconsistante pour les Iterateurs i.e: 
  // tout iterateur defini sur l'objet n'est plus valide apres
  // cette operation.
  // Il faut donc mettre a jour l'etat du tampon.
  //
  etat_++;
  char* s = total_;
  char* d = total_;

  while (*s)
  { // boucle sur les champs

    // copie des séparateurs
    while (estSeparateur (*s) && (*s != '\n'))
      *d++ = *s++;

    // traitement du champ
    if (*s == '\n')
    { // copie de la fin de ligne
      *d++ = *s++;
    }
    else if (estCarCommentaire (*s))
    { // saut du commentaire
      while (*s && (*s != '\n'))
        s++;
    }
    else if (estCarGuillemet (*s))
    { // copie de la chaîne entre '"' ou '\''
      const char *fin = strchr (s, '\n');
      int lg = fin ? (fin - s) : strlen (s);
      AnalyseurLexical al (s, lg);
      al.autoriseChainesC       ();
      al.autoriseChainesFortran ();

      int code = al.suivant ();
      if ((code == AnalyseurLexical::codeChaineC)
          ||
          (code == AnalyseurLexical::codeChaineFortran))
      { // on a bien reconnu une chaîne
        // le lexème lui-même est inutilisable : la lecture l'a transformé
        lg = al.apresLexeme () - al.debutLexeme ();
        (void) strncpy (d, s, lg);
        s += lg;
        d += lg;
      }
      else
      { // il y a une erreur de syntaxe
        throw ClubErreurs( ClubErreurs::manque_guillemet,
                           nom_.c_str ()                 );
      }

    }
    else
    { // copie de la suite de caractères non blancs (sauf commentaires)
      while (*s && (!estSeparateur (*s)) && (! estCarCommentaire (*s))
             && (! estCarGuillemet (*s)))
        *d++ = *s++;
    }

  }

  // ajout du caractère de fin de chaîne
  *d = '\0';

  // mise à jour de la longueur
  longueur_ -= s - d;
  // mise a jour position courante : 
  if( courant_ > (total_ + longueur_ - 1 ) ){
    courant_ = total_ + longueur_ - 1;
  }

}

void TamponAscii::initSeparateurs (const char* chaine)
{ // changement des caractères séparateurs

  if ((chaine == NULL) || (*chaine == '\0'))
    separateurs_ = "\t\n\v\f\r ";   // réinitialisation à la valeur par défaut
  else
  { // l'appelant a fourni une chaîne explicite

    if (interprete_)
    { // extraction des caractères '"' et '\'' éventuels de la chaîne
      char *dst    = new char [1 + strlen (chaine)];
      char *mobile = dst;
      for (const char *src = chaine; *src; src++)
        if ((*src != '"') && (*src != '\''))
          *mobile++ = *src;
      *mobile = '\0';

      // sauvegarde de la chaîne nettoyée
      separateurs_ = dst;

      delete [] dst;

    }
    else
      separateurs_ = chaine;

    // il faut forcer '\n' comme etant un separateur ( notement pour 
    // pouvoir traiter le cas de ligne vide).
    separateurs_ += '\n';
  }

}

void TamponAscii::ajouteSeparateurs (const char* chaine)
{ // changement des séparateurs
  if ((chaine == NULL) || (*chaine == '\0'))
    return;

  if (interprete_)
  { // extraction des caractères '"' et '\'' éventuels de la chaîne
    char *dst    = new char [1 + strlen (chaine)];
    char *mobile = dst;
    for (const char *src = chaine; *src; src++)
      if ((*src != '"') && (*src != '\''))
        *mobile++ = *src;
    *mobile = '\0';

    // sauvegarde de la chaîne nettoyée
    separateurs_ += dst;

    delete [] dst;
  }
  else
    separateurs_ += chaine;

}

void TamponAscii::elimineBlancs ()
{ 
  //
  // elimine les blancs reconnus dans le tampon.
  // operation inconsistante pour les Iterateurs i.e: 
  // tout iterateur defini sur l'objet n'est plus valide apres
  // cette operation.
  // Il faut donc mettre a jour l'etat du tampon.
  //
  etat_++;
  char* s = total_;
  char* d = total_;

  while (*s)
  { // saut des blancs de début de ligne (et des lignes entièrement blanches)
    while (estSeparateur (*s))
      s++;

    if (*s == '\0')
    { // on a atteint la fin du tampon
      *d = '\0';
    }
    else
    { // recherche de la fin de ligne
      char* fin = s + 1;
      while (*fin && (*fin != '\n'))
        fin++;

      // recherche du dernier caractère non blanc
      char* dernier = fin - 1;
      while (estSeparateur (*dernier))
        dernier--;

      // copie des caractères entre s et dernier
      while (s <= dernier)
        *d++ = *s++;

      // copie du caractère de fin
      *d++ = *fin;

      // préparation de l'itération suivante
      s = fin;

    }

  }
  // mise à jour de la longueur
  longueur_ -= s - d;
  // mise a jour position courante : 
  if( courant_ > (total_ + longueur_ - 1 ) ){
    courant_ = total_ + longueur_ - 1;
  }
}

void TamponAscii::insereDebut (IterateurAscii& pos,
			      const char*     valeur )
  throw(ClubErreurs)
{
  //
  // insere la chaine valeur avant la position pointee par pos.
  //
  int nboctets;
  // synchro iterateur/tampon, apres l'appel courant_ pointe
  // sur le meme caractere que le pointeur interne de l'iterateur
  pos.synchronize();
  int deplacement = courant_ - total_;
  if( deplacement < 0 ) deplacement = 0;

  nboctets = insereZone( courant_ , valeur );
  // mise à jour de la longueur
  longueur_ += nboctets;
  // repositionner courant_ :
  courant_ = total_ + deplacement + nboctets;
  etat_++;
  // synchro tampon/iterateur, apres l'appel pos pointe sur la meme valeur
  // que courant_ et les compteurs internes de l'iterateur sont a jour :
  pos.synchronize(1);

}
 
void TamponAscii::insereFin (IterateurAscii& pos,
                             const char*     valeur )
  throw(ClubErreurs)
{
  //
  // insere la chaine valeur apres la position pointee
  // par pos. L'insertion se fait apres le dernier caractere
  // significatif pour l'iterateur. i.e. : on insere avant la marque
  // de fin d'element structurel. ainsi pour inserer une ligne apres
  // une autre avec un iterateur IterateurLigne il faudra que la chaine
  // valeur commence par '\n'.
  //
  int         nboctets;

  // synchro iterateur/tampon, apres l'appel courant_ pointe

  // sur le meme caractere que le pointeur interne de l'iterateur
  pos.synchronize();
  int deplacement = courant_ - total_;
  if( deplacement < 0 ) deplacement = 0;
  // on se positionne sur la fin de l'element, puis on effectue l'insertion.
  courant_ += pos.longueurElement();

  nboctets = insereZone( courant_ , valeur );
  // mise à jour de la longueur 
  longueur_ += nboctets;
  // repositionner courant_ :
  courant_ = total_ + deplacement;
  etat_++;

  // synchro tampon/iterateur, apres l'appel pos pointe sur la meme valeur
  // que courant_ et les compteurs internes de l'iterateur sont a jour :
  pos.synchronize(1);
}

void TamponAscii::supprime (IterateurAscii& pos )
  throw(ClubErreurs)
{
  // synchro iterateur/tampon, apres l'appel : courant_ pointe
  // sur le meme caractere que le pointeur interne de l'iterateur
  pos.synchronize();
  char* zdebut = courant_;
  int   deplacement = courant_ - total_;
  if( deplacement < 0 ) deplacement = 0;
  // on recherche la fin de l'element structurant :
  char *zfin = courant_ + pos.longueurElement(1) - 1;

  // suppression de la zone {zdebut,zfin}
  int nboctets = supprimeZone( zdebut, zfin );
  
  // mise a jour de l'etat du tampon :
  longueur_ -= nboctets;
  courant_ = total_ + deplacement;

  etat_++;
  pos.synchronize(1);
}

void TamponAscii::supprime (IterateurAscii& debut,
			   IterateurAscii& fin  )
  throw(ClubErreurs)
{
  // synchro iterateur/tampon, apres l'appel : courant_ pointe
  // sur le meme caractere que le pointeur interne de l'iterateur
  debut.synchronize();
  char* zdebut = courant_;
  int deplacement = courant_ - total_;

  // recherche de la fin de l'iteration de fin.
  fin.synchronize();
  char* zfin = courant_ + fin.longueurElement(1) - 1;

  // suppression de la zone (zdebut,zfin) :
  int nboctets = supprimeZone( zdebut, zfin );
  // mise a jour de l'etat du tampon :
  longueur_ -= nboctets;
  courant_  =  total_ + deplacement;
  etat_++;
  // courant_ pointe sur la nouvelle position de l'iterateur fin.

  fin.synchronize(1);
  // on repart de cette position pour l'iterateur debut et on decremente :
  debut.synchronize(1);
  debut--;

}

void TamponAscii::remplace (IterateurAscii& pos,
			   const char *    valeur )
  throw(ClubErreurs)
{
  //
  // remplace l'element pointe par pos par la chaine pointee par valeur.
  // seul les parties significative de l'element sont remplacees i.e.:
  // les separateurs ou les fin de lignes sont conserves, il est donc inutile
  // de les ajouter dans valeur.
  //
  // synchro iterateur/tampon, apres l'appel : courant_ pointe
  // sur le meme caractere que le pointeur interne de l'iterateur
  pos.synchronize();
  char* zdebut = courant_;

  int deplacement = courant_ - total_;
  if( deplacement < 0 ) deplacement = 0; 

  char* zfin = courant_+pos.longueurElement()-1;
  //zone a remplacer : zdebut,zfin

  int nboctets = supprimeZone( zdebut, zfin );
  // insertion en zdebut :
  // si la suppression n'a pas echoue.


  int nboctetsAjoutes = 0;
  // dans le cas d'un element vide la suppression renvoie 0
  // mais l'insertion reste possible.
  if( nboctets || !pos.longueurElement() )
    nboctetsAjoutes = insereZone( zdebut, valeur );

  // mise a jour de l'etat du tampon :
  longueur_ = longueur_ - nboctets + nboctetsAjoutes;
  courant_ = total_ + deplacement;
  etat_++;
  pos.synchronize(1);

}
 
void TamponAscii::remplace (IterateurAscii& debut,
			   IterateurAscii& fin,
			   const char*     valeur )
  throw(ClubErreurs)
{
  //
  // remplace les elements entre debut et fin (inclus) par la chaine pointee
  // par valeur.
  // lors de la supression du dernier element on conserve la valeur du ou des
  // separateurs ( de champ, ou de ligne). il n'est donc pas necessaire de
  // de les ajouter dans valeur.
  // synchro iterateur/tampon, apres l'appel : courant_ pointe
  // sur le meme caractere que le pointeur interne de l'iterateur
  debut.synchronize();
  char* zdebut = courant_;
  int deplacementFin = courant_ - total_;
  if( deplacementFin < 0 ) deplacementFin = 0;
  // sauver la position precedente de l'iterateur pour pouvoir restaurer
  // une position valide pour celui-ci.
  debut--;
  debut.synchronize();
  int deplacementDebut = courant_ - total_;
  if( deplacementDebut < 0 ) deplacementDebut = 0;
  // recherche de la position du pointeur de fin :
  //fin.synchronize();
  //  fin++;
  fin.synchronize();
  char* zfin = courant_ + fin.longueurElement() -1;
  // les elements a supprimer sont-il tous vides ?
  int estVide = (int)(zdebut <= zfin);
  //zone a remplacer : zdebut,zfin
  int nboctets = supprimeZone( zdebut, zfin );
  // insertion en zdebut :
  // si la suppression n'a pas echoue:
  int nboctetsAjoutes = 0;
  if( nboctets || estVide )
    nboctetsAjoutes = insereZone( zdebut, valeur );

  // mise a jour de l'etat du tampon :
  longueur_ = longueur_ - nboctets + nboctetsAjoutes;
  courant_ = total_ + deplacementFin + nboctetsAjoutes;
  etat_++;
  fin.synchronize(1);
  courant_ = total_ + deplacementDebut;
  debut.synchronize(1);
  debut++;
  
}

int TamponAscii::estCarGuillemet (char c) const
{ 
  return interprete_ && ((c == '"') || (c == '\'')); 
}


int TamponAscii::estCarCommentaire (char c) const
{
  // test direct du '\0' (strchr considèrerait qu'il est dans la chaîne)
  if (c == '\0')
    return 0;

  // recherche du caractère dans la chaîne
  return strchr (carCommentaires_.c_str (), c) ? 1 : 0;
}

int TamponAscii::estSeparateur (char& c) const
{
  // test direct du '\0' (strchr considèrerait qu'il est dans la chaîne)
  if (c == '\0')
    return 0;

  // recherche du caractère dans la chaîne
  return strchr (separateurs_.c_str (), c) ? 1 : 0;

}

int TamponAscii::supprimeZone( char* zdebut, char* zfin )
{
  // 
  // methode privee permettant de supprimer une zone du buffer.
  // Cette operation est inconsistante pour les iterateurs.
  // i.e. tout iterateur defini sur l'objet n'est plus valide
  // apres l'appel. Il faut synchroniser les iterateurs et le tampon.
  // Si zdebut,zfin n'est pas une zone valide (i.e. zfin > zdebut ),
  // la suppression n'est pas effectuee.
  //
  if( total_ == 0 )
    return 0;
  if( zdebut > zfin )
    return 0;
  // suppression
  int aSupprimer = zfin + 1 - zdebut;
  int aCopier    = total_ + longueur_ - zfin;
  for (int i = 0; i < aCopier; i++)
  { *zdebut = *(zdebut + aSupprimer);
  zdebut++;
  }

  return aSupprimer;
}

int TamponAscii::insereZone(char* pos, const char* valeur)
{
  // copie des morceaux de tampon
  int longueurChaine     = strlen (valeur);
  int longueurNecessaire = longueur_ + longueurChaine + 1;
  if (longueurNecessaire > tailleTampon_)
  { // il faut allouer un nouveau tampon
    char* tempo   = new char [longueurNecessaire];

    // copie (fonctionne même si total_ est nul, courant_ est alors aussi nul)
    if (pos != total_)
      (void) strncpy (tempo, total_, pos - total_);
    (void) strncpy (tempo + (pos - total_), valeur, longueurChaine);
    if (pos == 0)
    { // en fait c'est une création de tampon, pas une modification
      tempo [longueurChaine] = '\0';
    }
    else
      (void) strcpy  (tempo + (pos - total_) + longueurChaine, pos);

    // remplacement du tampon
    if (total_ != 0)
      delete [] total_;
    total_        = tempo;
    tailleTampon_ = longueurNecessaire;

  }
  else
  { // le tampon existant suffit

    // décalage de la fin du tampon, en commencant par les derniers caractères
    char* src = total_ + longueur_;
    char* dst = src + longueurChaine;
    while (src >= pos)
      *dst-- = *src--;

    // insertion de la chaîne
    (void) strncpy (pos, valeur, longueurChaine);

  }

  // retourne le nombre d'octet inseres :
  etat_++;
  return longueurChaine;

} 




 
