subroutine mvi_car_kep_parab (pos_car,vit_car,moment_cinetique,norme_vect_pos,norme_moment_cinetique,&
                              e, parametre,pos_fois_vit,mu,kep,retour,jacob)

! (C) Copyright CNES - MSLIB - 1998

!************************************************************************
!
! But:  Passage des coordonnees CARtesiennes aux coordonnees KEPleriennes dans le cas PARABolique.
! ===
!
! Note d'utilisation: - Routine interne  
! ==================  - L'appelant doit tester que :
!                           1) l'orbite est parabolique : e  = 1
!                           2) le parametre est > 0
!                           3) la norme du moment cinetique est non nulle
!                           4) la norme du vecteur position est non nulle
!
! Historique:
! ==========
!   + Version 1.0 (SP 229 ed01 rev00): creation a partir de la routine MVPACO de la MSLIB f77
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!
!************************************************************************


! Modules
! =======
use test_mslib
use math_mslib
use int_mslib_mu_angle2

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mvi_car_kep_parab.h'

! Autres declarations
! -------------------

!     tableaux derivees intermediaires
real(pm_reel),dimension(6)      :: drdx(6),dpos_fois_vit(6)
real(pm_reel),dimension(6)      :: drxv1(6),drxv2(6),drxv3(6)
real(pm_reel),dimension(6)      :: drxv(6),dddx(6),dpovdx(6)
real(pm_reel),dimension(6)      :: dacpov(6),drsav(6),davdx(6)
real(pm_reel),dimension(6)      :: dpdx(6),dedx(6),dxidx(6)
real(pm_reel),dimension(6)      :: dpodx(6),dgodx(6),dxmdx(6)

real(pm_reel)      :: r                                   !     norme vecteur position
real(pm_reel)      :: rxv1,rxv2,rxv3,rxv,nrxv1,nrxv2,nrxv3!     coordonnees produit vectoriel position x vitesse,
                                                          !     norme et norme**2
real(pm_reel)      :: po,pov,av                           !     variables angles intermediaires
real(pm_reel)      :: cof,rxvsi2,rsxi2,r2,d,rxvsmu        !     termes intermediaires

!     variables calculs sinus-cosinus d'angles
real(pm_reel)      :: rxvsxi,cxi,sxi,rsicgo,rsisgo
real(pm_reel)      :: aspov,acpov,rcav,rsav

type(tm_code_retour)  :: code_retour

intrinsic  present, modulo, sqrt


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
     '@(#) Fichier MSLIB mvi_car_kep_parab.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mvi_car_kep_parab.f90,v 1.8 2003/10/14 12:55:23 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
retour = pm_OK

r=norme_vect_pos!     norme vecteur position 

rxv1 = moment_cinetique(1)!
rxv2 = moment_cinetique(2)!     produit vectoriel (position x vitesse)
rxv3 = moment_cinetique(3)!

rxv  = norme_moment_cinetique!     norme du vecteur produit vectoriel (position x vitesse)

nrxv1 = rxv1 / rxv
nrxv2 = rxv2 / rxv
nrxv3 = rxv3 / rxv


! parametre p=a de la parabole
! ----------------------------

kep%a = parametre      !  p      = parametre = rxv**2/mu = 2 * distance au perigee


! excentricite
! ------------

kep%e = e

! inclinaison sur le plan equatorial kep%i
! ----------------------------------------

rxvsxi = sqrt(rxv1*rxv1+rxv2*rxv2)!    avec rxvsxi non nul si inclinaison non nulle
sxi = rxvsxi/rxv                  !    sinus(inclinaison)
cxi = nrxv3                       !    cosinus(inclinaison)


if (sxi < pm_eps_equa) then!         orbite equatoriale
   retour = pm_err_i_equa
   go to 6000
end if

call mu_angle2(cxi,sxi,kep%i,code_retour)!    calcul de l'inclinaison par appel a mu_angle2
!    (resultat dans [0,pi] car sin(inclinaison) > 0)
if (code_retour%valeur == pm_err_vect_nul)  then
   retour = pm_err_cni   
   go to 6000
end if

! longitude du noeud ascendant
! ----------------------------

rsicgo = - rxv2
rsisgo =   rxv1

call mu_angle2(rsicgo,rsisgo,kep%gom,code_retour)
if (code_retour%valeur == pm_err_vect_nul)  then
   retour = pm_err_cni   
   go to 6000
end if


! argument du perigee
! -------------------

!     perigee + anomalie vraie
aspov = pos_car(3)
acpov = nrxv1*pos_car(2)-nrxv2*pos_car(1)
call mu_angle2(acpov, aspov, pov, code_retour)
if (code_retour%valeur == pm_err_vect_nul)  then
   retour = pm_err_cni   
   go to 6000
