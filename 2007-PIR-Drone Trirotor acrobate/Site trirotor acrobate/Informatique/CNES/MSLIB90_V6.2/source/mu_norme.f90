subroutine mu_norme (vect, norme, code_retour ,vect_norme)

! (C) Copyright CNES - MSLIB - 1998

!************************************************************************
!
! But:  Norme euclidienne d'un vecteur dans l'espace
! ===
!
! Historique:
! ==========
!   + Version 1.0 (SP 204 ed01 rev00): creation a partir de la routine MUNORM de la MSLIB f77
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!
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

include 'arg_mu_norme.h'

! Autres declarations
! -------------------

real(pm_reel) :: presque_zero   !variable de test des reels
real(pm_reel) :: norme_carre    !carre de la norme du vecteur vect en entree
real(pm_reel) :: norme_vect     !norme du vecteur vect en entree (variable intermediaire)

intrinsic tiny, sqrt, present, dot_product


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mu_norme.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mu_norme.f90,v 1.7 2003/10/14 12:53:48 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
code_retour%valeur = pm_OK

! initialisation constante de test
!.................................

presque_zero = tiny(1._pm_reel)  ! recherche du plus petit reel positif non nul

! -----------------------------
! calcul de la norme du vecteur 
! -----------------------------
norme_carre = dot_product(vect,vect)
norme_vect = sqrt(norme_carre)
norme = norme_vect

! --------------------------------------------
! calcul optionnel du vecteur norme vect_norme
! --------------------------------------------

if (present(vect_norme)) then          !     Calcul du vecteur norme.
   if (norme_vect < presque_zero) then !     test si la norme = 0
      code_retour%valeur = pm_err_vect_nul
      go to 6000
   else
      vect_norme(:) = vect(:)/norme_vect
   end if
end if

6000 continue

code_retour%routine = pm_num_mu_norme
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mu_norme
