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
//       Marmottes
//
//$Nom
//>       Field.cpp
//$Resume
//       implementation file for the class
//
//$Description
//       implementation file for the class
//
//$Contenu
//>       FindFarPoint()   
//>       DegeneratedLoop()   
//>       RestrictSpan()   
//>       ArcSpan()   
//>       LeftToRightCrossing()   
//>       class Field         
//>         Field()           
//>         operator =()      
//>         operator -()      
//>         simplifyBoundary()
//>         select()          
//>         selectClosest()          
//>         recursRejectionCone()          
//>         computeRejectionCone()          
//>         isInside()        
//>         computeTargetPoint()        
//>         offsetFromBoundary()        
//>         selectInside()    
//>         rotate()          
//>         initWalk()        
//>         nextPoint()       
//>         stopWalk()    
//    
//$Historique
//       $Log: Field.cpp,v $
//       Revision 2.15  2005/03/04 07:42:15  chope
//       correction de la réduction de l'arc test :
//       il pouvait changer de direction lors de la mise
//       à jour, et passer par les points qui avaient été
//       interdits au préalable (BIBMS-FA-2811-199-CN)
//
//       Revision 2.14  2003/07/30 07:11:35  cantor
//       FA-ID 22 added forgotten symetrical cases and improved robustness
//
//       Revision 2.13 2003/07/28 16:12:32 cantor
//       correction d'une réinitialisation manquante lors d'une
//       modification d'un champ existant
//
//       Revision 2.12 2003/07/09 08:59:54 cantor
//       (ArcSpan, RestrictSpan): correction d'une erreur de calcul de
//       l'étendue d'un arc vu d'un point quelconque de la sphère, qui
//       conduisait à prendre de mauvaises directions de test lors des
//       constructions de champs de vue (FA 22)
//
//       Revision 2.11 2003/02/04 09:27:27 cantor
//       DM-ID 17 Mise à jour du nom du fichier dans le bandeau suite
//       à la modification des extensions.
//
//       Revision 2.10  2002/09/09 13:56:43  cantor
//       Ajout d'une heuristic permettant une simplification du code amont.
//
//       Revision 2.9  2002/09/03 15:05:44  cantor
//       modification de fond (FA15)
//
//       Revision 2.8  2002/09/02 09:19:07  cantor
//       complete revamp to use oriented annotated arcs
//
//       Revision 2.7  2002/02/14 09:41:11  cantor
//       Changement -#include cstdio- en -#include <cstdio>- suite à
//       un problème de compilation sur Sun avec CC
//
//       Revision 2.6  2002/02/04 09:19:29  cantor
//       nouvelle correction du calcul du cône de rejet
//
//       Revision 2.5  2002/01/17 08:40:36  cantor
//       correction de spécifications throw
//
//       Revision 2.4  2001/09/18 16:09:08  cantor
//       ajout des attributs rejectionCone_ et activeRejectionCone_ et des
//       méthodes selectClosest, recursRejectionCone et computeRejectionCone
//       pour accélérer les tests d'appartenance
//
//       Revision 2.3  2001/09/06 09:14:47  cantor
//       cleaned a statement to make a code verification utility happy
//       (despite the fact the utility seems to be wrong here)
//
//       Revision 2.2  2001/08/23 15:07:17  cantor
//       corrected initialization error of the variables pointed to by
//       ptrSide1, ptrSide2 and ptrDegenerated in case of degenerated
//       boundaries
//
//       Revision 2.1  2001/06/22 06:22:16  cantor
//       completely changed the building of fields by spreading an arc
//       we now rely on a specific constructor of Braid
//
//       Revision 1.4  2001/06/12 12:52:20  cantor
//       use an axis and an angle instead of a rotation for spreading
//
//       Revision 1.3  2001/06/08 10:06:21  cantor
//       better implementation of the preceding bug correction
//
//       Revision 1.2  2001/06/07 12:20:04  cantor
//       corrected a bug in the sector filtering
//
//       Revision 1.1  2001/06/05 15:49:14  cantor
//       initial version
//
//$Version
//       $Id: Field.cpp,v 2.15 2005/03/04 07:42:15 chope Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2001 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <cstdio>
#include "cantor/Field.h"
#include "cantor/Braid.h"
#include "cantor/Intervalle.h"
#include "cantor/Creneau.h"

// The limited accuracy of computers prevents from processing fields
// in some configurations. One cannot accurately find point inside of
// too narrow fields. This is also true for arcs on the unit sphere (see
// class Arc). Since the Field class relies on the Arc class, the
// small threshold of this class should be slightly greater than those
// of the Arc class. We have decided to use 4.85e-6 for Field, which
// is one arc second (or its sine, there is almost no difference at
// this level) and to use 3.16e-6 for Arc, which is the square root of
// 1.0e-11 (thus preserving 5 significant digits in base 10 when
// computing 1 - x * x for a computer following IEEE 754 norm).

const double small  = 4.85e-6;

