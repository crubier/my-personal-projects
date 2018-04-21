subroutine me_lyddane_moy ( r_equa, cn0, osc, moy, code_retour )

! (C) Copyright CNES - MSLIB - 2004

!************************************************************************
!
! But:  Calcul des parametres moyens du modele d'extrapolation d'orbite de Lydanne
! ===
!
! Note d'utilisation: les unites de distance sont en metres OBLIGATOIREMENT 
! ==================  (pour mu, r_equa, et a)
!                     
!                     l'excentricite doit appartenir a [ 0. , 0.9 [
!                     le domaine d'erreur est          < 0. et >= 0.9
!
!                     l'inclinaison  doit appartenir a [ 0. , pi ]
!                     et non proches des inclinaisons critiques definies par
!                     (pm_i_critique_non_retro, pm_i_critique_retro) a pm_eps_i_critique pres.
!
!
! Historique:
! ==========
!   + Version 6.0 (SP 620 ed01 rev00): creation a partir de la routine me_eck_hech_moy 
!
!************************************************************************


! Modules
! =======

use int_mslib_me_lyddane
use int_mslib_mv_kep_cir_equa
use int_mslib_mv_cir_equa_kep

use precision_mslib
use math_mslib
use test_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_me_lyddane_moy.h'

! Autres declarations
! ===================
integer                     :: n                           ! nombre d'iterations
type(tm_orb_cir_equa)       :: moy_local, moy_sortie, oscn ! variables intermediaires   
type(tm_orb_cir_equa)       :: ecart, ecart_admi           ! ecarts et seuils entre les parametres adaptes
type(tm_jour_sec)           :: date                        ! date a laquelle on extrapole les parametres
logical                     :: convergence                 ! variable logique a vrai si tests de convergence verifies
                                                          
integer, parameter          :: nmax = 51       ! nombre maximum d'iterations admises

real(pm_reel), parameter    :: mu = 1._pm_reel ! valeur inutile pour appel a me_lyddane

real(pm_reel)               :: eps1000                     ! epsilon pour test de convergence
type(tm_code_retour)        :: code_retour_local

character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
     '@(#) Fichier MSLIB me_lyddane_moy.f90: derniere modification V6.0 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: me_lyddane_moy.f90,v 1.11 2004/06/16 08:17:01 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
code_retour%valeur = pm_OK

! autres initialisations
! ......................
n           = 1           ! initialisation du numero d'iterations
convergence = .false.     ! initialisation de l'indicateur de convergence

eps1000     = 1000._pm_reel  * epsilon(1._pm_reel) ! epsilon pour test de convergence

! la date est inutile dans l'appel a me_lyddane: on l'initialise a 1 j 0 sec, 
! ainsi que mu (initialisable en parameter). 
date%jour   = 1_pm_entier
date%sec    = 0._pm_reel
                          


! initialisation des moyens aux osculateurs en entree et passage des angles dans l'intervalle [0,2*pi]
! ....................................................................................................

moy_local%a     = osc%a
moy_local%ex    = osc%ex
moy_local%ey    = osc%ey
moy_local%ix    = osc%ix
moy_local%iy    = osc%iy
moy_local%pso_M = modulo(osc%pso_M,pm_deux_pi)

ecart_admi%a  = eps1000*(1._pm_reel + abs(moy_local%a))
ecart_admi%ex = eps1000*(1._pm_reel + abs(moy_local%ex))
ecart_admi%ey = eps1000*(1._pm_reel + abs(moy_local%ey))
ecart_admi%ix = eps1000*(1._pm_reel + abs(moy_local%ix))
ecart_admi%iy = eps1000*(1._pm_reel + abs(moy_local%iy))
ecart_admi%pso_M = eps1000*(1._pm_reel + abs(moy_local%pso_M))

! debut d'iteration
! .................
do while ((n < nmax) .and. (.not.convergence))  ! iterations tant que le nombre maximum d'iterations n'est pas atteint et convergence non atteinte


   !  calcul des osculateurs correspondant aux moyens (a la meme date)
   call me_lyddane( mu, r_equa, cn0, date, moy_local, date, moy_sortie, code_retour_local, osc_t2=oscn )
   if (code_retour_local%valeur /= pm_OK)  then
      code_retour%valeur = code_retour_local%valeur
      if (code_retour_local%valeur < pm_OK)  go to 6000
   end if

   !  calcul des ecarts entre parametres osculateurs calcules et ceux de depart. 
   !  Ces ecarts sont ramenes sur [-pi,pi].
   ecart%a     = osc%a - oscn%a
   ecart%ex    = osc%ex - oscn%ex
   ecart%ey    = osc%ey - oscn%ey
   ecart%ix    = osc%ix - oscn%ix
   ecart%iy    = osc%iy - oscn%iy
   ecart%pso_M = osc%pso_M - oscn%pso_M

   if (ecart%pso_M < (- pm_pi)) then
      ecart%pso_M = ecart%pso_M + pm_deux_pi
   else if (ecart%pso_M > pm_pi) then
      ecart%pso_M = ecart%pso_M - pm_deux_pi
   end if

   !  test de convergence
   if (     (abs(ecart%a)  <= ecart_admi%a)  .and. (abs(ecart%ex)    <= ecart_admi%ex)    &
      .and. (abs(ecart%ey) <= ecart_admi%ey) .and. (abs(ecart%ix)    <= ecart_admi%ix)    &
      .and. (abs(ecart%iy) <= ecart_admi%iy) .and. (abs(ecart%pso_M) <= ecart_admi%pso_M) ) then

      convergence = .true. ! convergence atteinte

   else
      !  reinitialisation des elements moyens
      moy_local%a     = moy_local%a+ecart%a
      moy_local%ex    = moy_local%ex+ecart%ex
      moy_local%ey    = moy_local%ey+ecart%ey
      moy_local%ix    = moy_local%ix+ecart%ix
      moy_local%iy    = moy_local%iy+ecart%iy
      moy_local%pso_M = modulo(moy_local%pso_M+ecart%pso_M, pm_deux_pi)

   end if

   n = n + 1

end do


if (.not.convergence) code_retour%valeur = pm_err_conv_lyddane  ! pas de convergence 

! affectation des parametres de sortie
! ....................................
moy%a     = moy_local%a
moy%ex    = moy_local%ex
moy%ey    = moy_local%ey
moy%ix    = moy_local%ix
moy%iy    = moy_local%iy
moy%pso_M = moy_local%pso_M

6000 continue

code_retour%routine = pm_num_me_lyddane_moy
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine me_lyddane_moy
