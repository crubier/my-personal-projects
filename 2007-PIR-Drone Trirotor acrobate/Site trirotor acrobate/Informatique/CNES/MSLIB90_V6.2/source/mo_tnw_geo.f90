subroutine mo_tnw_geo (pos_car, vit_car, vect_tnw, vect_geo, code_retour)

! (C) Copyright CNES - MSLIB - 1998

!************************************************************************
!
! But:  Passage dans le repere geocentrique inertiel d'un vecteur exprime dans le repere orbital local (t,n,w)
! ===
!
! Note d'utilisation: La transformation inverse peut s'effectuer par la routine mo_geo_tnw
! ==================  
!
! Historique:
! ==========
!   + Version 1.0 (SP 221 ed01 rev00): creation a partir de la routine MVVI0R de la MSLIB f77
!   + Version 2.0 (DE 371 ed01 rev00): utilisation de la routine mo_def_tnw
!                                      suppression du parametre eps100 (non utilise)
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!
!************************************************************************


! Modules
! =======
use int_mslib_mo_def_tnw

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mo_tnw_geo.h'

! Autres declarations
! -------------------
real(pm_reel), dimension(3) :: t, n, w                        ! directions du repere (t, n, w)
type(tm_code_retour)        :: code_retour_local

character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mo_tnw_geo.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mo_tnw_geo.f90,v 1.7 2003/10/14 12:47:44 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
code_retour%valeur = pm_OK

call mo_def_tnw ( pos_car, vit_car, t, n, w, code_retour_local)
if (code_retour_local%valeur < 0) then
   code_retour%valeur = code_retour_local%valeur
   go to 6000
else
   code_retour%valeur = code_retour_local%valeur
end if


! calcul des composantes du vecteur dans le repere geocentrique
! =============================================================
!

      vect_geo (:) = vect_tnw(1)*t(:) + vect_tnw(2)*n(:) + vect_tnw(3)*w(:)

6000 continue

code_retour%routine = pm_num_mo_tnw_geo
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mo_tnw_geo
