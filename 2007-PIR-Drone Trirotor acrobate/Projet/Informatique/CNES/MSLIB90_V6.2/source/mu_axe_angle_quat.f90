subroutine mu_axe_angle_quat (axe, angle, quat, code_retour)

  ! (C) Copyright CNES - MSLIB - 2000

  !************************************************************************
  !
  ! But: Conversion d'une rotation definie par son AXE et son ANGLE en QUATernion.
  ! ===
  !
  ! Note d'utilisation:  La transformation inverse peut etre effectuee par la routine mu_quat_axe_angle
  ! ==================
  !
  ! Historique:
  ! ==========
  !   + Version 3.0 (SP 421 ed01 rev00): creation a partir de la routine MUCVECQUA de la MSLIB f77
  !   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
  !
  !************************************************************************


  ! Modules
  ! =======
  use int_mslib_mu_norme

  use math_mslib


  use precision_mslib
  use type_mslib
  use valeur_code_retour_mslib
  use numero_routine_mslib
  use longueur_chaine_mslib


  ! Declarations
  ! ============
  implicit none

  include 'arg_mu_axe_angle_quat.h'

  ! Autres declarations
  ! ===================
  real(pm_reel), dimension(3)   :: axe_norme           ! vecteur axe norme
  real(pm_reel)                 :: anglemod, norme_axe ! angle modulo 2*pi, norme de l'axe

  intrinsic modulo, cos, sin


  character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
       '@(#) Fichier MSLIB mu_axe_angle_quat.f90: derniere modification V3.1 >'

  ! Ne pas toucher a la ligne suivante
  character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mu_axe_angle_quat.f90,v 1.4 2003/04/04 14:57:37 mslibatv Exp $ '

  !************************************************************************

  ! initialisations
  ! ===============

  ! initialisation de la valeur du code retour

  code_retour%valeur = pm_OK

  !
  call mu_norme(axe, norme_axe, code_retour, vect_norme = axe_norme) !calcul de la norme et normalisation du vecteur axe
  if (code_retour%valeur /= pm_OK) then
     if (code_retour%valeur == pm_err_vect_nul) then
        code_retour%valeur = pm_err_axe_rot_nul      ! affectation specifique du code retour dans le cas d'un axe nul
     else
        code_retour%valeur = pm_err_valid            ! probleme dans la MSLIB90
     end if
     go to 6000
  end if
  !
  !
  anglemod = modulo (angle, pm_deux_pi)                               !conversion de l'angle sur [0,2pi[
  !
  quat%q0      = cos (anglemod / 2._pm_reel)                          !calcul du quaternion equivalent
  quat%q123(:) = sin (anglemod / 2._pm_reel) * axe_norme(:)
  !

6000 continue

  code_retour%routine = pm_num_mu_axe_angle_quat
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mu_axe_angle_quat
