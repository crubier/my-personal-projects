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
//>       Instanciations.cpp
//
//$Resume
//       fichier d'instanciation des classes et fonctions "template"
//
//$Description
//       Module des instanciations explicites
//
//$Contenu
//>       class Vecteur3<double> 
//>       class Rotation<double> 
//>       class Polynome<double> 
//>       class Vecteur3<ValeurDerivee1> 
//>       class Rotation<ValeurDerivee1> 
//>       class Polynome<ValeurDerivee1> 
//>       class Vecteur3<ValeurDerivee2> 
//>       class Rotation<ValeurDerivee2> 
//>       class Polynome<ValeurDerivee2> 
//
//$Historique
//       $Log: Instanciations.cpp,v $
//       Revision 1.15  2003/02/04 08:39:56  cantor
//       DM-ID 17 Modifications suite à la modification des extensions (CC <- CPP)
//
//       Revision 1.14  2002/02/06 17:50:48  cantor
//       ajout des -throw(CantorErreurs)- (*6) apres probleme de compilation avec CC
//
//       Revision 1.13  2001/06/05 15:45:54  cantor
//       utilisation du mécanisme des exceptions pour la gestion des erreurs
//
//       Revision 1.12  2000/10/24 16:25:23  cantor
//       modification des includes pour permettre la compilation avec le
//       compilateur Sun Workshop 5.0
//
//       Revision 1.11  2000/08/09 14:36:42  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.10.2.1  2000/03/30 15:36:05  cantor
//       ajout du copyright CNES
//
//       Revision 1.10  1999/06/28 13:47:34  cantor
//       l'argument Vecteur3<T> de l'operateur * est desormais passe par reference constante
//
//       Revision 1.9  1999/02/05 07:43:16  cantor
//       correction d'inhomogénéités entre des instanciations de signatures et
//       les déclarations des fonctions templates (problèmes de const réels,
//       détectés par egcs)
//
//       Revision 1.8  1998/08/05 08:08:28  cantor
//       utilisation de HAVE_INSTANTIATIONS (mis en place par configure)
//
//       Revision 1.7  1998/06/24 10:09:22  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.6  1997/07/06 10:38:42  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.5  1997/04/17 06:20:44  luc
//       transfert de corrigeOrthog dans l'interface publique de la bibliothèque
//       élimination de fonctions statiques (intégrées dans corrigeOrthog)
//       
//       Revision 1.4  1997/03/26 06:54:30  luc
//       changement des conventions de nommage
//       
//       Revision 1.3  1997/03/24 09:32:40  luc
//       passage de SCCS à RCS
//       
//       Revision 1.2  1996/07/16 12:12:17  luc
//       élimination de la dépendance aux tools.h++ (Rogue Wave)
//       suppression de l'opérateur == (il n'avait pas de raison d'être intrinsèque,
//       il n'était présent jusqu'ici qu'à cause des tools.h++)
//       
//       Revision 1.1  1994/11/26 16:00:36  mercator
//       Initial revision
//
//$Version
//       $Id: Instanciations.cpp,v 1.15 2003/02/04 08:39:56 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

// Ce fichier réalise les instanciations des classes templates utilisées
// par la librairie CANTOR.


#include <CantorConfigNoInstall.h>

#ifdef HAVE_INSTANTIATIONS

#include "cantor/ValeurDerivee1.h"
#include "cantor/ValeurDerivee2.h"

#include "cantor/Vecteur3.h"
#include "cantor/Rotation.h"
#include "cantor/Polynome.h"

#include "cantor/Vecteur3.cpp"
#include "cantor/Rotation.cpp"
#include "cantor/Polynome.cpp"

template class Vecteur3<double>;
template inline ostream&         operator << (ostream& s,
                                              const Vecteur3<double>& u);
template inline Vecteur3<double> operator *  (const double& t,
                                              const Vecteur3<double>& u);
template inline double           angle       (const Vecteur3<double>& u,
                                              const Vecteur3<double>& v);
template inline Vecteur3<double> vecteurOrthogonalNorme
                                             (const Vecteur3<double>& u)
  throw(CantorErreurs);
template inline Vecteur3<double> vecteurNorme
                                             (Vecteur3<double> u)
  throw(CantorErreurs);
