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
//>       ChaineSimple.cpp
//
//$Resume
//       fichier d'implantation de la classe ChaineSimple
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       inline short int & EntierCourt()          
//>       inline short int & NombreTotalCellules()  
//>       inline short int & NombreCellulesLibres() 
//>       inline short int & PremiereCelluleLibre() 
//>       inline short int & CellulesBlocCourant()  
//>       inline short int & CellulesBlocPrecedent()
//>       inline char *MemoireUtilisateur()         
//>       static int CreeTampon()                   
//>       static int CelluleReservable()            
//>       static void ReserveChaine()               
//>       static void RestitueChaine()              
//>       class ChaineSimple                        
//>         alloueChaine()                          
//>         etendChaine()                           
//>         ChaineSimple()                          
//>         ~ChaineSimple()                         
//>         reinitialise()                          
//>         formate()                               
//>         vFormate()                              
//>         modifieCaractere()                      
//>         elimineBlancsFinaux()                   
//>         elimineBlancsInitiaux()                 
//>         operator +=()                           
//>         operator()()                            
//
//$Historique
//       $Log: ChaineSimple.cpp,v $
//       Revision 1.20  2003/07/17 12:38:06  club
//       Mise a jour suite aux patchs du 17/07/003
//
//       Revision 1.19  2003/02/03 09:05:10  club
//       DM-ID 17 Changement de l'extension du fichier dans le bandeau
//
//       Revision 1.18  2002/12/10 08:51:42  club
//       DM-ID 12 Modification portant sur l'initialisation des pointeurset des variables.
//
//       Revision 1.17  2000/10/24 08:33:29  club
//       modification des include standard du C : utilisation de cNAME au lieu de
//       NAME.h (pour permettre la compilation avec le Sun Workshop 5.0)
//
//       Revision 1.16  2000/08/30 14:20:44  club
//       Ajout du '\0' à la fin de la ChaineSimple construite à partir d'un string STL.
//
//       Revision 1.15  2000/08/25 07:43:13  club
//       Ajout du constructeur de ChaineSimple à partir d'un string.
//
//       Revision 1.14  2000/07/03 08:57:18  club
//       Ajout du copyright CNES
//
//       Revision 1.13.2.2  2000/03/30 14:46:46  club
//       ajout du copyright CNES
//
//       Revision 1.13.2.1  2000/03/30 11:23:14  club
//       élimination d'une portion de code optionnelle posant
//       des problèmes de droits de distribution
//
//       Revision 1.13  1999/03/15 13:15:41  club
//       modification lors de la réinitialisation d'une chaîne simple, si la chaîne
//       n'existe pas elle est allouée automatiquement
//
//       Revision 1.12  1998/07/27 10:13:40  club
//       passage à une configuration de type GNU (fichier ClubConfig.h généré)
//
//       Revision 1.11  1998/06/24 08:43:39  luc
//       correction d'un écrasement mémoire lors des libérations de chaînes
//
//       Revision 1.10  1998/06/21 15:53:34  luc
//       modification du format de l'en-tête
//       élimination de la chaîne statique RCS
//
//       Revision 1.9  1998/04/26 13:02:19  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.8  1998/01/22 08:20:14  luc
//       initialisation d'une variable pour supprimer un avertissement
//
//       Revision 1.7  1997/10/14 16:44:42  luc
//       accélération de la recherche des cellules libres contiguës
//       passage par un typedef pour faciliter le travail du compilateur SUN
//
//       Revision 1.6  1997/08/21 16:48:10  luc
//       ajout d'un en-tête de fichier
//       prise en compte des '\0' pouvant être contenus dans une chaîne
//       dont on donne explicitement une longueur plus grande
//       constructeur ChaineSimple::ChaineSimple (const char *chaine, int longueur)
//
//       Revision 1.5  1997/04/28 14:18:18  luc
//       correction d'une longueur de copie
//       
//       Revision 1.4  1997/04/27 17:15:04  luc
//       allocation du tampon d'écriture de ChaineSimple::vFormate
//       uniquement au premier appel
//       
//       Revision 1.3  1997/03/25 14:45:44  luc
//       ajout d'une méthode vFormate prenant un argument de type va_list
//       changement des règles de nommage
//       
//       Revision 1.2  1997/03/19 15:13:44  luc
//       ajout d'un niveau intermédiaire pour la gestion mémoire
//       entre les chaînes de caractères et les opérateurs new/delete
//       
//       Revision 1.1  1997/03/16 18:09:59  luc
//       Initial revision
//
//$Version
//       $Id: ChaineSimple.cpp,v 1.20 2003/07/17 12:38:06 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "club/ChaineSimple.h"

