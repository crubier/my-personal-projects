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
//>       ValeurDerivee2.cpp
//
//$Resume
//       fichier d'implantation de la classe ValeurDerivee2
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class ValeurDerivee2          
//>         operator =()                
//>         operator *=()               
//>         operator /=()               
//>       ValeurDerivee2 sqrt()         
//>       ValeurDerivee2 sin()          
//>       ValeurDerivee2 cos()          
//>       ValeurDerivee2 tan()          
//>       ValeurDerivee2 asin()         
//>       ValeurDerivee2 acos()         
//>       ValeurDerivee2 atan()         
//>       ValeurDerivee2 exp()          
//>       ValeurDerivee2 log()          
//>       ValeurDerivee2 atan2()        
//>       ValeurDerivee2& operator +=() 
//>       ValeurDerivee2& operator -=() 
//>       ValeurDerivee2& operator *=() 
//>       ValeurDerivee2& operator /=() 
//>       ValeurDerivee2 Approximation()
//>       ostream& operator <<()        
//
//$Historique
//       $Log: ValeurDerivee2.cpp,v $
//       Revision 1.10  2003/02/04 09:30:49  cantor
//       DM-ID 17 Mise à jour du nom du fichier dans le bandeau suite à la modification des extensions.
//
//       Revision 1.9  2000/08/09 14:36:42  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.8.4.1  2000/03/30 15:36:07  cantor
//       ajout du copyright CNES
//
//       Revision 1.8  1998/06/24 10:12:10  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.7  1998/04/26 15:24:13  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.6  1997/07/11 09:16:06  luc
//       ajout d'une protection sur les dérivées de la racine carrée
//       ajout d'un en-tête de fichier
//
//       Revision 1.5  1997/05/20 08:17:50  luc
//       correction des fonctions amies :
//         operator *= (ValeurDerivee2& a, double b)
//         operator /= (ValeurDerivee2& a, double b)
//         ValeurDerivee2 Approximation (const ValeurDerivee2& t,
//                                       const ValeurDerivee2& ta,
//                                       const ValeurDerivee2& fa,
//                                       const ValeurDerivee2& tb,
//                                       const ValeurDerivee2& fb)
//       
//       Revision 1.4  1997/03/26 06:54:37  luc
//       changement des conventions de nommage
//       
//       Revision 1.3  1997/03/24 09:32:46  luc
//       passage de SCCS à RCS
//       
//       Revision 1.2  1994/11/26 15:17:42  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.1  1994/07/27 14:53:36  luc
//       Initial revision
//
//$Version
//       $Id: ValeurDerivee2.cpp,v 1.10 2003/02/04 09:30:49 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "cantor/ValeurDerivee2.h"


ValeurDerivee2& ValeurDerivee2::operator = (const ValeurDerivee2& a)
{ if (this != &a)            // protection contre x = x
  { f2_ = a.f2_;
    f1_ = a.f1_;
    f0_ = a.f0_;
  }

  return *this;

}

ValeurDerivee2& ValeurDerivee2::operator *= (const ValeurDerivee2& a)
{ double t = f1_ * a.f1_;

  f2_  = f2_ * a.f0_ + t + t + f0_ * a.f2_; // (f.g)" = f".g + 2 f'.g' + f.g"
  f1_  = f1_ * a.f0_ + f0_ * a.f1_;         // (f.g)' = f'.g + f.g'
  f0_  = f0_ * a.f0_;                       // (f.g)  = f.g

  return *this;

}

ValeurDerivee2& ValeurDerivee2::operator /= (const ValeurDerivee2& a)
{ double t1  = a.f0_ * a.f0_;
  double t2  = f1_ * a.f0_ - f0_ * a.f1_;
         t2 += t2;
  double t3  = f2_ * a.f0_ - f0_ * a.f2_;

  f2_  = (a.f0_ * t3  - a.f1_ * t2) / (a.f0_ * t1);
  f1_  = (f1_ * a.f0_ - f0_ * a.f1_) / t1;
  f0_  = f0_ / a.f0_;

  return *this;

}

ValeurDerivee2 sqrt (const ValeurDerivee2& a)
{ double x   = a.f0 ();
  double u0  = sqrt (x);
  double xu0 = x * u0;
  return Composition (u0,
                      0.5 / (u0 < 1.0e-20 ? 1.0e-20 : u0),
                      -0.25 / (xu0 < 1.0e-20 ? 1.0e-20 : xu0),
                      a);
}

ValeurDerivee2 sin (const ValeurDerivee2& a)
{ double x  = a.f0 ();
  double u0 = sin (x);
  return Composition (u0, cos (x), -u0, a);
}

ValeurDerivee2 cos (const ValeurDerivee2& a)
{ double x  = a.f0 ();
  double u0 = cos (x);
  return Composition (u0, -sin (x), -u0, a);
}

ValeurDerivee2 tan (const ValeurDerivee2& a)
{ double u0  = tan (a.f0 ());
  double u1  = 1.0 + u0 * u0;
  double u2  = u0 * u1;
         u2 += u2;
  return Composition (u0, u1, u2, a);
}

ValeurDerivee2 asin (const ValeurDerivee2& a)
{ double x   = a.f0 ();
  double s   = 1.0 - x * x;
  double u0  = asin (x);
  double u1  = 1.0 / sqrt (s);
  double u2  = x * u1 / s;
  return Composition (u0, u1, u2, a);
}

