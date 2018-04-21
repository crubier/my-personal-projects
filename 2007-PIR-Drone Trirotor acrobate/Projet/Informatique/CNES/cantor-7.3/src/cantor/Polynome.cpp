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
//>       Polynome.cpp
//
//$Resume
//       fichier d'implantation de la classe Polynome
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class Polynome                           
//>         affecter()                             
//>         ajusteDegre()                          
//>         Polynome()                             
//>         operator =()                           
//>         coeff()                                
//>         derivee()                              
//>         derivee()                              
//>         integrale()                            
//>         operator +=()                          
//>         operator -=()                          
//>         operator *=()                          
//>         operator /=()                          
//>         operator()()                           
//>         operator()()                           
//>         zeros()                                
//>         operator -()                           
//>       template <class T> ostream& operator <<()
//
//$Historique
//       $Log: Polynome.cpp,v $
//       Revision 1.19  2003/02/04 09:34:43  cantor
//       DM-ID 17 Mise à jour du nom du fichier dans le bandeau suite à la modification des extensions (CC <- CPP)
//
//       Revision 1.18  2001/06/05 15:29:03  cantor
//       passage au mécanisme des exceptions pour la gestion des erreurs
//
//       Revision 1.17  2000/08/09 14:36:44  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.16.2.1  2000/03/30 17:10:27  cantor
//       ajout du copyright CNES
//
//       Revision 1.16  1999/08/05 09:55:57  cantor
//       modification résultant du merge entre les versions
//       release-5-0-1 et pre-5-2
//
//       Revision 1.15.2.1  1999/04/26 09:37:52  cantor
//       remplacement de abs par fabs
//
//       Revision 1.15  1998/10/05 13:32:53  cantor
//       utilisation des constantes cantorEpsilon et cantorEnorme de cantor/Util.h
//
//       Revision 1.14  1998/06/24 10:05:49  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.13  1998/04/26 15:24:01  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.12  1998/04/19 18:23:47  luc
//       élimination de la méthode estValide
//       élimination de la génération des erreurs sans pointeur
//
//       Revision 1.11  1998/01/22 10:41:09  luc
//       correction de valeurs de retours oubliées dans les opérateurs
//       =, +=, -=, ...
//
//       Revision 1.10  1997/07/06 10:30:33  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.9  1997/03/26 06:39:46  luc
//       changement des conventions de nommage
//       
//       Revision 1.8  1997/03/24 08:53:56  luc
//       remplacement des multiplications entières par des additions
//       prise en compte du renommage de UtilErreurs en ClubErreurs
//       passage de SCCS à RCS
//       
//       Revision 1.7  1996/07/16 10:36:46  luc
//       élimination de la dépendance aux tools.h++ (Rogue Wave)
//       
//       Revision 1.6  1995/06/26 16:32:30  mercator
//       limitation de portee de variables locales a un switch
//       modification de portee de variables de boucles
//       
//       Revision 1.5  1994/12/12 15:14:35  mercator
//       generalisation a toute la biliotheque de l'argument CantorErreurs* optionnel
//       
//       Revision 1.4  1994/11/26 15:16:59  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.3  1994/11/14 08:54:42  mercator
//       correction d'une faute de declaration d'un RWCString
//       
//       Revision 1.2  1994/11/09 16:15:19  mercator
//       transformation de certains operateurs en operateurs membres
//       remplacement de la fonction "lance" par "erreur"
//       
//       Revision 1.1  1994/07/27 14:57:21  luc
//       Initial revision
//
//$Version
//       $Id: Polynome.cpp,v 1.19 2003/02/04 09:34:43 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_Polynome_cc
#define __cantor_Polynome_cc

#include "cantor/Polynome.h"

template <class T>
void Polynome<T>::affecter (const Polynome<T>& p)
{ // copie du degré
  degre_ = p.degre_;

  // copie des coefficients
  for (int i = 0; i <= degre_; i++)
    coeff_ [i] = p.coeff_ [i];

}

template <class T>
void Polynome<T>::ajusteDegre ()
{ while ((degre_ > 0) && (fabs (coeff_ [degre_]) <= T (cantorEpsilon)))
    degre_--;
}

template <class T>
Polynome<T>::Polynome (int degre, const T coeff [])
  throw (CantorErreurs)
{
  if ((degre < 0) || (degre > polynome_max_degre))
    throw CantorErreurs (CantorErreurs::indice_hors_bornes,
                         "degre polynome", degre, 0, polynome_max_degre);
  else
  {
    degre_ = degre;

    for (int i = 0; i <= degre_; i++)
      coeff_ [i] = coeff [i];

    ajusteDegre ();

  }
}

template <class T>
Polynome<T>::Polynome (const Polynome<T>& p)
{ affecter (p); }

