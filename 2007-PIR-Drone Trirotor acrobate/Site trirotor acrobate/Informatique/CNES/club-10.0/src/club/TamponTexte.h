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
//>       TamponTexte.h
//$Resume
//       fichier d'en-tête de la classe TamponTexte
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class TamponTexte            
//>       inline ostream& operator <<()
//$Historique
//       $Log: TamponTexte.h,v $
//       Revision 3.15  2003/10/22 12:54:39  club
//       DM 0029
//
//       Revision 3.14  2000/10/25 09:31:44  club
//       modification des include du standard C++ : suppression de ".h" dans le nom
//       du fichier inclus.
//
//       Revision 3.13  2000/09/07 07:42:15  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//
//       Revision 3.12  2000/07/03 08:53:50  club
//       Ajout du copyright CNES
//
//       Revision 3.11.2.1  2000/03/30 14:46:59  club
//       ajout du copyright CNES
//
//       Revision 3.11  1999/07/06 15:24:17  club
//       Changement des signatures pour gestion des erreurs
//       par mécanisme d'exception
//
//       Revision 3.10  1999/03/15 15:09:18  club
//       modification totale de TamponTexte, qui repose sur la hiérarchie de TamponAscii
//       et des itérateurs, sans changement de l'interface utilisateur
//       TamponTexte bloquent les exceptions des objets utilisés et conserve en
//       interface le système d'erreur ClubErreur
//
//       Revision 3.9  1998/07/27 10:14:14  club
//       passage à une configuration de type GNU (fichier ClubConfig.h généré)
//
//       Revision 3.8  1998/06/25 06:48:33  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//       élimination de la méthode estValide
//
//       Revision 3.7  1998/04/26 13:02:48  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 3.6  1998/01/22 08:30:24  luc
//       amélioration de l'en-tête de classe
//
//       Revision 3.5  1997/08/24 13:37:40  luc
//       reconnaissance des chaînes de caractères du fortran
//       utilisation de la classe AnalyseurLexical
//       traitement en bloc des commentaires
//       dans le cas de l'interprétation des guillemets
//       (sinon, on confond les apostrophes dans les commentaires
//       avec les spécificateurs de chaînes fortran)
//
//       Revision 3.4  1997/08/21 16:36:28  luc
//       ajout d'un en-tête de fichier
//
//       Revision 3.3  1997/04/03 12:50:54  luc
//       inversion des codes de retour, 0 signifie désormais : pas d'erreur
//       
//       Revision 3.2  1997/03/25 15:03:48  luc
//       changement des règles de nommage
//       
//       Revision 3.1  1997/03/19 14:50:50  luc
//       utilisation de la classe ChaineSimple
//       renommage de la bibliothèque util_c++ en club
//       passage de SCCS à RCS
//       
//       Revision 2.1  1996/07/15 17:30:47  luc
//       élimination de la dépendance au tools.h++ (Rogue Wave)
//       prise en compte du renommage de erreurs.h en util_erreurs.h
//       
//       Revision 1.8  1995/07/12 14:58:06  mercator
//       ajout de signatures pour aider le compilateur SUN a comprendre ...
//       
//       Revision 1.7  1995/07/07 14:02:51  mercator
//       transformation de toutes les fonctions de lecture en fonctions "const"
//       (on estime licite de modifier des attributs d'optimisation invisibles
//       de l'exterieur dans des fonctions "const")
//       
//       Revision 1.6  1994/12/13 07:55:20  mercator
//       ajout d'une interface en FILE* a la construction et a la lecture
//       
//       Revision 1.5  1994/12/09 13:54:59  mercator
//       ajout d'une possibilite de mettre hors-circuit l'interpretation des '"'
//       
//       Revision 1.4  1994/11/09 15:00:45  mercator
//       elimination des directives #pragma
//       
//       Revision 1.3  1994/09/30 07:17:20  mercator
//       transformation des routines d'insertion dans les lignes
//       ajout de tests de validite des numeros de champs et lignes
//       elimination de tests redondants entre appelants et appeles
//       
//       Revision 1.2  1994/09/28 16:17:51  mercator
//       ajout d'une possibilite de personnalisation des separateurs
//       ajout de pointeurs d'erreur optionnels dans les signatures des methodes
//       
//       Revision 1.1  1994/07/27 11:55:30  luc
//       Initial revision
//
//$Version
//       $Id: TamponTexte.h,v 3.15 2003/10/22 12:54:39 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef club_TamponTexte_h
#define club_TamponTexte_h

