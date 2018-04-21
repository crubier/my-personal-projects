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
//>       BaseErreurs.cpp
//$Resume
//       fichier d'implantation de la classe BaseErreurs
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       static string *AlloueMessage()
//>       static void LibereMessage()         
//>       inline const char* trad()           
//>       class BaseErreurs                   
//>         formate()                         
//>         BaseErreurs()                     
//>         operator =()                      
//>         ~BaseErreurs()                    
//>         affiche()                         
//>         miseAJour()                       
//>         correspond()                      
//>         avertissement()                   
//>         erreur()                          
//$Historique
//       $Log: BaseErreurs.cpp,v $
//       Revision 3.21  2003/02/03 09:04:23  club
//       DM-ID 17 Changement de l'extension du fichier dans le bandeau
//
//       Revision 3.20  2000/10/25 09:31:42  club
//       modification des include du standard C++ : suppression de ".h" dans le nom
//       du fichier inclus.
//
//       Revision 3.19  2000/10/24 14:21:00  club
//       Remplacement de l'include ClubConfig.h par ClubConfigNoInstall.h
//
//       Revision 3.18  2000/10/24 08:33:29  club
//       modification des include standard du C : utilisation de cNAME au lieu de
//       NAME.h (pour permettre la compilation avec le Sun Workshop 5.0)
//
//       Revision 3.17  2000/09/07 08:00:49  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//       ajout de l'include stdio.h
//
//       Revision 3.16  2000/08/30 14:19:44  club
//       Ajout de l'include à limits.h (avant celui à float.h pour éviter des conflits)
//
//       Revision 3.15  2000/07/03 08:57:18  club
//       Ajout du copyright CNES
//
//       Revision 3.14.2.1  2000/03/30 14:46:46  club
//       ajout du copyright CNES
//
//       Revision 3.14  1999/08/12 13:55:10  club
//       La classe StructureErreurs devient interne à BaseErreurs
//
//       Revision 3.13  1999/08/12 09:59:57  club
//       utilisation de l'initialiseur stockeCode du code
//       d'erreur résultant de la modification de la classe
//       BaseErreurs
//
//       Revision 3.12  1999/04/12 15:08:04  club
//       ajout d'une nouvelle fonction de liberation mémoire
//
//       Revision 3.11  1999/03/15 13:11:53  club
//       modification du principe de copie ou affectation, toutes les instances
//       d'une même erreur partagent le même message par un TamponPartage
//       cette modification corrige le problème de duplication des messages lors de
//       la destruction des instances (instances créées par le lancement d'une
//       exception)
//
//       Revision 3.10  1998/11/17 11:58:53  club
//       élimination de l'inclusion de ctype.h
//
//       Revision 3.9  1998/10/05 06:59:15  club
//       inclusion de stdlib.h pour avoir le prototype de exit
//
//       Revision 3.8  1998/07/27 10:13:39  club
//       passage à une configuration de type GNU (fichier ClubConfig.h généré)
//
//       Revision 3.7  1998/06/21 16:13:54  luc
//       modification du format de l'en-tête
//       élimination de la chaîne statique RCS
//
//       Revision 3.6  1998/04/26 13:07:57  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 3.5  1998/01/22 08:12:15  luc
//       inversion de la macro-définition sur les exceptions
//       (désormais active par défaut)
//       ajout d'un else pour gérer les cas sans exceptions
//       ajout de commentaires
//
//       Revision 3.4  1997/08/21 16:43:58  luc
//       ajout d'un en-tête de fichier
//
//       Revision 3.3  1997/04/03 12:46:25  luc
//       inversion des codes de retour, 0 signifie désormais : pas d'erreur
//       
//       Revision 3.2  1997/03/25 14:57:24  luc
//       changement du type de retour des méthodes formate
//       (const char *  --> const ChaineSimple&)
//       ajout d'une signature pour la méthode protégée stockeMessage
//       changement des règles de nommage
//       
//       Revision 3.1  1997/03/25 09:46:32  luc
//       utilisation de la classe ChaineSimple
//       renommage de la bibliothèque util_c++ en club
//       passage de SCCS à RCS
//       
//       Revision 2.1  1996/07/15 17:11:15  luc
//       élimination de la dépendance au tools.h++ (Rogue Wave)
//       
//       Revision 1.9  1995/07/12 14:54:30  mercator
//       elimination du nom d'un argument inutilise pour
//       - supprimer un avertissement du compilateur SUN
//       - montrer explicitement que la variable ne sert pas ici
//       (la variable ne sert que dans les classes derivees)
//       
//       Revision 1.8  1995/01/03 07:58:40  mercator
//       remplacement des variables globales de traduction
//       par des fonctions globales
//       
//       Revision 1.7  1994/12/22 15:48:02  mercator
//       modification de la methode why () de facon a ne jamais retourner NULL
//       (on retourne une chaine vide s'il n'y a pas d'erreur)
//       
//       Revision 1.6  1994/11/09 15:01:02  mercator
//       elimination des directives #pragma
//       
//       Revision 1.5  1994/09/28 10:47:39  mercator
//       correction d'une erreur de passage d'arguments variables
//       
//       Revision 1.4  1994/09/14 08:46:58  mercator
//       elimination de la derivation a partir de RWXmsg
//       apres decouverte d'une incoherence dans les #ifdef de RogueWave
//       (signature du constructeur de RWXmsg variable)
//       
//       Revision 1.3  1994/09/09 14:10:35  mercator
//       remplacement des fonctions de lancement d'exceptions
//       par des fonctions configurables par l'utilisateur
//       
//       Revision 1.2  1994/08/10 12:19:53  mercator
//       correction d'une erreur d'utilisation d'arguments variables
//       
//       Revision 1.1  1994/07/27 12:05:47  luc
//       Initial revision
//
//$Version
//       $Id: BaseErreurs.cpp,v 3.21 2003/02/03 09:04:23 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       M. Julien    CSSI
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#if STDC_HEADERS
# include <climits>
# include <cfloat>
# include <cstdlib>
# include <cstdio>
#endif

