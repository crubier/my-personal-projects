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
//>       FormatFortran.cpp
//
//$Resume
//       fichier d'implantation de la classe FormatFortran
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class FormatFortran
//>         ajoutePart()     
//>         modificateurs()  
//>         terme()          
//>         specificateur()  
//>         liste()          
//>         FormatFortran()  
//>         operator =()     
//>         ~FormatFortran() 
//>         analyse()        
//>         applique()       
//>         compatible()     
//>         nbArgs()         
//>         typeArg()        
//
//$Historique
//       $Log: FormatFortran.cpp,v $
//       Revision 1.17  2004/06/11 07:51:33  club
//       correction du format d'écriture des réels (FA-ID 33)
//
//       Revision 1.16  2003/07/17 12:38:06  club
//       Mise a jour suite aux patchs du 17/07/003
//
//       Revision 1.15  2003/02/03 13:35:21  club
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.14  2002/12/10 09:06:56  club
//       DM-ID 12 Modification portant sur l'initialisation des pointeurs et variables.
//
//       Revision 1.13  2000/10/24 14:21:01  club
//       Remplacement de l'include ClubConfig.h par ClubConfigNoInstall.h
//
//       Revision 1.12  2000/10/24 08:33:30  club
//       modification des include standard du C : utilisation de cNAME au lieu de
//       NAME.h (pour permettre la compilation avec le Sun Workshop 5.0)
//
//       Revision 1.11  2000/09/07 08:09:27  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//       ajout de l'include stdio.h
//
//       Revision 1.10  2000/07/03 08:57:19  club
//       Ajout du copyright CNES
//
//       Revision 1.9.2.1  2000/03/30 14:46:47  club
//       ajout du copyright CNES
//
//       Revision 1.9  1999/07/07 07:55:16  club
//       Passage a une gestion d'erreurs par exceptions
//
//       Revision 1.8  1998/11/17 11:55:49  club
//       élimination de l'inclusion de ctype.h
//       ajout de (void) explicites pour indiquer que l'on ignore certains retours
//
//       Revision 1.7  1998/07/27 10:13:46  club
//       passage à une configuration de type GNU (fichier ClubConfig.h généré)
//
//       Revision 1.6  1998/06/21 15:54:12  luc
//       modification du format de l'en-tête
//       élimination de la chaîne statique RCS
//
//       Revision 1.5  1998/04/26 13:02:26  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.4  1998/01/22 08:21:02  luc
//       correction d'une valeur de retour manquante
//
//       Revision 1.3  1997/10/14 16:46:49  luc
//       élimination d'une répétition de valeur par défaut dans une signature
//       passage par un typedef pour faciliter le travail du compilateur SUN
//
//       Revision 1.2  1997/08/28 20:18:21  luc
//       modification de la signature de applique pour répondre aux besoins
//       des interfaces fortran tradecrch_ et tradecrfd_
//
//       Revision 1.1  1997/08/27 20:57:59  luc
//       Initial revision
//
//$Version
//       $Id: FormatFortran.cpp,v 1.17 2004/06/11 07:51:33 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       G. Lajon     CSSI
//       O. Queyrut  CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#if STDC_HEADERS
# include <cstdlib>
# include <cstdio>
#endif

#include "club/FormatFortran.h"
#include "club/Traducteur.h"


FormatFortran::FormatFortran (const FormatFortran& f)
  : tailleTableParts_ (0), nombreParts_ (0), type_ (0), formatC_ (0),
    chaine_ (f.chaine_)
{ // constructeur par copie
  for (int i = 0; i < f.nombreParts_; i++)
    ajoutePart (f.type_ [i], f.formatC_ [i]);
}

FormatFortran& FormatFortran::operator = (const FormatFortran& f)
{ // affectation
  if (this != &f)    // protection contre x = x
  { // copie des tables
    nombreParts_ = 0;
    for (int i = 0; i < f.nombreParts_; i++)
      ajoutePart (f.type_ [i], f.formatC_ [i]);

    chaine_ = f.chaine_;
  }
  return *this;
}

FormatFortran::~FormatFortran ()
{ // destructeur
  if (tailleTableParts_)
  { // libération de la mémoire allouée
    delete [] type_;
    delete [] formatC_;
  }
}

void FormatFortran::analyse (const string& format)
  throw(ClubErreurs)
{ // analyse d'un format fortran
  chaine_      = format;
  nombreParts_ = 0;

  // préparation de l'analyseur lexical
  AnalyseurLexical al       (format);
  al.interditReels          ();
  al.autoriseChainesFortran ();
  al.initSeparateurs        (".,");
  al.initOperateurs         ("/AaDdEeFfGgIiLlOoXxZz");

  // analyse
  if (liste (&al))
    throw ClubErreurs (ClubErreurs::format_fortran,
                       format.c_str ());
}

