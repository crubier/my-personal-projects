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
//>       ValeurDerivee2.h
//
//$Resume
//       fichier d'en-tête de la classe ValeurDerivee2
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class ValeurDerivee2               
//>       ostream& operator <<()             
//>       ValeurDerivee2 sqrt()              
//>       ValeurDerivee2 sin()               
//>       ValeurDerivee2 cos()               
//>       ValeurDerivee2 tan()               
//>       ValeurDerivee2 asin()              
//>       ValeurDerivee2 acos()              
//>       ValeurDerivee2 atan()              
//>       ValeurDerivee2 exp()               
//>       ValeurDerivee2 log()               
//>       ValeurDerivee2 atan2()             
//>       ValeurDerivee2 Approximation()     
//>       inline ValeurDerivee2 operator -() 
//>       inline ValeurDerivee2 operator +() 
//>       inline ValeurDerivee2 operator *() 
//>       inline ValeurDerivee2 operator /() 
//>       inline int operator <()            
//>       inline int operator <=()           
//>       inline int operator >()            
//>       inline int operator >=()           
//>       inline ValeurDerivee2 Composition()
//>       inline ValeurDerivee2 pow()        
//>       inline ValeurDerivee2 fabs()        
//>       inline ValeurDerivee2 max()        
//>       inline ValeurDerivee2 min()        
//
//$Historique
//       $Log: ValeurDerivee2.h,v $
//       Revision 1.15  2002/12/10 15:37:45  cantor
//       DM-ID 12 Ajout d'un destructeur pour prévenir celui créé par le compilateur
//
//       Revision 1.14  2002/12/02 13:49:15  cantor
//       DM-ID 12 Réorganisation des fichiers H de déclaration des classes selon le principe public/protected/private.
//
//       Revision 1.13  2001/02/16 16:11:44  cantor
//       recherche de ostream dans l'espace lexical std
//
//       Revision 1.12  2000/10/24 16:22:18  cantor
//       modification des includes : suppression de .h dans le nom du fichier
//
//       Revision 1.11  2000/08/09 14:36:45  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.10.2.1  2000/03/30 15:36:11  cantor
//       ajout du copyright CNES
//
//       Revision 1.10  1999/08/05 09:56:52  cantor
//       modification résultant du merge entre les versions
//       release-5-0-1 et pre-5-2
//
//       Revision 1.9.2.1  1999/04/26 09:35:49  cantor
//       remplacement de abs par fabs
//
//       Revision 1.9  1998/06/24 16:47:17  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.8  1998/04/26 15:24:13  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.7  1998/01/22 10:45:13  luc
//       amélioration de l'en-tête de classe
//
//       Revision 1.6  1997/07/06 10:36:41  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.5  1997/03/26 06:39:52  luc
//       changement des conventions de nommage
//       
//       Revision 1.4  1997/03/24 09:22:21  luc
//       passage de SCCS à RCS
//       
//       Revision 1.3  1996/05/29 17:37:38  luc
//       utilisation d'un fichier d'inclusion garantissant la définition de M_PI
//       même si la compilation a été faite avec l'option -ansi.
//       
//       Revision 1.2  1994/11/26 15:15:59  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.1  1994/07/27 14:57:17  luc
//       Initial revision
//
//$Version
//       $Id: ValeurDerivee2.h,v 1.15 2002/12/10 15:37:45 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_ValeurDerivee2_h
#define __cantor_ValeurDerivee2_h

#include <iostream>

