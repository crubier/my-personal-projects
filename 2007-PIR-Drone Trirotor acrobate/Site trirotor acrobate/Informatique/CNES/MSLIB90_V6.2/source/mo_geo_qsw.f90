subroutine mo_geo_qsw (pos_car, vit_car, vect_geo, vect_qsw, code_retour)

! (C) Copyright CNES - MSLIB - 1998

!************************************************************************
!
! But:  Calcul des composantes dans le repere orbital local (Q, S, W) d'un vecteur
! ===   defini dans le repere GEOcentrique inertiel ou sont exprimees les positions-vitesses
!       du satellite
!
! Note d'utilisation:  La transformation inverse peut se faire par la routine mo_qsw_geo.
! ==================  
!
! Historique:
! ==========
!   + Version 1.0 (SP 218 ed01 rev00): creation a partir de la routine MV0RRA de la MSLIB f77
!   + Version 2.0 (DE 368 ed01 rev00): utilisation de la routine mo_def_qsw
!                                      suppression du parametre eps100 (non utilise)
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!
!************************************************************************


! Modules
! =======
use int_mslib_mo_def_qsw

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mo_geo_qsw.h'

! Autres declarations
! -------------------

real(pm_reel), dimension(3) :: q, s, w                        ! directions du repere orbital local
type(tm_code_retour)        :: code_retour_local

intrinsic dot_product

character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mo_geo_qsw.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mo_geo_qsw.f90,v 1.7 2003/10/14 12:47:29 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
code_retour%valeur = pm_OK

call mo_def_qsw ( pos_car, vit_car, q, s, w, code_retour_local)
if (code_retour_local%valeur < 0) then
   code_retour%valeur = code_retour_local%valeur
   go to 6000
else
   code_retour%valeur = code_retour_local%valeur
end if

! calcul des composantes du vecteur dans (q,s,w)
! ----------------------------------------------

vect_qsw(1) = dot_product(vect_geo, q)! composante selon l'axe q
vect_qsw(2) = dot_product(vect_geo, s)! composante selon l'axe s
vect_qsw(3) = dot_product(vect_geo, w)! composante selon l'axe w

6000 continue

code_retour%routine = pm_num_mo_geo_qsw
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mo_geo_qsw
