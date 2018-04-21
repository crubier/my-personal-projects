subroutine mu_prod_quat (quat1, quat2, quat_prod, code_retour)

! (C) Copyright CNES - MSLIB - 2000

!************************************************************************
!
! But: Calcul du PRODuit de deux QUATernions 
! ===
!
! Note d'utilisation: Sans objet 
! ==================
!
! Historique:
! ==========
!   + Version 3.0 (SP 426 ed01 rev00): creation a partir de la routine MUQPROD de la MSLIB f77
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!
!************************************************************************


! Modules
! =======
use int_mslib_mu_prod_vect

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mu_prod_quat.h'

! Autres declarations
! ===================

real(pm_reel), dimension(3)   ::   produit_vectoriel ! produit vectoriel des champs q123 respectifs 
                                                     ! des deux quaternions

intrinsic dot_product


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mu_prod_quat.f90: derniere modification V3.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mu_prod_quat.f90,v 1.4 2003/04/04 14:57:37 mslibatv Exp $ '

!************************************************************************

! initialisations
! ===============

! initialisation de la valeur du code retour

code_retour%valeur = pm_OK


quat_prod%q0 = quat1%q0 * quat2%q0 - dot_product(quat1%q123, quat2%q123)
call mu_prod_vect(quat1%q123, quat2%q123, produit_vectoriel, code_retour)
! Le code retour est toujours OK
quat_prod%q123(:) = produit_vectoriel(:) + quat1%q0 * quat2%q123(:) + quat2%q0 * quat1%q123(:)

6000 continue

code_retour%routine = pm_num_mu_prod_quat
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mu_prod_quat