#include "cantor/CantorConfig.h"
#ifdef HAVE_STREAMS_IN_NAMESPACE_STD
using std::ostream;
#endif
#include "cantor/MathPi.h"
#include "cantor/ValeurDerivee1.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class ValeurDerivee2
//$Resume
//       calcul de valeurs et de dérivées de fonctions quelconques
//
//$Description
//       calcul de différentielle automatique de fonction scalaire
//       jusqu'à l'ordre 2
//
//$Usage
//>     construction : 
//          à partir des premières dérivées (0 par défaut)
//>     utilisation  : 
//>       ValeurDerivee2& operator =         () 
//          affectation
//>       ValeurDerivee2& operator *=        () 
//          retourne une référence sur l'instance après l'avoir
//          modifiée par multiplication
//>       ValeurDerivee2& operator /=        () 
//          retourne une référence sur l'instance après l'avoir
//          modifiée par division
//>       ValeurDerivee2& operator +=        () 
//          retourne une référence sur l'instance après l'avoir
//          modifiée par addition
//>       ValeurDerivee2& operator -=        () 
//          retourne une référence sur l'instance après l'avoir
//          modifiée par soustraction
//>       friend ValeurDerivee2& operator += () 
//          retourne une référence sur l'instance après l'avoir
//          modifiée par addition
//>       friend ValeurDerivee2& operator -= () 
//          retourne une référence sur l'instance après l'avoir
//          modifiée par soustraction
//>       friend ValeurDerivee2& operator *= () 
//          retourne une référence sur l'instance après l'avoir
//          modifiée par multiplication
//>       friend ValeurDerivee2& operator /= () 
//          retourne une référence sur l'instance après l'avoir
//          modifiée par division
//>       double f0                          () 
//          retourne une copie de la valeur de la fonction
//>       double f1                          () 
//          retourne une copie de la dérivée de la fonction
//>       double f2                          () 
//          retourne une copie de la dérivée seconde de la fonction
//>       double taylor                      () 
//          calcul une approximation de taylor de la fonction
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class ValeurDerivee2
{ 

public :

  // constructeur d'un développement limité à partir des premières dérivées
  ValeurDerivee2 (double f0 = 0, double f1 = 0, double f2 = 0)
    : f2_ (f2), f1_ (f1), f0_ (f0)
  {}

  // constructeur par copie et affectation
  ValeurDerivee2    (const ValeurDerivee2& a)
    : f2_ (a.f2_), f1_ (a.f1_), f0_ (a.f0_)
  {}

  ValeurDerivee2& operator = (const ValeurDerivee2& a);

  // destructeur
  ~ValeurDerivee2 () {}

  // fonctions d'accès aux éléments canoniques
  double f0  () const { return f0_; }
  double f1  () const { return f1_; }
  double f2  () const { return f2_; }

  // opérateurs entre développements limités
  ValeurDerivee2& operator += (const ValeurDerivee2& a)
                              { f2_ += a.f2_; f1_ += a.f1_; f0_ += a.f0_;
                                return *this;
                              }
  ValeurDerivee2& operator -= (const ValeurDerivee2& a)
                              { f2_ -= a.f2_; f1_ -= a.f1_; f0_ -= a.f0_;
                                return *this;
                              }
  ValeurDerivee2& operator *= (const ValeurDerivee2& a);
  ValeurDerivee2& operator /= (const ValeurDerivee2& a);

  // formule de taylor
  double          taylor      (double h) const
                              { return f0_ + h * (f1_ + h * f2_ * 0.5); }

  // opérateurs amis (voir les paquetages de combinaisons d'opérateurs)
  friend ValeurDerivee2& operator += (ValeurDerivee2& a, double b);
  friend ValeurDerivee2& operator -= (ValeurDerivee2& a, double b);
  friend ValeurDerivee2& operator *= (ValeurDerivee2& a, double b);
  friend ValeurDerivee2& operator /= (ValeurDerivee2& a, double b);

  friend ValeurDerivee2& operator += (ValeurDerivee2& a,
                                      const ValeurDerivee1& b);
  friend ValeurDerivee2& operator -= (ValeurDerivee2& a,
                                      const ValeurDerivee1& b);
private :

  double f2_;
  double f1_;
  double f0_;

};


// fonction de sortie
ostream& operator <<  (ostream& s, const ValeurDerivee2& d);


