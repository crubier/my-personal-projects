////////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Type
//       DEF
//
//$Projet
//        Bibam
//$Application
//        Club
//$Nom
//>       TamponBase.cpp
//$Resume
//       fichier d'implantation de la classe TamponBase
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class TamponBase                   
//>         lit () 
//>         ecrit() 
//
//$Historique
//       $Log: TamponBase.cpp,v $
//       Revision 1.6  2003/02/03 13:49:11  club
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.5  2000/10/24 08:33:31  club
//       modification des include standard du C : utilisation de cNAME au lieu de
//       NAME.h (pour permettre la compilation avec le Sun Workshop 5.0)
//
//       Revision 1.4  2000/09/07 08:06:52  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//
//       Revision 1.3  1999/07/07 07:55:17  club
//       Passage a une gestion d'erreurs par exceptions
//
//       Revision 1.2  1999/06/01 15:00:03  club
//       correction de l'indentation
//
//       Revision 1.1  1999/03/15 13:26:36  club
//       version initiale
//
//$Version
//       $Id: TamponBase.cpp,v 1.6 2003/02/03 13:49:11 club Exp $
//$Auteur
//        P-A.Cros   CSSI
//        M. Julien  CSSI 
//        O. Queyrut CSSI
//        Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "club/TamponBase.h"


void TamponBase::lit (FILE* ptrFic )
  throw(ClubErreurs)
{ 
  // préparation du tampon
  if (tailleTampon_ <= 0)
  { 
    if (total_ != 0)
      delete [] total_;
    tailleTampon_ = 512;
    total_        = new char [tailleTampon_];
  }

  // lecture du fichier caractère par caractère
  char* mobile = total_;
  while (fread (mobile, 1, 1, ptrFic) == 1)
  { 
    if (++mobile >= total_ + tailleTampon_)
    { // il faut agrandir le tampon
      mobile         = new char [tailleTampon_ + tailleTampon_];
      (void) strncpy (mobile, total_, tailleTampon_);
      delete [] total_;
      total_         = mobile;
      mobile        += tailleTampon_;
      tailleTampon_ += tailleTampon_;
    }
  }
  *mobile = '\0';
  longueur_ = strlen (total_);  // < taille s'il y a des '\0' dans le fichier

}

void TamponBase::lit (const char* nom )
  throw(ClubErreurs)
{ // ouverture du fichier
  ifstream fichier ((nom && *nom) ? nom : nom_.c_str ());
  if (! fichier.good ())
    throw ClubErreurs( ClubErreurs::ouverture_fichier,
                       ((nom && *nom) ? nom : nom_.c_str ()));

  if (nom && *nom)
    nom_ = nom;

  // recherche de la longueur du fichier
  (void) fichier.seekg (0, ios::end);
  int taille = int (fichier.tellg ()) + 1;

  // préparation du tampon
  if (taille > tailleTampon_)
  { 
    if (total_ != NULL)
    {
      delete [] total_;
    }
    tailleTampon_ = taille;
    total_        = new char [tailleTampon_];
  }


  // lecture du fichier
  (void) fichier.seekg (0, ios::beg);
  (void) fichier.read (total_, taille - 1);
  total_ [taille - 1] = '\0';
  longueur_ = strlen (total_);  // < taille s'il y a des '\0' dans le fichier

}

void TamponBase::ecrit (const char* nom) const 
  throw(ClubErreurs)
{ // ouverture du fichier
  ofstream fichier ((nom && *nom) ? nom : nom_.c_str ());
  if (! fichier.good ())
    throw ClubErreurs(ClubErreurs::ouverture_fichier,
                      ((nom && *nom) ? nom : nom_.c_str ()));

  // écriture dans le fichier
  (void) fichier.write (total_, longueur_);

}
