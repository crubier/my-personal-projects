subroutine mv_kepler_std (anom_M, e, anom_E, code_retour)

! (C) Copyright CNES - MSLIB - 1998-2003

!************************************************************************
!
! But:  Resolution de l'equation de Kepler, orbite elliptique.
! ===
!
! Historique:
! ==========
!   + Version 1.0 (SP 208 ed01 rev00): creation a partir de la routine MVRXKN de la MSLIB f77
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!************************************************************************


! Modules
! =======
use test_mslib
use math_mslib

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib



! Declarations
! ============
implicit none

include 'arg_mv_kepler_std.h'

! Autres declarations
! -------------------

real(pm_reel) :: eps100             !     nom constante eps    
real(pm_reel) :: pi                 !     pi
real(pm_reel) :: eps_cir, eps_parab !     epsilons de test pour orbites circulaire ou parabolique
real(pm_reel) :: e0,ei,eip1         !     valeurs initiale ,courante et suivante pour resolution iterative
real(pm_reel) :: az                 !     variable intermediaire az pour initialisation de encke
real(pm_reel) :: cosM,sinM          !     variables intermediaires de calcul de cosinus et sinus de M
real(pm_reel) :: rapport, az2       !     variables intermediaires de calcul
real(pm_reel) :: anom_M0            !     anomalie moyenne proche de 0
real(pm_reel) :: err1, err2         !     criteres de convergence

integer       :: iter               !     indice d'iteration
integer       :: kpi                !     multiple de pi

integer, parameter :: max_nb_iter = 20 !  nombre maximum d'iterations



intrinsic epsilon, sin, cos, abs, sqrt, real, mod, nint, max


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mv_kepler_std.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mv_kepler_std.f90,v 1.7 2003/10/14 12:54:48 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
code_retour%valeur = pm_OK

eps100  =  100._pm_reel  * epsilon(1._pm_reel)                 ! constante eps pour les reels

pi = pm_pi  ! recuperation de la valeur de pi
! recuperation des epsilons de test sur l'excentricite
eps_cir = pm_eps_cir
eps_parab = pm_eps_parab


! controle de l'excentricite ( e dans [0,1[)
! ===========================================
if (e < 0._pm_reel) then                   ! excentricite negative
   code_retour%valeur = pm_err_e_negatif
   go to 6000
end if

if (e > (1._pm_reel-eps_parab)) then       ! orbite parabolique ou hyperbolique
   code_retour%valeur = pm_err_e_non_ellip
   go to 6000
end if

! traitement des cas de fonctionnement non optimal:     exc < eps_cir (orbite circulaire),    sin(M) < 100*eps
! ==========================================================================================================


if (e < eps_cir)  then !     orbite circulaire : pas de code retour necessaire
   anom_E = anom_M
   go to 6000
end if

sinM = sin(anom_M)     !     calcul du sinus de l'anomalie moyenne
cosM = cos(anom_M)     !     calcul du cosinus de l'anomalie moyenne

if (abs(sinM) < eps100) then    !     M est "presque" un multiple de pi: M = M0 + kpi.pi
                                !                                        avec M0 nul ou proche de 0
   kpi = nint(anom_M/pi)
   anom_M0 = anom_M - real(kpi, kind=pm_reel)*pi

   if (mod(kpi,2) == 0) then   ! determination de la parite de kpi
      anom_E = real(kpi, kind=pm_reel)*pi + anom_M0/(1._pm_reel - e)
   else
      anom_E = real(kpi, kind=pm_reel)*pi + anom_M0/(1._pm_reel + e)
   end if

   go to 6000
end if

!initialisation de encke
!=======================
!
rapport = (e - cosM) / sinM
az = e / sqrt (1._pm_reel+(rapport*rapport))
!
if (sinM < 0._pm_reel)  az = -az
!
az2 = az*az
e0 = anom_M + az - ( az2*az2*cosM*(1._pm_reel-e*e)/(6._pm_reel*sinM) )

!resolution iterative par methode de newton
!    f(x) = 0
!    xi+1 = xi - (f(xi) / f'(xi))
!==========================================

eip1 = e0         !
iter = 0          !  Initialisations avant boucle do while
err1 = 1._pm_reel !
err2 = 1._pm_reel !


do while ((err1 > eps100) .and. (err2 > eps100).and.(iter /= max_nb_iter))
   ei = eip1
   iter = iter + 1
   
   eip1 = ei - ((anom_M + e*sin(ei) - ei) / (e*cos(ei) - 1.0_pm_reel))   !        calcul pour l'iteration courante
   err1 = abs(eip1-ei)/max(abs(eip1),1.0_pm_reel)   !        calcul du residu
   err2 = abs(anom_M + e*sin(eip1) - eip1)/max(abs(anom_M),1.0_pm_reel)

end do

if ((err1 > eps100) .and. (err2 > eps100)) then !     pas de convergence au bout du nombre maximum d'iterations
   code_retour%valeur = pm_err_conv_kepler_ellip
   go to 6000
end if

! affectation du resultat

anom_E = eip1

6000 continue

code_retour%routine = pm_num_mv_kepler_std
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mv_kepler_std
