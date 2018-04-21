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
//>       OptionsAppli.h
//
//$Resume
//       fichier d'en-tête de la classe OptionsAppli
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class OptionsAppli
//
//$Historique
//       $Log: OptionsAppli.h,v $
//       Revision 3.17  2002/12/09 15:57:52  club
//       DM-ID 12 Mise en conformité des constructeurs/destructeurs avec la norme qualité
//
//       Revision 3.16  2001/02/16 12:28:11  club
//       remplacement de la classe hash_map par la classe standard map
//
//       Revision 3.15  2000/10/25 09:31:43  club
//       modification des include du standard C++ : suppression de ".h" dans le nom
//       du fichier inclus.
//
//       Revision 3.14  2000/10/24 14:18:15  club
//       mise à jour des includes et ajout des tests de configuration.
//
//       Revision 3.13  2000/09/11 12:18:50  club
//       Mise à jour des include et suppression des tests sur variable de
//       configuration de ClubConfig.h qui n'est pas installé.
//
//       Revision 3.12  2000/09/07 07:56:49  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//
//       Revision 3.11  2000/08/30 14:15:56  club
//       utilisation de la structure de données hash_map de la stl au lieu de la
//       classe Adressage pour définir le type de l'attribut tableOptions_.
//       Ajout de l'include hash_map et string de la STL.
//       Utilisation de l'espace de nommage std.
//
//       Revision 3.10  2000/07/03 08:48:31  club
//       Ajout du copyright CNES.
//
//       Revision 3.9.2.1  2000/03/30 14:46:58  club
//       ajout du copyright CNES
//
//       Revision 3.9  1999/07/06 15:24:17  club
//       Changement des signatures pour gestion des erreurs
//       par mécanisme d'exception
//
//       Revision 3.8  1999/03/18 10:05:52  club
//       normalisation des déclarations de chaînes littérales par l'utilisation
//       de const char* au lieu de char*
//
//       Revision 3.7  1998/06/25 06:45:40  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 3.6  1998/04/26 13:02:42  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 3.5  1998/01/22 08:34:21  luc
//       amélioration de l'en-tête de classe
//
//       Revision 3.4  1997/08/21 16:36:14  luc
//       ajout d'un en-tête de fichier
//
//       Revision 3.3  1997/04/03 12:50:47  luc
//       inversion des codes de retour, 0 signifie désormais : pas d'erreur
//       
//       Revision 3.2  1997/03/25 15:01:13  luc
//       changement des règles de nommage
//       
//       Revision 3.1  1997/03/19 14:47:11  luc
//       utilisation de la classe ChaineSimple
//       renommage de la bibliothèque util_c++ en club
//       passage de SCCS à RCS
//       
//       Revision 2.1  1996/07/15 17:20:09  luc
//       élimination de la dépendance au tools.h++ (Rogue Wave)
//       prise en compte du renommage de erreurs.h en util_erreurs.h
//       correction d'orthographe dans les noms de fonctions (occurence -> occurrence)
//       utilisation d'une valeur de retour entière et d'un UtilErreurs *ptrErreur
//       pour les fonctions pouvant générer des erreurs
//       
//       Revision 1.4  1994/11/09 15:00:34  mercator
//       elimination des directives #pragma
//       
//       Revision 1.3  1994/08/23 14:07:21  mercator
//       ajout de signatures en const char* pour garantir la duree
//       de vie d'une variable utilisee en RWCString& (non constante)
//       
//       Revision 1.2  1994/08/12 06:58:56  mercator
//       ajout de signatures en const char* pour garantir la duree
//       de vie d'une variable utilisee en RWCString& (non constante)
//       
//       Revision 1.1  1994/07/27 11:55:38  luc
//       Initial revision
//
//$Version
//       $Id: OptionsAppli.h,v 3.17 2002/12/09 15:57:52 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       G. Lajon     CSSI
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __club_OptionsAppli_h
#define __club_OptionsAppli_h

#include <club/ClubConfig.h>

#if CLUB_HAVE_NAMESPACES
using namespace std;
#endif

# include <map>
# include <string>