va_list FormatFortran::applique (va_list ap,
                                 int nbLong, long int tabLong [],
                                 string *ptrChaine) const
{ // écriture d'une chaîne selon un format analysé
  int i;
  *ptrChaine = "";

  // comptabilisation des arguments
  int nbEntiers  = 0;
  int nbReels    = 0;
  int nbChaines  = 0;
  int nbBooleens = 0;
  for (i = 0; i < nombreParts_; i++)
    if (type_ [i] == ENTIER)
      nbEntiers++;
    else if (type_ [i] == REEL)
      nbReels++;
    else if (type_ [i] == CHAINE_ARG)
      nbChaines++;
    else if (type_ [i] == BOOLEEN)
      nbBooleens++;

  // allocation des tables
  typedef char *CharPTR;
  int           *entier        = new int      [nbEntiers];
  double        *reel          = new double   [nbReels];
  CharPTR       *chaine        = new CharPTR  [nbChaines];
  string        *chaineLimitee = new string   [nbChaines];
  int           *booleen       = new int      [nbBooleens];

  int iEntier  = 0;
  int iReel    = 0;
  int iChaine  = 0;
  int iBooleen = 0;

  // lecture des arguments
  int    *ptrEntier    = NULL;
  double *ptrReel      = NULL;
  char   *ptrChaineArg = NULL;
  for (i = 0; i < nombreParts_; i++)
  { // boucle sur les constituants du format
    switch (type_ [i])
    { // sélection selon le type de part
      case ENTIER :
        ptrEntier = va_arg(ap, int *);
        entier [iEntier++] = *ptrEntier;
        break;

      case REEL :
        ptrReel = va_arg(ap, double *);
        reel [iReel++] = *ptrReel;
        break;

      case CHAINE_ARG :
        ptrChaineArg  = va_arg(ap, char *);
        chaine [iChaine++] = ptrChaineArg;
        break;

      case BOOLEEN :
        ptrEntier = va_arg(ap, int *);
        booleen [iBooleen++] = *ptrEntier;
        break;

      default :
        // pas d'argument
        break;
    }
  }

  // lecture des longueurs de chaînes supplémentaires
  for (i = 0; i < nbLong; i++)
    tabLong [i] = va_arg(ap, long int);

  for (i = 0; i < nbChaines; i++)
  { // lecture des longueurs des chaînes arguments
    long int lg = va_arg(ap, long int);
    chaineLimitee [i] = string (chaine [i], lg);
  }

  iEntier  = 0;
  iReel    = 0;
  iChaine  = 0;
  iBooleen = 0;

  // écriture dans un tampon de taille supposée suffisante
  char* c = new char [4096];

  for (i = 0; i < nombreParts_; i++)
  { // boucle de formatage
    switch (type_ [i])
    { // sélection selon le type de part
      case ENTIER :
        (void) sprintf (c, formatC_ [i].c_str (), entier [iEntier++]);
        *ptrChaine += c;
        break;

      case REEL :
        (void) sprintf (c, formatC_ [i].c_str (), reel [iReel++]);
        *ptrChaine += c;
        break;

      case CHAINE_ARG :
        if (formatC_ [i] != "")
        { // il y avait une spécification de taille de champ
          unsigned int taille = atoi (formatC_ [i].c_str ());
          unsigned int tailleChaine = chaineLimitee [iChaine].size ();
          if (taille > tailleChaine)
            chaineLimitee [iChaine] = string (taille-tailleChaine, ' ') +
                                      chaineLimitee [iChaine];
          else if (taille < tailleChaine)
            chaineLimitee [iChaine].erase (taille);
        }
        *ptrChaine += chaineLimitee [iChaine++];
        break;

      case BOOLEEN :
        *ptrChaine += booleen [iBooleen++] ? "T" : "F";
        break;

      default :
        *ptrChaine += formatC_ [i];
        break;
    }
  }

  delete [] c;
  
  // libération des tables
  delete [] entier;
  delete [] reel;
  delete [] chaine;
  delete [] chaineLimitee;
  delete [] booleen;

  return ap;

}

int FormatFortran::compatible (const FormatFortran& f) const
{ // teste la compatibilité de deux formats au niveau des arguments attendus
  int n = nbArgs ();

  if (n != f.nbArgs ())
    return 0;

  for (int i = 0; i < n; i++)
    if (typeArg (i) != f.typeArg (i))
      return 0;

  return 1;  
}

