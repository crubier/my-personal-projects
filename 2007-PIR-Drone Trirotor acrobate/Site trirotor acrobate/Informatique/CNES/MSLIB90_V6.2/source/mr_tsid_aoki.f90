subroutine mr_tsid_aoki (jul1950, delta_tu1, tsid, code_retour)

! (C) Copyright CNES - MSLIB - 1998

!************************************************************************
!
! But:  Calcul du Temps SIDeral dans le systeme de reference defini par l'IAU en 1980 (AOKI)
! ===
!
! Historique:
! ==========
!   + Version 1.0 (SP 288 ed01 rev00): creation a partir de la routine MRTSMO de la MSLIB f77
!   + Version 2.0 (DE 366 ed01 rev00): utilisation de md_joursec_jourfrac
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!
!************************************************************************


! Modules
! =======
use math_mslib

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib

use int_mslib_md_joursec_jourfrac

! Declarations
! ============
implicit none

include 'arg_mr_tsid_aoki.h'

! Autres declarations
! -------------------

real(pm_reel)   :: tsmo             ! temps sideral moyen calcule
real(pm_reel)   :: dtu              ! nombre de siecles depuis le 01/01/1950 a 0 heure ut1 jusqu'au jour courant jul1950
real(pm_reel)   :: dteta            ! temps sideral avant operation modulo [2*pi]
real(pm_reel)   :: dt_temp          ! temps pour calcul intermediaire


real(pm_reel),  parameter   ::  un=1.0_pm_reel
real(pm_reel),  parameter   ::  secj=86400._pm_reel

! facteurs de transformations : secondes en jour, jours juliens en siecles
real(pm_reel),  parameter   ::  unssec=un/secj, unss=un/36525.0_pm_reel 

! coefficients de calcul pour la formule de reference pour J2000 (Aoki)
! theta = s + db0 + dtu*db1 + dtu**2*db2 + dtu**3*db3
real(pm_reel),  parameter   ::  db0=24110.54841_pm_reel, db1=8640184.812866_pm_reel, db2=0.093104_pm_reel, db3=-6.2e-6_pm_reel

type(tm_jour_sec)    :: jour_TU1                  ! jul1950 ramenees au temps TU1 pour l appel a md_joursec_jourfrac
type(tm_code_retour) :: code_retour_local

intrinsic  modulo


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mr_tsid_aoki.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mr_tsid_aoki.f90,v 1.7 2003/10/14 12:49:20 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
code_retour%valeur = pm_OK

!      -----------------------------------------------------------------
!      Aoki, reference de datation le 01/01/2000 a 12 heures ut1:                   
!                    dtu = dtu0 - 0.5
!      avec dtu0=nbre de siecle julien ecoule depuis 
!            le 1/1/1950 a 0h ut1 jusqu'a la date de calcul
!      -----------------------------------------------------------------

jour_TU1%jour = jul1950%jour
jour_TU1%sec  = jul1950%sec + delta_tu1

call md_joursec_jourfrac ( jour_TU1, dt_temp, code_retour_local ) ! code_retour_local%valeur = 0 est le seul retour possible => non teste

dtu   = dt_temp * unss - 0.5_pm_reel
dteta = jour_TU1%sec + ((db3*dtu + db2) * dtu + db1) * dtu + db0
tsmo  = modulo(dteta,secj)
tsid  = tsmo * pm_deux_pi * unssec


6000 continue

code_retour%routine = pm_num_mr_tsid_aoki
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mr_tsid_aoki
