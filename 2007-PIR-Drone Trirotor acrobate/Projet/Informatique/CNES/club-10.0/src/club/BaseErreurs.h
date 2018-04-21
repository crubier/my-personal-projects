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
//>       BaseErreurs.h
//
//$Resume
//       fichier d'en-tête de la classe BaseErreurs
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class BaseErreurs
//
//$Historique
//       $Log: BaseErreurs.h,v $
//       Revision 3.19  2002/12/09 15:52:37  club
//       DM-ID 12 Mise en conformité des constructeurs/destructeurs avec la norme qualité
//
//       Revision 3.18  2002/11/29 10:44:46  club
//       DM-ID 12 Correction de l'ordre des déclarations (public, protected, private)
//
//       Revision 3.17  2000/10/25 09:31:43  club
//       modification des include du standard C++ : suppression de ".h" dans le nom
//       du fichier inclus.
//
//       Revision 3.16  2000/10/24 14:18:14  club
//       mise à jour des includes et ajout des tests de configuration.
//
//       Revision 3.15  2000/09/11 12:18:50  club
//       Mise à jour des include et suppression des tests sur variable de
//       configuration de ClubConfig.h qui n'est pas installé.
//
//       Revision 3.14  2000/09/07 07:39:53  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//
//       Revision 3.13  2000/07/03 08:54:18  club
//       Ajout du copyright CNES
//
//       Revision 3.12.2.1  2000/03/30 14:46:53  club
//       ajout du copyright CNES
//
//       Revision 3.12  1999/08/12 13:55:10  club
//       La classe StructureErreurs devient interne à BaseErreurs
//
//       Revision 3.11  1999/08/12 09:56:39  club
//       création de la classe StructureErreurs utilisée par
//       BaseErreurs comme structure pour les données partagées
//       des instances d'erreur
//
//       Revision 3.10  1999/04/12 15:22:11  club
//       transfert du constructeur par défaut dans le fichier d'implantation
//
//       Revision 3.9  1999/03/15 14:52:13  club
//       modification du principe de copie ou affectation, toutes les instances
//       d'une même erreur partagent le même message par un TamponPartage
//       cette modification corrige le problème de duplication des messages lors de
//       la destruction des instances (instances créées par le lancement d'une
//       exception)
//
//       Revision 3.8  1998/07/27 10:13:57  club
//       passage à une configuration de type GNU (fichier ClubConfig.h généré)
//
//       Revision 3.7  1998/06/25 06:39:33  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 3.6  1998/04/26 13:06:45  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 3.5  1998/01/22 08:26:46  luc
//       amélioration de l'en-tête de classe
//
//       Revision 3.4  1997/08/21 16:33:55  luc
//       ajout d'un en-tête de fichier
//
//       Revision 3.3  1997/04/03 12:50:24  luc
//       inversion des codes de retour, 0 signifie désormais : pas d'erreur
//       
//       Revision 3.2  1997/03/25 14:51:42  luc
//       changement du type de retour des méthodes formate
//       (const char *  --> const ChaineSimple&)
//       ajout d'une signature pour la méthode protégée stockeMessage
//       changement des règles de nommage
//       
//       Revision 3.1  1997/03/19 14:40:06  luc
//       utilisation de la classe ChaineSimple
//       renommage de la bibliothèque util_c++ en club
//       passage de SCCS à RCS
//       
//       Revision 2.1  1996/07/15 17:11:41  luc
//       élimination de la dépendance au tools.h++ (Rogue Wave)
//       
//       Revision 1.6  1994/12/22 15:48:01  mercator
//       modification de la methode why () de facon a ne jamais retourner NULL
//       (on retourne une chaine vide s'il n'y a pas d'erreur)
//       
//       Revision 1.5  1994/11/09 14:59:32  mercator
//       elimination des directives #pragma
//       
//       Revision 1.4  1994/09/13 08:30:32  mercator
//       elimination de la derivation a partir de RWXmsg
//       apres decouverte d'une incoherence dans les #ifdef de RogueWave
//       (signature du constructeur de RWXmsg variable)
//       
//       Revision 1.3  1994/09/09 14:10:33  mercator
//       remplacement des fonctions de lancement d'exceptions
//       par des fonctions configurables par l'utilisateur
//       
//       Revision 1.2  1994/08/30 12:53:20  mercator
//       remplacement des fonctions de lancement d'exceptions
//       par des fonctions configurables par l'utilisateur
//       ajout d'une fonction d'affichage par defaut dans l'interface publique
//       
//       Revision 1.1  1994/07/27 11:55:27  luc
//       Initial revision
//
//$Version
//       $Id: BaseErreurs.h,v 3.19 2002/12/09 15:52:37 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       M. Julien    CSSI
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __club_BaseErreurs_h
#define __club_BaseErreurs_h

