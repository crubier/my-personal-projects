subroutine mv_conv_anom (e, type_anom1, anom1, type_anom2, anom2, code_retour)

! (C) Copyright CNES - MSLIB - 2004

!************************************************************************
!
! But:  Conversion d'anomalies excentrique, moyenne et vraie 
! ===   dans les cas elliptique, hyperbolique, et parabolique
!
! Note d'utilisation:  On utilise le terme d'anomalie excentrique E 
! ==================   pour le cas hyperbolique (H) et parabolique (D = tan(v/2))
!
!                      La conversion anomalie moyenne --> anomalie excentrique
!                      peut aussi se faire par mv_kepler_bar pour les 3 types de coniques.
! Historique:
! ==========
!   + Version 6.2 : creation 
!
!************************************************************************

! Modules
! =======
use int_mslib_mvi_conv_anom_ellip
use int_mslib_mvi_conv_anom_hyperb
use int_mslib_mvi_conv_anom_parab

use code_anomalies_mslib
use test_mslib

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mv_conv_anom.h'

! Autres declarations
! ===================
integer    ::  retour


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
     '@(#) Fichier MSLIB mv_conv_anom.f90: derniere modification V6.2 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mv_conv_anom.f90,v 1.5 2005/02/28 07:51:26 mslibdev Exp $ '

!************************************************************************

! initialisations
! ===============
code_retour%valeur = pm_OK

! Verifications
! =============

if (type_anom1 == type_anom2) then ! conversion identite

   ! les 2 clefs sont identiques: il suffit de tester la validite d'une seule
   if (type_anom1 /= pm_anom_E .AND. type_anom1 /= pm_anom_M &
                               .AND. type_anom1 /= pm_anom_v) then
      code_retour%valeur = pm_err_type_anom
      go to 6000
   end if

   ! pas de conversion a effectuer
   code_retour%valeur = pm_warn_conv_identite
   anom2 = anom1
   go to 6000

end if


if (e < 0._pm_reel) then
   code_retour%valeur = pm_err_e_negatif
   go to 6000
end if

! calculs
! =======

if (e <= (1._pm_reel - pm_eps_parab)) then ! cas elliptique

   call mvi_conv_anom_ellip (e, type_anom1, anom1, type_anom2, anom2, retour)

else if (e >= (1._pm_reel + pm_eps_parab))  then ! cas hyperbolique

   call mvi_conv_anom_hyperb (e, type_anom1, anom1, type_anom2, anom2, retour)

else ! cas parabolique

   call mvi_conv_anom_parab (e, type_anom1, anom1, type_anom2, anom2, retour)

end if

! affectation du code retour
code_retour%valeur = retour

6000 continue

code_retour%routine = pm_num_mv_conv_anom
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mv_conv_anom



