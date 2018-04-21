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
//>       FichierStructure.cpp
//$Resume
//       fichier d'implantation de la classe FichierStructure
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       static int BlocSuivant()                 
//>       static char* AlloueChaine()              
//>       static void LibereChaine()               
//>       static char* SepareDelimiteurs()         
//>       static int RechercheSousBlocElementaire()
//>       class FichierStructure                   
//>         rechercheSousBloc()                    
//>         FichierStructure()                     
//>         operator =()                           
//>         lit()                                  
//>         terminal()                             
//>         nombreChamps()                         
//>         champ()                                
//>         contientSousBloc()                     
//$Historique
//       $Log: FichierStructure.cpp,v $
//       Revision 3.25  2003/07/17 12:38:06  club
//       Mise a jour suite aux patchs du 17/07/003
//
//       Revision 3.24  2003/02/03 13:31:54  club
//       DM-ID 12 Mise à jour d'un include selon la norme C++
//
//       Revision 3.22  2002/12/10 09:05:14  club
//       DM-ID 12 Modification portant sur l'initialisation des pointeurs et variables.
//
//       Revision 3.21  2002/08/30 08:27:53  club
//       Ajout de la prise en compte de la FA16, changement de signature d'une méthode
//
//       Revision 3.20  2002/06/27 15:48:42  club
//       ajout de la méthode listeSousBlocs
//
//       Revision 3.19  2001/06/22 05:41:29  club
//       remplacement de l'inclusion de cwctype par l'inclusion de cctype
//
//       Revision 3.18  2000/11/21 10:24:04  club
//       homogénéisation de la signature des catch
//
//       Revision 3.17  2000/10/24 14:21:00  club
//       Remplacement de l'include ClubConfig.h par ClubConfigNoInstall.h
//
//       Revision 3.16  2000/10/24 08:33:29  club
//       modification des include standard du C : utilisation de cNAME au lieu de
//       NAME.h (pour permettre la compilation avec le Sun Workshop 5.0)
//
//       Revision 3.15  2000/09/07 08:07:56  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//       ajout de l'include ctype.h et stdio.h
//
//       Revision 3.14  2000/07/03 08:57:19  club
//       Ajout du copyright CNES
//
//       Revision 3.13.2.1  2000/03/30 14:46:47  club
//       ajout du copyright CNES
//
//       Revision 3.13  1999/08/12 09:58:25  club
//       suppression de la copie d'erreur dans la fonction
//       rechercheSousBloc
//
//       Revision 3.12  1999/07/07 07:55:16  club
//       Passage a une gestion d'erreurs par exceptions
//
//       Revision 3.11  1999/04/12 15:15:48  club
//       *** empty log message ***
//
//       Revision 3.10  1998/11/17 11:58:31  club
//       élimination de l'inclusion de ctype.h
//       protection contre trois possibilités d'utilisation de pointeurs nuls
//
//       Revision 3.9  1998/09/14 09:10:26  club
//       gestion de la date et de la signature du contenu des fichiers lus
//
//       Revision 3.8  1998/07/27 10:13:44  club
//       passage à une configuration de type GNU (fichier ClubConfig.h généré)
//
//       Revision 3.7  1998/06/21 15:52:32  luc
//       modification du format de l'en-tête
//       élimination de la chaîne statique RCS
//
//       Revision 3.6  1998/04/26 13:02:24  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 3.5  1997/08/21 16:44:01  luc
//       ajout d'un en-tête de fichier
//
//       Revision 3.4  1997/06/30 08:52:48  luc
//       ajout de la définition de :
//       FichierStructure::FichierStructure (const ChaineSimple& nomFichier,
//                                           ClubErreurs *ptrErreur)
//       
//       Revision 3.3  1997/04/03 12:47:11  luc
//       inversion des codes de retour, 0 signifie désormais : pas d'erreur
//       
//       Revision 3.2  1997/03/25 15:04:56  luc
//       changement des règles de nommage
//       
//       Revision 3.1  1997/03/19 15:17:36  luc
//       utilisation de la classe ChaineSimple
//       renommage de la classe UtilErreurs en ClubErreurs
//       renommage de la bibliothèque util_c++ en club
//       passage de SCCS à RCS
//       
//       Revision 2.3  1996/07/15 17:12:24  luc
//       prise en compte de renommage de erreur.h en util_erreur.h
//       
//       Revision 2.2  1996/05/24 11:35:02  luc
//       correction d'une erreur de detection d'erreurs lors des suivis d'indirection
//       (le mauvais type d'erreur était émis, avec le mauvais nom de bloc père)
//       
//       Revision 2.1  1996/05/14 09:45:48  luc
//       élimination des tools.h++
//       extension de l'indirection de bloc (notion de valeurs par défaut)
//       ajout de l'inclusion de fichiers
//       élimination de code redondant (lectures)
//       restructuration de code
//       
//       Revision 1.9  1995/06/26 07:36:11  mercator
//       modification de la portee de variables de boucle for
//       
//       Revision 1.8  1995/01/03 07:58:42  mercator
//       remplacement des variables globales de traduction
//       par des fonctions globales
//       
//       Revision 1.7  1994/12/19 13:48:13  mercator
//       amelioration de la gestion des erreurs
//       lors de la recherche des sous-blocs
//       
//       Revision 1.6  1994/12/13 07:55:19  mercator
//       ajout d'une interface en FILE* a la construction et a la lecture
//       
//       Revision 1.5  1994/11/20 14:22:49  mercator
//       ajout d'un pointeur d'erreur nul par defaut dans plusieurs fonctions membres
//       
//       Revision 1.4  1994/11/09 15:01:41  mercator
//       elimination des directives #pragma
//       
//       Revision 1.3  1994/09/28 16:28:31  mercator
//       prise en compte du changement de nom:
//       FichierTexte --> TamponTexte
//       
//       Revision 1.2  1994/08/30 12:54:22  mercator
//       remplacement de "lance" par "erreur"
//       
//       Revision 1.1  1994/08/10 14:31:57  mercator
//       Initial revision
//
//$Version
//       $Id: FichierStructure.cpp,v 3.25 2003/07/17 12:38:06 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       G. Lajon     CSSI
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif

