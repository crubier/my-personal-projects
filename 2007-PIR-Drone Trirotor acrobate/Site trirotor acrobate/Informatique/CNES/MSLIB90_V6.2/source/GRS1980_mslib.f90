
module GRS1980_mslib

! (C) Copyright CNES - MSLIB - 1998

!************************************************************************
!
! But:  Definition des constantes geodesiques du modele GRS1980. 
! ===
!
! Note d'utilisation:
! ==================
!
! Historique:
! ==========
!   
!   + Version 1.0 (SP 214 ed01 rev00) : creation pour l'acces par la routine mc_GRS1980
!************************************************************************

  use precision_mslib           ! definition des precisions retenues
  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres


  implicit none

real(pm_reel), parameter :: pm_r_equa_GRS1980   = 6.378137e6_pm_reel                    ! rayon equatorial de la terre (m)
real(pm_reel), parameter :: pm_inv_apla_GRS1980 = 2.98257222101e2_pm_reel               ! inverse de l'aplatissement de la terre
real(pm_reel), parameter :: pm_apla_GRS1980     = 1._pm_reel/pm_inv_apla_GRS1980       ! aplatissement de la terre

!................................................................................................................

  character(len=pm_longueur_info_utilisateur),private :: info_utilisateur = &
                    '@(#) Fichier MSLIB GRS1980_mslib.f90: derniere modification V1.0 >'

!................................................................................................................

  character(len=pm_longueur_rcs_id), private :: rcs_id =' $Id: GRS1980_mslib.f90,v 1.4 2003/04/04 14:53:31 mslibatv Exp $ '

end module GRS1980_mslib
