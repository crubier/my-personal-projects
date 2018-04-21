module code_planetes_mslib

! (C) Copyright CNES - MSLIB - 2003

!************************************************************************
!
! But:  Definition des codes des planetes NASA - NAIF/SPICE
! ===  
!
!
! Note d'utilisation: 
! ==================  
!
! Historique:
! ==========
!   + Version 5.0 (SP 601 ed01 rev00): creation
!                         (Date: 12/2003 - Bruno Revelin)
!
!************************************************************************

use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres
use precision_mslib

implicit none

! Parametres representant les planetes (nomenclature NASA - NAIF/SPICE)
! =====================================================================

integer, parameter :: pm_pla_mercure = 199
integer, parameter :: pm_pla_venus   = 299
integer, parameter :: pm_pla_terre   = 399
integer, parameter :: pm_pla_mars    = 499
integer, parameter :: pm_pla_jupiter = 599
integer, parameter :: pm_pla_saturne = 699
integer, parameter :: pm_pla_uranus  = 799
integer, parameter :: pm_pla_neptune = 899
integer, parameter :: pm_pla_pluton  = 999




!................................................................................................................

  character(len=pm_longueur_info_utilisateur),private :: info_utilisateur = &
                    '@(#) Fichier MSLIB code_planetes_mslib.f90: derniere modification V5.0 >'

!................................................................................................................

  character(len=pm_longueur_rcs_id), private :: rcs_id =' $Id: code_planetes_mslib.f90,v 1.2 2003/12/15 17:37:22 mslibdev Exp $ '

end module code_planetes_mslib
