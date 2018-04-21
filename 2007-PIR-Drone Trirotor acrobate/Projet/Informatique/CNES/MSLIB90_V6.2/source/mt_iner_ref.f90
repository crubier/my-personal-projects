subroutine mt_iner_ref (vit_rot, long, sec, pos_iner, pos_ref, code_retour, vit_iner, vit_ref, jacob)

! (C) Copyright CNES - MSLIB - 1998-2003

!************************************************************************
!
! But:  Passage du repere geocentrique INERtiel lie a un mobile (du type "H0-9")au repere terrestre de REFerence. 
! ===
!
! Note d'utilisation:  La transformation inverse peut s'effectuer par la routine mt_ref_iner.
! ==================
!
! Historique:
! ==========
!   + Version 1.0 (SP 255 ed01 rev00): creation a partir de la routine MVINGE de la MSLIB f77
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
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

include 'arg_mt_iner_ref.h'

! Autres declarations
! -------------------

real(pm_reel), dimension(3)    ::    position  ! vecteur position intermediaire
real(pm_reel)    ::    rphi         !     angle entre le repere geocentrique et le repere inertiel
real(pm_reel)    ::    rcosfi,rsinfi!     variables intermediaires pour le calcul des positions vitesses

intrinsic cos, sin, present

character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mt_iner_ref.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mt_iner_ref.f90,v 1.9 2003/12/03 16:31:21 mslibatv Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
code_retour%valeur = pm_OK

!-------------------------------------------------------
! calcul de l'angle entre le repere geocentrique et le   
! repere inertiel au moment du changement de repere
!-------------------------------------------------------

rphi = vit_rot*sec - long   
rcosfi = cos(rphi)
rsinfi = sin(rphi)

!-------------------------------------------------------
! calcul des composantes positions en repere geocentrique
!------------------------------------------------------

position(1) = rcosfi * pos_iner(1) + rsinfi * pos_iner(2)
position(2) = - rsinfi * pos_iner(1) + rcosfi * pos_iner(2) 
position(3) = pos_iner(3)

!--------------------
! calcul optionnel
!--------------------
if (present(jacob)) then    ! calcul du jacobien

   jacob(:,:) = 0._pm_reel

   !     derivee partielle de x :
   !     ------------------------
   jacob(1,1) = rcosfi
   jacob(1,2) = rsinfi

   !     derivee partielle de y :
   !     ------------------------
   jacob(2,1) = -rsinfi
   jacob(2,2) = rcosfi

   !     derivee partielle de z :
   !     ------------------------
   jacob(3,3) = 1._pm_reel

   !     derivee partielle de vx :
   !     -------------------------
   jacob(4,1) = -vit_rot * rsinfi
   jacob(4,2) = vit_rot * rcosfi
   jacob(4,4) = rcosfi
   jacob(4,5) = rsinfi

   !     derivee partielle de vy :
   !     -------------------------
   jacob(5,1) = - vit_rot * rcosfi
   jacob(5,2) = - vit_rot * rsinfi
   jacob(5,4) = -rsinfi
   jacob(5,5) = rcosfi

   !     derivee partielle de vz :
   !     -------------------------
   jacob(6,6) = 1._pm_reel

end if


if (present(vit_ref).and..not.present(vit_iner)) then ! mauvais parametrage
      code_retour%valeur = pm_err_para_option
      go to 6000
else if (present(vit_iner).and.present(vit_ref)) then  ! calcul des composantes de la vitesse dans le repere geocentrique 
                                                       !de reference
      vit_ref(1) =  (vit_rot * position(2))+ (rcosfi * vit_iner(1)) + (rsinfi * vit_iner(2))
      vit_ref(2) = -(vit_rot * position(1))- (rsinfi * vit_iner(1)) + (rcosfi * vit_iner(2)) 
      vit_ref(3) =   vit_iner(3)
end if
if (.not.present(vit_ref).and. present(vit_iner))  code_retour%valeur = pm_warn_para_option ! parametrage optionnel incoherent


6000 continue

! Affectation de la position en repere de reference
pos_ref(:) = position(:)

code_retour%routine = pm_num_mt_iner_ref
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mt_iner_ref
