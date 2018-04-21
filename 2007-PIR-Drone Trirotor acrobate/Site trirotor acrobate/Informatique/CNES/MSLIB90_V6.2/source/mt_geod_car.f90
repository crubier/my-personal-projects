subroutine mt_geod_car ( pos_geod, r_equa, apla, pos_car, code_retour, jacob)

! (C) Copyright CNES - MSLIB - 1998-2003

!************************************************************************
!
! But:  Passage des coordonnees GEODesiques aux coordonnees CARtesiennes
! ===
!
! Note d'utilisation: 1) La transformation inverse peut s'effectuer par mt_car_geod.
! ==================  2) L'aplatissement f doit appartenir a [0.,1.[.
!                        Aucun test n'est effectue sur f < 0.
!                     3) Le rayon equatorial doit etre > 0. : aucun test n'est effectue ici.
! Historique:
! ==========
!   + Version 1.0 (SP 248 ed01 rev00): creation a partir de la routine MVELCA de la MSLIB f77
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!   + Version 4.1 (DE 486 ed01 rev00) : calcul de la jacobienne
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

include 'arg_mt_geod_car.h'

! Autres declarations
! -------------------

real(pm_reel)  :: latitude,longitude     ! latitude et longitude exprimes en radians
real(pm_reel)  :: ex2,correc,Rphi        ! ex2 = terme permettant la correction du rayon en fonction de la latitude          
                                         ! correc = correction de rayon
                                         ! Rphi  = rayon terrestre a la latitude donnee

real(pm_reel):: K, KRphiplusH, RphiplusH ! variables de calcul pour la jacobienne

intrinsic sin, cos, sqrt


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mt_geod_car.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mt_geod_car.f90,v 1.10 2003/10/14 12:52:33 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
code_retour%valeur = pm_OK

! verification des donnees d'entree
!..................................
if (apla >= 1._pm_reel) then
   code_retour%valeur = pm_err_apla_sup1
   go to 6000
end if

latitude = pos_geod%lat
longitude = pos_geod%long

ex2 = apla * (2._pm_reel - apla)           

correc = 1._pm_reel - ex2 * (sin(latitude)**2) ! correc est > 0.
                                               ! correc peut etre nul si apla=1: impossible a ce stade des calculs
Rphi = r_equa / sqrt (correc)                  ! rayon a la latitude donnee

RphiplusH = Rphi + pos_geod%haut

! calcul des coordonnees x,y,z
! ============================
pos_car(1) = RphiplusH * cos (latitude) * cos (longitude)
pos_car(2) = RphiplusH * cos (latitude) * sin (longitude)
pos_car(3) = (Rphi * (1._pm_reel - ex2) + pos_geod%haut) * sin (latitude)

if (present(jacob)) then

   K = (1._pm_reel - ex2)/ correc  ! K dans [0,1]
  ! si apla = 0 : exc2 = 0 ; correc = 1 ; Rphi = r_equa; K = 1

   KRphiplusH = K*Rphi + pos_geod%haut

   jacob(1,1) = - KRphiplusH * sin(latitude)*cos(longitude)
   jacob(1,2) = - RphiplusH * cos(latitude)*sin(longitude)
   jacob(1,3) =   cos(latitude)*cos(longitude)

   jacob(2,1) = - KRphiplusH * sin(latitude)*sin(longitude)
   jacob(2,2) =   RphiplusH * cos(latitude)*cos(longitude)
   jacob(2,3) =   cos(latitude)*sin(longitude)

   jacob(3,1) =   KRphiplusH * cos(latitude)
   jacob(3,2) =   0._pm_reel
   jacob(3,3) =   sin(latitude)

end if

6000 continue

code_retour%routine = pm_num_mt_geod_car
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mt_geod_car
