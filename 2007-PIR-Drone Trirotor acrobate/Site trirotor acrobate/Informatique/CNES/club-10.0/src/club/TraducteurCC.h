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
//>       TraducteurCC.h
//
//$Resume
//       fichier d'en-tête de la classe Traducteur
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class Traducteur      
//>       int domtrad_()        
//>       void tradext_()       
//>       void tradint_()       
//>       void tradform_()      
//>       void tradecrch_()     
//>       void tradecrfd_()     
//>       void InitDomaineClub()
//
//$Historique
//       $Log: TraducteurCC.h,v $
//       Revision 2.18  2002/11/29 15:51:24  club
//       DM-ID 12 Correction de l'ordre des déclarations (public, protected, private)
//
//       Revision 2.17  2001/02/16 12:27:29  club
//       remplacement de la classe hash_map par la classe standard map
//
//       Revision 2.16  2000/10/25 09:31:44  club
//       modification des include du standard C++ : suppression de ".h" dans le nom
//       du fichier inclus.
//
//       Revision 2.15  2000/10/24 14:18:15  club
//       mise à jour des includes et ajout des tests de configuration.
//
//       Revision 2.14  2000/09/11 12:18:51  club
//       Mise à jour des include et suppression des tests sur variable de
//       configuration de ClubConfig.h qui n'est pas installé.
//
//       Revision 2.13  2000/09/07 07:45:42  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//
//       Revision 2.12  2000/08/30 14:12:37  club
//       Utilisation de hash_map au lieu de Adressage pour stocker la table de
//       correspondance. Ajout des include hash_map et string de la STL.
//       Utilisation de l'espace de nommage de la STL.
//
//       Revision 2.11  2000/08/25 06:59:47  club
//       ajout de l'include FormatC pour permettre l'utilisation de ses
//       services dans la traduction des messages.
//
//       Revision 2.10  2000/07/03 08:54:19  club
//       Ajout du copyright CNES
//
//       Revision 2.9.2.1  2000/03/30 14:46:59  club
//       ajout du copyright CNES
//
//       Revision 2.9  1998/07/27 10:14:16  club
//       passage à une configuration de type GNU (fichier ClubConfig.h généré)
//
//       Revision 2.8  1998/06/25 06:49:03  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 2.7  1998/04/26 13:02:55  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 2.6  1998/01/22 08:30:41  luc
//       amélioration de l'en-tête de classe
//
//       Revision 2.5  1997/08/28 20:21:46  luc
//       ajout des interfaces fortran tradecrch_ et tradecrfd_
//       amélioration des messages d'erreurs de traduction de formats fortran
//       changement de signature de traductionFormatF
//
//       Revision 2.4  1997/08/21 16:37:43  luc
//       ajout d'un en-tête de fichier
//
//       Revision 2.3  1997/03/25 15:00:52  luc
//       changement des règles de nommage
//       
//       Revision 2.2  1997/03/19 16:20:30  luc
//       utilisation de la classe ChaineSimple
//       renommage de la bibliothèque util_c++ en club
//       passage de SCCS à RCS
//       
//       Revision 2.1  1996/07/15 17:31:58  luc
//       élimination de la dépendance au tools.h++ (Rogue Wave)
//       
//       Revision 1.1  1995/10/09 16:05:39  mercator
//       Initial revision
//
//$Version
//       $Id: TraducteurCC.h,v 2.18 2002/11/29 15:51:24 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __club_TraducteurCC_h
#define __club_TraducteurCC_h

#include <club/ClubConfig.h>

#if CLUB_HAVE_NAMESPACES
using namespace std;
#endif

#include <map>
#include <string>

#include "club/FormatC.h"
#include "club/FormatFortran.h"