// gestion de la mémoire par allocation de plusieurs tampons
// et distribution de cellules de taille fixe dans ces tampons
static int    TailleTable       = 0;
static char **TableTampons      = 0;

// avec 250 cellules de 16 octets plus une cellule pour la gestion,
// les tampons minimaux occuperont 4000 octets, même en comptant large
// les opérateurs new et les éventuels malloc sous-jacents peuvent ajouter
// leur mémoire de gestion tout en restant dans une page de 4096 octets.
const  int    TailleCellule     = 16;
const  int    NombreCellulesMin = 250;

// les tampons sont des zones contiguës de cellules toutes de même
// taille, la première cellule est réservée à la gestion du tampon
// elle contient le nombre total de cellules (sans compter la
// première) et le nombre de cellules libres ; lorsque de la mémoire
// est attribuée à l'utilisateur, le nombre de cellules concernées et
// le nombre de cellules du bloc précédent sont stockés dans deux
// entiers courts au début de la première cellule, on attribue donc
// toujours une taille de la forme k * tc - 2 * s, où tc est la taille
// d'une cellule et s la taille d'un entier court
inline short int & EntierCourt (int i, int decalage)
{ return *((short int *) (TableTampons [i] + decalage)); }


// informations globales du tampon d'index i
inline short int & NombreTotalCellules (int i)
{ return EntierCourt (i, 0); }

inline short int & NombreCellulesLibres (int i)
{ return EntierCourt (i, sizeof(short int)); }

inline short int & PremiereCelluleLibre (int i)
{ return EntierCourt (i, 2 * sizeof(short int)); }


// information pour le bloc commençant à la cellule c du tampon i
// (attention, les nombres de cellules sont positifs si les blocs
//  contiennent des données, et négatifs si les blocs sont libres)
inline short int & CellulesBlocCourant (int i, int c)
{ return EntierCourt (i, (c + 1) * TailleCellule); }

inline short int & CellulesBlocPrecedent (int i, int c)
{ return EntierCourt (i, (c + 1) * TailleCellule + sizeof(short int)); }

inline char *MemoireUtilisateur (int i, int c)
{ return TableTampons [i] + (c + 1) * TailleCellule + 2 * sizeof(short int); }


static int CreeTampon (int nombreCellules)
{ // création d'un tampon contenant au moins un nombre de cellules donné
  if (nombreCellules < NombreCellulesMin)
    nombreCellules = NombreCellulesMin;

  int i, index = -1;

  // recherche d'une entrée disponible dans la table
  for (i = 0; (i < TailleTable) && (index < 0); i++)
    if (TableTampons [i] == 0)
      index = i;

  if (index < 0)
  { // la table est pleine (ou inexistante), il faut l'étendre
    typedef char *CharPTR;
    int    nouvelleTaille = TailleTable ? (TailleTable << 1) : 8;
    char **nouvelleTable  = new CharPTR [nouvelleTaille];

    for (i = 0; i < TailleTable; i++)
      nouvelleTable [i] = TableTampons [i];
    for (i = TailleTable; i < nouvelleTaille; i++)
      nouvelleTable [i] = 0;

    // mémorisation de la première entrée libre
    index = TailleTable;

    // mise en place de la nouvelle table
    if (TailleTable)
      delete [] TableTampons;
    TailleTable  = nouvelleTaille;
    TableTampons = nouvelleTable;

  }

  // allocation du tampon
  TableTampons [index] = new char [(1 + nombreCellules) * TailleCellule];

  // initialisation du tampon
  NombreTotalCellules   (index)    = nombreCellules;
  NombreCellulesLibres  (index)    = nombreCellules;
  PremiereCelluleLibre  (index)    = 0;
  CellulesBlocCourant   (index, 0) = -nombreCellules;
  CellulesBlocPrecedent (index, 0) = 0;

  return index;

}