#if STDC_HEADERS
# include <cctype>
# include <cstdio>
#endif

#ifdef HAVE_SYS_STAT_H
# include <sys/stat.h>
#endif

#ifdef HAVE_CTIME
# include <ctime>
#endif

#include "club/ClubErreurs.h"
#include "club/Traducteur.h"
#include "club/FichierStructure.h"

static void  BlocSuivant                (const char *nomPere,
                                         const string& nomFichier,
                                         const char  *max,
                                         const char **accOuvre,
                                         const char **accFerme,
                                         const char **debutNom,
                                         const char **apresNom)
  throw (ClubErreurs);
static char* AlloueChaine               (int longueur);
static void  LibereChaine               (void *memoire, void *);
static char* SepareDelimiteurs          (const string& nomFichier,
                                         const char *brut) 
  throw (ClubErreurs);

static void RechercheSousBlocElementaire (const char *clef,
                                          int         longClef,
                                          const char *nomPere,
                                          const string& nomFichier,
                                          const char  *debut,
                                          const char *max,
                                          const char **addrDebut,
                                          const char **addrFin)
  throw (ClubErreurs);

static void BlocSuivant (const char *nomPere,
                         const string& nomFichier,
                         const char  *max,
                         const char **accOuvre, const char **accFerme,
                         const char **debutNom, const char **apresNom)
  throw (ClubErreurs)
{ // initialisation de la recherche
  *debutNom = *accFerme + 1;

  // extraction du premier champ
  while (isspace(**debutNom) && (*debutNom <= max))
    (*debutNom)++;

  // test des limites
  if (*debutNom >= max)
    throw ClubErreurs (CodeInconnu);


  // recherche des limites du nom du bloc
  if (**debutNom == '{')
  { // c'est un bloc sans nom
    *apresNom = *debutNom;
  }
  else
  { // c'est un bloc avec nom
    *apresNom = *debutNom;
    while (**apresNom && !isspace(**apresNom))
      (*apresNom)++;
  }

  // recherche du début du bloc
  *accOuvre = *apresNom;
  while (isspace (**accOuvre))
    (*accOuvre)++;
  if (**accOuvre != '{')
  { 
    string nom (nomPere);
    nom += ".";
    nom += string (*debutNom, *apresNom - *debutNom);
    throw ClubErreurs(ClubErreurs::manque_accolade, nom.c_str (),
                      nomFichier.c_str ());
  }

  // recherche de la fin du bloc
  // les prétraitements à la lecture du fichier garantissent le succès
  *accFerme   = *accOuvre + 1;
  int niveau = 1;
  while (niveau)
  { 
    (*accFerme)++;
    
    if (**accFerme == '{')
      niveau++;
    else if (**accFerme == '}')
      niveau--;
    
  }

}

