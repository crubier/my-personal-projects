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
//>       AnalyseurLexical.h
//
//$Resume
//       fichier d'en-tête de la classe AnalyseurLexical
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class AnalyseurLexical
//
//$Historique
//       $Log: AnalyseurLexical.h,v $
//       Revision 1.14  2002/12/10 08:47:49  club
//       Modification visant à mettre le corps du destructeur dans le fichier H plutôt que dans le fichier CC.
//
//       Revision 1.13  2002/12/09 15:52:21  club
//       DM-ID 12 Mise en conformité des constructeurs/destructeurs avec la norme qualité
//
//       Revision 1.12  2001/04/04 11:29:11  club
//       ajout de la reconnaissance paramétrable des réels du langage fortran
//
//       Revision 1.11  2000/10/25 09:31:43  club
//       modification des include du standard C++ : suppression de ".h" dans le nom
//       du fichier inclus.
//
//       Revision 1.10  2000/10/24 14:18:14  club
//       mise à jour des includes et ajout des tests de configuration.
//
//       Revision 1.9  2000/09/11 12:18:50  club
//       Mise à jour des include et suppression des tests sur variable de
//       configuration de ClubConfig.h qui n'est pas installé.
//
//       Revision 1.8  2000/09/07 07:47:30  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//
//       Revision 1.7  2000/07/03 08:54:18  club
//       Ajout du copyright CNES
//
//       Revision 1.6.2.1  2000/03/30 14:46:53  club
//       ajout du copyright CNES
//
//       Revision 1.6  1998/06/25 06:38:19  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.5  1998/04/26 13:02:13  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.4  1998/01/22 08:26:24  luc
//       amélioration de l'en-tête de classe
//
//       Revision 1.3  1997/08/24 13:37:18  luc
//       reconnaissance des chaînes de caractères C et fortran
//       débrayage possible de la reconnaissance des réels
//       débrayage possible de la reconnaissance des chaînes
//       ajout des méthodes etatCourant et retourneAEtat
//
//       Revision 1.2  1997/08/21 16:33:46  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.1  1997/04/08 09:54:21  luc
//       Initial revision
//
//$Version
//       $Id: AnalyseurLexical.h,v 1.14 2002/12/10 08:47:49 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __club_AnalyseurLexical_h
#define __club_AnalyseurLexical_h

#include <club/ClubConfig.h>

#if CLUB_HAVE_NAMESPACES
using namespace std;
#endif

