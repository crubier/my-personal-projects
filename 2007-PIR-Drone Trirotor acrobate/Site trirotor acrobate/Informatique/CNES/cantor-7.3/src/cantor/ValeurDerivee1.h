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
//>       ValeurDerivee1.h
//
//$Resume
//       fichier d'en-tête de la classe ValeurDerivee1
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class ValeurDerivee1               
//>       ostream& operator <<()             
//>       ValeurDerivee1 sqrt()              
//>       ValeurDerivee1 sin()               
//>       ValeurDerivee1 cos()               
//>       ValeurDerivee1 tan()               
//>       ValeurDerivee1 asin()              
//>       ValeurDerivee1 acos()              
//>       ValeurDerivee1 atan()              
//>       ValeurDerivee1 exp()               
//>       ValeurDerivee1 log()               
//>       ValeurDerivee1 atan2()             
//>       ValeurDerivee1 Approximation()     
//>       inline ValeurDerivee1 operator -() 
//>       inline ValeurDerivee1 operator +() 
//>       inline ValeurDerivee1 operator *() 
//>       inline ValeurDerivee1 operator /() 
//>       inline int operator <()            
//>       inline int operator <=()           
//>       inline int operator >()            
//>       inline int operator >=()           
//>       inline ValeurDerivee1 Composition()
//>       inline ValeurDerivee1 pow()        
//>       inline ValeurDerivee1 fabs()        
//>       inline ValeurDerivee1 max()        
//>       inline ValeurDerivee1 min()        
//
//$Historique
//       $Log: ValeurDerivee1.h,v $
//       Revision 1.15  2002/12/10 15:37:11  cantor
//       DM-ID 12 Ajout d'un destructeur pour prévenir celui créé par le compilateur
//
//       Revision 1.14  2002/12/02 13:49:03  cantor
//       DM-ID 12 Réorganisation des fichiers H de déclaration des classes selon le principe public/protected/private.
//
//       Revision 1.13  2001/02/16 16:12:04  cantor
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
//       Revision 1.9.2.1  1999/04/26 09:35:32  cantor
//       remplacement de abs par fabs
//
//       Revision 1.9  1998/06/24 16:46:30  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.8  1998/04/26 15:24:11  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.7  1998/01/22 10:44:59  luc
//       amélioration de l'en-tête de classe
//
//       Revision 1.6  1997/07/06 10:36:33  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.5  1997/03/26 06:39:51  luc
//       changement des conventions de nommage
//       
//       Revision 1.4  1997/03/24 09:22:20  luc
//       passage de SCCS à RCS
//       
//       Revision 1.3  1996/05/29 17:37:14  luc
//       utilisation d'un fichier d'inclusion garantissant la définition de M_PI
//       même si la compilation a été faite avec l'option -ansi.
//       
//       Revision 1.2  1994/11/26 15:15:53  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.1  1994/07/27 14:57:16  luc
//       Initial revision
//
//$Version
//       $Id: ValeurDerivee1.h,v 1.15 2002/12/10 15:37:11 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_ValeurDerivee1_h
#define __cantor_ValeurDerivee1_h

#include <iostream>

#include "cantor/CantorConfig.h"
#ifdef HAVE_STREAMS_IN_NAMESPACE_STD
using std::ostream;
#endif
#include "cantor/MathPi.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class ValeurDerivee1
//
//$Resume
//       calcul de valeurs et de dérivée première de fonctions quelconques
//
//$Description
//       calcul de différentielle automatique de fonction scalaire
//       jusqu'à l'ordre 1
//
//$Usage
//>     construction : 
//          à partir des premières dérivées (0 par défaut)
//>     utilisation  : 
//>       ValeurDerivee1& operator =         () 
//          affectation
//>       ValeurDerivee1& operator *=        () 
//          retourne une référence sur l'instance après l'avoir
//          modifiée par multiplication
//>       ValeurDerivee1& operator /=        () 
//          retourne une référence sur l'instance après l'avoir
//          modifiée par division
//>       ValeurDerivee1& operator +=        () 
//          retourne une référence sur l'instance après l'avoir
//          modifiée par addition
//>       ValeurDerivee1& operator -=        () 
//          retourne une référence sur l'instance après l'avoir
//          modifiée par soustraction
//>       friend ValeurDerivee1& operator += () 
//          retourne une référence sur l'instance après l'avoir
//          modifiée par addition
//>       friend ValeurDerivee1& operator -= () 
//          retourne une référence sur l'instance après l'avoir
//          modifiée par soustraction
//>       friend ValeurDerivee1& operator *= () 
//          retourne une référence sur l'instance après l'avoir
//          modifiée par multiplication
//>       friend ValeurDerivee1& operator /= () 
//          retourne une référence sur l'instance après l'avoir
//          modifiée par division
//>       double f0                          () 
//          retourne une copie de la valeur de la fonction
//>       double f1                          () 
//          retourne une copie de la dérivée de la fonction
//>       double taylor                      () 
//          calcul une approximation de taylor de la fonction
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class ValeurDerivee1
{ 

public :

  // constructeur d'un développement limité à partir des premières dérivées
  ValeurDerivee1    (double f0 = 0, double f1 = 0) : f1_ (f1), f0_ (f0)  {}

  // constructeur par copie et affectation
  ValeurDerivee1    (const ValeurDerivee1& a) : f1_ (a.f1_), f0_ (a.f0_) {}
  ValeurDerivee1& operator = (const ValeurDerivee1& a);

  // destructeur
  ~ValeurDerivee1 () {}

  // fonctions d'accès aux éléments canoniques
  double f0       () const    { return f0_; }
  double f1       () const    { return f1_; }

  // opérateurs entre ValeurDerivee1
  ValeurDerivee1& operator += (const ValeurDerivee1& a)
                              { f1_ += a.f1_; f0_ += a.f0_; return *this; }
  ValeurDerivee1& operator -= (const ValeurDerivee1& a)
                              { f1_ -= a.f1_; f0_ -= a.f0_; return *this; }
  ValeurDerivee1& operator *= (const ValeurDerivee1& a);
  ValeurDerivee1& operator /= (const ValeurDerivee1& a);

  // formule de taylor
  double          taylor      (double h) const { return f0_ + h * f1_; }

  // opérateurs amis (voir les paquetages de combinaisons d'opérateurs)
  friend ValeurDerivee1& operator += (ValeurDerivee1& a, double b);
  friend ValeurDerivee1& operator -= (ValeurDerivee1& a, double b);
  friend ValeurDerivee1& operator *= (ValeurDerivee1& a, double b);
  friend ValeurDerivee1& operator /= (ValeurDerivee1& a, double b);

private :

  double f1_;
  double f0_;

};