static char* AlloueChaine (int longueur)
{ return new char [longueur + 1]; }

static void  LibereChaine (void *memoire, void *)
{ delete [] ((char *) memoire); }

static char* SepareDelimiteurs (const string& nomFichier,
                                const char* brut)
  throw (ClubErreurs)
{ // vérification des imbrications d'accolades
  int nombre   = 0;
  int niveau   = 0;
  const char* s = NULL;

  for (s = brut; *s; s++)
  { 
    if (*s == '{')
    { 
      niveau++;
      nombre++;
    }
    else if (*s == '}')
    { 
      niveau--;
      nombre++;
    }
  }

  if (niveau != 0)
  { 
    throw ClubErreurs (ClubErreurs::accolades_non_equilibrees,
                       (char *) nomFichier.c_str ());
  }

  // séparation des '{' et '}' (pour pouvoir se fier aux ' ')
  char* memoire = AlloueChaine (s - brut + 2 * nombre);
        s       = brut;
  char* d       = memoire;
  while (*s)
  { 
    if ((*s == '{') || (*s == '}'))
    { 
      *d++ = ' ';
      *d++ = *s++;
      *d++ = ' ';
    }
    else
      *d++ = *s++;
  }
  *d = '\0';

  return memoire;

}

static void RechercheSousBlocElementaire (const char *clef,
                                          int         longClef,
                                          const char *nomPere,
                                          const string& nomFichier,
                                          const char  *debut,
                                          const char *max,
                                          const char **addrDebut,
                                          const char **addrFin)
  throw (ClubErreurs)
{ 
  // la partie en cours d'analyse contient-elle des sous-blocs ?
  const char *mobile = debut;
  while ((mobile <= max) && (*mobile != '{'))
    mobile++;
  if (*mobile != '{')
  { 
    string clefLocale (clef, longClef);
    throw ClubErreurs (ClubErreurs::bloc_introuvable,
                       clefLocale.c_str (),
                       nomPere, nomFichier.c_str ());
  }

  // itérateur sur les sous-blocs dans les limites imposées
  const char* accFerme = debut - 1;
  const char* accOuvre = NULL;
  const char* debutNom = NULL;
  const char* apresNom = NULL;


  try 
  {
    bool trouve = false;
    while (!trouve)
    { 
      BlocSuivant (nomPere, nomFichier, max,
                   &accOuvre, &accFerme, &debutNom, &apresNom);
      int longNom = apresNom - debutNom;
      if (longClef == longNom)
      { 
        if ((longClef == 0) || (strncmp (clef, debutNom, longClef) == 0))
        { // le bloc courant correspond à la clef cherchée
          *addrDebut = accOuvre + 1;
          *addrFin   = accFerme - 1;
          trouve=true;
        }
      }
    }
  }

  catch(ClubErreurs ce)
  {
    // la clef n'existe pas
    if (ce.code () != CodeInconnu)
    {
      throw; // Le ClubErreurs ce est déjà renseigné correctement
    }
    else
    { 
      ce.correction();
      string clefLocale (clef, longClef);
      throw ClubErreurs(ClubErreurs::bloc_introuvable,
                        clefLocale.c_str (),
                        nomPere, nomFichier.c_str ());
    }
  }
}


