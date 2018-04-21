subroutine mu_quat_conjug (quat, quat_conjug, code_retour)

  ! (C) Copyright CNES - MSLIB - 2000

  !************************************************************************
  !
  ! But:  Calcul du QUATernion CONJUGue d'un quaternion donne
  ! ===
  !
  ! Note d'utilisation: Sans objet 
  ! ==================
  !
  ! Historique:
  ! ==========
  !   + Version 3.0 (SP 425 ed01 rev00): creation a partir de la routine MUQCONJUG de la MSLIB f77
  !   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
  !
  !************************************************************************


  ! Modules
  ! =======

  use precision_mslib
  use type_mslib
  use valeur_code_retour_mslib
  use numero_routine_mslib
  use longueur_chaine_mslib


  ! Declarations
  ! ============
  implicit none

  include 'arg_mu_quat_conjug.h'

  ! Autres declarations
  ! ===================

  character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
       '@(#) Fichier MSLIB mu_quat_conjug.f90: derniere modification V3.1 >'

  ! Ne pas toucher a la ligne suivante
  character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mu_quat_conjug.f90,v 1.4 2003/04/04 14:57:38 mslibatv Exp $ '

  !************************************************************************

  ! initialisations
  ! ===============

  ! initialisation de la valeur du code retour

  code_retour%valeur = pm_OK

  quat_conjug%q0      =  quat%q0
  quat_conjug%q123(:) = -quat%q123(:)

6000 continue

  code_retour%routine = pm_num_mu_quat_conjug
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mu_quat_conjug
