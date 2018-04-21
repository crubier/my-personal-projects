function mui_axe_norme_quat (axe_norme, angle )

! (C) Copyright CNES - MSLIB - 2003

!************************************************************************
!
! But:  Conversion d'une rotation definie par son AXE norme et son ANGLE en QUATernion.
! ===
!
! Note d'utilisation:  ATTENTION: 
! ==================
!                            * fonction dediee aux axes de norme 1, tels les axes canoniques X, Y ou Z
!                            * pas de test effectue sur la norme de l'axe
!                            * equivalent a la routine mu_axe_angle_quat sans les tests pour 
!                              des raisons de gain en temps calcul
! Historique:
! ==========
! 
!   + Version 5.0 (SP 608 ed01 rev00): creation par transfert de la routine de meme nom de la MSPRO
!
!************************************************************************


! Modules
! =======
use math_mslib

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mui_axe_norme_quat.h'

! Autres declarations
! -------------------
type(tm_quat)                          ::  quat        ! quaternion norme              
real(pm_reel)                          :: anglemod
intrinsic modulo, cos, sin



character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mui_axe_norme_quat.f90: derniere modification V5.0 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mui_axe_norme_quat.f90,v 1.3 2003/12/15 17:36:13 mslibdev Exp $ '

!************************************************************************

anglemod = modulo (angle, pm_deux_pi)                               !conversion de l'angle sur [0,2pi[
quat%q0      = cos (anglemod / 2._pm_reel)                          !calcul du quaternion equivalent
quat%q123(:) = sin (anglemod / 2._pm_reel) * axe_norme

mui_axe_norme_quat%q0 = quat%q0
mui_axe_norme_quat%q123(:)= quat%q123(:)


end function mui_axe_norme_quat
