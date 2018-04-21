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
//>       CombScalDBLVD2.h
//
//$Resume
//       fichier d'en-tête des combinaisons d'opérandes CombScalDBLVD2
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
//>       inline double& operator +=()        
//>       inline double& operator -=()        
//>       inline double& operator *=()        
//>       inline double& operator /=()        
//>       inline ValeurDerivee1 operator +()  
//>       inline ValeurDerivee1 operator -()  
//>       inline ValeurDerivee1 operator *()  
//>       inline ValeurDerivee1 operator /()  
//
//$Historique
//       $Log: CombScalDBLVD2.h,v $
//       Revision 1.8  2000/08/09 14:36:46  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.7.4.1  2000/03/30 15:36:12  cantor
//       ajout du copyright CNES
//
//       Revision 1.7  1998/06/24 10:29:33  luc
//       modification du format de l'en-tête
//       élimination de la variable statique RCS
//
//       Revision 1.6  1998/04/26 15:30:01  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.5  1997/07/06 10:37:50  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.4  1997/03/26 06:28:37  luc
//       changement des conventions de nommage
//       
//       Revision 1.3  1997/03/24 08:48:48  luc
//       passage de SCCS à RCS
//       
//       Revision 1.2  1994/11/26 15:13:20  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.1  1994/07/27 14:56:49  luc
//       Initial revision
//
//$Version
//       $Id: CombScalDBLVD2.h,v 1.8 2000/08/09 14:36:46 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_CombScalDBLVD2_h
#define __cantor_CombScalDBLVD2_h


// ce paquetage réalise les combinaisons d'opérandes
// entre les types scalaires suivants:
//            double
//            class ValeurDerivee2
//

// il ne doit être utilisé que par le fichier "cantor/DeclDBLVD2.h",
// dont il n'est séparé que pour des raisons de clarté

// combinaisons
inline ValeurDerivee2& operator += (ValeurDerivee2& a, double b)
{ a.f0_ += b; return a; }

inline ValeurDerivee2& operator -= (ValeurDerivee2& a, double b)
{ a.f0_ -= b; return a; }

inline ValeurDerivee2& operator *= (ValeurDerivee2& a, double b)
{ a.f2_ *= b; a.f1_ *= b; a.f0_ *= b; return a; }

inline ValeurDerivee2& operator /= (ValeurDerivee2& a, double b)
{ a.f2_ /= b; a.f1_ /= b; a.f0_ /= b; return a; }

inline ValeurDerivee2 operator +  (ValeurDerivee2  a, double b)
{ a += b; return a; }

inline ValeurDerivee2 operator -  (ValeurDerivee2  a, double b)
{ a -= b; return a; }

inline ValeurDerivee2 operator *  (ValeurDerivee2  a, double b)
{ a *= b; return a; }

inline ValeurDerivee2 operator /  (ValeurDerivee2  a, double b)
{ a /= b; return a; }

inline int            operator <  (const ValeurDerivee2& a, double b)
{ return a.f0 () <  b; }

inline int            operator <= (const ValeurDerivee2& a, double b)
{ return a.f0 () <= b; }

inline int            operator >  (const ValeurDerivee2& a, double b)
{ return a.f0 () >  b; }

inline int            operator >= (const ValeurDerivee2& a, double b)
{ return a.f0 () >= b; }


inline double&        operator += (double& a, const ValeurDerivee2& b)
{ a += ScalVD2DBL (b); return a; }

inline double&        operator -= (double& a, const ValeurDerivee2& b)
{ a -= ScalVD2DBL (b); return a; }

inline double&        operator *= (double& a, const ValeurDerivee2& b)
{ a *= ScalVD2DBL (b); return a; }

inline double&        operator /= (double& a, const ValeurDerivee2& b)
{ a /= ScalVD2DBL (b); return a; }

inline ValeurDerivee1 operator +  (double  a, ValeurDerivee2 b)
{ b += a; return b; }

inline ValeurDerivee1 operator -  (double  a, ValeurDerivee2 b)
{ b -= a; return -b; }

inline ValeurDerivee1 operator *  (double  a, ValeurDerivee2 b)
{ b *= a; return b; }

inline ValeurDerivee1 operator /  (double  a, const ValeurDerivee2& b)
{ ValeurDerivee2 a_prime = ScalDBLVD2 (a); a_prime /= b; return a_prime; }

inline int            operator <  (double  a, const ValeurDerivee2& b)
{ return a <  b.f0 (); }

inline int            operator <= (double  a, const ValeurDerivee2& b)
{ return a <= b.f0 (); }

inline int            operator >  (double  a, const ValeurDerivee2& b)
{ return a >  b.f0 (); }

inline int            operator >= (double  a, const ValeurDerivee2& b)
{ return a >= b.f0 (); }

#endif
