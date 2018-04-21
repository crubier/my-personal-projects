
module indic_comp_joursec_mslib

! (C) Copyright CNES - MSLIB - 1999-2002

!************************************************************************
!
! But:  Definition des indicateurs de comparaison des quantites, en jours et secondes, de la MSLIB. 
! ===
!
! Note d'utilisation:  toute routine ou module utilisant parametre_mslib connait implicitement ce module.
! ==================
!
! Historique:
! ==========
!   + Version  2.0 (SP 349 ed01 rev00):creation
!   + Version 4.0 (DE 454 ed01 rev00) : modif de la ligne rcs_id cause depassement de 132 caracteres
!
!************************************************************************

use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

implicit none

! Valeurs associees aux indicateurs de comparaison de 2 quantites jours, sec:
! ===========================================================================

! Convention adoptee : Q1 > Q2 -> pm_joursec1_sup_joursec2
!                      Q1 = Q2 -> pm_joursec1_egal_joursec2
!                      Q1 < Q2 -> pm_joursec1_inf_joursec2

integer, parameter :: pm_joursec1_sup_joursec2  =  7
integer, parameter :: pm_joursec1_egal_joursec2 =  8
integer, parameter :: pm_joursec1_inf_joursec2  =  9

!................................................................................................................

  character(len=pm_longueur_info_utilisateur),private :: info_utilisateur = &
                    '@(#) Fichier MSLIB indic_comp_joursec_mslib.f90: derniere modification V4.0 >'

!................................................................................................................

  character(len=pm_longueur_rcs_id), private :: rcs_id = &
           ' $Id: indic_comp_joursec_mslib.f90,v 1.8 2003/04/10 14:49:02 mslibdev Exp $ '

end module indic_comp_joursec_mslib
