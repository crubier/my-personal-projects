////////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Type
//       DEF
//
//$Projet
//        Marmottes
//
//$Application
//        Marmottes
//
//$Nom
//>       AnnotatedArc.cpp
//$Resume
//       implementation file for the class
//
//$Description
//       implementation file for the class
//
//$Contenu
//>       DeleteNode()                    
//>       class AnnotatedArc              
//>         operator =()                  
//>         confines()                    
//>         parallelConnections()         
//>         isConnected()                 
//>         propagate()                   
//>         oppositeNode()                
//>         propagateThroughOppositeNode()
//>         ptrUpstreamArc()              
//>         ptrDownstreamArc()            
//>         removeIfPossible()            
//$Historique
//       $Log: AnnotatedArc.cpp,v $
//       Revision 1.4  2003/02/04 09:23:51  cantor
//       DM-ID 17 Mise à jour du nom du fichier dans le bandeau suite à la modification des extensions.
//
//       Revision 1.3  2002/09/02 09:17:39  cantor
//       added a connect method between two arcs only
//
//       Revision 1.2  2002/08/30 08:56:59  cantor
//       Correction de la FA 17
//
//       Revision 1.1  2001/06/05 15:40:42  cantor
//       initial version
//
//$Version
//       $Id: AnnotatedArc.cpp,v 1.4 2003/02/04 09:23:51 cantor Exp $
//$Auteur
//        L. Maisonobe CNES
//        Copyright (C) 2001 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <set>

#include "cantor/AnnotatedArc.h"
#include "cantor/Node.h"

const double small = 4.85e-6;

static void
DeleteNode (void *memory, void *)
{ // memory freeing function (to be registered with TamponPartage)
  delete (Node *) memory;
}

AnnotatedArc&
AnnotatedArc::operator = (const AnnotatedArc& a)
{

  if (&a != this)      // protection against x = x
  {
    Arc::operator= (a);
    upstreamNode_   = a.upstreamNode_;
    downstreamNode_ = a.downstreamNode_;
    annotation_     = a.annotation_;
    origin_         = a.origin_;
  }

  return *this;

}

bool
AnnotatedArc::confines (const AnnotatedArc& a, VecDBL *ptrEscape) const
{ // check if an arc if confined in a corridor along the instance (it
  // can escape only at the extremal openings) This method should be
  // used ONLY when one already knows the arc comes close to at least
  // one point of the instance. If the arc is not confined around the
  // instance, the escape point is updated
  int nbInt;
  VecDBL v2;

  // the check is done by surrounding the instance by two parallel
  // arcs that form a corridor and testing whether the test arc
  // crosses these limites. If it does then it escapes from the
  // corridor, otherwise it is confined.

  if (angle () - 2.0 * small > 0.0)
  { // there is an internal boudary (between the instance and its axis)
    Arc b (axe (), angle () - 2.0 * small, debut (), fin ());
    b.intersection (a, &nbInt, ptrEscape, &v2);
    if (nbInt > 0)
      return false;
  }

  if (angle () + 2.0 * small < M_PI)
  { // there is an external boundary (between the instance and the
    // opposite of its axis)
    Arc b (axe (), angle () + 2.0 * small, debut (), fin ());
    b.intersection (a, &nbInt, ptrEscape, &v2);
    if (nbInt > 0)
      return false;
  }

  // the arc stay confined around the instance
  return true;

}

bool
AnnotatedArc::parallelConnections (const AnnotatedArc& a, Node *n) const
{ // check if two arcs are connected to a node and follow parallel paths
  VecDBL escape;
  if (! confines (a, &escape))
    return false;

  // we set the direction of the tangents towards the interior of the
  // arc, not according to the rotation direction
  VecDBL tangent1 = axe () ^ n->direction ();
  if (n == (Node *) downstreamNode_.memoire ())
    tangent1 = -tangent1;

  VecDBL tangent2 = a.axe () ^ n->direction ();
  if (n == (Node *) a.downstreamNode_.memoire ())
    tangent2 = -tangent2;

  return (tangent1 | tangent2) > 0.0;

}

void
AnnotatedArc::replace (AnnotatedArc *ptrNew)
  throw (CantorErreurs)
{ // replace the instance by one equivalent arc

  // preserve the topology
  Node *upstream = (Node *) upstreamNode_.memoire ();
  if (upstream)
    upstream->replaceDownstreamArc (this, ptrNew);
  ptrNew->upstreamNode_ = upstreamNode_;

  Node *downstream = (Node *) downstreamNode_.memoire ();
  if (downstream)
    downstream->replaceUpstreamArc (this, ptrNew);
  ptrNew->downstreamNode_ = downstreamNode_;

}

