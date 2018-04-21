
module code_modeles_mslib

! (C) Copyright CNES - MSLIB - 1998-2003

!************************************************************************
!
! But:  Definition des indicateurs de modeles utilises dans les routines de la MSLIB. 
! ===
!
! Note d'utilisation:  toute routine ou module utilisant parametre_mslib connait implicitement ce module.
! ==================
!
! Historique:
! ==========
!   + Version  1.0 (SP 284 ed01 rev00):creation
!   + Version 2.0  (DE 362 ed01 rev00): modification des valeurs numeriques des clefs
!   + Version 5.0  (DE 603 ed01 rev00): ajout des modeles UAI
!
!************************************************************************

use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

implicit none

! Valeurs associees aux indicateurs de modeles:
! ============================================

! modeles de precession et nutation

integer, parameter :: pm_lieske_wahr = 17  ! modele en nutation et precession Wahr+Lieske 
integer, parameter :: pm_lieske      = 18  ! indicateur du modele de precession de Lieske
integer, parameter :: pm_wahr        = 19  ! indicateur du modele de nutation de Wahr

! modeles decrivant les axes de rotation des astres

integer, parameter :: pm_nb_modelesUAI = 2
integer, parameter :: pm_UAI_modeles_min = 20
integer, parameter :: pm_UAI_autre_modele = pm_UAI_modeles_min
integer, parameter :: pm_UAI1994 = pm_UAI_autre_modele + 1
integer, parameter :: pm_UAI2000 = pm_UAI1994 + 1
integer, parameter :: pm_UAI_modeles_max = pm_UAI2000

!................................................................................................................

  character(len=pm_longueur_info_utilisateur),private :: info_utilisateur = &
                    '@(#) Fichier MSLIB code_modeles_mslib.f90: derniere modification V5.0 >'

!................................................................................................................

  character(len=pm_longueur_rcs_id), private :: rcs_id =' $Id: code_modeles_mslib.f90,v 1.9 2003/12/15 17:34:17 mslibdev Exp $ '

end module code_modeles_mslib

