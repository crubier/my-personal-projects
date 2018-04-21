
module indic_reperes_mslib

! (C) Copyright CNES - MSLIB - 1999

!************************************************************************
!
! But:  Definition des indicateurs de repere de calcul de la MSLIB. 
! ===
!
! Note d'utilisation:  toute routine ou module utilisant parametre_mslib connait implicitement ce module.
! ==================
!
! Historique:
! ==========
!   + Version  2.0 (SP 339 ed01 rev00):creation
!
!************************************************************************

use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

implicit none

! Valeurs associees aux indicateurs de repere:
! ============================================

! Convention adoptee : repere geocentrique inertiel -> pm_rep_geo
!                      repere qsw                   -> pm_rep_qsw
!                      repere tnw                   -> pm_rep_tnw

integer, parameter :: pm_rep_geo = 1001
integer, parameter :: pm_rep_qsw = 2002
integer, parameter :: pm_rep_tnw = 2003

!................................................................................................................

  character(len=pm_longueur_info_utilisateur),private :: info_utilisateur = &
                    '@(#) Fichier MSLIB indic_reperes_mslib.f90: derniere modification V2.0 >'

!................................................................................................................

  character(len=pm_longueur_rcs_id), private :: rcs_id =' $Id: indic_reperes_mslib.f90,v 1.4 2003/04/04 14:53:40 mslibatv Exp $ '

end module indic_reperes_mslib
