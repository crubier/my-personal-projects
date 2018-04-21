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
//       Cantor
//
//$Nom
//>       CantorErreurs.cpp
//
//$Resume
//       fichier d'implantation de la classe CantorErreurs
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       inline const char* trad()      
//>       static void InitDomaineCantor()
//>       class CantorErreurs            
//>         formate()                    
//>         CantorErreurs()              
//>         operator =()                 
//>         erreur()                     
//
//$Historique
//       $Log: CantorErreurs.cpp,v $
//       Revision 2.24  2005/03/04 13:41:15  chope
//       correction d'un partage de données erroné entrainant un affichage intempestif
//
//       Revision 2.23  2003/07/17 12:39:59  cantor
//       Mise a jour suite aux patchs du 17/07/003
//
//       Revision 2.22  2003/02/04 09:26:09  cantor
//       DM-ID 17 Mise à jour du nom du fichier dans le bandeau suite à la modification des extensions.
//
//       Revision 2.21  2002/12/10 16:19:16  cantor
//       DM-ID 12 Correction d'un défaut d'initialisation de chaine
//
//       Revision 2.20  2002/09/03 15:01:48  cantor
//       ajout de l'erreur alignement_axe_extremite (FA15)
//
//       Revision 2.19  2002/09/02 09:18:51  cantor
//       ajout de l'erreur desequilibre_connexions
//
//       Revision 2.18  2002/02/04 09:19:29  cantor
//       ajout de l'erreur singularite_angle
//
//       Revision 2.18  2002/01/18 15:48:06  cantor
//       ajout de l'erreur singularite_angle
//
//       Revision 2.17  2001/06/05 15:48:06  cantor
//       ajout des erreurs ordre_inconnu, matrice_singuliere,
//       echec_heuristique, frontiere_ouverte et erreur_interne
//
//       Revision 2.16  2000/10/24 16:25:23  cantor
//       modification des includes pour permettre la compilation avec le
//       compilateur Sun Workshop 5.0
//
//       Revision 2.15  2000/09/11 13:39:01  cantor
//       La méthode formate de CantorErreurs retourne un string STL au lieu d'une
//       ChaineSimple conformément à l'évolution réalisée sur la classe
//       BaseErreurs de CLUB.
//
//       Revision 2.14  2000/08/09 14:36:41  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 2.13.2.1  2000/03/30 15:36:05  cantor
//       ajout du copyright CNES
//
//       Revision 2.13  1999/08/13 11:33:18  cantor
//       utilisation de stockeCode() à la place de l'affectation
//       pour donner une valeur au code d'erreur (qui est une donnée
//       partagée)
//
//       Revision 2.12  1998/10/05 11:32:36  cantor
//       inclusion de stdlib.h pour avoir le prototype de exit
//
//       Revision 2.11  1998/07/29 11:25:03  cantor
//       utilisation de CantorConfig.h et des macros
//       générées par configure
//
//       Revision 2.10  1998/07/24 14:08:50  luc
//       ajout de l'erreur repere_indirect
//
//       Revision 2.9  1998/06/24 10:07:45  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 2.8  1998/04/26 18:40:56  luc
//       déplacement de Champ vers la bibliothèque marmottes
//
//       Revision 2.7  1998/04/19 18:24:44  luc
//       élimination du code d'erreur inversion
//       reformulation de certains messages
//
//       Revision 2.6  1998/01/22 10:26:02  luc
//       inversion de la macro-définition sur les exceptions
//       (désormais active par défaut)
//       ajout de commentaires
//
//       Revision 2.5  1997/07/06 10:19:02  luc
//       ajout d'un en-tête de fichier
//       ajout d'une erreur pour les points triples des frontières de champ
//
//       Revision 2.4  1997/04/03 19:29:24  luc
//       inversion des codes de retour, 0 signifie désormais : pas d'erreur
//       
//       Revision 2.3  1997/03/26 06:58:49  luc
//       changement du type de retour de la méthode formate
//       (const char *  -->  const ChaineSimple&)
//       changement des conventions de nommage
//       
//       Revision 2.2  1997/03/25 10:20:48  luc
//       correction d'un bug de passage d'arguments variables
//       prise en compte du renommage de util_c++ en club
//       passage de SCCS à RCS
//       
//       Revision 2.1  1996/07/16 09:42:50  luc
//       élimination de la dépendance aux tools.h++ (Rogue Wave)
//       ajout des erreurs liés à l'approximation fonctionnelle
//       
//       Revision 1.5  1995/04/12 12:59:22  mercator
//       modification du comportement par defaut sans gestion d'erreur: arret
//       correction d'une erreur de classe de declaration (oubli d'un static)
//       
//       Revision 1.4  1995/01/03 08:17:14  mercator
//       remplacement des variables globales de traduction par des fonctions globales
//       
//       Revision 1.3  1994/11/26 15:22:02  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.2  1994/11/09 16:04:02  mercator
//       remplacement de la fonction "lance" par "erreur"
//       
//       Revision 1.1  1994/08/10 14:38:15  mercator
//       Initial revision
//
//$Version
//       $Id: CantorErreurs.cpp,v 2.24 2005/03/04 13:41:15 chope Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <CantorConfigNoInstall.h>

