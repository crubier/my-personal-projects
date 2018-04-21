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
//>       Arc.h
//
//$Resume
//       fichier d'en-tête de la classe Arc
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class Arc
//
//$Historique
//       $Log: Arc.h,v $
//       Revision 2.17  2002/12/10 14:51:00  cantor
//       DM-ID 12 Ajout d'un destructeur pour prévenir celui créer par le compilateur
//
//       Revision 2.16  2002/12/02 13:32:04  cantor
//       DM-ID 12 Réorganisation des fichiers H de déclaration des classes selon le principe public/protected/private.
//
//       Revision 2.15  2002/09/03 15:09:16  cantor
//       correction de 'throw', nouvelle méthode 'balaye' (FA15)
//
//       Revision 2.14  2001/09/18 16:06:46  cantor
//       ajout de la méthode Arc::proche
//
//       Revision 2.13  2001/06/22 06:24:48  cantor
//       correction d'un bug dans l'opérateur - de la classe Arc
//
//       Revision 2.12  2001/06/05 15:24:13  cantor
//       remontée d'exceptions lancées par les classes sous-jacentes
//
//       Revision 2.11  2000/08/09 14:36:43  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 2.10.4.1  2000/03/30 15:36:07  cantor
//       ajout du copyright CNES
//
//       Revision 2.10  1998/06/24 16:48:45  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 2.9  1998/05/12 12:59:37  luc
//       inversion d'une expression pour contourner un bug du compiplateur SUN 4.0
//
//       Revision 2.8  1998/04/26 15:23:39  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 2.7  1998/04/18 19:07:31  luc
//       élimination de la méthode estValide
//
//       Revision 2.6  1998/01/22 10:38:10  luc
//       amélioration de l'en-tête de classe
//
//       Revision 2.5  1997/07/08 10:14:22  luc
//       ajout d'un en-tête de fichier
//       ajout d'une méthode de test des recouvrements
//       séparation en deux fichiers Arc.h et ArcIterateur.h
//
//       Revision 2.4  1997/03/26 06:39:37  luc
//       changement des conventions de nommage
//       
//       Revision 2.3  1997/03/24 09:20:18  luc
//       passage de SCCS à RCS
//       
//       Revision 2.2  1996/08/06 17:15:59  luc
//       ajout d'un constructeur
//       
//       Revision 2.1  1996/07/19 12:23:04  luc
//       refonte de la classe
//       (ajout des méthodes distance, diedreContient, partage, intersection,
//       appliqueRotation, - unaire)
//       
//       Revision 1.5  1995/01/25 16:14:40  mercator
//       ajout de const devant les arguments reference des constructeurs
//       
//       Revision 1.4  1994/12/22 16:19:39  mercator
//       utilisation de retours de references constantes pour optimiser la vitesse
//       
//       Revision 1.3  1994/11/26 15:12:29  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.2  1994/08/11 13:59:48  mercator
//       ajout de qualificatifs const dans la signature de initvecteurs
//       
//       Revision 1.1  1994/07/27 14:56:42  luc
//       Initial revision
//
//$Version
//       $Id: Arc.h,v 2.17 2002/12/10 14:51:00 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000-2001 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_Arc_h
#define __cantor_Arc_h