void
AnnotatedArc::replace (AnnotatedArc *ptrUp, AnnotatedArc *ptrDown)
  throw (CantorErreurs)
{ // replace the instance by two equivalent arcs

  // set an intermediate node
  ptrUp->connect (ptrDown);

  // preserve the topology
  Node *upstream = (Node *) upstreamNode_.memoire ();
  if (upstream)
    upstream->replaceDownstreamArc (this, ptrUp);
  ptrUp->upstreamNode_ = upstreamNode_;

  Node *downstream = (Node *) downstreamNode_.memoire ();
  if (downstream)
    downstream->replaceUpstreamArc (this, ptrDown);
  ptrDown->downstreamNode_ = downstreamNode_;

}

void
AnnotatedArc::connect (AnnotatedArc *ptrDown)
  throw (CantorErreurs)
{ // create a simple node between the instance and the specified arc
  // the instance is upstream and the specified arc downstream
  if (fin ().angleAvecVecteur (ptrDown->debut ()) > small)
    throw CantorErreurs (CantorErreurs::frontiere_ouverte);

  // create the shared node
  downstreamNode_ = TamponPartage (new Node (fin (), this, ptrDown),
                                   DeleteNode, 0);
  ptrDown->upstreamNode_ = downstreamNode_;

}

void
AnnotatedArc::connect (AnnotatedArc *ptrDown1,
                       AnnotatedArc *ptrUp2, AnnotatedArc *ptrDown2)
  throw (CantorErreurs)
{ // create a multiple node between the instance and the specified
  // arcs the instance and the second arc are upstream while the
  // first and third arcs are downstream
  if (fin ().angleAvecVecteur (ptrDown1->debut ()) > small
      ||
      fin ().angleAvecVecteur (ptrUp2->fin ()) > small
      ||
      fin ().angleAvecVecteur (ptrDown2->debut ()) > small)
    throw CantorErreurs (CantorErreurs::frontiere_ouverte);

  // create the shared node
  downstreamNode_ = TamponPartage (new Node (fin (),
                                             this, ptrDown1, ptrUp2, ptrDown2),
                                   DeleteNode, 0);
  ptrDown1->upstreamNode_ = downstreamNode_;
  ptrUp2->downstreamNode_ = downstreamNode_;
  ptrDown2->upstreamNode_ = downstreamNode_;

}

void
AnnotatedArc::connect (vector<AnnotatedArc *> *ptrDownstreamArcs,
                       vector<AnnotatedArc *> *ptrOtherUpstreamArcs)
  throw (CantorErreurs)
{ // create a multiple node between the instance and the specified arcs

  // check the position of the node
  for (vector<AnnotatedArc *>::iterator iter = ptrDownstreamArcs->begin ();
       iter != ptrDownstreamArcs->end ();
       ++iter)
  {
    if (fin ().angleAvecVecteur ((*iter)->debut ()) > small)
      throw CantorErreurs (CantorErreurs::frontiere_ouverte);
  }

  for (vector<AnnotatedArc *>::iterator iter = ptrOtherUpstreamArcs->begin ();
       iter != ptrOtherUpstreamArcs->end ();
       ++iter)
  {
    if (fin ().angleAvecVecteur ((*iter)->fin ()) > small)
      throw CantorErreurs (CantorErreurs::frontiere_ouverte);
  }

  // create the shared node
  downstreamNode_ = TamponPartage (new Node (fin (),
                                             this, *ptrDownstreamArcs,
                                             *ptrOtherUpstreamArcs),
                                   DeleteNode, 0);

  for (vector<AnnotatedArc *>::iterator iter = ptrDownstreamArcs->begin ();
       iter != ptrDownstreamArcs->end ();
       ++iter)
    (*iter)->upstreamNode_ = downstreamNode_;

  for (vector<AnnotatedArc *>::iterator iter = ptrOtherUpstreamArcs->begin ();
       iter != ptrOtherUpstreamArcs->end ();
       ++iter)
    (*iter)->downstreamNode_ = downstreamNode_;

}

