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
//>       FichierStructure.h
//
//$Resume
//       fichier d'en-tête de la classe FichierStructure
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class FichierStructure
//
//$Historique
//       $Log: FichierStructure.h,v $
//       Revision 3.18  2002/12/09 15:53:23  club
//       DM-ID 12 Mise en conformité des constructeurs/destructeurs avec la norme qualité
//
//       Revision 3.17  2002/08/30 08:30:11  club
//       Changement de signature d'une méthode
//
//       Revision 3.16  2002/06/27 15:50:06  club
//       ajout de la méthode listeSousBlocs
//
//       Revision 3.15  2000/10/25 09:31:43  club
//       modification des include du standard C++ : suppression de ".h" dans le nom
//       du fichier inclus.
//
//       Revision 3.14  2000/10/24 14:18:14  club
//       mise à jour des includes et ajout des tests de configuration.
//
//       Revision 3.13  2000/09/11 12:18:50  club
//       Mise à jour des include et suppression des tests sur variable de
//       configuration de ClubConfig.h qui n'est pas installé.
//
//       Revision 3.12  2000/09/07 07:38:11  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//
//       Revision 3.11  2000/07/03 08:54:19  club
//       Ajout du copyright CNES
//
//       Revision 3.10.2.1  2000/03/30 14:46:54  club
//       ajout du copyright CNES
//
//       Revision 3.10  1999/07/06 15:24:16  club
//       Changement des signatures pour gestion des erreurs
//       par mécanisme d'exception
//
//       Revision 3.9  1998/09/14 09:08:41  club
//       gestion de la date et de la signature du contenu des fichiers lus
//
//       Revision 3.8  1998/06/25 06:41:28  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//       élimination de la méthode estValide
//
//       Revision 3.7  1998/04/26 13:02:23  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 3.6  1998/01/22 08:28:19  luc
//       amélioration de l'en-tête de classe
//
//       Revision 3.5  1997/09/12 07:40:43  luc
//       correction d'un commentaire dans l'en-tête
//
//       Revision 3.4  1997/08/21 16:35:19  luc
//       ajout d'un en-tête de fichier
//
//       Revision 3.3  1997/04/03 12:50:40  luc
//       inversion des codes de retour, 0 signifie désormais : pas d'erreur
//       
//       Revision 3.2  1997/03/25 15:01:58  luc
//       changement des règles de nommage
//       
//       Revision 3.1  1997/03/19 14:42:42  luc
//       utilisation de la classe ChaineSimple
//       renommage de la bibliothèque util_c++ en club
//       passage de SCCS à RCS
//       
//       Revision 2.1  1996/05/14 08:26:38  luc
//       élimination des tools.h++
//       extension de l'indirection de bloc (notion de valeurs par défaut)
//       ajout de l'inclusion de fichiers
//       élimination de code redondant (lectures)
//       restructuration de code
//       
//       Revision 1.5  1994/12/13 07:55:21  mercator
//       ajout d'une interface en FILE* a la construction et a la lecture
//       
//       Revision 1.4  1994/11/20 14:22:48  mercator
//       ajout d'un pointeur d'erreur nul par defaut dans plusieurs fonctions membres
//       
//       Revision 1.3  1994/11/09 14:59:45  mercator
//       elimination des directives #pragma
//       
//       Revision 1.2  1994/09/28 16:28:41  mercator
//       prise en compte du changement de nom:
//       FichierTexte --> TamponTexte
//       
//       Revision 1.1  1994/07/27 11:55:29  luc
//       Initial revision
//
//$Version
//       $Id: FichierStructure.h,v 3.18 2002/12/09 15:53:23 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       G. Lajon     CSSI
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __club_FichierStructure_h
#define __club_FichierStructure_h

#include <club/ClubConfig.h>

#if CLUB_HAVE_NAMESPACES
using namespace std;
#endif

#include <string>
#include <vector>