static VecDBL
FindFarPoint (Field::Boundary::const_iterator begin,
              Field::Boundary::const_iterator end)
{ // find a point far from a boundary. This does not mean this point
  // is the farthest possible from the boundary, it only means its
  // distance to the boundary is strictly positive

  if (begin == end)
    return VecDBL (1.0, 0.0, 0.0);

  // if we consider only the first arc, we can take either
  // the axis or the opposite of the axis
  const Arc *alreadyChecked = &(*(begin->begin ()));
  VecDBL v = alreadyChecked->axe ();
  double freeRadius = alreadyChecked->angle ();
  if (freeRadius < 0.5 * M_PI)
  {
    v = -v;
    freeRadius = M_PI - freeRadius;
  }

  // consider all new arcs in turn, updating the point as needed
  for (Field::Boundary::const_iterator i = begin; i != end; ++i)
    for (Field::Loop::const_iterator j = i->begin ();
         j != i->end ();
         ++j)
    {
      alreadyChecked = &(*j);
      const VecDBL& close = alreadyChecked->proche (v);
      double d = close.angleAvecVecteur (v);
      if (d < freeRadius)
      {
        // try to move away from the closest point
        VecDBL rotationAxis =  (d < small)
                               ? ((alreadyChecked->sinus () < small)
                                  ? close.orthogonal ()
                                  : (close ^ alreadyChecked->axe ()))
                               : (close ^ v);
        VecDBL newV = (RotDBL (rotationAxis, 0.5 * (freeRadius - d))) (v);

        // check the distance of the new point to the already checked arcs
        double newD = 10.0;
        bool loop = true;
        for (Field::Boundary::const_iterator k = begin;
             loop && (k != end);
             ++k)
          for (Field::Loop::const_iterator l = k->begin ();
               loop && (l != k->end ());
               ++l)
          {
            double d = l->distance (newV);
            if (d < newD)
              newD = d;

            loop = (&(*l) == alreadyChecked);

          }

        if (newD > d)
        {
          v = newV;
          freeRadius = newD;
        }

    }
  }

  return v;

}

static bool
DegeneratedLoop (const Field::Loop::iterator& begin,
                 const Field::Loop::iterator& end)
{ // check if a loop is degenerated, i.e. if all its arcs are close
  // to one another

  // we begin by searching a small disk overlapping one boundary arc
  VecDBL p;
  double safetyRadius = 0.0;
  for (Field::Loop::iterator i = begin;
       (i != end) && (safetyRadius <= 2.0 * small);
       ++i)
  {
    // compute the safety radius to overlap properly the selected arc
    p = i->intermediaire (0.5 * i->balayage ());
    safetyRadius = i->angle ();
    if (safetyRadius > 0.5 * M_PI)
      safetyRadius = M_PI - safetyRadius;

    // eventually reduce the radius to prevent overlapping other arcs
    for (Field::Loop::const_iterator j = begin;
         (j != end) && (safetyRadius > 2.0 * small);
         ++j)
      if (i != j)
      {
        double dist = j->distance (p);
        if (dist < safetyRadius)
          safetyRadius = dist;
      }

  }

  return (safetyRadius <= 2.0 * small);

}

static void
RestrictSpan(const Arc& a, const VecDBL& point, VecDBL u, VecDBL v,
             double zeta, double *ptrInf, double *ptrSup)
{ // restrict the angular span of an arc as seen from a point that do
  // not belong to this arc taking into account the arc ends

  // zeta: points of the cone corresponding to the theoretical maximal span
  double cz = cos (zeta);
  double sz = sin (zeta);

  // first theoretical point
  VecDBL vInf = cz * point
              + (sz * cos (*ptrInf)) * u
              + (sz * sin (*ptrInf)) * v;

  // last theoretical point
  VecDBL vSup = cz * point
              + (sz * cos (*ptrSup)) * u
              + (sz * sin (*ptrSup)) * v;

  // azimuth angle of the interval center
  double center  = 0.5 * (*ptrInf + *ptrSup);

  // azimuth angles of the arc endpoints
  double startAz = recaleAngle(atan2 (a.debut () | v, a.debut () | u), center);
  double endAz   = recaleAngle(atan2 (a.fin   () | v, a.fin   () | u), center);

  // take arc ends into account
  if (a.diedreContient (vInf))
  {
    if (! a.diedreContient (vSup))
      *ptrSup = (startAz > endAz) ? startAz : endAz;
  }
  else
  {
    if (a.diedreContient (vSup))
    {
      *ptrInf = (startAz > endAz) ? endAz : startAz;
    }
    else
    {
      if (startAz > endAz)
      {
        *ptrInf = endAz;
        *ptrSup = startAz;
      }
      else
      {
        *ptrInf = startAz;
        *ptrSup = endAz;
      }
    }
  }

}

