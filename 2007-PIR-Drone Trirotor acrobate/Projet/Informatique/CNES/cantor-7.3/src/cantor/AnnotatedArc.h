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
//>       AnnotatedArc.h
//$Resume
//       header file for the AnnotatedArc class
//
//$Description
//       Declaration module for the class
//
//$Contenu
//>       class AnnotatedArc
//>       enum Annotation   
//$Historique
//       $Log: AnnotatedArc.h,v $
//       Revision 1.5  2002/12/10 14:50:10  cantor
//       DM-ID 12 Ajout d'un destructeur pour prévenir celui créer par le compilateur
//
//       Revision 1.4  2002/09/09 14:03:58  cantor
//       Suppression de l'appel à la classe Field du au changement de type Field<-void dans quelques méthodes.
//
//       Revision 1.3  2002/09/02 09:20:09  cantor
//       added a connect method between two arcs only
//
//       Revision 1.2  2002/08/30 08:58:08  cantor
//       Correction de la FA 17
//
//       Revision 1.1  2001/06/05 15:22:46  cantor
//       initial version
//
//$Version
//       $Id: AnnotatedArc.h,v 1.5 2002/12/10 14:50:10 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2001 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_AnnotatedArc_h
#define __cantor_AnnotatedArc_h

#include "cantor/Arc.h"
#include "cantor/CantorErreurs.h"
#include <vector>

class Node;

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class AnnotatedArc
//$Resume
//       model of an arc on the unit sphere that can be annotated
//
//$Description
//       Instances of this class represent arcs that can be annotated
//       and that are connected to each others through nodes in order
//       to form braids. The global structure is the complete set of
//       arcs resulting from the combination of two fields
//       boundaries. Some ars can be unabmbiguously annotated as
//       belonging either to the boundary of the union or the
//       intersection of the fields, and the topological structure is
//       used to propagate these annotation as far as possible from
//       arc to arc. The Braid class is responsible for the overall
//       handling of these arcs, it does the annotation and extract
//       the selected arcs once everything has been properly
//       identified. The AnnotatedArc class handles the local
//       properties, it holds the annotation and in conjunction with
//       the Node class handles the step by step propagation of
//       annotations.
//
//$Usage
//>     construction : 
//          without argument
//          from an arc (and eventually two nodes and an annotation)
//          by copy
//>     utilisation : 
//>       AnnotatedArc& operator =               () 
//          affectation
//>       const void *origin                     ()
//          return the origin field of the instance
//>       bool confines                          () 
//          check if an arc if confined in a corridor along the instance
//>       bool parallelConnections               () 
//          check if two arcs are connected to a node and follow parallel paths
//>       void replace                           () 2 signatures - 
//          replace the instance by one or two equivalent arcs
//>       bool removeIfPossible                  ()
//          remove the instance from the topology if it is possible
//>       void connect                           () 2 signatures - 
//          connect an arc with one or three other arcs
//>       bool isConnected                       () 
//          check if the instance is connected with another arc
//>       Node *upstreamNode                     ()
//          get the upstream node
//>       const Node *upstreamNode               ()
//          get the upstream node
//>       Node *downstreamNode                   ()
//          get the downstream node
//>       const Node *downstreamNode             ()
//          get the downstream node
//>       Node *oppositeNode                     ()
//          get the node opposite to the given one
//>       static AnnotatedArc oppositeAnnotation () 
//          return the opposite of the given annotation
//>       AnnotatedArc annotation                () 
//          get the annotation of the instance
//>       void annotate                          () 
//          set the annotation
//>       void propagate                         () 
//          propagate the annotation of the instance to the neighboring
//          arcs (recursively as far as possible) through the nodes
//>       void propagateThroughOppositeNode      () 
//          propagate the annotation of the instance to the neighboring
//          arcs (recursively as far as possible) but only in the
//          direction specified by the given node
//>       AnnotatedArc* ptrUpstreamArc           () 
//          get a pointer to the upstream arc if it is uniq, or returns null
//>       AnnotatedArc* ptrDownstreamArc         () 
//          get a pointer to the downstream arc if it is uniq, or returns null
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2001 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////


class AnnotatedArc : public Arc
{

public :

  enum Annotation
  {
    notAnnotated,
    unionAnnotated,
    intersectionAnnotated
  };

  // constructors
  AnnotatedArc ()
    : annotation_ (notAnnotated), origin_ (0)
  {}

  AnnotatedArc (const Arc& a, const void *origin)
    : Arc (a), annotation_ (notAnnotated), origin_ (origin)
  {}

  AnnotatedArc (const AnnotatedArc& a)
    : Arc (a),
      upstreamNode_ (a.upstreamNode_),
      downstreamNode_ (a.downstreamNode_),
      annotation_ (a.annotation_), origin_ (a.origin_)
  {}

  AnnotatedArc& operator = (const AnnotatedArc& a);

  // destructor
  ~AnnotatedArc () {}

  // get the origin field
  const void *origin () const { return origin_; }

  // check if an arc if confined in a corridor along the instance (it
  // can escape only at the extremal openings) This method should be
  // used ONLY when one already knows the arc comes close to at least
  // one point of the instance. If the arc is not confined around the
  // instance, the escape point is updated
  bool confines (const AnnotatedArc& a, VecDBL *ptrEscape) const;

  // check if two arcs are connected to a node and follow parallel paths
  bool parallelConnections (const AnnotatedArc& a, Node *n) const;

  // replace the instance by one or two equivalent arcs
  void replace (AnnotatedArc *ptrNew)
    throw (CantorErreurs);
  void replace (AnnotatedArc *ptrUp, AnnotatedArc *ptrDown)
    throw (CantorErreurs);

  // remove the instance from the topology if it is possible
  // (i.e. if the arc if very short and the nodes can be reconnected)
  // return true if the arc has been removed
  bool removeIfPossible ();

  // create a node between several arcs
  void connect (AnnotatedArc *ptrDown) throw (CantorErreurs);
  void connect (AnnotatedArc *ptrDown1,
                AnnotatedArc *ptrUp2, AnnotatedArc *ptrDown2
               ) throw (CantorErreurs);
  void connect (vector<AnnotatedArc *> *ptrDownstreamArcs,
                vector<AnnotatedArc *> *ptrOtherUpstreamArcs)
    throw (CantorErreurs);

  // check if the instance is connected with another arc
  bool isConnected (AnnotatedArc *ptrA) const;

  // nodes handling
  Node *upstreamNode ()
  { return (Node *) upstreamNode_.memoire (); }

  const Node *upstreamNode () const
  { return (const Node *) upstreamNode_.memoire (); }

  Node *downstreamNode  ()
  { return (Node *) downstreamNode_.memoire  (); }

  const Node *downstreamNode  () const
  { return (const Node *) downstreamNode_.memoire  (); }

  Node *oppositeNode (const Node *n) const;

  // annotation handling
  static Annotation oppositeAnnotation (Annotation a)
  {
    return (a == intersectionAnnotated)
      ? unionAnnotated : intersectionAnnotated;
  }

  Annotation annotation () const       { return annotation_; }
  void annotate         (Annotation a) { annotation_ = a; }
  void propagate        ();
  void propagateThroughOppositeNode (const Node *n);

  // neighbors handling
  AnnotatedArc *ptrUpstreamArc   () const;
  AnnotatedArc *ptrDownstreamArc () const;

private :

  TamponPartage upstreamNode_;
  TamponPartage downstreamNode_;
  Annotation    annotation_;
  const void   *origin_;

};

#endif
