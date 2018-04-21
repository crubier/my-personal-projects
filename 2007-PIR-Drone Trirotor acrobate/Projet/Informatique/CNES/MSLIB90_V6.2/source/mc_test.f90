subroutine mc_test ( code_retour, eps_cir, eps_parab, eps_equa, eps_i_critique )

! (C) Copyright CNES - MSLIB - 1998-2003

!************************************************************************
!
! But:  Affectation des constantes physiques de test sur l'excentricite et l'inclinaison
! ===
!
! Historique:
! ==========
!   + Version 1.0 (SP 209 ed01 rev00): creation a partir de la routine MCONST de la MSLIB f77
!   + Version 2.0 (DE 400 ed01 rev00): ajout de la sortie eps_i_critique
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!************************************************************************


! Modules
! =======
use test_mslib

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mc_test.h'

! Autres declarations
! -------------------

intrinsic present

character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mc_test.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mc_test.f90,v 1.7 2003/10/14 12:45:55 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
code_retour%valeur = pm_OK

! Affectation des valeurs des constantes demandees

if (present(eps_cir))        eps_cir        = pm_eps_cir         ! epsilon de test pour l'orbite circulaire
if (present(eps_parab))      eps_parab      = pm_eps_parab       ! epsilon de test pour l'orbite parabolique
if (present(eps_equa))       eps_equa       = pm_eps_equa        ! epsilon de test pour l'orbite equatoriale
if (present(eps_i_critique)) eps_i_critique = pm_eps_i_critique  ! epsilon de test pour l'inclinaison critique

6000 continue

code_retour%routine = pm_num_mc_test
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mc_test
