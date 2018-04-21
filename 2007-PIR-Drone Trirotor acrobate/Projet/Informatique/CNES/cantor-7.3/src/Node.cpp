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
//>       Node.cpp
//$Resume
//       implementation file for the class
//
//$Description
//       implementation file for the class
//
//$Contenu
//>       class Node              
//>         Node()                
//>         operator =()          
//>         arc()                 
//>         replaceUpstreamArc()  
//>         replaceDownstreamArc()
//>         detach()              
//>         absorbDownstream()    
//>         isConvergent()        
//>         selectDownstream()              
//>         propagate()           
//>         ptrUpstreamArc()      
//>         ptrDownstreamArc()    
//$Historique
//       $Log: Node.cpp,v $
//       Revision 1.6  2003/02/04 09:29:02  cantor
//       DM-ID 17 Mise à jour du nom du fichier dans le bandeau suite à la modification des extensions.
//
//       Revision 1.5  2002/09/06 08:34:09  cantor
//       propagation du marquage lorsque des arcs de longueurs nulles ont ete elimine (FA 15)
//
//       Revision 1.4  2002/09/02 09:19:32  cantor
//       changed the class in order to handle an arbitrary (even) number of arcs
//
//       Revision 1.3  2002/01/17 08:40:36  cantor
//       correction de spécifications throw
//
//       Revision 1.2  2001/06/22 06:17:21  cantor
//       added a set of already selected arcs in the select method
//
//       Revision 1.1  2001/06/05 15:41:52  cantor
//       initial version
//
//$Version
//       $Id: Node.cpp,v 1.6 2003/02/04 09:29:02 cantor Exp $
//$Auteur
//        L. Maisonobe CNES
//        Copyright (C) 2001 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "cantor/Node.h"

const double small = 4.85e-6;

Node::Node (const Node& n)
  : direction_ (n.direction_)
{ // copy-constructor
  for (vector<AnnotatedArc *>::const_iterator iter = n.upstreamArcs_.begin ();
       iter != n.upstreamArcs_.end ();
       ++iter)
    upstreamArcs_.push_back (*iter);
  for (vector<AnnotatedArc *>::const_iterator iter = n.downstreamArcs_.begin ();
       iter != n.downstreamArcs_.end ();
       ++iter)
    downstreamArcs_.push_back (*iter);
}

Node::Node (const VecDBL& u, AnnotatedArc *upstream, AnnotatedArc *downstream)
  throw (CantorErreurs)
  : direction_ (u)
{ // build a simple node between two arcs
  direction_.normalise ();
  upstreamArcs_.push_back (upstream);
  downstreamArcs_.push_back (downstream);
}

Node::Node (const VecDBL& u,
            AnnotatedArc *upstream1, AnnotatedArc *downstream1,
            AnnotatedArc *upstream2, AnnotatedArc *downstream2)
  throw (CantorErreurs)
  : direction_ (u)
{ // build a multiple node between four arcs
  direction_.normalise ();
  upstreamArcs_.push_back (upstream1);
  downstreamArcs_.push_back (downstream1);
  upstreamArcs_.push_back (upstream2);
  downstreamArcs_.push_back (downstream2);
}

Node::Node (const VecDBL& u,
            AnnotatedArc *upstream1,
            const vector<AnnotatedArc *>& downstreamArcs,
            const vector<AnnotatedArc *>& otherUpstreamArcs)
  throw (CantorErreurs)
  : direction_ (u)
{
  // check the arcs numbers balance
  if (downstreamArcs.size () != (otherUpstreamArcs.size () + 1))
    throw CantorErreurs (CantorErreurs::desequilibre_connexions);
  direction_.normalise ();

  // store the upstream arcs pointers
  upstreamArcs_.push_back (upstream1);
  for (vector<AnnotatedArc *>::const_iterator iter = otherUpstreamArcs.begin ();
       iter != otherUpstreamArcs.end ();
       ++iter)
    upstreamArcs_.push_back (*iter);

  // store the downstream arcs pointers
  for (vector<AnnotatedArc *>::const_iterator iter = downstreamArcs.begin ();
       iter != downstreamArcs.end ();
       ++iter)
    downstreamArcs_.push_back (*iter);

}

