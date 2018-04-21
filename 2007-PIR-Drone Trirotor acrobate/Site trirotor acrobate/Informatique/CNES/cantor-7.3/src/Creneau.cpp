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
//>       Creneau.cpp
//$Resume
//       fichier d'implantation de la classe Creneau
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class Creneau         
//>         Creneau()           
//>         operator =()        
//>         etendTable()        
//>         inf()               
//>         sup()               
//>         operator []()       
//>         vide()              
//>         contient()          
//>         rencontre()         
//>         disjoint()          
//>         decale()            
//>         operator +=()       
//>         operator -=()       
//>         operator *=()       
//>       Creneau operator *()  
//>       ostream& operator <<()
//$Historique
//       $Log: Creneau.cpp,v $
//       Revision 1.18  2003/02/04 09:27:11  cantor
//       DM-ID 17 Mise à jour du nom du fichier dans le bandeau suite à la modification des extensions.
//
//       Revision 1.17  2002/09/03 15:04:23  cantor
//       surcharge de l'opérateur '-', ajout de constructeurs (FA15)
//
//       Revision 1.16  2001/06/05 15:47:02  cantor
//       utilisation du mécanisme des exceptions pour la gestion des erreurs
//
//       Revision 1.15  2000/08/09 14:36:42  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.14.2.1  2000/03/30 15:36:05  cantor
//       ajout du copyright CNES
//
//       Revision 1.14  1999/08/05 09:54:29  cantor
//       modification résultant du merge entre les versions
//       release-5-0-1 et pre-5-2
//
//       Revision 1.13.2.1  1999/04/26 13:54:26  cantor
//       ajout de la méthode decale
//
//       Revision 1.13  1998/10/05 13:09:11  cantor
//       utilisation des constantes cantorEpsilon et cantorEnorme de cantor/Util.h
//
//       Revision 1.12  1998/10/05 12:35:35  cantor
//       remplacement de la constante DBL_EPSILON par 1.0e-15
//       (pour éviter les problèmes de non-portabilité)
//
//       Revision 1.11  1998/06/24 10:08:51  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.10  1998/04/26 15:23:49  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.9  1998/04/19 18:25:10  luc
//       amélioration d'un message d'erreur
//
//       Revision 1.8  1997/07/06 10:24:01  luc
//       ajout d'un en-tête de fichier
//       remplacement des size_t par des int
//
//       Revision 1.7  1997/03/26 06:54:29  luc
//       changement des conventions de nommage
//       
//       Revision 1.6  1997/03/24 09:32:40  luc
//       passage de SCCS à RCS
//       
//       Revision 1.5  1996/07/16 10:28:23  luc
//       élimination de la dépendance aux tools.h++ (Rogue Wave)
//       (les intervalles sont désormais conservés dans un tableau géré par l'instance)
//       
//       Revision 1.4  1994/12/12 15:14:32  mercator
//       generalisation a toute la biliotheque de l'argument CantorErreurs* optionnel
//       
//       Revision 1.3  1994/11/26 15:16:38  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.2  1994/11/09 16:04:16  mercator
//       remplacement de la fonction "lance" par "erreur"
//       
//       Revision 1.1  1994/07/27 14:53:17  luc
//       Initial revision
//
//$Version
//       $Id: Creneau.cpp,v 1.18 2003/02/04 09:27:11 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "cantor/Creneau.h"
#include "cantor/Util.h"


const int TailleParDefaut = 3;

Creneau::Creneau (const Intervalle& i)
  : tailleTable_ (TailleParDefaut), nbIntervalles_ (1),
    table_ (new Intervalle [tailleTable_])
{ table_ [0] = i; }

Creneau::Creneau (const Intervalle& i1, const Intervalle& i2)
  : tailleTable_ (TailleParDefaut), nbIntervalles_ (0),
    table_ (new Intervalle [tailleTable_])
{
  if (i1.rencontre (i2))
  {
    nbIntervalles_ = 1;
    table_ [0] = Intervalle(min (i1.inf (), i2.inf ()),
                            max (i1.sup (), i2.sup ()));
  }
  else
  {
    nbIntervalles_ = 2;
    if (i1 < i2)
    {
      table_ [0] = i1;
      table_ [1] = i2;
    }
    else
    {
      table_ [0] = i2;
      table_ [1] = i1;
    }
  }
}

Creneau::Creneau (double a, double b)
  : tailleTable_ (TailleParDefaut), nbIntervalles_ (1),
    table_ (new Intervalle [tailleTable_])
{ table_ [0] = Intervalle (a, b); }

Creneau::Creneau (const Creneau& c)
  : tailleTable_ (c.nbIntervalles_), nbIntervalles_ (c.nbIntervalles_),
    table_ (tailleTable_ ? new Intervalle [tailleTable_] : 0)
{ for (int k = 0; k < nbIntervalles_; k++)
  table_ [k] = c.table_ [k];
}

Creneau& Creneau::operator = (const Creneau& c)
{ if (&c != this) // protection contre x = x
  { if (tailleTable_ < c.nbIntervalles_)
    { if (tailleTable_)
        delete [] table_;
      tailleTable_ = c.nbIntervalles_;
      table_       = new Intervalle [tailleTable_];
    }
    nbIntervalles_ = c.nbIntervalles_;
    for (int k = 0; k < nbIntervalles_; k++)
      table_ [k] = c.table_ [k];
  }

  return *this;

}

