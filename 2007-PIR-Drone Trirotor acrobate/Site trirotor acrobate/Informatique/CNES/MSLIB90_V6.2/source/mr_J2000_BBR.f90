subroutine mr_J2000_BBR (pos_J2000, pos_Pla1, vit_Pla1, pos_Pla2, vit_Pla2, pos_BBR, code_retour, vit_J2000, vit_BBR)

! (C) Copyright CNES - MSLIB - 2004

!************************************************************************
!
! But: Passage du repere J2000 au repere Body Body Rotating (BBR)
! ===
!
! Note d'utilisation: 
! ==================
!
! Historique:
! ==========
!   + Version 6.2 : creation a partir de la routine MOD_MAT_EME2000RLAG de la LIBIP90
!
!************************************************************************


! Modules
! =======
use int_mslib_mr_mat_J2000_BBR

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mr_J2000_BBR.h'

! Autres declarations
! ===================
real(pm_reel), dimension(6)   :: posvitJ2000
real(pm_reel), dimension(6)   :: posvitBBR
real(pm_reel), dimension(6,6) :: mat

intrinsic matmul


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
     '@(#) Fichier MSLIB mr_J2000_BBR.f90: derniere modification V6.2 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mr_J2000_BBR.f90,v 1.4 2005/02/28 07:50:29 mslibdev Exp $ '

!************************************************************************

! initialisations
! ===============

code_retour%valeur = pm_OK

! calculs
! =======

! calcul de la matrice de passage J2000 -> BBR
call mr_mat_J2000_BBR(pos_Pla1, vit_Pla1, pos_Pla2, vit_Pla2, mat, code_retour)
if (code_retour%valeur /= pm_OK) go to 6000


! recuperation des positions-vitesses dans le J2000
posvitJ2000(1:3) = pos_J2000(1:3)

if (present(vit_J2000)) then

   posvitJ2000(4:6) = vit_J2000(1:3)

else ! initialisation a 0 dans le cas ou la vitesse J2000 n'est pas fournie

   posvitJ2000(4:6) = 0._pm_reel

end if

! calcul des positions-vitesses dans BBR
! (calcul valable en cas de presence ou non de la vitesse J2000)
posvitBBR(:) = matmul(mat, posvitJ2000)

! affectation des sorties

! pour la position
pos_BBR(:) = posvitBBR(1:3)

! pour la vitesse optionnelle

if (present(vit_BBR) .and. (.not.present(vit_J2000))) then

   code_retour%valeur = pm_err_para_option
   go to 6000

else if (present(vit_J2000) .and. (.not.present(vit_BBR))) then

   code_retour%valeur = pm_warn_para_option

else if (present(vit_J2000) .and. present(vit_BBR)) then

   vit_BBR(:) = posvitBBR(4:6)

end if

6000 continue

code_retour%routine = pm_num_mr_J2000_BBR
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mr_J2000_BBR
