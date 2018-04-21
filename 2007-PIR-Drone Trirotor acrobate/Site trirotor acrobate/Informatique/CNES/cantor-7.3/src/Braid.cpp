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
//>       Braid.cpp
//$Resume
//       implementation file for the Braid class
//
//$Description
//       implementation file for the Braid class
//
//$Contenu
//>       SpliceArcs()                 
//>       TestPoint()                 
//>       SplitArc()                  
//>       RemoveNullUpstreamArcs()    
//>       RemoveNullDownstreamArcs()  
//>       GenerateTrail()  
//>       class Braid                 
//>         operator =()              
//>         initAnnotations()         
//>         identifyArcs()            
//>         simplify()                
//>         absorb()                  
//>         isCompletelyAnnotated()   
//>         coveringHeuristic()      
//>         closeParallelsHeuristic()      
//>         splittingHeuristic()      
//>         equivalentPathsHeuristic()
//>         boundary()                
//$Historique
//       $Log: Braid.cpp,v $
//       Revision 1.12  2003/02/04 09:25:33  cantor
//       DM-ID 17 Mise à jour du nom du fichier dans le bandeau suite à la modification des extensions.
//
//       Revision 1.11  2002/09/09 13:54:31  cantor
//       Modification de la logique d'annotation des arcs.
//
//       Revision 1.10  2002/09/06 08:32:22  cantor
//       ajout d'une protection contre le marquage des arcs de longueurs nulles (FA 15)
//
//       Revision 1.9  2002/09/03 15:00:39  cantor
//       correction d'un 'throw', suppression de la méthode 'isCovered' (FA15)
//
//       Revision 1.8  2002/09/02 09:18:39  cantor
//       complete revamp to use oriented annotated arcs
//
//       Revision 1.7  2002/08/30 08:57:20  cantor
//       Correction de la FA 17
//
//       Revision 1.6  2002/01/17 08:40:36  cantor
//       correction de spécifications throw
//
//       Revision 1.5  2001/09/12 14:23:32  cantor
//       corrected a free memory read error
//       (an iterator was incremented in a for loop despite it was erased
//       during the last iteration of the loop)
//
//       Revision 1.4  2001/08/23 15:08:34  cantor
//       added a test to detect alignement degenerated cases during spreading
//       allowed negative values for the spreading angles
//
//       Revision 1.3  2001/06/22 06:34:24  cantor
//       added the isCovered, coveringHeuristic and closeParallelsHeuristic methods
//       revamped the constructor by spreading of an arc
//       corrected various degenerated case handling errors
//
//       Revision 1.2  2001/06/12 12:51:47  cantor
//       use an axis and an angle instead of a rotation for spreading
//
//       Revision 1.1  2001/06/05 15:41:34  cantor
//       initial version
//
//$Version
//       $Id: Braid.cpp,v 1.12 2003/02/04 09:25:33 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2001 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <CantorConfigNoInstall.h>
#include "cantor/Braid.h"
#include "cantor/Node.h"

// The limited accuracy of computers prevents from processing fields
// in some configurations. One cannot accurately find point inside of
// too narrow fields. This is also true for arcs on the unit sphe (see
// class Arc). Since the Field class relies on the Arc class, the
// small threshold of this class should be slightly greater than those
// of the Arc class. We have decided to use 4.85e-6 for Field, which
// is one arc second (or its sine, there is almost no difference at
// this level) and to use 3.16e-6 for Arc, which is the square root of
// 1.0e-11 (thus preserving 5 significant digits in base 10 when
// computing 1 - x * x for a computer following IEEE 754 norm).

const double small  = 4.85e-6;

// iterator over annotated arcs
typedef list<AnnotatedArc>::iterator iter;

static void
SpliceArcs (list<AnnotatedArc> *ptrDst, list<AnnotatedArc> *ptrSrc)
{
#ifdef STL_LIST_SPLICE_MOVES_OBJECTS

  // splice is broken, we should copy the elements and update the pointers
  // this is weird ...
  for (iter i = ptrSrc->begin (); i != ptrSrc->end (); ++i)
  {
    // copy one arc
    iter copy = ptrDst->insert (ptrDst->end (), *i);

    // update the pointers
    i->replace (&(*copy));

  }

  // clear the old list
  ptrSrc->clear ();

#else

  // we can safely use the splice method
  ptrDst->splice (ptrDst->end (), *ptrSrc);

#endif
}

inline VecDBL
TestPoint (const iter& i)
{
  return i->intermediaire (0.5 * i->balayage ());
}

