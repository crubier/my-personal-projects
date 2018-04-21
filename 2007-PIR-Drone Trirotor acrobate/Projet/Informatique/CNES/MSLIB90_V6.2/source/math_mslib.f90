
module math_mslib

! (C) Copyright CNES - MSLIB - 1997

!************************************************************************
!
! But:  Definition des constantes mathematiques. 
! ===
!
! Note d'utilisation:
! ==================
!
! Historique:
! ==========
!   + Version 0.1 (SP 177 ed01 rev00): creation
!   + Version 0.1.1 (DE globale 182 ed01 rev00): modification regle de marquage pour info_utilisateur
!   + Version 1.0 (DE globale 217 ed01 rev00): modification des noms des constantes: ajout du prefixe pm_
!************************************************************************

  use precision_mslib           ! definition des precisions retenues
  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres


  implicit none

  real(pm_reel),parameter :: pm_pi      = 3.1415926535897932384626433832795028841972_pm_reel
  real(pm_reel),parameter :: pm_deux_pi = 6.2831853071795864769252867665590057683943_pm_reel
  real(pm_reel),parameter :: pm_pi_sur2 = 1.5707963267948966192313216916397514420986_pm_reel
  real(pm_reel),parameter :: pm_deg_rad = 0.017453292519943295769236907684886127134429_pm_reel
  real(pm_reel),parameter :: pm_rad_deg = 57.295779513082320876798154814105170332405_pm_reel


!................................................................................................................

  character(len=pm_longueur_info_utilisateur),private :: info_utilisateur = &
                    '@(#) Fichier MSLIB math_mslib.f90: derniere modification V1.0 >'

!................................................................................................................

  character(len=pm_longueur_rcs_id), private :: rcs_id =' $Id: math_mslib.f90,v 1.4 2003/04/04 14:53:47 mslibatv Exp $ '

end module math_mslib
