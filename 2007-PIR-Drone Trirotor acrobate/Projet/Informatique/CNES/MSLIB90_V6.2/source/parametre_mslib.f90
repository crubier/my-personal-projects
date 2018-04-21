module parametre_mslib

! (C) Copyright CNES - MSLIB - 1998-2005

!************************************************************************
!
! But:  Definition des parametres MSLIB. 
! ===   En particulier la chaine de caracteres "pm_version_MSLIB90" donnant le numero
!       de version MSLIB.
!
! Note d'utilisation: Penser a chaque evolution de la librairie a changer: pm_version_MSLIB90.
! ==================  Ce module est accessible a l'utilisateur via le module mslib.
!
! Historique:
! ==========
!   + Version 0.1 (SP 172 ed01 rev00): creation
!   + Version 0.1.1 (DE globale 182 ed01 rev00): modification regle de marquage pour info_utilisateur
!   + Version 1.0 (DE 290 ed01 rev00) : ajout de nouveaux modules
!   + Version 2.0 (DE 340 ed01 rev00) : ajout de nouveaux modules
!   + Version 3.0 (sans DE)           : modification du numero de version
!   + Version 3.1 (sans DE) : modification du numero de version
!   + Version 3.2 (DE 448 ed01 rev00) : remplacement du parameter pm_version_MSLIB par pm_version_MSLIB90
!   + Version 4.0 (sans DE)           : modification du numero de version
!   + Version 4.1 (sans DE)           : modification du numero de version
!   + Version 5.0 (sans DE)           : modification du numero de version
!   + Version 5.0 (DE 602 ed01 rev00) : ajout de code_planetes_mslib
!   + Version 6.0 (sans DE)           : modification du numero de version
!   + Version 6.1 (sans DE)           : modification du numero de version
!   + Version 6.2 (sans DE)           : modification du numero de version
!   + Version 6.2 (DE 1)              : ajout du module code_anomalies_mslib
!************************************************************************

  use precision_mslib           ! definition des precisions retenues
  use valeur_code_retour_mslib  ! definition des valeurs des codes retour
  use numero_routine_mslib      ! definition des numeros des routines
  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres
  use code_transfo_mslib        ! definition des indicateurs de passage d'un repere a un autre
  use code_modeles_mslib        ! definition des modeles de la MSLIB
  use indic_reperes_mslib       ! definition des indicateurs des reperes de la MSLIB
  use indic_comp_joursec_mslib  ! definition des indicateurs de comparaison de jour
  use code_planetes_mslib       ! definition des clefs definissant les planetes
  use code_anomalies_mslib      ! definition des clefs definissant les types d'anomalies


  implicit none


  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  ! Numero courant de version MSLIB Fortran 90
  character(len=*),parameter :: pm_version_MSLIB90 =  'MSLIB Fortran 90 version 6.2'
  character(len=*),parameter :: pm_version_MSLIB =  pm_version_MSLIB90 ! pour assurer la compatibilite ascendante

  !................................................................................................................

  character(len=pm_longueur_info_utilisateur),private :: info_utilisateur = &
                    '@(#) Fichier MSLIB parametre_mslib.f90: derniere modification V6.2 >'

!................................................................................................................

  character(len=pm_longueur_rcs_id), private :: rcs_id =' $Id: parametre_mslib.f90,v 1.24 2005/02/28 07:52:06 mslibdev Exp $ '

end module parametre_mslib

