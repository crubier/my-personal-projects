subroutine mt_def_topo_N (lat, long, vect_i, vect_j, vect_k, code_retour)

! (C) Copyright CNES - MSLIB - 1998-2003

!************************************************************************
!
! But:  DEFinition des cosinus directeurs d'un repere TOPOcentrique Nord (convention axe Ox vers le Nord).
! ===
!
! Historique:
! ==========
!   + Version 1.0 (SP 251 ed01 rev00): creation a partir de la routine MVCAST de la MSLIB f77
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!************************************************************************


! Modules
! =======

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mt_def_topo_N.h'

! Autres declarations
! -------------------

intrinsic cos, sin


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mt_def_topo_N.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mt_def_topo_N.f90,v 1.7 2003/10/14 12:52:28 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
code_retour%valeur = pm_OK


! --------------------------------------------------------------
! calcul des composantes de i : horizontale locale dirigee vers
!                               le nord
!             i = (-sin(lat)cos(long),-sin(lat)sin(long),cos(lat))
! --------------------------------------------------------------

vect_i (1) = - sin (lat) * cos (long)
vect_i (2) = - sin (lat) * sin (long)
vect_i (3) =   cos (lat)

!-----------------------------------------------------------------
! calcul des composantes de j : tangente au parallele local dirigee
!                               vers l'ouest
!             j = (sin(long),-cos(long),0)
!-----------------------------------------------------------------

vect_j (1) =   sin (long)
vect_j (2) = - cos (long)
vect_j (3) = 0._pm_reel

!------------------------------------------------------------
! calcul des composantes de k : verticale locale
!             k = (cos(lat)cos(long),cos(lat)sin(long),sin(lat))
!------------------------------------------------------------

vect_k (1) = cos (lat) * cos (long)
vect_k (2) = cos (lat) * sin (long)
vect_k (3) = sin (lat)

6000 continue

code_retour%routine = pm_num_mt_def_topo_N
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mt_def_topo_N
