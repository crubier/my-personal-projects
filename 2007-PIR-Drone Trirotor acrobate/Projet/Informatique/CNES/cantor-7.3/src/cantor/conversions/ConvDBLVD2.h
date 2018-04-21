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
//>       ConvDBLVD2.h
//
//$Resume
//       fichier d'en-tête des conversions ConvDBLVD2
//
//$Description
//       Module de définition des fonctions "inline"
//
//$Contenu
//>       inline ValeurDerivee2 ScalDBLVD2()
//>       inline VecVD2 VecDBLVD2()         
//>       inline RotVD2 RotDBLVD2()         
//>       inline PolVD2 PolDBLVD2()         
//>       inline double ScalVD2DBL()        
//>       inline VecDBL VecVD2DBL()         
//>       inline RotDBL RotVD2DBL()         
//>       inline PolDBL PolVD2DBL()         
//
//$Historique
//       $Log: ConvDBLVD2.h,v $
//       Revision 1.7  2000/08/09 14:36:46  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.6.4.1  2000/03/30 15:36:13  cantor
//       ajout du copyright CNES
//
//       Revision 1.6  1998/06/24 10:30:37  luc
//       modification du format de l'en-tête
//       élimination de la variable statique RCS
//
//       Revision 1.5  1997/07/06 10:38:18  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.4  1997/03/26 06:28:34  luc
//       changement des conventions de nommage
//       
//       Revision 1.3  1997/03/24 08:49:24  luc
//       passage de SCCS à RCS
//       
//       Revision 1.2  1994/11/26 15:14:06  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.1  1994/07/27 14:56:57  luc
//       Initial revision
//
//$Version
//       $Id: ConvDBLVD2.h,v 1.7 2000/08/09 14:36:46 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_ConvDBLVD2_h
#define __cantor_ConvDBLVD2_h


// ce paquetage réalise les conversions de types sur les classes
// utilisant les types scalaires suivants:
//            double
//            class ValeurDerivee2
//

// il ne doit être utilisé que par le fichier "cantor/DeclDBLVD2.h",
// dont il n'est séparé que pour des raisons de clarté

// conversions
inline ValeurDerivee2 ScalDBLVD2 (double x)
                                 { return ValeurDerivee2 (x, 0.0, 0.0); }
inline VecVD2          VecDBLVD2 (const VecDBL& v)
                                 { return VecVD2 (ScalDBLVD2 (v.x ()),
                                                  ScalDBLVD2 (v.y ()),
                                                  ScalDBLVD2 (v.z ()));
                                 }
inline RotVD2          RotDBLVD2 (const RotDBL& r)
                                 { return RotVD2 (ScalDBLVD2 (r.q0 ()),
                                                  ScalDBLVD2 (r.q1 ()),
                                                  ScalDBLVD2 (r.q2 ()),
                                                  ScalDBLVD2 (r.q3 ()));
                                 }
inline PolVD2          PolDBLVD2 (const PolDBL& p)
                                 { ValeurDerivee2 tbl [polynome_max_degre + 1];
                                   for (int i = 0; i <= p.degre (); i++)
                                     tbl [i] = ScalDBLVD2 (p.coeff (i));
                                   return PolVD2 (p.degre (), tbl);
                                 }

inline double         ScalVD2DBL (const ValeurDerivee2& x)
                                 { return x.f0 (); }
inline VecDBL          VecVD2DBL (const VecVD2& v)
                                 { return VecDBL (ScalVD2DBL (v.x ()),
                                                  ScalVD2DBL (v.y ()),
                                                  ScalVD2DBL (v.z ()));
                                 }
inline RotDBL          RotVD2DBL (const RotVD2& r)
                                 { return RotDBL (ScalVD2DBL (r.q0 ()),
                                                  ScalVD2DBL (r.q1 ()),
                                                  ScalVD2DBL (r.q2 ()),
                                                  ScalVD2DBL (r.q3 ()));
                                 }
inline PolDBL          PolVD2DBL (const PolVD2& p)
                                 { double tbl [polynome_max_degre + 1];
                                   for (int i = 0; i <= p.degre (); i++)
                                     tbl [i] = ScalVD2DBL (p.coeff (i));
                                   return PolDBL (p.degre (), tbl);
                                 }

#endif