#include <iostream>
#include <fstream>

#include "club/ClubErreurs.h"
#include "club/TamponAscii.h"
#include "club/IterateurCaractere.h"
#include "club/IterateurChamp.h"
#include "club/IterateurLigne.h"
#include "club/IterateurChampLigne.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class TamponTexte
//$Resume
//       classe de gestion de texte en mémoire (image d'un fichier ou non)
//
//$Description
//       accès aux éléments internes (lignes, champs) d'un texte
//       pouvant comporter des lignes blanches, des commentaires, des
//       chaînes de caractères comportant des caractères blancs ou
//       spéciaux du langage C (\n, \012, ...)  (les caractères -ou le
//       champ complet- sont alors inclus entre '"')
//
//$Usage
//>     construction : 
//          sans argument, ou à partir d'un fichier, ou du nom du
//          fichier, par copie, avec éventuelle suppression de
//          l'interprétation des commentaires
//>     utilisation  : 
//>       TamponTexte& operator =              () 
//          affectation
//>       void lit                             () 2 signatures - 
//          relit le fichier donné en argument. Si le nom est vide
//          (c'est la valeur par défaut) utilise le nom conservé dans
//          l'instance.
//>       void ecrit                           () 
//          stocke dans le fichier dont le nom est donné en
//          argument. Si ce nom est vide (c'est la valeur par defaut)
//          utilise le nom conservé dans l'instance. 
//>       void elimineCommentaires             () 
//          élimine les caractères qui vont d'un caractère marqueur de
//          commentaire à la fin de la ligne (sauf si le marqueur est
//          dans une chaîne entre '"'). 
//>       void elimineBlancs                   () 
//          élimine les caractères blancs de début et de fin de ligne
//          (pour une ligne entièrement blanche, le '\n' est également
//          éliminé). 
//>       void initCarCommentaires            () 
//          utilise les caractères de str comme marqueurs de
//          commentaires. Si str est la chaîne vide ou le pointeur
//          nul, cette fonction réinitialise à la valeur par défaut
//          qui est "#".
//>       void ajouteCarCommentaires          () 
//          ajoute les caractères de str à la liste des caractères
//          marqueurs de commentaires.
//>       const string& carCommentaires       () 
//          retourne la liste des caractères marqueurs de
//          commentaires.
//>       void initSeparateurs                () 
//          utilise les caractères de str comme caractères séparateurs
//          de champs. Si str est la chaîne vide ou le pointeur nul,
//          cette fonction réinitialise à la valeur par défaut qui est
//          "\t\n\v\f\r ".
//>       void ajouteSeparateurs              () 
//          ajoute les caractères de str à la liste des caractères
//          séparateurs.
//>       const string& separateurs           () 
//          retourne la liste des caractères séparateurs.
//>       const char* nom                     () 
//          retourne le nom du fichier
//>       int estVide                         () 
//          teste si l'instance est vide
//>       const char* total                   () 
//          retourne un pointeur sur le tampon constant contenant les
//          données (totalité du fichier)
//>       int longueur                        () 
//          retourne la longueur du tampon (sans le '\0' final)
//>       int insereAAdresse                  () 
//          insere la chaine pointee par p a l'adresse donnee par ad
//          (si ad est avant le debut, on insere au debut, si ad est
//          apres la fin, on ajoute a la fin).
//>       int insereAuDebut                   () 
//          insere la chaîne pointée par p avant le début du
//          fichier. 
//>       void ajouteALaFin                    () 
//          ajoute la chaîne pointée par p après la fin du
//          fichier. 
//>       void elimineZone                     () 
//          elimine la zone s'etendant de l'adresse d a l'adresse f.
//>       void elimineTout                     () 
//          vide le tampon complet. 
//>       void remplaceTout                    ()
//          remplace le tampon complet par la chaine pointee par p.
//>       int nombreLignes                    () 
//          retourne le nombre de lignes, ou -1 en cas de problème.
//>       const char* ligne                   () 
//          retourne la ligne numéro l du fichier (lignes numérotées a
//          partir de 1)
//>       void insereDebutLigne                () 
//          insère une chaîne en début de ligne l. 
//>       void insereFinLigne                  () 
//          insère une chaîne en fin de ligne l. 
//>       void elimineLigne                    () 
//          élimine la ligne l. 
//>       void remplaceLigne                   () 
//          remplace la ligne l par la chaîne pointée
//          (les séparateurs de champ sont gérés par l'instance,
//          il est inutile de les mettre dans p). 
//>       int nombreChampsLigne               () 
//          retourne le nombre de champs de la ligne numéro l, ou -1
//          en cas de problème (lignes numérotées à partir de 1)
//>       const char* champLigne              () 
//          retourne le champ numéro c de la ligne numéro l (lignes
//          numérotées à partir de 1, champs numérotés à partir de 1)
//>       void insereAvantChampLigne           () 
//          insère la chaîne pointée par p avant le champ c de la
//          ligne l.
//>       void ajouteApresChampLigne           () 
//          ajoute la chaîne pointée par p après le champ c de la
//          ligne l. 
//>       void elimineChampLigne               () 
//          élimine le champ c de la ligne l. 
//>       void remplaceChampLigne              () 
//          remplace le champ c de la ligne l par la chaîne pointée
//          par p (les séparateurs de champ sont gérés par l'instance,
//          il est inutile de les mettre dans p). 
//>       int nombreChamps                    () 
//          retourne le nombre de champs total du fichier, ou -1 en
//          cas de problème.
//>       const char* champ                   () 
//          retourne le champ numéro c du fichier (champs numérotés a
//          partir de 1)
//>       void insereAvantChamp                () 
//          insère la chaîne pointée par p avant le champ c. 
//>       void ajouteApresChamp                () 
//          ajoute la chaîne pointée par p après le champ c. 
//>       void elimineChamp                    () 
//          élimine le champ c (ne fait rien si c n'est pas
//          valide). 
//>       void remplaceChamp                   () 
//          remplace le champ c par la chaîne pointée par p (les
//          séparateurs de champ existants sont conservés,il est
//          inutile de les mettre dans p).
//$Auteur
//       L. Maisonobe CNES
//       M. Julien    CSSI
//       P-A. Cros    CSSI
//       G. Lajon     CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class TamponTexte
{ 
public :

  // constructeurs
  TamponTexte (int interprete = 1) throw(ClubErreurs) : tampon_ (0)  
    {tampon_ = new TamponAscii( interprete );
    parcoursCaractere_ = new IterateurCaractere(tampon_);
    parcoursChamp_ = new IterateurChamp(tampon_,0);
    parcoursLigne_ = new IterateurLigne(tampon_,0);
    parcoursChampLigne_ = new IterateurChampLigne(tampon_,0);
    }


  TamponTexte (FILE* ptrFic,  int interprete = 1)
    throw(ClubErreurs);
  TamponTexte (const char* nom, int interprete = 1)
    throw(ClubErreurs);

  // constructeur par copie et affectation
  TamponTexte             (const TamponTexte& t)
    throw(ClubErreurs);

  TamponTexte& operator = (const TamponTexte& t)
    throw(ClubErreurs);
  
  // destructeur
  ~TamponTexte ()
    throw();

  // relecture d'un fichier
  void        lit                   (FILE* ptrFic, int interprete = 1) 
    throw(ClubErreurs);
  void        lit                   (const char* nom = 0, int interprete = 1) 
    throw(ClubErreurs);
  // sauvegarde dans un fichier
  void        ecrit                 (const char* nom = 0) const 
    throw(ClubErreurs);

  // fonctions de filtrage
  void          elimineCommentaires   () throw(ClubErreurs);
  void          elimineBlancs         () throw(ClubErreurs);
  void          initCarCommentaires   (const char* chaine) throw();
  void          ajouteCarCommentaires (const char* chaine) throw();
  const string& carCommentaires       () const throw();

  void          initSeparateurs       (const char* chaine) throw();
  void          ajouteSeparateurs     (const char* chaine) throw();
  const string& separateurs           () const throw();


  // routines d'accès globales
  const char* nom                   () const throw();
  int         estVide               () const throw();
  const char* total                 () const throw();
  int         longueur              () const throw();

  void        insereAAdresse        (const char* adresse, const char* chaine)
    throw(ClubErreurs);
  void        insereAuDebut         (const char* chaine) throw (ClubErreurs)
    { insereAAdresse (total(), chaine); }

  void        ajouteALaFin          (const char* chaine)
    throw(ClubErreurs);
  void        elimineZone           (char* debut, char* fin)
    throw(ClubErreurs);
  void        elimineTout           ()
    throw(ClubErreurs)
    { elimineZone ((char *)total(), (char *)total() + longueur() - 1); }

  void        remplaceTout          (const char* chaine)
    throw(ClubErreurs);

  // routines d'accès par lignes
  int         nombreLignes          () const throw(ClubErreurs);
  const char* ligne                 (int l) const
    throw(ClubErreurs);
  void        insereDebutLigne      (int l, const char* chaine)
    throw(ClubErreurs);
  void        insereFinLigne        (int l, const char* chaine)
    throw(ClubErreurs);
  void        elimineLigne          (int l)
    throw(ClubErreurs);
  void        remplaceLigne         (int l, const char* chaine)
    throw(ClubErreurs);

  // routines d'accès par champs dans les lignes
  int         nombreChampsLigne     (int l) const
    throw(ClubErreurs);
  const char* champLigne            (int c, int l) const
    throw(ClubErreurs);
  void        insereAvantChampLigne (int c, int l, const char* chaine)
    throw(ClubErreurs);
  void        ajouteApresChampLigne (int c, int l, const char* chaine)
    throw(ClubErreurs);
  void        elimineChampLigne     (int c, int l)
    throw(ClubErreurs);
  void        remplaceChampLigne    (int c, int l, const char* chaine)
    throw(ClubErreurs);

  // routines d'accès par champs dans l'ensemble du fichier
  int         nombreChamps          () const throw();
  const char* champ                 (int c) const
    throw(ClubErreurs);
  void        insereAvantChamp      (int c, const char* chaine)
    throw(ClubErreurs);
  void        ajouteApresChamp      (int c, const char* chaine)
    throw(ClubErreurs);
  void        elimineChamp          (int c)
    throw(ClubErreurs);
  void        remplaceChamp         (int c, const char* chaine)
    throw(ClubErreurs);
  const TamponAscii* getTampon      ();

protected :
  TamponAscii         *tampon_;
  IterateurCaractere  *parcoursCaractere_;
  IterateurChamp      *parcoursChamp_;
  IterateurLigne      *parcoursLigne_;
  IterateurChampLigne *parcoursChampLigne_;

private :

  void actualiseIterateurs();

};

inline ostream& operator << (ostream& s, TamponTexte& t)
{return s << t.getTampon(); }

#endif