#include <club/ClubConfig.h>

#if CLUB_HAVE_NAMESPACES
using namespace std;
#endif

#include <iostream>
#include <new>
#include <cstdarg>

#include <string>

#include "club/TamponPartage.h"

const int AucuneErreur =  0;
const int CodeInconnu  = -1;


///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class BaseErreurs
//
//$Resume
//       classe abstraite de gestion d'erreurs
//
//$Description
//       cette classe implante un mécanisme de gestion des erreurs
//       permettant le stockage d'un code et d'un domaine d'erreur à
//       l'usage du programme (pour que l'appelant puisse reconnaître
//       les différentes erreurs) et le stockage d'un message à
//       l'usage de l'utilisateur. Le formatage est séparé de
//       l'affichage, car une bibliothèque doit générer ses erreurs à
//       bas niveau mais d'une part ne sait pas si une erreur sera
//       corrigée à plus haut niveau ou affichée. La classe peut
//       afficher l'erreur soit sur demande soit si l'instance est
//       détruite avant d'avoir été corrigée. La classe utilise le
//       système de traduction s'il est en place. Elle peut travailler
//       avec ou sans exceptions.
//
//$Usage
//>     construction : 
//          à partir du code d'erreur (ou du format) et des arguments
//          associés (sous forme d'arguments variables ou de va_list)
//          par copie et affectation
//>     utilisation  : 
//>       BaseErreurs& operator =     () 
//          affectation
//>       void miseAJour              () 
//          reformate l'instance avec une nouvelle erreur
//>       int correspond              () 
//          indique si une erreur correspond à un code et un domaine
//          donnés
//>       void affiche                () 
//          affiche l'erreur courante (soit sur un flot spécifié, soit
//          à l'aide d'une fonction utilisateur)
//>       static void avertissement   () 
//          crée une erreur à partir d'un format et de ses arguments
//          et l'affiche si le drapeau d'avertissement l'autorise.
//>       static int erreur           () 
//          crée une erreur dans l'instance fournie en argument si
//          elle existe (pointeur non nul) ou dans un objet local
//>       void correction             () 
//          remet l'erreur à zéro
//>       const char* why             () 
//          retourne le message d'erreur
//>       int code                    () 
//          retourne le code d'erreur
//>       virtual const char* domaine () 
//          retourne le domaine d'erreur
//>       int existe                  () 
//          indique si une erreur existe (c'est à dire si le code
//          n'est pas AucuneErreur)
//>       static int okavt            () 
//         indique si la fonction "avertissement" doit faire quelque
//         chose ou non
//>       static int exceptions       () 
//         indique si la fonction "erreurs" doit générer des
//         exceptions lorsque l'appelant ne lui fournit pas de
//         pointeur d'erreur
//>       static void (* fonAffiche ()) (const char*, void*)
//         retourne un pointeur sur la fonction d'affichage
//>       static void* argAffiche     () 
//         retourne un pointeur sur l'argument d'affichage anonyme
//
//$Auteur
//       L. Maisonobe CNES
//       M. Julien    CSSI
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class BaseErreurs
{ 
  // classe procurant une structure pour les données partagées des 
  // instances d'erreur
  class StructureErreurs {
    
    public :
    
    // méthodes utilisées pour la construction du TamponPartage
    static StructureErreurs *AlloueMessage (void)
    { return new StructureErreurs (); }
    
    static void LibereMessage (void *memoire, void *)
    { delete ((StructureErreurs *) memoire); }

    // constructeur
    StructureErreurs () : msg_ (), code_ (AucuneErreur) {}
    
    // modification des attributs privés
    void reinitialiseCode (int code) { code_ = code; }
    void reinitialiseMessage (const char   *message) { msg_ = message; }
    void reinitialiseMessage (const string& message) { msg_ = message; }

    // accesseurs
    int code () const { return code_; }
    const char* msg () const { return (msg_.c_str ()); }

    protected :

    // constructeur par copie
    StructureErreurs (const StructureErreurs & other)
    {
      msg_  = other.msg_;
      code_ = other.code_;
    }
    // constructeur par affectation
    StructureErreurs & operator = (const StructureErreurs & other)
    {
      if (this != &other)
      {
        msg_  = other.msg_;
        code_ = other.code_;
      }
      return *this;
    }

    // destructeur
    ~StructureErreurs () {}

    private:

    // les données partagées sont le code d'erreur et le message d'erreur
    // afin qu'une erreur construite par copie ou affectation ne provoque
    // pas l'affichage du message d'erreur à sa destruction si
    // l'original a été corrigé.
    string       msg_  ;
    int          code_ ;  

  };

  public :

  // constructeurs
  BaseErreurs     ();
  BaseErreurs     (int code ...);
  BaseErreurs     (const char* format ...);
  BaseErreurs     (const BaseErreurs& e)
  {
    donneesPartagees_ = TamponPartage(e.donneesPartagees_);
  }

  // affectation
  BaseErreurs& operator =        (const BaseErreurs& e);

  // fonctions de réinitialisation de l'erreur
  void miseAJour                 (int code ...);
  void miseAJour                 (const char* format ...);
  void correction                () { stockeCode (AucuneErreur); }

  // destructeur
  virtual ~BaseErreurs           ();

  // fonctions d'accès aux éléments canoniques
  const char*         why        () const 
  { 
    return ((StructureErreurs *) donneesPartagees_.memoire ())->msg () ;
  }
  
  int                 code       () const 
  { 
    return ((StructureErreurs *) donneesPartagees_.memoire ())->code () ;
  }
  
  virtual const char* domaine    () const { return "base"; }
  int                 correspond (int code, const char* domaine) const;
  int                 existe     () const { return (code() == AucuneErreur)
                                                   ? 0 : 1;
                                          }

  // fonctions d'affichage
  ostream& affiche (ostream& s) const { return s << why () << '\n'; }
  void     affiche ()           const;

  // personnalisation de la gestion GLOBALE des erreurs
  static void initErreurs (void (*f) (const char*, void*), void* arg,
                           int       exceptions = 0,
                           int       avertissements = 0);

  // fonctions d'accès aux éléments de gestion GLOBALE
  static int                           okavt ()  { return avertissements_; }
  static int                           exceptions () { return exceptions_; }
  static void (* fonAffiche ()) (const char*, void*) { return fonAffiche_; }
  static void*                         argAffiche () { return argAffiche_; }

  // déclenchement général d'un avertissement
  static void avertissement (const char* format ...);

  // déclenchement général d'une erreur (utile surtout pour les bibliothèques)
  static int erreur (BaseErreurs* ptr, int code ...);
  static int erreur (BaseErreurs* ptr, const char* format ...);

  protected :

  void stockeMessage (const char         *message)
  { ((StructureErreurs *) donneesPartagees_.memoire())
      -> reinitialiseMessage (message); }
  
  void stockeMessage (const string& message)
  { ((StructureErreurs *) donneesPartagees_.memoire())
      -> reinitialiseMessage (message); }

  void stockeCode (int code)
  { ((StructureErreurs *) donneesPartagees_.memoire())
      -> reinitialiseCode (code); }

  virtual const string& formate (int code,           va_list ap) const;
          const string& formate (const char* format, va_list ap) const;

  private :

  // tampon partage de ce message
  TamponPartage donneesPartagees_;

  // arguments de gestion GLOBALE des erreurs
  static int       exceptions_;
  static int       avertissements_;
  static void*     argAffiche_;
  static void    (*fonAffiche_) (const char* message, void* arg);

};


#endif