Node&
Node::operator = (const Node& n)
{
  if (&n != this)    // protection against x = x
  {
    direction_ = n.direction_;
    for (vector<AnnotatedArc *>::const_iterator iter = n.upstreamArcs_.begin ();
         iter != n.upstreamArcs_.end ();
         ++iter)
      upstreamArcs_.push_back (*iter);
    for (vector<AnnotatedArc *>::const_iterator iter = n.downstreamArcs_.begin ();
         iter != n.downstreamArcs_.end ();
         ++iter)
      downstreamArcs_.push_back (*iter);
  }

  return *this;

}

AnnotatedArc *
Node::arc (int i) const
{
  if ((i % 2) == 0)
    return upstreamArcs_ [i / 2];
  else
    return downstreamArcs_ [(i - 1) / 2];
}

void
Node::replaceUpstreamArc (AnnotatedArc *ptrOld, AnnotatedArc *ptrNew)
{ // replace one arc arriving at the node by a new one
  for (vector<AnnotatedArc *>::iterator iter = upstreamArcs_.begin ();
       iter != upstreamArcs_.end ();
       ++iter)
  {
    if (*iter == ptrOld)
      *iter = ptrNew;
  }
}

void
Node::replaceDownstreamArc (AnnotatedArc *ptrOld, AnnotatedArc *ptrNew)
{ // replace one arc going out of the node by a new one
  for (vector<AnnotatedArc *>::iterator iter = downstreamArcs_.begin ();
       iter != downstreamArcs_.end ();
       ++iter)
  {
    if (*iter == ptrOld)
      *iter = ptrNew;
  }
}

void
Node::detach (AnnotatedArc *upstream, AnnotatedArc *downstream)
{ // detach two arcs from a node
  vector<AnnotatedArc *>::iterator foundUpstream   = upstreamArcs_.end ();
  vector<AnnotatedArc *>::iterator foundDownstream = downstreamArcs_.end ();

  for (vector<AnnotatedArc *>::iterator iter = upstreamArcs_.begin ();
       iter != upstreamArcs_.end ();
       ++iter)
  {
    if (*iter == upstream)
      foundUpstream = iter;
  }

  for (vector<AnnotatedArc *>::iterator iter = downstreamArcs_.begin ();
       iter != downstreamArcs_.end ();
       ++iter)
  {
    if (*iter == downstream)
      foundDownstream = iter;
  }

  // remove the arcs only if they have both been found
  if ((foundUpstream != upstreamArcs_.end ())
      & (foundDownstream != downstreamArcs_.end ()))
  {
    upstreamArcs_.erase   (foundUpstream);
    downstreamArcs_.erase (foundDownstream);
  }

}