FichierStructure::FichierStructure (FILE *ptrFic) 
  throw (ClubErreurs)
{ 
  lit (ptrFic);
}

FichierStructure::FichierStructure (const char *nomFichier) 
  throw (ClubErreurs)
{
  lit (nomFichier);
}

FichierStructure::FichierStructure (const string& nomFichier) 
  throw (ClubErreurs)
{
  lit (nomFichier);
}

FichierStructure::FichierStructure (TamponTexte *fichier) 
  throw (ClubErreurs)
{
  lit (fichier);
}

FichierStructure::FichierStructure (const char *clef,
                                    const FichierStructure *pere) 
  throw (ClubErreurs)
{
  // le bloc doit être entièrement à l'intérieur de son père
  *this = *pere;
  rechercheSousBloc (string (clef),
                     (const char **) &debut_, (const char **) &fin_,
                     &nomBloc_);
}

FichierStructure::FichierStructure (const string& clef,
                                    const FichierStructure *pere)
 throw (ClubErreurs)
{ 
  // le bloc doit être entièrement à l'intérieur de son père
  *this = *pere;
  rechercheSousBloc (clef,
                     (const char **) &debut_, (const char **) &fin_,
                     &nomBloc_);
}

FichierStructure& FichierStructure::operator = (const FichierStructure& f)
{ 
  if (this != &f)     // protection contre x = x
  { 
    nomFichier_ = f.nomFichier_;
    nomBloc_    = f.nomBloc_;
    total_      = f.total_;
    debut_      = f.debut_;
    fin_        = f.fin_;
    date_       = f.date_;
    signature_  = f.signature_;    
  }
  return *this;
}

void FichierStructure::lit (FILE *ptrFic)
  throw (ClubErreurs)
{ // ouverture du fichier (sans interprétation des guillemets)

  TamponTexte fichier (ptrFic, 0);

  lit (&fichier);

}

void FichierStructure::lit (const char *nomFichier)
  throw (ClubErreurs)
{ // ouverture du fichier (sans interprétation des guillemets)

  TamponTexte fichier (nomFichier, 0);
  lit (&fichier);
}

void FichierStructure::lit (const string& nomFichier)
  throw (ClubErreurs)
{ // ouverture du fichier (sans interprétation des guillemets)

  TamponTexte fichier (nomFichier.c_str (), 0);
  lit (&fichier);
}

