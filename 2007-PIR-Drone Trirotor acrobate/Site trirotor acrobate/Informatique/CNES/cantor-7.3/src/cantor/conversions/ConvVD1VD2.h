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
//>       ConvVD1VD2.h
//
//$Resume
//       fichier d'en-tête des conversions ConvVD1VD2
//
//$Description
//       Module de définition des fonctions "inline"
//
//$Contenu
//>       inline ValeurDerivee2 ScalVD1VD2()
//>       inline VecVD2 VecVD1VD2()         
//>       inline RotVD2 RotVD1VD2()         
//>       inline PolVD2 PolVD1VD2()         
//>       inline ValeurDerivee1 ScalVD2VD1()
//>       inline VecVD1 VecVD2VD1()         
//>       inline RotVD1 RotVD2VD1()         
//>       inline PolVD1 PolVD2VD1()         
//
//$Historique
//       $Log: ConvVD1VD2.h,v $
//       Revision 1.7  2000/08/09 14:36:46  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.6.4.1  2000/03/30 15:36:13  cantor
//       ajout du copyright CNES
//
//       Revision 1.6  1998/06/24 10:30:45  luc
//       modification du format de l'en-tête
//       élimination de la variable statique RCS
//
//       Revision 1.5  1997/07/06 10:38:22  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.4  1997/03/26 06:28:34  luc
//       changement des conventions de nommage
//       
//       Revision 1.3  1997/03/24 08:49:31  luc
//       passage de SCCS à RCS
//       
//       Revision 1.2  1994/11/26 15:14:12  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.1  1994/07/27 14:56:58  luc
//       Initial revision
//
//$Version
//       $Id: ConvVD1VD2.h,v 1.7 2000/08/09 14:36:46 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_ConvVD1VD2_h
#define __cantor_ConvVD1VD2_h


// ce paquetage réalise les conversions de types sur les classes
// utilisant les types scalaires suivants:
//            class ValeurDerivee1
//            class ValeurDerivee2
//

// il ne doit être utilisé que par le fichier "cantor/DeclVD1VD2.h",
// dont il n'est séparé que pour des raisons de clarté

// conversions
inline ValeurDerivee2 ScalVD1VD2 (const ValeurDerivee1& x)
                                 { return ValeurDerivee2 (x.f0 (),
                                                          x.f1 (),
                                                          0.0);
                                 }
inline VecVD2          VecVD1VD2 (const VecVD1& v)
                                 { return VecVD2 (ScalVD1VD2 (v.x ()),
                                                  ScalVD1VD2 (v.y ()),
                                                  ScalVD1VD2 (v.z ()));
                                 }
inline RotVD2          RotVD1VD2 (const RotVD1& r)
                                 { return RotVD2 (ScalVD1VD2 (r.q0 ()),
                                                  ScalVD1VD2 (r.q1 ()),
                                                  ScalVD1VD2 (r.q2 ()),
                                                  ScalVD1VD2 (r.q3 ()));
                                 }
inline PolVD2          PolVD1VD2 (const PolVD1& p)
                                 { ValeurDerivee2 tbl [polynome_max_degre + 1];
                                   for (int i = 0; i <= p.degre (); i++)
                                     tbl [i] = ScalVD1VD2 (p.coeff (i));
                                   return PolVD2 (p.degre (), tbl);
                                 }

inline ValeurDerivee1 ScalVD2VD1 (const ValeurDerivee2& x)
                                 { return ValeurDerivee1 (x.f0 (), x.f1 ()); }
inline VecVD1          VecVD2VD1 (const VecVD2& v)
                                 { return VecVD1 (ScalVD2VD1 (v.x ()),
                                                  ScalVD2VD1 (v.y ()),
                                                  ScalVD2VD1 (v.z ()));
                                 }
inline RotVD1          RotVD2VD1 (const RotVD2& r)
                                 { return RotVD1 (ScalVD2VD1 (r.q0 ()),
                                                  ScalVD2VD1 (r.q1 ()),
                                                  ScalVD2VD1 (r.q2 ()),
                                                  ScalVD2VD1 (r.q3 ()));
                                 }
inline PolVD1          PolVD2VD1 (const PolVD2& p)
                                 { ValeurDerivee1 tbl [polynome_max_degre + 1];
                                   for (int i = 0; i <= p.degre (); i++)
                                     tbl [i] = ScalVD2VD1 (p.coeff (i));
                                   return PolVD1 (p.degre (), tbl);
                                 }

#endif