bool
Node::absorbDownstream (list<AnnotatedArc> *ptrArcs,
                        list<AnnotatedArc>::iterator iterNull)
  throw (CantorErreurs)
{ // absorb the node connected to the instance through a null arc
  Node *downstreamNode = iterNull->downstreamNode ();

  if (downstreamNode == this)
  { // this is a null loop connected only to the instance, we simply remove it

    vector<AnnotatedArc *>::iterator foundUpstream = upstreamArcs_.end ();
    for (vector<AnnotatedArc *>::iterator iter = upstreamArcs_.begin ();
         iter != upstreamArcs_.end ();
         ++iter)
    {
      if (*iter == &(*iterNull))
        foundUpstream = iter;
    }

    vector<AnnotatedArc *>::iterator foundDownstream = downstreamArcs_.end ();
    for (vector<AnnotatedArc *>::iterator iter = downstreamArcs_.begin ();
         iter != downstreamArcs_.end ();
         ++iter)
    {
      if (*iter == &(*iterNull))
        foundDownstream = iter;
    }

    if ((foundUpstream != upstreamArcs_.end ())
        && (foundDownstream != downstreamArcs_.end ()))
    {
      upstreamArcs_.erase (foundUpstream);
      downstreamArcs_.erase (foundDownstream);
      ptrArcs->erase (iterNull);

      propagate ();

      // the connections have changed
      return true;

    }
    else
    { // logically, this should never happen

      // we were not able to process this arc
      return false;
    }

  }
  else
  { // this is an arc connecting two different nodes
    vector<AnnotatedArc *> otherUpstreamArcs;
    vector<AnnotatedArc *> downstreamArcs;

    vector<AnnotatedArc *>::iterator iter = upstreamArcs_.begin ();

    // select the first upstream arc and gather all the other ones in a vector
    AnnotatedArc *firstUpstream = *iter;
    while (++iter != upstreamArcs_.end ())
      otherUpstreamArcs.push_back (*iter);
    for (iter = downstreamNode->upstreamArcs_.begin ();
         iter != downstreamNode->upstreamArcs_.end ();
         ++iter)
      if (*iter != &(*iterNull))
        otherUpstreamArcs.push_back (*iter);

    // gather all downstream arcs in a vector
    for (iter = downstreamArcs_.begin ();
         iter != downstreamArcs_.end ();
         ++iter)
      if (*iter != &(*iterNull))
        downstreamArcs.push_back (*iter);
    for (iter = downstreamNode->downstreamArcs_.begin ();
         iter != downstreamNode->downstreamArcs_.end ();
         ++iter)
      downstreamArcs.push_back (*iter);

    // connect everything
    firstUpstream->connect (&downstreamArcs, &otherUpstreamArcs);

    firstUpstream->downstreamNode()->propagate ();

    ptrArcs->erase (iterNull);

    // the connections have changed, we have to start again
    return true;

  }

}

bool
Node::isConvergent (AnnotatedArc *ptrTest,
                    set<const AnnotatedArc *> *ptrAlreadyTested) const
{ // check if the given arc converges to the node
  // (either directly or through intervening null arcs)
  for (int i = 0; i < nbArcs (); ++i)
  {
    if (arc (i) == ptrTest)
      return true;
  }

  for (int i = 0; i < nbArcs (); ++i)
  {
    AnnotatedArc *a = arc (i);
    if ((ptrAlreadyTested->find (a) == ptrAlreadyTested->end ())
        && (a->longueur () < small))
    { // since the arc has null length,
      // both its nodes are considered equivalent,
      // we continue searching through the opposite node
      ptrAlreadyTested->insert (a);
      Node *opposite = a->oppositeNode (this);
      if (opposite != 0 && opposite->isConvergent (ptrTest, ptrAlreadyTested))
        return true;

    }
  }

  return false;

}

void
Node::selectDownstream (AnnotatedArc::Annotation annotation,
                        const AnnotatedArc **ptrA,
                        set<const AnnotatedArc *> *ptrAlreadySelected) const
{ // select an arc according to its annotation
  *ptrA = 0;

  for (vector<AnnotatedArc *>::const_iterator i = downstreamArcs_.begin ();
       i != downstreamArcs_.end ();
       ++i)
  {
    AnnotatedArc *a = *i;
    if ((ptrAlreadySelected->find (a) == ptrAlreadySelected->end ())
        && (a->annotation () == annotation))
    { // we have found a downstream arc with the specified annotation
      *ptrA = a;
      ptrAlreadySelected->insert (a);
      return;
    }
  }

}