#include <string>

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class AnalyseurLexical
//
//$Resume
//       classe implantant un analyseur lexical simple
//
//$Description
//       cette classe implante un analyseur lexical paramétrable et
//       pouvant reconnaître les nombres, les parenthèses, les
//       séparateurs, les opérateurs, les noms et les chaines des
//       langages C et fortran.
//
//$Usage
//>     construction : 
//          sans argument, à partir d'une chaîne initiale, par copie
//>     utilisation  : 
//>       AnalyseurLexical& operator =      () 
//          affectation
//>       void redemarre                    () 
//          reprend l'analyse de la chaîne courante au début
//>       int suivant                       () 
//          passe au lexème suivant (retourne le type)
//>       int precedent                     () 
//          revient au lexème précédent (retourne le type)
//>       int retourneAEtat                 () 
//          remet l'instance dans un état mémorisé au préalable
//>       void initBlancs                   () 
//          réinitialise la liste des caractères blancs (ils séparent
//          les lexèmes mais ne sont pas des lexèmes en eux mêmes)
//>       void initSeparateurs              () 
//          réinitialise la liste des caractères séparateurs (ce sont
//          des lexèmes)
//>       void initOperateurs               () 
//          réinitialise la liste des caractères opérateurs (pas
//          d'opérateur à plusieurs caractères)
//>       void autoriseReels                () 
//          autorise la reconnaissance des réels
//>       void interditReels                () 
//          interdit la reconnaissance des réels
//>       void autoriseReelsFortran         () 
//          autorise la reconnaissance des réels du langage fortran
//>       void interditReelsFortran         () 
//          interdit la reconnaissance des réels du langage fortran
//>       void autoriseChainesC             () 
//          autorise la reconnaissance des chaînes du langage C
//>       void interditChainesC             () 
//          interdit la reconnaissance des chaînes du langage C
//>       void autoriseChainesFortran       () 
//          autorise la reconnaissance des chaînes du langage fortran
//>       void interditChainesFortran       () 
//          interdit la reconnaissance des chaînes du langage fortran
//>       void reinitialise                 () 
//          réinitialise l'analyseur pour la chaîne c (sans changer
//          les listes de séparateurs ou d'opérateurs, mais en se
//          replaçant au début)
//>       int etatCourant                   () 
//          retourne un état de sorte que l'on puisse y retourner par
//          la suite
//>       const string& chaine              () 
//         retourne la chaîne complète en cours d'analyse
//>       const string& lexeme              () 
//          retourne le lexème courant
//>       int debutLexeme                   () 
//          retourne l'index du premier caractère du lexème courant
//          dans la chaîne
//>       int apresLexeme                   () 
//          retourne l'index du caractère suivant le lexème courant
//          dans la chaîne
//>       int type                          () 
//          retourne le type du lexème courant
//>       int entier                        () 
//          retourne le dernier entier analysé
//>       double reel                       () 
//          retourne le dernier réel analysé
//>       const string& nom                 () 
//          retourne le dernier nom analysé
//>       const string& chaineC             () 
//          retourne la dernière chaîne du langage C analysée
//>       const string& chaineFortran       () 
//          retourne la dernière chaîne du langage fortran analysée
//>       char separateur                   () 
//          retourne le dernier séparateur analysé
//>       char parenthese                   () 
//          retourne la dernière parenthèse analysée
//>       char operateur                    () 
//          retourne le dernier opérateur analysé
//
//$Auteur
//       L. Maisonobe CNES
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class AnalyseurLexical
{

public :

  enum { codeFin,           codeSeparateur, codeOperateur, codeParenthese,
         codeEntier,        codeReel,       codeNom,       codeChaineC,
         codeChaineFortran, codeInconnu
       };

  // constructeurs et affectations
  AnalyseurLexical (const string& chaine);
  AnalyseurLexical (const char *chaine = 0);
  AnalyseurLexical (const char *chaine, int longueur);

  AnalyseurLexical (const AnalyseurLexical& a);
  AnalyseurLexical& operator = (const AnalyseurLexical& a);

  // destructeur
  ~AnalyseurLexical () {};

  // modification de l'analyseur
  void initBlancs (const string& blancs)
  { blancs_ = blancs; redemarre (); }

  void initBlancs (const char *blancs)
  { blancs_ = blancs; redemarre (); }

  void initSeparateurs (const string& separateurs)
  { separateurs_ = separateurs; redemarre (); }

  void initSeparateurs (const char *separateurs)
  { separateurs_ = separateurs; redemarre (); }

  void initOperateurs (const string& operateurs)
  { operateurs_ = operateurs; redemarre (); }

  void initOperateurs (const char *operateurs)
  { operateurs_ = operateurs; redemarre (); }

  void autoriseReels          () { reconnaitReels_          = true;  }
  void interditReels          () { reconnaitReels_          = false; }

  void autoriseReelsFortran   () { reconnaitReelsFortran_   = true;  }
  void interditReelsFortran   () { reconnaitReelsFortran_   = false; }

  void autoriseChainesC       () { reconnaitChainesC_       = true;  }
  void interditChainesC       () { reconnaitChainesC_       = false; }

  void autoriseChainesFortran () { reconnaitChainesFortran_ = true;  }
  void interditChainesFortran () { reconnaitChainesFortran_ = false; }

  // analyse
  void reinitialise (const string& c)
  { chaine_ = c; redemarre (); }

  void reinitialise (const char *c)
  { chaine_ = c; redemarre (); }

  void reinitialise (const char *c, int longueur)
  { chaine_ = string (c, longueur); redemarre (); }

  void redemarre    ();

  int suivant       ();
  int precedent     ();

  int etatCourant   () const { return index_; }
  int retourneAEtat (int etat);

  // accès aux éléments internes
  const string& chaine        () const { return chaine_;                }
  const string& lexeme        () const { return dernierLexeme_;         }
  int           debutLexeme   () const { return debut_
                                                    - chaine_.c_str (); }
  int           apresLexeme   () const { return mobile_
                                                    - chaine_.c_str (); }
  int           type          () const { return dernierType_;           }
  int           entier        () const { return dernierEntier_;         }
  double        reel          () const { return dernierReel_;           }
  const string& nom           () const { return dernierNom_;            }
  const string& chaineC       () const { return derniereChaineC_;       }
  const string& chaineFortran () const { return derniereChaineFortran_; }
  char          separateur    () const { return dernierSeparateur_;     }
  char          parenthese    () const { return derniereParenthese_;    }
  char          operateur     () const { return dernierOperateur_;      }

private :

  string       chaine_;
  const char  *debut_;
  const char  *mobile_;
  int          index_;

  string       blancs_;
  string       separateurs_;
  string       operateurs_;

  bool         reconnaitReels_;
  bool         reconnaitReelsFortran_;
  bool         reconnaitChainesC_;
  bool         reconnaitChainesFortran_;

  string       dernierLexeme_;
  int          dernierType_;
  int          dernierEntier_;
  double       dernierReel_;
  string       dernierNom_;
  string       derniereChaineC_;
  string       derniereChaineFortran_;
  char         dernierSeparateur_;
  char         derniereParenthese_;
  char         dernierOperateur_;

  void analyseReelOuEntier  ();
  void analyseEntier        ();
  void analyseChaineC       ();
  void analyseChaineFortran ();

};

#endif