ValeurDerivee2 acos (const ValeurDerivee2& a)
{ double x   = a.f0 ();
  double s   = 1.0 - x * x;
  double u0  = acos (x);
  double u1  = -1.0 / sqrt (s);
  double u2  = x * u1 / s;
  return Composition (u0, u1, u2, a);
}

ValeurDerivee2 atan (const ValeurDerivee2& a)
{ double x   = a.f0 ();
  double u0  = atan (x);
  double u1  = 1.0 / (1.0 + x * x);
  double u2  = -x * u1 * u1;
         u2 += u2;
  return Composition (u0, u1, u2, a);
}

ValeurDerivee2 exp (const ValeurDerivee2& a)
{ double x   = a.f0 ();
  double u0  = exp (x);
  return Composition (u0, u0, u0, a);
}

ValeurDerivee2 log (const ValeurDerivee2& a)
{ double x   = a.f0 ();
  double u0  = log (x);
  double u1  = 1.0 / x;
  return Composition (u0, u1, -u1 * u1, a);
}

ValeurDerivee2 atan2 (const ValeurDerivee2& y, const ValeurDerivee2& x)
{ // l'angle retourné est toujours compris entre -pi et +pi
  // la formulation évite les points singuliers -pi/2, 0, +pi/2

  ValeurDerivee2 r = sqrt (x * x + y * y);

  if (x >= 0.0)
  { ValeurDerivee2 a = atan (y / (r + x));
    return a + a;
  }
  else
  { ValeurDerivee2 a  = atan (y / (r - x));
            a += a;
    if (a <= 0.0)
      return -M_PI - a;
    else
      return  M_PI - a;
  }

}

ValeurDerivee2& operator += (ValeurDerivee2& a, double b)
{ a.f0_ += b; return a; }

ValeurDerivee2& operator -= (ValeurDerivee2& a, double b)
{ a.f0_ -= b; return a; }

ValeurDerivee2& operator *= (ValeurDerivee2& a, double b)
{ a.f2_ *= b; a.f1_ *= b; a.f0_ *= b; return a; }

ValeurDerivee2& operator /= (ValeurDerivee2& a, double b)
{ a.f2_ /= b; a.f1_ /= b; a.f0_ /= b; return a; }

ValeurDerivee2& operator += (ValeurDerivee2& a, const ValeurDerivee1& b)
{ a.f0_ += b.f0 (); a.f1_ += b.f1 (); return a; }

ValeurDerivee2& operator -= (ValeurDerivee2& a, const ValeurDerivee1& b)
{ a.f0_ -= b.f0 (); a.f1_ -= b.f1 (); return a; }

ValeurDerivee2 Approximation (const ValeurDerivee2& t,
                              const ValeurDerivee2& ta,
                              const ValeurDerivee2& fa,
                              const ValeurDerivee2& tb,
                              const ValeurDerivee2& fb)
{ ValeurDerivee2 b_a    = tb    - ta;
  ValeurDerivee2 b_a_2  = b_a   * b_a;
  ValeurDerivee2 b_a_3  = b_a_2 * b_a;
  ValeurDerivee2 b_a_s4 = b_a   / 4.0;
  ValeurDerivee2 c      = 5.0   * b_a_s4 * b_a_s4;

  ValeurDerivee2 x_b    = t     - tb;
  ValeurDerivee2 x_a    = t     - ta;

  // polynôme de valeur 1 en a
  ValeurDerivee2 x_b_3  = x_b * x_b * x_b;
  ValeurDerivee2 y      = x_a + b_a_s4;
  ValeurDerivee2 p0a    = -2.0 * x_b_3 * (3.0 * y * y + c) / (b_a_2 * b_a_3);

  // polynôme de valeur 1 en b
  ValeurDerivee2 x_a_3  = x_a * x_a * x_a;
                 y      = x_b - b_a_s4;
  ValeurDerivee2 p0b    =  2.0 * x_a_3 * (3.0 * y * y + c) / (b_a_2 * b_a_3);

  // polynôme de dérivée 1 en a
  ValeurDerivee2 p1a    = -x_b_3 * x_a * (3.0 * x_a + b_a) / (b_a_2 * b_a_2);

  // polynôme de dérivée 1 en b
  ValeurDerivee2 p1b    = -x_a_3 * x_b * (3.0 * x_b - b_a) / (b_a_2 * b_a_2);

  // polynôme de dérivée seconde 1 en a
  ValeurDerivee2 p2a    = -x_a * x_a * x_b_3 / (b_a_3 + b_a_3);

  // polynôme de dérivée seconde 1 en b
  ValeurDerivee2 p2b    =  x_b * x_b * x_a_3 / (b_a_3 + b_a_3);

  // combinaison linéaire des polynômes
  return p0a * fa.f0 () + p1a * fa.f1 () + p2a * fa.f2 ()
       + p0b * fb.f0 () + p1b * fb.f1 () + p2b * fb.f2 ();

}

ostream& operator << (ostream& s, const ValeurDerivee2& a)
{ char signe1, signe2;
  double f1, f2;

  if (a.f1 () < 0.0)
  { signe1 = '-';
    f1     = -(a.f1 ());
  }
  else
  { signe1 = '+';
    f1     = a.f1 ();
  }

  if (a.f2 () < 0.0)
  { signe2 = '-';
    f2     = -(a.f2 ());
  }
  else
  { signe2 = '+';
    f2     = a.f2 ();
  }

  return s << a.f0 () << " (" << signe1 << f1 << " (" << signe2 << f2 << "))";

}
  
