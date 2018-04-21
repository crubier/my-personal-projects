subroutine mri_eclip_M_equa_M (model, jul1950_t1, jul1950_t2, mat_pass, retour)

! (C) Copyright CNES - MSLIB - 1998-2003

!************************************************************************
!
! But:  Calcul de la matrice de passage du repere ECLIPtique MOYen a T1 au repere EQUAtorial MOYen a T2.
! ===
!
! Note d'utilisation: - Routine interne
! ==================  
!
! Historique:
! ==========
!   + Version 1.0 (SP 272 ed01 rev00): creation a partir de la routine MRCQMO de la MSLIB f77
!   + Version 2.0 (DE 362 ed01 rev00): suppression des commentaires sur la limitation sur les dates et des codes retour
!                                      utilisation de md_joursec_jourfrac, revision clef de modele
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!************************************************************************


! Modules
! =======

use math_mslib
use int_mslib_mri_eclip_moy_t1_t2
use int_mslib_md_joursec_jourfrac
use code_modeles_mslib   ! contient toutes les valeurs possibles pour "model"

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mri_eclip_M_equa_M.h'

! Autres declarations
! -------------------

real(pm_reel)                  ::  sec_rad                       ! 3600 * pi/180.
real(pm_reel), dimension(3,3)  ::  mat_pass1, mat_pass2          ! matrices de passage intermediaires
real(pm_reel), parameter       ::  delta_te_tai = 32.184_pm_reel ! ecart en secondes entre le temps des ephemerides et le TAI
real(pm_reel)                  ::  t2                            ! date exprimee en jours juliens fractionnaires
real(pm_reel), parameter       ::  tl0 = 18262.5_pm_reel         ! initialisation de l'epoque de base du modele Lieske = j2000.0
real(pm_reel)                  ::  t, ta2, ta3                   ! temps intermediaires
real(pm_reel)                  ::  e0, eps                       ! obliquite moyenne a l'epoque de base et obliquite a la date cherchee
real(pm_reel)                  ::  ceps, seps                    ! sinus et cosinus de l'obliquite eps
integer                        ::  modele_precession             ! indicateur du modele de precession correspondant a "model" en entree
type(tm_jour_sec)              ::  jul1950_temp                  ! variable temporaire pour appel md_joursec_jourfrac
type(tm_code_retour)           ::  code_retour_local

! coefficients pour le modele de Lieske
!    ******************************************************************
!    les coefficients de l'expression de l'obliquite sont tires de :
!    "connaissance des temps" p.xxx   1984
!     ******************************************************************
real(pm_reel), dimension(3), parameter  :: el0  = (/23._pm_reel,26._pm_reel,21.448_pm_reel/)      ! coeff el0
real(pm_reel), dimension(3), parameter  :: epsl = (/-468.150_pm_reel,-0.059_pm_reel,1.813_pm_reel/) ! coeff epsl

intrinsic cos, sin, matmul


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mri_eclip_M_equa_M.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mri_eclip_M_equa_M.f90,v 1.8 2003/10/14 12:50:00 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
retour = pm_OK

if (model == pm_lieske) then 

   ! Calcul de la matrice de passage de l'ecliptique moyen a t1 a l'equateur moyen a t2
   ! avec le modele de precession de Lieske (epoque de base : J2000)

   sec_rad = pm_deg_rad/3600._pm_reel!     . . . initialisation de la valeur sec_rad

   !     . . . calcul de la date en jours juliens cnes fractionnaires
   jul1950_temp%jour = jul1950_t2%jour
   jul1950_temp%sec  = jul1950_t2%sec + delta_te_tai
   call md_joursec_jourfrac ( jul1950_temp, t2, code_retour_local )   ! code_retour_local%valeur = 0 est le seul retour possible => non teste

   ! ------------------------------------------------------------------------------------
   ! calcul de la matrice de passage de l'ecliptique moyen a t1 a l'ecliptique moyen a t2
   ! ------------------------------------------------------------------------------------

   modele_precession = pm_lieske
   call mri_eclip_moy_t1_t2 (modele_precession, jul1950_t1, jul1950_t2, mat_pass1, retour)
   ! pas de test de retour car il ne peut etre que nul (controles deja effectues)


   ! ---------------------------------------------------------
   ! calcul de l'obliquite au temps t2 par le modele de Lieske
   ! ---------------------------------------------------------

   t=(t2-tl0)/365250._pm_reel               !        t  en milliers d'annees juliennes de 365250 jours

   ta2=t*t
   ta3=ta2*t

   !     epsl est en secondes d'arc
   !     el0(1) en degres
   !     el0(2) en minutes
   !     el0(3) en secondes

   e0 = el0(1)*pm_deg_rad + el0(2)*pm_deg_rad/60._pm_reel +el0(3)*sec_rad
   eps = e0 + (epsl(1)*t+epsl(2)*ta2+epsl(3)*ta3)*sec_rad  !     l'obliquite eps est calculee en radians


   ! -----------------------------------------------------------------------------------------------
   ! calcul de la matrice de passage du repere ecliptique moyen a t2 au repere equatorial moyen a t2
   ! (rotation autour de ox d'angle egal a (- obliquite)
   ! -----------------------------------------------------------------------------------------------


   mat_pass2(:,:) = 0._pm_reel


   ceps=cos(eps)
   seps=sin(eps)
   mat_pass2(1,1)=1._pm_reel
   mat_pass2(2,2)=ceps
   mat_pass2(3,2)=seps
   mat_pass2(2,3)=-seps
   mat_pass2(3,3)=ceps


   ! ------------------------------------------------------------------------------------
   ! calcul de la matrice de passage de l'ecliptique moyen a t1 a l'equatorial moyen a t2
   !-------------------------------------------------------------------------------------

   !     . . . il s'agit du produit des 2 matrices mat_pass1 et mat_pass2

   mat_pass(:,:) = matmul(mat_pass2(:,:), mat_pass1(:,:))

else   ! modele inconnu

   retour = pm_err_ind_model

end if

6000 continue

end subroutine mri_eclip_M_equa_M
