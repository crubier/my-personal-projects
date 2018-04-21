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
//>       Field.h
//$Resume
//       header file for Field class
//
//$Description
//       Declaration module for the class
//
//$Contenu
//>       class Field                     
//>       typedef vector<Arc> Loop      
//>       typedef vector<Loop> Boundary
//$Historique
//       $Log: Field.h,v $
//       Revision 1.7  2002/12/10 15:05:20  cantor
//       DM-ID 12 Ajout d'un destructeur pour prévenir celui crée par le compilateur
//
//       Revision 1.6  2002/09/03 15:21:34  cantor
//       modification de fond (FA15)
//
//       Revision 1.5  2002/01/17 08:42:47  cantor
//       correction de spécifications throw
//
//       Revision 1.4  2001/09/18 16:07:23  cantor
//       ajout des attributs rejectionCone_ et activeRejectionCone_ et des
//       méthodes selectClosest, recursRejectionCone et computeRejectionCone
//       pour accélérer les tests d'appartenance
//
//       Revision 1.3  2001/06/22 06:20:31  cantor
//       added the isEmpty and isFull methods
//
//       Revision 1.2  2001/06/12 12:49:43  cantor
//       use an axis and an angle instead of a rotation for spreading
//
//       Revision 1.1  2001/06/05 15:21:23  cantor
//       initial version
//
//$Version
//       $Id: Field.h,v 1.7 2002/12/10 15:05:20 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2001 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_Field_h
#define __cantor_Field_h

#include <list>
#include <vector>

#include "cantor/Arc.h"
#include "cantor/ArcIterateur.h"
#include "cantor/CantorErreurs.h"
#include "cantor/Secteurs.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class Field
//$Resume
//       model for a field on the unit sphere
//
//$Description
//       model for a field on the unit sphere
//       (it can be splitted in several disjoint parts)
//
//$Usage
//>     construction : 
//          without argument
//          from a cone
//          from the spreading of an arc by a rotation around an axis
//          by copy
//>     utilisation  : 
//>       typedef vector<Arc> Loop         :
//          boundary of an elementary field
//>       typedef vector<Loop> Boundary    :
//          boundary of a complex field
//>       typedef void TypeFuncConstField ()
//          function operating on a constant field
//>       typedef void TypeFuncField      ()
//          function operating on a field
//>       Field& operator =               () 
//          affectation
//>       bool isEmpty                    ()
//          check if the instance is empty
//>       bool isFull                     ()
//          check if the instance covers the all sphere
//>       bool isInside                   ()
//          check if a point is inside the instance 
//>       double offsetFromBoundary       ()
//          compute the signed offset between a point and the boundary
//>       Secteurs selectInside           () 2 signatures - 
//          return the part of a sector or a cone that belong to the field
//>       Field operator -                () 
//          switch inside and outside
//>       const Field& operator *=        () 
//          intersect the instance and the argument
//>       const Field& operator +=        () 
//          merge the instance and the argument
//>       const Field& operator -=        () 
//          remove the argument from the instance
//>       void rotate                     () 
//          rotate the instance
//>       void spread                     () 
//          spread the instance using a rotation around an axis
//>       void applyMargin                () 
//          add (or remove according to the sign) an angular margin
//>       void initWalk                   () 
//          initialize a boundary walk with a given tolerance
//>       bool nextPoint                  () 
//          compute the following point in the boundary walk,
//          indicate if this point will be the last of a given loop
//          (i.e. the next point belong to a disjoint loop)
//          retourne a validity indicator
//>       void stopWalk                   () 
//          interrupt the boundary walk
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2001 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class Field
{
  public :

  // types of the global functions that can by applied to a Field
  typedef void TypeFuncConstField (const Field& f, void* arg);
  typedef void TypeFuncField      (      Field& f, void* arg);

  // types simplifying boundary handling
  typedef vector<Arc>  Loop;
  typedef vector<Loop> Boundary;

  // constructors
  Field ()
    : empty_ (true), rejectionCone_ (), activeRejectionCone_ (false),
      targetPoint_ (1.0, 0.0, 0.0), activeTargetPoint_ (false),
      iter_ (0), init_ (false), tolerance_ (1.0e-4)
  {}
  Field (const Cone& c);
  Field (const Arc& a, const VecDBL& axis, double spreading)
    throw (CantorErreurs);
  Field (const Field& f);
  Field& operator = (const Field& f);

  // destructor
  ~Field () {}

  // inclusion check functions
  bool isEmpty () const { return boundary_.empty () &&   empty_; }
  bool isFull  () const { return boundary_.empty () && ! empty_; }
  bool isInside (const VecDBL& point, bool *ptrDegenerated = 0) const
    throw (CantorErreurs);

  double offsetFromBoundary (const VecDBL& point) const
    throw (CantorErreurs);

  Secteurs selectInside (const Secteurs& s) const
    throw (CantorErreurs);

  Secteurs selectInside (const Cone& c) const
    throw (CantorErreurs)
  { return selectInside (Secteurs (c)); }

  // set-like operators (complementation, union, intersection, disjunction)
  Field operator - () const;

  const Field& operator *= (const Field& f) throw (CantorErreurs)
  { return combine (f, true);  }

  const Field& operator += (const Field& f) throw (CantorErreurs)
  { return combine (f, false); }

  const Field& operator -= (const Field& f) throw (CantorErreurs)
  { return *this *= -f; }

  // specific operations
  void rotate      (const RotDBL& r);
  void spread      (const VecDBL& axis, double spreading)
    throw (CantorErreurs);
  void applyMargin (double m) throw (CantorErreurs);

  // boundary walks
  void initWalk    (double tolerance = 1.0e-4);
  bool nextPoint   (VecDBL *ptrPoint, bool *ptrLast);
  void stopWalk    ();

private :

  // empty indicator, used when there is no boundary, i.e. when
  // the field is either empty or cover the all sphere
  bool empty_;

  // boundary between inside and outside
  Boundary boundary_;

  // rejection cone used to speed up checks
  Cone rejectionCone_;
  bool activeRejectionCone_;

  // target point on the boundary used to check inside/outside
  mutable VecDBL targetPoint_;
  mutable bool activeTargetPoint_;

  // attributes used for the boundary walks
  ArcIterateur            *iter_;                
  bool                     init_;                
  Boundary::const_iterator i_; 
  Loop::const_iterator     j_;
  double                   tolerance_;

  // generic function to compute both reunion and intersection
  const Field& combine (const Field& f, bool intersection)
    throw (CantorErreurs);

  // remove unneeded null arcs
  void simplifyBoundary ();

  // select the arcs that are inside the instance
  void select (list<Arc> *ptrList) const
    throw (CantorErreurs);

  // compute the rejection cone
  bool selectClosest (VecDBL *ptrP,
                      const VecDBL& p,
                      int nbPointsToAvoid, const VecDBL** pointsToAvoid) const;
  Cone recursRejectionCone (const VecDBL& p1,
                            const VecDBL& p2,
                            const VecDBL& p3,
                            int depth) const
    throw (CantorErreurs);
  void computeRejectionCone () throw (CantorErreurs);

  void computeTargetPoint (const VecDBL& point) const
    throw (CantorErreurs);
  void firstCrossing (Arc *ptrArc, Loop::const_iterator *ptrCrossing) const
    throw (CantorErreurs);

};

#endif