static int CelluleReservable (int index, int nombreCellules)
{ // recherche d'une zone de cellules libres contiguës
  int cellule        = PremiereCelluleLibre (index);
  int cellulesLibres = NombreCellulesLibres (index);

  while (nombreCellules <= cellulesLibres)
  { // test de la cellule courante
    int reservees = CellulesBlocCourant (index, cellule);

    if (reservees > 0)
    { // il y a des cellules réservées ici, on les évite
      cellule += reservees;
    }
    else
    { // il y a des cellules libres
      if (nombreCellules > -reservees)
      { // le trou est trop petit
        cellule        += -reservees;
        cellulesLibres +=  reservees;
      }
      else
        return cellule;
    }

  }

  // il n'y a pas de zone utilisable
  return -1;

}

static void ReserveChaine (int tailleRequise,
                           int *ptrTailleReservee, char **ptrChaine)
{ // réservation d'espace dans les tampons pour stocker une chaîne
  if (tailleRequise < 0)
    tailleRequise = 0;

  int nombreCellules = (tailleRequise + 2 * sizeof(short int)
                      + TailleCellule - 1) / TailleCellule;

  // recherche de cellules libres contiguës dans les tampons
  int cellule = -1, index = -1;
  for (int i = 0; (i < TailleTable) && (index < 0); i++)
  { // parcours de la table

    if (TableTampons [i] != 0)
    { // peut-on réserver une zone dans ce tampon ?
      cellule = CelluleReservable (i, nombreCellules);
      if (cellule >= 0)
        index = i; // le couple (i, cellule) convient, on arrête la recherche
    }

  }

  if (index < 0)
  { // aucun tampon ne disposait des cellules nécessaires : on en crée un
    index   = CreeTampon (nombreCellules);
    cellule = PremiereCelluleLibre (index);
  }

  // réservation des cellules
  int reste = (-CellulesBlocCourant (index, cellule)) - nombreCellules;
  if (reste > 0)
  { // on ne prend qu'une partie d'un bloc libre
    if (cellule + nombreCellules + reste < NombreTotalCellules (index))
      CellulesBlocPrecedent (index, cellule + nombreCellules + reste) = -reste;
    CellulesBlocCourant   (index, cellule + nombreCellules) = -reste;
  }

  if (cellule + nombreCellules < NombreTotalCellules (index))
    CellulesBlocPrecedent (index, cellule + nombreCellules) = nombreCellules;
  CellulesBlocCourant (index, cellule) = nombreCellules;

  // mise à jour du tampon
  NombreCellulesLibres (index) -= nombreCellules;
  if (cellule == PremiereCelluleLibre (index))
    PremiereCelluleLibre (index) = CelluleReservable (index, 1);

  // affectation des variables de l'appelant
  *ptrTailleReservee = nombreCellules * TailleCellule - 2 * sizeof(short int);
  *ptrChaine         = MemoireUtilisateur (index, cellule);

}

static void RestitueChaine (char *chaine)
{ // restitution de mémoire
  // cette fonction ne marche QUE si la chaîne provient d'un ReserveChaine

  // recherche du tampon contenant la chaîne
  int index = 0;
  while ((TableTampons [index] == 0)
         ||
         (MemoireUtilisateur (index, 0) > chaine)
         ||
         (MemoireUtilisateur (index,
                              NombreTotalCellules (index) - 1) < chaine))
    index++;

  // récupération des éléments de gestion du tampon
  int nombreTotal    = NombreTotalCellules (index);
  int cellule        = (chaine - TableTampons [index]) / TailleCellule - 1;
  int nombreRestitue = CellulesBlocCourant (index, cellule);

  if (NombreCellulesLibres (index) + nombreRestitue == nombreTotal)
  { // on doit libérer la totalité du tampon : on le rend au système
    delete [] TableTampons [index];
    TableTampons [index] = 0;
  }
  else
  { // il reste des chaînes allouées dans le tampon : on le met à jour
    int tailleBloc = nombreRestitue;

    if (cellule + nombreRestitue < nombreTotal)
    { // analyse du bloc suivant le bloc restitué
      int cellulesSuivant = CellulesBlocCourant (index,
                                                 cellule + nombreRestitue);

      // si le bloc suivant est un trou, on l'incorpore au bloc courant
      if (cellulesSuivant < 0)
        tailleBloc += -cellulesSuivant;

    }

    // analyse du bloc précédant le bloc restitué
    int cellulesPrecedant = CellulesBlocPrecedent (index, cellule);

    // si le bloc précédant est un trou, on l'incorpore au bloc courant
    if (cellulesPrecedant < 0)
    { tailleBloc += -cellulesPrecedant;
      cellule    +=  cellulesPrecedant;
    }

    // transformation du bloc alloué en bloc libre
    CellulesBlocCourant (index, cellule) = -tailleBloc;
    if (cellule + tailleBloc < nombreTotal)
      CellulesBlocPrecedent (index, cellule + tailleBloc) = -tailleBloc;

    // mise à jour des compteurs globaux du tampon
    NombreCellulesLibres (index) += nombreRestitue;
    short int premiere = PremiereCelluleLibre (index);
    if ((premiere < 0) || (premiere > cellule))
      PremiereCelluleLibre (index) = cellule;

  }

}

