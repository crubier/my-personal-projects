
module precision_mslib

! (C) Copyright CNES - MSLIB - 1998

!************************************************************************
!
! But:  Definition des precisions MSLIB. 
! ===
!
! Note d'utilisation:  toute routine ou module utilisant parametre_mslib connait implicitement ce module.
! ==================
!
! Historique:
! ==========
!   + Version 0.1 (SP 178 ed01 rev00): creation
!   + Version 0.1.1 (DE globale 182 ed01 rev00): modification regle de marquage pour info_utilisateur
!
!************************************************************************

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none


  ! Precisions retenues
  ! ===================

  integer, parameter, public :: pm_reel = selected_real_kind(13)
  integer, parameter, public :: pm_entier = selected_int_kind(9)


!................................................................................................................

  character(len=pm_longueur_info_utilisateur),private :: info_utilisateur = &
                    '@(#) Fichier MSLIB precision_mslib.f90: derniere modification V0.1.1 >'

!................................................................................................................

  character(len=pm_longueur_rcs_id), private :: rcs_id =' $Id: precision_mslib.f90,v 1.4 2003/04/04 14:57:42 mslibatv Exp $ '

end module precision_mslib