static void
SplitArc (list<AnnotatedArc> *ptrList, iter i, VecDBL p,
          iter *ptrUpstream, iter *ptrDownstream)
  throw (CantorErreurs)
{ // replace an arc by its parts apart from a point

  // topological aspect : the two parts replace the initial arc in the
  // topological structure, they are connected to other arcs if the
  // initial arc was connected to other arcs, they are not connected
  // if the arc was not connected. In every case they are connected to
  // each other with a simple node at the splitting point. This simple
  // node will probably be replaced by a multiple node by the caller.

  // storage aspect : the two parts are inserted in the list, the
  // upstream part before the downstream part, they replace completely
  // the initial arc which is removed. The iterators pointed to by
  // ptrUpstream and ptrDownstream are updated to point to the two
  // parts. Some null length arcs can be created by this function, if
  // the point is too close from one of the vertices of the initial
  // arc.

  Arc a, b;
  i->partage (p, &a, &b);

  // create the arcs in the storage list
  AnnotatedArc annotatedA (a, i->origin ());
  ptrList->insert (i, annotatedA);
  *ptrUpstream = i;
  --(*ptrUpstream);

  AnnotatedArc annotatedB (b, i->origin ());
  ptrList->insert (i, annotatedB);
  *ptrDownstream = i;
  --(*ptrDownstream);

  // preserve the topology
  i->replace (&(*(*ptrUpstream)), &(*(*ptrDownstream)));

  // removing the initial arc
  ptrList->erase (i);

}

static iter
RemoveNullUpstreamArcs (list<AnnotatedArc> *ptrList, iter i)
{ // remove some null arcs while going upstream
  // (some null arcs can remain, for example the ones between multiple nodes)
  while (i->removeIfPossible ())
  {
    if (i == ptrList->begin ())
      return ptrList->erase (i);
    else
    {
      i = ptrList->erase (i);
      i--;
    }
  }

  return i;

}

static iter
RemoveNullDownstreamArcs (list<AnnotatedArc> *ptrList, iter i)
{ // remove some null arcs while going downstream
  // (some null arcs can remain, for example the ones between multiple nodes)
  while (i->removeIfPossible ())
  {
    i = ptrList->erase (i);
    if (i == ptrList->end ())
      return i;
  }

  return i;

}

static void
GenerateTrail (const Arc& a, const VecDBL& axis, double spreading,
               bool closeLeavesTrack, bool farLeavesTrack,
               const void *origin, list<AnnotatedArc> *ptrTrail)
{ // generate a trail from the spreading

  // BEWARE this function works ONLY if the closest point of the
  // spreaded arc is exactly at its beginning and if the farthest
  // point of the spreaded arc is exactly at its end

  // original arc
  ptrTrail->push_back (AnnotatedArc (a, origin));
  list<AnnotatedArc>::reference a1 = ptrTrail->back ();

  // track left by the farthest point
  if (farLeavesTrack)
  {
    ptrTrail->push_back (AnnotatedArc (Arc (axis,
                                            axis.angleAvecVecteur (a1.fin ()),
                                            a1.fin (), spreading),
                                       origin));
  }
  list<AnnotatedArc>::reference b1 = ptrTrail->back ();

  // reversed image of the original arc
  ptrTrail->push_back (AnnotatedArc (-a, origin));
  list<AnnotatedArc>::reference c1 = ptrTrail->back ();
  c1.appliqueRotation (RotDBL (axis, spreading));

  // track left by the closest point
  if (closeLeavesTrack)
  {
    VecDBL mAxis = -axis;
    ptrTrail->push_back (AnnotatedArc (Arc (mAxis,
                                            mAxis.angleAvecVecteur (c1.fin ()),
                                            c1.fin (), spreading),
                                       origin));
  }
  list<AnnotatedArc>::reference d1 = ptrTrail->back ();

  if (farLeavesTrack)
  {
    a1.connect  (&b1);
    b1.connect  (&c1);
  }
  else
  { // there is no farthest point track
    // (it is degenerated into a single point)
    a1.connect  (&c1);
  }

  if (closeLeavesTrack)
  {
    c1.connect  (&d1);
    d1.connect  (&a1);
  }
  else
  { // there is no closest point track
    // (it is degenerated into a single point)
    c1.connect  (&a1);
  }

}