void ChaineSimple::alloueChaine (int taille)
{ // allocation d'une chaîne d'au moins taille caractères
  ReserveChaine (taille, &taille_, &chaine_);

  // mise en place d'un chien de garde pour la méthode modifieCaractere 
  chaine_ [taille_ - 1] = '\0';

  // initialisation de la chaîne
  chaine_ [0]           = '\0';
  longueur_             = 0;

}

void ChaineSimple::etendChaine (int taille)
{ // extension du tableau de mémorisation d'une chaîne

  // préparation d'un nouveau tableau
  int   nouvelleTaille = 0;
  char *nouvelleChaine = NULL;
  ReserveChaine (taille, &nouvelleTaille, &nouvelleChaine);

  // mise en place d'un chien de garde pour la méthode modifieCaractere 
  nouvelleChaine [nouvelleTaille - 1] = '\0';

  // copie de l'ancienne chaîne
  (void) memcpy ((void *) nouvelleChaine, (void *) chaine_, 1 + longueur_);

  // élimination du tableau précédent
  RestitueChaine (chaine_);

  // remplacement
  taille_ = nouvelleTaille;
  chaine_ = nouvelleChaine;

}

ChaineSimple::ChaineSimple (const char *chaine)
{ // création à partir d'une chaîne constante
  if (chaine)
  { // il y a bien une chaîne
    int longueur = strlen (chaine);
    alloueChaine (1 + longueur);
    longueur_    = longueur;
    (void) memcpy ((void *) chaine_, (void *) chaine, 1 + longueur_);
  }
  else
    alloueChaine (-1);

}

ChaineSimple::ChaineSimple (const char *chaine, int longueur)
{ // création à partir d'un tronçon (éventuellement vide) de chaîne constante
  alloueChaine (1 + longueur);

  if (chaine)
  { // il y a bien une chaîne
    if (longueur)
      (void) memcpy ((void *) chaine_, (void *) chaine, longueur);

    // recherche d'un éventuel '\0' avant la fin de la chaîne
    longueur_ = 0;
    while ((longueur_ < longueur) && (chaine_ [longueur_] != '\0'))
      longueur_++;

  }
  else
    longueur_ = 0;

  chaine_ [longueur_] = '\0';

}

ChaineSimple::ChaineSimple (char caractere, int repetitions)
{ // création par duplication d'un caractère
  alloueChaine (1 + repetitions);

  longueur_ = repetitions;

  char *ptr = chaine_;
  while (repetitions-- > 0)
    *ptr++ = caractere;

  chaine_ [longueur_] = '\0';

}

ChaineSimple::ChaineSimple (const ChaineSimple& c)
{ alloueChaine (1 + c.longueur_);
  longueur_ = c.longueur_;
  (void) strcpy (chaine_, c.chaine_);
}

ChaineSimple::ChaineSimple (const string& c)
{ alloueChaine (1 + c.size ());
  longueur_ = c.size ();
  for (int i=0 ; i<longueur_ ; i++)
    chaine_[i] = c[i];
  chaine_ [longueur_] = '\0';
}

