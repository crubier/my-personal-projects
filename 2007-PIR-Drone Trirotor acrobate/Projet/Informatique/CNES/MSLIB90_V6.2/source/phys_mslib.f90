module phys_mslib

! (C) Copyright CNES - MSLIB - 1998-2003

!************************************************************************
!
! But:  Definition des donnees et constantes physiques. 
! ===
!
! Note d'utilisation:
! ==================
!                     [DR1] "Les systemes de reference utilises en astronomie"
!                            de M. Chapront-Touze, G. Francou et B. Morando
!                            Bureau Des Longitudes (BDL) novembre 1994
!                            ISSN 1243-4272
!                            ISBN 2-910015-05-X
!                            nomenclature MSLIB M-NT-0-160-CN
!                     [DR2} "Report of the IAU/IAG working group on cartographic
!                            coordinates and rotational elements of the planets 
!                            and satellites: 2000"
!                            par P.K. Seidelmann et al.
!
! Historique:
! ==========
!   + Version 1.0  (SP 213 ed01 rev00): creation
!   + Version 2.0  (DE 401 ed01 rev00): ajout de la definition des parameters pm_i_critique_non_retro et pm_i_critique_retro
!   + Version 5.0 (DE 613 ed01 rev00): ajout des caracteristiques physiques des planetes (UAI) et de l'obliquite
!
!************************************************************************

use precision_mslib           ! definition des precisions retenues
use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

implicit none


! Constantes diverses

real(pm_reel),parameter :: pm_ua       = 1.495987e8_pm_reel   ! unite astronomique (km)

real(pm_reel),parameter :: pm_vit_lum  = 2.99792458e8_pm_reel ! vitesse de la lumiere (m/s)

! Inclinaisons critiques, solution de 1 - 5*cos(i))*cos(i) = 0

real(pm_reel),parameter :: pm_i_critique_non_retro = 1.1071487177940905030170654601785370400700476454014_pm_reel ! i critique non retrograde (rad)

real(pm_reel),parameter :: pm_i_critique_retro     = 2.0344439357957027354455779231009658441271217539737_pm_reel ! i critique retrograde (rad)



! Valeur de l'obliquite du pole moyen de la Terre a l'epoque J2000
! cf reference [DR1] p91 (IERS 1992):  23 deg, 26 min, 21.4119 secondes

real(pm_reel), parameter :: pm_obliquite2000 = 0.40909262920459006_pm_reel


! Rayon equatorial (m) et aplatissement pour les planetes du systeme solaire
! cf reference [DR2] table IV
! --------------------------------------------------------------------------

! mercure
real(pm_reel), parameter :: pm_mercure_r_equa_UAI   = 2439.7e3_pm_reel
real(pm_reel), parameter :: pm_mercure_apla_UAI     = 0._pm_reel

! venus
real(pm_reel), parameter :: pm_venus_r_equa_UAI   = 6051.8e3_pm_reel
real(pm_reel), parameter :: pm_venus_apla_UAI     = 0._pm_reel

! Terre
real(pm_reel), parameter :: pm_terre_r_equa_UAI   = 6378.14e3_pm_reel
real(pm_reel), parameter :: pm_terre_apla_UAI     = (pm_terre_r_equa_UAI-6356.75e3_pm_reel)/pm_terre_r_equa_UAI

! mars
real(pm_reel), parameter :: pm_mars_r_equa_UAI   = 3396.19e3_pm_reel
real(pm_reel), parameter :: pm_mars_apla_UAI     = (pm_mars_r_equa_UAI-3376.20e3_pm_reel)/pm_mars_r_equa_UAI ! moyen

! jupiter
real(pm_reel), parameter :: pm_jupiter_r_equa_UAI   = 71492.e3_pm_reel
real(pm_reel), parameter :: pm_jupiter_apla_UAI     = (pm_jupiter_r_equa_UAI-66854.e3_pm_reel)/pm_jupiter_r_equa_UAI

! saturne
real(pm_reel), parameter :: pm_saturne_r_equa_UAI   = 60268.e3_pm_reel
real(pm_reel), parameter :: pm_saturne_apla_UAI     = (pm_saturne_r_equa_UAI-54364.e3_pm_reel)/pm_saturne_r_equa_UAI

! uranus
real(pm_reel), parameter :: pm_uranus_r_equa_UAI   = 25559.e3_pm_reel
real(pm_reel), parameter :: pm_uranus_apla_UAI     = (pm_uranus_r_equa_UAI-24973.e3_pm_reel)/pm_uranus_r_equa_UAI

! neptune
real(pm_reel), parameter :: pm_neptune_r_equa_UAI   = 24764.e3_pm_reel
real(pm_reel), parameter :: pm_neptune_apla_UAI     = (pm_neptune_r_equa_UAI-24341.e3_pm_reel)/pm_neptune_r_equa_UAI

! pluton
real(pm_reel), parameter :: pm_pluton_r_equa_UAI   = 1195.e3_pm_reel
real(pm_reel), parameter :: pm_pluton_apla_UAI     = 0._pm_reel


!................................................................................................................

character(len=pm_longueur_info_utilisateur),private :: info_utilisateur = &
                  '@(#) Fichier MSLIB phys_mslib.f90: derniere modification V5.0 >'

!................................................................................................................

character(len=pm_longueur_rcs_id), private :: rcs_id =' $Id: phys_mslib.f90,v 1.10 2003/12/15 17:35:03 mslibdev Exp $ '

end module phys_mslib
