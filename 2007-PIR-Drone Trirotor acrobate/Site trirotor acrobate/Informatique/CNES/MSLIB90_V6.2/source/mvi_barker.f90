subroutine mvi_barker (anom_M, D, retour)

! (C) Copyright CNES - MSLIB - 1998-2003

!************************************************************************
!
! But:  Resolution de l'equation de BARKER
! ===
!
! Note d'utilisation:  routine interne
! ==================
!
! Historique:
! ==========
!   + Version 1.0 (SP 225 ed01 rev00): creation a partir du code traitant le cas parabolique dans la routine MVRYKN de la MSLIB f77
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!************************************************************************


! Modules
! =======

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mvi_barker.h'

! Autres declarations
! -------------------

real(pm_reel) :: aux,bux,delta,uns3,anom_M3               ! variables intermediaires

intrinsic sqrt, sign, abs


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mvi_barker.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mvi_barker.f90,v 1.8 2003/10/14 12:54:53 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
retour = pm_OK

anom_M3 = 3._pm_reel * anom_M
delta = sqrt(1._pm_reel+anom_M3*anom_M3)
aux = anom_M3 + delta
bux = anom_M3 - delta
uns3 = 1._pm_reel / 3._pm_reel
D = sign(1._pm_reel,aux)*abs(aux)**uns3+sign(1._pm_reel,bux)*abs(bux)**uns3

6000 continue

end subroutine mvi_barker