ChaineSimple::~ChaineSimple ()
{ // nettoyage de l'instance
  RestitueChaine (chaine_);
}

void ChaineSimple::reinitialise (const ChaineSimple& c)
{ // réaffectation à partir d'une autre instance

  if (this != &c)     // protection contre x.reinitialise (x)
  { // on doit copier tous les caractères stockés au cas où
    // l'utilisateur ait inséré un '\0' en plein milieu de sa chaîne
    // avec modifieCaractere (i, '\0') et qu'il désire malgré tout
    // pouvoir reconstruire la chaîne complète initiale

    // vérification de la place nécessaire
    if (taille_ < c.taille_)
    {
      if( !chaine_ )
        alloueChaine( c.taille_ );
      else
        etendChaine (c.taille_);
    }

    // copie
    (void) memcpy ((void *) chaine_, (void *) c.chaine_, c.taille_);
    longueur_ = c.longueur_;

  }

}

void ChaineSimple::reinitialise (const char *chaine)
{ // réaffectation à partir d'une chaîne brute
  if (chaine)
  { // taille nécessaire en comptant le '\0' final
    int tailleNecessaire = 1 + strlen (chaine);
  
    // vérification de la place nécessaire

    if ((taille_ < tailleNecessaire) || (!chaine_)){
      if( !chaine_ )
        alloueChaine( tailleNecessaire );
      else
        etendChaine (tailleNecessaire);
    }    

    // copie
    (void) memcpy ((void *) chaine_, (void *) chaine, tailleNecessaire);
    longueur_ = tailleNecessaire - 1;

  }
  else
  { // il n'y a pas de chaîne brute
    chaine_ [0] = '\0';
    longueur_   = 0;
  }
}

void ChaineSimple::reinitialise (const char *chaine, int longueur)
{ // réaffectation à partir d'un tronçon (éventuellement vide) de chaîne

  // vérification de la place nécessaire
  int tailleNecessaire = longueur + 1;
  if (taille_ < tailleNecessaire)
    if( !chaine_ )
      alloueChaine( tailleNecessaire );
    else
      etendChaine (tailleNecessaire);

  if (chaine)
  { // il y a bien une chaîne
    if (longueur)
      (void) memcpy ((void *) chaine_, (void *) chaine, longueur);
  }
  else
    longueur = 0;

  chaine_ [longueur] = '\0';
  longueur_ = strlen (chaine_); // indispensable s'il y a des '\0' inclus

}

void ChaineSimple::reinitialise (char caractere, int repetitions)
{ // réaffectation par duplication d'un caractère

  // vérification de la place nécessaire
  int tailleNecessaire = repetitions + 1;
  if (taille_ < tailleNecessaire)
    if( !chaine_ )
      alloueChaine( tailleNecessaire );
    else
      etendChaine (tailleNecessaire);

  longueur_ = repetitions;

  char *ptr = chaine_;
  while (repetitions-- > 0)
    *ptr++ = caractere;

  chaine_ [longueur_] = '\0';

}

void ChaineSimple::formate (const char *f ...)
{ // écrit dans l'instance à l'aide d'un format C
  va_list    ap;

  // initialisation du traitement des arguments variables
  va_start(ap, f);

  vFormate (f, ap);

  // fin de récupération des arguments d'appel
  va_end(ap);

}

void ChaineSimple::vFormate (const char *f, va_list ap)
{ // écrit dans l'instance à l'aide d'un format C

  // écriture dans un tampon de taille supposée suffisante
  static char *tampon = 0;
  if (tampon == 0)
    tampon = new char [4096];
  (void) vsprintf (tampon, f, ap);

  // recopie du tampon dans l'instance
  *this = tampon;

}

void ChaineSimple::modifieCaractere (int i, char c)
{ // modification du caractère d'index i

  // on autorise la modification dans toute la chaîne stockée,
  // y compris au delà de la fin courante de la chaîne
  if ((i < 0) || (i >= taille_ - 1))
    return;

  // modification
  chaine_ [i] = c;

  // mise à jour de la longueur
  if (c == '\0')
    longueur_ = i;
  else if (i == longueur_)
    longueur_ += strlen (chaine_ + i);

}