#ifdef HAVE_CSTDARG
# include <cstdarg>
#endif

#include "club/BaseErreurs.h"
#include "club/Traducteur.h"
#include "club/TamponPartage.h"


// définition des attributs de classe
int     BaseErreurs::avertissements_                   = 0;
int     BaseErreurs::exceptions_                       = 0;
void (* BaseErreurs::fonAffiche_) (const char*, void*) = 0;
void*   BaseErreurs::argAffiche_                       = 0;


inline const char* trad (const char* s)
{ return TraduitFormatCVersExterne (s); }

const string& BaseErreurs::formate (int code, va_list) const
{ // les messages d'erreurs utilisent le domaine de traduction "club"
  InitDomaineClub ();

  // tampon de formatage du message
  static string *ptrTampon = 0;
  if (ptrTampon == 0)
    ptrTampon = new string;

  // écriture dans un tampon de taille supposée suffisante
  char temp[4096];

  // formatage du message
  (void) sprintf (temp, trad ("erreur du domaine %s numero %d non reconnue"),
                  domaine (), code);
  *ptrTampon = temp;

  // retour du message formaté
  return *ptrTampon;

}

const string& BaseErreurs::formate (const char* format, va_list ap) const
{ // les messages d'erreurs utilisent le domaine de traduction "club"
  InitDomaineClub ();

  // tampon de formatage du message
  static string *ptrTampon = 0;
  if (ptrTampon == 0)
    ptrTampon = new string;

  // écriture dans un tampon de taille supposée suffisante
  char temp[4096];

  // formatage du message
  (void) vsprintf (temp, trad (format), ap);
  *ptrTampon = temp;

  // retour du message formaté
  return *ptrTampon;

}

BaseErreurs::BaseErreurs ()
  : donneesPartagees_  (StructureErreurs::AlloueMessage (), 
                        StructureErreurs::LibereMessage, 0)
{}

BaseErreurs::BaseErreurs (int code ...)
{ va_list    ap;

  // initialisation du traitement des arguments variables
  va_start(ap, code);

  donneesPartagees_ = TamponPartage (StructureErreurs::AlloueMessage (), 
                                     StructureErreurs::LibereMessage, 0);

  // sauvegarde du code d'erreur dans la partie privée de la classe
  stockeCode (code);

  // formatage et stockage du message
  stockeMessage (formate (code, ap));

  // fin de récupération des arguments d'appel
  va_end(ap);

}

