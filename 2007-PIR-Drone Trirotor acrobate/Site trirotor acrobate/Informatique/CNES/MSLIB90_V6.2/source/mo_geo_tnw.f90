subroutine mo_geo_tnw (pos_car, vit_car, vect_geo, vect_tnw, code_retour)

! (C) Copyright CNES - MSLIB - 1998

!************************************************************************
!
! But:  Passage dans le repere orbital local (t, n, w) d'un vecteur quelconque.
! ===
!
! Note d'utilisation:  La transformation inverse peut s'effectuer par mo_tnw_geo.
! ==================   
!
! Historique:
! ==========
!   + Version 1.0 (SP 220 ed01 rev00): creation a partir de la routine MV0RVI de la MSLIB f77
!   + Version 2.0 (DE 369 ed01 rev00): utilisation de la routine mo_def_tnw
!                                      suppression du parametre eps_100 (non utilise)
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!
!************************************************************************


! Modules
! =======
use int_mslib_mo_def_tnw

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mo_geo_tnw.h'

! Autres declarations
! -------------------

real(pm_reel), dimension(3) :: t, n, w                        ! directions du repere (t, n, w)
type(tm_code_retour)        :: code_retour_local


intrinsic dot_product

character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mo_geo_tnw.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mo_geo_tnw.f90,v 1.7 2003/10/14 12:47:34 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
code_retour%valeur = pm_OK

call mo_def_tnw ( pos_car, vit_car, t, n, w, code_retour_local)
if (code_retour_local%valeur < 0) then
   code_retour%valeur = code_retour_local%valeur
   go to 6000
else
   code_retour%valeur = code_retour_local%valeur
end if

! calcul des composantes du vecteur dans (t,n,w)
! ==============================================

vect_tnw (1) = dot_product(vect_geo,t) ! composante selon l'axe t
vect_tnw (2) = dot_product(vect_geo,n) ! composante selon l'axe n
vect_tnw (3) = dot_product(vect_geo,w) ! composante selon l'axe w

6000 continue

code_retour%routine = pm_num_mo_geo_tnw
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mo_geo_tnw
