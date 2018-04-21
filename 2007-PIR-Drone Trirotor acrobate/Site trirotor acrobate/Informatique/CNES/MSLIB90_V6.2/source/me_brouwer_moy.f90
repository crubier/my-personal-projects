
subroutine me_brouwer_moy (r_equa, cn0, ecart_admi, osc, moy, code_retour)

! (C) Copyright CNES - MSLIB - 1998-2003

!************************************************************************
!
! But:  Calcul des parametres moyens du modele de Brouwer
! ===
!
! Note d'utilisation:  Les valeurs suivantes sont recommandees pour les ecarts admissibles sur les parametres:
! ==================
!                      1) sur le demi grand axe : ecart_admi(a) = 0.01 m
!                      2) sur l'excentricite :    ecart_admi(e) = ecart_admi(a)/(2*osc(a))
!                      3) sur l'inclinaison :     ecart_admi(i) = ecart_admi(a)/osc(a)
!
!                      L'excentricite  doit etre superieure >= 10e-4 et inferieure a 0.9.
!                      Le domaine d'erreur est ................. [ 0E+0 , 1E-4 [ et >= 9E-1.
!                      Le domaine de precision degradee est .... [ 1E-4 , 1E-2 [.
!                      Le domaine d'utilisation du modele est .. [ 1E-2 , 9E-1 [.
!
!                      L'inclinaison  doit etre >0. et < pi et non proches des inclinaisons critiques
!                      ( pm_i_critique_non_retro, pm_i_critique_retro ) a pm_eps_i_critique pres.
!                      De plus si 0 < i < 0.018 radian ( environ 1 degre ) alors on est egalement en mode degradee.
!
! Historique:
! ==========
!   + Version 1.0 (SP 206 ed01 rev00): creation a partir de la routine MEBR5M de la MSLIB f77
!   + Version 2.0 (FA 352 ed01 rev00): revision du test sur l'inclinaison critique - ajout de commentaire
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!
!************************************************************************


! Modules
! =======
use math_mslib
use phys_mslib
use test_mslib
use int_mslib_me_brouwer

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib




! Declarations
! ============
implicit none

include 'arg_me_brouwer_moy.h'

! Autres declarations
! -------------------

integer                  :: n               ! nombre d'iterations 
type(tm_orb_kep)         :: oscn, ecart     ! parametres osculateurs calcules et ecarts entre le donne et le calcule
type(tm_orb_kep)         :: moy_sortie      ! parametres moyens en sortie de me_brouwer ( variable inutilisee)
logical                  :: converge        ! variable logique a vrai si tests de convergence verifies
type(tm_jour_sec)        :: date            ! variable a affecter pour l'appel a me_brouwer, mais inutile
real(pm_reel)            :: mu              ! idem
real(pm_reel), dimension(4)    :: ecart_ang ! tableau intermediaire contenant les ecarts angulaires
integer                  :: i               ! indice de boucle
type(tm_orb_kep)         :: moy_int         ! pour calculs intermediaires avec valeurs de sortie

integer,parameter        :: nmax = 51       ! nombre max d'iterations

intrinsic modulo, abs


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
     '@(#) Fichier MSLIB me_brouwer_moy.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: me_brouwer_moy.f90,v 1.9 2003/10/14 12:46:47 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
code_retour%valeur = pm_OK


!     ---------------------------------------------------------------
! 1. Affectation initiale des moyens moy aux osculateurs en entree et
!    passage des angles dans l'intervalle [0,2*pi]
!     ---------------------------------------------------------------

moy_int%a = osc%a
moy_int%e = osc%e
moy_int%i   =  osc%i
moy_int%pom =  modulo(osc%pom, pm_deux_pi)
moy_int%gom =  modulo(osc%gom, pm_deux_pi)
moy_int%M   =  modulo(osc%M, pm_deux_pi)


! Initialisations
! ---------------
converge = .false. 
! la date est inutile dans l'appel a me_brouwer : on l'initialise a 1, ainsi que mu. 
date%jour = 1_pm_entier
date%sec  = 0._pm_reel
mu = 1._pm_reel

   !     =================
   !     debut d'iteration
   !     =================
n=1
do while (n<=nmax .and..not.converge)  !Iterations tant que le nombre maximum d'iterations n'est pas atteint

   !        --------------------------------------------------
   !    2. calcul des osculateurs correspondant aux moyens
   !        --------------------------------------------------

   call me_brouwer(mu, r_equa, cn0, date, moy_int, date, moy_sortie, code_retour, osc_t2=oscn)
   if (code_retour%valeur < pm_OK) go to 6000


   !        ----------------------------------------------------------
   !    3. calcul des ecarts entre osculateurs calcules et ceux en
   !       entree.on ramene ces ecarts sur l'intervalle [-pi,pi]
   !        ---------------------------------------------------------------

   ecart%a = osc%a-oscn%a
   ecart%e = osc%e-oscn%e
   ecart%i = osc%i-oscn%i
   ecart%pom = osc%pom-oscn%pom
   ecart%gom = osc%gom-oscn%gom
   ecart%M   = osc%M-oscn%M

   !on ramene eventuellement entre 0 et pi ou 0 et -pi les valeurs angulaires du bulletin

   ecart_ang = (/ecart%i,ecart%pom,ecart%gom,ecart%M/)
   do i = 1,4
      if (ecart_ang(i) < - pm_pi) then
         ecart_ang(i) = ecart_ang(i) + pm_deux_pi
      else if (ecart_ang(i) > pm_pi) then
         ecart_ang(i) = ecart_ang(i) - pm_deux_pi
      end if
   end do
   ecart%i   = ecart_ang(1)
   ecart%pom = ecart_ang(2)
   ecart%gom = ecart_ang(3)
   ecart%M   = ecart_ang(4)


   !        ----------------------
   !    4. test de convergence
   !        ----------------------


   if (abs(ecart%a) <= ecart_admi%a .and. abs(ecart%e) <= ecart_admi%e .and. abs(ecart%i) <= ecart_admi%i    &
        .and. abs(ecart%pom) <= ecart_admi%pom .and. abs(ecart%gom) <= ecart_admi%gom .and. abs(ecart%M) <= ecart_admi%M ) then
      converge = .true.! convergence atteinte

   else

      !reinitialisation des elements moyens et on ramene les valeurs angulaires entre 0 et 2*pi

     
      moy_int%a = moy_int%a+ecart%a
      moy_int%e = moy_int%e+ecart%e
      moy_int%i = modulo(moy_int%i+ecart%i, pm_deux_pi)
      moy_int%pom =  modulo(moy_int%pom+ecart%pom, pm_deux_pi)
      moy_int%gom =  modulo(moy_int%gom+ecart%gom, pm_deux_pi)
      moy_int%M   =  modulo(moy_int%M+ecart%M, pm_deux_pi)

   end if

   n = n+1

end do

if (.not.converge)   code_retour%valeur = pm_err_conv_brouwer   ! pas de convergence dans le nombre imparti d'iterations compte
! tenu des ecarts admissibles demandes

6000 continue

! reaffectation des eventuelles sorties
moy%a = moy_int%a
moy%e = moy_int%e
moy%i = moy_int%i
moy%pom = moy_int%pom
moy%gom = moy_int%gom
moy%M = moy_int%M


code_retour%routine = pm_num_me_brouwer_moy
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '
end subroutine me_brouwer_moy