BaseErreurs::BaseErreurs (const char* format ...) 
{ va_list    ap;

  // initialisation du traitement des arguments variables
  va_start(ap, format);

  donneesPartagees_ = TamponPartage (StructureErreurs::AlloueMessage (), 
                                     StructureErreurs::LibereMessage, 0);

  // sauvegarde du code d'erreur dans la partie privée de la classe
  stockeCode (CodeInconnu);

  // formatage et stockage du message
  stockeMessage (formate (format, ap));

  // fin de récupération des arguments d'appel
  va_end(ap);

}

BaseErreurs& BaseErreurs::operator = (const BaseErreurs& e)
{ 
  if (this != &e)     // protection contre x = x
    { 
      donneesPartagees_ = TamponPartage(e.donneesPartagees_);
    }

    return *this;
}

BaseErreurs::~BaseErreurs ()
{ if ((code () != AucuneErreur) && (donneesPartagees_.references() == 1))
 {
   affiche ();
 }
}

void BaseErreurs::affiche () const
{ if (BaseErreurs::fonAffiche_ != 0)
    BaseErreurs::fonAffiche_ ( ((StructureErreurs *) donneesPartagees_.memoire ())
                               ->msg (),
                              BaseErreurs::argAffiche_);
  else
    cerr <<  ((StructureErreurs *) donneesPartagees_.memoire ())->msg () << endl;
}

void BaseErreurs::miseAJour (int code ...)
{ va_list    ap;

  // initialisation du traitement des arguments variables
  va_start(ap, code);

  // sauvegarde du code d'erreur dans la partie privée
  stockeCode (code);

  // formatage et stockage du message
  stockeMessage (formate (code, ap));

  // fin de récupération des arguments d'appel
  va_end(ap);

}

void BaseErreurs::miseAJour (const char* format ...)
{ va_list    ap;

  // initialisation du traitement des arguments variables
  va_start(ap, format);

  // sauvegarde du code d'erreur dans la partie privée
  stockeCode (CodeInconnu);

  // formatage et stockage du message
  stockeMessage (formate (format, ap));

  // fin de récupération des arguments d'appel
  va_end(ap);

}

int BaseErreurs::correspond (int ncode, const char* dom) const
{ // vérification de la correspondance avec une erreur donnée
  return ((code () == ncode) && (strcmp (dom, domaine ()) == 0)) ? 1 : 0;
}

void BaseErreurs::initErreurs (void (*f) (const char*, void*), void* arg,
                               int exceptions, int avertissements)
{ BaseErreurs::fonAffiche_     = f;
  BaseErreurs::argAffiche_     = arg;
  BaseErreurs::exceptions_     = exceptions;
  BaseErreurs::avertissements_ = avertissements;
}

void BaseErreurs::avertissement (const char* format ...)
{ va_list    ap;

  // initialisation du traitement des arguments variables
  va_start(ap, format);

  // construction d'une erreur par défaut
  BaseErreurs err;

  // mise à jour de l'erreur
  err.stockeCode (CodeInconnu);
  err.stockeMessage (err.formate (format, ap));

  va_end(ap);

}

int BaseErreurs::erreur (BaseErreurs* ptr, int code ...)
{ va_list    ap;

  // initialisation du traitement des arguments variables
  va_start(ap, code);

  if (ptr != 0)
  { // l'appelant a donné une instance d'erreur à remplir
    ptr->stockeCode (code);
    ptr->stockeMessage (ptr->formate (code, ap));
  }
  else
  { // l'appelant n'a pas donné d'instance, il faut la créer
    BaseErreurs err;
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

int BaseErreurs::erreur (BaseErreurs* ptr, const char* format ...)
{ va_list    ap;

  // initialisation du traitement des arguments variables
  va_start(ap, format);

  // gestion de l'erreur sans argument variable
  if (ptr != 0)
  { // l'appelant a donné une instance d'erreur à remplir
    ptr->stockeCode (CodeInconnu);
    ptr->stockeMessage (ptr->formate (format, ap));
  }
  else
  { // l'appelant n'a pas donné d'instance, il faut la créer
    BaseErreurs err;
    err.stockeCode (CodeInconnu);
    err.stockeMessage (err.formate (format, ap));

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
