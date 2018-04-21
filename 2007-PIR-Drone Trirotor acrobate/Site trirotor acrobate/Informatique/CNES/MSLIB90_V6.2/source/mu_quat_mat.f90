subroutine mu_quat_mat (quat, mat, code_retour)

! (C) Copyright CNES - MSLIB - 2003

!************************************************************************
!
! But: Calcul de la matrice de rotation associee a un quaternion 
! ===
!
! Note d'utilisation:  
! ==================
!               Le quaternion peut etre norme ou non. Il est systematiquement norme ici.
!               La transformation inverse peut s'effectuer par la routine mu_mat_quat
!
! Historique:
! ==========
!   + Version 5.0 (SP 605 ed01 rev00): creation par transfert de la routine de meme nom de la MSPRO
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

include 'arg_mu_quat_mat.h'

! Autres declarations
! ===================

real(pm_reel) :: norme           ! norme du quaternion  
type(tm_quat) :: quat_norme      ! quaternion norme
real(pm_reel) :: matii_1er_terme ! partie commune aux termes (i,i) de la diagonale de la matrice M
integer       :: i               ! indice


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mu_quat_mat.f90: derniere modification V5.0 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mu_quat_mat.f90,v 1.4 2003/12/15 17:36:08 mslibdev Exp $ '

!************************************************************************

! initialisations
! ===============

! initialisation de la valeur du code retour

code_retour%valeur = pm_OK

! le quaternion en entree doit etre norme: on le norme obligatoirement
call mu_quat_norme (quat, quat_norme, norme, code_retour)
if (code_retour%valeur < pm_OK) go to 6000  ! le quaternion en entree est nul


! calcul de la matrice de rotation associe
! ========================================

! le quaternion etant norme, cela assure que la matrice est orthonormale
! et de derminant = +1 (pour plus de details de reporter a la note
! algo et a mu_mat_quat)


! calcul de la diagonale de la matrice M
matii_1er_terme =  2._pm_reel*quat_norme%q0*quat_norme%q0 - 1._pm_reel

do i = 1,3
   mat(i,i) = matii_1er_terme + 2._pm_reel*quat_norme%q123(i)*quat_norme%q123(i)
end do


! calcul des elements non diagonaux de la matrice M
mat(1,2) = 2._pm_reel * ( quat_norme%q123(1) * quat_norme%q123(2) +  quat_norme%q0 * quat_norme%q123(3) )
mat(1,3) = 2._pm_reel * ( quat_norme%q123(1) * quat_norme%q123(3) -  quat_norme%q0 * quat_norme%q123(2) )
mat(2,1) = 2._pm_reel * ( quat_norme%q123(1) * quat_norme%q123(2) -  quat_norme%q0 * quat_norme%q123(3) )
mat(2,3) = 2._pm_reel * ( quat_norme%q123(2) * quat_norme%q123(3) +  quat_norme%q0 * quat_norme%q123(1) )
mat(3,1) = 2._pm_reel * ( quat_norme%q123(1) * quat_norme%q123(3) +  quat_norme%q0 * quat_norme%q123(2) )
mat(3,2) = 2._pm_reel * ( quat_norme%q123(2) * quat_norme%q123(3) -  quat_norme%q0 * quat_norme%q123(1) )


6000 continue

code_retour%routine = pm_num_mu_quat_mat
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mu_quat_mat