Braid::Braid (const Field *origin,
              vector< vector<Arc> >::const_iterator begin,
              vector< vector<Arc> >::const_iterator end)
  throw (CantorErreurs)
{ // create a braid strand from the boundary of one field

  for (vector< vector<Arc> >::const_iterator i = begin; i != end; ++i)
  { // handling all loops
    list<AnnotatedArc> loop;

    // insert the arcs of the first loop in the list
    for (vector<Arc>::const_iterator j = i->begin (); j != i->end (); ++j)
      loop.push_back (AnnotatedArc (*j, origin));

    // put the simple nodes on the loop. Warning: the geometric
    // connexions represented by the nodes has nothing to do with the
    // list structure of the braid. This list structure is only a
    // storage device and we use iterators to go through all arcs. On
    // the other hand, the nodes build a topological structure and
    // both the nodes and the arcs are used to propagate annotations
    // along this structure. The following connection algorithm shows
    // the nodes can be deduced from the list, but this is true only
    // at the very beginning of the build (that is to say only
    // here). As soon as we begin splitting and intertwining arcs,
    // this is not more true and the two structures should not be
    // confused.
    iter k    = loop.begin ();
    iter next = k;
    while (++next != loop.end ())
    {
      k->connect (&(*next));
      k = next;
    }

    // close the loop
    k->connect (&(*loop.begin ()));

    // add the loop to the braid
    SpliceArcs (&arcs_, &loop);

  }

}