#if STDC_HEADERS
# include <cstdlib>
# include <cstdio>
#endif

#ifdef HAVE_CSTDARG
# include <cstdarg>
#endif

#include "club/Traducteur.h"
#include "cantor/CantorErreurs.h"


inline const char* trad (const char* s)
{ return TraduitFormatCVersExterne (s); }

static void InitDomaineCantor ()
{ // initialisation des domaines de traduction pour la bibliothèque cantor
  static int dejaInitialise = 0;

  if (!dejaInitialise)
  { // le mécanisme de traduction n'est qu'un "plus" qui peut travailler
    // sans le fichier de ressource (les messages sont alors ceux du code),
    // on ignore donc ici l'erreur d'accès au domaine de traduction
    CantorErreurs e;
    (void) AjouterDomaine (e.domaine ());
    e.correction ();

    dejaInitialise = 1;

  }

}

static void appliqueFormat (const string& format, string *ptrDst ...)
{
  va_list ap;
  va_start(ap, ptrDst);
  FormatC f (format);
  ap = f.applique (ap, ptrDst);
  va_end(ap);
}

const string& CantorErreurs::formate (int code, va_list ap) const
{ char*      chaine_1 = NULL;
  int        entier_1;
  int        entier_2;
  int        entier_3;

  // les messages d'erreurs utilisent le domaine de traduction "cantor"
  InitDomaineCantor ();

  // buffer de formatage du message
  static string *tampon = 0;
  if (tampon == 0)
  { // c'est la première fois que l'on passe ici
    // on alloue le tampon une fois pour toutes
    // (si le programme principal n'est pas un C++, les objets statiques
    //  ne sont pas alloués dès l'initialisation ...)
    tampon = new string;
  }

  // écriture dans un tampon de taille supposée suffisante
  char temp[4096];

  // formatage du message
  switch (code)
  { case norme_nulle :
      return BaseErreurs::formate ("norme d'un vecteur nulle", ap);
      break;

    case axe_rotation_nul :
      return BaseErreurs::formate ("axe d'une rotation nul", ap);
      break;

    case ordre_inconnu :
      entier_1 = va_arg(ap, int);
      appliqueFormat (trad ("ordre de rotations elementaires inconnu : %d\nordres connus :"),
                      tampon, entier_1);
      do
      {
        chaine_1 = va_arg(ap, char *);
      
        if (chaine_1 != 0)
        {
          *tampon += ' ';
          *tampon += TraduitVersExterne (chaine_1);
        }
      
      } while (chaine_1 != 0);
      break;

    case matrice_non_orthogonalisable :
      return BaseErreurs::formate ("matrice non orthogonalisable", ap);
      break;

    case matrice_singuliere :
      return BaseErreurs::formate ("matrice singuliere", ap);
      break;

    case repere_indirect :
      return BaseErreurs::formate ("impossible de creer une rotation"
                                   " donnant un repere indirect", ap);
      break;

    case alignement_axe_extremite :
      return BaseErreurs::formate ("extremite d'un arc alignee avec l'axe",
                                   ap);
      break;

    case cones_coaxiaux :
      return BaseErreurs::formate ("cones coaxiaux", ap);
      break;

    case cones_disjoints :
      return BaseErreurs::formate ("cones disjoints", ap);
      break;

    case creneau_vide :
      return BaseErreurs::formate ("ensemble vide d'intervalles", ap);
      break;

    case indice_hors_bornes :
      chaine_1 = va_arg(ap, char *);
      entier_1 = va_arg(ap, int);
      entier_2 = va_arg(ap, int);
      entier_3 = va_arg(ap, int);
      (void) sprintf (temp, trad ("indice \"%s\" = %d, hors bornes [%d; %d]"),
                      TraduitVersExterne (chaine_1),
                      entier_1, entier_2, entier_3);
      *tampon = temp;
      break;

    case polynome_invalide :
      return BaseErreurs::formate ("operation sur un polynome invalide", ap);
      break;

    case aucune_fonction_base :
      return BaseErreurs::formate ("pas de base de fonctions d'approximation",
                                   ap);
      break;

    case erreur_fonction_base :
      return BaseErreurs::formate ("erreur %d dans les fonctions de base"
                                   " de l'approximation", ap);
      break;

    case ajuste_dimension_nulle :
      return BaseErreurs::formate ("dimension de l'espace d'approximation"
                                   " nulle", ap);
      break;

    case non_ajustable :
      return BaseErreurs::formate ("ajustement des moindres carres impossible"
                                   " (matrice singuliere)",
                                   ap);
      break;

    case non_ajustee :
      return BaseErreurs::formate ("ajustement du filtre des moindres carres"
                                   " non effectue", ap);
      break;

    case echec_heuristique :
      return BaseErreurs::formate ("cas non implante\n"
                                   "veuillez contacter la maintenance"
                                   " de CANTOR", ap);
      break;

    case frontiere_ouverte :
      return BaseErreurs::formate ("frontiere de champ ouverte", ap);
      break;

    case desequilibre_connexions :
      return BaseErreurs::formate ("connexions entrantes et sortantes d'un"
                                   " noeud non equilibrees", ap);
      break;

    case erreur_interne :
      return BaseErreurs::formate ("erreur interne de CANTOR,"
                                   " veuillez contacter la maintenance"
                                   " (ligne %d, fichier %s)", ap);
      break;
    case singularite_angle :
      return BaseErreurs::formate ("singularite au niveau du calcul"
                                   " des angle de rotation", ap);
      break;

    default :
      return BaseErreurs::formate (code, ap);
      break;

  }

  // retour du message formaté
  return *tampon;

}

