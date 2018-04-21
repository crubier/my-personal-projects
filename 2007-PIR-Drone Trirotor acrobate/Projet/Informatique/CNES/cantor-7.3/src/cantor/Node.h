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
//>       Node.h
//$Resume
//       header file for the class
//
//$Description
//       Declaration module for the class
//
//$Contenu
//>       class Node
//$Historique
//       $Log: Node.h,v $
//       Revision 1.5  2002/12/10 15:06:44  cantor
//       DM-ID 12 Ajout d'un destructeur pour prévenir celui crée par le compilateur
//
//       Revision 1.4  2002/09/02 09:22:03  cantor
//       changed the class in order to handle an arbitrary (even) number of arcs
//
//       Revision 1.3  2002/01/17 08:44:54  cantor
//       correction de spécifications throw - correction d'une faute de frappe (absorbDonwstream -> absorbDownstream)
//
//       Revision 1.2  2001/06/22 06:17:02  cantor
//       added a set of already selected arcs in the select method
//
//       Revision 1.1  2001/06/05 15:21:53  cantor
//       initial version
//
//$Version
//       $Id: Node.h,v 1.5 2002/12/10 15:06:44 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2001 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_Node_h
#define __cantor_Node_h

#include <set>
#include <list>
#include <vector>

#include "cantor/DeclDBL.h"
#include "cantor/CantorErreurs.h"
#include "cantor/AnnotatedArc.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class Node
//$Resume
//       model of the nodes between arcs of the unit sphere
//
//$Description
//       The nodes are points of the unit sphere that connect several
//       arcs in the braids used to compute fields boundaries. All
//       nodes connect an even number of arcs. Simple nodes connecting
//       only two arcs come from the simple boundaries of
//       fields. Multiple nodes arise while computing the intersection
//       of arcs from different fields. The nodes are used to preserve
//       the topology of the braid and for arcs annotations
//       propagation. Since boundaries are always composed of closed
//       loops and since they can be build by selecting arcs according
//       to their annotation, there should never be an odd number of
//       annotations of one type on any node (once all related arcs
//       have been annotated). Therefore, when n-1 arcs are already
//       annotated, the annotation for the remaining arc can be
//       deduced and propagated.
//
//$Usage
//>     construction : 
//        without argument
//        from a point on the spere and an even number of arcs
//        by copy
//>     utilisation  : 
//>       Node& operator =                 () 
//          affectation
//>       const VecDBL& direction          () 
//          get the direction of the node on the unit sphere
//>       int nbArcs                       () 
//          get the number of arcs connected to the instance
//>       AnnotatedArc *arc                () 
//          get one of the arcs connected to the instance
//>       AnnotatedArc *ptrUpstreamArc     () 
//          get a pointer to the upstream arc if it is uniq, or return null
//>       AnnotatedArc* ptrDownstreamArc   () 
//          get a pointer to the downstream arc if it is uniq, or return null
//>       void replaceUpstreamArc          () 
//          replace the given upstream arc by another one
//>       void replaceDownstreamArc        () 
//          replace the given downstream arc by another one
//>       void detach                      () 
//          detach two arcs from the node
//>       bool absorbDownStreamNode        () 
//          absorb the following downstream node (which should be close)
//>       bool propagate                   () 
//          propagate the annotations through the node
//>       bool isConvergent                () 
//          check if the given arc converges to the node
//          (either directly or through intervening null arcs)
//>       void selectDownstream           () 
//          select one arc with the given annotation
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2001 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class Node
{
public :

  // constructors
  Node ()
    : direction_ (1.0, 0.0, 0.0)
  {}

  Node (const Node&  n);
  Node (const VecDBL& u,
        AnnotatedArc *upstream, AnnotatedArc *downstream)
    throw (CantorErreurs);
  Node (const VecDBL& u,
        AnnotatedArc *upstream1, AnnotatedArc *downstream1,
        AnnotatedArc *upstream2, AnnotatedArc *downstream2)
    throw (CantorErreurs);
  Node (const VecDBL& u,
        AnnotatedArc *upstream1,
        const vector<AnnotatedArc *>& downstreamArcs,
        const vector<AnnotatedArc *>& otherUpstreamArcs)
    throw (CantorErreurs);

  Node& operator = (const Node& n);

  // destructor
  ~Node () {}

  // get the direction of the node on the unit sphere
  const VecDBL& direction () const { return direction_; }

  // arcs accessor
  int           nbArcs           () const
                { return upstreamArcs_.size () + downstreamArcs_.size (); }
  AnnotatedArc *arc              (int i) const;
  AnnotatedArc* ptrUpstreamArc   () const;
  AnnotatedArc* ptrDownstreamArc () const;

  // modifications of the topology
  void replaceUpstreamArc   (AnnotatedArc *ptrOld,   AnnotatedArc *ptrNew);
  void replaceDownstreamArc (AnnotatedArc *ptrOld,   AnnotatedArc *ptrNew);
  void detach               (AnnotatedArc *upstream, AnnotatedArc *downstream);
  bool absorbDownstream     (list<AnnotatedArc> *ptrArcs,
                             list<AnnotatedArc>::iterator iterNull)
    throw (CantorErreurs);

  // walk through the topology
  bool propagate        ();
  bool isConvergent     (AnnotatedArc    *ptrTest,
                         set<const AnnotatedArc *> *ptrAlreadyTested) const;
  void selectDownstream (AnnotatedArc::Annotation annotation,
                         const AnnotatedArc **ptrA,
                         set<const AnnotatedArc *> *ptrAlreadySelected) const;

private :

  VecDBL                 direction_;
  vector<AnnotatedArc *> upstreamArcs_;
  vector<AnnotatedArc *> downstreamArcs_;

};

#endif
