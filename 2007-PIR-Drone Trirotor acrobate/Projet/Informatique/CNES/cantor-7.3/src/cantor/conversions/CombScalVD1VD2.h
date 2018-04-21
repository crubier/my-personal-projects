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
//>       CombScalVD1VD2.h
//
//$Resume
//       fichier d'en-tête des combinaisons d'opérandes CombScalVD1VD2
//
//$Description
//       Module de définition des fonctions "inline"
//
//$Contenu
//>       inline ValeurDerivee2& operator +=()
//>       inline ValeurDerivee2& operator -=()
//>       inline ValeurDerivee2& operator *=()
//>       inline ValeurDerivee2& operator /=()
//>       inline ValeurDerivee2 operator +()  
//>       inline ValeurDerivee2 operator -()  
//>       inline ValeurDerivee2 operator *()  
//>       inline ValeurDerivee2 operator /()  
//>       inline int operator <()             
//>       inline int operator <=()            
//>       inline int operator >()             
//>       inline int operator >=()            
//>       inline ValeurDerivee1& operator +=()
//>       inline ValeurDerivee1& operator -=()
//>       inline ValeurDerivee1& operator *=()
//>       inline ValeurDerivee1& operator /=()
//
//$Historique
//       $Log: CombScalVD1VD2.h,v $
//       Revision 1.8  2000/08/09 14:36:46  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.7.4.1  2000/03/30 15:36:13  cantor
//       ajout du copyright CNES
//
//       Revision 1.7  1998/06/24 10:29:45  luc
//       modification du format de l'en-tête
//       élimination de la variable statique RCS
//
//       Revision 1.6  1998/04/26 15:30:06  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.5  1997/07/06 10:37:55  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.4  1997/03/26 06:28:37  luc
//       changement des conventions de nommage
//       
//       Revision 1.3  1997/03/24 08:48:54  luc
//       passage de SCCS à RCS
//       
//       Revision 1.2  1994/11/26 15:13:27  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.1  1994/07/27 14:56:50  luc
//       Initial revision
//
//$Version
//       $Id: CombScalVD1VD2.h,v 1.8 2000/08/09 14:36:46 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_CombScalVD1VD2_h
#define __cantor_CombScalVD1VD2_h


// ce paquetage réalise les combinaisons d'opérandes
// entre les types scalaires suivants:
//            class ValeurDerivee1
//            class ValeurDerivee2
//

// il ne doit être utilisé que par le fichier "cantor/DeclVD1VD2.h",
// dont il n'est séparé que pour des raisons de clarté

// combinaisons
inline ValeurDerivee2& operator += (ValeurDerivee2& a, const ValeurDerivee1& b)
{ a.f1_ += b.f1 (); a.f0_ += b.f0 (); return a; }

inline ValeurDerivee2& operator -= (ValeurDerivee2& a, const ValeurDerivee1& b)
{ a.f1_ -= b.f1 (); a.f0_ -= b.f0 (); return a; }

inline ValeurDerivee2& operator *= (ValeurDerivee2& a, const ValeurDerivee1& b)
{ a *= ScalVD1VD2 (b); return a; }

inline ValeurDerivee2& operator /= (ValeurDerivee2& a, const ValeurDerivee1& b)
{ a /= ScalVD1VD2 (b); return a; }

inline ValeurDerivee2 operator +  (ValeurDerivee2  a, const ValeurDerivee1& b)
{ a += b; return a; }

inline ValeurDerivee2 operator -  (ValeurDerivee2  a, const ValeurDerivee1& b)
{ a -= b; return a; }

inline ValeurDerivee2 operator *  (ValeurDerivee2  a, const ValeurDerivee1& b)
{ a *= b; return a; }

inline ValeurDerivee2 operator /  (ValeurDerivee2  a, const ValeurDerivee1& b)
{ a /= b; return a; }

inline int            operator <  (const ValeurDerivee2& a,
                                   const ValeurDerivee1& b)
{ return a.f0 () <  b.f0 (); }

inline int            operator <= (const ValeurDerivee2& a,
                                   const ValeurDerivee1& b)
{ return a.f0 () <= b.f0 (); }

inline int            operator >  (const ValeurDerivee2& a,
                                   const ValeurDerivee1& b)
{ return a.f0 () >  b.f0 (); }

inline int            operator >= (const ValeurDerivee2& a,
                                   const ValeurDerivee1& b)
{ return a.f0 () >= b.f0 (); }


inline ValeurDerivee1& operator += (ValeurDerivee1& a, const ValeurDerivee2& b)
{ a += ScalVD2VD1 (b); return a; }

inline ValeurDerivee1& operator -= (ValeurDerivee1& a, const ValeurDerivee2& b)
{ a -= ScalVD2VD1 (b); return a; }

inline ValeurDerivee1& operator *= (ValeurDerivee1& a, const ValeurDerivee2& b)
{ a *= ScalVD2VD1 (b); return a; }

inline ValeurDerivee1& operator /= (ValeurDerivee1& a, const ValeurDerivee2& b)
{ a /= ScalVD2VD1 (b); return a; }

inline ValeurDerivee2 operator +  (const ValeurDerivee1& a, ValeurDerivee2  b)
{ b += a; return b; }

inline ValeurDerivee2 operator -  (const ValeurDerivee1& a, ValeurDerivee2  b)
{ b -= a; return -b; }

inline ValeurDerivee2 operator *  (const ValeurDerivee1& a, ValeurDerivee2  b)
{ b *= a; return b; }

inline ValeurDerivee2 operator /  (const ValeurDerivee1& a,
                                   const ValeurDerivee2& b)
{ ValeurDerivee2 a_prime = ScalVD1VD2 (a); a_prime /= b; return a_prime; }

inline int            operator <  (const ValeurDerivee1& a,
                                   const ValeurDerivee2& b)
{ return a.f0 () <  b.f0 (); }

inline int            operator <= (const ValeurDerivee1& a,
                                   const ValeurDerivee2& b)
{ return a.f0 () <= b.f0 (); }

inline int            operator >  (const ValeurDerivee1& a,
                                   const ValeurDerivee2& b)
{ return a.f0 () >  b.f0 (); }

inline int            operator >= (const ValeurDerivee1& a,
                                   const ValeurDerivee2& b)
{ return a.f0 () >= b.f0 (); }

#endif