// fonction de sortie
ostream& operator <<  (ostream& s, const ValeurDerivee1& d);


// opérateurs arithmétiques non amis (entre ValeurDerivee1)
inline ValeurDerivee1 operator - (const ValeurDerivee1& a)
{ return ValeurDerivee1 (-(a.f0 ()), -(a.f1 ())); }

inline ValeurDerivee1 operator - (const ValeurDerivee1& a,
                                  const ValeurDerivee1& b)
{ ValeurDerivee1 d = a; d -= b; return d; }

inline ValeurDerivee1 operator + (const ValeurDerivee1& a,
                                  const ValeurDerivee1& b)
{ ValeurDerivee1 d = a; d += b; return d; }

inline ValeurDerivee1 operator * (const ValeurDerivee1& a,
                                  const ValeurDerivee1& b)
{ ValeurDerivee1 d = a; d *= b; return d; }

inline ValeurDerivee1 operator / (const ValeurDerivee1& a,
                                  const ValeurDerivee1& b)
{ ValeurDerivee1 d = a; d /= b; return d; }

inline int operator <  (const ValeurDerivee1& a, const ValeurDerivee1& b)
{ return a.f0 () < b.f0 (); }

inline int operator <= (const ValeurDerivee1& a, const ValeurDerivee1& b)
{ return a.f0 () <= b.f0 (); }

inline int operator >  (const ValeurDerivee1& a, const ValeurDerivee1& b)
{ return a.f0 () > b.f0 (); }

inline int operator >= (const ValeurDerivee1& a, const ValeurDerivee1& b)
{ return a.f0 () >= b.f0 (); }


// composition par une fonction scalaire
inline ValeurDerivee1 Composition (double u0, double u1,
                                   const ValeurDerivee1& x)
{ return ValeurDerivee1 (u0, u1 * x.f1 ()); }

inline ValeurDerivee1 Composition (const ValeurDerivee1& f,
                                   const ValeurDerivee1& x)
{ return ValeurDerivee1 (f.f0 (), f.f1 () * x.f1 ()); }


// fonctions mathématiques usuelles
ValeurDerivee1 sqrt  (const ValeurDerivee1& a);
ValeurDerivee1 sin   (const ValeurDerivee1& a);
ValeurDerivee1 cos   (const ValeurDerivee1& a);
ValeurDerivee1 tan   (const ValeurDerivee1& a);
ValeurDerivee1 asin  (const ValeurDerivee1& a);
ValeurDerivee1 acos  (const ValeurDerivee1& a);
ValeurDerivee1 atan  (const ValeurDerivee1& a);
ValeurDerivee1 exp   (const ValeurDerivee1& a);
ValeurDerivee1 log   (const ValeurDerivee1& a);
ValeurDerivee1 atan2 (const ValeurDerivee1& y, const ValeurDerivee1& x);

inline ValeurDerivee1 pow (const ValeurDerivee1& a, const ValeurDerivee1& b)
{ ValeurDerivee1 p = log (a); p *= b; return exp (p); }

inline ValeurDerivee1 fabs (const ValeurDerivee1& a)
{ return (a.f0 () < 0.0) ? -a : a; }

inline ValeurDerivee1 max (const ValeurDerivee1& a, const ValeurDerivee1& b)
{ return (a < b) ? b : a; }

inline ValeurDerivee1 min (const ValeurDerivee1& a, const ValeurDerivee1& b)
{ return (a < b) ? a : b; }


// approximation polynômiale
ValeurDerivee1 Approximation (const ValeurDerivee1& t,
                              const ValeurDerivee1& ta,
                              const ValeurDerivee1& fa,
                              const ValeurDerivee1& tb,
                              const ValeurDerivee1& fb);

#endif