int FormatFortran::nbArgs () const
{ // comptabilisation des arguments
  int n = 0;
  for (int i = 0; i < nombreParts_; i++)
    if ((type_ [i] == ENTIER)     || (type_ [i] == REEL)
     || (type_ [i] == CHAINE_ARG) || (type_ [i] == BOOLEEN))
      n++;

  return n;
}

int FormatFortran::typeArg (int i) const
{ // récupération du type attendu pour un argument
  if (i < 0)
    return ERREUR;

  for (int j = 0; j < nombreParts_; j++)
    if ((type_ [j] == ENTIER)     || (type_ [j] == REEL)
     || (type_ [j] == CHAINE_ARG) || (type_ [j] == BOOLEEN))
      if (i-- == 0)
        return type_ [j];

  return ERREUR;

}

void FormatFortran::ajoutePart (int type, const string& format)
{ // ajout d'un élément aux tables d'analyse de parts de format

  // sauvegarde (plus explicite qu'un passage par copie) de l'argument
  // cette précaution évite les problèmes si l'on appelle cette
  // méthode avec un élément du tableau formatC_, lequel peut être
  // désalloué en cours d'exécution (la méthode specificateur utilise
  // un appel de ce genre)
  string sauve (format);

  if (nombreParts_ == tailleTableParts_)
  { // extension des tables d'analyse de parts de format
    int taille = (tailleTableParts_ <= 0) ? 5 : (tailleTableParts_ << 1);

    int    *nouveauxTypes   = new int    [taille];
    string *nouveauxFormats = new string [taille];

    for (int i = 0; i < nombreParts_; i++)
    { // copie des anciennes tables
      nouveauxTypes   [i] = type_    [i];
      nouveauxFormats [i] = formatC_ [i];
    }

    if (tailleTableParts_)
    { // libération des anciennes tables
      delete [] type_;
      delete [] formatC_;
    }

    // mise en place des nouvelles tables
    tailleTableParts_ = taille;
    type_             = nouveauxTypes;
    formatC_          = nouveauxFormats;
  }
  type_    [nombreParts_] = type;
  formatC_ [nombreParts_] = sauve;
  nombreParts_++;
}

int FormatFortran::modificateurs (AnalyseurLexical *al,
                                  int *ptrTaille, int *ptrPrecision)
{ // analyse des modificateurs de termes
  // exemples : le "6.3" de "F6.3", ou le "2" de "I2"
  *ptrTaille    = -1;
  *ptrPrecision = -1;

  if (al->suivant () == AnalyseurLexical::codeEntier)
  { // il y a un modificateur de taille
    *ptrTaille = al->entier ();

    if ((al->suivant () == AnalyseurLexical::codeSeparateur)
        &&
        (al->separateur () == '.'))
    { // il doit y avoir un modificateur de précision
      if (al->suivant () != AnalyseurLexical::codeEntier)
      { // erreur de syntaxe, le '.' devrait introduire un modificateur
        (void) al->precedent ();
        return 1;
      }
      *ptrPrecision = al->entier ();
    }
    else
    { // il n'y a pas de modificateur
      (void) al->precedent ();
    }
  }
  else
  { // il n'y a pas de modificateur
    (void) al->precedent ();
  }

  return 0;
}

