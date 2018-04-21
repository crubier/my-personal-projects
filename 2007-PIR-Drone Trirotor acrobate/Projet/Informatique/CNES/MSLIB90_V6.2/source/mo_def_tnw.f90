subroutine mo_def_tnw (pos_car, vit_car, t, n, w, code_retour)

! (C) Copyright CNES - MSLIB - 1999-2003

!************************************************************************
!
! But:  calcul des coordonnees des vecteurs directeurs du repere orbital local (t,n,w), 
! ===   dans un repere geocentrique inertiel
!
! Historique:
! ==========
!   + Version 2.0 (SP 336 ed01 rev00): creation a partir de la routine MVAXETNW de la MSLIB f77
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!************************************************************************


! Modules
! =======
use int_mslib_mu_prod_vect
use int_mslib_mu_norme

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mo_def_tnw.h'

! Autres declarations
! ===================
real(pm_reel), dimension(3) :: pos(3)
real(pm_reel), dimension(3) :: vit(3)
real(pm_reel), dimension(3) :: wo(3)
real(pm_reel), dimension(3) :: t_intermediaire(3)
real(pm_reel), dimension(3) :: n_intermediaire(3)
real(pm_reel), dimension(3) :: w_intermediaire(3)
real(pm_reel)               :: norme
type(tm_code_retour)        :: code_retour_intermediaire


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mo_def_tnw.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mo_def_tnw.f90,v 1.7 2003/10/14 12:47:23 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
code_retour%valeur = pm_OK
pos(:) = pos_car(:)
vit(:) = vit_car(:)

! calcul du vecteur t_intermediaire tangent au vecteur vitesse
! ............................................................
call mu_norme ( vit, norme, code_retour_intermediaire, vect_norme=t_intermediaire )

if (code_retour_intermediaire%valeur < 0) then
   code_retour%valeur = code_retour_intermediaire%valeur
   go to 6000
else
   code_retour%valeur = code_retour_intermediaire%valeur
end if

! calcul du produit vectoriel p^v
! ...............................
call mu_prod_vect ( pos, vit, wo, code_retour_intermediaire ) ! pas de test du code retour : toujours nul

! calcul du vecteur w_intermediaire designant la direction du moment cinetique
! ............................................................................
call mu_norme ( wo, norme, code_retour_intermediaire, vect_norme=w_intermediaire )

if (code_retour_intermediaire%valeur < 0) then
   code_retour%valeur = code_retour_intermediaire%valeur
   go to 6000
else
   code_retour%valeur = code_retour_intermediaire%valeur
end if

! calcul du produit vectoriel n_intermediaire=w_intermediaire^t_intermediaire
! ...........................................................................
call mu_prod_vect ( w_intermediaire, t_intermediaire, n_intermediaire, code_retour_intermediaire ) ! pas de test du code retour : toujours nul

! Affectation des variables en sortie
! ===================================
t(:) = t_intermediaire(:)
n(:) = n_intermediaire(:)
w(:) = w_intermediaire(:)


6000 continue

code_retour%routine = pm_num_mo_def_tnw
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mo_def_tnw
