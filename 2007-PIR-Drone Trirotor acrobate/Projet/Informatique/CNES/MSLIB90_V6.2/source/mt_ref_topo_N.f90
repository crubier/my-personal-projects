subroutine mt_ref_topo_N (orig_topo, r_equa, apla, pos_ref, pos_topo, code_retour, vit_ref, vit_topo, jacob)

! (C) Copyright CNES - MSLIB - 1998

!************************************************************************
!
! But:  Passage du repere terrestre de REFerence a un repere TOPOcentrique Nord (convention axe Ox vers le Nord).
! ===
!
! Note d'utilisation:  La transformation inverse peut s'effectuer par mt_topo_N_ref
! ==================
!
! Historique:
! ==========
!   + Version 1.0 (SP 252 ed01 rev00): creation a partir de la routine MVGETO de la MSLIB f77
!   + Version 2.0 (FA 347 ed01 rev00): Modification du test sur l'aplatissement
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

include 'arg_mt_ref_topo_N.h'

! Autres declarations
! -------------------
real(pm_reel), dimension(3)   ::   vectu,vectv,vectw ! composantes dans le repere geocentrique des trois vecteurs (u,v,w)
real(pm_reel), dimension(3)   ::   sta               ! coordonnees cartesiennes de l'origine du repere topocentrique
real(pm_reel), dimension(3)   ::   pos               ! coordonnees intermediaires de calcul


intrinsic dot_product, present


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mt_ref_topo_N.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mt_ref_topo_N.f90,v 1.7 2003/10/14 12:52:48 mslibdev Exp $ '

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


! -------------------------------------------------------
! calcul des composantes des vecteurs (u,v,w) constituant
! le repere topocentrique de la station 
! -------------------------------------------------------
call mt_def_topo_N (orig_topo%lat,orig_topo%long,vectu,vectv,vectw,code_retour) 
! code retour toujours OK

!-------------------------------------------------------------------------
! calcul des coordonnees cartesiennes de l'origine du repere topocentrique
!-------------------------------------------------------------------------   
call mt_geod_car(orig_topo, r_equa, apla, sta, code_retour)
! code retour toujours OK puisque apla deja teste.

pos(:) = pos_ref(:) - sta(:)!calcul des variables intermediaires : 
                            !positions du satellite -coordonnees de la station dans le repere geocentrique terrestre

!-------------------------------------------------------
! calcul des composantes du vecteur position du satellite
! dans le repere topocentrique
!-------------------------------------------------------
pos_topo(1) = dot_product(vectu, pos)
pos_topo(2) = dot_product(vectv, pos)
pos_topo(3) = dot_product(vectw, pos)

!---------------------------------------------------
! calculs optionnels
!---------------------------------------------------
!---------------------------------------------------------
! calcul optionel du jacobien : calcul des derivees partielles des 
! vecteurs position et vitesse
!---------------------------------------------------------

if (present(jacob)) then

   jacob(:,:) = 0._pm_reel

   jacob(1,1:3) = vectu(:)   !     derivee partiellle de x 
   jacob(2,1:3) = vectv(:)   !     derivee partiellle de y 
   jacob(3,1:3) = vectw(:)   !     derivee partiellle de z 
   jacob(4,4:6) = vectu(:)   !     derivee partiellle de vx 
   jacob(5,4:6) = vectv(:)   !     derivee partiellle de vy
   jacob(6,4:6) = vectw(:)   !     derivee partiellle de vz 

end if

! verification du parametrage pour le calcul de la vitesse
!=========================================================

if (present(vit_topo).and..not.present(vit_ref)) then  ! mauvais parametrage

   code_retour%valeur = pm_err_para_option
   go to 6000

else if (present(vit_topo).and.present(vit_ref)) then  ! calcul optionel des composantes du vecteur vitesse du satellite
                                                       ! dans le repere topocentrique

      vit_topo(1) = dot_product(vectu, vit_ref)
      vit_topo(2) = dot_product(vectv, vit_ref)
      vit_topo(3) = dot_product(vectw, vit_ref)

end if
if (present(vit_ref).and..not.present(vit_topo)) code_retour%valeur = pm_warn_para_option

6000 continue

code_retour%routine = pm_num_mt_ref_topo_N
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mt_ref_topo_N