#include "cantor/Cone.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class Arc
//$Resume
//       modélisation d'un arc de cercle sur la sphère unité
//
//$Description
//       modélisation d'un arc de cercle sur la sphère
//       (arc de petit ou de grand cercle)
//
//$Usage
//>     construction : 
//          sans argument, à partir d'un cône, à partir d'un vecteur,
//          à partir d'un axe de cône et d'un angle d'ouverture,
//          à partir d'un axe de cône et de deux extrémités,
//          à partir d'un cône (axe et angle) et de deux extrémités
//>     utilisation  : 
//>       Arc& operator =       () 
//          affectation
//>       VecDBL proche         () 
//          retourne le point de l'arc le plus proche de p
//>       double distance       () 
//          retourne la distance angulaire entre p et le point de
//          l'arc le plus proche
//>       bool diedreContient   () 
//          indique si p est dans le dièdre défini par l'arc
//>       void partage          () 
//          calcule les deux arcs résultant du partage de l'instance
//          de part et d'autre de p. Si p n'est pas dans l'arc, le
//          sous-arc av sera égal à l'instance et ap sera de longueur
//          nulle, sinon l'arc av va de debut à p et l'arc ap va de p
//          à fin. Il est licite de faire pointer av ou ap sur
//          l'instance courante.
//>       void intersection     () 
//          retourne les intersections entre l'arc et un cône ou un
//          autre arc. S'il y a deux intersections, elles sont donnees
//          dans l'ordre : deb < v1 < v2 < fin.
//>       bool balaye           () 
//          indique si l'instance recouvre un point pendant un balayage
//>       bool recouvre         () 
//          indique si l'instance recouvre l'arc a (à epsilon près).
//>       void appliqueRotation () 
//          remplace l'instance par son image à travers une rotation
//>       const VecDBL& axe     () 
//          retourne l'axe
//>       const VecDBL& debut   () 
//          retourne le point début
//>       const VecDBL& fin     () 
//          retourne le point de fin
//>       VecDBL intermediaire  () 
//          retourne un point de intermédiaire d'angle de position
//          alpha (si alpha n'est pas entre 0 et balayage_, le point
//          ne sera pas vraiment intermédiaire ...)
//>       double cosinus        () 
//          retourne une copie du cosinus de l'ouverture du cercle
//>       double sinus          () 
//          retourne une copie du sinus de l'ouverture du cercle
//>       double angle          () 
//          retourne une copie de l'angle d'ouverture du cercle
//>       const VecDBL& u       () 
//          retourne le premier vecteur canonique de la base calcul
//          des points intermédiaires
//>       const VecDBL& v       () 
//          retourne le deuxième vecteur canonique de la base calcul
//          des points intermédiaires
//>       const VecDBL& w       () 
//          retourne le troisième vecteur canonique de la base calcul
//          des points intermédiaires
//>       double balayage       () 
//          retourne l'angle de balayage autour de l'axe
//>       double longueur       () 
//          retourne la longueur (en radians) de l'arc
//>       Arc operator -        () 
//         retourne un arc renversé par rapport à l'instance (c'est à
//         dire contenant les mêmes points, mais parcouru en sens
//         inverse)
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class Arc
{
  public :

  // constructeurs
  Arc ()
   : axe_ (1.0, 0.0, 0.0),
     cos_ (1.0), sin_ (0.0), angle_ (0.0),
     deb_ (1.0, 0.0, 0.0), fin_ (1.0, 0.0, 0.0),
     u_   (0.0, 0.0, 0.0), v_   (0.0, 0.0, 0.0), w_ (1.0, 0.0, 0.0),
     balayage_ (0.0)
  {}

  Arc (const VecDBL& axe, double angle = 0.5 * M_PI)
    throw (CantorErreurs);

  Arc (const Cone& c)
    throw (CantorErreurs);

  Arc (const VecDBL& debut, const VecDBL& fin)
    throw (CantorErreurs);

  Arc (const VecDBL& axe, const VecDBL& debut, const VecDBL& fin)
    throw (CantorErreurs)
  { initVecteurs (axe, 0.5 * M_PI, debut, fin); }

  Arc (const VecDBL& axe, double angle,
       const VecDBL& debut, const VecDBL& fin)
    throw (CantorErreurs)
  { initVecteurs (axe, angle, debut, fin); }

  Arc (const VecDBL& axe, double angle,
       const VecDBL& debut, double balayage)
    throw (CantorErreurs);

  // copie constructeur et affectation
  Arc (const Arc& a)
    : axe_ (a.axe_), cos_ (a.cos_), sin_ (a.sin_), angle_ (a.angle_),
      deb_ (a.deb_), fin_ (a.fin_),
      u_   (a. u_),  v_   (a.v_), w_ (a.w_),
      balayage_ (a.balayage_)
  {}

  Arc& operator = (const Arc& a);

  // destructeur
  ~Arc () {}

  const VecDBL& axe      () const { return axe_; }
  const VecDBL& debut    () const { return deb_; }
  const VecDBL& fin      () const { return fin_; }

  VecDBL  intermediaire (double alpha) const
  { return u_ * cos (alpha) + v_ * sin (alpha) + w_; }

  double        cosinus  () const { return cos_;      }
  double        sinus    () const { return sin_;      }
  double        angle    () const { return angle_;    }
  const VecDBL& u        () const { return u_;        }
  const VecDBL& v        () const { return v_;        }
  const VecDBL& w        () const { return w_;        }
  double        balayage () const { return balayage_; }
  double        longueur () const { return balayage_ * sin_; }

  VecDBL        proche         (const VecDBL& p) const;
  double        distance       (const VecDBL& p) const;
  bool          diedreContient (const VecDBL& p) const;
  void          partage        (const VecDBL& p, Arc *ptrAv, Arc *ptrAp) const;

  void          intersection (const VecDBL& a, double cosinus,
                              int *ptrNbInt, VecDBL *ptrV1, VecDBL *ptrV2
                             ) const;
  void          intersection (const Cone& c,
                              int *ptrNbInt, VecDBL *ptrV1, VecDBL *ptrV2
                             ) const
  { intersection (c.axe (), c.cosinus (), ptrNbInt, ptrV1, ptrV2); }
  void          intersection (const Arc& a,
                              int *ptrNbInt, VecDBL *ptrV1, VecDBL *ptrV2
                             ) const;

  bool recouvre (const Arc& a, double epsilon) const;

  bool balaye (const VecDBL& point,
               const VecDBL& axe, double balayage) const
    throw (CantorErreurs);

  void appliqueRotation (const RotDBL& r);

  Arc operator - () const;

  private :

  VecDBL            axe_;  // définition du cône sur lequel est appuyé l'arc
  double            cos_;
  double            sin_;
  double            angle_;

  VecDBL            deb_;  // point extrêmes
  VecDBL            fin_;

  VecDBL            u_;    // repère canonique de calcul des points
  VecDBL            v_;    // intermédiaires (orthogonal mais non normé)
  VecDBL            w_;

  double            balayage_; // angle de balayage autour de l'axe

  // fonction d'initialisation utilisée par (presque) tous les constructeurs
  void initVecteurs (const VecDBL& axe, double alpha,
                     const VecDBL& debut, const VecDBL& fin)
    throw (CantorErreurs);

};

#endif
