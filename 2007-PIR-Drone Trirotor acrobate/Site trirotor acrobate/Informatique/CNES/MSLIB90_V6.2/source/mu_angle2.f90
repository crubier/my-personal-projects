subroutine mu_angle2 (x, y, angle, code_retour)

! (C) Copyright CNES - MSLIB - 1998-2003

!************************************************************************
!
! But:  dans le plan, calcul d'un angle connaissant son cosinus et son sinus
! ===
!
! Note d'utilisation:  l'entree x = cosinus(angle) et l'entree y = sinus(angle)
! ==================
!
! Historique:
! ==========
!   + Version 0.1 (SP 145 ed01 rev00): creation a partir de la routine MUANGL de la MSLIB f77
!   + Version 0.1.1 (DE globale 182 ed01 rev00): prise en compte de regles de codage
!   + Version 1.0 (DE globale 217 ed01 rev00): prise en compte des modifications de nommage des
!                                              parametres mathematiques
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!************************************************************************


! Modules
! =======
use math_mslib

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mu_angle2.h'

! Autres declarations
! -------------------

real(pm_reel) :: presque_zero, arctg_angle, s ! variables intermediaires de calcul

intrinsic abs,atan


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mu_angle2.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mu_angle2.f90,v 1.7 2003/10/14 12:52:58 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
code_retour%valeur = pm_OK

! initialisation constante de test
! ................................
presque_zero = tiny(1._pm_reel)  ! recherche du plus petit reel positif non nul



! Controle des parametres d'entree (x=y=0)
! ========================================

if ((abs(x) <= presque_zero) .and. (abs(y) <= presque_zero)) then
   code_retour%valeur = pm_err_vect_nul
   angle = 0._pm_reel
   go to 6000
end if


! Calcul arctg(s) avec s = min( | x | , | y |) / max( | x | , | y |)
! =====================================================================


if (abs(x) < abs(y)) then  ! si   | x | < | y | :  s = | x | / | y |  et  angle = pi/2 - arctg(s)

   s = abs(x) / abs(y)
   arctg_angle = pm_pi_sur2 - atan(s)

else   ! si | x | > | y | :   s = | y | / | x |  et angle = arctg(s)

   s = abs(y) / abs(x)
   arctg_angle = atan(s)

end if

! Determination signe et quadrant de l'angle suivant les signes de x et y
! =======================================================================

if (y >= 0._pm_reel) then    ! y > ou = 0

   angle = arctg_angle           ! si y >= 0 et x >= 0: angle = angle

   if (x < 0._pm_reel) then
      angle = pm_pi - arctg_angle   ! si y >= 0 et x < 0: angle = pi - angle
   end if

else    !  y < 0

   if (x > 0._pm_reel) then ! y < 0 et x > 0

      angle = pm_deux_pi - arctg_angle ! si y < 0 et x > 0: angle = 2pi - angle

   else ! y < 0 et x <= 0

      angle = pm_pi + arctg_angle      ! si y < 0 et x <= 0: angle = pi + angle

   end if

end if

6000 continue

code_retour%routine = pm_num_mu_angle2
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mu_angle2