template class Rotation<double>;
template inline Rotation<double> operator -  (const Rotation<double>& r);
template void corrigeOrthog (double m [3][3], double orth [3][3],
                             double convergence)
  throw (CantorErreurs);
template class Polynome<double>;
template inline ostream&                 operator <<
                                         (ostream& s,
                                          const Polynome<double>& u);
template inline Polynome<double>         operator +
                                         (const double& t,
                                          Polynome<double> u);
template inline Polynome<double>         operator -
                                         (const double& t,
                                          Polynome<double> u);
template inline Polynome<double>         operator *
                                         (const double& t,
                                          Polynome<double> u);

template class Vecteur3<ValeurDerivee1>;
template inline ostream&                 operator <<
                                         (ostream& s,
                                          const Vecteur3<ValeurDerivee1>& u);
template inline Vecteur3<ValeurDerivee1> operator *
                                         (const ValeurDerivee1& t,
                                          const Vecteur3<ValeurDerivee1>& u);
template inline ValeurDerivee1           angle
                                         (const Vecteur3<ValeurDerivee1>& u,
                                          const Vecteur3<ValeurDerivee1>& v);
template inline Vecteur3<ValeurDerivee1> vecteurOrthogonalNorme
                                         (const Vecteur3<ValeurDerivee1>& u)
  throw(CantorErreurs);
template inline Vecteur3<ValeurDerivee1> vecteurNorme
                                         (Vecteur3<ValeurDerivee1> u)
  throw(CantorErreurs);
template class Rotation<ValeurDerivee1>;
template inline Rotation<ValeurDerivee1> operator -
                                         (const Rotation<ValeurDerivee1>& r);
template void corrigeOrthog (ValeurDerivee1 m [3][3],
                             ValeurDerivee1 orth [3][3],
                             ValeurDerivee1 convergence)
  throw (CantorErreurs);
template class Polynome<ValeurDerivee1>;
template inline ostream&                 operator <<
                                         (ostream& s,
                                          const Polynome<ValeurDerivee1>& u);
template inline Polynome<ValeurDerivee1> operator +
                                         (const ValeurDerivee1& t,
                                          Polynome<ValeurDerivee1> u);
template inline Polynome<ValeurDerivee1> operator -
                                         (const ValeurDerivee1& t,
                                          Polynome<ValeurDerivee1> u);
template inline Polynome<ValeurDerivee1> operator *
                                         (const ValeurDerivee1& t,
                                          Polynome<ValeurDerivee1> u);

template class Vecteur3<ValeurDerivee2>;
template inline ostream&                 operator <<
                                         (ostream& s,
                                          const Vecteur3<ValeurDerivee2>& u);
template inline Vecteur3<ValeurDerivee2> operator *
                                         (const ValeurDerivee2& t,
                                          const Vecteur3<ValeurDerivee2>& u);
template inline ValeurDerivee2           angle
                                         (const Vecteur3<ValeurDerivee2>& u,
                                          const Vecteur3<ValeurDerivee2>& v);
template inline Vecteur3<ValeurDerivee2> vecteurOrthogonalNorme
                                         (const Vecteur3<ValeurDerivee2>& u)
  throw(CantorErreurs);
template inline Vecteur3<ValeurDerivee2> vecteurNorme
                                         (Vecteur3<ValeurDerivee2> u)
  throw(CantorErreurs);
template class Rotation<ValeurDerivee2>;
template inline Rotation<ValeurDerivee2> operator -
                                         (const Rotation<ValeurDerivee2>& r);
template void corrigeOrthog (ValeurDerivee2 m [3][3],
                             ValeurDerivee2 orth [3][3],
                             ValeurDerivee2 convergence)
  throw (CantorErreurs);
template class Polynome<ValeurDerivee2>;
template inline ostream&                 operator <<
                                         (ostream& s,
                                          const Polynome<ValeurDerivee2>& u);
template inline Polynome<ValeurDerivee2> operator +
                                         (const ValeurDerivee2& t,
                                          Polynome<ValeurDerivee2> u);
template inline Polynome<ValeurDerivee2> operator -
                                         (const ValeurDerivee2& t,
                                          Polynome<ValeurDerivee2> u);
template inline Polynome<ValeurDerivee2> operator *
                                         (const ValeurDerivee2& t,
                                          Polynome<ValeurDerivee2> u);

#endif