template <class T>
Polynome<T>& Polynome<T>::operator = (const Polynome<T>& p)
{ if (&p != this)   // protection contre l'affectation p = p
    affecter (p);
  return *this;
}

template <class T>
T Polynome<T>::coeff (int i) const
  throw (CantorErreurs)
{
  if ((i < 0) || (i > degre_))
    throw CantorErreurs (CantorErreurs::indice_hors_bornes,
                         "degre coefficient", i, 0, degre_);

  return coeff_ [i];

}

template <class T>
T Polynome<T>::derivee (const T& x) const
  throw (CantorErreurs)
{
  if ((degre_ < 0) || (degre_ > polynome_max_degre))
    throw CantorErreurs (CantorErreurs::polynome_invalide);

  T y = coeff_ [degre_] * degre_;
  for (int i = degre_ - 1; i >= 1; i--)
  { y *= x;
    y += coeff_ [i] * i;
  }

  return y;

}

template <class T>
Polynome<T> Polynome<T>::derivee () const
  throw (CantorErreurs)
{
  if ((degre_ < 0) || (degre_ > polynome_max_degre))
    throw CantorErreurs (CantorErreurs::polynome_invalide);

  T coeff [polynome_max_degre];  // polynome_max_degre suffit dans ce cas !!

  // calcul des coefficients du polynôme dérivée
  for (int i = 1; i <= degre_; i++)
    coeff [i-1] = coeff_ [i] * i;

  // construction du polynôme à partir de son tableau de coefficients
  return Polynome<T> (degre_ - 1, coeff);

}

template <class T>
Polynome<T> Polynome<T>::integrale (const T& y, const T& x) const
  throw (CantorErreurs)
{
  if (degre_ > polynome_max_degre - 1)
    throw CantorErreurs (CantorErreurs::indice_hors_bornes,
                         "degre polynome",
                         degre_ + 1, 0, polynome_max_degre);

  // calcul des coefficients du polynôme intégrale
  T coeff [polynome_max_degre + 1];
  coeff [0] = T (0.0);
  for (int i = 0; i <= degre_; i++)
    coeff [i+1] = coeff_ [i] / (i+1);

  // construction du polynôme à partir de son tableau de coefficients
  Polynome<T> p (degre_ + 1, coeff);

  // ajustement de la constante d'intégration pour avoir P (x) = y
  p.coeff_ [0] += y - p (x);

  return p;

}

template <class T>
Polynome<T>& Polynome<T>::operator += (const Polynome<T>& p)
{ // addition des monômes communs aux deux polynômes
  int i;
  for (i = 0; i <= min (degre_, p.degre_); i++)
    coeff_ [i] += p.coeff_ [i];

  // prise en compte des monômes n'appartenant qu'au deuxième polynôme
  for (i = min (degre_, p.degre_) + 1; i <= p.degre_; i++)
    coeff_ [i] = p.coeff_ [i];

  // mise à jour du degré
  degre_ = max (degre_, p.degre_);
  ajusteDegre ();

  return *this;

}

template <class T>
Polynome<T>& Polynome<T>::operator -= (const Polynome<T>& p)
{ // soustraction des monômes communs aux deux polynômes
  int i;
  for (i = 0; i <= min (degre_, p.degre_); i++)
    coeff_ [i] -= p.coeff_ [i];

  // prise en compte des monômes n'appartenant qu'au deuxième polynôme
  for (i = min (degre_, p.degre_) + 1; i <= p.degre_; i++)
    coeff_ [i] = -p.coeff_ [i];

  // mise à jour du degré
  degre_ = max (degre_, p.degre_);
  ajusteDegre ();

  return *this;

}

template <class T>
Polynome<T>& Polynome<T>::operator *= (const Polynome<T>& p)
  throw (CantorErreurs)
{
  if (degre_ + p.degre_ > polynome_max_degre)
    throw CantorErreurs (CantorErreurs::indice_hors_bornes,
                         "degre polynome", degre_ + p.degre_,
                         0, polynome_max_degre);

  // multiplication (avec réutilisation du tableau coeff_ de l'instance)
  for (int k = degre_ + p.degre_; k >= 0; k--)
  { int j = max (0, k - degre_);
    coeff_ [k] = coeff_ [k-j] * p.coeff_ [j];

    while (++j <= min (p.degre_, k))
      coeff_ [k] += coeff_ [k-j] * p.coeff_ [j];

  }

  // mise à jour du degré
  degre_ += p.degre_;

  return *this;

}

template <class T>
Polynome<T>& Polynome<T>::operator += (const T& c)
{ // ajustement du terme constant
  coeff_ [0] += c;

  ajusteDegre ();

  return *this;

}

template <class T>
Polynome<T>& Polynome<T>::operator -= (const T& c)
{ // ajustement du terme constant
  coeff_ [0] -= c;

  ajusteDegre ();

  return *this;

}

