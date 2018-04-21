subroutine mv_kep_car (mu, kep, pos_car, vit_car, code_retour, jacob)

! (C) Copyright CNES - MSLIB - 1998-2003

!************************************************************************
!
! But: Passage des parametres KEPleriens aux parametres CARtesiens. 
! ===
!
! Note d'utilisation: 1) Applicable aux orbites circulaires, elliptiques, hyperboliques, et paraboliques, et equatoriales ou non.
! ==================  2) kep%a represente en entree le demi grand axe dans le cas de l'ellipse et de l'hyperbole, 
!                        et le parametre p (2 x la distance au foyer) dans le cas de la parabole.
!                     3) Les unites en entree doivent etre coherentes entre elles. Ex.: pos_car en metres, vit_car en m/s,
!                        mu en m**3/s**2, et les parametres kepleriens seront en metres et radians.
!                     4) L'element (i,j) de la jacobienne correspond a la derivee partielle du parametre cartesien numero i
!                        par rapport a la derivee partielle du parametre keplerien numero j.
!                     5) La transformation inverse se fait par mv_car_kep sauf dans les cas d'orbite elliptiques equatoriales
!                        et/ou circulaires: voir alors mv_car_cir_equa (circulaire ET equatoriale, mv_car_cir (circulaire) ou
!                        mv_car_equa (equatoriale). 
!
! Historique:
! ==========
!   + Version 1.0 (SP 230 ed01 rev00): creation a partir de la routine MVOSRD de la MSLIB f77
!   + Version 2.0 (FA 360 ed01 rev00): ajout de commentaires sur le parametre p
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!************************************************************************


! Modules
! =======
use int_mslib_mvi_kep_car_ellip
use int_mslib_mvi_kep_car_hyperb
use int_mslib_mvi_kep_car_parab

use math_mslib
use test_mslib

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mv_kep_car.h'

! Autres declarations
! -------------------

real(pm_reel)    ::  aoup,exc,ai    !     parametres kepleriens (a ou p,e,angles i)
real(pm_reel)    ::  eps100         !     variable epsilon machine *100


intrinsic epsilon


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mv_kep_car.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mv_kep_car.f90,v 1.7 2003/10/14 12:54:33 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
code_retour%valeur = pm_OK

! autres initialisations
! ......................
aoup   = kep%a
exc    = kep%e
ai     = kep%i

eps100 = 100._pm_reel * epsilon(1._pm_reel)

! controle des donnees
! ====================

if (mu <= eps100) then  
   if (mu < 0._pm_reel) then       ! constante de la gravitation < 0.
      code_retour%valeur= pm_err_mu_negatif
      go to 6000
   else                    ! constante de la gravitation = 0.
      code_retour%valeur= pm_err_mu_nul
      go to 6000
   end if
end if

if (aoup <= eps100) then
   if (aoup < 0._pm_reel) then               ! demi-grand axe ou parametre de la parabole < 0.
      code_retour%valeur= pm_err_a_negatif
      go to 6000
   else                                      ! demi-grand axe ou parametre de la parabole = 0.
      code_retour%valeur= pm_err_a_nul
      go to 6000
   end if
end if

if (exc < 0._pm_reel) then       ! excentricite negative
   code_retour%valeur= pm_err_e_negatif
   go to 6000
end if

if (ai < 0._pm_reel) then        ! inclinaison  negative
   code_retour%valeur = pm_err_i_negatif
   go to 6000
else if(ai > pm_pi) then      ! inclinaison > pi 
   code_retour%valeur= pm_err_i_sup_pi
   go to 6000
end if

!*********************************************************
! passage kepleriens ---> cartesiens selon le type d'orbite
! *********************************************************


if (exc <= (1._pm_reel- pm_eps_parab)) then        !     cas elliptique

   if (present(jacob)) then
      call mvi_kep_car_ellip (kep,mu,pos_car,vit_car,code_retour%valeur,jacob=jacob) ! en retour de mvi_kep_car_ellip: 
   else                                                                       ! seul code_retour%valeur = 0
      call mvi_kep_car_ellip (kep,mu,pos_car,vit_car,code_retour%valeur)      !               = pm_err_conv_kepler_ellip     
   end if


else if (exc >= (1._pm_reel+ pm_eps_parab)) then   !     cas hyperbolique

   if (present(jacob)) then
      call mvi_kep_car_hyperb (kep,mu,pos_car,vit_car,code_retour%valeur,jacob=jacob)
   else                                                                    !  en retour de mvi_kep_car_hyperb:
      call mvi_kep_car_hyperb (kep,mu,pos_car,vit_car,code_retour%valeur)  !  seul code_retour%valeur = 0                
   end if                                                                  !          = pm_err_conv_kepler_hyperb 

else                                      !     cas parabolique ((exc > (1.-pm_eps_parab)).or.(exc < (1.+ pm_eps_parab))

   if (present(jacob)) then
      call mvi_kep_car_parab (kep,mu,pos_car,vit_car,code_retour%valeur,jacob=jacob) !  en retour de mvi_kep_car_parab:
   else
      call mvi_kep_car_parab (kep,mu,pos_car,vit_car,code_retour%valeur)             ! seul code_retour%valeur = 0  possible ici
   end if
   if (code_retour%valeur == 0) code_retour%valeur = pm_warn_e_parab

end if

6000 continue

code_retour%routine = pm_num_mv_kep_car
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mv_kep_car
