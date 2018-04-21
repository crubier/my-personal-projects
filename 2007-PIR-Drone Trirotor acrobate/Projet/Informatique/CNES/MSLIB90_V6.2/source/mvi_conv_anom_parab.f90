subroutine mvi_conv_anom_parab (e, type_anom1, anom1, type_anom2, anom2, retour)

! (C) Copyright CNES - MSLIB - 2005

!************************************************************************
!
! But:  Conversion d'anomalies dans le cas parabolique
! ===
!
! Note d'utilisation:  
! ==================
!
! Historique:
! ==========
!   + Version 6.2 : creation 
!************************************************************************

! Modules
! =======
use int_mslib_mvi_barker

use code_anomalies_mslib

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mvi_conv_anom_parab.h'

! Autres declarations
! -------------------

real(pm_reel) :: anom_D ! variables intermediaires de calcul

intrinsic atan, tan


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
     '@(#) Fichier MSLIB mvi_conv_anom_parab.f90: derniere modification V6.2 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mvi_conv_anom_parab.f90,v 1.6 2005/02/28 07:51:46 mslibdev Exp $ '

!************************************************************************

! initialisation
! ..............
retour = pm_OK

! calculs selon les types d'anomalies
! ...................................

select case (type_anom1)

case (pm_anom_E)  ! conversion d'une anomalie "excentrique" D = tan(v/2)

   select case (type_anom2)

   case (pm_anom_M)
      anom2 = anom1*(0.5_pm_reel + anom1*anom1/6._pm_reel)

   case(pm_anom_v)
      anom2 = 2._pm_reel*atan(anom1) ! resultat dans ]-pi, +pi[

   case default ! type_anom2 incorrect
      retour = pm_err_type_anom

   end select

case (pm_anom_v)  ! conversion d'une anomalie vraie

   anom_D = tan(anom1/2._pm_reel)

   select case (type_anom2)

   case (pm_anom_M)
      anom2 = anom_D*(0.5_pm_reel + anom_D*anom_D/6._pm_reel)

   case(pm_anom_E)
      anom2 = anom_D

   case default ! type_anom2 incorrect
      retour = pm_err_type_anom

   end select

case (pm_anom_M)  ! conversion d'une anomalie moyenne

   call mvi_barker (anom1, anom_D, retour)
   if (retour /= pm_OK) go to 6000

   select case (type_anom2)

   case (pm_anom_v)
      anom2 = 2._pm_reel*atan(anom_D) ! resultat dans ]-pi, +pi[

   case(pm_anom_E)
      anom2 = anom_D

   case default ! type_anom2 incorrect
      retour = pm_err_type_anom

   end select

case default ! type_anom1 incorrect

   retour = pm_err_type_anom

end select


6000 continue

end subroutine mvi_conv_anom_parab
