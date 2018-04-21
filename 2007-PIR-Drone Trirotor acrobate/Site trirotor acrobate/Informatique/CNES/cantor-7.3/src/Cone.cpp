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
//>       Cone.cpp
//
//$Resume
//       fichier d'implantation de la classe Cone
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class Cone      
//>         Cone()        
//>         operator =()  
//>         operator -()  
//>         corrige()     
//>         intersection()
//
//$Historique
//       $Log: Cone.cpp,v $
//       Revision 2.14  2003/02/04 09:26:48  cantor
//       DM-ID 17 Mise à jour du nom du fichier dans le bandeau suite à la modification des extensions.
//
//       Revision 2.13  2001/09/18 16:08:51  cantor
//       ajout d'un constructeur à partir de trois points,
//       ajout de l'opérateur « - » unaire pour la complémentation
//
//       Revision 2.12  2001/06/05 15:47:23  cantor
//       utilisation du mécanisme des exceptions pour la gestion des erreurs
//
//       Revision 2.11  2000/08/09 14:36:41  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 2.10.2.1  2000/03/30 15:36:05  cantor
//       ajout du copyright CNES
//
//       Revision 2.10  1999/08/05 09:54:29  cantor
//       modification résultant du merge entre les versions
//       release-5-0-1 et pre-5-2
//
//       Revision 2.9.2.1  1999/04/26 10:39:35  cantor
//       gestion du sinus du demi-angle
//
//       Revision 2.9  1998/06/24 10:08:38  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 2.8  1998/05/12 12:56:40  luc
//       inversion d'une expression pour contourner un bug du compiplateur SUN 4.0
//
//       Revision 2.7  1998/04/26 15:59:47  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 2.6  1998/04/18 18:09:47  luc
//       élimination de la méthode estValide
//
//       Revision 2.5  1997/07/06 10:23:40  luc
//       ajout d'un en-tête de fichier
//
//       Revision 2.4  1997/04/03 19:30:25  luc
//       inversion des codes de retour, 0 signifie désormais : pas d'erreur
//       
//       Revision 2.3  1997/03/26 06:54:28  luc
//       changement des conventions de nommage
//       
//       Revision 2.2  1997/03/24 09:32:39  luc
//       passage de SCCS à RCS
//       
//       Revision 2.1  1996/07/16 11:53:20  luc
//       élimination de la dépendance aux tools.h++ (Rogue Wave)
//       
//       Revision 1.7  1995/08/17 12:16:44  mercator
//       modification des seuils d'alignement
//       (0.2 seconde d'arc au lieu de la precision machine)
//       
//       Revision 1.6  1994/12/16 09:21:14  mercator
//       correction d'une erreur de parenthesage
//       (qui engendrait des resultats faux pour l'intersection de cones
//        non perpendiculaires)
//       
//       Revision 1.5  1994/12/13 10:24:36  mercator
//       transformation du type de retour de "intersection" de void a int
//       
//       Revision 1.4  1994/12/12 15:14:30  mercator
//       generalisation a toute la biliotheque de l'argument CantorErreurs* optionnel
//       
//       Revision 1.3  1994/11/26 15:16:31  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.2  1994/11/09 16:04:18  mercator
//       remplacement de la fonction "lance" par "erreur"
//       
//       Revision 1.1  1994/07/27 14:53:16  luc
//       Initial revision
//
//$Version
//       $Id: Cone.cpp,v 2.14 2003/02/04 09:26:48 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000-2001 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "cantor/Cone.h"


Cone::Cone ()
  : a_ (1.0, 0.0, 0.0), mu_ (0.0), cosMu_ (1.0), sinMu_ (0.0)
{}

Cone::Cone (const VecDBL& a, double mu)
  throw (CantorErreurs)
  : a_ (a)
{
  a_.normalise ();
  mu_    = (mu >= M_PI) ? M_PI : ((mu <= 0) ? 0 : mu);
  cosMu_ = cos  (mu_);
  sinMu_ = sin  (mu_);
}

Cone::Cone (const VecDBL& p1, const VecDBL& p2, const VecDBL& p3)
  throw (CantorErreurs)
  : a_ ((p2 - p1) ^ (p3 - p1))
{
  // construit un cône passant par trois points
  a_.normalise ();
  mu_    = a_.angleAvecVecteur (p1),
  cosMu_ = cos  (mu_);
  sinMu_ = sin  (mu_);
}

Cone& Cone::operator = (const Cone& c)
{ if (this != &c)       // protection contre x = x
  {
    a_     = c.a_;
    mu_    = c.mu_;
    cosMu_ = c.cosMu_;
    sinMu_ = c.sinMu_;
  }

  return *this;

}

Cone Cone::operator - () const
{ // calcule le cône complémentaire par rapport à la sphère unité
  return Cone (-a_, M_PI - mu_);
}

void Cone::corrige (double ecart)
{ // calcul du nouvel angle d'ouverture du cône
  mu_ += ecart;

  // recadrage entre 0 et PI
  if (mu_ < 0.0)
    mu_ = 0.0;
  if (mu_ > M_PI)
    mu_ = M_PI;

  cosMu_ = cos (mu_);
  sinMu_ = sin (mu_);

}

void Cone::intersection (const Cone &c, VecDBL* p_deb, VecDBL* p_fin) const
  throw (CantorErreurs)
{
  double scal  = a_ | c.a_;
  double coeff = 1.0 - scal * scal;

  if (coeff < 1.0e-12)  // seuil d'alignement: 0.2 seconde d'arc
    throw CantorErreurs (CantorErreurs::cones_coaxiaux);
  coeff = 1.0 / coeff;

  // calcul des coordonnées de la partie coplanaire a (u, v)
  double x          = (  cosMu_ - scal * c.cosMu_) * coeff;
  double y          = (c.cosMu_ - scal *   cosMu_) * coeff;
  VecDBL coplanaire = a_ * x + c.a_ * y;

  // calcul de la coordonnée normale
  double            norme_2 = 1.0 - (coplanaire | coplanaire);
  if (norme_2 < 1.0e-12)
    throw CantorErreurs (CantorErreurs::cones_disjoints);
  double z       = sqrt (norme_2 * coeff);
  VecDBL normale = z * (a_ ^ c.a_);

  // début et fin de l'intersection (rotation orientée par this->a_)
  *p_deb = coplanaire - normale;
  *p_fin = coplanaire + normale;

}
