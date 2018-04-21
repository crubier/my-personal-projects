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
//       Marmottes
//
//$Nom
//>       TableInstances.cpp
//
//$Resume
//       fichier d'implantation des fonctions d'accès à la table d'instances
//
//$Description
//       Module de définition des fonctions d'accès à la table d'instances
//
//$Contenu
//>       Marmottes *InstanceInitialisee()   
//>       void InstanceNonInitialisee()
//
//$Historique
//       $Log: TableInstances.cpp,v $
//       Revision 1.7  2003/02/04 16:42:37  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.6  2000/03/30 17:01:21  luc
//       ajout du copyright CNES
//
//       Revision 1.5  1999/04/23 11:45:39  luc
//       élimination de CopieMessageC
//       utilisation d'exceptions simplifiant InstanceInitialisee
//
//       Revision 1.4  1998/10/05 15:42:25  luc
//       ajout d'un typedef pour aider le compilateur Sun à comprendre une
//       allocation de table de pointeurs
//
//       Revision 1.3  1998/07/31 08:43:19  luc
//       inclusion de MarmottesConfig.h
//
//       Revision 1.2  1998/06/24 20:07:20  luc
//       élimination des variables statiques RCS
//       modification du format des en-têtes
//
//       Revision 1.1  1998/04/29 16:11:42  luc
//       Initial revision
//
//$Version
//       $Id: TableInstances.cpp,v 1.7 2003/02/04 16:42:37 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/TableInstances.h"

// déclaration d'une table statique pour contenir les simulateurs
// (l'élément 0 n'est jamais utilisé, ce numéro sert pour les erreurs)
static Marmottes **tableMarmottes       = 0;
static int         tailleTableMarmottes = 0;

static void EtendreTable ()
{ int nouvelleTailleTable = tailleTableMarmottes ?
                            (tailleTableMarmottes << 1) : 3;
  typedef Marmottes *MarmottesPTR;
  Marmottes **nouvelleTableMarmottes = new MarmottesPTR [nouvelleTailleTable];

  for (int i = 0; i < tailleTableMarmottes; i++)
    nouvelleTableMarmottes [i] = tableMarmottes [i];
  for (int j = tailleTableMarmottes; j < nouvelleTailleTable; j++)
    nouvelleTableMarmottes [j] = new Marmottes;

  if (tailleTableMarmottes)
  { // désallocation de l'ancienne table
    delete [] tableMarmottes;
  }
  tailleTableMarmottes = nouvelleTailleTable;
  tableMarmottes       = nouvelleTableMarmottes;

}

Marmottes *InstanceInitialisee (int ident) throw (MarmottesErreurs)
{ // récupération d'une instance Marmottes dans une table
  if (((ident < 1) || (ident >= tailleTableMarmottes))
      ||
      (! tableMarmottes [ident]->estInitialise ()))
    throw MarmottesErreurs (MarmottesErreurs::id_marmottes_non_initialise,
                            ident);

  return tableMarmottes [ident];

}

void InstanceNonInitialisee (int *ptrIdent, Marmottes **adrPtrInstance)
{ // récupération d'une nouvelle instance Marmottes dans une table
  if (tailleTableMarmottes < 1)
    EtendreTable ();

  *ptrIdent = 1;
  while ((*ptrIdent < tailleTableMarmottes)
         &&
         (tableMarmottes [*ptrIdent]->estInitialise ()))
    (*ptrIdent)++;

  if (*ptrIdent >= tailleTableMarmottes)
    EtendreTable ();

  *adrPtrInstance = tableMarmottes [*ptrIdent];

}