Braid::Braid (const Arc& a, VecDBL axis, double spreading)
  throw (CantorErreurs)
{ // build a braid from an arc and a spreading rotation
  if (spreading < 0)
  {
    axis      = -axis;
    spreading = -spreading;
  }

  double dotProd = a.axe () | axis;

  // handle some degenerated cases
  if (fabs (dotProd) > 1.0 - small * small)
  {
    Arc orientedA = (((a.axe () ^ a.debut ()) | axis) * dotProd >= 0.0) ? -a : a;
    arcs_.push_back (AnnotatedArc (orientedA, 0));
    arcs_.push_back (AnnotatedArc (Arc (axis,
                                        angle (axis, orientedA.fin ()),
                                        orientedA.fin (),
                                        spreading),
                                   0));
    Arc ra (-orientedA);
    ra.appliqueRotation (RotDBL (axis, spreading));
    arcs_.push_back (AnnotatedArc (ra, 0));
    arcs_.push_back (AnnotatedArc (Arc (axis,
                                        angle (axis, ra.fin ()),
                                        ra.fin (),
                                        -spreading),
                                   0));

    list<AnnotatedArc>::iterator i4 = arcs_.begin ();
    list<AnnotatedArc>::iterator i1 = i4++;
    list<AnnotatedArc>::iterator i2 = i4++;
    list<AnnotatedArc>::iterator i3 = i4++;
    i1->connect (&(*i2));
    i2->connect (&(*i3));
    i3->connect (&(*i4));
    i4->connect (&(*i1));
    i1->annotate (AnnotatedArc::unionAnnotated);
    i2->annotate (AnnotatedArc::unionAnnotated);
    i3->annotate (AnnotatedArc::unionAnnotated);
    i4->annotate (AnnotatedArc::unionAnnotated);

    return;

  }

  if (spreading < small)
  {
    // if the spreading is small, only the arc and its image matter
    arcs_.push_back (AnnotatedArc (a, 0));

    Arc ra (-a);
    ra.appliqueRotation (RotDBL (axis, spreading));
    arcs_.push_back (AnnotatedArc (ra, 0));

    list<AnnotatedArc>::iterator j = arcs_.begin ();
    list<AnnotatedArc>::iterator i = j++;
    i->connect (&(*j));
    j->connect (&(*i));

    i->annotate (AnnotatedArc::unionAnnotated);
    j->annotate (AnnotatedArc::unionAnnotated);

    return;

  }

  if (spreading > (M_PI + M_PI - small))
  {
    // if the spreading is a complete turn, only the trails left by
    // the points close and far from the axis matter
    Arc a1 (axis, a.distance (axis));
    arcs_.push_back (AnnotatedArc (-a1, 0));
    Arc a2 (-axis, a.distance (-axis));
    arcs_.push_back (AnnotatedArc (-a2, 0));

    list<AnnotatedArc>::iterator j = arcs_.begin ();
    list<AnnotatedArc>::iterator i = j++;
    i->connect (&(*i));
    j->connect (&(*j));

    i->annotate (AnnotatedArc::unionAnnotated);
    j->annotate (AnnotatedArc::unionAnnotated);

    return;

  }

  // split the arc into oriented NOT CONNECTED sub-arcs as needed to
  // handle the contributions of the closest and farthest points with
  // regard to the spreading axis
  double beta  = sqrt ((1.0 - a.cosinus () * a.cosinus ())
               / (1.0 - dotProd * dotProd));
  VecDBL close = (a.cosinus () - beta * dotProd) * a.axe () + beta * axis;
  VecDBL far   = (a.cosinus () + beta * dotProd) * a.axe () - beta * axis;

  bool completeTurn     = (angle (a.debut (), a.fin ()) < small)
                        && (a.balayage () > M_PI);
  bool closeLeavesTrack = ((close | axis) < 1.0 - small * small)
                        && (completeTurn || a.diedreContient (close));
  bool farLeavesTrack   = ((far | axis) > -1.0 + small * small)
                        && (completeTurn || a.diedreContient (far));

  if (completeTurn)
  {
    // place the end points of the arc at the closest point,
    // in order to avoid spurious trails generated by badly chosen end points
    Arc turnedA (a.axe (), a.angle (), close, 2.0 * M_PI);

    // build the braids generated by two sub-arcs,
    // both oriented from the closest point to the farthest point
    Arc s1, s2;
    turnedA.partage (far, &s1, &s2);

    // s1 goes from close to far
    GenerateTrail (s1, axis, spreading, closeLeavesTrack, farLeavesTrack,
                   &s1, &arcs_);

    // s2 goes from far to close, so -s2 goes from close to far
    Braid other;
    GenerateTrail (-s2, axis, spreading, closeLeavesTrack, farLeavesTrack,
                   &s2, &(other.arcs_));

    // intertwine the two trails
    intertwine (this, &other);
    absorb (&other);

  }
  else
  {

    if (a.diedreContient (close))
    {
      if (a.diedreContient (far))
      {
        // build the braids generated by three sub-arcs,
        // all oriented from the closest point to the farthest point
        Arc s1, s2, s3;
        a.partage (close, &s1, &s2);

        if (s1.diedreContient (far))
        {
          s3 = s2;
          s1.partage (far, &s1, &s2);

          // s1 goes from begin to far
          GenerateTrail (s1, axis, spreading, true, farLeavesTrack,
                         &s1, &arcs_);

          // s2 goes from far to close, so -s2 goes from close to far
          Braid other1;
          GenerateTrail (-s2, axis, spreading, closeLeavesTrack, farLeavesTrack,
                         &s2, &(other1.arcs_));

          // s3 goes from close to end
          Braid other2;
          GenerateTrail (s3, axis, spreading, closeLeavesTrack, true,
                         &s3, &(other2.arcs_));

          // intertwine the three trails
          intertwine (this, &other1);
          absorb (&other1);
          intertwine (this, &other2);
          absorb (&other2);

        }
        else
        {
          s2.partage (far, &s2, &s3);

          // s1 goes from begin to close, so -s1 goes from close to begin
          GenerateTrail (-s1, axis, spreading, closeLeavesTrack, true,
                         &s1, &arcs_);

          // s2 goes from close to far
          Braid other1;
          GenerateTrail (s2, axis, spreading, closeLeavesTrack, farLeavesTrack,
                         &s2, &(other1.arcs_));

          // s3 goes from far to end, so -s3 goes from end to far
          Braid other2;
          GenerateTrail (-s3, axis, spreading, true, farLeavesTrack,
                         &s3, &(other2.arcs_));

          // intertwine the three trails
          intertwine (this, &other1);
          absorb (&other1);
          intertwine (this, &other2);
          absorb (&other2);
        }
      }
      else
      {
        // build the braids generated by two sub-arcs,
        // all oriented from the closest point to the farthest point
        Arc s1, s2;
        a.partage (close, &s1, &s2);

        // s1 goes from begin to close, so -s1 goes from close to begin
        GenerateTrail (-s1, axis, spreading, closeLeavesTrack, true,
                       &s1, &arcs_);

        // s2 goes from close to end
        Braid other;
        GenerateTrail (s2, axis, spreading, closeLeavesTrack, true,
                       &s2, &(other.arcs_));

        // intertwine the two trails
        intertwine (this, &other);
        absorb (&other);

      }
    }
    else
    {
      if (a.diedreContient (far))
      {
        // build the braids generated by two sub-arcs,
        // all oriented from the closest point to the farthest point
        Arc s1, s2;
        a.partage (far, &s1, &s2);

        // s1 goes from begin to far
        GenerateTrail (s1, axis, spreading, true, farLeavesTrack,
                       &s1, &arcs_);

        // s2 goes from far to end, so -s2 goes from end to far
        Braid other;
        GenerateTrail (-s2, axis, spreading, true, farLeavesTrack,
                       &s2, &(other.arcs_));

        // intertwine the two trails
        intertwine (this, &other);
        absorb (&other);
      }
      else
      {
        double beginDistance = a.debut ().angleAvecVecteur (axis);
        double endDistance   = a.fin   ().angleAvecVecteur (axis);
        GenerateTrail ((beginDistance < endDistance) ? a : -a,
                       axis, spreading, true, true, &a, &arcs_);
      }
    }

  }

}