void FichierStructure::lit (TamponTexte *ptrTampon)
  throw (ClubErreurs)
{ // lecture d'un fichier
  time_t derniereDate = 0;
  if (*(ptrTampon->nom ()) != '\0')
  { // on utilise la date de dernière modification du contenu du fichier
    struct stat buf;
    if (stat (ptrTampon->nom (), &buf))
      throw ClubErreurs( ClubErreurs::etat_fichier, ptrTampon->nom ());
    derniereDate = buf.st_mtime;
  }

  // extraction du nom du répertoire
  const char *nomFic      = ptrTampon->nom ();
  const char *finRep      = strrchr (nomFic, '/');
  int         longRep     = finRep ? (finRep - nomFic + 1) : 0;
  string      repertoire  = longRep ? string (nomFic, longRep)
                                    : string ("");
  int nouveauPassage;
  do
  { // élimination des commentaires et des lignes blanches

     ptrTampon->elimineCommentaires ();
     ptrTampon->elimineBlancs       ();

    // recherche d'un indicateur d'inclusion
    const char *premier = ptrTampon->total ();
    const char *mobile  = premier;
    while (*mobile && (*mobile != '<'))
      mobile++;
    if (*mobile)
    { 
      int chevronOuvre = mobile - premier;

      mobile++;
      while (isspace(*mobile))
        mobile++;
      int debutNom = mobile - premier;

      while (*mobile && (!isspace(*mobile)) && (*mobile != '>'))
        mobile++;
      int apresNom = mobile - premier;

      while (isspace(*mobile))
        mobile++;
      int chevronFerme = mobile - premier;

      // vérification de la syntaxe
      if (*mobile != '>')
      { 
        string zone (premier + chevronOuvre,
                     chevronFerme - chevronOuvre + 1);
        throw ClubErreurs( ClubErreurs::manque_chevron,
                           zone.c_str (), nomFic);
      }
      if (apresNom <= debutNom)
        throw ClubErreurs(ClubErreurs::nom_inclusion, nomFic);

      // constitution du nom du fichier à inclure
      string nom = (premier [debutNom] == '/')
                       ? string ("")
                       : string (repertoire.c_str (), longRep);
      nom += string (premier + debutNom, apresNom - debutNom);

      // lecture du fichier (sans interprétation des guillemets)

      TamponTexte inclus (nom.c_str (), 0);

      // inclusion du fichier

      ptrTampon->elimineZone    ((char *) premier + chevronOuvre +1,
                                 (char *) premier + chevronFerme);

      ptrTampon->insereAAdresse ((char *) ptrTampon->total () + chevronOuvre,
                                 inclus.total ());

      // correction éventuelle de la date
      struct stat buf;
      if (stat (nom.c_str (), &buf))
        throw ClubErreurs( ClubErreurs::etat_fichier, nom.c_str ());
      if (derniereDate < buf.st_mtime)
        derniereDate = buf.st_mtime;

      nouveauPassage = 1;
    }
    else
      nouveauPassage = 0;

  } while (nouveauPassage);

  // formatage de la date
  struct tm  *tmptr = NULL;
  tmptr = gmtime (&derniereDate);

  // écriture dans un tampon de taille supposée suffisante
  char temp[4096];

  // le champ tm_year contient le nombre d'années depuis 1900.
  (void) sprintf (temp, "%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d",
                  tmptr->tm_year + 1900, tmptr->tm_mon + 1, tmptr->tm_mday,
                  tmptr->tm_hour, tmptr->tm_min, tmptr->tm_sec);
  date_ = temp;

  // calcul de la signature
  signature_ = 0;
  for (const char *mobile = ptrTampon->total (); *mobile; mobile++)
  { // fonction de hachage de P. J. Weinberger
    signature_ = (signature_ << 4) + *mobile;
    unsigned int poidsFort = signature_ & 0xF0000000;
    if (poidsFort != 0)
    { // on redescend les bits de poids fort
      signature_ ^= poidsFort >> 24;
      signature_ ^= poidsFort;
    }
  }

  // séparation des '{' et des '}'
  char* tampon = SepareDelimiteurs (ptrTampon->nom (), ptrTampon->total ());

  // mémorisation du fichier
  total_ = TamponPartage (tampon, LibereChaine, 0);

  // mise en place des pointeurs
  debut_      = (char *) total_.memoire ();
  fin_        = debut_ + strlen (debut_) - 1;
  nomBloc_    = "";
  nomFichier_ = ptrTampon->nom ();
}

bool FichierStructure::terminal () const
{ 
  if (debut_ == 0)
    return true;

  for (char* mobile = debut_; mobile <= fin_; mobile++)
   if (*mobile == '{')
     return false;

  return true;
}

int FichierStructure::nombreChamps () const
{ 
  if ((debut_ == 0) || !terminal ())
    return 0;

  int n        = 0;
  char* mobile = debut_;
  while (mobile < fin_)
  { // saut des blancs initiaux
    while (isspace(*mobile))
      mobile++;

    if (mobile <= fin_)
    { n++;

      // saut des caractères du champ
      while (!isspace(*mobile))
        mobile++;
    }
  }
  return n;
}

