module code_anomalies_mslib

! (C) Copyright CNES - MSLIB - 2004

!************************************************************************
!
! But:  Definition des types d'anomalies (v, M, E/H/D)
! ===
!
! Note d'utilisation:  toute routine ou module utilisant parametre_mslib 
! ==================   connait implicitement ce module.
! 
! Historique:
! ==========
!   + Version 6.2 : creation
!
!************************************************************************

use longueur_chaine_mslib  ! definition des longueurs de chaines de caracteres

implicit none

! Valeurs associees aux types d'anomalies:
! =======================================

integer, parameter :: pm_anom_E = 11 ! anomalie excentrique : E pour l'ellipse, 
                                     ! H pour l'hyperbole et D pour la parabole
integer, parameter :: pm_anom_v = 12 ! anomalie vraie
integer, parameter :: pm_anom_M = 13 ! anomalie moyenne


character(len=pm_longueur_info_utilisateur),private :: info_utilisateur = &
         '@(#) Fichier MSLIB code_anomalies_mslib.f90: derniere modification V6.2 >'
!................................................................................................................

character(len=pm_longueur_rcs_id), private :: rcs_id =' $Id: code_anomalies_mslib.f90,v 1.4 2005/02/28 07:49:51 mslibdev Exp $ '

end module code_anomalies_mslib