template <class T>
Polynome<T>& Polynome<T>::operator *= (const T& c)
{ // multiplication des coefficients
  for (int i = 0; i <= degre_; i++)
    coeff_ [i] *= c;

  ajusteDegre ();

  return *this;

}

template <class T>
Polynome<T>& Polynome<T>::operator /= (const T& c)
{ // division des coefficients
  for (int i = 0; i <= degre_; i++)
    coeff_ [i] /= c;

  ajusteDegre ();

  return *this;

}

template <class T>
T Polynome<T>::operator () (const T& x) const
  throw (CantorErreurs)
{
  if ((degre_ < 0) || (degre_ > polynome_max_degre))
    throw CantorErreurs (CantorErreurs::polynome_invalide);

  T y = coeff_ [degre_];
  for (int i = degre_ - 1; i >= 0; i--)
  { y *= x;
    y += coeff_ [i];
  }

  return y;

}

template <class T>
Polynome<T> Polynome<T>::operator () (const Polynome<T>& x) const
  throw (CantorErreurs)
{
  if (((degre_ < 0) || (degre_ > polynome_max_degre))
      ||
      ((x.degre_ < 0) || (x.degre_ > polynome_max_degre)))
    throw CantorErreurs (CantorErreurs::polynome_invalide);

  Polynome<T> y (coeff_ [degre_]);
  for (int i = degre_ - 1; i >= 0; i--)
  { y *= x;
    y += coeff_ [i];
  }

  return y;

}