void FichierStructure::champ (int numero,
                              char *tampon, const int max) const
  throw (ClubErreurs)
{ 
  tampon [0] = '\0';

  if (! terminal ())
    throw ClubErreurs(ClubErreurs::bloc_non_terminal,
                      nomBloc_.c_str (), nomFichier_.c_str ());

  if ((numero < 1) || (debut_ == 0))
    throw ClubErreurs (ClubErreurs::bloc_champ_inexistant,
                       numero, nomBloc_.c_str (),
                       nomFichier_.c_str ());

  // saut des premiers blancs
  char* mobile = debut_;
  while ((mobile < fin_) && (isspace(*mobile)))
    mobile++;

  // saut des premiers champs
  int n = numero;
  while (--n)
  { 
    while ((mobile < fin_) && !isspace(*mobile))
      mobile++;
    while ((mobile < fin_) &&  isspace(*mobile))
      mobile++;
  }

  if (mobile == fin_)
    throw ClubErreurs (ClubErreurs::bloc_champ_inexistant,
                       numero, nomBloc_.c_str (),
                       nomFichier_.c_str ());

  // extraction du champ désiré
  char* dernier = tampon + max - 1;
  while ((tampon < dernier) && !isspace(*mobile))
    *tampon++ = *mobile++;
  *tampon = '\0';
}

bool FichierStructure::contientSousBloc (const char *clef) const
  throw (ClubErreurs)
{ 
  const char *debut = debut_;
  const char *fin   = fin_;
  bool retour = true;
  string nomBloc;

  try
  {    
   rechercheSousBloc (string (clef), &debut, &fin, &nomBloc);
  }

  catch(ClubErreurs ce)
  {
    // l'erreur "bloc_introuvable" n'est pas considérée grave ici

    if(ce.correspond(ClubErreurs::bloc_introuvable, "club"))
    {    
      ce.correction();
      retour=false;
    }
    else
    {
      throw;
    }
  }
  return retour;
}


void FichierStructure::rechercheSousBloc (const string& clef,
                                          const char  **addrDebut,
                                          const char  **addrFin,
                                          string *addrNomBloc) const
  throw (ClubErreurs)
{ // initialisation des bornes
  const char *localDebut = debut_;
  const char *localFin   = fin_;

  const char *localNomPere = NULL;
  const char *mobile       = NULL;

  // initialisation du nom du bloc (complet avec son père)
  string localNomBloc (nomBloc_.size () + clef.size () + 3, '\0');
  if (! nomBloc_.empty ())
  { // création du nom complet
    localNomBloc  = nomBloc_;
    localNomBloc += ".";
    localNomBloc += clef;
    localNomBloc += ".";

    // séparation du nom en deux chaînes
    localNomBloc [nomBloc_.size ()] = '\0';
    localNomPere  = localNomBloc.c_str ();
    mobile        = localNomBloc.c_str () + nomBloc_.size () + 1;

  }
  else
  { // le nom du bloc fils est complet à lui tout seul
    localNomBloc  = clef;
    localNomBloc += ".";
    mobile        = localNomBloc.c_str ();
    localNomPere  = "";
  }

  while (*mobile)
  { // itération sur les éléments internes de la clef (séparés par des '.')
    const char *finClef = strchr (mobile, '.');

    try 
    {
      RechercheSousBlocElementaire (mobile, finClef - mobile,
                                    localNomPere, nomFichier_,
                                    localDebut,  localFin,
                                    &localDebut, &localFin);
      // on a trouvé le sous-bloc directement
      
      // mise à jour du nom du bloc père
      localNomPere = localNomBloc.c_str ();
      if (mobile != localNomBloc.c_str ())
        localNomBloc [mobile - 1 - localNomBloc.c_str ()] = '.';

      // mise à jour de l'élément interne de la clef
      localNomBloc [finClef - localNomBloc.c_str ()] = '\0';
      mobile   = finClef + 1;
    }
    catch (ClubErreurs ce)
    { // on n'a pas trouvé le sous-bloc
      try 
      {
        RechercheSousBlocElementaire ("=>", 2,
                                      localNomPere, nomFichier_,
                                      localDebut,   localFin,
                                      &localDebut, &localFin);
          
        // il y a un bloc d'indirection
        // extraction du nom du bloc d'indirection
        while (isspace(*localDebut))
          localDebut++;
        while (isspace(*localFin))
          localFin--;

        int longIndirection = ((localFin + 1) < localDebut)
          ? 0 : (localFin + 1 - localDebut);

        // modification de la clef et des bornes pour suivre l'indirection
        string nouveauNom (localDebut, longIndirection);
        if (longIndirection)
          nouveauNom += ".";
        nouveauNom += mobile;
        localNomBloc = nouveauNom;

        localNomPere = "";
        mobile       = localNomBloc.c_str ();
        localDebut   = (const char *) total_.memoire ();
        localFin     = localDebut + strlen (localDebut);
        
      }
      catch( ClubErreurs recherche_indirection)
      { // on ignore l'erreur de la recherche d'indirection
        // on revient sur l'erreur de la recherche directe
        recherche_indirection.correction();
        
        throw ce;
      }
      // si on arrive ici, on a trouvé le sous bloc dans un bloc d'indirection
      ce.correction();
    }
  }
  
  // copie des résultats dans les variables de l'appelant
  *addrDebut   = localDebut;
  *addrFin     = localFin;
  *addrNomBloc = localNomBloc.c_str ();
    
}