void Creneau::etendTable ()
{ // allocation d'une nouvelle table plus grande
  int nouvelleTaille = tailleTable_ ? (tailleTable_ << 1) : TailleParDefaut;
  Intervalle *nouvelleTable = new Intervalle [nouvelleTaille];

  // copie de l'ancienne table
  for (int k = 0; k < nbIntervalles_; k++)
    nouvelleTable [k] = table_ [k];

  // remplacement de l'ancienne table
  if (tailleTable_)
    delete [] table_;
  tailleTable_ = nouvelleTaille;
  table_       = nouvelleTable;

}


double Creneau::inf () const
  throw (CantorErreurs)
{
  if (nbIntervalles_ < 1)
    throw CantorErreurs (CantorErreurs::creneau_vide);

  return table_ [0].inf ();

}


double Creneau::sup () const
  throw (CantorErreurs)
{
  if (nbIntervalles_ < 1)
    throw CantorErreurs (CantorErreurs::creneau_vide);

  return table_ [nbIntervalles_ - 1].sup ();

}


const Intervalle& Creneau::operator [] (int i) const
  throw (CantorErreurs)
{  
  if (nbIntervalles_ < 1)
    throw CantorErreurs (CantorErreurs::creneau_vide);
  else if ((i < 0) || (i >= nbIntervalles_))
    throw CantorErreurs (CantorErreurs::indice_hors_bornes,
                         "indice intervalle", i, 0, nbIntervalles_ - 1);

  return table_ [i];

}


// fonctions de test
bool Creneau::vide () const
{ for (int k = 0; k < nbIntervalles_; k++)
    if (table_ [k].longueur () > cantorEpsilon)
      return false;

  return true;
}

bool Creneau::contient (double x) const
{ for (int k = 0; k < nbIntervalles_; k++)
    if (table_ [k].contient (x))
      return true;

  return false;
}

bool Creneau::contient (const Intervalle& i) const
{ for (int k = 0; k < nbIntervalles_; k++)
    if (table_ [k].contient (i))
      return true;

  return false;
}

bool Creneau::rencontre (const Intervalle& i) const
{ for (int k = 0; k < nbIntervalles_; k++)
    if (table_ [k].rencontre (i))
      return true;

  return false;
}

bool Creneau::disjoint (const Intervalle& i) const
{ for (int k = 0; k < nbIntervalles_; k++)
    if (table_ [k].rencontre (i))
      return false;

  return true;
}

void Creneau::decale (double delta)
{ for (int k = 0; k < nbIntervalles_; k++)
    table_ [k].decale (delta);
}


// operations avec des intervalles
Creneau& Creneau::operator += (const Intervalle& i)
{ // recherche du premier intervalle pouvant interagir avec i
  int k = 0;
  while ((k < nbIntervalles_) && (table_ [k] < i))
    k++;

  if (k == nbIntervalles_)
  { // i est au delà du dernier intervalle
    if (nbIntervalles_ == tailleTable_)
      etendTable ();
    table_ [nbIntervalles_++] = i;
    return *this;
  }

  if (i < table_ [k])
  { // i est entre les intervalles k-1 et k (ou avant le premier)
    if (nbIntervalles_ == tailleTable_)
      etendTable ();

    // décalage de la fin de la table
    for (int l = nbIntervalles_; l > k; l--)
      table_ [l] = table_ [l-1];

    // insertion de i
    table_ [k] = i;
    nbIntervalles_++;

    return *this;

  }

  // recherche du dernier intervalle interagissant avec i
  int l = k;
  while ((l+1 < nbIntervalles_) && (table_ [l+1].inf () <= i.sup ()))
    l++;

  // réunion des intervalles en interaction
  table_ [k] = Intervalle (min (table_ [k].inf (), i.inf ()),
                           max (table_ [l].sup (), i.sup ()));

  // copie des intervalles restant
  if (++k < ++l)
  { while (l < nbIntervalles_)
      table_ [k++] = table_ [l++];
    nbIntervalles_ = k;
  }

  return *this;

}

Creneau& Creneau::operator -= (const Intervalle& i)
{
  double a = min (inf (), i.inf ());
  double b = max (sup (), i.sup ());
  Creneau complementaire (Intervalle (a - 1.0, i.inf ()),
                          Intervalle (i.sup (), b + 1.0));
  return operator *= (complementaire);
}

Creneau& Creneau::operator *= (const Intervalle& i)
{ // saut des intervalles en deçà de i
  int k = 0;
  while ((k < nbIntervalles_) && (table_ [k] < i))
    k++;

  // copie des intervalles interagissant avec i
  int l = 0;
  while ((k < nbIntervalles_) && (table_ [k].inf () <= i.sup ()))
    table_ [l++] = table_ [k++] * i;
  nbIntervalles_ = l;

  return *this;

}


// operations entre creneaux
Creneau& Creneau::operator += (const Creneau& c)
{ for (int k = 0; k < c.nbIntervalles_; k++)
    *this += c.table_ [k];
  return *this;
}

Creneau& Creneau::operator -= (const Creneau& c)
{ for (int k = 0; k < c.nbIntervalles_; k++)
    *this -= c.table_ [k];
  return *this;
}

Creneau operator * (const Creneau& c1, const Creneau& c2)
{ Creneau c;
  for (int k = 0; k < c2.nbIntervalles_; k++)
    c += c1 * c2.table_ [k];
  return c;
}

ostream& operator << (ostream& s, const Creneau& c)
{ int nombre = c.nombre ();

  if (nombre == 0)
    return s << "[]";

  for (int k = 0; k < nombre; k++)
  { s << c [k];
    if (k < nombre - 1)
      s << " U ";
  }

  return s;

}

