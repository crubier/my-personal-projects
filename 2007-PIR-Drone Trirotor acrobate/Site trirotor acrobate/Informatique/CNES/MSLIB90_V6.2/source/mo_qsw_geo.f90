subroutine mo_qsw_geo (pos_car, vit_car, vect_qsw, vect_geo, code_retour)

! (C) Copyright CNES - MSLIB - 1998

!************************************************************************
!
! But:  Passage dans le repere geocentrique inertiel d'un vecteur exprime dams le 
! ===   repere orbital local (q,s,w).
!
! Note d'utilisation: La transformation inverse peut se faire par mo_geo_qsw
! ==================   
!
! Historique:
! ==========
!   + Version 1.0 (SP 219 ed01 rev00): creation a partir de la routine MVRA0R de la MSLIB f77
!   + Version 2.0 (DE 370 ed01 rev00): utilisation de la routine mo_def_qsw
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

include 'arg_mo_qsw_geo.h'

! Autres declarations
! -------------------

real(pm_reel), dimension(3) :: q, s, w                        ! directions du repere orbital local
type(tm_code_retour)        :: code_retour_local

character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mo_qsw_geo.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mo_qsw_geo.f90,v 1.7 2003/10/14 12:47:39 mslibdev Exp $ '

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

! calcul des composantes du vecteur dans le repere geocentrique inertiel

vect_geo(:) = vect_qsw(1)*q(:) + vect_qsw(2)*s(:) + vect_qsw(3)*w(:)

6000 continue

code_retour%routine = pm_num_mo_qsw_geo
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mo_qsw_geo