bool
Node::propagate ()
{ // propagate the annotations of the connected arcs
  if (upstreamArcs_.empty () && downstreamArcs_.empty ())
    return false;

  // count the annotations of the upstream arcs
  int nbIntersectionUp = 0;
  int nbUnionUp        = 0;
  int nbNotAnnotatedUp = 0;
  for (vector<AnnotatedArc *>::iterator i = upstreamArcs_.begin ();
       i != upstreamArcs_.end ();
       ++i)
  {
    switch ((*i)->annotation ())
    {

      case AnnotatedArc::intersectionAnnotated :
        ++nbIntersectionUp;
        break;

      case AnnotatedArc::unionAnnotated :
        ++nbUnionUp;
        break;

      default :
        ++nbNotAnnotatedUp;
        break;

    }
  }

  // count the annotations of the downstream arcs
  int nbIntersectionDown = 0;
  int nbUnionDown        = 0;
  int nbNotAnnotatedDown = 0;
  for (vector<AnnotatedArc *>::iterator i = downstreamArcs_.begin ();
       i != downstreamArcs_.end ();
       ++i)
  {
    switch ((*i)->annotation ())
    {

      case AnnotatedArc::intersectionAnnotated :
        ++nbIntersectionDown;
        break;

      case AnnotatedArc::unionAnnotated :
        ++nbUnionDown;
        break;

      default :
        ++nbNotAnnotatedDown;
        break;

    }
  }

  bool somethingChanged = false;

  if (nbNotAnnotatedUp > 0)
  {

    if (nbUnionDown - nbUnionUp == nbNotAnnotatedUp)
    { // the pending upstream arcs should be marked as belonging to union

      for (vector<AnnotatedArc *>::iterator i = upstreamArcs_.begin ();
           i != upstreamArcs_.end ();
           ++i)
      {
        if ((*i)->annotation () == AnnotatedArc::notAnnotated)
        {
          (*i)->annotate (AnnotatedArc::unionAnnotated);
          (*i)->propagateThroughOppositeNode (this);
        }
        somethingChanged = true;
      }
    }
    else if (nbIntersectionDown - nbIntersectionUp == nbNotAnnotatedUp)
    { // the pending upstream arcs should be marked as belonging to intersection

      for (vector<AnnotatedArc *>::iterator i = upstreamArcs_.begin ();
           i != upstreamArcs_.end ();
           ++i)
      {
        if ((*i)->annotation () == AnnotatedArc::notAnnotated)
        {
          (*i)->annotate (AnnotatedArc::intersectionAnnotated);
          (*i)->propagateThroughOppositeNode (this);
        }
        somethingChanged = true;
      }
    }
  }

  if (nbNotAnnotatedDown > 0)
  {

    if (nbUnionUp - nbUnionDown == nbNotAnnotatedDown)
    { // the pending downstream arcs should be marked as belonging to union

      for (vector<AnnotatedArc *>::iterator i = downstreamArcs_.begin ();
           i != downstreamArcs_.end ();
           ++i)
      {
        if ((*i)->annotation () == AnnotatedArc::notAnnotated)
        {
          (*i)->annotate (AnnotatedArc::unionAnnotated);
          (*i)->propagateThroughOppositeNode (this);
        }
        somethingChanged = true;
      }
    }
    else if (nbIntersectionUp - nbIntersectionDown == nbNotAnnotatedDown)
    { // the pending downstream arcs should be marked as belonging to intersection

      for (vector<AnnotatedArc *>::iterator i = downstreamArcs_.begin ();
           i != downstreamArcs_.end ();
           ++i)
      {
        if ((*i)->annotation () == AnnotatedArc::notAnnotated)
        {
          (*i)->annotate (AnnotatedArc::intersectionAnnotated);
          (*i)->propagateThroughOppositeNode (this);
        }
        somethingChanged = true;
      }
    }
  }

  return somethingChanged;

}

AnnotatedArc*
Node::ptrUpstreamArc () const
{ // get a pointer to the upstream arc if it is uniq, or return null
  return (upstreamArcs_.size () == 1) ? upstreamArcs_ [0] : 0;
}

AnnotatedArc*
Node::ptrDownstreamArc () const
{ // get a pointer to the downstream arc if it is uniq, or return null
  return (downstreamArcs_.size () == 1) ? downstreamArcs_ [0] : 0;
}
