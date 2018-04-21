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
//>       Braid.h
//$Resume
//       header file for Braid class
//
//$Description
//       Declaration module for the class
//
//$Contenu
//>       class Braid
//$Historique
//       $Log: Braid.h,v $
//       Revision 1.7  2002/12/10 14:52:59  cantor
//       DM-ID 12 Ajout d'un destructeur pour prévenir celui crée par le compilateur
//
//       Revision 1.6  2002/09/03 15:10:01  cantor
//       correction de 'throw', suppression de la méthode 'isCovered' (FA15)
//
//       Revision 1.5  2002/09/02 09:21:24  cantor
//       complete revamp to use oriented annotated arcs
//
//       Revision 1.4  2002/01/17 08:42:47  cantor
//       correction de spécifications throw
//
//       Revision 1.3  2001/06/22 06:30:16  cantor
//       added the methods isCovered, coveringHeuristic and closeParallelsHeuristic
//       the methods intersectionBoundary, unionBoundary and boundary are now const
//
//       Revision 1.2  2001/06/12 12:50:13  cantor
//       use an axis and an angle instead of a rotation for spreading
//
//       Revision 1.1  2001/06/05 15:22:16  cantor
//       initial version
//
//$Version
//       $Id: Braid.h,v 1.7 2002/12/10 14:52:59 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2001 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_Braid_h
#define __cantor_Braid_h

#include <list>
#include <vector>

#include "cantor/CantorErreurs.h"
#include "cantor/AnnotatedArc.h"
#include "cantor/Field.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class Braid
//$Resume
//       represents braids of annotated arcs for fields boundaries building
//
//$Description
//       modelizes braids of annotated arcs on the unit sphere. These
//       braids are used during the computation of fields unions and
//       intersections. A braid of all intervening arcs from all
//       fields is built and the arcs are later annotated as either
//       belonging to the intersection or to the union. Once all arcs
//       are correctly annotated, the boundary is built by selecting
//       the proper arcs. The braid is then discarded.
//
//$Usage
//>     construction : 
//          without argument
//          from a field boundary
//          from the spreading of an arc
//          by copy
//>     utilisation  : 
//>       Braid& operator =                    () 
//          affectation
//>       static void intertwine               () 
//          combine two braids by splitting their arcs with respect to
//          one another and inserting nodes to build the proper topology
//>       void absorb                          () 
//          absorb another braid, which becomes empty
//>       void initAnnotations                 () 
//          Annotate all arcs as unknown
//>       void identifyArcs                    () 
//          identify the arcs with respect to the field they do not come from
//>       bool isCompletelyAnnotated           () 
//          chek if all arcs have been annotated
//>       void simplify                        () 
//          Simplify the instance by removing unneeded arcs
//>       bool coveringHeuristic               () 
//          try to annotate the arcs covered by the spreading of an arc
//>       bool closeParallelsHeuristic         () 
//          try to annotate the close parallel arcs
//>       bool equivalentPathsHeuristic        () 
//          try to annotate the arcs of equivalent paths
//>       bool splittingHeuristic              () 
//          try to split some arcs that are ambiguous only in the
//          check point neighborhood
//>       bool peelingHeuristic                () 
//          try to remove ambiguous paths protrubing from the boundary
//          and which are merely flakes
//>       void intersectionBoundary            () 
//          extract the boundary of the intersection of the initial fields
//>       void unionBoundary                   () 
//          extract the boundary of the union of the initial fields
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2001 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class Braid
{
public :

  // constructors
  Braid ()
  {}

  Braid (const Field *origin,
         vector< vector<Arc> >::const_iterator begin,
         vector< vector<Arc> >::const_iterator end)
    throw (CantorErreurs);

  Braid (const Arc& a, VecDBL axis, double spreading)
    throw (CantorErreurs);

  Braid (const Braid& b)
    : arcs_ (b.arcs_)
  {}

  Braid& operator = (const Braid& b);

  // destructor
  ~Braid ()
  {}

  // braids combination
  static void intertwine (Braid *ptrB1, Braid *ptrB2)
    throw (CantorErreurs);
  void absorb            (Braid *ptrOther);

  // nominal annotations handling
  void initAnnotations       ();
  void identifyArcs          (const Field *ptrF1, const Field *ptrF2)
    throw (CantorErreurs);
  bool isCompletelyAnnotated () const;

  // ambiguous cases handling
  void simplify                 ()
    throw (CantorErreurs);
  bool coveringHeuristic        (const Arc& a,
                                 const VecDBL& axis, double spreading)
    throw (CantorErreurs);
  bool closeParallelsHeuristic  ()
    throw (CantorErreurs);
  bool splittingHeuristic       ()
    throw (CantorErreurs);
  bool equivalentPathsHeuristic ();
  bool peelingHeuristic ();

  // boundary extraction
  void intersectionBoundary (vector< vector<Arc> > *ptrB) const
  { boundary (ptrB, AnnotatedArc::intersectionAnnotated); }

  void unionBoundary        (vector< vector<Arc> > *ptrB) const
  { boundary (ptrB, AnnotatedArc::unionAnnotated); }

private :

  // arcs list
  list<AnnotatedArc> arcs_;

  // generic function to extract arcs according to their annotation
  void boundary (vector< vector<Arc> > *ptrB,
                 AnnotatedArc::Annotation annotation) const;

};

#endif
