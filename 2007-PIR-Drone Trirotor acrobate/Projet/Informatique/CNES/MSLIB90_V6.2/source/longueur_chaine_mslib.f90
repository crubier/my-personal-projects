
module longueur_chaine_mslib

! (C) Copyright CNES - MSLIB - 1997-2003

!************************************************************************
!
! But:  Definition des longueurs de chaines de caracteres. 
! ===
!
! Note d'utilisation:  toute routine ou module utilisant parametre_mslib connait implicitement ce module.
! ==================
!
! Historique:
! ==========
!   + Version 0.1 (SP 173 ed01 rev00): creation
!   + Version 0.1.1 (DE globale 182 ed01 rev00): modification regle de marquage pour info_utilisateur
!   + Version 3.1 (DE 441 ed01 rev00): ajout de la longueur pm_message
!   + Version 5.0 (DE 616 ed01 rev00): revision de la longueur pm_nom_routine
!
!************************************************************************

  implicit none

  ! Connu de l'utilisateur
  integer, parameter, public :: pm_nom_routine = 21                ! nom de routine
  integer, parameter, public :: pm_identification_routine = 500    ! identification de routine
  integer, parameter, public :: pm_signification_code_retour = 550 ! signification valeur code retour
  integer, parameter, public :: pm_message = 512                   ! champ message (code retour)


  ! interne projet (mais utilise partout)
  integer, parameter, public :: pm_longueur_info_utilisateur = 100 ! pour le marquage par what
  integer, parameter, public :: pm_longueur_rcs_id = 100           ! pour le marquage par RCS


!................................................................................................................

  character(len=pm_longueur_info_utilisateur),private :: info_utilisateur = &
                    '@(#) Fichier MSLIB longueur_chaine_mslib.f90: derniere modification V5.0 >'

!................................................................................................................

  character(len=pm_longueur_rcs_id), private :: rcs_id =' $Id: longueur_chaine_mslib.f90,v 1.6 2003/12/15 17:34:33 mslibdev Exp $ '

end module longueur_chaine_mslib
