subroutine mu_quat_rep (vect1, quat, vect2, code_retour)

  ! (C) Copyright CNES - MSLIB - 2000

  !************************************************************************
  !
  ! But: A l'aide d'un QUATernion, calcul de changement de REPere.
  ! ===
  !
  ! Note d'utilisation: Sans objet 
  ! ==================
  !
  ! Historique:
  ! ==========
  !   + Version 3.0 (SP 427 ed01 rev00): creation a partir de la routine MUQUATROT de la MSLIB f77
  !   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
  !
  !************************************************************************


  ! Modules
  ! =======
  use int_mslib_mu_quat_norme
  use int_mslib_mu_prod_quat
  use int_mslib_mu_quat_conjug

  use precision_mslib
  use type_mslib
  use valeur_code_retour_mslib
  use numero_routine_mslib
  use longueur_chaine_mslib


  ! Declarations
  ! ============
  implicit none

  include 'arg_mu_quat_rep.h'

  ! Autres declarations
  ! ===================

  real(pm_reel) :: norme                              ! norme du quaternion d'entree
  type(tm_quat) :: quat_norme, quat_vect1, quat_prod1 ! quaternion d'entree norme, quaternion associe au vecteur
                                                      ! en entree, et produit de ces deux quaternions
  type(tm_quat) :: quat_norme_conjug                  ! quaternion conjugue du quaternion d'entree norme
  type(tm_quat) :: quat_vect2                         ! quaternion associe au vecteur en sortie


  character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
       '@(#) Fichier MSLIB mu_quat_rep.f90: derniere modification V3.1 >'

  ! Ne pas toucher a la ligne suivante
  character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mu_quat_rep.f90,v 1.4 2003/04/04 14:57:38 mslibatv Exp $ '

  !************************************************************************

  ! initialisations
  ! ===============

  ! initialisation de la valeur du code retour

  code_retour%valeur = pm_OK

  call mu_quat_norme(quat, quat_norme, norme, code_retour) ! normalisation du quaternion
  if (code_retour%valeur /= pm_OK) then       ! erreur dans le cas d'un quaternion a norme nulle
     if (code_retour%valeur /= pm_err_quat_nul ) then
        code_retour%valeur = pm_err_valid     ! probleme dans la MSLIB90
     end if
     go to 6000
  end if

  ! Affectation du quaternion associe au vecteur en entree
  quat_vect1%q0 = 0._pm_reel
  quat_vect1%q123(:) = vect1(:)

  ! Calcul du quaternion resultat
  call mu_prod_quat(quat_vect1, quat_norme, quat_prod1, code_retour) ! les codes retour sont toujours OK
  call mu_quat_conjug (quat_norme, quat_norme_conjug, code_retour)
  call mu_prod_quat(quat_norme_conjug, quat_prod1, quat_vect2, code_retour)

  vect2(:) = quat_vect2%q123(:) ! Calcul du vecteur issu du quaternion resultat

6000 continue

  code_retour%routine = pm_num_mu_quat_rep
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mu_quat_rep