Braid&
Braid::operator = (const Braid& b)
{
  if (&b != this) // protection against x = x
    arcs_ = b.arcs_;
  return *this;
}

void
Braid::intertwine (Braid *ptrB1, Braid *ptrB2)
  throw (CantorErreurs)
{ // intertwine two strands by splitting the arcs with respect to each
  // other and inserting multiple nodes in the topology


  // looking for strands intersections
  iter a1, b1, c1;
  iter a2, b2, c2;
  iter i1Next = ptrB1->arcs_.begin ();
  while (i1Next != ptrB1->arcs_.end ())
  {
    iter i1 = i1Next++;
    iter i2Next = ptrB2->arcs_.begin ();
    while (i2Next != ptrB2->arcs_.end ())
    {
      iter i2 = i2Next++;
      if (! i1->isConnected (&(*i2)))
      { // the two arcs are topologically independant

        // do the arcs intersect ?
        int nbInt;
        VecDBL v1, v2;
        i1->intersection (*i2, &nbInt, &v1, &v2);
        if (nbInt)
        { // they intersect each other, we should replace them by
          // their sub-arcs

          // first split
          SplitArc (&(ptrB1->arcs_), i1, v1, &a1, &b1);
          SplitArc (&(ptrB2->arcs_), i2, v1, &a2, &b2);

          if (nbInt < 2)
          { // there is only one intersection point

            // create one multiple node in the topology
            a1->connect (&(*b1), &(*a2), &(*b2));

            c1 = b1;
            c2 = b2;

          }
          else
          { // there are two intersection points

            if (a1->diedreContient (v2))
            { // along the arc 1, we encounter first v2 and later v1
              SplitArc (&(ptrB1->arcs_), a1, v2, &a1, &b1);
              c1 = b1;
              ++c1;

              if (a2->diedreContient (v2))
              { // along the arc 2, we encounter first v2 and later v1
                SplitArc (&(ptrB2->arcs_), a2, v2, &a2, &b2);
                c2 = b2;
                ++c2;

                // create two multiple nodes in the topology
                a1->connect (&(*b1), &(*a2), &(*b2));
                b1->connect (&(*c1), &(*b2), &(*c2));

              }
              else
              { // along the arc 2, we encounter first v1 and later v2
                SplitArc (&(ptrB2->arcs_), b2, v2, &b2, &c2);

                // create two multiple nodes in the topology
                a1->connect (&(*b1), &(*b2), &(*c2));
                b1->connect (&(*c1), &(*a2), &(*b2));

              }

            }
            else
            { // along the arc 1, we encounter first v1 and later v2
              SplitArc (&(ptrB1->arcs_), b1, v2, &b1, &c1);

              if (a2->diedreContient (v2))
              { // along the arc 2, we encounter first v2 and later v1
                SplitArc (&(ptrB2->arcs_), a2, v2, &a2, &b2);
                c2 = b2;
                ++c2;

                // create two multiple nodes in the topology
                a1->connect (&(*b1), &(*b2), &(*c2));
                b1->connect (&(*c1), &(*a2), &(*b2));

              }
              else
              { // along the arc 2, we encounter first v1 and later v2
                SplitArc (&(ptrB2->arcs_), b2, v2, &b2, &c2);

                // create two multiple nodes in the topology
                a1->connect (&(*b1), &(*a2), &(*b2));
                b1->connect (&(*c1), &(*b2), &(*c2));

              }

            }

          }

          // remove the null arcs when it is possible
          a1 = RemoveNullUpstreamArcs   (&(ptrB1->arcs_), a1);
          c1 = RemoveNullDownstreamArcs (&(ptrB1->arcs_), c1);
          a2 = RemoveNullUpstreamArcs   (&(ptrB2->arcs_), a2);
          c2 = RemoveNullDownstreamArcs (&(ptrB2->arcs_), c2);

          i2Next = (c2 != ptrB2->arcs_.end ()) ? ++c2 : c2;

          i1     = a1;
          i1Next = (a1 != ptrB1->arcs_.end ()) ? ++a1 : a1;

        }
      }
    }
  }

}

