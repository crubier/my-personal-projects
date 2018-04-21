///////////////////////////////////////////////////////////////////////////////
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
//>       IterateurAscii.h
//$Resume
//       fichier d'en-tête de la classe IterateurAscii
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class TamponAscii   
//>       class IterateurAscii
//$Historique
//       $Log: IterateurAscii.h,v $
//       Revision 1.7  2002/12/09 15:53:42  club
//       DM-ID 12 Mise en conformité des constructeurs/destructeurs avec la norme qualité
//
//       Revision 1.6  2000/10/25 09:31:43  club
//       modification des include du standard C++ : suppression de ".h" dans le nom
//       du fichier inclus.
//
//       Revision 1.5  2000/10/24 14:18:14  club
//       mise à jour des includes et ajout des tests de configuration.
//
//       Revision 1.4  2000/09/11 12:18:50  club
//       Mise à jour des include et suppression des tests sur variable de
//       configuration de ClubConfig.h qui n'est pas installé.
//
//       Revision 1.3  2000/09/07 07:45:08  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//
//       Revision 1.2  2000/07/03 08:49:05  club
//       Ajout du copyright CNES
//
//       Revision 1.1.2.3  2000/04/04 07:08:08  club
//       déplacement du copyright
//
//       Revision 1.1.2.2  2000/04/03 16:30:37  club
//       replacement du copyright
//
//       Revision 1.1.2.1  2000/03/30 14:46:55  club
//       ajout du copyright CNES
//
//       Revision 1.1  1999/03/15 15:03:39  club
//       version initiale
//
//$Version
//       $Id: IterateurAscii.h,v 1.7 2002/12/09 15:53:42 club Exp $
//
//$Auteur
//        P-A.Cros M. Julien CSSI
//        O. Queyrut         CSSI
//        Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef club_IterateurAscii_h
#define club_IterateurAscii_h

#include <club/ClubConfig.h>

#if CLUB_HAVE_NAMESPACES
using namespace std;
#endif

#include <string>

#include "club/IterateurBase.h"

// definition en avant de la classe TamponAscii :
class TamponAscii;

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class IterateurAscii
//$Resume
//
//$Description
//
//$Usage
//>     construction : 
//          protégée car seuls les classes dérivées peuvent instancier
//          un itérateur ascii
//>     utilisation  : 
//>       virtual void synchronize    (int direction)
//          si direction = 1 synchronise la position de l'itérateur 
//          sur la position réelle dans le tampon (itérateur altéré 
//          lors d'une modification du tampon)
//          si direction = 0 (par defaut)
//          synchronise l'état du tampon (position courante du curseur) 
//          sur la position courante de l'itérateur (mémorisation avant
//          altération du tampon)
//>       virtual const char * valeur ()
//          renvoie la valeur de l'élément courant pointé par l'itérateur
//>       virtual int longueurElement ()
//          renvoie la longueur de l'élément courant, en comptant ou non le
//          caractère fin de ligne
//>       char* total                 () protegee - 
//          retourne un pointeur sur le tampon constant contenant les
//          données (totalité du fichier)        
//>       char* courant               () protegee - 
//          retourne la position courante dans le tampon 
//>       void affecteCourant         () protegee - 
//          mémorise la position courante de l'itérateur dans le tampon 
//>       int tailleAllouee           () protegee - 
//          retourne la taille du tampon 
//>       unsigned long etat          () protegee - 
//          retourne l'état courant du tampon 
//>       int longueur                () protegee - 
//          retourne la longueur totale du tampon
//>       int estCarGuillemet         () protegee - 
//          retourne vrai si le caractère courant est un guillemet 
//>       int estCarCommentaire       () protegee - 
//          retourne vrai si le caractère courant est un marqueur de commentaire 
//>       int estSeparateur           () protegee - 
//          retourne vrai si le caractère courant est un séparateur 
//>       const char* sauteChaine     () protegee - 
//          retourne l'état courant du tampon 
//>       virtual void  actualiseEtat () protegee - 
//          remet l'itérateur en conformité avec l'état courant du tampon
//>       void controleEtat()
//          retourne vrai si l'état de l'itérateur est conforme à l'état du 
//          tampon
//$Auteur
//        P-A.Cros   CSSI
//        O. Queyrut CSSI
//        Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////



class IterateurAscii : public IterateurBase {
public :

  virtual void synchronize( int direction = 0 ) throw(ClubErreurs)= 0;
  
  // methode d'acces a la valeur de l'iterateur : 
  virtual const char * valeur() const throw(ClubErreurs)= 0;  

  // longueur de l'element valeur 
  // ( moins les caracteres separateurs eventuels si avecFin est faux )
  // ( avec au moins un separateur si avec fin est vrai ).
  // 
  virtual int longueurElement(int avecFin = 0) const throw(ClubErreurs)= 0;

protected :
  const TamponAscii*  ptrTampon_;
  string              sortie_; // utilise pour le retour de la valeur 
  
  // constructeur protege pour empecher l'instanciation :
  IterateurAscii  () 
    : ptrTampon_ (0), sortie_ ("") {}
  IterateurAscii (const IterateurAscii & other)
  {
    ptrTampon_ = other.ptrTampon_;
    sortie_    = other.sortie_;
  }
  IterateurAscii & operator = (const IterateurAscii & other)
  {
    if (this != &other)
    {
      ptrTampon_ = other.ptrTampon_;
      sortie_    = other.sortie_;
    }
    return *this;
  }
  virtual ~IterateurAscii()
    {}

  // methodes permettant aux classes filles d'acceder aux donnees
  // protegees de TamponAscii.
  char*         total           ();
  char*         courant         ();
  void          affecteCourant  (char* valeur) throw(ClubErreurs);
  int           tailleAllouee   ();
  int           longueur        () const;
  unsigned long etat            ();

  // reconnaissance des codes speciaux 
  int         estCarGuillemet      (char c) const;
  int         estCarCommentaire    (char c) const;
  int         estSeparateur        (char c) const;

  // deplacements
  const char* sauteChaine          (char*   mobile) const throw(ClubErreurs);

  // etat de l'iterateur :
  virtual void  actualiseEtat   () = 0;
  void controleEtat() const throw(ClubErreurs);


};

#endif