bool
AnnotatedArc::isConnected (AnnotatedArc *ptrA) const
{ // check if the instance is connected with another arc
  Node *downstream = (Node *) downstreamNode_.memoire ();
  Node *upstream   = (Node *) upstreamNode_.memoire ();

  set<const AnnotatedArc *> alreadyTested;
  alreadyTested.insert (this);

  return (((downstream != 0)
           && downstream->isConvergent (ptrA, &alreadyTested))
          ||  ((upstream != 0)
               && upstream->isConvergent (ptrA, &alreadyTested)));

}

void
AnnotatedArc::propagate ()
{ // propagate the annotation of the instance to the neighboring
  // arcs (recursively as far as possible) through the nodes

  // propagate downstream
  Node *downstream = (Node *) downstreamNode_.memoire ();
  if (downstream)
    downstream->propagate ();

  // propagate upstream
  Node *upstream = (Node *) upstreamNode_.memoire ();
  if (upstream)
    upstream->propagate ();

}

Node *
AnnotatedArc::oppositeNode (const Node *n) const
{
  Node *downstream = (Node *) downstreamNode_.memoire ();
  Node *upstream   = (Node *) upstreamNode_.memoire ();
  if (n == upstream)
    return downstream;
  if (n == downstream)
    return upstream;
  return 0;
}

void
AnnotatedArc::propagateThroughOppositeNode (const Node *n)
{ // propagate the annotation of the instance to the neighboring
  // arcs (recursively as far as possible) but only in the
  // direction specified by the given node
  Node *opposite = oppositeNode (n);
  if (opposite != 0)
    opposite->propagate ();
}

AnnotatedArc*
AnnotatedArc::ptrUpstreamArc () const
{ // get a pointer to the upstream arc if it is uniq, or returns null
  Node *n = (Node *) upstreamNode_.memoire ();
  return (n == 0) ? 0 : n->ptrUpstreamArc ();
}

AnnotatedArc*
AnnotatedArc::ptrDownstreamArc () const
{ // get a pointer to the downstream arc if it is uniq, or returns null
  Node *n = (Node *) downstreamNode_.memoire ();
  return (n == 0) ? 0 : n->ptrDownstreamArc ();
}

bool
AnnotatedArc::removeIfPossible ()
{ // remove the instance from the topology if it is possible
  // (i.e. if the arc if very short and the nodes can be reconnected)
  // return true if the arc has been removed
  if (longueur () >= small)
    return false;

  Node *upstream   = (Node *) upstreamNode_.memoire ();
  Node *downstream = (Node *) downstreamNode_.memoire ();

  if (upstream == 0)
  { // the upstream side is not connected at all

    if (downstream == 0)
    { // neither side is connected, nothing prevents from removing
      // the instance and the nodes
      return true;
    }
    else
    {
      AnnotatedArc *downstreamArc = downstream->ptrDownstreamArc ();
      if (downstreamArc == 0)
      { // the instance goes to a multiple node we cannot remove,
        // we refuse detaching ourself
        return false;
      }
      else
      { // the instance goes to a simple node,
        // we detach ourself by unconnecting the downstream arc
        // (recycling the upstream node which does not point anywhere,
        // there is no need to create another one)
        downstreamArc->upstreamNode_ = upstreamNode_;
        return true;
      }
    }

  }

  AnnotatedArc *upstreamArc = upstream->ptrUpstreamArc ();
  if (upstreamArc == 0)
  { // the instance comes from a multiple node

    if (downstream == 0)
    { // we cannot remove the multiple node,
      // we refuse detaching ourself
      return false;
    }
    else
    {
      AnnotatedArc *downstreamArc = downstream->ptrDownstreamArc ();
      if (downstreamArc == 0)
      { // the instance is between two multiple node,
        // we refuse detaching ourself
        return false;
      }
      else
      { // neither the instance nor the downstream simple node are useful,
        // we detach ourself by connecting the downstream arc
        // to the upstream multiple node
        upstream->replaceDownstreamArc (this, downstreamArc);
        downstreamArc->upstreamNode_ = upstreamNode_;
        return true;
      }
    }
  }

  // the instance comes from a simple node
  if (downstream == 0)
  { // the upstream side is not connected at all
    // we detach ourself by unconnecting the upstream arc
    // (recycling the downstream node which does not point anywhere,
    // there is no need to create another one)
    upstreamArc->downstreamNode_ = downstreamNode_;
  }
  else
  { // neither the instance nor the upstream simple node are useful,
    // we detach ourself by connecting the upstream arc to the downstream
    // node (which can be either a simple node or a multiple node)
    downstream->replaceUpstreamArc (this, upstreamArc);
    upstreamArc->downstreamNode_ = downstreamNode_;
  }

  return true;

}