static Creneau
ArcSpan (const Arc& a, const VecDBL& point, VecDBL u, VecDBL v)
{ // compute the angular span of an arc as seen from a point that do
  // not belong to this arc. The result is an angular interval
  double eta    = point.angleAvecVecteur(a.axe ());
  double sinEta = sin (eta);
  double cosEta = cos (eta);
  double middle = atan2(a.axe () | v, a.axe () | u);
  double inf, sup;

  if (sinEta < (a.sinus() - small))
  { // there is no theoretical bound, the span could be from -PI to +PI,
    // it depends only on the arc ends
    if ((a.debut ().angleAvecVecteur (a.fin ()) < small)
        && (a.balayage () > M_PI))
    { // the arc is a complete turn
      inf = -M_PI;
      sup =  M_PI;
    }
    else
    {

      if (eta <= a.angle ())
      { // the point is inside the cone defined by the arc
        inf = atan2 (a.debut () | v, a.debut () | u);
        sup = recaleAngle (atan2 (a.fin () | v, a.fin () | u), inf + M_PI);
      }
      else
      { // the point is outside of the cone defined by the arc
        inf = atan2 (a.fin () | v, a.fin () | u);
        sup = recaleAngle (atan2 (a.debut () | v, a.debut () | u), inf + M_PI);
      }

    }
  }
  else if (sinEta < (a.sinus() + small))
  {
    double cosCos = cosEta * a.cosinus ();
    if (fabs(cosCos) > 1.0e-10)
    { // either the point or its opposite is on the cone

      // the plane orthogonal to "normal" contains all the cone boundary points
      // and is tangent to the cone at point (or -point)
      double s = a.axe () | point;
      VecDBL normal = (a.cosinus () < 0)
                    ? (s * point - a.axe ()) : (a.axe () - s * point);

      inf = atan2(normal | v, normal | u) - 0.5 * M_PI;
      sup = inf + M_PI;
      RestrictSpan(a, point, u, v, (cosCos > 0) ? 0.0 : M_PI, &inf, &sup);

    }
    else
    { // the point and its opposite are both on the cone
      // which is a big circle splitting the sphere in exact hemispheres
      if (point.angleAvecVecteur(a.debut ())
          < point.angleAvecVecteur(a.fin ()))
        inf = atan2 (a.debut () | v, a.debut () | u);
      else
        inf = atan2 (a.fin () | v, a.fin () | u);
      sup = inf;
    }
  }
  else
  { // there are theoretical bounds given by the cone containing the arc
    sup =  asin(a.sinus () / sinEta);
    inf = -sup;
    if (a.cosinus () < 0)
    {
      if (middle < 0)
      {
        inf += M_PI;
        sup += M_PI;
      }
      else
      {
        inf -= M_PI;
        sup -= M_PI;
      }
    }
    inf += middle;
    sup += middle;

    RestrictSpan(a, point, u, v, acos (cosEta / a.cosinus ()), &inf, &sup);

  }

  // return a result between -PI and +PI
  if (sup <= -M_PI)
    return Creneau (Intervalle (inf + 2.0 * M_PI, sup + 2.0 * M_PI));
  else if (inf <= -M_PI)
    return Creneau (Intervalle (-M_PI, sup),
                    Intervalle (inf + 2.0 * M_PI, M_PI));
  else if (sup <= M_PI)
    return Creneau (Intervalle (inf, sup));
  else if (inf <= M_PI)
    return Creneau (Intervalle (-M_PI, sup - 2.0 * M_PI),
                    Intervalle (inf, M_PI));
  else
    return Creneau (Intervalle (inf - 2.0 * M_PI, sup - 2.0 * M_PI));

}

static bool
LeftToRightCrossing (const Arc& testArc, const Arc& boundaryArc)
{ // check if the end of the test arc arrive on the boundary arc
  // from the left or from the right
  // the end point of the test arc MUST be on the boundary arc
  // there is no verification here
  const VecDBL& end = testArc.fin ();

  // tangent of the test arc at the endpoint
  VecDBL endDirection = testArc.axe () ^ end;

  // tangent of the boundary at the test arc endpoint
  VecDBL boundaryDirection = boundaryArc.axe () ^ end;

  return (endDirection | (boundaryDirection ^ end)) > 0;

}

Field::Field (const Cone& c)
  : rejectionCone_ (), activeRejectionCone_ (false),
    targetPoint_ (1.0, 0.0, 0.0), activeTargetPoint_ (false),
    iter_ (0), init_ (false), tolerance_ (1.0e-4)
{ // create a simple field from a cone

  if ((c.angle () <= small) || (c.angle () >= M_PI - small))
  { // consider degenerated cones
    empty_ = (c.angle () < 1.57);  // full sphere or empty cone
  }
  else
  { // the cone really defines a boundary
    Arc a (c);
    boundary_ = Boundary (1, Loop (1, a));
    empty_    = false;
    targetPoint_ = a.intermediaire (M_PI);
    activeTargetPoint_ = true;
  }

  // compute the rejection cone
  computeRejectionCone ();

}

