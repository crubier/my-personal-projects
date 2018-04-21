subroutine mu_prod_vect (vect_a, vect_b, vect_c, code_retour)

! (C) Copyright CNES - MSLIB - 1998-2003

!************************************************************************
!
! But:  Dans un repere orthonorme, calcul du produit vectoriel de deux vecteurs.
! ===  
!
! Historique:
! ==========
!   + Version 1.0 (SP 205 ed01 rev00): creation a partir de la routine MUPVEC de la MSLIB f77
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!************************************************************************


! Modules
! =======

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mu_prod_vect.h'

! Autres declarations
! -------------------

character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mu_prod_vect.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mu_prod_vect.f90,v 1.7 2003/10/14 12:53:53 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
code_retour%valeur = pm_OK

!     ==================================================
! calcul du produit vectoriel vect_c = vect_a * vect_b
!          ( a1            ( b1            ( c1 = a2*b3 - a3*b2
!   vect_a ( a2  *  vect_b ( b2  =  vect_c ( c2 = a3*b1 - a1*b3
!          ( a3            ( b3            ( c3 = a1*b2 - a2*b1
!     ==================================================

vect_c(1) = (vect_a(2) * vect_b(3)) - (vect_a(3) * vect_b(2))
vect_c(2) = (vect_a(3) * vect_b(1)) - (vect_a(1) * vect_b(3))
vect_c(3) = (vect_a(1) * vect_b(2)) - (vect_a(2) * vect_b(1))

6000 continue

code_retour%routine = pm_num_mu_prod_vect
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mu_prod_vect
