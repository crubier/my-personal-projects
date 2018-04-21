subroutine mt_topo_N_ref (orig_topo, r_equa, apla, pos_topo, pos_ref, code_retour, vit_topo, vit_ref, jacob)

! (C) Copyright CNES - MSLIB - 1998

!************************************************************************
!
! But:  Passage du repere TOPOcentrique Nord (convention axe Ox vers le Nord) au repere terrestre de REFerence .
! ===
!
! Note d'utilisation: La transformation inverse peut se faire par mt_ref_topo_N
! ==================
!
! Historique:
! ==========
!   + Version 1.0 (SP 253 ed01 rev00): creation a partir de la routine MVTOGE de la MSLIB f77
!   + Version 2.0 (FA 346 ed01 rev00): Modification du test sur l'aplatissement
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!
!************************************************************************


! Modules
! =======
use int_mslib_mt_def_topo_N
use int_mslib_mt_geod_car

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mt_topo_N_ref.h'

! Autres declarations
! -------------------

real(pm_reel), dimension(3)   ::   vectu,vectv,vectw!     composantes dans le repere geocentrique des trois vecteurs (u,v,w)
                                                    !     constituant le repere topocentrique de la station     
real(pm_reel), dimension(3)   ::   pos              !     vecteur intermediaire pour le calcul du vecteur position satellite
real(pm_reel), dimension(3)   ::   sta              !     coordonnees cartesiennes de l'origine du repere topocentrique.




character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
     '@(#) Fichier MSLIB mt_topo_N_ref.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mt_topo_N_ref.f90,v 1.7 2003/10/14 12:53:13 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
code_retour%valeur = pm_OK

! controle des donnees d'entree
! .............................
if (apla >= 1._pm_reel) then    ! aplatissement terrestre superieur ou egal a 1
   code_retour%valeur = pm_err_apla_sup1
   go to 6000
end if

!-------------------------------------------------------
! calcul des composantes des vecteurs (u,v,w) constituant
! le repere topocentrique de la station 
! -------------------------------------------------------

call mt_def_topo_N (orig_topo%lat,orig_topo%long,vectu,vectv,vectw,code_retour)
! le code retour est toujours OK

!-------------------------------------------------------------------------
! calcul des coordonnees cartesiennes de l'origine du repere topocentrique
!-------------------------------------------------------------------------   
call mt_geod_car(orig_topo, r_equa, apla, sta, code_retour)
! code retour toujours OK puisque apla deja teste.

!----------------------------------------------------
! calcul des composantes du vecteur position satellite
! dans le repere geocentrique
!----------------------------------------------------
! calcul des variables intermediaires :
! positions du satellite - coordonnees de la station dans le repere geocentrique terrestre

pos(:) = vectu(:) * pos_topo(1) + vectv(:) * pos_topo(2) + vectw(:) * pos_topo(3)
pos_ref(:) = pos(:) + sta(:)


! ------------------
! calculs optionnels
! ------------------

! ---------------------------------------------------------
! calcul du jacobien : calcul des derivees partielles des 
! vecteurs position et vitesse 
! ---------------------------------------------------------

if (present(jacob)) then

   jacob(:,:) = 0._pm_reel

   jacob(1:3,1) = vectu(:)         !     derivee partielle de x 
   jacob(1:3,2) = vectv(:)         !     derivee partielle de y 
   jacob(1:3,3) = vectw(:)         !     derivee partielle de z 
   jacob(4:6,4) = vectu(:)         !     derivee partielle de vx  
   jacob(4:6,5) = vectv(:)         !     derivee partielle de vy 
   jacob(4:6,6) = vectw(:)         !     derivee partielle de vz 

end if

! ---------------------------------------------------
! calcul des composantes du vecteur vitesse satellite
! dans le repere geocentrique
! ---------------------------------------------------


if (present(vit_ref).and..not.present(vit_topo)) then ! mauvais parametrage

      code_retour%valeur = pm_err_para_option
      go to 6000

else if (present(vit_topo).and.present(vit_ref)) then

      vit_ref(:) = vectu(:) * vit_topo(1) + vectv(:) * vit_topo(2) + vectw(:) * vit_topo(3) 

end if
if (present(vit_topo).and..not.present(vit_ref)) code_retour%valeur = pm_warn_para_option



6000 continue

code_retour%routine = pm_num_mt_topo_N_ref
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mt_topo_N_ref