end if
!     anomalie vraie
rcav  = parametre - r

rsav  = pos_fois_vit*sqrt(parametre/mu)
call mu_angle2(rcav, rsav, av, code_retour)!     anomalie vraie

if (code_retour%valeur == pm_err_vect_nul)  then
   retour = pm_err_cni   
   go to 6000
end if

po     = pov - av
kep%pom = modulo(po,pm_deux_pi)!     d'ou l'argument du perigee


! anomalie moyenne
! ----------------


d     = pos_fois_vit/rxv!     equation de Barker : 6 * xm = 3*d + d**3
                        !                         d = tan(anomalie vraie /2)

kep%M= d*(0.5_pm_reel + d*d/6._pm_reel)

! Jacobienne
! ----------
if (present(jacob))  then

   !     calcul derivees
   !     ***************


   ! calcul derivees intermediaires
   ! ------------------------------

   ! derivees normes vecteurs position, vitesse, et r x v
   drdx (1:3) = pos_car(:)/r
   drdx (4:6) = 0._pm_reel

   drxv1(1) = 0._pm_reel
   drxv1(2) =  vit_car(3)
   drxv1(3) = -vit_car(2)
   drxv1(4) = 0._pm_reel
   drxv1(5) = -pos_car(3)
   drxv1(6) =  pos_car(2)

   drxv2(1) = -vit_car(3)
   drxv2(2) = 0._pm_reel
   drxv2(3) =  vit_car(1)
   drxv2(4) =  pos_car(3)
   drxv2(5) = 0._pm_reel
   drxv2(6) = -pos_car(1)

   drxv3(1) =  vit_car(2)
   drxv3(2) = -vit_car(1)
   drxv3(3) = 0._pm_reel
   drxv3(4) = -pos_car(2)
   drxv3(5) =  pos_car(1)
   drxv3(6) = 0._pm_reel

   drxv(:) = drxv1(:)*nrxv1+drxv2(:)*nrxv2+drxv3(:)*nrxv3

   ! derivees produit scalaire
   dpos_fois_vit(1:3)= vit_car(:)
   dpos_fois_vit(4:6)= pos_car(:)

   rxvsmu = 2._pm_reel*rxv/mu
   dpdx(:) = rxvsmu*drxv(:)   ! calcul derivees du parametre p
   dedx(:)= 0._pm_reel        ! calcul derivees de l'excentricite e
   dxidx(:) = (cxi*drxv(:) - drxv3(:))/rxvsxi   ! calcul derivees inclinaison
   rxvsi2 = rxvsxi*rxvsxi
   dgodx(:) = (rxv1*drxv2(:) - rxv2*drxv1(:))/rxvsi2   ! calcul derivees noeud ascendant

   ! calcul derivees perigee
   ! -----------------------
   !     po = pov - av --> dpodx(:)=dpovdx(:)-davdx(:)

   !         r*sxi * spov = aspov = pos_car(3)
   !         r*sxi * cpov = acpov

   rsxi2 = (r*sxi)**2
   dacpov(:)  = (drxv1(:)*pos_car(2) - drxv2(:)*pos_car(1) - acpov * drxv(:) )/ rxv                 
   dacpov(1)  = dacpov(1) - nrxv2
   dacpov(2)  = dacpov(2) + nrxv1

   dpovdx(:)  = -pos_car(3)*dacpov(:)/rsxi2   !         avec rsxi2 non nul si inclinaison non nulle et r non nul
   dpovdx(3)  = dpovdx(3) + acpov/rsxi2

   !     r*cav = rcav = p - r
   !     r*sav = rsav = pos_fois_vit*sqrt(p/mu) = pos_fois_vit*rxv/mu

   r2   = r*r
   drsav(:)  = (dpos_fois_vit(:)*rxv + pos_fois_vit*drxv(:))/mu
   davdx(:)  = (-rsav*(dpdx(:)-drdx(:)) + rcav*drsav(:))/r2


   dpodx(:)   = dpovdx(:) - davdx(:)


   ! calcul derivees anomalie moyenne
   ! --------------------------------
   !     derivees de d = pos_fois_vit/rxv
   dddx(:) = (dpos_fois_vit(:) - d*drxv(:)) / rxv

   cof = (1._pm_reel+ d*d)*0.5_pm_reel
   dxmdx(:)= cof * dddx(:)


   ! affectation de la jacobienne de la transformation
   ! -------------------------------------------------


   jacob(1,:)=dpdx(:)
   jacob(2,:)=dedx(:)
   jacob(3,:)=dxidx(:)
   jacob(4,:)=dpodx(:)
   jacob(5,:)=dgodx(:)
   jacob(6,:)=dxmdx(:)

end if

6000 continue

end subroutine mvi_car_kep_parab