void
Braid::initAnnotations ()
{ // initialize all arcs to the value AnnotatedArc::notAnnotated

  for (iter i = arcs_.begin (); i != arcs_.end (); ++i)
    i->annotate (AnnotatedArc::notAnnotated);

}

void
Braid::identifyArcs (const Field *ptrF1, const Field *ptrF2)
  throw (CantorErreurs)
{
  for (iter i = arcs_.begin (); i != arcs_.end (); ++i)
    if (i->annotation () == AnnotatedArc::notAnnotated)
    { // look for the arc inclusion according to one test point at the middle
      bool inter, degenerated;
      if (i->origin () != ptrF1)
        inter = ptrF1->isInside (TestPoint (i), &degenerated);
      else
        inter = ptrF2->isInside (TestPoint (i), &degenerated);
  
      if (! degenerated)
      {
        i->annotate (inter
                     ? AnnotatedArc::intersectionAnnotated
                     : AnnotatedArc::unionAnnotated);
        i->propagate ();
      }
    }
}

void
Braid::simplify ()
  throw (CantorErreurs)
{ // simplify the braid by removing null arcs
  iter i = arcs_.begin ();
  while (i != arcs_.end ())
  {
    if ((i->longueur () < small)
        && (i->upstreamNode   () != 0)
        && (i->downstreamNode () != 0))
    {
      if (i->upstreamNode ()->absorbDownstream (&arcs_, i))
      {
        // the connections have changed, we should restart the loop
        i = arcs_.begin ();
      }
      else
      {
        ++i;
      }
    }
    else
    {
      ++i;
    }
  }
}

void
Braid::absorb (Braid *ptrOther)
{ // absorbing one braid into the instance
  SpliceArcs (&arcs_, &(ptrOther->arcs_));
}

bool
Braid::isCompletelyAnnotated () const
{ // chek if all arcs have been annotated

  for (list<AnnotatedArc>::const_iterator i = arcs_.begin ();
       i != arcs_.end ();
       ++i)
    if (i->annotation () == AnnotatedArc::notAnnotated)
      return false;

  return true;

}

bool
Braid::coveringHeuristic (const Arc& a, const VecDBL& axis, double spreading)
  throw (CantorErreurs)
{ // identify arcs that are covered by the spreading of another arc
  for (iter i = arcs_.begin (); i != arcs_.end (); ++i)
    if (i->annotation () == AnnotatedArc::notAnnotated)
    {
      // compute the safety radius to overlap properly the selected arc
      VecDBL p = TestPoint (i);
      double safetyRadius = i->angle ();
      if (safetyRadius > 0.5 * M_PI)
        safetyRadius = M_PI - safetyRadius;

      // eventually reduce the radius to prevent overlapping other arcs
      for (iter j = arcs_.begin (); j != arcs_.end (); ++j)
        if (j != i)
        {
          double dist = j->distance (p);
          if (dist < safetyRadius)
            safetyRadius = dist;
        }

      if (safetyRadius > 2.0 * small)
      {
        // we now have a disk having one half on one side of the arc
        // and the other half on the other side. We select one point
        // in each half-disk : the ones farthest from the arc. We know
        // for sure the closest arc from these points is the test arc
        // and that it is strictly farther than "small"
        RotDBL r (i->axe () ^ p, 0.5 * safetyRadius);
        bool b1 = a.balaye (  r  (p), axis, spreading);
        bool b2 = a.balaye ((-r) (p), axis, spreading);
        if (b1 && b2)
        {
          i->annotate (AnnotatedArc::intersectionAnnotated);
          i->propagate ();
          return true;
        }
        else if (b1 ^ b2)
        {
          i->annotate (AnnotatedArc::unionAnnotated);
          i->propagate ();
          return true;
        }
      }

    }

  // the heuristic failed, nothing have been modified
  return false;

}

