subroutine mv_kepler_bar (anom_M, e, anom_E_D, code_retour)

! (C) Copyright CNES - MSLIB - 1998

!************************************************************************
!
! But:  Resolution des equations de KEPLER (ellipse et hyperbole) et de BARker (parabole).
! ===
!
! Historique:
! ==========
!   + Version 1.0 (SP 223 ed01 rev00): creation a partir de la routine MVRYKN de la MSLIB f77
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!
!************************************************************************


! Modules
! =======
use test_mslib

use int_mslib_mv_kepler_std
use int_mslib_mvi_kepler_hyperb
use int_mslib_mvi_barker

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mv_kepler_bar.h'

! Autres declarations
! ------------------

real(pm_reel)    ::   D   !  tangente (anomalie vraie/2)

character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mv_kepler_bar.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mv_kepler_bar.f90,v 1.7 2003/10/14 12:54:38 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
code_retour%valeur = pm_OK

! controle du parametre excentricite (e>0) 
! ------------------------------------------

if (e < 0._pm_reel) then    !   excentricite negative
   anom_E_D = 0._pm_reel
   code_retour%valeur = pm_err_e_negatif
   go to 6000
end if

if (e <= (1._pm_reel- pm_eps_parab)) then  !  cas elliptique : resolution de  E - e * sin(E) = M par appel a mv_kepler_std 
                                           !  en retour de cette routine, seules valeurs possibles du code_retour:
                                           !  0 ou pm_conv_kepler_ellip

   call mv_kepler_std( anom_M, e, anom_E_D, code_retour)
   
else if (e >= (1._pm_reel+ pm_eps_parab))  then    ! cas hyperbolique : resolution de  e * sinh(E) - E = M
   
   call mvi_kepler_hyperb(anom_M, e, anom_E_D, code_retour%valeur)

else      !        (e > (1._pm_reel- pm_eps_parab) .and. e < (1._pm_reel+ pm_eps_parab))
          ! cas parabolique :  resolution de l'equation de BARKER:    6 * M = 3 * D + D**3

   call mvi_barker(anom_M, D, code_retour%valeur)
   if (code_retour%valeur == pm_OK) code_retour%valeur = pm_warn_e_parab
   anom_E_D = D

end if

6000 continue

code_retour%routine = pm_num_mv_kepler_bar
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mv_kepler_bar