int FormatFortran::terme (AnalyseurLexical *al)
{ // analyse d'un "terme" de spécificateur de champ de format fortran
  // un "terme" est ici un élément sans son facteur de répétition
  // exemples : le "F6.3" de "12F6.3", ou le "(3X, I2)" de "5(3X, I2)"
  if ((al->suivant () == AnalyseurLexical::codeParenthese)
      &&
      (al->parenthese () == '('))
  { // c'est le début d'une nouvelle liste
    (void) al->precedent ();
    return liste (al);
  }
  else if (al->type () == AnalyseurLexical::codeChaineFortran)
  { // c'est une chaîne littérale
    ajoutePart (CHAINE_FIXE, al->chaineFortran ());
  }
  else if ((al->type () == AnalyseurLexical::codeOperateur)
           &&
           (al->operateur () == '/'))
  { // c'est un (ou plusieurs) saut(s) de ligne(s)
    while ((al->type () == AnalyseurLexical::codeOperateur)
           &&
           (al->operateur () == '/'))
    { ajoutePart (CHAINE_FIXE, "\n");
      (void) al->suivant ();
    }
    (void) al->precedent ();
  }
  else if (al->type () == AnalyseurLexical::codeOperateur)
  { // c'est un terme élémentaire
    int specificateur = al->operateur ();

    // extraction préalable des modificateurs
    int taille, precision;
    if (modificateurs (al, &taille, &precision))
      return 1;

    string chaine;

    // écriture dans un tampon de taille supposée suffisante
    char* tampon = new char[4096];

    switch (specificateur)
    { // sélection du type de formatage

      case 'A' : case 'a' :   // chaînes de caractères
        if (taille < 0)
          chaine = "";
        else
        { (void) sprintf (tampon,"%d", taille);
          chaine = tampon; 
        }
        ajoutePart (CHAINE_ARG, chaine);
        break;

      case 'D' : case 'd' : case 'E' : case 'e' :   // réels
        if (taille < 0)
          chaine = "%e";
        else if (precision < 0)
        { (void) sprintf (tampon, "%%%de", taille);
          chaine = tampon; 
        }
        else
        { (void) sprintf (tampon, "%%%d.%de", taille, precision);
          chaine = tampon; 
        }
        ajoutePart (REEL, chaine);
        break;

      case 'F' : case 'f' :
        if (taille < 0)
          chaine = "%f";
        else if (precision < 0)
        { (void) sprintf (tampon, "%%%df", taille);
          chaine = tampon; 
        }
        else
        { (void) sprintf (tampon, "%%%d.%df", taille, precision);
          chaine = tampon; 
        }
        ajoutePart (REEL, chaine);
        break;

      case 'G' : case 'g' :
        if (taille < 0)
          chaine = "%g";
        else if (precision < 0)
        { (void) sprintf (tampon, "%%%dg", taille);
          chaine = tampon; 
        }
        else
        { (void) sprintf (tampon, "%%%d.%dg", taille, precision);
          chaine = tampon; 
        }
        ajoutePart (REEL, chaine);
        break;

      case 'I' : case 'i' :
        if (taille < 0)
          chaine = "%d";
        else
        { (void) sprintf (tampon, "%%%dd", taille);
          chaine = tampon; 
        }
        ajoutePart (ENTIER, chaine);
        break;

      case 'L' : case 'l' :
        ajoutePart (BOOLEEN, chaine);
        break;

      case 'O' : case 'o' :
        if (taille < 0)
          chaine = "%o";
        else
        { (void) sprintf (tampon, "%%%do", taille);
          chaine = tampon; 
        }
        ajoutePart (ENTIER, chaine);
        break;

      case 'X' : case 'x' :  // blancs
        chaine = " ";
        while (--taille > 0)
          chaine += " ";
        ajoutePart (CHAINE_FIXE, chaine);
        break;

      case 'Z' : case 'z' :
        if (taille < 0)
          chaine = "%x";
        else
        { (void) sprintf (tampon, "%%%dx", taille);
          chaine = tampon; 
        }
        ajoutePart (ENTIER, chaine);
        break;

      default :
        return 1;
        // break ;
    }

    delete [] tampon;
  }
  return 0;
}

int FormatFortran::specificateur (AnalyseurLexical *al)
{ // analyse d'un spécificateur de champ de format fortran, avec son
  // facteur de répétition éventuel
  // exemples : "12F6.3", "5(3X, I2)"

  // analyse du facteur de répétition
  int nombre = 1;
  if (al->suivant () == AnalyseurLexical::codeEntier)
    nombre = al->entier ();
  else
    (void) al->precedent ();

  // analyse et stockage du terme
  int nbSpecAvant = nombreParts_;
  if (terme (al))
    return 1;
  int nbSpecTerme = nombreParts_ - nbSpecAvant;

  while (--nombre)
  { // répétition du terme (pour arriver à un total de "nombre" occurrences)
    for (int i = 0; i < nbSpecTerme; i++)
      ajoutePart (type_    [nbSpecAvant + i],
                  formatC_ [nbSpecAvant + i]);
  }
  return 0;     
}

int FormatFortran::liste (AnalyseurLexical *al)
{ // analyse d'une liste de spécificateurs de champ de format fortran
  // "(12F6.3, 5(3X, I2))" est ainsi une liste de deux spécificateurs
  // (le deuxième étant lui-même une liste de deux spécificateurs)
  if ((al->suivant () != AnalyseurLexical::codeParenthese)
      ||
      (al->parenthese () != '('))
    return 1;

  // premier élément de la liste
  if (specificateur (al))
    return 1;

  while (1)
  { // tentative de reconnaissance d'un élément de liste supplémentaire

    if ((al->suivant () == AnalyseurLexical::codeSeparateur)
        &&
        (al->separateur () == ','))
    { // il reste au moins un spécificateur à analyser
      if (specificateur (al))
        return 1;
    }
    else if ((al->type () == AnalyseurLexical::codeParenthese)
             &&
             (al->parenthese () == ')'))
      return 0;
    else
      return 1;
  }
}