bool
Braid::closeParallelsHeuristic ()
  throw (CantorErreurs)
{ // identify close parrallel arcs
  for (iter i = arcs_.begin (); i != arcs_.end (); ++i)
    if (i->annotation () == AnnotatedArc::notAnnotated)
    {
      VecDBL p = TestPoint (i);

      // check the distance to both ends of the arc to prevent
      // confusion between close parallel arcs and natural neighbours
      if ((angle (p, i->debut ()) > 2.0 * small)
          && (angle (p, i->fin ()) > 2.0 * small))
      {

        VecDBL escape;
        for (iter j = arcs_.begin (); j != arcs_.end (); ++j)
          if ((j != i)
              && (j->annotation () == AnnotatedArc::notAnnotated)
              && (j->distance (p) <= 2.0 * small)
              && (i->confines (*j, &escape)))
          {
            // we have found two close parallel arcs
            i->annotate (AnnotatedArc::intersectionAnnotated);
            j->annotate (AnnotatedArc::intersectionAnnotated);
            i->propagate ();
            j->propagate ();
            return true;
          }
      }

    }

  // the heuristic failed, nothing have been modified
  return false;

}

bool
Braid::splittingHeuristic ()
  throw (CantorErreurs)
{ // split arcs where only one part is ambiguous
  VecDBL escape;

  for (iter i = arcs_.begin (); i != arcs_.end (); ++i)
    if (i->annotation () == AnnotatedArc::notAnnotated)
      for (iter j = arcs_.begin (); j != arcs_.end (); ++j)
        if ((j != i)
            && (j->distance (TestPoint (i)) < small)
            && (! j->confines (*i, &escape)))
        {
          // we have found an arc for which the test point is
          // ambiguous but for which one part escapes away from the
          // perturbing arc
          if ((escape.angleAvecVecteur (i->debut ()) > small)
            && (escape.angleAvecVecteur (i->fin ()) > small))
          {
            // the splitting is not degenerated, we perform it
            iter a, b;
            SplitArc (&arcs_, i, escape, &a, &b);
            return true;
          }

        }

  // the heuristic failed, nothing have been modified
  return false;

}

bool
Braid::equivalentPathsHeuristic ()
{ // detect parallel arcs perturbing each other

  for (iter i = arcs_.begin (); i != arcs_.end (); ++i)
    if (i->annotation () == AnnotatedArc::notAnnotated)
    { // we have found an arc not annotated

      Node *nodes [2];
      nodes [0] = i->upstreamNode   ();
      nodes [1] = i->downstreamNode ();

      for (int j = 0; j < 2; ++j)
        if (nodes [j]->nbArcs () > 2)
        { // the arc is connected to a multiple node
          for (int k = 0; k < nodes [j]->nbArcs (); ++k)
          {
            AnnotatedArc *other = nodes [j]->arc (k);
            if ((other != &(*i))
                && (other->annotation () == AnnotatedArc::notAnnotated)
                && (other->parallelConnections (*i, nodes [j]))
                && (i->origin () != other->origin ()))
            { // we have found two arcs converging to the same
              // multiple node, coming from different fields
              // and remaining parallel

              // this is an exact juxtaposition of the boundaries of
              // the two fields. We also know that the boundaries are
              // oriented, so the inside is always at the left of each
              // arc. Therefore, we can deduce that if the arcs go in
              // the same direction, then the two fields are locally
              // superimposed to each other, it they go in opposite
              // directions, then the two fields are side by side. In
              // the first case (superimposed fields) one arc should
              // be annotated as belonging to the union and the other
              // one as belonging to the intersection. In the second
              // case (side by side fields) both arcs should be
              // annotated as belonging to the intersection.

              Node *iU = i->upstreamNode ();
              Node *iD = i->downstreamNode ();
              Node *oU = other->upstreamNode ();
              Node *oD = other->downstreamNode ();
              bool sameDirection;
              if ((iU != iD) && (oU != oD))
                sameDirection = ((nodes [j] == iD) && (nodes [j] == oD))
                             || ((nodes [j] == iU) && (nodes [j] == oU));
              else
              { // checking the nodes is not sufficient to determine the direction
                VecDBL iTangent = i->axe ()     ^ nodes [j]->direction ();
                VecDBL oTangent = other->axe () ^ nodes [j]->direction ();
                sameDirection = (iTangent | oTangent) > 0;
              }

              if (sameDirection)
              { // arcs in same direction : superimposed fields
                i->annotate (AnnotatedArc::unionAnnotated);
                other->annotate (AnnotatedArc::intersectionAnnotated);
              }
              else
              { // arcs in opposite directions : side by side fields
                i->annotate (AnnotatedArc::intersectionAnnotated);
                other->annotate (AnnotatedArc::intersectionAnnotated);
              }
              i->propagate ();
              other->propagate ();

              return true;

            }
          }
        }

    }

  // the heuristic has failed, nothing has been modified
  return false;

}

