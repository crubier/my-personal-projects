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
//>       ValeurDerivee1.cpp
//
//$Resume
//       fichier d'implantation de la classe ValeurDerivee1
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class ValeurDerivee1          
//>         operator =()                
//>         operator *=()               
//>         operator /=()               
//>       ValeurDerivee1 sqrt()         
//>       ValeurDerivee1 sin()          
//>       ValeurDerivee1 cos()          
//>       ValeurDerivee1 tan()          
//>       ValeurDerivee1 asin()         
//>       ValeurDerivee1 acos()         
//>       ValeurDerivee1 atan()         
//>       ValeurDerivee1 exp()          
//>       ValeurDerivee1 log()          
//>       ValeurDerivee1 atan2()        
//>       ValeurDerivee1& operator +=() 
//>       ValeurDerivee1& operator -=() 
//>       ValeurDerivee1& operator *=() 
//>       ValeurDerivee1& operator /=() 
//>       ValeurDerivee1 Approximation()
//>       ostream& operator <<()        
//
//$Historique
//       $Log: ValeurDerivee1.cpp,v $
//       Revision 1.10  2003/02/04 09:30:40  cantor
//       DM-ID 17 Mise à jour du nom du fichier dans le bandeau suite à la modification des extensions.
//
//       Revision 1.9  2000/08/09 14:36:42  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.8.4.1  2000/03/30 15:36:07  cantor
//       ajout du copyright CNES
//
//       Revision 1.8  1998/06/24 10:11:54  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.7  1998/04/26 15:24:12  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.6  1997/07/11 09:13:55  luc
//       ajout d'une protection sur les dérivées de la racine carrée
//       ajout d'un en-tête de fichier
//
//       Revision 1.5  1997/05/20 08:20:24  luc
//       correction des fonctions amies :
//         operator *= (ValeurDerivee1& a, double b)
//         operator /= (ValeurDerivee1& a, double b)
//         ValeurDerivee1 Approximation (const ValeurDerivee1& t,
//                                       const ValeurDerivee1& ta,
//                                       const ValeurDerivee1& fa,
//                                       const ValeurDerivee1& tb,
//                                       const ValeurDerivee1& fb)
//       
//       Revision 1.4  1997/03/26 06:54:36  luc
//       changement des conventions de nommage
//       
//       Revision 1.3  1997/03/24 09:32:45  luc
//       passage de SCCS à RCS
//       
//       Revision 1.2  1994/11/26 15:17:37  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.1  1994/07/27 14:53:35  luc
//       Initial revision
//
//$Version
//       $Id: ValeurDerivee1.cpp,v 1.10 2003/02/04 09:30:40 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "cantor/ValeurDerivee1.h"


ValeurDerivee1& ValeurDerivee1::operator = (const ValeurDerivee1& a)
{ if (this != &a)            // protection contre x = x
  { f1_ = a.f1_;
    f0_ = a.f0_;
  }

  return *this;

}

ValeurDerivee1& ValeurDerivee1::operator *= (const ValeurDerivee1& a)
{ f1_  = f1_ * a.f0_ + f0_ * a.f1_;       // (f.g)' = f'.g + f.g'
  f0_  = f0_ * a.f0_;                     // (f.g)  = f.g

  return *this;

}

ValeurDerivee1& ValeurDerivee1::operator /= (const ValeurDerivee1& a)
{ f1_  = (f1_ * a.f0_ - f0_ * a.f1_) / (a.f0_ * a.f0_);
  f0_  = f0_ / a.f0_;

  return *this;

}

ValeurDerivee1 sqrt (const ValeurDerivee1& a)
{ double x  = a.f0 ();
  double u0 = sqrt (x);
  return Composition (u0, 0.5 / (u0 < 1.0e-20 ? 1.0e-20 : u0), a);
}

ValeurDerivee1 sin (const ValeurDerivee1& a)
{ double x  = a.f0 ();
  return Composition (sin (x), cos (x), a);
}

ValeurDerivee1 cos (const ValeurDerivee1& a)
{ double x  = a.f0 ();
  return Composition (cos (x), -sin (x), a);
}

