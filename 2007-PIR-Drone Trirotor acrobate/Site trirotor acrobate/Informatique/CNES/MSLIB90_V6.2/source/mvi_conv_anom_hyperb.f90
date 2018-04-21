subroutine mvi_conv_anom_hyperb (e, type_anom1, anom1, type_anom2, anom2, retour)

! (C) Copyright CNES - MSLIB - 2005

!************************************************************************
!
! But:  Conversion d'anomalies dans le cas hyperbolique
! ===
!
! Note d'utilisation:  l'appelant doit avoir teste que e > 1 (strictement)
! ==================   Aucun test n'est effectue ici.
!
! Historique:
! ==========
!   + Version 6.2 : creation
!
!************************************************************************


! Modules
! =======
use int_mslib_mvi_kepler_hyperb

use code_anomalies_mslib

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mvi_conv_anom_hyperb.h'

! Autres declarations: variables intermediaires
! -------------------

real(pm_reel) :: moins_un_sur_e, tan_vs2, anom_H ! variables intermediaires
real(pm_reel) :: tanh_Hs2, rapport_tanh_Hs2, pseudo_beta ! variables intermediaires

intrinsic tanh, sinh, sqrt, cos, tan, atan, log


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
     '@(#) Fichier MSLIB mvi_conv_anom_hyperb.f90: derniere modification V6.2 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mvi_conv_anom_hyperb.f90,v 1.7 2005/02/28 07:51:41 mslibdev Exp $ '

!************************************************************************

! initialisation
! ..............
retour = pm_OK


! avec e > 1
pseudo_beta = sqrt((e + 1._pm_reel)/(e - 1._pm_reel))


! calculs selon les types d'anomalies
! ...................................

select case (type_anom1)

case (pm_anom_E)  ! conversion d'une anomalie excentrique H

   select case (type_anom2)

   case (pm_anom_M)
      anom2 = e*sinh(anom1) - anom1 ! equation de Kepler pour l'hyperbole

   case(pm_anom_v)
      tan_vs2 = pseudo_beta*tanh(anom1/2._pm_reel)
      anom2 = 2._pm_reel*atan(tan_vs2) ! resultat dans ]-pi, +pi[

   case default ! type_anom2 incorrect
      retour = pm_err_type_anom

   end select


case (pm_anom_v)  ! conversion d'une anomalie vraie

   ! test de compatibilite de v avec l'excentricite e
   ! il faut que : cos(v) > ou = -1/e avec e > 1
   moins_un_sur_e = - 1._pm_reel/e

   if (cos(anom1) < moins_un_sur_e) then ! attention pas de valeur absolue
      retour = pm_err_anom_v_incompatible_e
      go to 6000
   end if

   ! avec e > 1 et cos(v) > -1/e ==> tan(v/2) n'est pas infini
   tanh_Hs2 = tan(anom1/2._pm_reel) / pseudo_beta
   rapport_tanh_Hs2 = (1._pm_reel + tanh_Hs2) / (1._pm_reel - tanh_Hs2)
   anom_H = log(rapport_tanh_Hs2)

   select case (type_anom2)

   case (pm_anom_M)
      anom2 = e*sinh(anom_H) - anom_H ! equation de Kepler pour l'hyperbole

   case(pm_anom_E)
      anom2 = anom_H     

   case default ! type_anom2 incorrect
      retour = pm_err_type_anom

   end select

case (pm_anom_M)  ! conversion d'une anomalie moyenne

   call mvi_kepler_hyperb (anom1, e, anom_H, retour)
   if (retour /= pm_OK) go to 6000

   select case (type_anom2)

   case (pm_anom_v)
      tan_vs2 = pseudo_beta*tanh(anom_H/2._pm_reel)
      anom2 = 2._pm_reel* atan(tan_vs2) ! resultat dans ]-pi, +pi[

   case(pm_anom_E)
      anom2 = anom_H

   case default ! type_anom2 incorrect
      retour = pm_err_type_anom

   end select

case default ! type_anom1 incorrect

   retour = pm_err_type_anom

end select


6000 continue


end subroutine mvi_conv_anom_hyperb
