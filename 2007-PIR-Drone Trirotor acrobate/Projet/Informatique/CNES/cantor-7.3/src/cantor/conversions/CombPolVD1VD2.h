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
//>       CombPolVD1VD2.h
//
//$Resume
//       fichier d'en-tête des combinaisons d'opérandes CombPolVD1VD2
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
//>       inline PolVD1& operator +=()
//>       inline PolVD1& operator -=()
//>       inline PolVD1& operator *=()
//>       inline PolVD1& operator /=()
//
//$Historique
//       $Log: CombPolVD1VD2.h,v $
//       Revision 1.7  2000/08/09 14:36:45  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.6.4.1  2000/03/30 15:36:12  cantor
//       ajout du copyright CNES
//
//       Revision 1.6  1998/06/24 10:29:08  luc
//       modification du format de l'en-tête
//       élimination de la variable statique RCS
//
//       Revision 1.5  1997/07/06 10:37:42  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.4  1997/03/26 06:27:34  luc
//       changement des conventions de nommage
//       
//       Revision 1.3  1997/03/24 08:48:33  luc
//       passage de SCCS à RCS
//       
//       Revision 1.2  1994/11/26 15:12:48  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.1  1994/07/27 14:56:45  luc
//       Initial revision
//
//$Version
//       $Id: CombPolVD1VD2.h,v 1.7 2000/08/09 14:36:45 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_CombPolVD1VD2_h
#define __cantor_CombPolVD1VD2_h


// ce paquetage réalise les combinaisons d'opérandes
// entre les types polynômes suivants:
//            class ValeurDerivee1
//            class ValeurDerivee2
//

// il ne doit être utilisé que par le fichier "cantor/DeclVD1VD2.h",
// dont il n'est séparé que pour des raisons de clarté

// combinaisons
inline PolVD2 operator +  (const PolVD2& a, const PolVD1& b)
{ return a + PolVD1VD2 (b); }

inline PolVD2 operator -  (const PolVD2& a, const PolVD1& b)
{ return a - PolVD1VD2 (b); }

inline PolVD2 operator *  (const PolVD2& a, const PolVD1& b)
{ return a * PolVD1VD2 (b); }

inline PolVD2& operator += (PolVD2& a, const PolVD1& b)
{ return a += PolVD1VD2 (b); }

inline PolVD2& operator -= (PolVD2& a, const PolVD1& b)
{ return a -= PolVD1VD2 (b); }

inline PolVD2& operator *= (PolVD2& a, const PolVD1& b)
{ return a *= PolVD1VD2 (b); }


inline PolVD2 operator +  (const PolVD2& a, const ValeurDerivee1& b)
{ return a + ScalVD1VD2 (b); }

inline PolVD2 operator +  (const ValeurDerivee1& a, const PolVD2& b)
{ return ScalVD1VD2 (a) + b; }

inline PolVD2 operator -  (const PolVD2& a, const ValeurDerivee1& b)
{ return a - ScalVD1VD2 (b); }

inline PolVD2 operator -  (const ValeurDerivee1& a, const PolVD2& b)
{ return ScalVD1VD2 (a) - b; }

inline PolVD2 operator *  (const PolVD2& a, const ValeurDerivee1& b)
{ return a * ScalVD1VD2 (b); }

inline PolVD2 operator *  (const ValeurDerivee1& a, const PolVD2& b)
{ return ScalVD1VD2 (a) * b; }

inline PolVD2 operator /  (const PolVD2& a, const ValeurDerivee1& b)
{ return a / ScalVD1VD2 (b); }

inline PolVD2& operator += (PolVD2& a, const ValeurDerivee1& b)
{ return a += ScalVD1VD2 (b); }

inline PolVD2& operator -= (PolVD2& a, const ValeurDerivee1& b)
{ return a -= ScalVD1VD2 (b); }

inline PolVD2& operator *= (PolVD2& a, const ValeurDerivee1& b)
{ return a *= ScalVD1VD2 (b); }

inline PolVD2& operator /= (PolVD2& a, const ValeurDerivee1& b)
{ return a /= ScalVD1VD2 (b); }



inline PolVD2 operator +  (const PolVD1& a, const PolVD2& b)
{ return PolVD1VD2 (a) + b; }

inline PolVD2 operator -  (const PolVD1& a, const PolVD2& b)
{ return PolVD1VD2 (a) - b; }

inline PolVD2 operator *  (const PolVD1& a, const PolVD2& b)
{ return PolVD1VD2 (a) * b; }

inline PolVD1& operator += (PolVD1& a, const PolVD2& b)
{ return a += PolVD2VD1 (b); }

inline PolVD1& operator -= (PolVD1& a, const PolVD2& b)
{ return a -= PolVD2VD1 (b); }

inline PolVD1& operator *= (PolVD1& a, const PolVD2& b)
{ return a *= PolVD2VD1 (b); }


inline PolVD2 operator +  (const PolVD1& a, const ValeurDerivee2& b)
{ return PolVD1VD2 (a) + b; }

inline PolVD2 operator +  (const ValeurDerivee2& a, const PolVD1& b)
{ return a + PolVD1VD2 (b); }

inline PolVD2 operator -  (const PolVD1& a, const ValeurDerivee2& b)
{ return PolVD1VD2 (a) - b; }

inline PolVD2 operator -  (const ValeurDerivee2& a, const PolVD1& b)
{ return a - PolVD1VD2 (b); }

inline PolVD2 operator *  (const PolVD1& a, const ValeurDerivee2& b)
{ return PolVD1VD2 (a) * b; }

inline PolVD2 operator *  (const ValeurDerivee2& a, const PolVD1& b)
{ return a * PolVD1VD2 (b); }

inline PolVD2 operator /  (const PolVD1& a, const ValeurDerivee2& b)
{ return a / ScalVD1VD2 (b); }

inline PolVD1& operator += (PolVD1& a, const ValeurDerivee2& b)
{ return a += ScalVD2VD1 (b); }

inline PolVD1& operator -= (PolVD1& a, const ValeurDerivee2& b)
{ return a -= ScalVD2VD1 (b); }

inline PolVD1& operator *= (PolVD1& a, const ValeurDerivee2& b)
{ return a *= ScalVD2VD1 (b); }

inline PolVD1& operator /= (PolVD1& a, const ValeurDerivee2& b)
{ return a /= ScalVD2VD1 (b); }


#endif
