#ifndef __cantor_CombRotDBLVD2_h
#define __cantor_CombRotDBLVD2_h

static char rcsid_CombRotDBLVD2_h [] = "$Id: CombRotDBLVD2.h,v 1.2 1997/03/26 06:38:24 luc Exp $";

// ce paquetage réalise les combinaisons d'opérandes
// entre les types rotations suivants:
//            double
//            class ValeurDerivee2
//

// il ne doit être utilisé que par le fichier "cantor/DeclDBLVD2.h",
// dont il n'est séparé que pour des raisons de clarté

// combinaisons
inline int    operator == (const RotVD2& r, const RotDBL& q)
{ return RotVD2DBL (r) == q; }


inline int    operator == (const RotDBL& r, const RotVD2& q)
{ return r == RotVD2DBL (q); }

#endif
