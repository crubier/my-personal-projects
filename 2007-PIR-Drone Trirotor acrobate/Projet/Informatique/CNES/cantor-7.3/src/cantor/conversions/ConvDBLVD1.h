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
//>       ConvDBLVD1.h
//
//$Resume
//       fichier d'en-tête des conversions ConvDBLVD1
//
//$Description
//       Module de définition des fonctions "inline"
//
//$Contenu
//>       inline ValeurDerivee1 ScalDBLVD1()
//>       inline VecVD1 VecDBLVD1()         
//>       inline RotVD1 RotDBLVD1()         
//>       inline PolVD1 PolDBLVD1()         
//>       inline double ScalVD1DBL()        
//>       inline VecDBL VecVD1DBL()         
//>       inline RotDBL RotVD1DBL()         
//>       inline PolDBL PolVD1DBL()         
//
//$Historique
//       $Log: ConvDBLVD1.h,v $
//       Revision 1.7  2000/08/09 14:36:46  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.6.4.1  2000/03/30 15:36:13  cantor
//       ajout du copyright CNES
//
//       Revision 1.6  1998/06/24 10:30:28  luc
//       modification du format de l'en-tête
//       élimination de la variable statique RCS
//
//       Revision 1.5  1997/07/06 10:38:14  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.4  1997/03/26 06:28:35  luc
//       changement des conventions de nommage
//       
//       Revision 1.3  1997/03/24 08:49:18  luc
//       passage de SCCS à RCS
//       
//       Revision 1.2  1994/11/26 15:14:00  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.1  1994/07/27 14:56:56  luc
//       Initial revision
//
//$Version
//       $Id: ConvDBLVD1.h,v 1.7 2000/08/09 14:36:46 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_ConvDBLVD1_h
#define __cantor_ConvDBLVD1_h


// ce paquetage réalise les conversions de types sur les classes
// utilisant les types scalaires suivants:
//            double
//            class ValeurDerivee1
//

// il ne doit être utilisé que par le fichier "cantor/DeclDBLVD1.h",
// dont il n'est séparé que pour des raisons de clarté

// conversions
inline ValeurDerivee1 ScalDBLVD1 (double x)
                                 { return ValeurDerivee1 (x, 0.0); }
inline VecVD1          VecDBLVD1 (const VecDBL& v)
                                 { return VecVD1 (ScalDBLVD1 (v.x ()),
                                                  ScalDBLVD1 (v.y ()),
                                                  ScalDBLVD1 (v.z ()));
                                 }
inline RotVD1          RotDBLVD1 (const RotDBL& r)
                                 { return RotVD1 (ScalDBLVD1 (r.q0 ()),
                                                  ScalDBLVD1 (r.q1 ()),
                                                  ScalDBLVD1 (r.q2 ()),
                                                  ScalDBLVD1 (r.q3 ()));
                                 }
inline PolVD1          PolDBLVD1 (const PolDBL& p)
                                 { ValeurDerivee1 tbl [polynome_max_degre + 1];
                                   for (int i = 0; i <= p.degre (); i++)
                                     tbl [i] = ScalDBLVD1 (p.coeff (i));
                                   return PolVD1 (p.degre (), tbl);
                                 }

inline double         ScalVD1DBL (const ValeurDerivee1& x)
                                 { return x.f0 (); }
inline VecDBL          VecVD1DBL (const VecVD1& v)
                                 { return VecDBL (ScalVD1DBL (v.x ()),
                                                  ScalVD1DBL (v.y ()),
                                                  ScalVD1DBL (v.z ()));
                                 }
inline RotDBL          RotVD1DBL (const RotVD1& r)
                                 { return RotDBL (ScalVD1DBL (r.q0 ()),
                                                  ScalVD1DBL (r.q1 ()),
                                                  ScalVD1DBL (r.q2 ()),
                                                  ScalVD1DBL (r.q3 ()));
                                 }
inline PolDBL          PolVD1DBL (const PolVD1& p)
                                 { double tbl [polynome_max_degre + 1];
                                   for (int i = 0; i <= p.degre (); i++)
                                     tbl [i] = ScalVD1DBL (p.coeff (i));
                                   return PolDBL (p.degre (), tbl);
                                 }

#endif