// opérateurs arithmétiques non amis (entre ValeurDerivee2)
inline ValeurDerivee2 operator - (const ValeurDerivee2& a)
{ return ValeurDerivee2 (-(a.f0 ()), -(a.f1 ()), -(a.f2 ())); }

inline ValeurDerivee2 operator - (const ValeurDerivee2& a,
                                  const ValeurDerivee2& b)
{ ValeurDerivee2 d = a; d -= b; return d; }

inline ValeurDerivee2 operator + (const ValeurDerivee2& a,
                                  const ValeurDerivee2& b)
{ ValeurDerivee2 d = a; d += b; return d; }

inline ValeurDerivee2 operator * (const ValeurDerivee2& a,
                                  const ValeurDerivee2& b)
{ ValeurDerivee2 d = a; d *= b; return d; }

inline ValeurDerivee2 operator / (const ValeurDerivee2& a,
                                  const ValeurDerivee2& b)
{ ValeurDerivee2 d = a; d /= b; return d; }

inline int operator <  (const ValeurDerivee2& a, const ValeurDerivee2& b)
{ return a.f0 () < b.f0 (); }

inline int operator <= (const ValeurDerivee2& a, const ValeurDerivee2& b)
{ return a.f0 () <= b.f0 (); }

inline int operator >  (const ValeurDerivee2& a, const ValeurDerivee2& b)
{ return a.f0 () > b.f0 (); }

inline int operator >= (const ValeurDerivee2& a, const ValeurDerivee2& b)
{ return a.f0 () >= b.f0 (); }


// composition par une fonction scalaire
inline ValeurDerivee2 Composition (double u0, double u1, double u2,
                                   const ValeurDerivee2& x)
{ return ValeurDerivee2 (u0,
                         u1 * x.f1 (),
                         u1 * x.f2 () + u2 * x.f1 () * x.f1 ());
}

inline ValeurDerivee2 Composition (const ValeurDerivee2& f,
                                   const ValeurDerivee2& x)
{ return ValeurDerivee2 (f.f0 (),
                         f.f1 () * x.f1 (),
                         f.f1 () * x.f2 () + f.f2 () * x.f1 () * x.f1 ());
}


// fonctions mathématiques usuelles
ValeurDerivee2 sqrt  (const ValeurDerivee2& a);
ValeurDerivee2 sin   (const ValeurDerivee2& a);
ValeurDerivee2 cos   (const ValeurDerivee2& a);
ValeurDerivee2 tan   (const ValeurDerivee2& a);
ValeurDerivee2 asin  (const ValeurDerivee2& a);
ValeurDerivee2 acos  (const ValeurDerivee2& a);
ValeurDerivee2 atan  (const ValeurDerivee2& a);
ValeurDerivee2 exp   (const ValeurDerivee2& a);
ValeurDerivee2 log   (const ValeurDerivee2& a);
ValeurDerivee2 atan2 (const ValeurDerivee2& y, const ValeurDerivee2& x);

inline ValeurDerivee2 pow (const ValeurDerivee2& a, const ValeurDerivee2& b)
{ ValeurDerivee2 p = log (a); p *= b; return exp (p); }

inline ValeurDerivee2 fabs (const ValeurDerivee2& a)
{ return (a.f0 () < 0.0) ? -a : a; }

inline ValeurDerivee2 max (const ValeurDerivee2& a, const ValeurDerivee2& b)
{ return (a < b) ? b : a; }

inline ValeurDerivee2 min (const ValeurDerivee2& a, const ValeurDerivee2& b)
{ return (a < b) ? a : b; }


// approximation polynômiale
ValeurDerivee2 Approximation (const ValeurDerivee2& t,
                              const ValeurDerivee2& ta,
                              const ValeurDerivee2& fa,
                              const ValeurDerivee2& tb,
                              const ValeurDerivee2& fb);

#endif