Field::Field (const Arc& a, const VecDBL& axis, double spreading)
  throw (CantorErreurs)
  : empty_ (true), rejectionCone_ (), activeRejectionCone_ (false),
    targetPoint_ (1.0, 0.0, 0.0), activeTargetPoint_ (false),
    iter_ (0), init_ (false), tolerance_ (1.0e-4)
{ // create a field by spreading an arc with a rotation

  // build and annotate the braid resulting from the spreading
  Braid braid (a, axis, spreading);
  braid.simplify ();

  while (! braid.isCompletelyAnnotated ())
  {
    // heuristic 1:
    // detect the arcs that are covered during the spreading
    bool modification = braid.coveringHeuristic (a, axis, spreading);

    // heuristic 2:
    // detect parallel paths
    if (! modification)
      modification = braid.equivalentPathsHeuristic ();

    // heuristic 3:
    // detect the close parallel arcs
    if (! modification)
      modification = braid.closeParallelsHeuristic ();

    // more heuristics can be added here

    if (! modification)
        throw CantorErreurs (CantorErreurs::echec_heuristique);

  }

  // select the arcs corresponding to reunion
  braid.unionBoundary (&boundary_);

  simplifyBoundary ();

  if (boundary_.empty ())
  { // there is no boundary left, the field is either the full sphere or empty
    VecDBL far = FindFarPoint (boundary_.begin (), boundary_.end ());
    empty_ = ! a.balaye (far, axis, spreading);
  }

  // compute the rejection cone
  computeRejectionCone ();

}

Field::Field (const Field& c)
  : empty_ (c.empty_), boundary_ (c.boundary_),
    rejectionCone_ (c.rejectionCone_),
    activeRejectionCone_ (c.activeRejectionCone_),
    targetPoint_ (c.targetPoint_),
    activeTargetPoint_ (c.activeTargetPoint_),
    iter_ (0), init_ (false), tolerance_ (1.0e-4)
{}

Field&
Field::operator = (const Field& c)
{ if (&c != this) // protection against x = x
  {
    empty_               = c.empty_;
    boundary_            = c.boundary_;
    rejectionCone_       = c.rejectionCone_;
    activeRejectionCone_ = c.activeRejectionCone_;
    targetPoint_         = c.targetPoint_;
    activeTargetPoint_   = c.activeTargetPoint_;

    // we do not copy the boundary walk state
    if (iter_ != 0)
      delete iter_;
    iter_       = 0;
    init_       = false;
    tolerance_  = 1.0e-4;

  }

  return *this;

}

Field
Field::operator - () const
{ // inside/outside switch

  if (boundary_.empty ())
  { // there is no boundary: we reverse only the emptiness indicator
    return Field (Cone (VecDBL (1.0, 0.0, 0.0), empty_ ? M_PI : 0.0));
  }
  else
  { // there is a boundary: we reverse the inside and outside points
    // and also reverse the boundary orientation
    Field f;

    // reverse the boundary
    for (Boundary::const_iterator i = boundary_.begin ();
         i != boundary_.end ();
         ++i)
    {
      Loop l;
      for (Loop::const_reverse_iterator j = i->rbegin (); j != i->rend (); ++j)
        l.push_back (-(*j));
      f.boundary_.push_back (l);
    }

    f.computeRejectionCone ();

    return f;

  }

}

void
Field::simplifyBoundary ()
{ // remove malformed loops

  bool modification = true;
  while (modification && ! boundary_.empty ())
  {
    modification = false;

    for (Field::Boundary::iterator i = boundary_.begin ();
         i != boundary_.end () && ! modification;
         ++i)
    {
      // remove empty, too thin and open loops
      if ((i->empty ())
          || DegeneratedLoop (i->begin (), i->end ())
          || (angle (i->front ().debut (), i->back ().fin ()) >= small))
      {
        boundary_.erase (i);
        modification = true;
      }
      else
      {
        Field::Loop::const_iterator k = i->begin ();
        for (Field::Loop::const_iterator j = k++; k != i->end (); j = k++)
          if (angle (j->fin (), k->debut ()) >= small)
          { // remove loops with gaps
            boundary_.erase (i);
            modification = true;
          }
      }
    }
  }
}

void
Field::select (list<Arc> *ptrList) const
  throw (CantorErreurs)
{ // select the arcs that are inside the field
  VecDBL v1, v2;
  int nbInt;

  // splitting the arcs in sections completely inside or outside the field
  for (Boundary::const_iterator i = boundary_.begin ();
       i != boundary_.end ();
       ++i)
    for (Loop::const_iterator j = i->begin (); j != i->end (); ++j)
      for (list<Arc>::iterator k = ptrList->begin (); k != ptrList->end (); ++k)
        if (k->longueur () > small)
        { // compare the current test arc against the current boundary arc
          k->intersection (*j, &nbInt, &v1, &v2);

          if (nbInt)
          { // the arcs intersect each other: we need to split the test arc
            Arc a, b;
            k->partage (v1, &a, &b);

            if (nbInt < 2)
            { // there is only one intersection point, and hence two sub-arcs
              *k = a;
              ++k;
              k = ptrList->insert (k, b);
            }
            else
            { // there are two intersection points, and hence three sub-arcs
              Arc c;

              if (a.diedreContient (v2))
              { // along the initial arc, we encounter first v2 and later v1
                c = b;
                a.partage (v2, &a, &b);
              }
              else
              { // along the initial arc, we encounter first v1 and later v2
                b.partage (v2, &b, &c);
              }

              *k = a;
              ptrList->insert (++k, b);
              k = ptrList->insert (k, c);

            }
          }
        }

  // remove the arcs outside the field
  list<Arc>::iterator next = ptrList->begin ();
  list<Arc>::iterator src  = next++;
  while (src != ptrList->end ())
  {
    double halfAngle = 0.5 * src->balayage ();
    VecDBL middle    = src->intermediaire (halfAngle);
    if (! isInside (middle))
      ptrList->erase (src);

    src = next++;

  }

}

