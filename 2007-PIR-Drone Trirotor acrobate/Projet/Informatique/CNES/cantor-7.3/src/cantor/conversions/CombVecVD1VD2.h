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
//>       CombVecVD1VD2.h
//
//$Resume
//       fichier d'en-tête des combinaisons d'opérandes CombVecVD1VD2
//
//$Description
//       Module de définition des fonctions "inline"
//
//$Contenu
//>       inline VecVD2 operator +()        
//>       inline VecVD2 operator -()        
//>       inline VecVD2 operator ^()        
//>       inline ValeurDerivee2 operator |()
//>       inline VecVD2 operator *()        
//>       inline VecVD2 operator /()        
//>       inline VecVD2& operator +=()      
//>       inline VecVD2& operator -=()      
//>       inline VecVD2& operator ^=()      
//>       inline VecVD2& operator *=()      
//>       inline VecVD2& operator /=()      
//>       inline VecVD1& operator +=()      
//>       inline VecVD1& operator -=()      
//>       inline VecVD1& operator ^=()      
//>       inline VecVD1& operator *=()      
//>       inline VecVD1& operator /=()      
//
//$Historique
//       $Log: CombVecVD1VD2.h,v $
//       Revision 1.8  2000/08/09 14:36:46  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.7.4.1  2000/03/30 15:36:13  cantor
//       ajout du copyright CNES
//
//       Revision 1.7  1998/06/24 10:30:17  luc
//       modification du format de l'en-tête
//       élimination de la variable statique RCS
//
//       Revision 1.6  1997/07/06 10:38:09  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.5  1997/03/26 06:28:35  luc
//       changement des conventions de nommage
//       
//       Revision 1.4  1997/03/24 08:49:13  luc
//       passage de SCCS à RCS
//       
//       Revision 1.3  1996/07/16 11:47:36  luc
//       suppression de l'opérateur == (il n'avait pas de raison d'être intrinsèque,
//       il n'était présent jusqu'ici qu'à cause des tools.h++)
//       
//       Revision 1.2  1994/11/26 15:13:47  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.1  1994/07/27 14:56:53  luc
//       Initial revision
//
//$Version
//       $Id: CombVecVD1VD2.h,v 1.8 2000/08/09 14:36:46 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_CombVecVD1VD2_h
#define __cantor_CombVecVD1VD2_h


// ce paquetage réalise les combinaisons d'opérandes
// entre les types vectoriels suivants:
//            class ValeurDerivee1
//            class ValeurDerivee2
//

// il ne doit être utilisé que par le fichier "cantor/DeclVD1VD2.h",
// dont il n'est séparé que pour des raisons de clarté

// combinaisons
inline VecVD2 operator +  (const VecVD2& a, const VecVD1& b)
{ return VecVD2 (a.x () + b.x (), a.y () + b.y (), a.z () + b.z ()); }

inline VecVD2 operator -  (const VecVD2& a, const VecVD1& b)
{ return VecVD2 (a.x () - b.x (), a.y () - b.y (), a.z () - b.z ()); }

inline VecVD2 operator ^  (const VecVD2& a, const VecVD1& b)
{ return VecVD2 (a.y () * b.z () - a.z () * b.y (),
                 a.z () * b.x () - a.x () * b.z (),
                 a.x () * b.y () - a.y () * b.x ());
}

inline ValeurDerivee2 operator |  (const VecVD2& a, const VecVD1& b)
{ return a.x () * b.x () + a.y () * b.y () + a.z () * b.z (); }

inline VecVD2 operator *  (const VecVD2& a, const ValeurDerivee1& b)
{ return VecVD2 (a.x () * b, a.y () * b, a.z () * b); }

inline VecVD2 operator *  (const ValeurDerivee1& a, const VecVD2& b)
{ return VecVD2 (b.x () * a, b.y () * a, b.z () * a); }

inline VecVD2 operator /  (const VecVD2& a, const ValeurDerivee1& b)
{ return VecVD2 (a.x () / b, a.y () / b, a.z () / b); }

inline VecVD2& operator += (VecVD2& a, const VecVD1& b)
{ return a += VecVD1VD2 (b); }

inline VecVD2& operator -= (VecVD2& a, const VecVD1& b)
{ return a -= VecVD1VD2 (b); }

inline VecVD2& operator ^= (VecVD2& a, const VecVD1& b)
{ return a ^= VecVD1VD2 (b); }

inline VecVD2& operator *= (VecVD2& a, const ValeurDerivee1& b)
{ return a *= ScalVD1VD2 (b); }

inline VecVD2& operator /= (VecVD2& a, const ValeurDerivee1& b)
{ return a /= ScalVD1VD2 (b); }


inline VecVD2 operator +  (const VecVD1& a, const VecVD2& b)
{ return VecVD2 (a.x () + b.x (), a.y () + b.y (), a.z () + b.z ()); }

inline VecVD2 operator -  (const VecVD1& a, const VecVD2& b)
{ return VecVD2 (a.x () - b.x (), a.y () - b.y (), a.z () - b.z ()); }

inline VecVD2 operator ^  (const VecVD1& a, const VecVD2& b)
{ return VecVD2 (a.y () * b.z () - a.z () * b.y (),
                 a.z () * b.x () - a.x () * b.z (),
                 a.x () * b.y () - a.y () * b.x ());
}

inline ValeurDerivee2 operator |  (const VecVD1& a, const VecVD2& b)
{ return a.x () * b.x () + a.y () * b.y () + a.z () * b.z (); }

inline VecVD2 operator *  (const VecVD1& a, const ValeurDerivee2& b)
{ return VecVD2 (a.x () * b, a.y () * b, a.z () * b); }

inline VecVD2 operator *  (const ValeurDerivee2& a, const VecVD1& b)
{ return VecVD2 (b.x () * a, b.y () * a, b.z () * a); }

inline VecVD2 operator /  (const VecVD1& a, const ValeurDerivee2& b)
{ return VecVD2 (a.x () / b, a.y () / b, a.z () / b); }

inline VecVD1& operator += (VecVD1& a, const VecVD2& b)
{ return a += VecVD2VD1 (b); }

inline VecVD1& operator -= (VecVD1& a, const VecVD2& b)
{ return a -= VecVD2VD1 (b); }

inline VecVD1& operator ^= (VecVD1& a, const VecVD2& b)
{ return a ^= VecVD2VD1 (b); }

inline VecVD1& operator *= (VecVD1& a, const ValeurDerivee2& b)
{ return a *= ScalVD2VD1 (b)me; }

inline VecVD1& operator /= (VecVD1& a, const ValeurDerivee2& b)
{ return a /= ScalVD2VD1 (b); }

#endif