// fonctions C d'interface FORTRAN avec le systeme de traduction général
// domtrad_ retourne 0 en cas de problème -on peut l'ignorer-)
extern "C" {
int         domtrad_                  (const char* domaine, long int lDecl);
void        tradext_                  (const char* interne, char* externe,
                                       int&        lUtile,
                                       long int    lDeclInt,
                                       long int    lDeclExt);
void        tradint_                  (const char* externe, char* interne,
                                       int&        lUtile,
                                       long int    lDeclExt,
                                       long int    lDeclInt);
void        tradform_                 (const char* interne, char* externe,
                                       int&        lUtile,
                                       long int    lDeclInt,
                                       long int    lDeclExt);
void        tradecrch_                (char* chaine, int& lUtile,
                                       const char* format ...);
void        tradecrfd_                (int& fd, const char* format ...);
           }

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class Traducteur
//
//$Resume
//       classe de traduction de mots-clefs et de messages
//
//$Description
//       gestion de la traduction de mots-clefs de messages et de
//       formats
//
//$Usage
//>     construction : 
//          sans argument (on utilise pour la langue la variable
//          d'environnement définie par la constante symbolique
//          CL_VAR_LANG, ou la chaine "??" par défaut) à partir de la
//          langue utilisateur
//>     utilisation  : 
//>       Traducteur& operator =                () 
//          affectation
//>       void ajouterDomaine                   () 
//          ajoute un domaine à l'ensemble des domaines gérés
//>       int domaineMembre                     () 
//          teste si un domaine fait partie de la liste des domaines
//          gérés
//>       const string& operator()              () 
//          retourne la traduction de la chaîne. Si la chaîne n'est
//          pas traduisible, retourne la chaîne initiale.
//>       const string& traductionFormatC       () 
//          retourne la traduction d'un format du langage C. Si le
//          format n'est pas traduisible, cette fonction retourne le
//          format initial, si le format est traduisible mais
//          incompatible avec le format initial (par exemple %s et %d
//          inversés), la référence est construite à partir d'un
//          avertissement suivi du format initial.  On est donc assuré
//          de pouvoir utiliser le format résultat dès lors que le
//          format origine est compatible avec les arguments du
//          printf.
//>       int traductionFormatF                 () 
//          retourne la traduction d'un format du langage Fortran. Si
//          le format n'est pas traduisible, cette fonction retourne
//          le format initial, si le format est traduisible mais
//          incompatible avec le format initial (par exemple %s et %d
//          inversés), la référence est construite à partir d'un
//          avertissement suivi du format initial.  On est donc assuré
//          de pouvoir utiliser le format résultat dès lors que le
//          format origine est compatible avec les arguments du
//          printf.
//>       const string& langueUtilisateur       () 
//          retourne une référence constante sur la langue de
//          l'utilisateur
//
//$Auteur
//       L. Maisonobe CNES
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class Traducteur
{ 
  public :

  // constructeurs
  Traducteur ();
  Traducteur (const char *langueUtilisateur)
    : tableCorrespondance_ (), nbDomaines_ (0), domaines_ (0),
      langueUtilisateur_ (langueUtilisateur)
  {}

  // copie constructeur et affectation
  Traducteur (const Traducteur& t);
  Traducteur& operator = (const Traducteur& t);

  // destructeur
 ~Traducteur () {if (nbDomaines_) delete [] domaines_; }

  // fonctions de gestion du traducteur lui-même
  void        ajouterDomaine            (const char  *domaine,
                                         TamponTexte& fichier,
                                         int          cleSurChampsImpairs);

  int         domaineMembre             (const char  *domaine) const;

  const string& langueUtilisateur () const { return langueUtilisateur_; }

  // fonctions de traduction
  const string&  operator ()       (const char *clef)   const;
  const string&  traductionFormatC (const char *format) const;
  int traductionFormatF (const char *format, FormatFortran *ptrTrad) const;

  protected :

  map<string, string> tableCorrespondance_;
  int                 nbDomaines_;
  string             *domaines_;
  string              langueUtilisateur_;

};

// fonction d'initialisation du domaine de traduction "club"
void InitDomaineClub ();

#endif