CantorErreurs::CantorErreurs (int code ...)
  : BaseErreurs ()
{ va_list    ap;

  // initialisation du traitement des arguments variables
  va_start(ap, code);

  // sauvegarde du code d'erreur dans la partie privée de la classe
  stockeCode (code);

  // formatage et stockage du message
  stockeMessage (formate (code, ap));

  // fin de récupération des arguments d'appel
  va_end(ap);

}

CantorErreurs::CantorErreurs (const char* format ...)
  : BaseErreurs ()
{ va_list    ap;

  // initialisation du traitement des arguments variables
  va_start(ap, format);

  // sauvegarde du code d'erreur dans la partie privée de la classe
  stockeCode (CodeInconnu);

  // formatage et stockage du message
  stockeMessage (BaseErreurs::formate (format, ap));

  // fin de récupération des arguments d'appel
  va_end(ap);

}

CantorErreurs& CantorErreurs::operator = (const CantorErreurs& e)
{ if (this != &e)     // protection contre x = x
  { 
    BaseErreurs::operator = (e);
  }

  return *this;

}

int CantorErreurs::erreur (CantorErreurs* ptr, int code ...)
{ va_list    ap;

  // initialisation du traitement des arguments variables
  va_start(ap, code);

  // gestion de l'erreur sans argument variable
  if (ptr != 0)
  { // l'appelant a donné une instance d'erreur à remplir
    ptr->stockeCode (code);
    ptr->stockeMessage (ptr->formate (code, ap));
  }
  else
  { // l'appelant n'a pas donné d'instance, il faut la créer
   CantorErreurs err;
    err.stockeCode (code);
    err.stockeMessage (err.formate (code, ap));

    if (BaseErreurs::exceptions ())
#ifdef HAVE_EXCEPTIONS
      throw err;
#else
    { // l'utilisateur veut des exceptions, mais le code est compilé sans
      err.affiche    ();
      err.correction ();
      exit (1);
    }
#endif
    else
    { err.affiche    ();
      err.correction ();
      exit (1);
    }
  }

  // fin de récupération des arguments d'appel
  va_end(ap);

  // retour avec un code d'erreur à la fonction appelante
  return code;

}

int CantorErreurs::erreur (CantorErreurs* ptr, const char* format ...)
{ va_list    ap;

  // initialisation du traitement des arguments variables
  va_start(ap, format);

  // gestion de l'erreur sans argument variable
  if (ptr != 0)
  { // l'appelant a donné une instance d'erreur à remplir
    ptr->stockeCode (CodeInconnu);
    ptr->stockeMessage (ptr->BaseErreurs::formate (format, ap));
  }
  else
  { // l'appelant n'a pas donné d'instance, il faut la créer
    CantorErreurs err;
    err.stockeCode (CodeInconnu);
    err.stockeMessage (err.BaseErreurs::formate (format, ap));

    if (BaseErreurs::exceptions ())
#ifdef HAVE_EXCEPTIONS
      throw err;
#else
    { // l'utilisateur veut des exceptions, mais le code est compilé sans
      err.affiche    ();
      err.correction ();
      exit (1);
    }
#endif
    else
    { err.affiche    ();
      err.correction ();
      exit (1);
    }

  }

  // fin de récupération des arguments d'appel
  va_end(ap);

  // retour avec un code d'erreur à la fonction appelante
  return CodeInconnu;

}
