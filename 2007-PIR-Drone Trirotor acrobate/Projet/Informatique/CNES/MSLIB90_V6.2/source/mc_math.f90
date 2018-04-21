subroutine mc_math ( code_retour, pi, deux_pi, pi_sur2, deg_rad, rad_deg)

! (C) Copyright CNES - MSLIB - 1998-2003

!************************************************************************
!
! But:  Acces aux constantes mathematiques elementaires
! ===

! Historique:
! ==========
!   + Version 1.0 (SP 210 ed01 rev00): creation a partir de la routine MCONST de la MSLIB f77
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

include 'arg_mc_math.h'

! Autres declarations
! -------------------

intrinsic present


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mc_math.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mc_math.f90,v 1.7 2003/10/14 12:45:34 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
code_retour%valeur = pm_OK

! Affectation des valeurs des constantes demandees

if (present(pi))       pi      = pm_pi
if (present(deux_pi))  deux_pi = pm_deux_pi
if (present(pi_sur2))  pi_sur2 = pm_pi_sur2
if (present(deg_rad))  deg_rad = pm_deg_rad
if (present(rad_deg))  rad_deg = pm_rad_deg

6000 continue

code_retour%routine = pm_num_mc_math
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mc_math
