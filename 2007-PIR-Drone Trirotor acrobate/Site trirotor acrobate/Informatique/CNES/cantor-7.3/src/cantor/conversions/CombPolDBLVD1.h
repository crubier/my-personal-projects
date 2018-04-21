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
//>       CombPolDBLVD1.h
//
//$Resume
//       fichier d'en-tête des combinaisons d'opérandes CombPolDBLVD1
//
//$Description
//       Module de définition des fonctions "inline"
//
//$Contenu
//>       inline PolVD1 operator +()  
//>       inline PolVD1 operator -()  
//>       inline PolVD1 operator *()  
//>       inline PolVD1& operator +=()
//>       inline PolVD1& operator -=()
//>       inline PolVD1& operator *=()
//>       inline PolVD1 operator /()  
//>       inline PolVD1& operator /=()
//>       inline PolDBL& operator +=()
//>       inline PolDBL& operator -=()
//>       inline PolDBL& operator *=()
//>       inline PolDBL& operator /=()
//
//$Historique
//       $Log: CombPolDBLVD1.h,v $
//       Revision 1.8  2000/08/09 14:36:45  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.7.4.1  2000/03/30 15:36:12  cantor
//       ajout du copyright CNES
//
//       Revision 1.7  1998/10/05 14:15:22  cantor
//       contournement d'un bug des compilateurs Sun 4.0 et 4.2 (au moins)
//
//       Revision 1.6  1998/06/24 10:27:50  luc
//       modification du format de l'en-tête
//       élimination de la variable statique RCS
//
//       Revision 1.5  1997/07/06 10:37:33  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.4  1997/04/01 07:49:26  luc
//       changement des conventions de nommage
//       
//       Revision 1.3  1997/03/24 08:48:19  luc
//       passage de SCCS à RCS
//       
//       Revision 1.2  1994/11/26 14:59:28  mercator
//       correction d'une erreur de conversion
//       remplacement du pragma interface par une variable statique
//       
//       Revision 1.1  1994/07/27 14:56:43  luc
//       Initial revision
//
//$Version
//       $Id: CombPolDBLVD1.h,v 1.8 2000/08/09 14:36:45 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_CombPolDBLVD1_h
#define __cantor_CombPolDBLVD1_h


// ce paquetage réalise les combinaisons d'opérandes
// entre les types polynômes suivants:
//            double
//            class ValeurDerivee1
//

// il ne doit être utilisé que par le fichier "cantor/DeclDBLVD1.h",
// dont il n'est séparé que pour des raisons de clarté

// combinaisons
inline PolVD1 operator +  (const PolVD1& a, const PolDBL& b)
{ return a + PolDBLVD1 (b); }

inline PolVD1 operator -  (const PolVD1& a, const PolDBL& b)
{ return a - PolDBLVD1 (b); }

inline PolVD1 operator *  (const PolVD1& a, const PolDBL& b)
{ return a * PolDBLVD1 (b); }

inline PolVD1& operator += (PolVD1& a, const PolDBL& b)
{ return a += PolDBLVD1 (b); }

inline PolVD1& operator -= (PolVD1& a, const PolDBL& b)
{ return a -= PolDBLVD1 (b); }

inline PolVD1& operator *= (PolVD1& a, const PolDBL& b)
{ return a *= PolDBLVD1 (b); }


inline PolVD1 operator +  (const PolVD1& a, double b)
{ return a + ScalDBLVD1 (b); }

inline PolVD1 operator +  (double a, const PolVD1& b)
{ return b + ScalDBLVD1 (a); }

inline PolVD1 operator -  (const PolVD1& a, double b)
{ return a - ScalDBLVD1 (b); }

inline PolVD1 operator -  (double a, const PolVD1& b)
{ return -(b - ScalDBLVD1 (a)); }

inline PolVD1 operator *  (const PolVD1& a, double b)
{ return a * ScalDBLVD1 (b); }

inline PolVD1 operator *  (double a, const PolVD1& b)
{ return b * ScalDBLVD1 (a); }

inline PolVD1 operator /  (const PolVD1& a, double b)
{ return a / ScalDBLVD1 (b); }

inline PolVD1& operator += (PolVD1& a, double b)
{ return a += ScalDBLVD1 (b); }

inline PolVD1& operator -= (PolVD1& a, double b)
{ return a -= ScalDBLVD1 (b); }

inline PolVD1& operator *= (PolVD1& a, double b)
{ return a *= ScalDBLVD1 (b); }

inline PolVD1& operator /= (PolVD1& a, double b)
{ return a /= ScalDBLVD1 (b); }



inline PolVD1 operator +  (const PolDBL& a, const PolVD1& b)
{ return PolDBLVD1 (a) + b; }

inline PolVD1 operator -  (const PolDBL& a, const PolVD1& b)
{ return PolDBLVD1 (a) - b; }

inline PolVD1 operator *  (const PolDBL& a, const PolVD1& b)
{ return PolDBLVD1 (a) * b; }

inline PolDBL& operator += (PolDBL& a, const PolVD1& b)
{ return a += PolVD1DBL (b); }

inline PolDBL& operator -= (PolDBL& a, const PolVD1& b)
{ return a -= PolVD1DBL (b); }

inline PolDBL& operator *= (PolDBL& a, const PolVD1& b)
{ return a *= PolVD1DBL (b); }


inline PolVD1 operator +  (const PolDBL& a, const ValeurDerivee1& b)
{ return PolDBLVD1 (a) + b; }

inline PolVD1 operator +  (const ValeurDerivee1& a, const PolDBL& b)
{ return a + PolDBLVD1 (b); }

inline PolVD1 operator -  (const PolDBL& a, const ValeurDerivee1& b)
{ return PolDBLVD1 (a) - b; }

inline PolVD1 operator -  (const ValeurDerivee1& a, const PolDBL& b)
{ return a - PolDBLVD1 (b); }

inline PolVD1 operator *  (const PolDBL& a, const ValeurDerivee1& b)
{ return PolDBLVD1 (a) * b; }

inline PolVD1 operator *  (const ValeurDerivee1& a, const PolDBL& b)
{ return a * PolDBLVD1 (b); }

inline PolVD1 operator /  (const PolDBL& a, const ValeurDerivee1& b)
{ return PolDBLVD1 (a) / b; }

inline PolDBL& operator += (PolDBL& a, const ValeurDerivee1& b)
{ return a += ScalVD1DBL (b); }

inline PolDBL& operator -= (PolDBL& a, const ValeurDerivee1& b)
{ return a -= ScalVD1DBL (b); }

inline PolDBL& operator *= (PolDBL& a, const ValeurDerivee1& b)
{ return a *= ScalVD1DBL (b); }

inline PolDBL& operator /= (PolDBL& a, const ValeurDerivee1& b)
{ return a /= ScalVD1DBL (b); }


#endif
