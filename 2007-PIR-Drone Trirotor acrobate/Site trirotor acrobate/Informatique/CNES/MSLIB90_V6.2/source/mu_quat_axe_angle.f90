subroutine mu_quat_axe_angle (quat, axe, angle, code_retour)

  ! (C) Copyright CNES - MSLIB - 2000

  !************************************************************************
  !
  ! But: Conversion d'un QUATernion en une rotation definie par son AXE et son ANGLE 
  ! ===
  !
  ! Note d'utilisation:  La transformation inverse (rotation -> quaternion) 
  ! ==================   peut etre realisee par la routine mu_axe_angle_quat
  !
  ! Historique:
  ! ==========
  !   + Version 3.0 (SP 422 ed01 rev00): creation a partir de la routine MUCQUAVEC de la MSLIB f77
  !   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
  !
  !************************************************************************


  ! Modules
  ! =======
  use int_mslib_mu_quat_norme

  use precision_mslib
  use type_mslib
  use valeur_code_retour_mslib
  use numero_routine_mslib
  use longueur_chaine_mslib


  ! Declarations
  ! ============
  implicit none

  include 'arg_mu_quat_axe_angle.h'

  ! Autres declarations
  ! ===================
  ! variables intermediaires de calcul
  real(pm_reel)                 :: sinus_angle, norme
  type(tm_quat)                 :: quat_norme
  real(pm_reel)                 :: presque_zero ! plus petit nombre machine

  intrinsic tiny, acos, sqrt, abs

  character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
       '@(#) Fichier MSLIB mu_quat_axe_angle.f90: derniere modification V3.1 >'

  ! Ne pas toucher a la ligne suivante
  character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mu_quat_axe_angle.f90,v 1.4 2003/04/04 14:57:38 mslibatv Exp $ '

  !************************************************************************

  ! initialisations
  ! ===============

  ! initialisation de la valeur du code retour

  code_retour%valeur = pm_OK

  presque_zero = tiny(1._pm_reel)         ! plus petit reel machine


  call mu_quat_norme (quat, quat_norme, norme, code_retour) ! calcul de la norme et normalisation du quaternion
  if (code_retour%valeur /= pm_OK) then       ! erreur dans le cas d'un quaternion a norme nulle
     if (code_retour%valeur /= pm_err_quat_nul ) then
        code_retour%valeur = pm_err_valid     ! probleme dans la MSLIB90
     end if
     go to 6000
  end if
  
  ! calcul de l'angle de la rotation dans [0,2pi]
  
  angle       = 2._pm_reel * acos(quat_norme%q0) 
  sinus_angle = sqrt(1._pm_reel - quat_norme%q0**2)
  
  ! test du cas ou la 1ere composante du quaternion vaut 1 ou -1
  
  if (abs(sinus_angle)<= presque_zero) then
     code_retour%valeur = pm_err_axe_rot_indef
     go to 6000
  end if
  
  axe(1:3) = quat_norme%q123(1:3) / sinus_angle !calcul des coordonnees de l'axe

6000 continue

  code_retour%routine = pm_num_mu_quat_axe_angle
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mu_quat_axe_angle