bool
Field::selectClosest (VecDBL *ptrP,
                      const VecDBL& p,
                      int nbPointsToAvoid, const VecDBL** pointsToAvoid) const
{
  // initialize minD high enough to guaranty the first
  // test (d < minD) will succeed
  double minD = 10.0;

  for (Boundary::const_iterator i = boundary_.begin ();
       i != boundary_.end ();
       ++i)
    for (Loop::const_iterator j = i->begin (); j != i->end (); ++j)
    {
      VecDBL localClosest = j->proche (p);
      bool ok = true;
      for (int k = 0; ok && (k < nbPointsToAvoid); ++k)
        ok = (pointsToAvoid [k]->angleAvecVecteur (localClosest) > small);
      if (ok)
      {
        // we have a close point which is allowed
        double d = p.angleAvecVecteur (localClosest);
        if (d < minD)
        {
          *ptrP = localClosest;
          minD = d;
        }
      }
    }

  // return true if we have found a point
  return minD < 5.0;

}

Cone
Field::recursRejectionCone (const VecDBL& p1,
                            const VecDBL& p2,
                            const VecDBL& p3,
                            int depth) const
  throw (CantorErreurs)
{
  // find a rejection cone starting from three base points

  try
  {
    // build a cone going through p1, p2 and p3
    // and not containing the inside point
    Cone c (p1, p2, p3);
    if (isInside (c.axe ()))
    {
      if (isInside (-c.axe ()))
        return Cone (p1, 0.0); // unable to find a proper rejection cone
      else
        c = -c;
    }

    typedef const VecDBL *VecDBLptr;
    VecDBLptr pointsToAvoid [3];
    pointsToAvoid [0] = &p1;
    pointsToAvoid [1] = &p2;
    pointsToAvoid [2] = &p3;
    VecDBL p;
    if (selectClosest (&p, c.axe (), 3, pointsToAvoid))
    {
      if (c.inclus (p))
      {
        // the closest point from the boundary is not rejected, so the
        // current cone is bad, we should improve it to at least reject
        // this point
        if (depth == 2)
        {
          // we are already deep into the recursive stack
          // use a coarse method now: only reduce the angle
          return Cone (c.axe (), c.axe ().angleAvecVecteur (p));
        }
        else
        {
          // try to find better base points
          Cone c1 = recursRejectionCone (p,  p2, p3, depth + 1);
          Cone c2 = recursRejectionCone (p1, p,  p3, depth + 1);
          Cone c3 = recursRejectionCone (p1, p2, p,  depth + 1);
    
          // return the largest rejection cone found
          if (c1.angle () > c2.angle ())
            return (c1.angle () > c3.angle ()) ? c1 : c3;
          else
            return (c2.angle () > c3.angle ()) ? c2 : c3;
    
        }
      }
    }

    // the current cone is good
    return c;

  }
  catch (CantorErreurs ce)
  {
    // we were not able to compute a correct rejection cone
    ce.correction ();
    return Cone (p1, 0.0);
  }

}

void
Field::computeRejectionCone ()
  throw (CantorErreurs)
{
  activeRejectionCone_ = false;
  if (boundary_.empty ())
    return;

  VecDBL p1 = boundary_.begin ()->begin ()->debut ();

  typedef const VecDBL *VecDBLptr;
  VecDBLptr pointsToAvoid [2];
  pointsToAvoid [0] = &p1;
  pointsToAvoid [1] = 0;

  VecDBL p2;
  if (selectClosest (&p2, -p1, 1, pointsToAvoid))
  {

    pointsToAvoid [1] = &p2;
    VecDBL p3;
    if (selectClosest (&p3, -p2, 2, pointsToAvoid))
    {
      rejectionCone_       = recursRejectionCone (p1, p2, p3, 0);
      activeRejectionCone_ = (rejectionCone_.angle () > 0.1)
                          && (! isInside (rejectionCone_.axe (), 0));
    }

  }

}