void FichierStructure::listeSousBlocs (vector<string> *ptrTable) const
  throw (ClubErreurs)
{

  // la partie en cours d'analyse contient-elle des sous-blocs ?
  const char *mobile = debut_;
  while ((mobile <= fin_) && (*mobile != '{'))
    mobile++;
  if (*mobile != '{')
    return;

  // itérateur sur les sous-blocs dans les limites imposées
  const char* accFerme = debut_ - 1;
  const char* accOuvre = NULL;
  const char* debutNom = NULL;
  const char* apresNom = NULL;

  try 
  {
    while (true)
    { 

      BlocSuivant (nomBloc_.empty () ? "" : nomBloc_.c_str (),
                   nomFichier_, fin_,
                   &accOuvre, &accFerme, &debutNom, &apresNom);

      if ((apresNom - debutNom == 2) && (strncmp (debutNom, "=>", 2) == 0))
      {
        // il s'agit d'un bloc d'indirection, on doit le suivre

        // extraction du nom du bloc d'indirection
        const char* localDebut = accOuvre + 1;
        const char* localFin   = accFerme - 1;
        while (isspace(*localDebut))
          localDebut++;
        while (isspace(*localFin))
          localFin--;
        int longIndirection = ((localFin + 1) < localDebut)
          ? 0 : (localFin + 1 - localDebut);
        string nomIndirect (localDebut, longIndirection);

        // analyse du bloc pointé par l'indirection
        FichierStructure indirect = *this;
        indirect.nomBloc_ = "";
        indirect.debut_   = (char *) total_.memoire ();
        indirect.fin_     = indirect.debut_ + strlen (indirect.debut_) - 1;
        indirect.rechercheSousBloc (nomIndirect,
                                    (const char **) &(indirect.debut_),
                                    (const char **) &(indirect.fin_),
                                    &(indirect.nomBloc_));
        indirect.listeSousBlocs (ptrTable);

      }
      else
      {
        ptrTable->push_back (string (debutNom, apresNom - debutNom));
      }
    }
  }

  catch(ClubErreurs ce)
  {
    if (ce.code () == CodeInconnu)
    {
      // on est arrivé normalement à la fin du bloc
      ce.correction();
    }
    else
    { 
      throw; // Le ClubErreurs ce est déjà renseigné correctement
    }
  }

}