#include "club/TamponTexte.h"
#include "club/TamponPartage.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class FichierStructure
//
//$Resume
//       classe gérant un fichier de données structurées (imbriquées)
//
//$Description
//       mécanisme de base de lecture de structures de données avec
//       plusieurs niveaux d'imbrication, la structuration n'étant pas
//       forcément figée au départ mais pouvant être découverte petit
//       à petit au cours de la lecture
//
//$Usage
//>     construction : 
//          sans argument, par un nom de fichier, par un fichier, par
//          un TamponTexte, par une clef et un père, par copie
//>     utilisation  : 
//>       FichierStructure& operator =   () 
//          affectation
//>       void lit                       () 
//          lit le bloc depuis un fichier
//>       bool terminal                  () 
//          indique si un bloc est terminal c'est a dire s'il ne
//          possède pas de sous-bloc)
//>       int nombreChamps               () 
//          retourne le nombre de champs d'un bloc terminal
//>       void champ                     () 
//          extrait d'un bloc terminal le nième champ et le met dans
//          le tampon de taille max
//>       bool contientSousBloc          () 
//          indique si un bloc contient un sous-bloc de clef donnée,
//          retourne un code en cas de problème
//>       const string& nomBloc          () 
//          retourne le nom du bloc (précédé des noms de ses pères)
//>       const string& nomFichier () 
//          retourne le nom du fichier
//>       const string& date             () 
//          retourne la date du plus récent des fichiers inclus
//>       unsigned int signature         () 
//          retourne une signature de l'ensemble des données
//
//$Auteur
//       L. Maisonobe CNES
//       G. Lajon     CSSI
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class FichierStructure
{ 
  public :

  // constructeurs
  FichierStructure ()
    : nomBloc_ (""), nomFichier_ (""), debut_ (0), fin_ (0),
      date_ ("1970-01-01 00:00:00"), signature_ (0)
  {}
  FichierStructure (FILE *ptrFic) throw (ClubErreurs);
  FichierStructure (const char   *nomFichier) throw (ClubErreurs);
  FichierStructure (const string& nomFichier) throw (ClubErreurs);
  FichierStructure (TamponTexte *fichier)     throw (ClubErreurs);

  FichierStructure (const char   *clef, const FichierStructure *pere)
    throw (ClubErreurs);
  FichierStructure (const string& clef, const FichierStructure *pere)
    throw (ClubErreurs);

  // copie constructeur et affectation
  FichierStructure             (const FichierStructure& f)
    : nomBloc_ (f.nomBloc_), nomFichier_ (f.nomFichier_),
      total_ (f.total_), debut_ (f.debut_), fin_ (f.fin_),
      date_ (f.date_), signature_ (f.signature_)
  {}
  FichierStructure& operator = (const FichierStructure& f);

  //destructeur
  ~FichierStructure () {}

  // lecture
  void        lit              (FILE *ptrFic) throw (ClubErreurs);
  void        lit              (const char   *nomFichier) throw (ClubErreurs);
  void        lit              (const string& nomFichier) throw (ClubErreurs);
  void        lit              (TamponTexte *ptrTampon) throw (ClubErreurs);

  // fonctions d'analyse
  bool        terminal         () const;
  int         nombreChamps     () const;
  void        champ            (int numero, char *tampon, const int max) 
    const throw (ClubErreurs);
  bool        contientSousBloc (const char *clef) const throw (ClubErreurs);
  void        listeSousBlocs   (vector<string> *ptrTable)
    const throw (ClubErreurs);

  const string& nomBloc    () const { return nomBloc_;    }
  const string& nomFichier () const { return nomFichier_; }

  const string& date       () const { return date_;      }
  unsigned int  signature  () const { return signature_; }

private:
  string            nomBloc_;
  string            nomFichier_;
  TamponPartage     total_;

  char             *debut_;
  char             *fin_;

  string            date_;
  unsigned int      signature_;

  void rechercheSousBloc (const string& clef,
                          const char  **addrDebut,   const char **addrFin,
                          string *addrNomBloc) const throw (ClubErreurs) ;

};

#endif