bool
Field::isInside (const VecDBL& point, bool *ptrDegenerated) const
  throw (CantorErreurs)
{ // check if a point is inside a field

  if (ptrDegenerated != 0)
    *ptrDegenerated = false;

  // handle specific cases of full sphere and empty field
  if (boundary_.empty ())
    return !empty_;

  // first quick check
  if (activeRejectionCone_ && rejectionCone_.inclus (point))
    return false;

  for (Boundary::const_iterator i = boundary_.begin ();
       i != boundary_.end ();
       ++i)
    for (Loop::const_iterator j = i->begin (); j != i->end (); ++j)
    { // the points too close to the boundary are considered inside
      // the field. This approximation is needed because there is no way in
      // this case to build a path from the test point to the reference
      // inside point that only have clean intersection with the boundary
      // arcs
      if (j->distance (point) <= small)
      {
        if (ptrDegenerated != 0)
          *ptrDegenerated = true;
        return true;
      }
    }

  // build an arc from the test point to the target point on the boundary
  Loop::const_iterator crossing = boundary_.begin ()->end ();
  bool recomputed = false;
  if (activeTargetPoint_)
  {
    if (point.angleAvecVecteur (targetPoint_) > (M_PI - small))
    {
      computeTargetPoint (point);
      recomputed = true;
    }
  }
  else
  {
    computeTargetPoint (point);
    recomputed = true;
  }
  Arc a (point, targetPoint_);
  firstCrossing (&a, &crossing);

  if ((crossing == boundary_.begin ()->end ()) && !recomputed)
  { // the old target point seems to be ambiguous
    // try a new one, specially computed for the current point
    computeTargetPoint (point);
    a = Arc (point, targetPoint_);
    firstCrossing (&a, &crossing);
  }

  if (crossing == boundary_.begin ()->end ())
  { // no way ! we don't know how to handle this case
    throw CantorErreurs (CantorErreurs::erreur_interne, __LINE__, __FILE__);
  }

  // we have the first crossing of an arc starting from our test point
  // to the boundary, the test point is inside the field if this first
  // crossing is from left to right according to the arc orientation
  return LeftToRightCrossing (a, *crossing);

}

void
Field::computeTargetPoint (const VecDBL& point) const
  throw (CantorErreurs)
{

  // compute the angular span of the boundary as seen from the test point
  VecDBL u = point.orthogonal();
  VecDBL v = point ^ u;
  Creneau span;

  for (Boundary::const_iterator i = boundary_.begin ();
       i != boundary_.end ();
       ++i)
    for (Loop::const_iterator j = i->begin (); j != i->end (); ++j)
    {
      span += ArcSpan (*j, point, u, v);
    }

  // all arcs starting from the test point, pointing in a direction
  // belonging to the angular span and long enough will cross the
  // boundary. However, not all crossing points are suitable for
  // unambiguous computation. For now, we avoid all vertices (this
  // could be improved in a future version, since some vertices are
  // not ambiguous)
  for (Boundary::const_iterator i = boundary_.begin ();
       i != boundary_.end ();
       ++i)
    for (Loop::const_iterator j = i->begin (); j != i->end (); ++j)
    {
      double alpha = atan2 (j->debut () | v, j->debut () | u);
      span -= Intervalle (alpha - small, alpha + small);
    }

  // now we can choose any shooting direction in the span,
  // we will just take the middle of the largest interval
  // (hence the exact size of the areas removed above around
  //  ambiguous vertices is not really important)
  double length = -1;
  int choice  =  0;
  for (int i = 0; i < span.nombre (); ++i)
  {
    double l = span [i].longueur ();
    if (l > length)
    {
      length   = l;
      choice = i;
    }
  }

  // shoot
  double targetDirection = 0.5 * (span [choice].inf () + span [choice].sup ());
  Arc a (cos (targetDirection) * v - sin (targetDirection) * u,
         0.5 * M_PI, point, M_PI);

  // find the first crossing of the boundary in the shooting direction
  VecDBL v1, v2;
  int nbInt;
  Loop::const_iterator closest = boundary_.begin ()->end ();
  for (Boundary::const_iterator i = boundary_.begin ();
       i != boundary_.end ();
       ++i)
    for (Loop::const_iterator j = i->begin (); j != i->end (); ++j)
    {
      a.intersection (*j, &nbInt, &v1, &v2);
      if (nbInt > 0)
      {
        a = Arc (a.axe (), point, v1);
        closest = j;
      }
    }

  // this should not happen
  if (closest == boundary_.begin ()->end ())
    throw CantorErreurs (CantorErreurs::erreur_interne, __LINE__, __FILE__);

  // this first crossing will be our target point
  targetPoint_ = a.fin ();
  activeTargetPoint_ = true;

}

