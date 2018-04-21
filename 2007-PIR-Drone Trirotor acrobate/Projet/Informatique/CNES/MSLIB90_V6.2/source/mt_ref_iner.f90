subroutine mt_ref_iner (vit_rot, long, sec, pos_ref, pos_iner, code_retour, vit_ref, vit_iner, jacob)

! (C) Copyright CNES - MSLIB - 1998-2003

!************************************************************************
!
! But:  Passage du repere terrestre de REFerence a un repere geocentrique INERtiel lie a un mobile (du type "H0-9")
! ===
!
! Note d'utilisation:  La transformation inverse peut s'effectuer par la routine mt_iner_ref
! ==================   
!
! Historique:
! ==========
!   + Version 1.0 (SP 254 ed01 rev00): creation a partir de la routine MVGEIN de la MSLIB f77
!   + Version 2.0 (DE 350 global ed01 rev00): Suppression du use constantes_terre_mslib
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

include 'arg_mt_ref_iner.h'

! Autres declarations
! -------------------
real(pm_reel), dimension(3)  :: position !     vecteur position intermediaire
real(pm_reel)   ::   rphi                !     angle entre le repere geocentrique et le repere inertiel
real(pm_reel)   ::   rcosfi,rsinfi       !     variables intermediaires pour le calcul des positions vitesses

intrinsic cos, sin, present


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mt_ref_iner.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mt_ref_iner.f90,v 1.9 2003/12/03 16:31:24 mslibatv Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
code_retour%valeur = pm_OK


! ----------------------------------------------------------------------
! calcul intermediaire de l'angle rphi entre le repere geocentrique et le   
! repere inertiel au moment du changement de repere
! ----------------------------------------------------------------------

rphi = vit_rot*sec - long
rcosfi = cos(rphi)
rsinfi = sin(rphi)

! --------------------------------------------------------------
! calcul des composantes positions en repere inertiel : pos_iner
! ---------------------------------------------------------------

position(1) = rcosfi * pos_ref(1) - rsinfi * pos_ref(2)
position(2) = rsinfi * pos_ref(1) + rcosfi * pos_ref(2) 
position(3) = pos_ref(3)

! -------------------
! calcul optionnels
! -------------------
if (present(jacob)) then  ! calcul du jacobien : calcul des derivees partielles des vecteurs position et vitesse 
   jacob(:,:) = 0._pm_reel

   !     derivee partielle de x :
   !     ------------------------
   jacob(1,1) = rcosfi
   jacob(1,2) = -rsinfi

   !     derivee partielle de y :
   !     ------------------------
   jacob(2,1) = rsinfi
   jacob(2,2) = rcosfi

   !     derivee partielle de z :
   !     ------------------------
   jacob(3,3) = 1._pm_reel

   !     derivee partielle de vx :
   !     -------------------------
   jacob(4,1) = -vit_rot * rsinfi
   jacob(4,2) = -vit_rot * rcosfi
   jacob(4,4) = rcosfi
   jacob(4,5) = -rsinfi

   !     derivee partielle de vy :
   !     -------------------------
   jacob(5,1) =  vit_rot * rcosfi
   jacob(5,2) = -vit_rot * rsinfi
   jacob(5,4) = rsinfi
   jacob(5,5) = rcosfi

   !     derivee partielle de vz :
   !     -------------------------
   jacob(6,6) = 1._pm_reel

end if

if (present(vit_iner).and..not.present(vit_ref)) then  ! erreur de parametrage

   code_retour%valeur =pm_err_para_option
   go to 6000

else if  (present(vit_ref).and.present(vit_iner)) then      ! calcul des composantes vitesses en repere inertiel

   vit_iner(1) = - (vit_rot * position(2))+ (rcosfi * vit_ref(1)) - (rsinfi * vit_ref(2))
   vit_iner(2) =  vit_rot * position(1)+ (rsinfi * vit_ref(1)) + (rcosfi * vit_ref(2)) 
   vit_iner(3) = vit_ref(3)

end if
if (present(vit_ref).and..not.present(vit_iner)) code_retour%valeur = pm_warn_para_option ! parametrage optionnel incoherent


6000 continue

! Affectation de la sortie obligatoire:
pos_iner(:) = position(:)

code_retour%routine = pm_num_mt_ref_iner
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mt_ref_iner