#include "club/OptionEntier.h"
#include "club/OptionTableauEntiers.h"
#include "club/OptionReel.h"
#include "club/OptionTableauReels.h"
#include "club/OptionChaine.h"
#include "club/OptionTableauChaines.h"
#include "club/OptionSansValeur.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class OptionsAppli
//
//$Resume
//       classe regroupant l'ensembles des options d'une application
//
//$Description
//       gestion des options de la ligne de commande de l'application
//
//$Usage
//>     construction : 
//          à partir du nom de l'application (souvent argv [0])
//>     utilisation  : 
//>       OptionsAppli& operator = () 
//          affectation
//>       void ajouterOption        () 
//          ajoute une copie de l'option à la liste des options pouvant
//          être reconnues par l'analyseur (on ne peut ajouter des
//          options que tant que l'analyseur n'a pas été initialisé).
//>       void initialiser          () 
//          interprète les arguments pour initialiser les paramètres
//          des options passées.  une fois cette méthode
//          exécutée, l'ajout d'options dans l'analyseur ou une
//          nouvelle initialisation sont interdits.
//>       const char *usage        () 
//          retourne un message indiquant les arguments reconnus.
//>       int verifier             () 
//          effectue les vérifications propres à chaque option (espace
//          de validité, présence obligatoire, ...), retourne un code
//          d'erreur en cas de problème
//>       void argvReste            () 
//          initialise le tableau argv avec les arguments non reconnus
//          dans la ligne de commande, ce qui permet un traitement des
//          options en plusieurs passes, pour les bibliothèques de
//          base, les bibliothèques thématiques, les applications. (le
//          tableau argv doit avoir une taille au moins égale à la
//          valeur retournée par argcReste (). Les pointeurs du tableau
//          correspondent a des chaînes allouées avec l'opérateur new
//          [], la libération de la mémoire est à la charge de
//          l'appelant) 
//>       void garantirComplet      () 
//          effectue la vérification complète (appel à la méthode
//          verifier) et teste s'il reste des arguments non reconnus
//          (méthode argvReste). 
//>       int occurrencesPassees    () 
//          retourne le nombre d'occurrences de l'option qui ont été
//          passées. Retourne un code d'erreur négatif en cas de
//          problème
//>       void lireValeur           () 
//          met à l'adresse fournie la valeur de l'option identifiée
//          par son code. 
//>       const string& nom         () 
//          retourne le nom de l'application.
//>       int argcReste             () 
//          retourne le nombre d'arguments restant après analyse plus
//          1 (le argv[0] est toujours compté). Si cette taille est
//          strictement supérieure a 1, il reste des des arguments non
//          reconnus dans la ligne. la taille retournée est toujours
//          inférieure ou égale au argc donné en argument à la méthode
//          initialiser.
//>       int estInitialise         () 
//          teste si les arguments ont été initialisés.
//
//$Auteur
//       L. Maisonobe CNES
//       G. Lajon     CSSI
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class OptionsAppli
{ 
public :

  // constructeurs
  OptionsAppli (const char *nom)
    : tableOptions_ (), nom_ (nom),
      nombreNonReconnus_ (0), argumentsNonReconnus_ (0), initialise_ (0)
  {}

  OptionsAppli (const string& nom)
    : tableOptions_ (), nom_ (nom),
      nombreNonReconnus_ (0), argumentsNonReconnus_ (0), initialise_ (0)
  {}

  // copie constructeur et affectation
  OptionsAppli             (const OptionsAppli& opts);
  OptionsAppli& operator = (const OptionsAppli& opts);

  // destructeur
 ~OptionsAppli ();

  // fonctions de mise à jour
  void      ajouterOption      (const OptionEntier&         option)
    throw (ClubErreurs);
  void      ajouterOption      (const OptionTableauEntiers& option)
    throw (ClubErreurs);
  void      ajouterOption      (const OptionReel&           option)
    throw (ClubErreurs);
  void      ajouterOption      (const OptionTableauReels&   option)
    throw (ClubErreurs);
  void      ajouterOption      (const OptionChaine&         option)
    throw (ClubErreurs);
  void      ajouterOption      (const OptionTableauChaines& option)
    throw (ClubErreurs);
  void      ajouterOption      (const OptionSansValeur&     option)
    throw (ClubErreurs);

  void      initialiser        (int  argc, const char *const argv [])
    throw (ClubErreurs);

  // fonctions d'accès générales
  const string& nom              () const { return nom_; }
  const char   *usage            (unsigned int largeur = 80) const;
  int           verifier         (string *ptrMessage) const;
  int           argcReste        () const { return nombreNonReconnus_; }
  void          argvReste        (char** argv)
    throw (ClubErreurs);
  void                garantirComplet  () const
    throw (ClubErreurs);

  // fonctions d'accès aux options individuelles
  int       occurrencesPassees (const char *code) const
    throw (ClubErreurs);

  int       estInitialise      () const { return initialise_; }

  void      lireValeur         (const char *code, int          *dest,
                                int         occurrence = 1) const
    throw (ClubErreurs);
  void      lireValeur         (const char *code, double       *dest,
                                int         occurrence = 1) const
    throw (ClubErreurs);

  void      lireValeur         (const char *code, char         *dest,
                                int         occurrence = 1) const
    throw (ClubErreurs);

  void      lireValeur         (const char *code, string *dest,
                                int         occurrence = 1) const
    throw (ClubErreurs);

  void      lireValeur         (const char *code,
                                int         nombre, int          dest [],
                                int         occurrence = 1) const
    throw (ClubErreurs);

  void      lireValeur         (const char *code,
                                int         nombre, double       dest [],
                                int         occurrence = 1) const
    throw (ClubErreurs);

  void      lireValeur         (const char *code,
                                int         nombre, char*        dest [],
                                int         occurrence = 1) const
    throw (ClubErreurs);

  void      lireValeur         (const char *code,
                                int         nombre, string dest [],
                                int         occurrence = 1) const
    throw (ClubErreurs);

private:
  map<string, OptionBase *> tableOptions_;
  string                    nom_;
  int                       nombreNonReconnus_;
  string                   *argumentsNonReconnus_;
  int                       initialise_;

  void   ajouterNonReconnu (const char* chaine);

  // AUTRES CONSTRUCTEURS
  // Constructeur par défaut : NE DOIT JAMAIS ETRE APPELLE
  OptionsAppli () {}
    
};

#endif