void
Field::firstCrossing (Arc *ptrArc, Loop::const_iterator *ptrCrossing) const
  throw (CantorErreurs)
{

  // find the first crossing
  VecDBL v1, v2;
  int nbInt;
  Loop::const_iterator crossing = boundary_.begin ()->end ();
  for (Boundary::const_iterator i = boundary_.begin ();
       i != boundary_.end ();
       ++i)
    for (Loop::const_iterator j = i->begin (); j != i->end (); ++j)
    {
      ptrArc->intersection (*j, &nbInt, &v1, &v2);
      if (nbInt > 0)
      {
        *ptrArc = Arc (ptrArc->debut (), v1);
        crossing = j;
      }
    }

  // verify we stay away from the vertices
  if (crossing != boundary_.begin ()->end ())
  {
    if ((ptrArc->fin ().angleAvecVecteur(crossing->debut ()) > small)
        && (ptrArc->fin ().angleAvecVecteur(crossing->fin   ()) > small))
      *ptrCrossing = crossing;
  }

}

double
Field::offsetFromBoundary (const VecDBL& point) const
  throw (CantorErreurs)
{
  // handle specific cases of full sphere and empty field
  if (boundary_.empty ())
    return empty_ ? -M_PI : M_PI;

  double minDistance = M_PI;
  for (Boundary::const_iterator i = boundary_.begin ();
       i != boundary_.end ();
       ++i)
    for (Loop::const_iterator j = i->begin (); j != i->end (); ++j)
    {
      double d = j->distance (point);
      if (d < minDistance)
        minDistance = d;
    }

  // return the minimal distance with a negative sign outside of the field
  return isInside (point) ? minDistance : -minDistance;

}

Secteurs
Field::selectInside (const Secteurs& s) const
  throw (CantorErreurs)
{ // select the parts of a sector which are inside the field

  // handling degenerated cases of full sphere or empty field
  if (boundary_.empty ())
  { if (empty_)
      return Secteurs (s.cone (), s.cone ().axe ().orthogonal (),
                       Creneau (0.0, 0.0));
    else
      return s;
  }

  // first quick check
  if (activeRejectionCone_)
  {
    double a1 = rejectionCone_.axe ().angleAvecVecteur (s.cone ().axe ());
    double a2 = s.cone ().angle ();
    if ((a1 + a2) <= rejectionCone_.angle ())
    {
      // s belongs to a cone which is rejected as a whole
      return Secteurs (s.cone (), s.cone ().axe ().orthogonal (),
                       Creneau (0.0, 0.0));
    }
  }

  // convert the sector into a list of arcs
  list<Arc> ls;
  VecDBL axis, beg, end;
  double angle = s.angle ();
  double spread;
  for (int i = 0; i < s.nombre (); ++i)
  { // create an arc from a sector item
    s.diedre (i, &axis, &beg, &end, &spread);
    ls.push_back (Arc (axis, angle, beg, spread));
  }

  // keep only the inside arcs
  select (&ls);

  // convert the list of arcs back to a sector
  Creneau selected;
  VecDBL u, v;
  if (ls.empty ())
  { // there is no arc at all, the references are meaningless
    u = s.cone ().axe ().orthogonal ();
    v = s.cone ().axe () ^ u;
  }
  else
  { // there is at least one arc, we take the references from the first one
    u = ls.front ().u ();
    v = ls.front ().v ();
  }

  for (list<Arc>::const_iterator j = ls.begin (); j != ls.end (); ++j)
  { // convert an arc into in angular interval
    double low  = atan2 (j->debut () | v, j->debut () | u);
    double high = low + j->balayage ();

    selected += Intervalle (low, high);

  }

  return Secteurs (s.cone (), u, selected);

}

const Field&
Field::combine (const Field& c, bool intersection)
  throw (CantorErreurs)
{ // generic function to compute both reunion and intersection

  // the boundary is going to change, we stop the walk
  stopWalk ();
  activeRejectionCone_ = false;
  activeTargetPoint_   = false;

  if (boundary_.empty ())
  { // handle the specific cases of full sphere and empty field
    if (empty_ ^ intersection)
    { // the full sphere is the neutral element for intersection
      // the empty field is the neutral element for union
      *this = c;
    }
    return *this;
  }

  if (c.boundary_.empty ())
  { // handle the specific cases of full sphere and empty field
    if (! (c.empty_ ^ intersection))
    { // the full sphere is the neutral element for intersection
      // the empty field is the neutral element for union
      *this = c;
    }
    return *this;
  }

  // create the two strands of a braid from the boundaries of both fields
  Braid b1 (this, boundary_.begin (), boundary_.end ());
  Braid b2 (&c, c.boundary_.begin (), c.boundary_.end ());
  Braid::intertwine (&b1, &b2);

  // gather the strands in a uniq list
  b1.absorb (&b2);
  b1.simplify ();

  // at the beginning, no arc is annotated
  b1.initAnnotations ();

  // annotation loop
  for (bool modification = true; modification;)
  {
    modification = false;

    // annotate unambiguous arcs
    b1.identifyArcs (this, &c);

    if (! b1.isCompletelyAnnotated ())
    {
      // there are some ambiguous arcs left
      // we apply several heuristics to remove the ambiguities

      // heuristic 1:
      // splitting arcs where only one part is ambiguous
      modification = b1.splittingHeuristic ();

      // heuristic 2:
      // detect parallel paths
      if (! modification)
        modification = b1.equivalentPathsHeuristic ();

      // heuristic 3:
      // peel flakes on the boundary
      if (! modification)
        modification = b1.peelingHeuristic ();

      // more heuristics can be added here

      if (! modification)
        throw CantorErreurs (CantorErreurs::echec_heuristique);

    }

  }

  // select the arcs according to the desired operation (intersection vs union)
  if (intersection)
    b1.intersectionBoundary (&boundary_);
  else
    b1.unionBoundary        (&boundary_);

  simplifyBoundary ();

  if (boundary_.empty ())
  { // there is no boundary left, the field is either the full sphere or empty
    //  - we cannot have c1 inter c2 == full sphere because neither of the
    //    fields was the full sphere
    //  - we cannot have c1 union c2 == empty because neither of the fields
    //    was empty
    // therefore we have either c1 inter c2 == empty or c1 union c2 == sphere
    // so we can deduce the emptyness from the operation type itself
    empty_ = intersection;
    boundary_.clear ();
  }

  // compute the rejection cone
  computeRejectionCone ();

  return *this;

}