ValeurDerivee1 tan (const ValeurDerivee1& a)
{ double u0  = tan (a.f0 ());
  return Composition (u0, 1.0 + u0 * u0, a);
}

ValeurDerivee1 asin (const ValeurDerivee1& a)
{ double x   = a.f0 ();
  double u0  = asin (x);
  double u1  = 1.0 / sqrt (1.0 - x * x);
  return Composition (u0, u1, a);
}

ValeurDerivee1 acos (const ValeurDerivee1& a)
{ double x   = a.f0 ();
  double u0  = acos (x);
  double u1  = -1.0 / sqrt (1.0 - x * x);
  return Composition (u0, u1, a);
}

ValeurDerivee1 atan (const ValeurDerivee1& a)
{ double x   = a.f0 ();
  double u0  = atan (x);
  double u1  = 1.0 / (1.0 + x * x);
  return Composition (u0, u1, a);
}

ValeurDerivee1 exp (const ValeurDerivee1& a)
{ double x   = a.f0 ();
  double u0  = exp (x);
  return Composition (u0, u0, a);
}

ValeurDerivee1 log (const ValeurDerivee1& a)
{ double x   = a.f0 ();
  double u0  = log (x);
  double u1  = 1.0 / x;
  return Composition (u0, u1, a);
}

ValeurDerivee1 atan2 (const ValeurDerivee1& y, const ValeurDerivee1& x)
{ // l'angle retourné est toujours compris entre -pi et +pi
  // la formulation évite les points singuliers -pi/2, 0, +pi/2

  ValeurDerivee1 r = sqrt (x * x + y * y);

  if (x >= 0.0)
  { ValeurDerivee1 a = atan (y / (r + x));
    return a + a;
  }
  else
  { ValeurDerivee1 a  = atan (y / (r - x));
            a += a;
    if (a <= 0.0)
      return -M_PI - a;
    else
      return  M_PI - a;
  }

}

ValeurDerivee1& operator += (ValeurDerivee1& a, double b)
{ a.f0_ += b; return a; }

ValeurDerivee1& operator -= (ValeurDerivee1& a, double b)
{ a.f0_ -= b; return a; }

ValeurDerivee1& operator *= (ValeurDerivee1& a, double b)
{ a.f1_ *= b; a.f0_ *= b; return a; }

ValeurDerivee1& operator /= (ValeurDerivee1& a, double b)
{ a.f1_ /= b; a.f0_ /= b; return a; }

ValeurDerivee1 Approximation (const ValeurDerivee1& t,
                              const ValeurDerivee1& ta,
                              const ValeurDerivee1& fa,
                              const ValeurDerivee1& tb,
                              const ValeurDerivee1& fb)
{ ValeurDerivee1 b_a   = tb    - ta;
  ValeurDerivee1 b_a_2 = b_a   * b_a;
  ValeurDerivee1 b_a_3 = b_a_2 * b_a;

  ValeurDerivee1 x_b   = t     - tb;
  ValeurDerivee1 x_b_2 = x_b   * x_b;
  ValeurDerivee1 x_a   = t     - ta;
  ValeurDerivee1 x_a_2 = x_a   * x_a;

  // polynôme de valeur 1 en a
  ValeurDerivee1 p0a = x_b_2 * (b_a + x_a + x_a) / b_a_3;

  // polynôme de valeur 1 en b
  ValeurDerivee1 p0b = x_a_2 * (b_a - x_b - x_b) / b_a_3;

  // polynôme de dérivée 1 en a
  ValeurDerivee1 p1a = x_a * x_b_2 / b_a_2;

  // polynôme de dérivée 1 en b
  ValeurDerivee1 p1b = x_b * x_a_2 / b_a_2;

  // combinaison linéaire des polynômes
  return p0a * fa.f0 () + p1a * fa.f1 () + p0b * fb.f0 () + p1b * fb.f1 ();

}

ostream& operator << (ostream& s, const ValeurDerivee1& a)
{ char signe1;
  double f1;

  if (a.f1 () < 0.0)
  { signe1 = '-';
    f1     = -(a.f1 ());
  }
  else
  { signe1 = '+';
    f1     = a.f1 ();
  }

  return s << a.f0 () << " (" << signe1 << f1 << ')';

}
