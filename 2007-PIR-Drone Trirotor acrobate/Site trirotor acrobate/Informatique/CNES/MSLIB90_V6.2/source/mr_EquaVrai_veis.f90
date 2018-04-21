subroutine mr_EquaVrai_veis ( model, jul1950, delta_tu1, delta_tai, pos_EquaVrai, pos_veis, code_retour, &
                              vit_EquaVrai, vit_veis, jacob )

! (C) Copyright CNES - MSLIB - 1999-2003

!************************************************************************
!
! But: Passage du repere equatorial vrai a la date t au repere de Veis a la meme date t 
! ===
!
! Notes d'utlisation:  [DR1] "Les systemes de reference utilises en astronomie"
! ===================        de M. Chapront-Touze, G. Francou et B. Morando
!                            Bureau Des Longitudes (BDL) novembre 1994
!                            ISSN 1243-4272
!                            ISBN 2-910015-05-X
!                            nomenclature MSLIB M-NT-0-160-CN
!                      Nota: Les epoques B1900, J1900 et J2000 sont explicitees en
!                            page 23 table 1.1
!
!                      Les vitesses declarees en sorties optionnelles ne peuvent etre calculees que si les vitesses declarees
!                      en entree optionnelles sont specifiees.
!
! Historique:
! ==========
!   + Version 2.0 (SP 383 ed01 rev00): creation a partir de la routine MRChgRepCVVeis de la MSLIB f77
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!   + Version 4.0 (DE 455 ed01 rev00) : remplacement des calculs par appel a 2 routines
!                         EquaVrai - TerVrai et TerVrai - veis
!   + Version 4.0 (DE globale 480 ed01 rev00) : remplacement des tests de report de code retour en select
!   + Version 4.1 (DE globale 484 ed01 rev00): calcul de la jacobienne 
!
!************************************************************************


! Modules
! =======
use int_mslib_mr_EquaVrai_TerVrai
use int_mslib_mr_TerVrai_veis

use code_modeles_mslib

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mr_EquaVrai_veis.h'

! Autres declarations
! ===================

real(pm_reel),dimension(3)     :: pos_TerVrai   ! position intermediaire
real(pm_reel),dimension(3)     :: vit_TerVrai   ! vitesse intermediaire
real(pm_reel),dimension(6,6)   :: jacob_1, jacob_2  ! jacobiennes intermediaires
type(tm_code_retour)           :: code_retour_local

character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mr_EquaVrai_veis.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id = &
           ' $Id: mr_EquaVrai_veis.f90,v 1.11 2003/10/14 12:48:14 mslibdev Exp $ '

!************************************************************************

! initialisations
! ===============

! initialisation de la valeur du code retour

code_retour%valeur = pm_OK

! Debut de corps du programme
! ===========================

! test sur la coherence des entrees/sorties optionnelles si precisees

if ((present(vit_veis)) .and. (.not. present(vit_EquaVrai))) then
   code_retour%valeur = pm_err_para_option
   go to 6000
end if

if ((present(vit_EquaVrai)) .and. (.not. present(vit_veis))) then
   code_retour%valeur = pm_warn_para_option
end if

! test sur le modele choisi 

if (model /= pm_lieske_wahr) then

   code_retour%valeur = pm_err_ind_model
   go to 6000

end if

! Appel a 2 routines successives

if (present(vit_veis)) then           ! avec les vitesses
 
   if (present(jacob)) then           ! avec la jacobienne
      call mr_EquaVrai_TerVrai ( model, jul1950, delta_tu1, delta_tai, pos_EquaVrai, pos_TerVrai, code_retour_local, &
           vit_EquaVrai=vit_EquaVrai, vit_TerVrai=vit_TerVrai, jacob=jacob_1 )
      if (code_retour_local%valeur /= pm_OK) then
         code_retour%valeur = code_retour_local%valeur           ! affectation du code retour
         if (code_retour%valeur < pm_OK) go to 6000              ! sortie si erreur
      end if

      call mr_TerVrai_veis ( jul1950, delta_tu1, pos_TerVrai, pos_veis, code_retour_local, &
           vit_TerVrai=vit_TerVrai, vit_veis=vit_veis, jacob=jacob_2 )
      if (code_retour_local%valeur /= pm_OK) then
         code_retour%valeur = code_retour_local%valeur           ! affectation du code retour
         if (code_retour%valeur < pm_OK) go to 6000              ! sortie si erreur
      end if
   else                               ! sans la jacobienne
      call mr_EquaVrai_TerVrai ( model, jul1950, delta_tu1, delta_tai, pos_EquaVrai, pos_TerVrai, code_retour_local, &
           vit_EquaVrai=vit_EquaVrai, vit_TerVrai=vit_TerVrai )
      if (code_retour_local%valeur /= pm_OK) then
         code_retour%valeur = code_retour_local%valeur           ! affectation du code retour
         if (code_retour%valeur < pm_OK) go to 6000              ! sortie si erreur
      end if

      call mr_TerVrai_veis ( jul1950, delta_tu1, pos_TerVrai, pos_veis, code_retour_local, &
           vit_TerVrai=vit_TerVrai, vit_veis=vit_veis )
      if (code_retour_local%valeur /= pm_OK) then
         code_retour%valeur = code_retour_local%valeur           ! affectation du code retour
         if (code_retour%valeur < pm_OK) go to 6000              ! sortie si erreur
      end if
   end if

else                                   ! sans les vitesses

   if (present(jacob)) then            ! avec la jacobienne
      call mr_EquaVrai_TerVrai ( model, jul1950, delta_tu1, delta_tai, pos_EquaVrai, pos_TerVrai, code_retour_local, jacob=jacob_1 )
      if (code_retour_local%valeur /= pm_OK) then
         code_retour%valeur = code_retour_local%valeur           ! affectation du code retour
         if (code_retour%valeur < pm_OK) go to 6000              ! sortie si erreur
      end if

      call mr_TerVrai_veis ( jul1950, delta_tu1, pos_TerVrai, pos_veis, code_retour_local, jacob=jacob_2 )
      if (code_retour_local%valeur /= pm_OK) then
         code_retour%valeur = code_retour_local%valeur           ! affectation du code retour
         if (code_retour%valeur < pm_OK) go to 6000              ! sortie si erreur
      end if
   else                               ! sans la jacobienne
      call mr_EquaVrai_TerVrai ( model, jul1950, delta_tu1, delta_tai, pos_EquaVrai, pos_TerVrai, code_retour_local )
      if (code_retour_local%valeur /= pm_OK) then
         code_retour%valeur = code_retour_local%valeur           ! affectation du code retour
         if (code_retour%valeur < pm_OK) go to 6000              ! sortie si erreur
      end if

      call mr_TerVrai_veis ( jul1950, delta_tu1, pos_TerVrai, pos_veis, code_retour_local )
      if (code_retour_local%valeur /= pm_OK) then
         code_retour%valeur = code_retour_local%valeur           ! affectation du code retour
         if (code_retour%valeur < pm_OK) go to 6000              ! sortie si erreur
      end if
   end if

end if

if (present(jacob)) jacob = matmul(jacob_2,jacob_1)

! Fin de corps du programme
! =========================


6000 continue

code_retour%routine = pm_num_mr_EquaVrai_veis
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mr_EquaVrai_veis
