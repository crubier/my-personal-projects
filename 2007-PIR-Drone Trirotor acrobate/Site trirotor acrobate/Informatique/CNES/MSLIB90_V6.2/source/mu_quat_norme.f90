subroutine mu_quat_norme (quat, quat_norme, norme, code_retour)

  ! (C) Copyright CNES - MSLIB - 2000

  !************************************************************************
  !
  ! But:  Normalisation d'un QUATernion apres calcul de sa NORME  
  ! ===
  !
  ! Note d'utilisation: Sans objet
  ! ==================
  !
  ! Historique:
  ! ==========
  !   + Version 3.0 (SP 424 ed01 rev00): creation a partir de la routine MUQNORME de la MSLIB f77
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

  include 'arg_mu_quat_norme.h'

  ! Autres declarations
  ! ===================

  real(pm_reel), dimension(4)  :: vect_quat    ! affectation a un vecteur du quaternion en entree pour 
                                               ! utilisation dans dot_product
  real(pm_reel)                :: presque_zero ! plus petit nombre machine
  real(pm_reel)                :: norme_locale ! affectation intermediaire de la norme

  intrinsic tiny, sqrt, dot_product

  character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
       '@(#) Fichier MSLIB mu_quat_norme.f90: derniere modification V3.1 >'

  ! Ne pas toucher a la ligne suivante
  character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mu_quat_norme.f90,v 1.4 2003/04/04 14:57:38 mslibatv Exp $ '

  !************************************************************************

  ! initialisations
  ! ===============

  ! initialisation de la valeur du code retour

  code_retour%valeur = pm_OK

  ! Autres initialisations:

  ! vecteur intermediaire
  vect_quat(1)  = quat%q0
  vect_quat(2:4)= quat%q123(:)

  presque_zero = tiny(1._pm_reel)         ! plus petit reel machine

  norme_locale = sqrt(dot_product(vect_quat, vect_quat))  !calcul de la norme du quaternion

  !test du cas ou la norme est nulle

  if (norme_locale <= presque_zero) then
     code_retour%valeur = pm_err_quat_nul
     go to 6000
  end if

  !calcul du quaternion norme

  quat_norme%q0      = quat%q0/norme_locale
  quat_norme%q123(:) = quat%q123(:)/norme_locale

  ! affectation de la norme
  norme = norme_locale


6000 continue

  code_retour%routine = pm_num_mu_quat_norme
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mu_quat_norme