template <class T>
void Polynome<T>::zeros (int* n, T z [], int ordre []) const
  throw (CantorErreurs)
{
  if ((degre_ < 0) || (degre_ > polynome_max_degre))
    throw CantorErreurs (CantorErreurs::polynome_invalide);

  // initialisation des zéros au plus grand réel existant
  for (int i = 0; i < degre_; i++)
  {
    z [i]     = T (cantorEnorme);
    ordre [i] = 0;
  }

  // sélection de la méthode analytique
  switch (degre_)
  { case 0 :
      // pas de zéro: on garde l'initialisation
      *n = 0;
      break;

    case 1 :
      *n        = 1;
      z     [0] = -coeff_ [0] / coeff_ [1];
      ordre [0] = 1;
      break;

    case 2 :
      { // encapsulation du cas pour limiter la portée des variables
        // locales delta2, inverse2, racine2
        T c2_c0_4  = coeff_ [2] * coeff_ [0];
          c2_c0_4 += c2_c0_4;
          c2_c0_4 += c2_c0_4;
        T delta2   = coeff_ [1] * coeff_ [1] - c2_c0_4;
        T inverse2 = T (0.5) / coeff_ [2];
        T racine2  = (inverse2 < 0) ? -sqrt (delta2) : sqrt (delta2);
      
        if (delta2 < -cantorEpsilon)
          *n = 0;
        else
        { z [0] = inverse2 * (-coeff_ [1] - racine2);

          if (delta2 <= cantorEpsilon)
          { *n        = 1;
            ordre [0] = 2;
          }
          else
          { *n        = 2;
            z     [1] = inverse2 * (-coeff_ [1] + racine2);
            ordre [0] = 1;
            ordre [1] = 1;
          }
        }
      }
      break;

    case 3 :
      { // encapsulation du cas pour limiter la portée des variables
        T c3_c3         = coeff_ [3] * coeff_ [3];
        T c2_c2         = coeff_ [2] * coeff_ [2];
        T c1_c3         = coeff_ [1] * coeff_ [3];
        T q_prime       = c1_c3 + c1_c3 + c1_c3 - c2_c2;
        T c0_c3_c3      = coeff_ [0] * c3_c3;
        T r_prime_sur_9 = coeff_ [2] * c1_c3 - c0_c3_c3 - c0_c3_c3 - c0_c3_c3;
        T r_prime       = r_prime_sur_9 + r_prime_sur_9;
          r_prime      += r_prime;
          r_prime      += r_prime;
          r_prime      += r_prime_sur_9;
        T c2_c2_c2      = coeff_ [2] * c2_c2;
          r_prime      -= c2_c2_c2;
          r_prime      -= c2_c2_c2;
        T q_3           = q_prime * q_prime * q_prime;

        T delta3        = q_3 + q_3;
          delta3       += delta3;
          delta3       += r_prime * r_prime;
        if (delta3 <= -cantorEpsilon)
        { // trois racines réelles
          *n = 3;

          // dans ce cas la resolution trigonométrique est plus facile
          T theta    = acos (0.5 * r_prime / sqrt (-q_3));
          T cos_1    = cos (theta / 3.0);
          T cos_cos  = T (-0.5) * cos_1;
          T sin_sin  = sqrt (T (0.75)) * sin (theta / 3.0);
          T cos_2    = cos_cos - sin_sin;
          T cos_3    = cos_cos + sin_sin;
          T racine3  = sqrt (-q_prime);
            racine3 += racine3;
          T inverse3 = T (1.0) / (coeff_ [3] + coeff_ [3] + coeff_ [3]);

          // mise en ordre selon les cosinus
          // (on sait d'emblée que cos_2 < cos_3)
          if (cos_1 <= cos_2)
          { z [0] = inverse3 * (racine3 * cos_1 - coeff_ [2]);
            z [1] = inverse3 * (racine3 * cos_2 - coeff_ [2]);
            z [2] = inverse3 * (racine3 * cos_3 - coeff_ [2]);
          }
          else if (cos_1 <= cos_3)
          { z [0] = inverse3 * (racine3 * cos_2 - coeff_ [2]);
            z [1] = inverse3 * (racine3 * cos_1 - coeff_ [2]);
            z [2] = inverse3 * (racine3 * cos_3 - coeff_ [2]);
          }
          else
          { z [0] = inverse3 * (racine3 * cos_2 - coeff_ [2]);
            z [1] = inverse3 * (racine3 * cos_3 - coeff_ [2]);
            z [2] = inverse3 * (racine3 * cos_1 - coeff_ [2]);
          }

          // correction de l'ordre en fonction du facteur commun
          if (inverse3 < 0)
          { T tempo = z [0];
            z [0]   = z [2];
            z [2]   = tempo;
          }

          // initialisation de l'ordre de multiplicité des racines
          ordre [0] = 1;
          ordre [1] = 1;
          ordre [2] = 1;

        }
        else if (delta3 <= cantorEpsilon)
        { // trois racines réelles, dont au moins deux sont égales

          T inverse3 = T (1.0) / (coeff_ [3] + coeff_ [3] + coeff_ [3]);
          T st       = (r_prime < T( 0.0))
                     ? -pow (T (-0.5) * r_prime, T (1.0 / 3.0))
                     :  pow (T  (0.5) * r_prime, T (1.0 / 3.0));

          if ((st <= -cantorEpsilon) || (st >= cantorEpsilon))
          { *n        = 2;
            z     [0] = inverse3 * (st + st - coeff_ [2]);
            z     [1] = inverse3 * (-st - coeff_ [2]);
            ordre [0] = 1;
            ordre [1] = 2;
            if (z[1] < z [0])
            { T tempo   = z [0];
              z     [0] = z [1];
              z     [1] = tempo;
              ordre [0] = 2;
              ordre [1] = 1;
            }
          }
          else
          { // en fait les trois racines sont égales
            *n        = 1;
            z     [0] = -inverse3 * coeff_ [2];
            ordre [0] = 3;
          }

        }
        else
        { // une racine réelle, et deux complexes conjuguées

          T inverse3 = T (1.0) / (coeff_ [3] +coeff_ [3] +coeff_ [3]);
          T racine3  = sqrt (delta3);
          T s_prime  = (r_prime < -racine3)
                     ? -pow (T (-0.5) * r_prime + racine3, T (1.0 / 3.0))
                     :  pow (T  (0.5) * r_prime + racine3, T (1.0 / 3.0));
          T t_prime  = (r_prime <  racine3)
                     ? -pow (T (-0.5) * r_prime - racine3, T (1.0 / 3.0))
                     :  pow (T  (0.5) * r_prime - racine3, T (1.0 / 3.0));

          *n         = 1;
          z     [0]  = inverse3 * (s_prime + t_prime - coeff_ [2]);
          ordre [0]  = 1;

        }
      }
      break;

    case 4 :
      // ce cas n'a pas encore été codé ...
      throw CantorErreurs (CantorErreurs::erreur_interne,
                           __LINE__, __FILE__);
      break;

    default :
      throw CantorErreurs (CantorErreurs::indice_hors_bornes,
                           "degre polynome", degre_, 0, 4);
      break;

  }

}

template <class T>
Polynome<T> Polynome<T>::operator - () const
{ // changement de signe des coefficients
  T coeff [polynome_max_degre + 1];
  for (int i = 0; i <= degre_; i++)
    coeff [i] = -coeff_ [i];

  return Polynome<T> (degre_, coeff);

}

template <class T>
ostream& operator << (ostream& s, const Polynome<T>& p)
{ // écriture d'un polynôme sur un flot de sortie

  // formatage d'une chaîne
  if (p.degre () == 0)
    return s << "0";
  else
  { for (int i = p.degre (); i >= 0; i--)
    { if ((i < p.degre ()) && (p.coeff (i) > 0))
        s << '+';

      if (i > 0)
        s << p.coeff (i) << " X^" << i << ' ';
      else
        s << p.coeff (i);
    }

    return s;

  }

}

#endif
