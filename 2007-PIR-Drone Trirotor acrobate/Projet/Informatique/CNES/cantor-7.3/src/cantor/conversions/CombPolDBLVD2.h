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
//>       CombPolDBLVD2.h
//
//$Resume
//       fichier d'en-tête des combinaisons d'opérandes CombPolDBLVD2
//
//$Description
//       Module de définition des fonctions "inline"
//
//$Contenu
//>       inline PolVD2 operator +()  
//>       inline PolVD2 operator -()  
//>       inline PolVD2 operator *()  
//>       inline PolVD2& operator +=()
//>       inline PolVD2& operator -=()
//>       inline PolVD2& operator *=()
//>       inline PolVD2 operator /()  
//>       inline PolVD2& operator /=()
//>       inline PolDBL& operator +=()
//>       inline PolDBL& operator -=()
//>       inline PolDBL& operator *=()
//>       inline PolDBL& operator /=()
//
//$Historique
//       $Log: CombPolDBLVD2.h,v $
//       Revision 1.8  2000/08/09 14:36:45  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.7.4.1  2000/03/30 15:36:12  cantor
//       ajout du copyright CNES
//
//       Revision 1.7  1998/10/05 14:16:55  cantor
//       contournement d'un bug des compilateurs Sun 4.0 et 4.2 (au moins)
//
//       Revision 1.6  1998/06/24 10:28:53  luc
//       modification du format de l'en-tête
//       élimination de la variable statique RCS
//
//       Revision 1.5  1997/07/06 10:37:38  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.4  1997/03/26 06:27:19  luc
//       changement des conventions de nommage
//       
//       Revision 1.3  1997/03/24 08:48:27  luc
//       passage de SCCS à RCS
//       
//       Revision 1.2  1994/11/26 15:12:41  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.1  1994/07/27 14:56:44  luc
//       Initial revision
//
//$Version
//       $Id: CombPolDBLVD2.h,v 1.8 2000/08/09 14:36:45 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_CombPolDBLVD2_h
#define __cantor_CombPolDBLVD2_h


// ce paquetage réalise les combinaisons d'opérandes
// entre les types polynomes suivants:
//            double
//            class ValeurDerivee2
//

// il ne doit être utilisé que par le fichier "cantor/DeclDBLVD2.h",
// dont il n'est séparé que pour des raisons de clarté

// combinaisons
inline PolVD2 operator +  (const PolVD2& a, const PolDBL& b)
{ return a + PolDBLVD2 (b); }

inline PolVD2 operator -  (const PolVD2& a, const PolDBL& b)
{ return a - PolDBLVD2 (b); }

inline PolVD2 operator *  (const PolVD2& a, const PolDBL& b)
{ return a * PolDBLVD2 (b); }

inline PolVD2& operator += (PolVD2& a, const PolDBL& b)
{ return a += PolDBLVD2 (b); }

inline PolVD2& operator -= (PolVD2& a, const PolDBL& b)
{ return a -= PolDBLVD2 (b); }

inline PolVD2& operator *= (PolVD2& a, const PolDBL& b)
{ return a *= PolDBLVD2 (b); }


inline PolVD2 operator +  (const PolVD2& a, double b)
{ return a + ScalDBLVD2 (b); }

inline PolVD2 operator +  (double a, const PolVD2& b)
{ return b + ScalDBLVD2 (a); }

inline PolVD2 operator -  (const PolVD2& a, double b)
{ return a - ScalDBLVD2 (b); }

inline PolVD2 operator -  (double a, const PolVD2& b)
{ return -(b - ScalDBLVD2 (a)); }

inline PolVD2 operator *  (const PolVD2& a, double b)
{ return a * ScalDBLVD2 (b); }

inline PolVD2 operator *  (double a, const PolVD2& b)
{ return b * ScalDBLVD2 (a); }

inline PolVD2 operator /  (const PolVD2& a, double b)
{ return a / ScalDBLVD2 (b); }

inline PolVD2& operator += (PolVD2& a, double b)
{ return a += ScalDBLVD2 (b); }

inline PolVD2& operator -= (PolVD2& a, double b)
{ return a -= ScalDBLVD2 (b); }

inline PolVD2& operator *= (PolVD2& a, double b)
{ return a *= ScalDBLVD2 (b); }

inline PolVD2& operator /= (PolVD2& a, double b)
{ return a /= ScalDBLVD2 (b); }



inline PolVD2 operator +  (const PolDBL& a, const PolVD2& b)
{ return PolDBLVD2 (a) + b; }

inline PolVD2 operator -  (const PolDBL& a, const PolVD2& b)
{ return PolDBLVD2 (a) - b; }

inline PolVD2 operator *  (const PolDBL& a, const PolVD2& b)
{ return PolDBLVD2 (a) * b; }

inline PolDBL& operator += (PolDBL& a, const PolVD2& b)
{ return a += PolVD2DBL (b); }

inline PolDBL& operator -= (PolDBL& a, const PolVD2& b)
{ return a -= PolVD2DBL (b); }

inline PolDBL& operator *= (PolDBL& a, const PolVD2& b)
{ return a *= PolVD2DBL (b); }


inline PolVD2 operator +  (const PolDBL& a, const ValeurDerivee2& b)
{ return PolDBLVD2 (a) + b; }

inline PolVD2 operator +  (const ValeurDerivee2& a, const PolDBL& b)
{ return a + PolDBLVD2 (b); }

inline PolVD2 operator -  (const PolDBL& a, const ValeurDerivee2& b)
{ return PolDBLVD2 (a) - b; }

inline PolVD2 operator -  (const ValeurDerivee2& a, const PolDBL& b)
{ return a - PolDBLVD2 (b); }

inline PolVD2 operator *  (const PolDBL& a, const ValeurDerivee2& b)
{ return PolDBLVD2 (a) * b; }

inline PolVD2 operator *  (const ValeurDerivee2& a, const PolDBL& b)
{ return a * PolDBLVD2 (b); }

inline PolVD2 operator /  (const PolDBL& a, const ValeurDerivee2& b)
{ return a / ScalDBLVD2 (b); }

inline PolDBL& operator += (PolDBL& a, const ValeurDerivee2& b)
{ return a += ScalVD2DBL (b); }

inline PolDBL& operator -= (PolDBL& a, const ValeurDerivee2& b)
{ return a -= ScalVD2DBL (b); }

inline PolDBL& operator *= (PolDBL& a, const ValeurDerivee2& b)
{ return a *= ScalVD2DBL (b); }

inline PolDBL& operator /= (PolDBL& a, const ValeurDerivee2& b)
{ return a /= ScalVD2DBL (b); }


#endif