void ChaineSimple::elimineBlancsFinaux ()
{ // élimine les blancs finaux

  // blancs finaux
  for (char *mobile = chaine_ + longueur_ - 1; isspace(*mobile); mobile--)
  { // élimination du dernier caractère
    *mobile = '\0';
    longueur_--;
  }

}

void ChaineSimple::elimineBlancsInitiaux ()
{ // élimine les blancs initiaux

  // blancs initiaux
  if (isspace(chaine_ [0]))
  { // comptage des blancs à éliminer
    char *src = chaine_ + 1;
    while (isspace(*src))
      src++;

    // décalage de la fin de chaîne
    char *dst = chaine_;
    while (*src)
      *dst++ = *src++;
    *dst = '\0';

    // correction de la longueur
    longueur_ = dst - chaine_;

  }

}

ChaineSimple& ChaineSimple::operator += (const ChaineSimple& c)
{ // ajout d'une instance à la fin d'une autre

  // vérification de la place nécessaire
  int tailleNecessaire = longueur_ + c.longueur_ + 1;
  if (taille_ < tailleNecessaire)
    etendChaine (tailleNecessaire);

  // copie
  (void) memcpy ((void *) (chaine_ + longueur_), (void *) c.chaine_,
                 1 + c.longueur_);
  longueur_ += c.longueur_;

  return *this;

}

ChaineSimple& ChaineSimple::operator += (const char *chaine)
{ // ajout d'une chaîne à la fin de l'instance

  if (chaine)
  { // il y a une chaîne brute
    int l = strlen (chaine);

    // vérification de la place nécessaire
    int tailleNecessaire = longueur_ + l + 1;
    if (taille_ < tailleNecessaire)
      etendChaine (tailleNecessaire);

    // copie
    (void) memcpy ((void *) (chaine_ + longueur_), (void *) chaine, 1 + l);
    longueur_ += l;

  }

  return *this;

}

ChaineSimple& ChaineSimple::operator += (char c)
{ // ajout d'un caractère à la fin de l'instance

    // vérification de la place nécessaire
    int tailleNecessaire = longueur_ + 2;
    if (taille_ < tailleNecessaire)
      etendChaine (tailleNecessaire);

    // copie
    chaine_ [longueur_++] = c;
    chaine_ [longueur_]   = '\0';

  return *this;

}

ChaineSimple ChaineSimple::operator () (const char *debut,
                                        const char *fin) const
{ // extraction d'une sous-chaîne

  // limitation des pointeurs
  if (debut < chaine_)
    debut = chaine_;
  if (fin > chaine_ + longueur_ - 1)
    fin = chaine_ + longueur_ - 1;

  // création d'une nouvelle instance
  int longueur = fin + 1 - debut;
  ChaineSimple sousChaine (1 + longueur);

  // copie de la sous-chaîne
  (void) memcpy ((void *) sousChaine.chaine_, (void *) debut, longueur);
  sousChaine.chaine_ [longueur] = '\0';
  sousChaine.longueur_ = longueur;

  return sousChaine;

}

ChaineSimple ChaineSimple::operator () (int debut, int fin) const
{ // extraction d'une sous-chaîne

  // limitation des pointeurs
  if (debut < 0)
    debut = 0;
  if (fin > longueur_ - 1)
    fin = longueur_ - 1;

  // création d'une nouvelle instance
  int longueur = fin + 1 - debut;
  ChaineSimple sousChaine (1 + longueur);

  // copie de la sous-chaîne
  (void) memcpy ((void *) sousChaine.chaine_, (void *) (chaine_ + debut),
                 longueur);
  sousChaine.chaine_ [longueur] = '\0';
  sousChaine.longueur_ = longueur;

  return sousChaine;

}

int ChaineSimple::operator == (const char *chaine) const
{ return strcmp (chaine_, chaine) == 0; }

int ChaineSimple::operator == (const ChaineSimple& chaine) const
{ return strcmp (chaine_, chaine.chaine_) == 0; }

int ChaineSimple::operator != (const char *chaine) const
{ return strcmp (chaine_, chaine); }

int ChaineSimple::operator != (const ChaineSimple& chaine) const
{ return strcmp (chaine_, chaine.chaine_); }
