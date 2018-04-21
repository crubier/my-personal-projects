subroutine mvi_conv_anom_ellip (e, type_anom1, anom1, type_anom2, anom2, retour)

! (C) Copyright CNES - MSLIB - 2004

!************************************************************************
!
! But:  Conversion d'anomalies dans le cas elliptique
! ===
!
! Note d'utilisation:  l'appelant doit avoir teste si e est dans [0, 1[
! ==================   Aucun test n'est effectue ici.
!
! Historique:
! ==========
!   + Version 6.2 : creation 
!
!************************************************************************

! Modules
! =======
use int_mslib_mv_kepler_std

use code_anomalies_mslib
use math_mslib

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mvi_conv_anom_ellip.h'

! Autres declarations
! -------------------

real(pm_reel) :: e_fois_beta, anom_E, anom_v, tan_vmEs2, tan_Emvs2 ! variables intermediaires de calcul
type(tm_code_retour) :: code_retour_local   ! code retour des routines appelees

intrinsic sqrt, sin, cos, atan


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
     '@(#) Fichier MSLIB mvi_conv_anom_ellip.f90: derniere modification V6.2 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mvi_conv_anom_ellip.f90,v 1.4 2005/02/28 07:51:31 mslibdev Exp $ '

!************************************************************************

! initialisation
! ..............
retour = pm_OK

! beta = fonction de e = 1 / 1 + sqrt(1 - e*e)
e_fois_beta = e/(1._pm_reel + sqrt(1._pm_reel - e*e))


! calculs selon les types d'anomalies
! ...................................

select case (type_anom1)

case (pm_anom_E) ! conversion d'une anomalie excentrique E

   select case (type_anom2)

   case (pm_anom_M)
      anom2 = anom1 - e*sin(anom1) ! equation de Kepler ...

   case(pm_anom_v)
      tan_vmEs2 = e_fois_beta*sin(anom1)/(1._pm_reel - e_fois_beta*cos(anom1))
      anom_v = 2._pm_reel*atan(tan_vmEs2) + anom1
      anom2 = modulo(anom_v,pm_deux_pi) ! resultat dans [0, 2pi]

   case default ! type_anom2 incorrect
      retour = pm_err_type_anom

   end select

case (pm_anom_v) ! conversion d'une anomalie vraie

   ! calcul de E (valable pour les 2 conversions)
   tan_Emvs2 = - e_fois_beta*sin(anom1)/(1._pm_reel + e_fois_beta*cos(anom1))
   anom_E = 2._pm_reel*atan(tan_Emvs2) + anom1

   select case (type_anom2)

   case (pm_anom_M)
      anom2 = anom_E - e*sin(anom_E) ! equation de Kepler ...

   case(pm_anom_E)
      anom2 = anom_E

   case default ! type_anom2 incorrect
      retour = pm_err_type_anom

   end select

case (pm_anom_M) ! conversion d'une anomalie moyenne

   ! calcul de E (valable pour les 2 conversions)
   call mv_kepler_std(anom1, e, anom_E, code_retour_local)
   if (code_retour_local%valeur /= pm_OK) then
      retour = code_retour_local%valeur
      if (retour /= pm_OK) go to 6000
   end if

   select case (type_anom2)

   case (pm_anom_v)
      tan_vmEs2 = e_fois_beta*sin(anom_E)/(1._pm_reel - e_fois_beta*cos(anom_E))
      anom_v = 2._pm_reel*atan(tan_vmEs2) + anom_E
      anom2 = modulo(anom_v,pm_deux_pi) ! resultat dans [0, 2pi]

   case(pm_anom_E)
      anom2 = anom_E

   case default ! type_anom2 incorrect
      retour = pm_err_type_anom

   end select

case default ! type_anom1 incorrect

   retour = pm_err_type_anom

end select

6000 continue


end subroutine mvi_conv_anom_ellip