bool
Braid::peelingHeuristic ()
{ // try to remove ambiguous paths protrubing from the boundary
  // and which are merely flakes

  set<AnnotatedArc *> checked;

  for (iter i = arcs_.begin (); i != arcs_.end (); ++i)
    if ((i->annotation () == AnnotatedArc::notAnnotated)
        && (checked.find (&(*i)) == checked.end ()))
    { // we have found an arc not annotated (and not already checked)

      set<AnnotatedArc *> loop;

      // select all arcs up to the previous multiple node
      AnnotatedArc *firstArc = 0;
      AnnotatedArc *current = &(*i);
      while (firstArc == 0)
      {
        loop.insert (current);
        AnnotatedArc *previous = current->upstreamNode ()->ptrUpstreamArc ();
        if (previous == 0)
          firstArc = current;
        else if (previous == &(*i))
          firstArc = &(*i); // there is no multiple node at all in this loop
        else
          current = previous;
      }

      // select all arcs up to the next multiple node
      AnnotatedArc *lastArc = 0;
      current = &(*i);
      while (lastArc == 0)
      {
        loop.insert (current);
        AnnotatedArc *next = current->downstreamNode ()->ptrDownstreamArc ();
        if ((next == 0) || (next == firstArc))
          lastArc = current;
        else
          current = next;
      }

      if (firstArc->upstreamNode () == lastArc->downstreamNode ())
      { // the arc belongs to a loop, we have selected all arcs in this
        // loop and we know for sure none of them is annotated (if one
        // of them were annotated, its annotation would have been
        // propagated to the other ones)

        // check if the ambiguities come from within the loop or from
        // outside
        bool externalPerturbation = false;

        for (set<AnnotatedArc *>::iterator iter1 = loop.begin ();
             (! externalPerturbation) && (iter1 != loop.end ());
             ++iter1)
        {
          VecDBL p = (*iter1)->intermediaire (0.5 * (*iter1)->balayage ());

          // check the distance to both ends of the arc to prevent
          // confusion between close parallel arcs and natural neighbours
          if ((angle (p, (*iter1)->debut ()) > 2.0 * small)
              && (angle (p, (*iter1)->fin ()) > 2.0 * small))
          {

            externalPerturbation = true;
            for (set<AnnotatedArc *>::iterator iter2 = loop.begin ();
                 externalPerturbation && (iter2 != loop.end ());
                 ++iter2)
              externalPerturbation = (iter1 == iter2)
                                  || ((*iter2)->distance (p) > 2.0 * small);

          }

        }

        if (externalPerturbation)
        { // some ambiguities come from outside, we don't know what to
          // do with the arcs from this loop, we continue to check
          for (set<AnnotatedArc *>::iterator iter1 = loop.begin ();
               (! externalPerturbation) && (iter1 != loop.end ());
               ++iter1)
            checked.insert (*iter1);
        }
        else
        { // all the ambiguities come from within the loop : it is a
          // flake and we can safely remove it

          if (firstArc->upstreamNode ()->nbArcs () > 2)
          { // the loop is connected to other arcs through a multiple node
            // we should detach it from this node
            firstArc->upstreamNode ()->detach (lastArc, firstArc);
          }

          // remove the loop arcs from the instance
          for (set<AnnotatedArc *>::iterator iter1 = loop.begin ();
               iter1 != loop.end ();
               ++iter1)
          {
            iter j = arcs_.begin ();
            while (j != arcs_.end ())
            {
              if (*iter1 == &(*j))
              {
                arcs_.erase (j);
                j = arcs_.end ();
              }
              else
                ++j;
            }
          }

          return true;

        }

      }

    }

  // the heuristic has failed, nothing has been modified
  return false;

}

void
Braid::boundary (vector< vector<Arc> >*ptrB,
                 AnnotatedArc::Annotation annotation) const
{ // extract arcs according to their annotation
  set<const AnnotatedArc *> alreadySelected;
  ptrB->clear ();

  for (list<AnnotatedArc>::const_iterator i = arcs_.begin ();
       i != arcs_.end ();
       ++i)
    if (i->annotation () == annotation
        && alreadySelected.find (&(*i)) == alreadySelected.end ())
    { // we have found the beginning of a new loop
      vector<Arc> loop;

      // building the loop following the annotations
      const AnnotatedArc *current = &(*i);
      while (current)
      {
        loop.push_back (*((const Arc *) current));
        alreadySelected.insert (current);
        current->downstreamNode ()->selectDownstream (annotation, &current,
                                                      &alreadySelected);
      }

      // insert the loop in the boundary
      ptrB->push_back (loop);

    }

}
