
module mslib

! (C) Copyright CNES - MSLIB - 1997-2003

!************************************************************************
!
! But:  acces simplifie pour l'utilisateur a tous les modules necessaires. 
! ===   Definition de la chaine de caracteres "version_MSLIB_id" donnant
!       via le binaire (commande what) le numero de version de la librairie.
!
! Note d'utilisation: l'utilisateur n'a besoin que de faire: use mslib
! ==================  En interne il n'est pas possible d'utiliser ce module
!                     a cause du module interface (compilation impossible).
!
! Historique:
! ==========
!   + Version 0.1 (SP 148 ed01 rev00): creation
!   + Version 0.1.1 (DE globale 182 ed01 rev00): modification regle de marquage pour info_utilisateur
!   + Version 1.0 (DE 282 ed01 rev01): rajout de l'acces a des constantes mathematiques ou physiques
!   + Version 3.2 (DE 447 ed01 rev00): Changement de l'utilisation du parameter pm_version_MSLIB par pm_version_MSLIB90
!   + Version 4.0 (FA globale 478 ed01 rev00): Remplacement de l'anti-slash par le caractere >
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!************************************************************************


  use interface_mslib    ! Definition de toutes les interfaces des routines utilisateurs.
  use parametre_mslib    ! Definition de parametres MSLIB.
  use type_mslib         ! Definition de tous les types MSLIB.

  ! Fourniture de l'acces direct a certaines constantes (decrites dans le Volume 3 de la documentation)
  use math_mslib         ! Definition de constantes mathematiques
  use phys_mslib         ! Definition de constantes physiques
  use GRS1980_mslib      ! Definition de constantes du modele GRS1980

  implicit none

  ! numero de version MSLIB pour le binaire (avec commande what)
  character(len=300),private  :: version_MSLIB_id = '@(#) '//pm_version_MSLIB90//'>'


!................................................................................................................

  character(len=pm_longueur_info_utilisateur),private :: info_utilisateur = &
                    '@(#) Fichier MSLIB mslib.f90: derniere modification V4.1 >'

!................................................................................................................

  character(len=pm_longueur_rcs_id), private :: rcs_id =' $Id: mslib.f90,v 1.8 2003/10/14 12:51:32 mslibdev Exp $ '

end module mslib