void
Field::rotate (const RotDBL& r)
{ // rotate a field

  // the boundary is going to change, we stop the walk
  stopWalk ();

  // moving the boundary
  for (Boundary::iterator i = boundary_.begin ();
       i != boundary_.end ();
       ++i)
    for (Loop::iterator j = i->begin (); j != i->end (); ++j)
      j->appliqueRotation (r);

  // moving the rejection cone
  rejectionCone_ = Cone (r (rejectionCone_.axe ()),
                         rejectionCone_.angle ());

  // moving the target point
  targetPoint_ = r(targetPoint_);

}

void
Field::spread (const VecDBL& axis, double spreading)
  throw (CantorErreurs)
{ // spread a field using a rotation

  // the boundary is going to change, we stop the walk
  stopWalk ();

  // the spread field is the union of the initial field and the
  // spreading of all its boundary arcs
  Field tmp;
  for (Boundary::const_iterator i = boundary_.begin ();
       i != boundary_.end ();
       ++i)
    for (Loop::const_iterator j = i->begin (); j != i->end (); ++j)
      tmp += Field (*j, axis, spreading);
  *this += tmp;

}

void
Field::applyMargin (double m)
  throw (CantorErreurs)
{ // add (or remove according to the sign) an angular margin from the field

  // the boundary is going to change, we stop the walk
  stopWalk ();

  // we do not consider too small margins
  if ((m >= -small) && (m <= small))
    return;

  // create the field containing all the points that are close to the boundary
  Field widenBoundary;
  for (Boundary::const_iterator i = boundary_.begin ();
       i != boundary_.end ();
       ++i)
    for (Loop::const_iterator j = i->begin (); j != i->end (); ++j)
    { // spread a neighborhood cone along the arc
      Cone c (j->debut (), fabs (m));
      Field stripe (c);
      stripe.spread (j->axe (), j->balayage ());
      widenBoundary += stripe;
    }

  // add (or remove) the points that are close to the boundary
  if (m > 0.0)
    *this += widenBoundary;
  else
    *this -= widenBoundary;

}

void
Field::initWalk (double tolerance)
{ // initialize the iterators to walk the boundary step by step
  stopWalk ();

  tolerance_ = tolerance;

  if (! boundary_.empty ())
  { // prepare the first iterator
    i_    = boundary_.begin ();
    j_    = i_->begin ();
    iter_ = new ArcIterateur (*j_, tolerance_);
    (void) iter_->suivant ();
    init_ = true;
  }

}

bool
Field::nextPoint (VecDBL *ptrPoint, bool *ptrLast)
{ // walk step by step along the boundary
  //  - a boundary is a set of disjoint loops
  //  - a loop is a set of arcs
  //  - an arc can be walk as a set of points
  // Therefore, there are three nested iterators

  // Furthermore, we want to warn the user that there will be a leap
  // from one loop to the other just before the leap, so the iterators
  // are handled one point ahead of the caller, so this is rather
  // tricky ...

  if (! init_)
    return false;

  // update the point that will be provided to the user
  *ptrPoint = iter_->point ();
  *ptrLast  = false;

  if (!iter_->suivant ())
  { // the current arc is finished, we have to swith to the next one
    delete iter_;

    if (++j_ != i_->end ())
    { // we are still in the same loop
      iter_ = new ArcIterateur (*j_, tolerance_);
      (void) iter_->suivant ();
    }
    else
    { // the loop is also finished, the next point will be after a
      // leap to a new loop
      *ptrLast = true;

      if (++i_ != boundary_.end ())
      { // prepare for the next loop
        j_    = i_->begin ();
        iter_ = new ArcIterateur (*j_, tolerance_);
        (void) iter_->suivant ();
      }
      else
      { // there is no loop anymore, we have finished
        iter_ = 0;
        init_ = false;
        return true;
      }
    }

  }

  return true;

}

void
Field::stopWalk ()
{ if (iter_)
    delete iter_;
  iter_ = 0;
  init_ = false;
}
